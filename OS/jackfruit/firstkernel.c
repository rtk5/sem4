#include <linux/init.h> // Macros for initialization and cleanup
#include <linux/module.h> // Core header for modules
#include <linux/kernel.h> // Kernel log levels
MODULE_LICENSE("GPL"); // License type
MODULE_AUTHOR("Your Name"); // Author information
MODULE_DESCRIPTION("A simple kernel module");
MODULE_VERSION("1.0");
// Initialization function
static int __init hello_init(void) {
 printk(KERN_INFO "Hello, Kernel!\n"); // Print to kernel log
 return 0; // 0 means successful loading
}
// Cleanup function
static void __exit hello_exit(void) {
 printk(KERN_INFO "Goodbye, Kernel!\n");
}
// Register the functions
module_init(hello_init);
module_exit(hello_exit);