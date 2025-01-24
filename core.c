#include <linux/init.h>
#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/fs.h>
#include <linux/uaccess.h>
#include <linux/ioctl.h>

#define MY_IOCTL_CMD _IOWR('a', 'b', struct my_struct *)

struct my_struct {
    int id;
    char name[64];
};

static long my_ioctl(struct file *file, unsigned int cmd, unsigned long arg) {
    struct my_struct data;
    struct my_struct __user *user_data = (struct my_struct __user *)arg;

    switch (cmd) {
        case MY_IOCTL_CMD:
            // Пример заполнения структуры
            data.id = 1;
            strncpy(data.name, "Example Name", sizeof(data.name));

            if (copy_to_user(user_data, &data, sizeof(data))) {
                return -EFAULT;
            }
            break;
        default:
            return -EINVAL;
    }
    return 0;
}

static const struct file_operations my_fops = {
    .unlocked_ioctl = my_ioctl,
};

static int __init my_init(void) {
    printk(KERN_INFO "My module loaded\n");
    register_chrdev(240, "my_dev", &my_fops);
    return 0;
}

static void __exit my_exit(void) {
    unregister_chrdev(240, "my_dev");
    printk(KERN_INFO "My module unloaded\n");
}

module_init(my_init);
module_exit(my_exit);

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Your Name");
MODULE_DESCRIPTION("A simple ioctl example");

