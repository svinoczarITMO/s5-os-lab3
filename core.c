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
    int swag_percent;
    char birth_date[64];
};

static long my_ioctl(struct file *file, unsigned int cmd, unsigned long arg) {
    struct my_struct data;
    struct my_struct __user *user_data = (struct my_struct __user *)arg;

    switch (cmd) {
        case MY_IOCTL_CMD:
            data.id = 52;
            strncpy(data.name, "Mr. Serge K.", sizeof(data.name) - 1);
            data.swag_percent = 110;
            strncpy(data.birth_date, "Svoevremenno", sizeof(data.birth_date) - 1);
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
    printk(KERN_INFO "KSV join his shelter\n");
    register_chrdev(240, "ksv_shelter", &my_fops);
    return 0;
}

static void __exit my_exit(void) {
    unregister_chrdev(240, "ksv_shelter");
    printk(KERN_INFO "KSV left his shelter\n");
}

module_init(my_init);
module_exit(my_exit);

MODULE_LICENSE("GPL");
MODULE_AUTHOR("svinoczar");
MODULE_DESCRIPTION("Shelter of KSV");
