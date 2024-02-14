# SPDX-License-Identifier: BSD-3-Clause

$(call print_var,DDR_CFG)

# DDR_CFG = ddr3_2133_x16
# DDR_CFG = ddr3_1866_x16
# DDR_CFG = ddr2_1333_x16

ifeq (${DDR_CFG},none)
DDR_CFG =
endif

ifeq ($(DDR_CFG), )
INCLUDES += \
	-Iplat/${CHIP_ARCH}/include/ddr

BL2_SOURCES += \
	plat/${CHIP_ARCH}/ddr/ddr.c

$(eval $(call add_define,NO_DDR_CFG))
else
INCLUDES += \
	-Iplat/${CHIP_ARCH}/include/ddr \
	-Iplat/${CHIP_ARCH}/include/ddr/ddr_config/${DDR_CFG}

BL2_SOURCES += \
	plat/${CHIP_ARCH}/ddr/ddr.c \
	plat/${CHIP_ARCH}/ddr/ddr_pkg_info.c \
	plat/${CHIP_ARCH}/ddr/ddr_sys_bring_up.c \
	plat/${CHIP_ARCH}/ddr/ddr_sys.c \
	plat/${CHIP_ARCH}/ddr/phy_pll_init.c \
	plat/${CHIP_ARCH}/ddr/cvx16_pinmux.c \
	plat/${CHIP_ARCH}/ddr/cvx16_dram_cap_check.c \
	plat/${CHIP_ARCH}/ddr/ddr_config/${DDR_CFG}/ddrc_init.c \
	plat/${CHIP_ARCH}/ddr/ddr_config/${DDR_CFG}/phy_init.c \
	plat/${CHIP_ARCH}/ddr/ddr_config/${DDR_CFG}/ddr_patch_regs.c

ifneq ($(findstring ddr3, ${DDR_CFG}),)
    $(eval $(call add_define,DDR3))
else ifneq ($(findstring ddr2, ${DDR_CFG}),)
    $(eval $(call add_define,DDR2))
else ifneq ($(findstring ddr_auto, ${DDR_CFG}),)
    $(eval $(call add_define,DDR2_3))
endif

ifneq ($(findstring 2133, ${DDR_CFG}),)
    $(eval $(call add_define,_mem_freq_2133))
else ifneq ($(findstring 1866, ${DDR_CFG}),)
    $(eval $(call add_define,_mem_freq_1866))
else ifneq ($(findstring 1333, ${DDR_CFG}),)
    $(eval $(call add_define,_mem_freq_1333))
endif

$(eval $(call add_define,REAL_DDRPHY))
$(eval $(call add_define,REAL_LOCK))
$(eval $(call add_define,X16_MODE))

# overdrive clock setting
ifeq ($(OD_CLK_SEL),y)
$(eval $(call add_define,OD_CLK_SEL))
endif

endif