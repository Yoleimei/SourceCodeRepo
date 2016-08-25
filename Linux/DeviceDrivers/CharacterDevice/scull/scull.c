#include <linux/init.h>
#include <linux/module.h>
#include <linux/types.h>
#include <linux/fs.h>
#include <linux/errno.h>
#include <linux/mm.h>
#include <linux/sched.h>
#include <linux/cdev.h>
#include <linux/slab.h>
#include <asm/io.h>
#include <asm/switch_to.h>
#include <asm/uaccess.h>

static int scull_major = 0;
static int scull_minor = 0;
static int scull_quantum = 4000;
static int scull_qset = 4000;

struct scull_qset {
	void **data;
	struct scull_qset *next;
};

struct scull_dev 
{
	struct cdev cdev;         // char device structure
	struct scull_qset *data;  //
	int quantum;
	int qset;
	unsigned long size;
	unsigned int access_key; //
	struct semaphore sem;
};
struct scull_dev *scull_devp;

struct scull_qset *scull_follow(struct scull_dev *dev, int n)
{
	struct scull_qset *dptr = dev->data;
	if (!dptr) {
		dev->data = kmalloc(sizeof(struct scull_qset), GFP_KERNEL);
		dptr = dev->data;
		if (dptr == NULL)
			return NULL;
		memset(dptr, 0, sizeof(struct scull_qset);
	}
	while (n--) {
		if (!dptr->next) {
			dptr->next = kmalloc(sizeof(struct scull_qset), GFP_KERNEL);
			if (dptr->next == NULL)
				return NULL;
			memset(dptr->next, 0, sizeof(struct scull_qset));
		}
		dptr = dptr->next;
		continue;
	}
	return dptr;
}

int scull_trim(struct scull_dev *dev)
{
	struct scull_qset *next, *dptr;
	int qset = dev->qset;
	int i;
	for (dptr = dev->data; dptr; dptr = next) {
		if (dptr->data) {
			for (i = 0; i < qset; i++) 
				kfree(dptr->data[i]);
			kfree(dptr->data);
			dptr->data = NULL;
		}
		next = dptr->next;
		kfree(dptr);
	}
	dev->size = 0;
	dev->quantum = scull_quantum;
	dev->qset = scull_qset;
	dev->data = NULL;
	return 0;
}

int scull_open(struct inode *inode, struct file *filp)
{
	struct scull_dev *dev;
	dev = container_of(inode->i_cdev, struct scull_dev, cdev);
	filp->private_data = dev;
	if ((filp->f_flags & O_ACCMODE) == O_WRONLY) {
		scull_trim(dev);
	}
	return 0;
}

int scull_release(struct inode *inode, struct file *filp)
{
	return 0;
}

static ssize_t scull_read(struct file *filp, char __user *buf, size_t count, loff_t *f_pos)
{
	ssize_t ret = 0;
	struct scull_dev *dev = filp->private_data;
	struct scull_qset *dptr;
	int quantum = dev->quantum, qset = dev->qset;
	int itemsize = quantum * qset;
	int item, s_pos, q_pos, rest;

	if (down_interruptible(&dev->sem))
		return -ERESTARTSYS;
	if (*f_pos >= dev->size)
		goto out;
	if (*f_pos + count > dev->size)
		count = dev->size - *f_pos;
	
	item = (long)*f_pos / itemsize;
	rest = (long)*f_pos % itemsize;
	s_pos = rest / quantum;
	q_pos = rest % quantum;
	
	dptr = scull_follow(dev, item);
	if (dptr == NULL || !dptr->data || !dptr->data[s_pos])
		goto out;
	
	if (count > quantum - q_pos)
		count = quantum - q_pos;
	
	if (copy_to_user(buf, dptr->data[s_pos], count)) {
		ret = -EFAULT;
		goto out;
	}
	*f_pos += count;
	ret = count;

	printk(KERN_INFO "read %d bytes(s) from %lu\n", count, f_pos);

out:
	up(&dev->sem);
	return ret;
}

static ssize_t scull_write(struct file *filp, const char __user *buf, size_t count, loff_t *f_pos)
{
	ssize_t ret = -ENOMEM;
	struct scull_dev *dev = filp->private_data;
	struct scull_qset *dptr;
	int quantum = dev->quantum, qset = dev->qset;
	int itemsize = quantum * qset;
	int item, s_pos, q_pos, rest;

	if (down_interruptible(&dev->sem))
		return -ERESTARTSYS;
	
	item = (long)*f_pos / itemsize;
	rest = (long)*f_pos % itemsize;
	s_pos = rest / quantum;
	q_pos = rest % quantum;
	dptr = scull_follow(dev, item);
	if (dptr == NULL)
		goto out;
	if (!dptr->data) {
		dptr->data = kmalloc(qset * sizeof(char *), GFP_KERNEL);
		if (!dptr->data)
			goto out;
		memset(dptr->data, 0, qset * sizeof(char *));
	}
	if (!dptr->data[s_pos]) {
		dptr->data[s_pos] = kmalloc(quantum, GFP_KERNEL);
		if (!dptr->data[s_pos])
			goto out;
	}

	if (count > quantum - q_pos)
		count = quantum - q_pos;
	if (copy_from_user(dev->data[s_pos] + q_pos, buf, count)) {
		ret = -EFAULT;
		goto out;
	}
	*f_pos += count;
	ret = count;
	
	if (dev->size < *f_pos)
		dev->size = *f_pos;

	printk(KERN_INFO "written %d bytes(s) from %lu\n", count, f_pos);

out:
	up(&dev->sem);
	return ret;
}

static const struct file_operations scull_fops = 
{
	.owner   = THIS_MODULE,
	.read    = scull_read,
	.write   = scull_write,
	.open    = scull_open,
	.release = scull_release,
};

static void scull_setup_cdev(struct scull_dev *dev, int index)
{
	int err, devno = MKDEV(scull_major, scull_minor + index);

	cdev_init(&dev->cdev, &scull_fops);
	dev->cdev.owner = THIS_MODULE;
	dev->cdev.ops = &scull_fops;
	err = cdev_add(&dev->cdev, devno, 1);
	if (err)
		printk(KERN_NOTICE "Error %d adding scull%d", err, index);
}

static int scull_init(void)
{
	int result;
	size_t len;
	dev_t devno = MKDEV(scull_major, 0);
	
	if (scull_major)
		result = register_chrdev_region(devno, 2, "scull");
	else {
		result = alloc_chrdev_region(&devno, 0, 2, "scull");
		scull_major = MAJOR(devno);
	}
	if (result < 0)
		return result;

	scull_devp = kmalloc(2*sizeof(struct scull_dev), GFP_KERNEL);
	if (!scull_devp) {
		result = -ENOMEM;
		goto fail_malloc;
	}
	len = sizeof(struct scull_dev);
	memset(scull_devp, 0, 2*len);

	scull_setup_cdev(&scull_devp[0], 0);
	scull_setup_cdev(&scull_devp[1], 1);
	return 0;

fail_malloc:
	unregister_chrdev_region(devno, 1);
	return result;
}

static void scull_exit(void)
{
	cdev_del(&(scull_devp[0].cdev));
	cdev_del(&(scull_devp[1].cdev));
	kfree(scull_devp);
	unregister_chrdev_region(MKDEV(scull_major, 0), 2);
}

MODULE_LICENSE("Dual BSD/GPL");

module_param(scull_major, int, S_IRUGO);

module_init(scull_init);
module_exit(scull_exit);

