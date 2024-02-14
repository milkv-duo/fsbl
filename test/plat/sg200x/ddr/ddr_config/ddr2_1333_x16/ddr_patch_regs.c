// SPDX-License-Identifier: BSD-3-Clause

#include <stddef.h>
#include <utils_def.h>
#include <mmio.h>
#include <ddr_sys.h>
#include "regconfig.h"

//regpatch_ddr2_1333_x16_qfn.c

struct regpatch ddr_patch_regs[] = {
	// tune damp //////
	{0x08000150, 0xFFFFFFFF, 0x00000005},

	// CSB & CA driving
	{0x0800097c, 0xFFFFFFFF, 0x08080404},

	// CLK driving
	{0x08000980, 0xFFFFFFFF, 0x08080808},

	// DQ driving // BYTE0
	{0x08000a38, 0xFFFFFFFF, 0x00000808},
	// DQS driving // BYTE0
	{0x08000a3c, 0xFFFFFFFF, 0x04040404},
	// DQ driving // BYTE1
	{0x08000a78, 0xFFFFFFFF, 0x00000808},
	// DQS driving // BYTE1
	{0x08000a7c, 0xFFFFFFFF, 0x04040404},

	//trigger level //////
	// BYTE0
	{0x08000b24, 0xFFFFFFFF, 0x00100010},
	// BYTE1
	{0x08000b54, 0xFFFFFFFF, 0x00100010},

	//APHY TX VREFDQ rangex2 [1]
	//VREF DQ   //
	{0x08000410, 0xFFFFFFFF, 0x00120002},

	//APHY TX VREFCA rangex2 [1]
	//VREF CA  //
	{0x08000414, 0xFFFFFFFF, 0x00100002},

	// tx dline code
	//  BYTE0 DQ
	{0x08000a00, 0xFFFFFFFF, 0x06440644},
	{0x08000a04, 0xFFFFFFFF, 0x06440644},
	{0x08000a08, 0xFFFFFFFF, 0x06440644},
	{0x08000a0c, 0xFFFFFFFF, 0x06440644},
	{0x08000a10, 0xFFFFFFFF, 0x00000644},
	{0x08000a14, 0xFFFFFFFF, 0x0d000000},
	//  BYTE1 DQ
	{0x08000a40, 0xFFFFFFFF, 0x06440644},
	{0x08000a44, 0xFFFFFFFF, 0x06440644},
	{0x08000a48, 0xFFFFFFFF, 0x06440644},
	{0x08000a4c, 0xFFFFFFFF, 0x06440644},
	{0x08000a50, 0xFFFFFFFF, 0x00000644},
	{0x08000a54, 0xFFFFFFFF, 0x0d000000},

	//APHY RX TRIG rangex2[18] & disable lsmode[0]
	//f0_param_phya_reg_rx_byte0_en_lsmode[0]
	//f0_param_phya_reg_byte0_en_rec_vol_mode[12]
	//f0_param_phya_reg_rx_byte0_force_en_lvstl_odt[16]
	//f0_param_phya_reg_rx_byte0_sel_dqs_rec_vref_mode[8]
	//param_phya_reg_rx_byte0_en_trig_lvl_rangex2[18]
	// BYTE0 [0]
	{0x08000500, 0xFFFFFFFF, 0x00041001},
	//f0_param_phya_reg_rx_byte1_en_lsmode[0]
	//f0_param_phya_reg_byte1_en_rec_vol_mode[12]
	//f0_param_phya_reg_rx_byte0_force_en_lvstl_odt[16]
	//f0_param_phya_reg_rx_byte0_sel_dqs_rec_vref_mode[8]
	//param_phya_reg_rx_byte0_en_trig_lvl_rangex2[18]
	// BYTE1 [0]
	{0x08000540, 0xFFFFFFFF, 0x00041001},

	////////  FOR U02 ///////
	/////////// U02 enable DQS voltage mode receiver
	// f0_param_phya_reg_tx_byte0_en_tx_de_dqs[20]
	{0x08000504, 0xFFFFFFFF, 0x00100000},
	// f0_param_phya_reg_tx_byte1_en_tx_de_dqs[20]
	{0x08000544, 0xFFFFFFFF, 0x00100000},
	/////////// U02 enable MASK voltage mode receiver
	// param_phya_reg_rx_sel_dqs_wo_pream_mode[2]
	{0x08000138, 0xFFFFFFFF, 0x00000014},

	// BYTE0 RX DQ deskew
	{0x08000b00, 0xFFFFFFFF, 0x02000202},
	{0x08000b04, 0xFFFFFFFF, 0x00020000},
	// BYTE0  DQ8 deskew [6:0] neg DQS  [15:8]  ;  pos DQS  [23:16]
	{0x08000b08, 0xFFFFFFFF, 0x002d3202},

	// BYTE1 RX DQ deskew
	{0x08000b30, 0xFFFFFFFF, 0x04020603},
	{0x08000b34, 0xFFFFFFFF, 0x00060203},
	// BYTE1  DQ8 deskew [6:0] neg DQS  [15:8]  ;  pos DQS  [23:16]
	{0x08000b38, 0xFFFFFFFF, 0x00313503},

	//Read gate TX dline + shift
	// BYTE0
	{0x08000b0c, 0xFFFFFFFF, 0x0000081e},
	// BYTE1
	{0x08000b3c, 0xFFFFFFFF, 0x0000081e},

	// CKE dline + shift CKE0 [6:0]+[13:8] ; CKE1 [22:16]+[29:24]
	{0x08000930, 0xFFFFFFFF, 0x04000400},
	// CSB dline + shift CSB0 [6:0]+[13:8] ; CSB1 [22:16]+[29:24]
	{0x08000934, 0xFFFFFFFF, 0x04000400},
};

uint32_t ddr_patch_regs_count = ARRAY_SIZE(ddr_patch_regs);
