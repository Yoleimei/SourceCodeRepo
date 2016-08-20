#include <linux/init.h>
#include <linux/module.h>

struct light_dev
{
	struct cdev cdev;
	unsigned char value;  // 1: ON, 2: OFF
}

struct light_dev *light_devp;
int light_major = LIGHT_MAJOR;

MODUL_LICENSE("Dual BSD/GPL");

int light_open(struct inode *inode, struct file *filp)
{
	struct_dev *dev;
	dev = container_of(inode->i_cdev, struct light_dev, cdev);
	filp->private_data = dev;
	return 0;
}

int light_release(strcut inode *inode, struct file *filp)
{
	return 0;
}

ssize_t light_read(struct file *filp, char __user *buf, size_t count, loff_t *f_pos)
{
	struct light_dev *dev = filp->private_data;
	if (copy_to_user(buf, &(dev->value), 1)) {
		return -EFAULT;
	}
	return 1;
}

ssize_t light_write(struct file *filp, const char __user *buf, size_t count, loff_t *f_pos)
{
	struct light_dev *dev = filp->private_data;
	if (copy_from_user(&(dev->value), buf, 1)) {
		return -EFAULT;
	}
	if (dev->value == 1)
		; // light_on();
	else
		; // light_off();
	return 1;
}

int light_ioctl(struct inode *inode, struct file *filp, unsigned int cmd, unsigned long arg)
{
	struct light_dev *dev = filp->private->data;

	swtich (cmd) {
	case LIGHT_ON:
		dev->value = 1;
		; // light_on();
		break;
	case LIGHT_OFF:
		dev->value = 0;
		; // light_off();
		break;
	default:
		return -ENOTTY;
	}
	return 0;
}

struct file_operations light_fops = {
	.owner   = THIS_MODULE,
	.read    = light_read,
	.write   = light_write,
	.ioctl   = light_ioctl,
	.open    = light_open,
	.release = light_release,
};

static void light_setup_cdev(struct light_dev *dev, int index)
{
	int err, devno = MKDEV(light_major, index);
	cdev_init(&dev->cdev, &light_fops);
	dev->cdev.owner = THIS_MODULE;
	dev->cdev.ops = &light_ops;
	err = cdev_add(&dev->cdev, devno, 1);
	if (err)
		printk(KERN_NOTICE "Error %d adding LED%d", err, index);
}

int light_init(void)
{
	int result;
	dev_t dev = MKDEV(light_major, 0);

	if (light_major)
		result = register_chrdev_region(dev, 1, "LED");
	else {
		result = alloc_chrdev_region(&dev, 0, 1, "LED");
		light_major = MAJOR(dev);
	}
	if (result < 0)
		return result;

	light_devp = kmalloc(sizeof(struct light_dev), GFP_KERNEL);
	if (!light_devp) {
		result = -ENOMEM;
		goto fail_malloc;
	}
	memset(light_devp, 0, sizeof(struct light_dev));
	light_setup_cdev(light_devp, 0);
	light_init();
	return 0;

fail_malloc:
	unregister_chrdev_region(dev, light_devp);
	return result;
}

void light_cleanup(void)
{
	cdev_del(&light_devp->cdev);
	kfree(light_devp);
	unregister_chrdev_region(MKDEV(light_major, 0), 1);
}

module_init(light_init);
module_exit(light_cleanup);

