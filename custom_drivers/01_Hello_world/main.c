#include <linux/module.h>
static int __init HW_module_init(void)
{
	pr_info("Hello From HW_module\n");
	return 0;

}


static void __exit HW_module_exit(void)
{
	pr_info("Bye! From HW_module\n");
}


module_init(HW_module_init);
module_exit(HW_module_exit);

MODULE_LICENSE("GPL");
MODULE_AUTHOR("RAGHU");
MODULE_DESCRIPTION("Hello Word BBB");
MODULE_INFO(board,"beaglebone black rev-c");


