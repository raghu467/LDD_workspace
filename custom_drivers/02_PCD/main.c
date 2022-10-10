#include <linux/module.h>
#include  <linux/fs.h>
#include <linux/cdev.h>
#include <linux/device.h>
#include <linux/uaccess.h>

//debug helper macros:

#define pr_fmt(fmt)  "%s :"fmt,__func__
#define PCD_MAX_DEV_BUFFER_SIZE 512

dev_t Device_ID;
struct class *PCD_Class;
struct device *PCD_Device;

struct cdev pcd_cdev;

//Device Buffer
char PCD_Device_buffer[PCD_MAX_DEV_BUFFER_SIZE];


loff_t pcd_llseek (struct file *filep, loff_t off, int whence)
{
	loff_t temp=0;
	pr_info("pcd llseek requesed\n");
	pr_info("pcd llseek requesed %lld bytes current_offset:%lld\n",off,filep->f_pos);
	

	/* seek set */

	switch(whence)
	{
		case SEEK_SET:
			if((off)>PCD_MAX_DEV_BUFFER_SIZE ||(off)<0 )
			{
				return(-EINVAL);
			}
			filep->f_pos=off;
		break;
		case SEEK_CUR:
			temp=filep->f_pos+off;
			if((temp )>PCD_MAX_DEV_BUFFER_SIZE || temp<0 )
			{
				return(-EINVAL);
			}
			else
			{
				filep->f_pos=temp;
			}
			
		break;
		case SEEK_END:
			temp=PCD_MAX_DEV_BUFFER_SIZE+off;
			if((temp>PCD_MAX_DEV_BUFFER_SIZE) || (temp<0))
			{
				return(-EINVAL);
			}
			else
			{
				filep->f_pos=temp;
			}
		break;
		default:
			return(-EINVAL);

	}
	pr_info(" new value of fpos=%lld \n",filep->f_pos);
	return filep->f_pos;

}
ssize_t pcd_read (struct file *filep, char __user *user_datap, size_t count, loff_t *offp)
{
	pr_info("pcd_read  requesed %zu bytes f_offset:%lld\n",count,*offp);
	/* check if we can read the requested count. */
	if((*offp+count)>PCD_MAX_DEV_BUFFER_SIZE)
	{
		count=PCD_MAX_DEV_BUFFER_SIZE-*offp;//only so many bytes can be copies 
	}

	/* copy to user */
	if(copy_to_user((void*)user_datap,&PCD_Device_buffer[*offp],count))
	{
		return(-EFAULT);
	}
	*offp+=count;

	pr_info("count=%zu",count);
	pr_info("file_offset=%lld",*offp);



	return count;

}
ssize_t pcd_write(struct file *filep, const char __user *user_datap, size_t count, loff_t * offp)
{
	pr_info("pcd write  requesed %zu bytes f_offset:%lld\n",count,*offp);
	/* check if we can read the requested count. */
	if((*offp+count)>PCD_MAX_DEV_BUFFER_SIZE)
	{
		 count=PCD_MAX_DEV_BUFFER_SIZE-*offp;//only so many bytes can be writen to device
	}

	/*check if reached end of file */
	if(!count)
	{
		pr_info("device out of memory\n");
		return (-ENOMEM);
	}
	/* copy to user */
	if(copy_from_user(&PCD_Device_buffer[*offp],user_datap,count))
	{
		return(-EFAULT);
	}
	*offp+=count;
	
	pr_info("count=%zu",count);
	pr_info("file_offset=%lld\n",*offp);

	return count;
}


int pcd_open(struct inode* inode, struct file* filep)
{
	pr_info("pcd_open  requesed\n");
	return 0;
}

int pcd_release(struct inode* inode, struct file* filep)
{
	pr_info("pcd_release  requesed\n");


	return 0;
}

struct file_operations pcd_fops={
	.open=pcd_open,
	.release=pcd_release,
	.read=pcd_read,
	.write=pcd_write,
	.llseek=pcd_llseek,
	.owner= THIS_MODULE


};


static int __init pcd_module_init(void)
{
	printk(KERN_INFO"Init called\n");
	
	/*Allocate device number*/
	alloc_chrdev_region(&Device_ID,0,1,"pcd");

	//debug:
	pr_info("Device M=%d MI=%d\n", MAJOR(Device_ID),MINOR(Device_ID));

	/*Initialize the 	cdev and fops*/
	cdev_init(&pcd_cdev,&pcd_fops);
	pcd_cdev.owner=THIS_MODULE;

	/*Register Cdev with VFS*/
	cdev_add(&pcd_cdev,Device_ID,1);


	// create device class under sysclass
	PCD_Class=class_create(THIS_MODULE,"pcd_class");

	//Populate the device file under class in sysfs

	PCD_Device=device_create(PCD_Class,NULL,Device_ID,NULL,"pcd");


	

	pr_info("PCD mdule Init called\n");
	return 0;

}


static void __exit pcd_module_exit(void)
{
	pr_info("PCD mdule exit called\n");

	//device destroy
	device_destroy(PCD_Class,Device_ID);


	//class destroy
	class_destroy(PCD_Class);
	

	//cdev_Remove
	cdev_del(&pcd_cdev);
	
	//un-register char dev region
	unregister_chrdev_region(Device_ID,1);

	pr_info("pcd_release  Module Unload complete\n");
}



module_init(pcd_module_init);
module_exit(pcd_module_exit);

MODULE_LICENSE("GPL");
MODULE_AUTHOR("RAGHU");
MODULE_DESCRIPTION("pcd BBB");
MODULE_INFO(board,"beaglebone black rev-c");


