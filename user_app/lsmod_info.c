#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <string.h>

#define MODULE_NAME_LEN (64 - sizeof(unsigned long))

#define __NR_lab_lsmod_count 451
#define __NR_lab_lsmod 452

static enum module_state {
	MODULE_STATE_LIVE, /* Normal state. */
	MODULE_STATE_COMING, /* Full formed, running module_init. */
	MODULE_STATE_GOING, /* Going away. */
	MODULE_STATE_UNFORMED, /* Still setting it up. */
};

static struct lab_lsmod_module_info {
	enum module_state state;
	unsigned int size;
	int references_count;
	char name[MODULE_NAME_LEN];
};

static long __lab_lsmod(struct lab_lsmod_module_info *modules_ptr) {
	return syscall(__NR_lab_lsmod, modules_ptr);
}

static long __lab_lsmod_count(size_t *count) {
	return syscall(__NR_lab_lsmod_count, count);
}

static void print_module(const struct lab_lsmod_module_info * const mod, size_t count) {
	printf("Module:               Status:  Size:    Use count:\n");

	for (size_t i = 0; i < count; i++) {
		if (mod[i].state == MODULE_STATE_GOING)
			printf("%-21s Unloading %-8u %-4d\n", mod[i].name,
            		       mod[i].size, mod[i].references_count);
		else if (mod[i].state == MODULE_STATE_COMING)
			printf("%-21s Loading %-8u %-4d\n", mod[i].name,
            		       mod[i].size, mod[i].references_count);
		else
			printf("%-21s Live %-8u %-4d\n", mod[i].name,
            		       mod[i].size, mod[i].references_count);
	}
}

int main(int argc, char **argv) {
	size_t *count = (size_t *) malloc(sizeof(size_t));

	long ret = __lab_lsmod_count(count);

	if (ret < 0) {
		printf("System call __cstm_lsmod_count error %s\n",
		       strerror(-ret));
		free(count);
		return -1;
	}

	printf("Number of modules: %zu\n", *count);

	struct lab_lsmod_module_info *modules_info = (struct lab_lsmod_module_info *)
		malloc(sizeof(struct lab_lsmod_module_info) * (*count));

	ret = __lab_lsmod(modules_info);

	if (ret < 0) {
		printf("System call __lab_lsmod error %s\n", strerror(-ret));
		free(modules_info);
		free(count);
		return -1;
	}

	print_module(modules_info, (*count));
	free(count);
	free(modules_info);

	return 0;
}