# SPDX-License-Identifier: GPL-2.0
#
# Makefile for the linux kernel.
#

obj-pci-y	:=
obj-pci-n	:=

# Device tree platform
obj-pci-$(CONFIG_MACH_IXP4XX_OF)	+= ixp4xx-of.o

obj-pci-$(CONFIG_MACH_GATEWAY7001)	+= gateway7001-pci.o

obj-y	+= common.o

obj-$(CONFIG_MACH_GATEWAY7001)	+= gateway7001-setup.o
obj-$(CONFIG_MACH_GORAMO_MLR)	+= goramo_mlr.o

obj-$(CONFIG_PCI)		+= $(obj-pci-$(CONFIG_PCI)) common-pci.o
