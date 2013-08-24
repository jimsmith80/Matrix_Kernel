/*
 * drivers/media/video/msm/mt9d113_reg_qtech_sunny_socket.c
 *
 * Refer to drivers/media/video/msm/mt9d112_reg.c
 * For MT9D113: 2.0Mp, 1/4-Inch System-On-A-Chip (SOC) CMOS Digital Image Sensor
 *
 * Copyright (C) 2009-2010 ZTE Corporation.
 *
 * This software is licensed under the terms of the GNU General Public
 * License version 2, as published by the Free Software Foundation, and
 * may be copied, distributed, and modified under those terms.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * Created by jia.jia@zte.com.cn
 */
/*-----------------------------------------------------------------------------------------
  when         who          what, where, why                         comment tag
  --------     ----         -------------------------------------    ----------------------
  2010-09-21   lijing       modify sensor settings for lab test      ZTE_LJ_CAM_20100921
                            failed for saturation
  2010-09-09   lijing       update contrast,sharpness and            ZTE_LJ_CAM_20100909
                            saturation settings
  2010-09-07   lijing       modify init, wb, and contrast and        ZTE_LJ_CAM_20100907
                            settings;
                            modify default value of brightness,
                            saturation, and sharpness to pass
                            lab test
  2010-09-04   lijing       update sensor settings                   ZTE_LJ_CAM_20100904
  2010-09-02   li.jing      created                                  ZTE_CAMERA_LIJING_20100902
                            merged from mt9d115_reg_qtech_sunny_socket.c
------------------------------------------------------------------------------------------*/

#include "mt9d113.h"

/* PLL Setup */
static struct mt9d113_i2c_reg_conf const pll_tbl[] = {
    {0x001A, 0x0051, WORD_LEN, 1}, 	// RESET_AND_MISC_CONTROL
    {0x001A, 0x0050, WORD_LEN, 1}, 	// RESET_AND_MISC_CONTROL
    {0x0014, 0x2545, WORD_LEN, 0},	//PLL Control: BYPASS PLL = 9541
    {0x0010, 0x0110, WORD_LEN, 0},	//PLL Dividers = 272
    {0x0012, 0x1FF7, WORD_LEN, 0},	//PLL P Dividers = 8183
    {0x0014, 0x2547, WORD_LEN, 0},	//PLL Control: PLL_ENABLE on = 9543
    {0x0014, 0x2447, WORD_LEN, 1},	//PLL Control: SEL_LOCK_DET on = 9287
    {0x0014, 0x2047, WORD_LEN, 0},	//PLL Control: PLL_BYPASS off = 8263
    {0x0014, 0x2046, WORD_LEN, 1},	//PLL Control: = 8262
    {0x001A, 0x0050, WORD_LEN, 0}, 	// RESET_AND_MISC_CONTROL
    {0x0018, 0x4028, WORD_LEN, 100}, // STANDBY_CONTROL
};

/* Clock Setup */
static struct mt9d113_i2c_reg_conf const clk_tbl[] = {
    //no code here
};

/* Preview and Snapshot Setup */
static struct mt9d113_i2c_reg_conf const prev_snap_tbl[] = {
    //errata for rev2/
    {0x3084, 0x240C, WORD_LEN, 0},
    {0x3092, 0x0A4C, WORD_LEN, 0},
    {0x3094, 0x4C4C, WORD_LEN, 0},
    {0x3096, 0x4C54, WORD_LEN, 0},

    // LSC 85%
    {0x364E, 0x05D0, WORD_LEN, 0}, 	// P_GR_P0Q0
    {0x3650, 0x82CB, WORD_LEN, 0}, 	// P_GR_P0Q1
    {0x3652, 0x78D1, WORD_LEN, 0}, 	// P_GR_P0Q2
    {0x3654, 0x8D31, WORD_LEN, 0}, 	// P_GR_P0Q3
    {0x3656, 0xE3D3, WORD_LEN, 0}, 	// P_GR_P0Q4
    {0x3658, 0x00F0, WORD_LEN, 0}, 	// P_RD_P0Q0
    {0x365A, 0xFFEB, WORD_LEN, 0}, 	// P_RD_P0Q1
    {0x365C, 0x60F1, WORD_LEN, 0}, 	// P_RD_P0Q2
    {0x365E, 0xD810, WORD_LEN, 0}, 	// P_RD_P0Q3
    {0x3660, 0x8C33, WORD_LEN, 0}, 	// P_RD_P0Q4
    {0x3662, 0x00F0, WORD_LEN, 0}, 	// P_BL_P0Q0
    {0x3664, 0xAFAA, WORD_LEN, 0}, 	// P_BL_P0Q1
    {0x3666, 0x6791, WORD_LEN, 0}, 	// P_BL_P0Q2
    {0x3668, 0x8051, WORD_LEN, 0}, 	// P_BL_P0Q3
    {0x366A, 0xB733, WORD_LEN, 0}, 	// P_BL_P0Q4
    {0x366C, 0x0130, WORD_LEN, 0}, 	// P_GB_P0Q0
    {0x366E, 0xA76C, WORD_LEN, 0}, 	// P_GB_P0Q1
    {0x3670, 0x6D11, WORD_LEN, 0}, 	// P_GB_P0Q2
    {0x3672, 0xE370, WORD_LEN, 0}, 	// P_GB_P0Q3
    {0x3674, 0xD353, WORD_LEN, 0}, 	// P_GB_P0Q4
    {0x3676, 0x616C, WORD_LEN, 0}, 	// P_GR_P1Q0
    {0x3678, 0x9670, WORD_LEN, 0}, 	// P_GR_P1Q1
    {0x367A, 0x63B0, WORD_LEN, 0}, 	// P_GR_P1Q2
    {0x367C, 0x1F72, WORD_LEN, 0}, 	// P_GR_P1Q3
    {0x367E, 0xB610, WORD_LEN, 0}, 	// P_GR_P1Q4
    {0x3680, 0x39ED, WORD_LEN, 0}, 	// P_RD_P1Q0
    {0x3682, 0x0310, WORD_LEN, 0}, 	// P_RD_P1Q1
    {0x3684, 0xB5AF, WORD_LEN, 0}, 	// P_RD_P1Q2
    {0x3686, 0xCED1, WORD_LEN, 0}, 	// P_RD_P1Q3
    {0x3688, 0x1A93, WORD_LEN, 0}, 	// P_RD_P1Q4
    {0x368A, 0x916B, WORD_LEN, 0}, 	// P_BL_P1Q0
    {0x368C, 0xF7CF, WORD_LEN, 0}, 	// P_BL_P1Q1
    {0x368E, 0x2FB0, WORD_LEN, 0}, 	// P_BL_P1Q2
    {0x3690, 0x4E52, WORD_LEN, 0}, 	// P_BL_P1Q3
    {0x3692, 0x0C32, WORD_LEN, 0}, 	// P_BL_P1Q4
    {0x3694, 0x0F8D, WORD_LEN, 0}, 	// P_GB_P1Q0
    {0x3696, 0x15B0, WORD_LEN, 0}, 	// P_GB_P1Q1
    {0x3698, 0x446D, WORD_LEN, 0}, 	// P_GB_P1Q2
    {0x369A, 0xA912, WORD_LEN, 0}, 	// P_GB_P1Q3
    {0x369C, 0x0570, WORD_LEN, 0}, 	// P_GB_P1Q4
    {0x369E, 0x62B2, WORD_LEN, 0}, 	// P_GR_P2Q0
    {0x36A0, 0x8952, WORD_LEN, 0}, 	// P_GR_P2Q1
    {0x36A2, 0xC9B4, WORD_LEN, 0}, 	// P_GR_P2Q2
    {0x36A4, 0x0333, WORD_LEN, 0}, 	// P_GR_P2Q3
    {0x36A6, 0x8975, WORD_LEN, 0}, 	// P_GR_P2Q4
    {0x36A8, 0x59D2, WORD_LEN, 0}, 	// P_RD_P2Q0
    {0x36AA, 0xB6F1, WORD_LEN, 0}, 	// P_RD_P2Q1
    {0x36AC, 0xAEF3, WORD_LEN, 0}, 	// P_RD_P2Q2
    {0x36AE, 0x396D, WORD_LEN, 0}, 	// P_RD_P2Q3
    {0x36B0, 0xCBD6, WORD_LEN, 0}, 	// P_RD_P2Q4
    {0x36B2, 0x64D2, WORD_LEN, 0}, 	// P_BL_P2Q0
    {0x36B4, 0x8B92, WORD_LEN, 0}, 	// P_BL_P2Q1
    {0x36B6, 0xD514, WORD_LEN, 0}, 	// P_BL_P2Q2
    {0x36B8, 0x3153, WORD_LEN, 0}, 	// P_BL_P2Q3
    {0x36BA, 0xB5B4, WORD_LEN, 0}, 	// P_BL_P2Q4
    {0x36BC, 0x7012, WORD_LEN, 0}, 	// P_GB_P2Q0
    {0x36BE, 0xD1D1, WORD_LEN, 0}, 	// P_GB_P2Q1
    {0x36C0, 0xD414, WORD_LEN, 0}, 	// P_GB_P2Q2
    {0x36C2, 0x6FF1, WORD_LEN, 0}, 	// P_GB_P2Q3
    {0x36C4, 0x8395, WORD_LEN, 0}, 	// P_GB_P2Q4
    {0x36C6, 0x0A31, WORD_LEN, 0}, 	// P_GR_P3Q0
    {0x36C8, 0x7FF0, WORD_LEN, 0}, 	// P_GR_P3Q1
    {0x36CA, 0x75B2, WORD_LEN, 0}, 	// P_GR_P3Q2
    {0x36CC, 0x1B31, WORD_LEN, 0}, 	// P_GR_P3Q3
    {0x36CE, 0xE1D6, WORD_LEN, 0}, 	// P_GR_P3Q4
    {0x36D0, 0x14F1, WORD_LEN, 0}, 	// P_RD_P3Q0
    {0x36D2, 0xAD30, WORD_LEN, 0}, 	// P_RD_P3Q1
    {0x36D4, 0x3454, WORD_LEN, 0}, 	// P_RD_P3Q2
    {0x36D6, 0x9335, WORD_LEN, 0}, 	// P_RD_P3Q3
    {0x36D8, 0xD717, WORD_LEN, 0}, 	// P_RD_P3Q4
    {0x36DA, 0x0D31, WORD_LEN, 0}, 	// P_BL_P3Q0
    {0x36DC, 0x5A50, WORD_LEN, 0}, 	// P_BL_P3Q1
    {0x36DE, 0x0754, WORD_LEN, 0}, 	// P_BL_P3Q2
    {0x36E0, 0xC5F3, WORD_LEN, 0}, 	// P_BL_P3Q3
    {0x36E2, 0xB2F7, WORD_LEN, 0}, 	// P_BL_P3Q4
    {0x36E4, 0x1B51, WORD_LEN, 0}, 	// P_GB_P3Q0
    {0x36E6, 0x92D2, WORD_LEN, 0}, 	// P_GB_P3Q1
    {0x36E8, 0x0373, WORD_LEN, 0}, 	// P_GB_P3Q2
    {0x36EA, 0x9310, WORD_LEN, 0}, 	// P_GB_P3Q3
    {0x36EC, 0xDBD6, WORD_LEN, 0}, 	// P_GB_P3Q4
    {0x36EE, 0xC0F4, WORD_LEN, 0}, 	// P_GR_P4Q0
    {0x36F0, 0xEED2, WORD_LEN, 0}, 	// P_GR_P4Q1
    {0x36F2, 0x8678, WORD_LEN, 0}, 	// P_GR_P4Q2
    {0x36F4, 0x7837, WORD_LEN, 0}, 	// P_GR_P4Q3
    {0x36F6, 0x0C3B, WORD_LEN, 0}, 	// P_GR_P4Q4
    {0x36F8, 0x82F4, WORD_LEN, 0}, 	// P_RD_P4Q0
    {0x36FA, 0x9AB3, WORD_LEN, 0}, 	// P_RD_P4Q1
    {0x36FC, 0xAF98, WORD_LEN, 0}, 	// P_RD_P4Q2
    {0x36FE, 0x5277, WORD_LEN, 0}, 	// P_RD_P4Q3
    {0x3700, 0x145B, WORD_LEN, 0}, 	// P_RD_P4Q4
    {0x3702, 0xABB4, WORD_LEN, 0}, 	// P_BL_P4Q0
    {0x3704, 0xDC90, WORD_LEN, 0}, 	// P_BL_P4Q1
    {0x3706, 0xFCB7, WORD_LEN, 0}, 	// P_BL_P4Q2
    {0x3708, 0x22B7, WORD_LEN, 0}, 	// P_BL_P4Q3
    {0x370A, 0x061B, WORD_LEN, 0}, 	// P_BL_P4Q4
    {0x370C, 0xC7B4, WORD_LEN, 0}, 	// P_GB_P4Q0
    {0x370E, 0x8893, WORD_LEN, 0}, 	// P_GB_P4Q1
    {0x3710, 0x8878, WORD_LEN, 0}, 	// P_GB_P4Q2
    {0x3712, 0x6217, WORD_LEN, 0}, 	// P_GB_P4Q3
    {0x3714, 0x06BB, WORD_LEN, 0}, 	// P_GB_P4Q4
    {0x3644, 0x0360, WORD_LEN, 0}, 	// POLY_ORIGIN_C
    {0x3642, 0x0234, WORD_LEN, 0}, 	// POLY_ORIGIN_R
    {0x3210, 0x01B8, WORD_LEN, 0}, 	// COLOR_PIPELINE_CONTROL

    // low light setting
    {0x098C, 0x2B28, WORD_LEN, 0}, 	// MCU_ADDRESS [HG_LL_BRIGHTNESSSTART]
    {0x0990, 0x35E8, WORD_LEN, 0}, 	// MCU_DATA_0
    {0x098C, 0x2B2A, WORD_LEN, 0}, 	// MCU_ADDRESS [HG_LL_BRIGHTNESSSTOP]
    {0x0990, 0xB3B0, WORD_LEN, 0}, 	// MCU_DATA_0
    {0x098C, 0xAB20, WORD_LEN, 0}, 	// MCU_ADDRESS [HG_LL_SAT1]
    {0x0990, 0x004B, WORD_LEN, 0}, 	// MCU_DATA_0
    {0x098C, 0xAB24, WORD_LEN, 0}, 	// MCU_ADDRESS [HG_LL_SAT2]
    {0x0990, 0x0000, WORD_LEN, 0}, 	// MCU_DATA_0
    {0x098C, 0xAB25, WORD_LEN, 0}, 	// MCU_ADDRESS [HG_LL_INTERPTHRESH2]
    {0x0990, 0x00FF, WORD_LEN, 0}, 	// MCU_DATA_0
    {0x098C, 0xAB30, WORD_LEN, 0}, 	// MCU_ADDRESS [HG_NR_STOP_R]
    {0x0990, 0x00FF, WORD_LEN, 0}, 	// MCU_DATA_0
    {0x098C, 0xAB31, WORD_LEN, 0}, 	// MCU_ADDRESS [HG_NR_STOP_G]
    {0x0990, 0x00FF, WORD_LEN, 0}, 	// MCU_DATA_0
    {0x098C, 0xAB32, WORD_LEN, 0}, 	// MCU_ADDRESS [HG_NR_STOP_B]
    {0x0990, 0x00FF, WORD_LEN, 0}, 	// MCU_DATA_0
    {0x098C, 0xAB33, WORD_LEN, 0}, 	// MCU_ADDRESS [HG_NR_STOP_OL]
    {0x0990, 0x0057, WORD_LEN, 0}, 	// MCU_DATA_0
    {0x098C, 0xAB34, WORD_LEN, 0}, 	// MCU_ADDRESS [HG_NR_GAINSTART]
    {0x0990, 0x0080, WORD_LEN, 0}, 	// MCU_DATA_0
    {0x098C, 0xAB35, WORD_LEN, 0}, 	// MCU_ADDRESS [HG_NR_GAINSTOP]
    {0x0990, 0x00FF, WORD_LEN, 0}, 	// MCU_DATA_0
    {0x098C, 0xAB36, WORD_LEN, 0}, 	// MCU_ADDRESS [HG_CLUSTERDC_TH]
    {0x0990, 0x0014, WORD_LEN, 0}, 	// MCU_DATA_0
    {0x098C, 0xAB37, WORD_LEN, 0}, 	// MCU_ADDRESS [HG_GAMMA_MORPH_CTRL]
    {0x0990, 0x0003, WORD_LEN, 0}, 	// MCU_DATA_0
    {0x098C, 0x2B38, WORD_LEN, 0}, 	// MCU_ADDRESS [HG_GAMMASTARTMORPH]
    {0x0990, 0x32C8, WORD_LEN, 0}, 	// MCU_DATA_0
    {0x098C, 0x2B3A, WORD_LEN, 0}, 	// MCU_ADDRESS [HG_GAMMASTOPMORPH]
    {0x0990, 0x7918, WORD_LEN, 0}, 	// MCU_DATA_0
    {0x098C, 0x2B62, WORD_LEN, 0}, 	// MCU_ADDRESS [HG_FTB_START_BM]
    {0x0990, 0xFFFE, WORD_LEN, 0}, 	// MCU_DATA_0
    {0x098C, 0x2B64, WORD_LEN, 0}, 	// MCU_ADDRESS [HG_FTB_STOP_BM]
    {0x0990, 0xFFFF, WORD_LEN, 0}, 	// MCU_DATA_0

    // AWB and CCM
    {0x098C, 0x2306, WORD_LEN, 0}, 	// MCU_ADDRESS [AWB_CCM_L_0]
    {0x0990, 0x0180, WORD_LEN, 0}, 	// MCU_DATA_0
    {0x098C, 0x231C, WORD_LEN, 0}, 	// MCU_ADDRESS [AWB_CCM_RL_0]
    {0x0990, 0x011C, WORD_LEN, 0}, 	// MCU_DATA_0
    {0x098C, 0x2308, WORD_LEN, 0}, 	// MCU_ADDRESS [AWB_CCM_L_1]
    {0x0990, 0xFF00, WORD_LEN, 0}, 	// MCU_DATA_0
    {0x098C, 0x231E, WORD_LEN, 0}, 	// MCU_ADDRESS [AWB_CCM_RL_1]
    {0x0990, 0xFF81, WORD_LEN, 0}, 	// MCU_DATA_0
    {0x098C, 0x230A, WORD_LEN, 0}, 	// MCU_ADDRESS [AWB_CCM_L_2]
    {0x0990, 0x0080, WORD_LEN, 0}, 	// MCU_DATA_0
    {0x098C, 0x2320, WORD_LEN, 0}, 	// MCU_ADDRESS [AWB_CCM_RL_2]
    {0x0990, 0x0005, WORD_LEN, 0}, 	// MCU_DATA_0
    {0x098C, 0x230C, WORD_LEN, 0}, 	// MCU_ADDRESS [AWB_CCM_L_3]
    {0x0990, 0xFF66, WORD_LEN, 0}, 	// MCU_DATA_0
    {0x098C, 0x2322, WORD_LEN, 0}, 	// MCU_ADDRESS [AWB_CCM_RL_3]
    {0x0990, 0x0045, WORD_LEN, 0}, 	// MCU_DATA_0
    {0x098C, 0x230E, WORD_LEN, 0}, 	// MCU_ADDRESS [AWB_CCM_L_4]
    {0x0990, 0x0180, WORD_LEN, 0}, 	// MCU_DATA_0
    {0x098C, 0x2324, WORD_LEN, 0}, 	// MCU_ADDRESS [AWB_CCM_RL_4]
    {0x0990, 0xFFD6, WORD_LEN, 0}, 	// MCU_DATA_0
    {0x098C, 0x2310, WORD_LEN, 0}, 	// MCU_ADDRESS [AWB_CCM_L_5]
    {0x0990, 0xFFEE, WORD_LEN, 0}, 	// MCU_DATA_0
    {0x098C, 0x2326, WORD_LEN, 0}, 	// MCU_ADDRESS [AWB_CCM_RL_5]
    {0x0990, 0xFFB2, WORD_LEN, 0}, 	// MCU_DATA_0
    {0x098C, 0x2312, WORD_LEN, 0}, 	// MCU_ADDRESS [AWB_CCM_L_6]
    {0x0990, 0xFFCD, WORD_LEN, 0}, 	// MCU_DATA_0
    {0x098C, 0x2328, WORD_LEN, 0}, 	// MCU_ADDRESS [AWB_CCM_RL_6]
    {0x0990, 0x004A, WORD_LEN, 0}, 	// MCU_DATA_0
    {0x098C, 0x2314, WORD_LEN, 0}, 	// MCU_ADDRESS [AWB_CCM_L_7]
    {0x0990, 0xFECD, WORD_LEN, 0}, 	// MCU_DATA_0
    {0x098C, 0x232A, WORD_LEN, 0}, 	// MCU_ADDRESS [AWB_CCM_RL_7]
    {0x0990, 0x0070, WORD_LEN, 0}, 	// MCU_DATA_0
    {0x098C, 0x2316, WORD_LEN, 0}, 	// MCU_ADDRESS [AWB_CCM_L_8]
    {0x0990, 0x019A, WORD_LEN, 0}, 	// MCU_DATA_0
    {0x098C, 0x232C, WORD_LEN, 0}, 	// MCU_ADDRESS [AWB_CCM_RL_8]
    {0x0990, 0xFF71, WORD_LEN, 0}, 	// MCU_DATA_0

    {0x098C, 0x232E, WORD_LEN, 0}, 	// MCU_ADDRESS [AWB_CCM_RL_9]
    {0x0990, 0x0008, WORD_LEN, 0}, 	// MCU_DATA_0
    {0x098C, 0x2330, WORD_LEN, 0}, 	// MCU_ADDRESS [AWB_CCM_RL_10]
    {0x0990, 0xFFF7, WORD_LEN, 0}, 	// MCU_DATA_0
    {0x098C, 0xA363, WORD_LEN, 0}, 	// MCU_ADDRESS [AWB_TG_MIN0]
    {0x0990, 0x00D2, WORD_LEN, 0}, 	// MCU_DATA_0
    {0x098C, 0xA364, WORD_LEN, 0}, 	// MCU_ADDRESS [AWB_TG_MAX0]
    {0x0990, 0x00EE, WORD_LEN, 0}, 	// MCU_DATA_0
    {0x3244, 0x0328, WORD_LEN, 0}, 	// AWB_CONFIG4
    {0x323E, 0xC22C, WORD_LEN, 10}, 	// AWB_CONFIG1

    //Patch
    {0x098C, 0x0415, WORD_LEN, 0}, 	// MCU_ADDRESS
    {0x0990, 0xF601, WORD_LEN, 0},
    {0x0992, 0x42C1, WORD_LEN, 0},
    {0x0994, 0x0326, WORD_LEN, 0},
    {0x0996, 0x11F6, WORD_LEN, 0},
    {0x0998, 0x0143, WORD_LEN, 0},
    {0x099A, 0xC104, WORD_LEN, 0},
    {0x099C, 0x260A, WORD_LEN, 0},
    {0x099E, 0xCC04, WORD_LEN, 0},
    {0x098C, 0x0425, WORD_LEN, 0}, 	// MCU_ADDRESS
    {0x0990, 0x33BD, WORD_LEN, 0},
    {0x0992, 0xA362, WORD_LEN, 0},
    {0x0994, 0xBD04, WORD_LEN, 0},
    {0x0996, 0x3339, WORD_LEN, 0},
    {0x0998, 0xC6FF, WORD_LEN, 0},
    {0x099A, 0xF701, WORD_LEN, 0},
    {0x099C, 0x6439, WORD_LEN, 0},
    {0x099E, 0xFE01, WORD_LEN, 0},
    {0x098C, 0x0435, WORD_LEN, 0}, 	// MCU_ADDRESS
    {0x0990, 0x6918, WORD_LEN, 0},
    {0x0992, 0xCE03, WORD_LEN, 0},
    {0x0994, 0x25CC, WORD_LEN, 0},
    {0x0996, 0x0013, WORD_LEN, 0},
    {0x0998, 0xBDC2, WORD_LEN, 0},
    {0x099A, 0xB8CC, WORD_LEN, 0},
    {0x099C, 0x0489, WORD_LEN, 0},
    {0x099E, 0xFD03, WORD_LEN, 0},
    {0x098C, 0x0445, WORD_LEN, 0}, 	// MCU_ADDRESS
    {0x0990, 0x27CC, WORD_LEN, 0},
    {0x0992, 0x0325, WORD_LEN, 0},
    {0x0994, 0xFD01, WORD_LEN, 0},
    {0x0996, 0x69FE, WORD_LEN, 0},
    {0x0998, 0x02BD, WORD_LEN, 0},
    {0x099A, 0x18CE, WORD_LEN, 0},
    {0x099C, 0x0339, WORD_LEN, 0},
    {0x099E, 0xCC00, WORD_LEN, 0},
    {0x098C, 0x0455, WORD_LEN, 0}, 	// MCU_ADDRESS
    {0x0990, 0x11BD, WORD_LEN, 0},
    {0x0992, 0xC2B8, WORD_LEN, 0},
    {0x0994, 0xCC04, WORD_LEN, 0},
    {0x0996, 0xC8FD, WORD_LEN, 0},
    {0x0998, 0x0347, WORD_LEN, 0},
    {0x099A, 0xCC03, WORD_LEN, 0},
    {0x099C, 0x39FD, WORD_LEN, 0},
    {0x099E, 0x02BD, WORD_LEN, 0},
    {0x098C, 0x0465, WORD_LEN, 0}, 	// MCU_ADDRESS
    {0x0990, 0xDE00, WORD_LEN, 0},
    {0x0992, 0x18CE, WORD_LEN, 0},
    {0x0994, 0x00C2, WORD_LEN, 0},
    {0x0996, 0xCC00, WORD_LEN, 0},
    {0x0998, 0x37BD, WORD_LEN, 0},
    {0x099A, 0xC2B8, WORD_LEN, 0},
    {0x099C, 0xCC04, WORD_LEN, 0},
    {0x099E, 0xEFDD, WORD_LEN, 0},
    {0x098C, 0x0475, WORD_LEN, 0}, 	// MCU_ADDRESS
    {0x0990, 0xE6CC, WORD_LEN, 0},
    {0x0992, 0x00C2, WORD_LEN, 0},
    {0x0994, 0xDD00, WORD_LEN, 0},
    {0x0996, 0xC601, WORD_LEN, 0},
    {0x0998, 0xF701, WORD_LEN, 0},
    {0x099A, 0x64C6, WORD_LEN, 0},
    {0x099C, 0x03F7, WORD_LEN, 0},
    {0x099E, 0x0165, WORD_LEN, 0},
    {0x098C, 0x0485, WORD_LEN, 0}, 	// MCU_ADDRESS
    {0x0990, 0x7F01, WORD_LEN, 0},
    {0x0992, 0x6639, WORD_LEN, 0},
    {0x0994, 0x3C3C, WORD_LEN, 0},
    {0x0996, 0x3C34, WORD_LEN, 0},
    {0x0998, 0xCC32, WORD_LEN, 0},
    {0x099A, 0x3EBD, WORD_LEN, 0},
    {0x099C, 0xA558, WORD_LEN, 0},
    {0x099E, 0x30ED, WORD_LEN, 0},
    {0x098C, 0x0495, WORD_LEN, 0}, 	// MCU_ADDRESS
    {0x0990, 0x04BD, WORD_LEN, 0},
    {0x0992, 0xB2D7, WORD_LEN, 0},
    {0x0994, 0x30E7, WORD_LEN, 0},
    {0x0996, 0x06CC, WORD_LEN, 0},
    {0x0998, 0x323E, WORD_LEN, 0},
    {0x099A, 0xED00, WORD_LEN, 0},
    {0x099C, 0xEC04, WORD_LEN, 0},
    {0x099E, 0xBDA5, WORD_LEN, 0},
    {0x098C, 0x04A5, WORD_LEN, 0}, 	// MCU_ADDRESS
    {0x0990, 0x44CC, WORD_LEN, 0},
    {0x0992, 0x3244, WORD_LEN, 0},
    {0x0994, 0xBDA5, WORD_LEN, 0},
    {0x0996, 0x585F, WORD_LEN, 0},
    {0x0998, 0x30ED, WORD_LEN, 0},
    {0x099A, 0x02CC, WORD_LEN, 0},
    {0x099C, 0x3244, WORD_LEN, 0},
    {0x099E, 0xED00, WORD_LEN, 0},
    {0x098C, 0x04B5, WORD_LEN, 0}, 	// MCU_ADDRESS
    {0x0990, 0xF601, WORD_LEN, 0},
    {0x0992, 0xD54F, WORD_LEN, 0},
    {0x0994, 0xEA03, WORD_LEN, 0},
    {0x0996, 0xAA02, WORD_LEN, 0},
    {0x0998, 0xBDA5, WORD_LEN, 0},
    {0x099A, 0x4430, WORD_LEN, 0},
    {0x099C, 0xE606, WORD_LEN, 0},
    {0x099E, 0x3838, WORD_LEN, 0},
    {0x098C, 0x04C5, WORD_LEN, 0}, 	// MCU_ADDRESS
    {0x0990, 0x3831, WORD_LEN, 0},
    {0x0992, 0x39BD, WORD_LEN, 0},
    {0x0994, 0xD661, WORD_LEN, 0},
    {0x0996, 0xF602, WORD_LEN, 0},
    {0x0998, 0xF4C1, WORD_LEN, 0},
    {0x099A, 0x0126, WORD_LEN, 0},
    {0x099C, 0x0BFE, WORD_LEN, 0},
    {0x099E, 0x02BD, WORD_LEN, 0},
    {0x098C, 0x04D5, WORD_LEN, 0}, 	// MCU_ADDRESS
    {0x0990, 0xEE10, WORD_LEN, 0},
    {0x0992, 0xFC02, WORD_LEN, 0},
    {0x0994, 0xF5AD, WORD_LEN, 0},
    {0x0996, 0x0039, WORD_LEN, 0},
    {0x0998, 0xF602, WORD_LEN, 0},
    {0x099A, 0xF4C1, WORD_LEN, 0},
    {0x099C, 0x0226, WORD_LEN, 0},
    {0x099E, 0x0AFE, WORD_LEN, 0},
    {0x098C, 0x04E5, WORD_LEN, 0}, 	// MCU_ADDRESS
    {0x0990, 0x02BD, WORD_LEN, 0},
    {0x0992, 0xEE10, WORD_LEN, 0},
    {0x0994, 0xFC02, WORD_LEN, 0},
    {0x0996, 0xF7AD, WORD_LEN, 0},
    {0x0998, 0x0039, WORD_LEN, 0},
    {0x099A, 0x3CBD, WORD_LEN, 0},
    {0x099C, 0xB059, WORD_LEN, 0},
    {0x099E, 0xCC00, WORD_LEN, 0},
    {0x098C, 0x04F5, WORD_LEN, 0}, 	// MCU_ADDRESS
    {0x0990, 0x28BD, WORD_LEN, 0},
    {0x0992, 0xA558, WORD_LEN, 0},
    {0x0994, 0x8300, WORD_LEN, 0},
    {0x0996, 0x0027, WORD_LEN, 0},
    {0x0998, 0x0BCC, WORD_LEN, 0},
    {0x099A, 0x0026, WORD_LEN, 0},
    {0x099C, 0x30ED, WORD_LEN, 0},
    {0x099E, 0x00C6, WORD_LEN, 0},
    {0x098C, 0x0505, WORD_LEN, 0}, 	// MCU_ADDRESS
    {0x0990, 0x03BD, WORD_LEN, 0},
    {0x0992, 0xA544, WORD_LEN, 0},
    {0x0994, 0x3839, WORD_LEN, 0},
    {0x098C, 0x2006, WORD_LEN, 0}, 	// MCU_ADDRESS [MON_ARG1]
    {0x0990, 0x0415, WORD_LEN, 0}, 	// MCU_DATA_0
    {0x098C, 0xA005, WORD_LEN, 0}, 	// MCU_ADDRESS [MON_CMD]
    {0x0990, 0x0001, WORD_LEN, 200}, 	// MCU_DATA_0
    //  POLL  MON_PATCH_ID_0 =>  0x01

    {0x321C, 0x0003, WORD_LEN, 0},	//By Pass TxFIFO = 3
    {0x098C, 0x2703, WORD_LEN, 0},	//Output Width (A)
    {0x0990, 0x0320, WORD_LEN, 0},	//      = 800
    {0x098C, 0x2705, WORD_LEN, 0},	//Output Height (A)
    {0x0990, 0x0258, WORD_LEN, 0},	//      = 600
    {0x098C, 0x2707, WORD_LEN, 0},	//Output Width (B)
    {0x0990, 0x0640, WORD_LEN, 0},	//      = 1600
    {0x098C, 0x2709, WORD_LEN, 0},	//Output Height (B)
    {0x0990, 0x04B0, WORD_LEN, 0},	//      = 1200
    {0x098C, 0x270D, WORD_LEN, 0},	//Row Start (A)
    {0x0990, 0x0000, WORD_LEN, 0},	//      = 0
    {0x098C, 0x270F, WORD_LEN, 0},	//Column Start (A)
    {0x0990, 0x0000, WORD_LEN, 0},	//      = 0
    {0x098C, 0x2711, WORD_LEN, 0},	//Row End (A)
    {0x0990, 0x04BD, WORD_LEN, 0},	//      = 1213
    {0x098C, 0x2713, WORD_LEN, 0},	//Column End (A)
    {0x0990, 0x064D, WORD_LEN, 0},	//      = 1613
    {0x098C, 0x2715, WORD_LEN, 0},	//Row Speed (A)
    {0x0990, 0x0111, WORD_LEN, 0},	//      = 273
    {0x098C, 0x2717, WORD_LEN, 0},	//Read Mode (A)
    {0x0990, 0x046f, WORD_LEN, 0},	//      = 1132
    {0x098C, 0x2719, WORD_LEN, 0},	//sensor_fine_correction (A)
    {0x0990, 0x005A, WORD_LEN, 0},	//      = 90
    {0x098C, 0x271B, WORD_LEN, 0},	//sensor_fine_IT_min (A)
    {0x0990, 0x01BE, WORD_LEN, 0},	//      = 446
    {0x098C, 0x271D, WORD_LEN, 0},	//sensor_fine_IT_max_margin (A)
    {0x0990, 0x0131, WORD_LEN, 0},	//      = 305
    {0x098C, 0x271F, WORD_LEN, 0},	//Frame Lines (A)
    {0x0990, 0x02B3, WORD_LEN, 0},	//      = 691
    {0x098C, 0x2721, WORD_LEN, 0},	//Line Length (A)
    {0x0990, 0x07BC, WORD_LEN, 0},	//      = 1980
    {0x098C, 0x2723, WORD_LEN, 0},	//Row Start (B)
    {0x0990, 0x0004, WORD_LEN, 0},	//      = 4
    {0x098C, 0x2725, WORD_LEN, 0},	//Column Start (B)
    {0x0990, 0x0004, WORD_LEN, 0},	//      = 4
    {0x098C, 0x2727, WORD_LEN, 0},	//Row End (B)
    {0x0990, 0x04BB, WORD_LEN, 0},	//      = 1211
    {0x098C, 0x2729, WORD_LEN, 0},	//Column End (B)
    {0x0990, 0x064B, WORD_LEN, 0},	//      = 1611
    {0x098C, 0x272B, WORD_LEN, 0},	//Row Speed (B)
    {0x0990, 0x0111, WORD_LEN, 0},	//      = 273
    {0x098C, 0x272D, WORD_LEN, 0},	//Read Mode (B)
    {0x0990, 0x0027, WORD_LEN, 0},	//      = 36
    {0x098C, 0x272F, WORD_LEN, 0},	//sensor_fine_correction (B)
    {0x0990, 0x003A, WORD_LEN, 0},	//      = 58
    {0x098C, 0x2731, WORD_LEN, 0},	//sensor_fine_IT_min (B)
    {0x0990, 0x00F6, WORD_LEN, 0},	//      = 246
    {0x098C, 0x2733, WORD_LEN, 0},	//sensor_fine_IT_max_margin (B)
    {0x0990, 0x008B, WORD_LEN, 0},	//      = 139
    {0x098C, 0x2735, WORD_LEN, 0},	//Frame Lines (B)
    {0x0990, 0x059A, WORD_LEN, 0},	//      = 1434
    {0x098C, 0x2737, WORD_LEN, 0},	//Line Length (B)
    {0x0990, 0x050D, WORD_LEN, 0},	//      = 1980
    {0x098C, 0x2739, WORD_LEN, 0},	//Crop_X0 (A)
    {0x0990, 0x0000, WORD_LEN, 0},	//      = 0
    {0x098C, 0x273B, WORD_LEN, 0},	//Crop_X1 (A)
    {0x0990, 0x031F, WORD_LEN, 0},	//      = 799
    {0x098C, 0x273D, WORD_LEN, 0},	//Crop_Y0 (A)
    {0x0990, 0x0000, WORD_LEN, 0},	//      = 0
    {0x098C, 0x273F, WORD_LEN, 0},	//Crop_Y1 (A)
    {0x0990, 0x0257, WORD_LEN, 0},	//      = 599
    {0x098C, 0x2747, WORD_LEN, 0},	//Crop_X0 (B)
    {0x0990, 0x0000, WORD_LEN, 0},	//      = 0
    {0x098C, 0x2749, WORD_LEN, 0},	//Crop_X1 (B)
    {0x0990, 0x063F, WORD_LEN, 0},	//      = 1599
    {0x098C, 0x274B, WORD_LEN, 0},	//Crop_Y0 (B)
    {0x0990, 0x0000, WORD_LEN, 0},	//      = 0
    {0x098C, 0x274D, WORD_LEN, 0},	//Crop_Y1 (B)
    {0x0990, 0x04AF, WORD_LEN, 0},	//      = 1199
    {0x098C, 0x222D, WORD_LEN, 0},	//R9 Step
    {0x0990, 0x0065, WORD_LEN, 0},	//      = 101
    {0x098C, 0xA408, WORD_LEN, 0},	//search_f1_50
    {0x0990, 0x0018, WORD_LEN, 0},	//      = 24
    {0x098C, 0xA409, WORD_LEN, 0},	//search_f2_50
    {0x0990, 0x001A, WORD_LEN, 0},	//      = 26
    {0x098C, 0xA40A, WORD_LEN, 0},	//search_f1_60
    {0x0990, 0x001D, WORD_LEN, 0},	//      = 29
    {0x098C, 0xA40B, WORD_LEN, 0},	//search_f2_60
    {0x0990, 0x001F, WORD_LEN, 0},	//      = 31
    {0x098C, 0x2411, WORD_LEN, 0},	//R9_Step_60 (A)
    {0x0990, 0x0065, WORD_LEN, 0},	//      = 101
    {0x098C, 0x2413, WORD_LEN, 0},	//R9_Step_50 (A)
    {0x0990, 0x0079, WORD_LEN, 0},	//      = 121
    {0x098C, 0x2415, WORD_LEN, 0},	//R9_Step_60 (B)
    {0x0990, 0x0065, WORD_LEN, 0},	//      = 101
    {0x098C, 0x2417, WORD_LEN, 0},	//R9_Step_50 (B)
    {0x0990, 0x0079, WORD_LEN, 0},	//      = 121
    {0x098C, 0xA404, WORD_LEN, 0},	//FD Mode
    {0x0990, 0x0010, WORD_LEN, 0},	//      = 16
    {0x098C, 0xA40D, WORD_LEN, 0},	//Stat_min
    {0x0990, 0x0002, WORD_LEN, 0},	//      = 2
    {0x098C, 0xA40E, WORD_LEN, 0},	//Stat_max
    {0x0990, 0x0003, WORD_LEN, 0},	//      = 3
    {0x098C, 0xA410, WORD_LEN, 0},	//Min_amplitude
    {0x0990, 0x000A, WORD_LEN, 0},	//      = 10

    // Performance Adjustment
    {0x098C, 0xA20E, WORD_LEN, 0}, 	// MCU_ADDRESS [AE_MAX_VIRTGAIN]
    {0x0990, 0x00A0, WORD_LEN, 0}, 	// MCU_DATA_0
    {0x098C, 0x2212, WORD_LEN, 0}, 	// MCU_ADDRESS [AE_MAX_DGAIN_AE1]
    {0x0990, 0x0100, WORD_LEN, 0}, 	// MCU_DATA_0

    // Set normal mode,  Frame rate >=15fps
    {0x098C, 0xA20C, WORD_LEN, 0}, 	// MCU_ADDRESS [AE_MAX_INDEX]
    {0x0990, 0x000B, WORD_LEN, 0}, 	// MCU_DATA_0
    {0x098C, 0xA215, WORD_LEN, 0}, 	// MCU_ADDRESS [AE_INDEX_TH23]
    {0x0990, 0x0009, WORD_LEN, 0}, 	// MCU_DATA_0

    {0x098C, 0xAB22, WORD_LEN, 0}, 	// MCU_ADDRESS [HG_LL_APCORR1]
    {0x0990, 0x0003, WORD_LEN, 0}, 	// MCU_DATA_0

    {0x098C, 0xA24F, WORD_LEN, 0}, 	// MCU_ADDRESS [AE_BASETARGET]
    {0x0990, 0x0038, WORD_LEN, 0}, 	// MCU_DATA_0

    {0x098C, 0xA34A, WORD_LEN, 0}, 	// MCU_ADDRESS [AWB_GAIN_MIN]
    {0x0990, 0x0059, WORD_LEN, 0}, 	// MCU_DATA_0
    {0x098C, 0xA34B, WORD_LEN, 0}, 	// MCU_ADDRESS [AWB_GAIN_MAX]
    {0x0990, 0x00C8, WORD_LEN, 0}, 	// MCU_DATA_0
    {0x098C, 0xA34C, WORD_LEN, 0}, 	// MCU_ADDRESS [AWB_GAINMIN_B]
    {0x0990, 0x0059, WORD_LEN, 0}, 	// MCU_DATA_0
    {0x098C, 0xA34D, WORD_LEN, 0}, 	// MCU_ADDRESS [AWB_GAINMAX_B]
    {0x0990, 0x00A6, WORD_LEN, 0}, 	// MCU_DATA_0
    {0x098C, 0xA351, WORD_LEN, 0}, 	// MCU_ADDRESS [AWB_CCM_POSITION_MIN]
    {0x0990, 0x0000, WORD_LEN, 0}, 	// MCU_DATA_0
    {0x098C, 0xA352, WORD_LEN, 0}, 	// MCU_ADDRESS [AWB_CCM_POSITION_MAX]
    {0x0990, 0x007F, WORD_LEN, 0}, 	// MCU_DATA_0
    
    {0x098C, 0xAB3C, WORD_LEN, 0}, 	// MCU_ADDRESS [HG_GAMMA_TABLE_A_0]
    {0x0990, 0x0000, WORD_LEN, 0}, 	// MCU_DATA_0
    {0x098C, 0xAB3D, WORD_LEN, 0}, 	// MCU_ADDRESS [HG_GAMMA_TABLE_A_1]
    {0x0990, 0x0003, WORD_LEN, 0}, 	// MCU_DATA_0
    {0x098C, 0xAB3E, WORD_LEN, 0}, 	// MCU_ADDRESS [HG_GAMMA_TABLE_A_2]
    {0x0990, 0x000B, WORD_LEN, 0}, 	// MCU_DATA_0
    {0x098C, 0xAB3F, WORD_LEN, 0}, 	// MCU_ADDRESS [HG_GAMMA_TABLE_A_3]
    {0x0990, 0x0024, WORD_LEN, 0}, 	// MCU_DATA_0
    {0x098C, 0xAB40, WORD_LEN, 0}, 	// MCU_ADDRESS [HG_GAMMA_TABLE_A_4]
    {0x0990, 0x0052, WORD_LEN, 0}, 	// MCU_DATA_0
    {0x098C, 0xAB41, WORD_LEN, 0}, 	// MCU_ADDRESS [HG_GAMMA_TABLE_A_5]
    {0x0990, 0x0073, WORD_LEN, 0}, 	// MCU_DATA_0
    {0x098C, 0xAB42, WORD_LEN, 0}, 	// MCU_ADDRESS [HG_GAMMA_TABLE_A_6]
    {0x0990, 0x008E, WORD_LEN, 0}, 	// MCU_DATA_0
    {0x098C, 0xAB43, WORD_LEN, 0}, 	// MCU_ADDRESS [HG_GAMMA_TABLE_A_7]
    {0x0990, 0x00A2, WORD_LEN, 0}, 	// MCU_DATA_0
    {0x098C, 0xAB44, WORD_LEN, 0}, 	// MCU_ADDRESS [HG_GAMMA_TABLE_A_8]
    {0x0990, 0x00B3, WORD_LEN, 0}, 	// MCU_DATA_0
    {0x098C, 0xAB45, WORD_LEN, 0}, 	// MCU_ADDRESS [HG_GAMMA_TABLE_A_9]
    {0x0990, 0x00C0, WORD_LEN, 0}, 	// MCU_DATA_0
    {0x098C, 0xAB46, WORD_LEN, 0}, 	// MCU_ADDRESS [HG_GAMMA_TABLE_A_10]
    {0x0990, 0x00CB, WORD_LEN, 0}, 	// MCU_DATA_0
    {0x098C, 0xAB47, WORD_LEN, 0}, 	// MCU_ADDRESS [HG_GAMMA_TABLE_A_11]
    {0x0990, 0x00D4, WORD_LEN, 0}, 	// MCU_DATA_0
    {0x098C, 0xAB48, WORD_LEN, 0}, 	// MCU_ADDRESS [HG_GAMMA_TABLE_A_12]
    {0x0990, 0x00DC, WORD_LEN, 0}, 	// MCU_DATA_0
    {0x098C, 0xAB49, WORD_LEN, 0}, 	// MCU_ADDRESS [HG_GAMMA_TABLE_A_13]
    {0x0990, 0x00E4, WORD_LEN, 0}, 	// MCU_DATA_0
    {0x098C, 0xAB4A, WORD_LEN, 0}, 	// MCU_ADDRESS [HG_GAMMA_TABLE_A_14]
    {0x0990, 0x00EA, WORD_LEN, 0}, 	// MCU_DATA_0
    {0x098C, 0xAB4B, WORD_LEN, 0}, 	// MCU_ADDRESS [HG_GAMMA_TABLE_A_15]
    {0x0990, 0x00F0, WORD_LEN, 0}, 	// MCU_DATA_0
    {0x098C, 0xAB4C, WORD_LEN, 0}, 	// MCU_ADDRESS [HG_GAMMA_TABLE_A_16]
    {0x0990, 0x00F5, WORD_LEN, 0}, 	// MCU_DATA_0
    {0x098C, 0xAB4D, WORD_LEN, 0}, 	// MCU_ADDRESS [HG_GAMMA_TABLE_A_17]
    {0x0990, 0x00FA, WORD_LEN, 0}, 	// MCU_DATA_0
    {0x098C, 0xAB4E, WORD_LEN, 0}, 	// MCU_ADDRESS [HG_GAMMA_TABLE_A_18]
    {0x0990, 0x00FF, WORD_LEN, 0}, 	// MCU_DATA_0
    {0x098C, 0xAB4F, WORD_LEN, 0}, 	// MCU_ADDRESS [HG_GAMMA_TABLE_B_0]
    {0x0990, 0x0000, WORD_LEN, 0}, 	// MCU_DATA_0
    {0x098C, 0xAB50, WORD_LEN, 0}, 	// MCU_ADDRESS [HG_GAMMA_TABLE_B_1]
    {0x0990, 0x0003, WORD_LEN, 0}, 	// MCU_DATA_0
    {0x098C, 0xAB51, WORD_LEN, 0}, 	// MCU_ADDRESS [HG_GAMMA_TABLE_B_2]
    {0x0990, 0x000B, WORD_LEN, 0}, 	// MCU_DATA_0
    {0x098C, 0xAB52, WORD_LEN, 0}, 	// MCU_ADDRESS [HG_GAMMA_TABLE_B_3]
    {0x0990, 0x0024, WORD_LEN, 0}, 	// MCU_DATA_0
    {0x098C, 0xAB53, WORD_LEN, 0}, 	// MCU_ADDRESS [HG_GAMMA_TABLE_B_4]
    {0x0990, 0x0052, WORD_LEN, 0}, 	// MCU_DATA_0
    {0x098C, 0xAB54, WORD_LEN, 0}, 	// MCU_ADDRESS [HG_GAMMA_TABLE_B_5]
    {0x0990, 0x0073, WORD_LEN, 0}, 	// MCU_DATA_0
    {0x098C, 0xAB55, WORD_LEN, 0}, 	// MCU_ADDRESS [HG_GAMMA_TABLE_B_6]
    {0x0990, 0x008E, WORD_LEN, 0}, 	// MCU_DATA_0
    {0x098C, 0xAB56, WORD_LEN, 0}, 	// MCU_ADDRESS [HG_GAMMA_TABLE_B_7]
    {0x0990, 0x00A2, WORD_LEN, 0}, 	// MCU_DATA_0
    {0x098C, 0xAB57, WORD_LEN, 0}, 	// MCU_ADDRESS [HG_GAMMA_TABLE_B_8]
    {0x0990, 0x00B3, WORD_LEN, 0}, 	// MCU_DATA_0
    {0x098C, 0xAB58, WORD_LEN, 0}, 	// MCU_ADDRESS [HG_GAMMA_TABLE_B_9]
    {0x0990, 0x00C0, WORD_LEN, 0}, 	// MCU_DATA_0
    {0x098C, 0xAB59, WORD_LEN, 0}, 	// MCU_ADDRESS [HG_GAMMA_TABLE_B_10]
    {0x0990, 0x00CB, WORD_LEN, 0}, 	// MCU_DATA_0
    {0x098C, 0xAB5A, WORD_LEN, 0}, 	// MCU_ADDRESS [HG_GAMMA_TABLE_B_11]
    {0x0990, 0x00D4, WORD_LEN, 0}, 	// MCU_DATA_0
    {0x098C, 0xAB5B, WORD_LEN, 0}, 	// MCU_ADDRESS [HG_GAMMA_TABLE_B_12]
    {0x0990, 0x00DC, WORD_LEN, 0}, 	// MCU_DATA_0
    {0x098C, 0xAB5C, WORD_LEN, 0}, 	// MCU_ADDRESS [HG_GAMMA_TABLE_B_13]
    {0x0990, 0x00E4, WORD_LEN, 0}, 	// MCU_DATA_0
    {0x098C, 0xAB5D, WORD_LEN, 0}, 	// MCU_ADDRESS [HG_GAMMA_TABLE_B_14]
    {0x0990, 0x00EA, WORD_LEN, 0}, 	// MCU_DATA_0
    {0x098C, 0xAB5E, WORD_LEN, 0}, 	// MCU_ADDRESS [HG_GAMMA_TABLE_B_15]
    {0x0990, 0x00F0, WORD_LEN, 0}, 	// MCU_DATA_0
    {0x098C, 0xAB5F, WORD_LEN, 0}, 	// MCU_ADDRESS [HG_GAMMA_TABLE_B_16]
    {0x0990, 0x00F5, WORD_LEN, 0}, 	// MCU_DATA_0
    {0x098C, 0xAB60, WORD_LEN, 0}, 	// MCU_ADDRESS [HG_GAMMA_TABLE_B_17]
    {0x0990, 0x00FA, WORD_LEN, 0}, 	// MCU_DATA_0
    {0x098C, 0xAB61, WORD_LEN, 0}, 	// MCU_ADDRESS [HG_GAMMA_TABLE_B_18]
    {0x0990, 0x00FF, WORD_LEN, 0}, 	// MCU_DATA_0
};

static struct mt9d113_i2c_reg_conf const wb_cloudy_tbl[] = {
    {0x098C, 0xA34A, WORD_LEN, 0}, 	// MCU_ADDRESS [AWB_GAIN_MIN]
    {0x0990, 0x00D0, WORD_LEN, 0}, 	// MCU_DATA_0
    {0x098C, 0xA34B, WORD_LEN, 0}, 	// MCU_ADDRESS [AWB_GAIN_MAX]
    {0x0990, 0x00D0, WORD_LEN, 0}, 	// MCU_DATA_0
    {0x098C, 0xA34C, WORD_LEN, 0}, 	// MCU_ADDRESS [AWB_GAINMIN_B]
    {0x0990, 0x0056, WORD_LEN, 0}, 	// MCU_DATA_0
    {0x098C, 0xA34D, WORD_LEN, 0}, 	// MCU_ADDRESS [AWB_GAINMAX_B]
    {0x0990, 0x0056, WORD_LEN, 0}, 	// MCU_DATA_0
    {0x098C, 0xA351, WORD_LEN, 0}, 	// MCU_ADDRESS [AWB_CCM_POSITION_MIN]
    {0x0990, 0x007f, WORD_LEN, 0}, 	// MCU_DATA_0
    {0x098C, 0xA352, WORD_LEN, 0}, 	// MCU_ADDRESS [AWB_CCM_POSITION_MAX]
    {0x0990, 0x007F, WORD_LEN, 0}, 	// MCU_DATA_0
    {0x098C, 0xA103, WORD_LEN, 0}, 	// MCU_ADDRESS [SEQ_CMD]
    {0x0990, 0x0005, WORD_LEN, 0}, 	// MCU_DATA_0
};

static struct mt9d113_i2c_reg_conf const wb_daylight_tbl[] = {
    {0x098C, 0xA34A, WORD_LEN, 0}, 	// MCU_ADDRESS [AWB_GAIN_MIN]
    {0x0990, 0x00C2, WORD_LEN, 0},	// MCU_DATA_0
    {0x098C, 0xA34B, WORD_LEN, 0}, 	// MCU_ADDRESS [AWB_GAIN_MAX]
    {0x0990, 0x00c4, WORD_LEN, 0}, 	// MCU_DATA_0
    {0x098C, 0xA34C, WORD_LEN, 0}, 	// MCU_ADDRESS [AWB_GAINMIN_B]
    {0x0990, 0x005d, WORD_LEN, 0}, 	// MCU_DATA_0
    {0x098C, 0xA34D, WORD_LEN, 0}, 	// MCU_ADDRESS [AWB_GAINMAX_B]
    {0x0990, 0x005f, WORD_LEN, 0}, 	// MCU_DATA_0
    {0x098C, 0xA351, WORD_LEN, 0}, 	// MCU_ADDRESS [AWB_CCM_POSITION_MIN]
    {0x0990, 0x007f, WORD_LEN, 0}, 	// MCU_DATA_0
    {0x098C, 0xA352, WORD_LEN, 0}, 	// MCU_ADDRESS [AWB_CCM_POSITION_MAX]
    {0x0990, 0x007F, WORD_LEN, 0}, 	// MCU_DATA_0
    {0x098C, 0xA103, WORD_LEN, 0}, 	// MCU_ADDRESS [SEQ_CMD]
    {0x0990, 0x0005, WORD_LEN, 0}, 	// MCU_DATA_0
};

static struct mt9d113_i2c_reg_conf const wb_flourescant_tbl[] = {
    {0x098C, 0xA34A, WORD_LEN, 0}, 	// MCU_ADDRESS [AWB_GAIN_MIN]
    {0x0990, 0x008C, WORD_LEN, 0}, 	// MCU_DATA_0
    {0x098C, 0xA34B, WORD_LEN, 0}, 	// MCU_ADDRESS [AWB_GAIN_MAX]
    {0x0990, 0x008C, WORD_LEN, 0}, 	// MCU_DATA_0
    {0x098C, 0xA34C, WORD_LEN, 0}, 	// MCU_ADDRESS [AWB_GAINMIN_B]
    {0x0990, 0x0081, WORD_LEN, 0}, 	// MCU_DATA_0
    {0x098C, 0xA34D, WORD_LEN, 0}, 	// MCU_ADDRESS [AWB_GAINMAX_B]
    {0x0990, 0x0081, WORD_LEN, 0}, 	// MCU_DATA_0
    {0x098C, 0xA351, WORD_LEN, 0}, 	// MCU_ADDRESS [AWB_CCM_POSITION_MIN]
    {0x0990, 0x0066, WORD_LEN, 0}, 	// MCU_DATA_0
    {0x098C, 0xA352, WORD_LEN, 0}, 	// MCU_ADDRESS [AWB_CCM_POSITION_MAX]
    {0x0990, 0x0066, WORD_LEN, 0}, 	// MCU_DATA_0
    {0x098C, 0xA103, WORD_LEN, 0}, 	// MCU_ADDRESS [SEQ_CMD]
    {0x0990, 0x0005, WORD_LEN, 0}, 	// MCU_DATA_0
};

static struct mt9d113_i2c_reg_conf const wb_incandescent_tbl[] = {
    {0x098C, 0xA34A, WORD_LEN, 0}, 	// MCU_ADDRESS [AWB_GAIN_MIN]
    {0x0990, 0x0086, WORD_LEN, 0}, 	// MCU_DATA_0
    {0x098C, 0xA34B, WORD_LEN, 0}, 	// MCU_ADDRESS [AWB_GAIN_MAX]
    {0x0990, 0x0088, WORD_LEN, 0}, 	// MCU_DATA_0
    {0x098C, 0xA34C, WORD_LEN, 0}, 	// MCU_ADDRESS [AWB_GAINMIN_B]
    {0x0990, 0x0092, WORD_LEN, 0}, 	// MCU_DATA_0
    {0x098C, 0xA34D, WORD_LEN, 0}, 	// MCU_ADDRESS [AWB_GAINMAX_B]
    {0x0990, 0x0094, WORD_LEN, 0}, 	// MCU_DATA_0
    {0x098C, 0xA351, WORD_LEN, 0}, 	// MCU_ADDRESS [AWB_CCM_POSITION_MIN]
    {0x0990, 0x0000, WORD_LEN, 0}, 	// MCU_DATA_0
    {0x098C, 0xA352, WORD_LEN, 0}, 	// MCU_ADDRESS [AWB_CCM_POSITION_MAX]
    {0x0990, 0x0000, WORD_LEN, 0}, 	// MCU_DATA_0
    {0x098C, 0xA103, WORD_LEN, 0}, 	// MCU_ADDRESS [SEQ_CMD]
    {0x0990, 0x0005, WORD_LEN, 0}, 	// MCU_DATA_0
};

static struct mt9d113_i2c_reg_conf const wb_auto_tbl[] = {
    {0x098C, 0xA34A, WORD_LEN, 0}, 	// MCU_ADDRESS [AWB_GAIN_MIN]
    {0x0990, 0x0059, WORD_LEN, 0}, 	// MCU_DATA_0
    {0x098C, 0xA34B, WORD_LEN, 0}, 	// MCU_ADDRESS [AWB_GAIN_MAX]
    {0x0990, 0x00C8, WORD_LEN, 0}, 	// MCU_DATA_0
    {0x098C, 0xA34C, WORD_LEN, 0}, 	// MCU_ADDRESS [AWB_GAINMIN_B]
    {0x0990, 0x0059, WORD_LEN, 0}, 	// MCU_DATA_0
    {0x098C, 0xA34D, WORD_LEN, 0}, 	// MCU_ADDRESS [AWB_GAINMAX_B]
    {0x0990, 0x00A6, WORD_LEN, 0}, 	// MCU_DATA_0
    {0x098C, 0xA351, WORD_LEN, 0}, 	// MCU_ADDRESS [AWB_CCM_POSITION_MIN]
    {0x0990, 0x0000, WORD_LEN, 0}, 	// MCU_DATA_0
    {0x098C, 0xA352, WORD_LEN, 0}, 	// MCU_ADDRESS [AWB_CCM_POSITION_MAX]
    {0x0990, 0x007F, WORD_LEN, 0}, 	// MCU_DATA_0
    {0x098C, 0xA103, WORD_LEN, 0}, 	// MCU_ADDRESS [SEQ_CMD]
    {0x0990, 0x0005, WORD_LEN, 0}, 	// MCU_DATA_0
};

/* Contrast Setup */
static struct mt9d113_i2c_reg_conf const contrast_tbl_0[] = {
    {0x098C, 0xAB3C, WORD_LEN, 0}, 	// MCU_ADDRESS [HG_GAMMA_TABLE_A_0]
    {0x0990, 0x0000, WORD_LEN, 0}, 	// MCU_DATA_0
    {0x098C, 0xAB3D, WORD_LEN, 0}, 	// MCU_ADDRESS [HG_GAMMA_TABLE_A_1]
    {0x0990, 0x000D, WORD_LEN, 0}, 	// MCU_DATA_0
    {0x098C, 0xAB3E, WORD_LEN, 0}, 	// MCU_ADDRESS [HG_GAMMA_TABLE_A_2]
    {0x0990, 0x002A, WORD_LEN, 0}, 	// MCU_DATA_0
    {0x098C, 0xAB3F, WORD_LEN, 0}, 	// MCU_ADDRESS [HG_GAMMA_TABLE_A_3]
    {0x0990, 0x005B, WORD_LEN, 0}, 	// MCU_DATA_0
    {0x098C, 0xAB40, WORD_LEN, 0}, 	// MCU_ADDRESS [HG_GAMMA_TABLE_A_4]
    {0x0990, 0x0080, WORD_LEN, 0}, 	// MCU_DATA_0
    {0x098C, 0xAB41, WORD_LEN, 0}, 	// MCU_ADDRESS [HG_GAMMA_TABLE_A_5]
    {0x0990, 0x0097, WORD_LEN, 0}, 	// MCU_DATA_0
    {0x098C, 0xAB42, WORD_LEN, 0}, 	// MCU_ADDRESS [HG_GAMMA_TABLE_A_6]
    {0x0990, 0x00A8, WORD_LEN, 0}, 	// MCU_DATA_0
    {0x098C, 0xAB43, WORD_LEN, 0}, 	// MCU_ADDRESS [HG_GAMMA_TABLE_A_7]
    {0x0990, 0x00B5, WORD_LEN, 0}, 	// MCU_DATA_0
    {0x098C, 0xAB44, WORD_LEN, 0}, 	// MCU_ADDRESS [HG_GAMMA_TABLE_A_8]
    {0x0990, 0x00C0, WORD_LEN, 0}, 	// MCU_DATA_0
    {0x098C, 0xAB45, WORD_LEN, 0}, 	// MCU_ADDRESS [HG_GAMMA_TABLE_A_9]
    {0x0990, 0x00C9, WORD_LEN, 0}, 	// MCU_DATA_0
    {0x098C, 0xAB46, WORD_LEN, 0}, 	// MCU_ADDRESS [HG_GAMMA_TABLE_A_10]
    {0x0990, 0x00D2, WORD_LEN, 0}, 	// MCU_DATA_0
    {0x098C, 0xAB47, WORD_LEN, 0}, 	// MCU_ADDRESS [HG_GAMMA_TABLE_A_11]
    {0x0990, 0x00D9, WORD_LEN, 0}, 	// MCU_DATA_0
    {0x098C, 0xAB48, WORD_LEN, 0}, 	// MCU_ADDRESS [HG_GAMMA_TABLE_A_12]
    {0x0990, 0x00E0, WORD_LEN, 0}, 	// MCU_DATA_0
    {0x098C, 0xAB49, WORD_LEN, 0}, 	// MCU_ADDRESS [HG_GAMMA_TABLE_A_13]
    {0x0990, 0x00E6, WORD_LEN, 0}, 	// MCU_DATA_0
    {0x098C, 0xAB4A, WORD_LEN, 0}, 	// MCU_ADDRESS [HG_GAMMA_TABLE_A_14]
    {0x0990, 0x00EC, WORD_LEN, 0}, 	// MCU_DATA_0
    {0x098C, 0xAB4B, WORD_LEN, 0}, 	// MCU_ADDRESS [HG_GAMMA_TABLE_A_15]
    {0x0990, 0x00F1, WORD_LEN, 0}, 	// MCU_DATA_0
    {0x098C, 0xAB4C, WORD_LEN, 0}, 	// MCU_ADDRESS [HG_GAMMA_TABLE_A_16]
    {0x0990, 0x00F6, WORD_LEN, 0}, 	// MCU_DATA_0
    {0x098C, 0xAB4D, WORD_LEN, 0}, 	// MCU_ADDRESS [HG_GAMMA_TABLE_A_17]
    {0x0990, 0x00FB, WORD_LEN, 0}, 	// MCU_DATA_0
    {0x098C, 0xAB4E, WORD_LEN, 0}, 	// MCU_ADDRESS [HG_GAMMA_TABLE_A_18]
    {0x0990, 0x00FF, WORD_LEN, 0}, 	// MCU_DATA_0
    {0x098C, 0xAB4F, WORD_LEN, 0}, 	// MCU_ADDRESS [HG_GAMMA_TABLE_B_0]
    {0x0990, 0x0000, WORD_LEN, 0}, 	// MCU_DATA_0
    {0x098C, 0xAB50, WORD_LEN, 0}, 	// MCU_ADDRESS [HG_GAMMA_TABLE_B_1]
    {0x0990, 0x000D, WORD_LEN, 0}, 	// MCU_DATA_0
    {0x098C, 0xAB51, WORD_LEN, 0}, 	// MCU_ADDRESS [HG_GAMMA_TABLE_B_2]
    {0x0990, 0x002A, WORD_LEN, 0}, 	// MCU_DATA_0
    {0x098C, 0xAB52, WORD_LEN, 0}, 	// MCU_ADDRESS [HG_GAMMA_TABLE_B_3]
    {0x0990, 0x005B, WORD_LEN, 0}, 	// MCU_DATA_0
    {0x098C, 0xAB53, WORD_LEN, 0}, 	// MCU_ADDRESS [HG_GAMMA_TABLE_B_4]
    {0x0990, 0x0080, WORD_LEN, 0}, 	// MCU_DATA_0
    {0x098C, 0xAB54, WORD_LEN, 0}, 	// MCU_ADDRESS [HG_GAMMA_TABLE_B_5]
    {0x0990, 0x0097, WORD_LEN, 0}, 	// MCU_DATA_0
    {0x098C, 0xAB55, WORD_LEN, 0}, 	// MCU_ADDRESS [HG_GAMMA_TABLE_B_6]
    {0x0990, 0x00A8, WORD_LEN, 0}, 	// MCU_DATA_0
    {0x098C, 0xAB56, WORD_LEN, 0}, 	// MCU_ADDRESS [HG_GAMMA_TABLE_B_7]
    {0x0990, 0x00B5, WORD_LEN, 0}, 	// MCU_DATA_0
    {0x098C, 0xAB57, WORD_LEN, 0}, 	// MCU_ADDRESS [HG_GAMMA_TABLE_B_8]
    {0x0990, 0x00C0, WORD_LEN, 0}, 	// MCU_DATA_0
    {0x098C, 0xAB58, WORD_LEN, 0}, 	// MCU_ADDRESS [HG_GAMMA_TABLE_B_9]
    {0x0990, 0x00C9, WORD_LEN, 0}, 	// MCU_DATA_0
    {0x098C, 0xAB59, WORD_LEN, 0}, 	// MCU_ADDRESS [HG_GAMMA_TABLE_B_10]
    {0x0990, 0x00D2, WORD_LEN, 0}, 	// MCU_DATA_0
    {0x098C, 0xAB5A, WORD_LEN, 0}, 	// MCU_ADDRESS [HG_GAMMA_TABLE_B_11]
    {0x0990, 0x00D9, WORD_LEN, 0}, 	// MCU_DATA_0
    {0x098C, 0xAB5B, WORD_LEN, 0}, 	// MCU_ADDRESS [HG_GAMMA_TABLE_B_12]
    {0x0990, 0x00E0, WORD_LEN, 0}, 	// MCU_DATA_0
    {0x098C, 0xAB5C, WORD_LEN, 0}, 	// MCU_ADDRESS [HG_GAMMA_TABLE_B_13]
    {0x0990, 0x00E6, WORD_LEN, 0}, 	// MCU_DATA_0
    {0x098C, 0xAB5D, WORD_LEN, 0}, 	// MCU_ADDRESS [HG_GAMMA_TABLE_B_14]
    {0x0990, 0x00EC, WORD_LEN, 0}, 	// MCU_DATA_0
    {0x098C, 0xAB5E, WORD_LEN, 0}, 	// MCU_ADDRESS [HG_GAMMA_TABLE_B_15]
    {0x0990, 0x00F1, WORD_LEN, 0}, 	// MCU_DATA_0
    {0x098C, 0xAB5F, WORD_LEN, 0}, 	// MCU_ADDRESS [HG_GAMMA_TABLE_B_16]
    {0x0990, 0x00F6, WORD_LEN, 0}, 	// MCU_DATA_0
    {0x098C, 0xAB60, WORD_LEN, 0}, 	// MCU_ADDRESS [HG_GAMMA_TABLE_B_17]
    {0x0990, 0x00FB, WORD_LEN, 0}, 	// MCU_DATA_0
    {0x098C, 0xAB61, WORD_LEN, 0}, 	// MCU_ADDRESS [HG_GAMMA_TABLE_B_18]
    {0x0990, 0x00FF, WORD_LEN, 0}, 	// MCU_DATA_0
};

static struct mt9d113_i2c_reg_conf const contrast_tbl_1[] = {
    {0x098C, 0xAB3C, WORD_LEN, 0}, 	// MCU_ADDRESS [HG_GAMMA_TABLE_A_0]
    {0x0990, 0x0000, WORD_LEN, 0}, 	// MCU_DATA_0
    {0x098C, 0xAB3D, WORD_LEN, 0}, 	// MCU_ADDRESS [HG_GAMMA_TABLE_A_1]
    {0x0990, 0x0004, WORD_LEN, 0}, 	// MCU_DATA_0
    {0x098C, 0xAB3E, WORD_LEN, 0}, 	// MCU_ADDRESS [HG_GAMMA_TABLE_A_2]
    {0x0990, 0x000F, WORD_LEN, 0}, 	// MCU_DATA_0
    {0x098C, 0xAB3F, WORD_LEN, 0}, 	// MCU_ADDRESS [HG_GAMMA_TABLE_A_3]
    {0x0990, 0x0030, WORD_LEN, 0}, 	// MCU_DATA_0
    {0x098C, 0xAB40, WORD_LEN, 0}, 	// MCU_ADDRESS [HG_GAMMA_TABLE_A_4]
    {0x0990, 0x0064, WORD_LEN, 0}, 	// MCU_DATA_0
    {0x098C, 0xAB41, WORD_LEN, 0}, 	// MCU_ADDRESS [HG_GAMMA_TABLE_A_5]
    {0x0990, 0x0084, WORD_LEN, 0}, 	// MCU_DATA_0
    {0x098C, 0xAB42, WORD_LEN, 0}, 	// MCU_ADDRESS [HG_GAMMA_TABLE_A_6]
    {0x0990, 0x009A, WORD_LEN, 0}, 	// MCU_DATA_0
    {0x098C, 0xAB43, WORD_LEN, 0}, 	// MCU_ADDRESS [HG_GAMMA_TABLE_A_7]
    {0x0990, 0x00AB, WORD_LEN, 0}, 	// MCU_DATA_0
    {0x098C, 0xAB44, WORD_LEN, 0}, 	// MCU_ADDRESS [HG_GAMMA_TABLE_A_8]
    {0x0990, 0x00B9, WORD_LEN, 0}, 	// MCU_DATA_0
    {0x098C, 0xAB45, WORD_LEN, 0}, 	// MCU_ADDRESS [HG_GAMMA_TABLE_A_9]
    {0x0990, 0x00C4, WORD_LEN, 0}, 	// MCU_DATA_0
    {0x098C, 0xAB46, WORD_LEN, 0}, 	// MCU_ADDRESS [HG_GAMMA_TABLE_A_10]
    {0x0990, 0x00CE, WORD_LEN, 0}, 	// MCU_DATA_0
    {0x098C, 0xAB47, WORD_LEN, 0}, 	// MCU_ADDRESS [HG_GAMMA_TABLE_A_11]
    {0x0990, 0x00D7, WORD_LEN, 0}, 	// MCU_DATA_0
    {0x098C, 0xAB48, WORD_LEN, 0}, 	// MCU_ADDRESS [HG_GAMMA_TABLE_A_12]
    {0x0990, 0x00DE, WORD_LEN, 0}, 	// MCU_DATA_0
    {0x098C, 0xAB49, WORD_LEN, 0}, 	// MCU_ADDRESS [HG_GAMMA_TABLE_A_13]
    {0x0990, 0x00E5, WORD_LEN, 0}, 	// MCU_DATA_0
    {0x098C, 0xAB4A, WORD_LEN, 0}, 	// MCU_ADDRESS [HG_GAMMA_TABLE_A_14]
    {0x0990, 0x00EB, WORD_LEN, 0}, 	// MCU_DATA_0
    {0x098C, 0xAB4B, WORD_LEN, 0}, 	// MCU_ADDRESS [HG_GAMMA_TABLE_A_15]
    {0x0990, 0x00F1, WORD_LEN, 0}, 	// MCU_DATA_0
    {0x098C, 0xAB4C, WORD_LEN, 0}, 	// MCU_ADDRESS [HG_GAMMA_TABLE_A_16]
    {0x0990, 0x00F6, WORD_LEN, 0}, 	// MCU_DATA_0
    {0x098C, 0xAB4D, WORD_LEN, 0}, 	// MCU_ADDRESS [HG_GAMMA_TABLE_A_17]
    {0x0990, 0x00FB, WORD_LEN, 0}, 	// MCU_DATA_0
    {0x098C, 0xAB4E, WORD_LEN, 0}, 	// MCU_ADDRESS [HG_GAMMA_TABLE_A_18]
    {0x0990, 0x00FF, WORD_LEN, 0}, 	// MCU_DATA_0
    {0x098C, 0xAB4F, WORD_LEN, 0}, 	// MCU_ADDRESS [HG_GAMMA_TABLE_B_0]
    {0x0990, 0x0000, WORD_LEN, 0}, 	// MCU_DATA_0
    {0x098C, 0xAB50, WORD_LEN, 0}, 	// MCU_ADDRESS [HG_GAMMA_TABLE_B_1]
    {0x0990, 0x0004, WORD_LEN, 0}, 	// MCU_DATA_0
    {0x098C, 0xAB51, WORD_LEN, 0}, 	// MCU_ADDRESS [HG_GAMMA_TABLE_B_2]
    {0x0990, 0x000F, WORD_LEN, 0}, 	// MCU_DATA_0
    {0x098C, 0xAB52, WORD_LEN, 0}, 	// MCU_ADDRESS [HG_GAMMA_TABLE_B_3]
    {0x0990, 0x0030, WORD_LEN, 0}, 	// MCU_DATA_0
    {0x098C, 0xAB53, WORD_LEN, 0}, 	// MCU_ADDRESS [HG_GAMMA_TABLE_B_4]
    {0x0990, 0x0064, WORD_LEN, 0}, 	// MCU_DATA_0
    {0x098C, 0xAB54, WORD_LEN, 0}, 	// MCU_ADDRESS [HG_GAMMA_TABLE_B_5]
    {0x0990, 0x0084, WORD_LEN, 0}, 	// MCU_DATA_0
    {0x098C, 0xAB55, WORD_LEN, 0}, 	// MCU_ADDRESS [HG_GAMMA_TABLE_B_6]
    {0x0990, 0x009A, WORD_LEN, 0}, 	// MCU_DATA_0
    {0x098C, 0xAB56, WORD_LEN, 0}, 	// MCU_ADDRESS [HG_GAMMA_TABLE_B_7]
    {0x0990, 0x00AB, WORD_LEN, 0}, 	// MCU_DATA_0
    {0x098C, 0xAB57, WORD_LEN, 0}, 	// MCU_ADDRESS [HG_GAMMA_TABLE_B_8]
    {0x0990, 0x00B9, WORD_LEN, 0}, 	// MCU_DATA_0
    {0x098C, 0xAB58, WORD_LEN, 0}, 	// MCU_ADDRESS [HG_GAMMA_TABLE_B_9]
    {0x0990, 0x00C4, WORD_LEN, 0}, 	// MCU_DATA_0
    {0x098C, 0xAB59, WORD_LEN, 0}, 	// MCU_ADDRESS [HG_GAMMA_TABLE_B_10]
    {0x0990, 0x00CE, WORD_LEN, 0}, 	// MCU_DATA_0
    {0x098C, 0xAB5A, WORD_LEN, 0}, 	// MCU_ADDRESS [HG_GAMMA_TABLE_B_11]
    {0x0990, 0x00D7, WORD_LEN, 0}, 	// MCU_DATA_0
    {0x098C, 0xAB5B, WORD_LEN, 0}, 	// MCU_ADDRESS [HG_GAMMA_TABLE_B_12]
    {0x0990, 0x00DE, WORD_LEN, 0}, 	// MCU_DATA_0
    {0x098C, 0xAB5C, WORD_LEN, 0}, 	// MCU_ADDRESS [HG_GAMMA_TABLE_B_13]
    {0x0990, 0x00E5, WORD_LEN, 0}, 	// MCU_DATA_0
    {0x098C, 0xAB5D, WORD_LEN, 0}, 	// MCU_ADDRESS [HG_GAMMA_TABLE_B_14]
    {0x0990, 0x00EB, WORD_LEN, 0}, 	// MCU_DATA_0
    {0x098C, 0xAB5E, WORD_LEN, 0}, 	// MCU_ADDRESS [HG_GAMMA_TABLE_B_15]
    {0x0990, 0x00F1, WORD_LEN, 0}, 	// MCU_DATA_0
    {0x098C, 0xAB5F, WORD_LEN, 0}, 	// MCU_ADDRESS [HG_GAMMA_TABLE_B_16]
    {0x0990, 0x00F6, WORD_LEN, 0}, 	// MCU_DATA_0
    {0x098C, 0xAB60, WORD_LEN, 0}, 	// MCU_ADDRESS [HG_GAMMA_TABLE_B_17]
    {0x0990, 0x00FB, WORD_LEN, 0}, 	// MCU_DATA_0
    {0x098C, 0xAB61, WORD_LEN, 0}, 	// MCU_ADDRESS [HG_GAMMA_TABLE_B_18]
    {0x0990, 0x00FF, WORD_LEN, 0}, 	// MCU_DATA_0
};

static struct mt9d113_i2c_reg_conf const contrast_tbl_2[] = {
    {0x098C, 0xAB3C, WORD_LEN, 0}, 	// MCU_ADDRESS [HG_GAMMA_TABLE_A_0]
    {0x0990, 0x0000, WORD_LEN, 0}, 	// MCU_DATA_0
    {0x098C, 0xAB3D, WORD_LEN, 0}, 	// MCU_ADDRESS [HG_GAMMA_TABLE_A_1]
    {0x0990, 0x0003, WORD_LEN, 0}, 	// MCU_DATA_0
    {0x098C, 0xAB3E, WORD_LEN, 0}, 	// MCU_ADDRESS [HG_GAMMA_TABLE_A_2]
    {0x0990, 0x000B, WORD_LEN, 0}, 	// MCU_DATA_0
    {0x098C, 0xAB3F, WORD_LEN, 0}, 	// MCU_ADDRESS [HG_GAMMA_TABLE_A_3]
    {0x0990, 0x0024, WORD_LEN, 0}, 	// MCU_DATA_0
    {0x098C, 0xAB40, WORD_LEN, 0}, 	// MCU_ADDRESS [HG_GAMMA_TABLE_A_4]
    {0x0990, 0x0052, WORD_LEN, 0}, 	// MCU_DATA_0
    {0x098C, 0xAB41, WORD_LEN, 0}, 	// MCU_ADDRESS [HG_GAMMA_TABLE_A_5]
    {0x0990, 0x0073, WORD_LEN, 0}, 	// MCU_DATA_0
    {0x098C, 0xAB42, WORD_LEN, 0}, 	// MCU_ADDRESS [HG_GAMMA_TABLE_A_6]
    {0x0990, 0x008E, WORD_LEN, 0}, 	// MCU_DATA_0
    {0x098C, 0xAB43, WORD_LEN, 0}, 	// MCU_ADDRESS [HG_GAMMA_TABLE_A_7]
    {0x0990, 0x00A2, WORD_LEN, 0}, 	// MCU_DATA_0
    {0x098C, 0xAB44, WORD_LEN, 0}, 	// MCU_ADDRESS [HG_GAMMA_TABLE_A_8]
    {0x0990, 0x00B3, WORD_LEN, 0}, 	// MCU_DATA_0
    {0x098C, 0xAB45, WORD_LEN, 0}, 	// MCU_ADDRESS [HG_GAMMA_TABLE_A_9]
    {0x0990, 0x00C0, WORD_LEN, 0}, 	// MCU_DATA_0
    {0x098C, 0xAB46, WORD_LEN, 0}, 	// MCU_ADDRESS [HG_GAMMA_TABLE_A_10]
    {0x0990, 0x00CB, WORD_LEN, 0}, 	// MCU_DATA_0
    {0x098C, 0xAB47, WORD_LEN, 0}, 	// MCU_ADDRESS [HG_GAMMA_TABLE_A_11]
    {0x0990, 0x00D4, WORD_LEN, 0}, 	// MCU_DATA_0
    {0x098C, 0xAB48, WORD_LEN, 0}, 	// MCU_ADDRESS [HG_GAMMA_TABLE_A_12]
    {0x0990, 0x00DC, WORD_LEN, 0}, 	// MCU_DATA_0
    {0x098C, 0xAB49, WORD_LEN, 0}, 	// MCU_ADDRESS [HG_GAMMA_TABLE_A_13]
    {0x0990, 0x00E4, WORD_LEN, 0}, 	// MCU_DATA_0
    {0x098C, 0xAB4A, WORD_LEN, 0}, 	// MCU_ADDRESS [HG_GAMMA_TABLE_A_14]
    {0x0990, 0x00EA, WORD_LEN, 0}, 	// MCU_DATA_0
    {0x098C, 0xAB4B, WORD_LEN, 0}, 	// MCU_ADDRESS [HG_GAMMA_TABLE_A_15]
    {0x0990, 0x00F0, WORD_LEN, 0}, 	// MCU_DATA_0
    {0x098C, 0xAB4C, WORD_LEN, 0}, 	// MCU_ADDRESS [HG_GAMMA_TABLE_A_16]
    {0x0990, 0x00F5, WORD_LEN, 0}, 	// MCU_DATA_0
    {0x098C, 0xAB4D, WORD_LEN, 0}, 	// MCU_ADDRESS [HG_GAMMA_TABLE_A_17]
    {0x0990, 0x00FA, WORD_LEN, 0}, 	// MCU_DATA_0
    {0x098C, 0xAB4E, WORD_LEN, 0}, 	// MCU_ADDRESS [HG_GAMMA_TABLE_A_18]
    {0x0990, 0x00FF, WORD_LEN, 0}, 	// MCU_DATA_0
    {0x098C, 0xAB4F, WORD_LEN, 0}, 	// MCU_ADDRESS [HG_GAMMA_TABLE_B_0]
    {0x0990, 0x0000, WORD_LEN, 0}, 	// MCU_DATA_0
    {0x098C, 0xAB50, WORD_LEN, 0}, 	// MCU_ADDRESS [HG_GAMMA_TABLE_B_1]
    {0x0990, 0x0003, WORD_LEN, 0}, 	// MCU_DATA_0
    {0x098C, 0xAB51, WORD_LEN, 0}, 	// MCU_ADDRESS [HG_GAMMA_TABLE_B_2]
    {0x0990, 0x000B, WORD_LEN, 0}, 	// MCU_DATA_0
    {0x098C, 0xAB52, WORD_LEN, 0}, 	// MCU_ADDRESS [HG_GAMMA_TABLE_B_3]
    {0x0990, 0x0024, WORD_LEN, 0}, 	// MCU_DATA_0
    {0x098C, 0xAB53, WORD_LEN, 0}, 	// MCU_ADDRESS [HG_GAMMA_TABLE_B_4]
    {0x0990, 0x0052, WORD_LEN, 0}, 	// MCU_DATA_0
    {0x098C, 0xAB54, WORD_LEN, 0}, 	// MCU_ADDRESS [HG_GAMMA_TABLE_B_5]
    {0x0990, 0x0073, WORD_LEN, 0}, 	// MCU_DATA_0
    {0x098C, 0xAB55, WORD_LEN, 0}, 	// MCU_ADDRESS [HG_GAMMA_TABLE_B_6]
    {0x0990, 0x008E, WORD_LEN, 0}, 	// MCU_DATA_0
    {0x098C, 0xAB56, WORD_LEN, 0}, 	// MCU_ADDRESS [HG_GAMMA_TABLE_B_7]
    {0x0990, 0x00A2, WORD_LEN, 0}, 	// MCU_DATA_0
    {0x098C, 0xAB57, WORD_LEN, 0}, 	// MCU_ADDRESS [HG_GAMMA_TABLE_B_8]
    {0x0990, 0x00B3, WORD_LEN, 0}, 	// MCU_DATA_0
    {0x098C, 0xAB58, WORD_LEN, 0}, 	// MCU_ADDRESS [HG_GAMMA_TABLE_B_9]
    {0x0990, 0x00C0, WORD_LEN, 0}, 	// MCU_DATA_0
    {0x098C, 0xAB59, WORD_LEN, 0}, 	// MCU_ADDRESS [HG_GAMMA_TABLE_B_10]
    {0x0990, 0x00CB, WORD_LEN, 0}, 	// MCU_DATA_0
    {0x098C, 0xAB5A, WORD_LEN, 0}, 	// MCU_ADDRESS [HG_GAMMA_TABLE_B_11]
    {0x0990, 0x00D4, WORD_LEN, 0}, 	// MCU_DATA_0
    {0x098C, 0xAB5B, WORD_LEN, 0}, 	// MCU_ADDRESS [HG_GAMMA_TABLE_B_12]
    {0x0990, 0x00DC, WORD_LEN, 0}, 	// MCU_DATA_0
    {0x098C, 0xAB5C, WORD_LEN, 0}, 	// MCU_ADDRESS [HG_GAMMA_TABLE_B_13]
    {0x0990, 0x00E4, WORD_LEN, 0}, 	// MCU_DATA_0
    {0x098C, 0xAB5D, WORD_LEN, 0}, 	// MCU_ADDRESS [HG_GAMMA_TABLE_B_14]
    {0x0990, 0x00EA, WORD_LEN, 0}, 	// MCU_DATA_0
    {0x098C, 0xAB5E, WORD_LEN, 0}, 	// MCU_ADDRESS [HG_GAMMA_TABLE_B_15]
    {0x0990, 0x00F0, WORD_LEN, 0}, 	// MCU_DATA_0
    {0x098C, 0xAB5F, WORD_LEN, 0}, 	// MCU_ADDRESS [HG_GAMMA_TABLE_B_16]
    {0x0990, 0x00F5, WORD_LEN, 0}, 	// MCU_DATA_0
    {0x098C, 0xAB60, WORD_LEN, 0}, 	// MCU_ADDRESS [HG_GAMMA_TABLE_B_17]
    {0x0990, 0x00FA, WORD_LEN, 0}, 	// MCU_DATA_0
    {0x098C, 0xAB61, WORD_LEN, 0}, 	// MCU_ADDRESS [HG_GAMMA_TABLE_B_18]
    {0x0990, 0x00FF, WORD_LEN, 0}, 	// MCU_DATA_0
};

static struct mt9d113_i2c_reg_conf const contrast_tbl_3[] = {
    {0x098C, 0xAB3C, WORD_LEN, 0}, 	// MCU_ADDRESS [HG_GAMMA_TABLE_A_0]
    {0x0990, 0x0000, WORD_LEN, 0}, 	// MCU_DATA_0
    {0x098C, 0xAB3D, WORD_LEN, 0}, 	// MCU_ADDRESS [HG_GAMMA_TABLE_A_1]
    {0x0990, 0x0002, WORD_LEN, 0}, 	// MCU_DATA_0
    {0x098C, 0xAB3E, WORD_LEN, 0}, 	// MCU_ADDRESS [HG_GAMMA_TABLE_A_2]
    {0x0990, 0x0008, WORD_LEN, 0}, 	// MCU_DATA_0
    {0x098C, 0xAB3F, WORD_LEN, 0}, 	// MCU_ADDRESS [HG_GAMMA_TABLE_A_3]
    {0x0990, 0x0018, WORD_LEN, 0}, 	// MCU_DATA_0
    {0x098C, 0xAB40, WORD_LEN, 0}, 	// MCU_ADDRESS [HG_GAMMA_TABLE_A_4]
    {0x0990, 0x003C, WORD_LEN, 0}, 	// MCU_DATA_0
    {0x098C, 0xAB41, WORD_LEN, 0}, 	// MCU_ADDRESS [HG_GAMMA_TABLE_A_5]
    {0x0990, 0x0057, WORD_LEN, 0}, 	// MCU_DATA_0
    {0x098C, 0xAB42, WORD_LEN, 0}, 	// MCU_ADDRESS [HG_GAMMA_TABLE_A_6]
    {0x0990, 0x0071, WORD_LEN, 0}, 	// MCU_DATA_0
    {0x098C, 0xAB43, WORD_LEN, 0}, 	// MCU_ADDRESS [HG_GAMMA_TABLE_A_7]
    {0x0990, 0x008A, WORD_LEN, 0}, 	// MCU_DATA_0
    {0x098C, 0xAB44, WORD_LEN, 0}, 	// MCU_ADDRESS [HG_GAMMA_TABLE_A_8]
    {0x0990, 0x009E, WORD_LEN, 0}, 	// MCU_DATA_0
    {0x098C, 0xAB45, WORD_LEN, 0}, 	// MCU_ADDRESS [HG_GAMMA_TABLE_A_9]
    {0x0990, 0x00AF, WORD_LEN, 0}, 	// MCU_DATA_0
    {0x098C, 0xAB46, WORD_LEN, 0}, 	// MCU_ADDRESS [HG_GAMMA_TABLE_A_10]
    {0x0990, 0x00BD, WORD_LEN, 0}, 	// MCU_DATA_0
    {0x098C, 0xAB47, WORD_LEN, 0}, 	// MCU_ADDRESS [HG_GAMMA_TABLE_A_11]
    {0x0990, 0x00C9, WORD_LEN, 0}, 	// MCU_DATA_0
    {0x098C, 0xAB48, WORD_LEN, 0}, 	// MCU_ADDRESS [HG_GAMMA_TABLE_A_12]
    {0x0990, 0x00D3, WORD_LEN, 0}, 	// MCU_DATA_0
    {0x098C, 0xAB49, WORD_LEN, 0}, 	// MCU_ADDRESS [HG_GAMMA_TABLE_A_13]
    {0x0990, 0x00DD, WORD_LEN, 0}, 	// MCU_DATA_0
    {0x098C, 0xAB4A, WORD_LEN, 0}, 	// MCU_ADDRESS [HG_GAMMA_TABLE_A_14]
    {0x0990, 0x00E5, WORD_LEN, 0}, 	// MCU_DATA_0
    {0x098C, 0xAB4B, WORD_LEN, 0}, 	// MCU_ADDRESS [HG_GAMMA_TABLE_A_15]
    {0x0990, 0x00EC, WORD_LEN, 0}, 	// MCU_DATA_0
    {0x098C, 0xAB4C, WORD_LEN, 0}, 	// MCU_ADDRESS [HG_GAMMA_TABLE_A_16]
    {0x0990, 0x00F3, WORD_LEN, 0}, 	// MCU_DATA_0
    {0x098C, 0xAB4D, WORD_LEN, 0}, 	// MCU_ADDRESS [HG_GAMMA_TABLE_A_17]
    {0x0990, 0x00F9, WORD_LEN, 0}, 	// MCU_DATA_0
    {0x098C, 0xAB4E, WORD_LEN, 0}, 	// MCU_ADDRESS [HG_GAMMA_TABLE_A_18]
    {0x0990, 0x00FF, WORD_LEN, 0}, 	// MCU_DATA_0
    {0x098C, 0xAB4F, WORD_LEN, 0}, 	// MCU_ADDRESS [HG_GAMMA_TABLE_B_0]
    {0x0990, 0x0000, WORD_LEN, 0}, 	// MCU_DATA_0
    {0x098C, 0xAB50, WORD_LEN, 0}, 	// MCU_ADDRESS [HG_GAMMA_TABLE_B_1]
    {0x0990, 0x0002, WORD_LEN, 0}, 	// MCU_DATA_0
    {0x098C, 0xAB51, WORD_LEN, 0}, 	// MCU_ADDRESS [HG_GAMMA_TABLE_B_2]
    {0x0990, 0x0008, WORD_LEN, 0}, 	// MCU_DATA_0
    {0x098C, 0xAB52, WORD_LEN, 0}, 	// MCU_ADDRESS [HG_GAMMA_TABLE_B_3]
    {0x0990, 0x0018, WORD_LEN, 0}, 	// MCU_DATA_0
    {0x098C, 0xAB53, WORD_LEN, 0}, 	// MCU_ADDRESS [HG_GAMMA_TABLE_B_4]
    {0x0990, 0x003C, WORD_LEN, 0}, 	// MCU_DATA_0
    {0x098C, 0xAB54, WORD_LEN, 0}, 	// MCU_ADDRESS [HG_GAMMA_TABLE_B_5]
    {0x0990, 0x0057, WORD_LEN, 0}, 	// MCU_DATA_0
    {0x098C, 0xAB55, WORD_LEN, 0}, 	// MCU_ADDRESS [HG_GAMMA_TABLE_B_6]
    {0x0990, 0x0071, WORD_LEN, 0}, 	// MCU_DATA_0
    {0x098C, 0xAB56, WORD_LEN, 0}, 	// MCU_ADDRESS [HG_GAMMA_TABLE_B_7]
    {0x0990, 0x008A, WORD_LEN, 0}, 	// MCU_DATA_0
    {0x098C, 0xAB57, WORD_LEN, 0}, 	// MCU_ADDRESS [HG_GAMMA_TABLE_B_8]
    {0x0990, 0x009E, WORD_LEN, 0}, 	// MCU_DATA_0
    {0x098C, 0xAB58, WORD_LEN, 0}, 	// MCU_ADDRESS [HG_GAMMA_TABLE_B_9]
    {0x0990, 0x00AF, WORD_LEN, 0}, 	// MCU_DATA_0
    {0x098C, 0xAB59, WORD_LEN, 0}, 	// MCU_ADDRESS [HG_GAMMA_TABLE_B_10]
    {0x0990, 0x00BD, WORD_LEN, 0}, 	// MCU_DATA_0
    {0x098C, 0xAB5A, WORD_LEN, 0}, 	// MCU_ADDRESS [HG_GAMMA_TABLE_B_11]
    {0x0990, 0x00C9, WORD_LEN, 0}, 	// MCU_DATA_0
    {0x098C, 0xAB5B, WORD_LEN, 0}, 	// MCU_ADDRESS [HG_GAMMA_TABLE_B_12]
    {0x0990, 0x00D3, WORD_LEN, 0}, 	// MCU_DATA_0
    {0x098C, 0xAB5C, WORD_LEN, 0}, 	// MCU_ADDRESS [HG_GAMMA_TABLE_B_13]
    {0x0990, 0x00DD, WORD_LEN, 0}, 	// MCU_DATA_0
    {0x098C, 0xAB5D, WORD_LEN, 0}, 	// MCU_ADDRESS [HG_GAMMA_TABLE_B_14]
    {0x0990, 0x00E5, WORD_LEN, 0}, 	// MCU_DATA_0
    {0x098C, 0xAB5E, WORD_LEN, 0}, 	// MCU_ADDRESS [HG_GAMMA_TABLE_B_15]
    {0x0990, 0x00EC, WORD_LEN, 0}, 	// MCU_DATA_0
    {0x098C, 0xAB5F, WORD_LEN, 0}, 	// MCU_ADDRESS [HG_GAMMA_TABLE_B_16]
    {0x0990, 0x00F3, WORD_LEN, 0}, 	// MCU_DATA_0
    {0x098C, 0xAB60, WORD_LEN, 0}, 	// MCU_ADDRESS [HG_GAMMA_TABLE_B_17]
    {0x0990, 0x00F9, WORD_LEN, 0}, 	// MCU_DATA_0
    {0x098C, 0xAB61, WORD_LEN, 0}, 	// MCU_ADDRESS [HG_GAMMA_TABLE_B_18]
    {0x0990, 0x00FF, WORD_LEN, 0}, 	// MCU_DATA_0
};

static struct mt9d113_i2c_reg_conf const contrast_tbl_4[] = {
    {0x098C, 0xAB3C, WORD_LEN, 0}, 	// MCU_ADDRESS [HG_GAMMA_TABLE_A_0]
    {0x0990, 0x0000, WORD_LEN, 0}, 	// MCU_DATA_0
    {0x098C, 0xAB3D, WORD_LEN, 0}, 	// MCU_ADDRESS [HG_GAMMA_TABLE_A_1]
    {0x0990, 0x0002, WORD_LEN, 0}, 	// MCU_DATA_0
    {0x098C, 0xAB3E, WORD_LEN, 0}, 	// MCU_ADDRESS [HG_GAMMA_TABLE_A_2]
    {0x0990, 0x0005, WORD_LEN, 0}, 	// MCU_DATA_0
    {0x098C, 0xAB3F, WORD_LEN, 0}, 	// MCU_ADDRESS [HG_GAMMA_TABLE_A_3]
    {0x0990, 0x0010, WORD_LEN, 0}, 	// MCU_DATA_0
    {0x098C, 0xAB40, WORD_LEN, 0}, 	// MCU_ADDRESS [HG_GAMMA_TABLE_A_4]
    {0x0990, 0x002A, WORD_LEN, 0}, 	// MCU_DATA_0
    {0x098C, 0xAB41, WORD_LEN, 0}, 	// MCU_ADDRESS [HG_GAMMA_TABLE_A_5]
    {0x0990, 0x0042, WORD_LEN, 0}, 	// MCU_DATA_0
    {0x098C, 0xAB42, WORD_LEN, 0}, 	// MCU_ADDRESS [HG_GAMMA_TABLE_A_6]
    {0x0990, 0x0059, WORD_LEN, 0}, 	// MCU_DATA_0
    {0x098C, 0xAB43, WORD_LEN, 0}, 	// MCU_ADDRESS [HG_GAMMA_TABLE_A_7]
    {0x0990, 0x0072, WORD_LEN, 0}, 	// MCU_DATA_0
    {0x098C, 0xAB44, WORD_LEN, 0}, 	// MCU_ADDRESS [HG_GAMMA_TABLE_A_8]
    {0x0990, 0x008A, WORD_LEN, 0}, 	// MCU_DATA_0
    {0x098C, 0xAB45, WORD_LEN, 0}, 	// MCU_ADDRESS [HG_GAMMA_TABLE_A_9]
    {0x0990, 0x009F, WORD_LEN, 0}, 	// MCU_DATA_0
    {0x098C, 0xAB46, WORD_LEN, 0}, 	// MCU_ADDRESS [HG_GAMMA_TABLE_A_10]
    {0x0990, 0x00B1, WORD_LEN, 0}, 	// MCU_DATA_0
    {0x098C, 0xAB47, WORD_LEN, 0}, 	// MCU_ADDRESS [HG_GAMMA_TABLE_A_11]
    {0x0990, 0x00C0, WORD_LEN, 0}, 	// MCU_DATA_0
    {0x098C, 0xAB48, WORD_LEN, 0}, 	// MCU_ADDRESS [HG_GAMMA_TABLE_A_12]
    {0x0990, 0x00CD, WORD_LEN, 0}, 	// MCU_DATA_0
    {0x098C, 0xAB49, WORD_LEN, 0}, 	// MCU_ADDRESS [HG_GAMMA_TABLE_A_13]
    {0x0990, 0x00D8, WORD_LEN, 0}, 	// MCU_DATA_0
    {0x098C, 0xAB4A, WORD_LEN, 0}, 	// MCU_ADDRESS [HG_GAMMA_TABLE_A_14]
    {0x0990, 0x00E1, WORD_LEN, 0}, 	// MCU_DATA_0
    {0x098C, 0xAB4B, WORD_LEN, 0}, 	// MCU_ADDRESS [HG_GAMMA_TABLE_A_15]
    {0x0990, 0x00EA, WORD_LEN, 0}, 	// MCU_DATA_0
    {0x098C, 0xAB4C, WORD_LEN, 0}, 	// MCU_ADDRESS [HG_GAMMA_TABLE_A_16]
    {0x0990, 0x00F1, WORD_LEN, 0}, 	// MCU_DATA_0
    {0x098C, 0xAB4D, WORD_LEN, 0}, 	// MCU_ADDRESS [HG_GAMMA_TABLE_A_17]
    {0x0990, 0x00F9, WORD_LEN, 0}, 	// MCU_DATA_0
    {0x098C, 0xAB4E, WORD_LEN, 0}, 	// MCU_ADDRESS [HG_GAMMA_TABLE_A_18]
    {0x0990, 0x00FF, WORD_LEN, 0}, 	// MCU_DATA_0
    {0x098C, 0xAB4F, WORD_LEN, 0}, 	// MCU_ADDRESS [HG_GAMMA_TABLE_B_0]
    {0x0990, 0x0000, WORD_LEN, 0}, 	// MCU_DATA_0
    {0x098C, 0xAB50, WORD_LEN, 0}, 	// MCU_ADDRESS [HG_GAMMA_TABLE_B_1]
    {0x0990, 0x0002, WORD_LEN, 0}, 	// MCU_DATA_0
    {0x098C, 0xAB51, WORD_LEN, 0}, 	// MCU_ADDRESS [HG_GAMMA_TABLE_B_2]
    {0x0990, 0x0005, WORD_LEN, 0}, 	// MCU_DATA_0
    {0x098C, 0xAB52, WORD_LEN, 0}, 	// MCU_ADDRESS [HG_GAMMA_TABLE_B_3]
    {0x0990, 0x0010, WORD_LEN, 0}, 	// MCU_DATA_0
    {0x098C, 0xAB53, WORD_LEN, 0}, 	// MCU_ADDRESS [HG_GAMMA_TABLE_B_4]
    {0x0990, 0x002A, WORD_LEN, 0}, 	// MCU_DATA_0
    {0x098C, 0xAB54, WORD_LEN, 0}, 	// MCU_ADDRESS [HG_GAMMA_TABLE_B_5]
    {0x0990, 0x0042, WORD_LEN, 0}, 	// MCU_DATA_0
    {0x098C, 0xAB55, WORD_LEN, 0}, 	// MCU_ADDRESS [HG_GAMMA_TABLE_B_6]
    {0x0990, 0x0059, WORD_LEN, 0}, 	// MCU_DATA_0
    {0x098C, 0xAB56, WORD_LEN, 0}, 	// MCU_ADDRESS [HG_GAMMA_TABLE_B_7]
    {0x0990, 0x0072, WORD_LEN, 0}, 	// MCU_DATA_0
    {0x098C, 0xAB57, WORD_LEN, 0}, 	// MCU_ADDRESS [HG_GAMMA_TABLE_B_8]
    {0x0990, 0x008A, WORD_LEN, 0}, 	// MCU_DATA_0
    {0x098C, 0xAB58, WORD_LEN, 0}, 	// MCU_ADDRESS [HG_GAMMA_TABLE_B_9]
    {0x0990, 0x009F, WORD_LEN, 0}, 	// MCU_DATA_0
    {0x098C, 0xAB59, WORD_LEN, 0}, 	// MCU_ADDRESS [HG_GAMMA_TABLE_B_10]
    {0x0990, 0x00B1, WORD_LEN, 0}, 	// MCU_DATA_0
    {0x098C, 0xAB5A, WORD_LEN, 0}, 	// MCU_ADDRESS [HG_GAMMA_TABLE_B_11]
    {0x0990, 0x00C0, WORD_LEN, 0}, 	// MCU_DATA_0
    {0x098C, 0xAB5B, WORD_LEN, 0}, 	// MCU_ADDRESS [HG_GAMMA_TABLE_B_12]
    {0x0990, 0x00CD, WORD_LEN, 0}, 	// MCU_DATA_0
    {0x098C, 0xAB5C, WORD_LEN, 0}, 	// MCU_ADDRESS [HG_GAMMA_TABLE_B_13]
    {0x0990, 0x00D8, WORD_LEN, 0}, 	// MCU_DATA_0
    {0x098C, 0xAB5D, WORD_LEN, 0}, 	// MCU_ADDRESS [HG_GAMMA_TABLE_B_14]
    {0x0990, 0x00E1, WORD_LEN, 0}, 	// MCU_DATA_0
    {0x098C, 0xAB5E, WORD_LEN, 0}, 	// MCU_ADDRESS [HG_GAMMA_TABLE_B_15]
    {0x0990, 0x00EA, WORD_LEN, 0}, 	// MCU_DATA_0
    {0x098C, 0xAB5F, WORD_LEN, 0}, 	// MCU_ADDRESS [HG_GAMMA_TABLE_B_16]
    {0x0990, 0x00F1, WORD_LEN, 0}, 	// MCU_DATA_0
    {0x098C, 0xAB60, WORD_LEN, 0}, 	// MCU_ADDRESS [HG_GAMMA_TABLE_B_17]
    {0x0990, 0x00F9, WORD_LEN, 0}, 	// MCU_DATA_0
    {0x098C, 0xAB61, WORD_LEN, 0}, 	// MCU_ADDRESS [HG_GAMMA_TABLE_B_18]
    {0x0990, 0x00FF, WORD_LEN, 0}, 	// MCU_DATA_0
};

static struct mt9d113_i2c_reg_conf const *contrast_tbl[] = {
    contrast_tbl_0,
    contrast_tbl_1,
    contrast_tbl_2,
    contrast_tbl_3,
    contrast_tbl_4,
};

static uint16_t const contrast_tbl_sz[] = {
    ARRAY_SIZE(contrast_tbl_0),
    ARRAY_SIZE(contrast_tbl_1),
    ARRAY_SIZE(contrast_tbl_2),
    ARRAY_SIZE(contrast_tbl_3),
    ARRAY_SIZE(contrast_tbl_4),
};

static struct mt9d113_i2c_reg_conf const brightness_tbl_0[] = {
    {0x098C, 0xA24F, WORD_LEN, 0}, 	// MCU_ADDRESS [AE_BASETARGET]
    {0x0990, 0x0012, WORD_LEN, 0}, 	// MCU_DATA_0
};

static struct mt9d113_i2c_reg_conf const brightness_tbl_1[] = {
    {0x098C, 0xA24F, WORD_LEN, 0}, 	// MCU_ADDRESS [AE_BASETARGET]
    {0x0990, 0x0022, WORD_LEN, 0}, 	// MCU_DATA_0
};

static struct mt9d113_i2c_reg_conf const brightness_tbl_2[] = {
    {0x098C, 0xA24F, WORD_LEN, 0}, 	// MCU_ADDRESS [AE_BASETARGET]
    {0x0990, 0x002A, WORD_LEN, 0}, 	// MCU_DATA_0
};

static struct mt9d113_i2c_reg_conf const brightness_tbl_3[] = {
    {0x098C, 0xA24F, WORD_LEN, 0}, 	// MCU_ADDRESS [AE_BASETARGET]
    {0x0990, 0x0038, WORD_LEN, 0}, 	// MCU_DATA_0

};

static struct mt9d113_i2c_reg_conf const brightness_tbl_4[] = {
    {0x098C, 0xA24F, WORD_LEN, 0}, 	// MCU_ADDRESS [AE_BASETARGET]
    {0x0990, 0x004F, WORD_LEN, 0}, 	// MCU_DATA_0
};

static struct mt9d113_i2c_reg_conf const brightness_tbl_5[] = {
    {0x098C, 0xA24F, WORD_LEN, 0}, 	// MCU_ADDRESS [AE_BASETARGET]
    {0x0990, 0x0054, WORD_LEN, 0}, 	// MCU_DATA_0
};

static struct mt9d113_i2c_reg_conf const brightness_tbl_6[] = {
    {0x098C, 0xA24F, WORD_LEN, 0}, 	// MCU_ADDRESS [AE_BASETARGET]
    {0x0990, 0x006F, WORD_LEN, 0}, 	// MCU_DATA_0
};

static struct mt9d113_i2c_reg_conf const *brightness_tbl[] = {
    brightness_tbl_0,
    brightness_tbl_1,
    brightness_tbl_2,
    brightness_tbl_3,
    brightness_tbl_4,
    brightness_tbl_5,
    brightness_tbl_6,
};

static uint16_t const brightness_tbl_sz[] = {
    ARRAY_SIZE(brightness_tbl_0),
    ARRAY_SIZE(brightness_tbl_1),
    ARRAY_SIZE(brightness_tbl_2),
    ARRAY_SIZE(brightness_tbl_3),
    ARRAY_SIZE(brightness_tbl_4),
    ARRAY_SIZE(brightness_tbl_5),
    ARRAY_SIZE(brightness_tbl_6),
};

static struct mt9d113_i2c_reg_conf const saturation_tbl_0[] = {
    {0x098C, 0xAB20, WORD_LEN, 0}, 	// MCU_ADDRESS [HG_LL_SAT1]
    {0x0990, 0x0020, WORD_LEN, 0}, 	// MCU_DATA_0
    {0x098C, 0xAB24, WORD_LEN, 0}, 	// MCU_ADDRESS [HG_LL_SAT1]
    {0x0990, 0x0000, WORD_LEN, 0}, 	// MCU_DATA_0
    {0x098C, 0xA103, WORD_LEN, 0}, 	// MCU_ADDRESS [HG_LL_SAT1]
    {0x0990, 0x0005, WORD_LEN, 0}, 	// MCU_DATA_0
};

static struct mt9d113_i2c_reg_conf const saturation_tbl_1[] = {
    {0x098C, 0xAB20, WORD_LEN, 0}, 	// MCU_ADDRESS [HG_LL_SAT1]
    {0x0990, 0x003A, WORD_LEN, 0}, 	// MCU_DATA_0
    {0x098C, 0xAB24, WORD_LEN, 0}, 	// MCU_ADDRESS [HG_LL_SAT1]
    {0x0990, 0x0000, WORD_LEN, 0}, 	// MCU_DATA_0
    {0x098C, 0xA103, WORD_LEN, 0}, 	// MCU_ADDRESS [HG_LL_SAT1]
    {0x0990, 0x0005, WORD_LEN, 0}, 	// MCU_DATA_0
};

static struct mt9d113_i2c_reg_conf const saturation_tbl_2[] = {
    {0x098C, 0xAB20, WORD_LEN, 0}, 	// MCU_ADDRESS [HG_LL_SAT1]
    {0x0990, 0x004B, WORD_LEN, 0}, 	// MCU_DATA_0
    {0x098C, 0xAB24, WORD_LEN, 0}, 	// MCU_ADDRESS [HG_LL_SAT1]
    {0x0990, 0x0000, WORD_LEN, 0}, 	// MCU_DATA_0
    {0x098C, 0xA103, WORD_LEN, 0}, 	// MCU_ADDRESS [HG_LL_SAT1]
    {0x0990, 0x0005, WORD_LEN, 0}, 	// MCU_DATA_0
};

static struct mt9d113_i2c_reg_conf const saturation_tbl_3[] = {
    {0x098C, 0xAB20, WORD_LEN, 0}, 	// MCU_ADDRESS [HG_LL_SAT1]
    {0x0990, 0x0060, WORD_LEN, 0}, 	// MCU_DATA_0
    {0x098C, 0xAB24, WORD_LEN, 0}, 	// MCU_ADDRESS [HG_LL_SAT1]
    {0x0990, 0x0020, WORD_LEN, 0}, 	// MCU_DATA_0
    {0x098C, 0xA103, WORD_LEN, 0}, 	// MCU_ADDRESS [HG_LL_SAT1]
    {0x0990, 0x0005, WORD_LEN, 0}, 	// MCU_DATA_0
};

static struct mt9d113_i2c_reg_conf const saturation_tbl_4[] = {
    {0x098C, 0xAB20, WORD_LEN, 0}, 	// MCU_ADDRESS [HG_LL_SAT1]
    {0x0990, 0x007F, WORD_LEN, 0}, 	// MCU_DATA_0
    {0x098C, 0xAB24, WORD_LEN, 0}, 	// MCU_ADDRESS [HG_LL_SAT1]
    {0x0990, 0x0040, WORD_LEN, 0}, 	// MCU_DATA_0
    {0x098C, 0xA103, WORD_LEN, 0}, 	// MCU_ADDRESS [HG_LL_SAT1]
    {0x0990, 0x0005, WORD_LEN, 0}, 	// MCU_DATA_0
};

static struct mt9d113_i2c_reg_conf const *saturation_tbl[] = {
    saturation_tbl_0,
    saturation_tbl_1,
    saturation_tbl_2,
    saturation_tbl_3,
    saturation_tbl_4,
};

static uint16_t const saturation_tbl_sz[] = {
    ARRAY_SIZE(saturation_tbl_0),
    ARRAY_SIZE(saturation_tbl_1),
    ARRAY_SIZE(saturation_tbl_2),
    ARRAY_SIZE(saturation_tbl_3),
    ARRAY_SIZE(saturation_tbl_4),
};

static struct mt9d113_i2c_reg_conf const sharpness_tbl_0[] = {
    {0x098C, 0xAB22, WORD_LEN, 0}, 	// MCU_ADDRESS [HG_LL_APCORR1]
    {0x0990, 0x0000, WORD_LEN, 0}, 	// MCU_DATA_0
};

static struct mt9d113_i2c_reg_conf const sharpness_tbl_1[] = {
    {0x098C, 0xAB22, WORD_LEN, 0}, 	// MCU_ADDRESS [HG_LL_APCORR1]
    {0x0990, 0x0002, WORD_LEN, 0}, 	// MCU_DATA_0
};

static struct mt9d113_i2c_reg_conf const sharpness_tbl_2[] = {    
    {0x098C, 0xAB22, WORD_LEN, 0}, 	// MCU_ADDRESS [HG_LL_APCORR1]
    {0x0990, 0x0003, WORD_LEN, 0}, 	// MCU_DATA_0
};

static struct mt9d113_i2c_reg_conf const sharpness_tbl_3[] = {
    {0x098C, 0xAB22, WORD_LEN, 0}, 	// MCU_ADDRESS [HG_LL_APCORR1]
    {0x0990, 0x0004, WORD_LEN, 0}, 	// MCU_DATA_0
};

static struct mt9d113_i2c_reg_conf const sharpness_tbl_4[] = {
    {0x098C, 0xAB22, WORD_LEN, 0}, 	// MCU_ADDRESS [HG_LL_APCORR1]
    {0x0990, 0x0007, WORD_LEN, 0}, 	// MCU_DATA_0
};

static struct mt9d113_i2c_reg_conf const *sharpness_tbl[] = {
    sharpness_tbl_0,
    sharpness_tbl_1,
    sharpness_tbl_2,
    sharpness_tbl_3,
    sharpness_tbl_4,
};

static uint16_t const sharpness_tbl_sz[] = {
    ARRAY_SIZE(sharpness_tbl_0),
    ARRAY_SIZE(sharpness_tbl_1),
    ARRAY_SIZE(sharpness_tbl_2),
    ARRAY_SIZE(sharpness_tbl_3),
    ARRAY_SIZE(sharpness_tbl_4),
};

struct mt9d113_reg_t mt9d113_regs = {
    .pll_tbl                = pll_tbl,
    .pll_tbl_sz             = ARRAY_SIZE(pll_tbl),

    .clk_tbl                = clk_tbl,
    .clk_tbl_sz             = ARRAY_SIZE(clk_tbl),

    .prevsnap_tbl           = prev_snap_tbl,
    .prevsnap_tbl_sz        = ARRAY_SIZE(prev_snap_tbl),

    .wb_cloudy_tbl          = wb_cloudy_tbl,
    .wb_cloudy_tbl_sz       = ARRAY_SIZE(wb_cloudy_tbl),

    .wb_daylight_tbl        = wb_daylight_tbl,
    .wb_daylight_tbl_sz     = ARRAY_SIZE(wb_daylight_tbl),

    .wb_flourescant_tbl     = wb_flourescant_tbl,
    .wb_flourescant_tbl_sz  = ARRAY_SIZE(wb_flourescant_tbl),

    .wb_incandescent_tbl    = wb_incandescent_tbl,
    .wb_incandescent_tbl_sz = ARRAY_SIZE(wb_incandescent_tbl),

    .wb_auto_tbl            = wb_auto_tbl,
    .wb_auto_tbl_sz         = ARRAY_SIZE(wb_auto_tbl),

    .contrast_tbl           = contrast_tbl,
    .contrast_tbl_sz        = contrast_tbl_sz,

    .brightness_tbl         = brightness_tbl,
    .brightness_tbl_sz      = brightness_tbl_sz,

    .saturation_tbl         = saturation_tbl,
    .saturation_tbl_sz      = saturation_tbl_sz,

    .sharpness_tbl          = sharpness_tbl,
    .sharpness_tbl_sz       = sharpness_tbl_sz,
};
