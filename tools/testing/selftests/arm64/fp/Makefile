# SPDX-License-Identifier: GPL-2.0

CFLAGS += -I../../../../../usr/include/
TEST_GEN_PROGS := sve-ptrace sve-probe-vls vec-syscfg
TEST_PROGS_EXTENDED := fpsimd-test fpsimd-stress \
	rdvl-sve \
	sve-test sve-stress \
	vlset

all: $(TEST_GEN_PROGS) $(TEST_PROGS_EXTENDED)

fpsimd-test: fpsimd-test.o asm-utils.o
	$(CC) -nostdlib $^ -o $@
rdvl-sve: rdvl-sve.o rdvl.o
sve-ptrace: sve-ptrace.o
sve-probe-vls: sve-probe-vls.o rdvl.o
sve-test: sve-test.o asm-utils.o
	$(CC) -nostdlib $^ -o $@
vec-syscfg: vec-syscfg.o rdvl.o
vlset: vlset.o

include ../../lib.mk
