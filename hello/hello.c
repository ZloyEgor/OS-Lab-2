#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/syscalls.h>

asmlinkage long __arm64_sys_hello(int i)
{
        printk("Hello world\n");
        return 0;
}
