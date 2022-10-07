#include <linux/module.h>
#include  <linux/fs.h>
#include <linux/cdev.h>
dev_t Device_ID;

struct cdev pcd_cdev;
struct file_operations pcd_fops;


static int __init pcd_module_init(void)
{
	printk(KERN_INFO"Init called\n");
	
	/*Allocate device number*/
	alloc_chrdev_region(&Device_ID,0,1,"PCD");
	/*Initialize the 	cdev and fops*/
	cdev_init(&pcd_cdev,&pcd_fops);
	pcd_cdev.owner=THIS_MODULE;

	/*Register Cdev with VFS*/
	cdev_add(&pcd_cdev,Device_ID,1);
	

	pr_info("PCD mdule Init called\n");
	return 0;

}


static void __exit pcd_module_exit(void)
{
	pr_info("PCD mdule exit called\n");
}


loff_t pcd_llseek (struct file *filep, loff_t off, int whence)
{
	return 0;

}
ssize_t pcd_read (struct file *filep, char __user *user_datap, size_t count, loff_t *offp)
{
	return 0;

}
ssize_t pcd_write(struct file *filep, const char __user *user_datap, size_t count, loff_t * offp)
{
	return 0;

}


int pcd_open(struct inode* inode, struct file* filep)
{

	return 0;
}

int pcd_release(struct inode* inode, struct file* filep)
{
	
	return 0;
}
module_init(pcd_module_init);
module_exit(pcd_module_exit);

MODULE_LICENSE("GPL");
MODULE_AUTHOR("RAGHU");
MODULE_DESCRIPTION("pcd BBB");
MODULE_INFO(board,"beaglebone black rev-c");


