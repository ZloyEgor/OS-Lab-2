#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <string.h>

#define IFNAMSIZ 16

#define __NR_lab_net_device 453

static struct lab_net_device_info {
    char name[IFNAMSIZ];
    unsigned long watchdog_timeo;
    unsigned char irq;
};

static long __lab_net_device(char* device_name, struct lab_net_device_info *net_device_info) {
    return syscall(__NR_lab_net_device, device_name, strlen(device_name), net_device_info);
}

static void print_net_device(struct lab_net_device_info *info) {
    printf("Name:\t\t%s\n", info->name);
//    printf("trans_start:\t%ld\n", info->trans_start);
    printf("watchdog_timeo:\t%ld\n", info->watchdog_timeo);
    printf("irq:\t\t%c\n", info->irq);
//    printf("mem_end:\t%ld\n", info->mem_end);
//    printf("mem_start:\t%ld\n", info->mem_start);
//    printf("base_addr:\t%ld\n", info->base_addr);
//    printf("dma:\t\t%c\n", info->dma);
}

int main(int argc, char **argv) {
    if (argc <= 1) {
        printf("Please specify name of device\n");
        return -1;
    }
    if (argc > 2) {
        printf("Too many arguments, please specify name of device\n");
        return -1;
    }
    char* device_name = *(argv + 1);

    struct lab_net_device_info *info = malloc(sizeof(struct lab_net_device_info));

    long ret_code = __lab_net_device(device_name, info);

    if(ret_code < 0) {
        printf("System call __lab_net_device error occurred\n");
        free(info);
        return -1;
    }

    print_net_device(info);
    free(info);
    return 0;
}
