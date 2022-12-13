#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <string.h>

#define IFNAMSIZ 16

#define __NR_lab_net_device 453

static struct lab_net_device_info {
    char name[IFNAMSIZ];
    unsigned long rmem_end;
    unsigned long rmem_start;
    unsigned long mem_end;
    unsigned long mem_start;
    unsigned long base_addr;
    unsigned char dma;
}

static long __lab_net_device_info(struct lab_net_device_info *net_device_info) {
    return syscall(__NR_lab_net_device, net_device_info);
}

static void print_net_device(struct lab_net_device_info *info) {
    printf("Name:\t%s\n", info->name);
    printf("rmem_start:\t%s\n", info->rmem_start);
    printf("rmem_end:\t%s\n", info->rmem_end);
    printf("mem_start:\t%s\n", info->mem_start);
    printf("mem_end:\t%s\n", info->mem_end);
    printf("base_addr:\t%s\n", info->base_addr);
    printf("dma:\t%s\n", info->dma);
}

int main(int argc, char **argv) {
    if (argc == 0) {
        printf("Please specify name of device\n");
        return -1;
    }
    if (argc > 1) {
        printf("Too many arguments, please specify name of device\n");
        return -1;
    }
    char* device_name = *argv;

    struct lab_net_device_info *info = malloc(sizeof(struct lab_net_device_info));

    long ret_code = __lab_net_device(device_name, strlen(device_name), info);

    if(ret_code < 0) {
        printf("System call __lab_net_device error occurred\n");
        free(info);
        return -1;
    }

    print_net_device(info);
    free(info);
    return 0;
}