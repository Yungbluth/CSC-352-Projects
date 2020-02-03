//By: Matthew Yungbluth

#include <linux/fs.h>
#include <linux/init.h>
#include <linux/miscdevice.h>
#include <linux/module.h>
#include <linux/random.h>
#include <asm/uaccess.h>

unsigned char get_random_byte(int max);

static ssize_t dice_read(struct file * file, char * buf, 
			  size_t count, loff_t *ppos)
{
	int len = 0;
	while(count > len) {
		//Loops until we get a long enough length
		*buf = get_random_byte(6);
		buf = buf + 1;
		len++;
	}
	*ppos = len;
	return len;
}

unsigned char get_random_byte(int max) {
	unsigned char c;
	get_random_bytes(&c, 1);
	return ((c%max) + 1);
}

static const struct file_operations dice_fops = {
	.owner		= THIS_MODULE,
	.read		= dice_read,
};

static struct miscdevice dice_dev = {
	MISC_DYNAMIC_MINOR,
	"dice",
	&dice_fops
};

static int __init
dice_init(void)
{
	int ret;
	ret = misc_register(&dice_dev);
	if (ret)
		printk(KERN_ERR
		       "Unable to register dice misc device\n");

	return ret;
}

module_init(dice_init);

static void __exit
dice_exit(void)
{
	misc_deregister(&dice_dev);
}

module_exit(dice_exit);

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Matthew Yungbluth");
MODULE_DESCRIPTION("Dice Roll Driver");
MODULE_VERSION("dev");
