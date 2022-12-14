#include <linux/netdevice.h>
#include <linux/module.h>
#include <linux/syscalls.h>

#define COPY_TO_USER_S(dest, src, size)                                        \
	if (copy_to_user(dest, src, size))                                     \
		return -EFAULT;

#define COPY_TO_USER(dest, src) COPY_TO_USER_S(&dest, &src, sizeof(dest))

#define COPY_FROM_USER(dest_struct, src_struct, size)                          \
	if (copy_from_user(dest_struct, src_struct, size))                     \
		return -EFAULT;

struct lab_net_device_info {
    char name[IFNAMSIZ];
    unsigned long watchdog_timeo;
    unsigned long mem_start;
    unsigned long mem_end;
    unsigned long base_addr;
    unsigned char irq;
    unsigned char dma;
};

SYSCALL_DEFINE3(lab_net_device, char *, device_name, size_t, device_name_len, struct lab_net_device_info *, net_device_info)
{
    char *device_name_from_user = (char *) kmalloc(sizeof(char) * device_name_len, GFP_KERNEL);

    COPY_FROM_USER(device_name_from_user, device_name, sizeof(char) * device_name_len);

    struct net_device *device = dev_get_by_name(&init_net, device_name_from_user);

    if(!device) {
        printk(KERN_ERR "Can't obtain device\n");
        kfree(device_name_from_user);
        return -1;
    }
    printk(KERN_INFO "lab_net_device: name: %s\n", device->name);

    COPY_TO_USER(net_device_info->name, device->name);
    COPY_TO_USER(net_device_info->watchdog_timeo, device->watchdog_timeo);
    COPY_TO_USER(net_device_info->mem_start, device->mem_start);
    COPY_TO_USER(net_device_info->mem_start, device->mem_start);
    COPY_TO_USER(net_device_info->mem_end, device->mem_end);
    COPY_TO_USER(net_device_info->base_addr, device->base_addr);
    COPY_TO_USER(net_device_info->irq, device->irq);
    COPY_TO_USER(net_device_info->dma, device->dma);

    kfree(device_name_from_user);
    kfree(device);
    return 0;
}