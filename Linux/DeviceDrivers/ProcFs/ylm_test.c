#include <linux/proc_fs.h>
#include <linux/seq_file.h>
#include <linux/time.h>

#define PROC_PATH_NAME "ylm_test"
#define TIMEZONE_NAME "timezone"

static int ylm_test_proc_show(struct seq_file *seq, void *v)
{
	char *filename = (char *)seq->private;

	if (!strcmp(TIMEZONE_NAME, filename)) {
		char strtm[128];
		char *strtm2 = &strtm[0];
		memset (strtm, 0, sizeof(strtm));
		sprintf(&strtm[0]
			, "tz_minuteswest=%d\n"
			, sys_tz.tz_minuteswest);
		while (*strtm2) {
			seq_putc(seq, *strtm2++);
		}
	}

	return 0;
}

static int ylm_test_proc_open(struct inode *inode, struct file *file)
{
	return single_open(file, ylm_test_proc_show, file->f_path.dentry->d_iname);
}

static const struct file_operations ylm_test_proc_fops = {
	.open    = ylm_test_proc_open,
	.read    = seq_read,
	.llseek  = seq_lseek,
	.release = single_release,
};

static int __init proc_ylm_test_init(void)
{
	proc_mkdir(PROC_PATH_NAME, NULL);
	proc_create(PROC_PATH_NAME"/"TIMEZONE_NAME, S_IRUSR, NULL, &ylm_test_proc_fops);

	return 0;
}

module_init(proc_ylm_test_init);
