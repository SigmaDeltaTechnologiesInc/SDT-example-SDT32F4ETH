#if 0 // H/W ver01
/* mbed Microcontroller Library
 * Copyright (c) 2019 ARM Limited
 * SPDX-License-Identifier: Apache-2.0
 */

#include "mbed.h"
#include "I2S.h"

#define SAMPLE_RATE 8000 // 44100
//#define USE_MAKE_SINE_WAVE

#if (SAMPLE_RATE == 44100)

#ifndef USE_MAKE_SINE_WAVE
#include "bell_stereo.pcm.h"
#endif

#elif (SAMPLE_RATE == 8000)

#ifndef USE_MAKE_SINE_WAVE
//#include "bell_stereo_8k.pcm.h"
//#include "bell_stereo_8k_vol_4x.pcm.h"
//#include "bell_stereo_8k_vol_2x.pcm.h"
#include "ko_hello.pcm.h"
#include "ko_kick_44100.pcm.h"
#endif

#endif

#define AK4954_REG_PM1 (0x00)
#define AK4954_REG_PM2 (0x01)
#define AK4954_REG_SIG_SEL_1 (0x02)
#define AK4954_REG_SIG_SEL_2 (0x03)
#define AK4954_REG_SIG_SEL_3 (0x04)
#define AK4954_REG_MODE_CTRL_1 (0x05)
#define AK4954_REG_MODE_CTRL_2 (0x06)
#define AK4954_REG_MODE_CTRL_3 (0x07)
#define AK4954_REG_DIG_MIC (0x08)
#define AK4954_REG_TIMER_SEL (0x09)
#define AK4954_REG_ALC_TIMER_SEL (0x0A)
#define AK4954_REG_ALC_MODE_CTRL_1 (0x0B)
#define AK4954_REG_ALC_MODE_CTRL_2 (0x0C)
#define AK4954_REG_IVL_CTRL (0x0D)
#define AK4954_REG_IVR_CTRL (0x0E)
#define AK4954_REG_RESERVED_1 (0x0F)
#define AK4954_REG_RESERVED_2 (0x10)
#define AK4954_REG_RESERVED_3 (0x11)
#define AK4954_REG_HP_OUT_CTRL (0x12)
#define AK4954_REG_DVL_CTRL (0x13)
#define AK4954_REG_DVR_CTRL (0x14)
#define AK4954_REG_BEEP_FREQ (0x15)
#define AK4954_REG_BEEP_ON_TIME (0x16)
#define AK4954_REG_BEEP_OFF_TIME (0x17)
#define AK4954_REG_BEEP_REPEAT_CNT (0x18)
#define AK4954_REG_BEEP_VOL_CTRL (0x19)
#define AK4954_REG_RESERVED_4 (0x1A)
#define AK4954_REG_DIG_FILTER_SEL_1 (0x1B)
#define AK4954_REG_DIG_FILTER_SEL_2 (0x1C)
#define AK4954_REG_DIG_FILTER_MODE (0x1D)
#define AK4954_REG_HPF2_COEF_0 (0x1E)
#define AK4954_REG_HPF2_COEF_1 (0x1F)
#define AK4954_REG_HPF2_COEF_2 (0x20)
#define AK4954_REG_HPF2_COEF_3 (0x21)
#define AK4954_REG_LPF_COEF_0 (0x22)
#define AK4954_REG_LPF_COEF_1 (0x23)
#define AK4954_REG_LPF_COEF_2 (0x24)
#define AK4954_REG_LPF_COEF_3 (0x25)
#define AK4954_REG_FIL3_COEF_0 (0x26)
#define AK4954_REG_FIL3_COEF_1 (0x27)
#define AK4954_REG_FIL3_COEF_2 (0x28)
#define AK4954_REG_FIL3_COEF_3 (0x29)
#define AK4954_REG_EQ_COEF_0 (0x2A)
#define AK4954_REG_EQ_COEF_1 (0x2B)
#define AK4954_REG_EQ_COEF_2 (0x2C)
#define AK4954_REG_EQ_COEF_3 (0x2D)
#define AK4954_REG_EQ_COEF_4 (0x2E)
#define AK4954_REG_EQ_COEF_5 (0x2F)
#define AK4954_REG_DIG_FILTER_SEL_3 (0x30)
#define AK4954_REG_RESERVED_5 (0x31)
#define AK4954_REG_E1_COEF_0 (0x32)
#define AK4954_REG_E1_COEF_1 (0x33)
#define AK4954_REG_E1_COEF_2 (0x34)
#define AK4954_REG_E1_COEF_3 (0x35)
#define AK4954_REG_E1_COEF_4 (0x36)
#define AK4954_REG_E1_COEF_5 (0x37)
#define AK4954_REG_E2_COEF_0 (0x38)
#define AK4954_REG_E2_COEF_1 (0x39)
#define AK4954_REG_E2_COEF_2 (0x3A)
#define AK4954_REG_E2_COEF_3 (0x3B)
#define AK4954_REG_E2_COEF_4 (0x3C)
#define AK4954_REG_E2_COEF_5 (0x3D)
#define AK4954_REG_E3_COEF_0 (0x3E)
#define AK4954_REG_E3_COEF_1 (0x3F)
#define AK4954_REG_E3_COEF_2 (0x40)
#define AK4954_REG_E3_COEF_3 (0x41)
#define AK4954_REG_E3_COEF_4 (0x42)
#define AK4954_REG_E3_COEF_5 (0x43)
#define AK4954_REG_E4_COEF_0 (0x44)
#define AK4954_REG_E4_COEF_1 (0x45)
#define AK4954_REG_E4_COEF_2 (0x46)
#define AK4954_REG_E4_COEF_3 (0x47)
#define AK4954_REG_E4_COEF_4 (0x48)
#define AK4954_REG_E4_COEF_5 (0x49)
#define AK4954_REG_E5_COEF_0 (0x4A)
#define AK4954_REG_E5_COEF_1 (0x4B)
#define AK4954_REG_E5_COEF_2 (0x4C)
#define AK4954_REG_E5_COEF_3 (0x4D)
#define AK4954_REG_E5_COEF_4 (0x4E)
#define AK4954_REG_E5_COEF_5 (0x4F)
#define AK4954_REG_DRC_MODE_CTRL (0x50)
#define AK4954_REG_NS_CTRL (0x51)
#define AK4954_REG_NS_GAIN_ATT_CTRL (0x52)
#define AK4954_REG_NS_ON_LVL (0x53)
#define AK4954_REG_NS_OFF_LVL (0x54)
#define AK4954_REG_NS_REF_SEL (0x55)
#define AK4954_REG_NS_LPF_COEF_0 (0x56)
#define AK4954_REG_NS_LPF_COEF_1 (0x57)
#define AK4954_REG_NS_LPF_COEF_2 (0x58)
#define AK4954_REG_NS_LPF_COEF_3 (0x59)
#define AK4954_REG_NS_HPF_COEF_0 (0x5A)
#define AK4954_REG_NS_HPF_COEF_1 (0x5B)
#define AK4954_REG_NS_HPF_COEF_2 (0x5C)
#define AK4954_REG_NS_HPF_COEF_3 (0x5D)
#define AK4954_REG_RESERVED_6 (0x5E)
#define AK4954_REG_RESERVED_7 (0x5F)
#define AK4954_REG_DVLC_FILTER_SEL (0x60)
#define AK4954_REG_DVLC_MODE_CTRL (0x61)
#define AK4954_REG_DVLCL_CURVE_X1 (0x62)
#define AK4954_REG_DVLCL_CURVE_Y1 (0x63)
#define AK4954_REG_DVLCL_CURVE_X2 (0x64)
#define AK4954_REG_DVLCL_CURVE_Y2 (0x65)
#define AK4954_REG_DVLCL_CURVE_X3 (0x66)
#define AK4954_REG_DVLCL_CURVE_Y3 (0x67)
#define AK4954_REG_DVLCL_SLOPE_1 (0x68)
#define AK4954_REG_DVLCL_SLOPE_2 (0x69)
#define AK4954_REG_DVLCL_SLOPE_3 (0x6A)
#define AK4954_REG_DVLCL_SLOPE_4 (0x6B)
#define AK4954_REG_DVLCM_CURVE_X1 (0x6C)
#define AK4954_REG_DVLCM_CURVE_Y1 (0x6D)
#define AK4954_REG_DVLCM_CURVE_X2 (0x6E)
#define AK4954_REG_DVLCM_CURVE_Y2 (0x6F)
#define AK4954_REG_DVLCM_CURVE_X3 (0x70)
#define AK4954_REG_DVLCM_CURVE_Y3 (0x71)
#define AK4954_REG_DVLCM_SLOPE_1 (0x72)
#define AK4954_REG_DVLCM_SLOPE_2 (0x73)
#define AK4954_REG_DVLCM_SLOPE_3 (0x74)
#define AK4954_REG_DVLCM_SLOPE_4 (0x75)
#define AK4954_REG_DVLCH_CURVE_X1 (0x76)
#define AK4954_REG_DVLCH_CURVE_Y1 (0x77)
#define AK4954_REG_DVLCH_CURVE_X2 (0x78)
#define AK4954_REG_DVLCH_CURVE_Y2 (0x79)
#define AK4954_REG_DVLCH_CURVE_X3 (0x7A)
#define AK4954_REG_DVLCH_CURVE_Y3 (0x7B)
#define AK4954_REG_DVLCH_SLOPE_1 (0x7C)
#define AK4954_REG_DVLCH_SLOPE_2 (0x7D)
#define AK4954_REG_DVLCH_SLOPE_3 (0x7E)
#define AK4954_REG_DVLCH_SLOPE_4 (0x7F)
#define AK4954_REG_DVLCL_LPF_COEF_0 (0x80)
#define AK4954_REG_DVLCL_LPF_COEF_1 (0x81)
#define AK4954_REG_DVLCL_LPF_COEF_2 (0x82)
#define AK4954_REG_DVLCL_LPF_COEF_3 (0x83)
#define AK4954_REG_DVLCM_HPF_COEF_0 (0x84)
#define AK4954_REG_DVLCM_HPF_COEF_1 (0x85)
#define AK4954_REG_DVLCM_HPF_COEF_2 (0x86)
#define AK4954_REG_DVLCM_HPF_COEF_3 (0x87)
#define AK4954_REG_DVLCM_LPF_COEF_0 (0x88)
#define AK4954_REG_DVLCM_LPF_COEF_1 (0x89)
#define AK4954_REG_DVLCM_LPF_COEF_2 (0x8A)
#define AK4954_REG_DVLCM_LPF_COEF_3 (0x8B)
#define AK4954_REG_DVLCH_HPF_COEF_0 (0x8C)
#define AK4954_REG_DVLCH_HPF_COEF_1 (0x8D)
#define AK4954_REG_DVLCH_HPF_COEF_2 (0x8E)
#define AK4954_REG_DVLCH_HPF_COEF_3 (0x8F)

/* 00H Power Management 1 */
#define AK4954_PMADL (0x01)
#define AK4954_PMADL_MASK (0x01)
#define AK4954_PMADL_SHIFT (0)
#define AK4954_PMADL_BITS (1)
#define AK4954_PMADR (0x02)
#define AK4954_PMADR_MASK (0x02)
#define AK4954_PMADR_SHIFT (1)
#define AK4954_PMADR_BITS (1)
#define AK4954_PMDAC (0x04)
#define AK4954_PMDAC_MASK (0x04)
#define AK4954_PMDAC_SHIFT (2)
#define AK4954_PMDAC_BITS (1)
#define AK4954_PMBP (0x20)
#define AK4954_PMBP_MASK (0x20)
#define AK4954_PMBP_SHIFT (5)
#define AK4954_PMBP_BITS (1)
#define AK4954_PMVCM (0x40)
#define AK4954_PMVCM_MASK (0x40)
#define AK4954_PMVCM_SHIFT (6)
#define AK4954_PMVCM_BITS (1)
#define AK4954_PMPFIL (0x80)
#define AK4954_PMPFIL_MASK (0x80)
#define AK4954_PMPFIL_SHIFT (7)
#define AK4954_PMPFIL_BITS (1)

/* 01H Power Management 2 */
#define AK4954_PMSL (0x2)
#define AK4954_PMSL_MASK (0x2)
#define AK4954_PMSL_SHIFT (1)
#define AK4954_PMPLL (0x04)
#define AK4954_PMPLL_MASK (0x04)
#define AK4954_PMPLL_SHIFT (2)
#define AK4954_PMPLL_BITS (1)
#define AK4954_MS (0x08)
#define AK4954_MS_MASK (0x08)
#define AK4954_MS_SHIFT (3)
#define AK4954_MS_BITS (1)
#define AK4954_PMHPL (0x10)
#define AK4954_PMHPL_MASK (0x10)
#define AK4954_PMHPL_SHIFT (4)
#define AK4954_PMHPR (0x20)
#define AK4954_PMHPR_MASK (0x20)
#define AK4954_PMHPR_SHIFT (5)

/* 02H Signal Select 1 */
#define AK4954_MGAIN_0DB (0x04)
#define AK4954_MGAIN_6DB (0x00)
#define AK4954_MGAIN_13DB (0x01)
#define AK4954_MGAIN_20DB (0x02)
#define AK4954_MGAIN_26DB (0x03)
#define AK4954_MGAIN_MASK (0x07)
#define AK4954_MGAIN_SHIFT (0)
#define AK4954_MGAIN_BITS (3)
#define AK4954_PMMP (0x08)
#define AK4954_PMMP_MASK (0x08)
#define AK4954_PMMP_SHIFT (3)
#define AK4954_PMMP_BITS (1)
#define AK4954_DACSL (0x20)
#define AK4954_DACSL_MASK (0x20)
#define AK4954_DACSL_SHIFT (5)
#define AK4954_DACSL_BITS (1)
#define AK4954_SLPSN (0x80)
#define AK4954_SLPSN_MASK (0x80)
#define AK4954_SLPSN_SHIFT (7)
#define AK4954_SLPSN_BITS (1)

/* 05H Mode Control 1 */
#define AK4954_DIF_MODE_0 (0x00)
#define AK4954_DIF_MODE_1 (0x01)
#define AK4954_DIF_MODE_2 (0x02)
#define AK4954_DIF_MODE_3 (0x03)
#define AK4954_DIF_MODE_4 (0x06)
#define AK4954_DIF_MODE_5 (0x07)
#define AK4954_DIF_MASK (0x07) /* [2:0] */
#define AK4954_DIF_SHIFT (0)
#define AK4954_DIF_BITS (3)
#define AK4954_BCKO_32FS (0x00)
#define AK4954_BCKO_64FS (0x08)
#define AK4954_BCKO_MASK (0x08)
#define AK4954_BCKO_SHIFT (3)
#define AK4954_BCKO_BITS (1)
#define AK4954_PLL_32FS (0x00)
#define AK4954_PLL_64FS (0x10)
#define AK4954_PLL_11P2896MHZ (0x20)
#define AK4954_PLL_12P288MHZ (0x30)
#define AK4954_PLL_12MHZ (0x40)
#define AK4954_PLL_24MHZ (0x50)
#define AK4954_PLL_13P5MHZ (0x60)
#define AK4954_PLL_27MHZ (0x70)
#define AK4954_PLL_MASK (0x70) /* [6:4] */
#define AK4954_PLL_SHIFT (4)
#define AK4954_PLL_BITS (3)

/* 06H Mode Control 2 */
#define AK4954_CM_256FS (0x00)
#define AK4954_CM_384FS (0x40)
#define AK4954_CM_512FS (0x80)
#define AK4954_CM_1024FS (0xC0)
#define AK4954_CM_MASK (0xC0)
#define AK4954_CM_SHIFT (6)
#define AK4954_CM_BITS (2)
#define AK4954_FS_8KHZ (0x00)
#define AK4954_FS_11P025KHZ (0x01)
#define AK4954_FS_12KHZ (0x02)
#define AK4954_FS_16KHZ (0x04)
#define AK4954_FS_22P05KHZ (0x05)
#define AK4954_FS_24KHZ (0x06)
#define AK4954_FS_32KHZ (0x08)
#define AK4954_FS_44P1KHZ (0x09)
#define AK4954_FS_48KHZ (0x0A)
#define AK4954_FS_64KHZ (0x0C)
#define AK4954_FS_88P2KHZ (0x0D)
#define AK4954_FS_96KHZ (0x0E)
#define AK4954_FS_MASK (0x0F) /* [3:0] */
#define AK4954_FS_SHIFT (0)
#define AK4954_FS_BITS (4)

/* 0BH ALC Mode Control 1 */
#define AK4954_ALC (0x20)
#define AK4954_ALC_MASK (0x20)
#define AK4954_ALC_SHIFT (5)
#define AK4954_ALC_BITS (1)

/* 0DH Lch Input Volume Control */
#define AK4954_IVL_MASK (0xFF)
#define AK4954_IVL_SHIFT (0)

/* 0EH Rch Input Volume Control */
#define AK4954_IVR_MASK (0xFF)
#define AK4954_IVR_SHIFT (0)

/* 13H Lch Digital Volume Control */
#define AK4954_DVL_MASK (0xFF)
#define AK4954_DVL_SHIFT (0)
#define AK4954_DVL_BITS (8)

/* 14H Rch Digital Volume Control */
#define AK4954_DVR_MASK (0xFF)
#define AK4954_DVR_SHIFT (0)
#define AK4954_DVR_BITS (8)

/* 1DH Digital Filter Mode */
#define AK4954_PFSDO (0x01)
#define AK4954_PFSDO_MASK (0x01)
#define AK4954_PFSDO_SHIFT (0)
#define AK4954_PFSDO_BITS (1)
#define AK4954_ADCPF (0x02)
#define AK4954_ADCPF_MASK (0x02)
#define AK4954_ADCPF_SHIFT (1)
#define AK4954_ADCPF_BITS (1)
#define AK4954_PFDAC_SDTI (0)
#define AK4954_PFDAC (0x04)
#define AK4954_PFDAC_MASK (0x04)
#define AK4954_PFDAC_SHIFT (2)
#define AK4954_PFDAC_BITS (1)
#define AK4954_PMDRC (0x80)
#define AK4954_PMDRC_MASK (0x80)
#define AK4954_PMDRC_SHIFT (7)
#define AK4954_PMDRC_BITS (1)

/* 0x0C is 0dB. */
#define AK4954_DVL_DEFAULT (0x0C)
//#define AK4954_DVL_DEFAULT                  (0x0C + 30)

/* From AK4954_Configuration_4_21_14.doc, AK4954 Full-duplex Audio Configuration. */
#define AK4954_MGAIN_DEFAULT (AK4954_MGAIN_20DB)

/* 0x91 is 0dB. */
#define AK4954_IVL_DEFAULT (0x91)

/* Input volume gain settings (Table 40). */
#define AK4954_IVL_GAIN_IN_DB_MIN (-52.5 + (5 * -0.375))
#define AK4954_IVL_GAIN_IN_DB_MAX (+36.0)
#define AK4954_IVL_GAIN_IN_DB_STEP (+0.375)

/* Output digital volume gain settings (Table 69). */
#define AK4954_DVL_GAIN_IN_DB_MIN (-65.5)
#define AK4954_DVL_GAIN_IN_DB_MAX (+6.0)
#define AK4954_DVL_GAIN_IN_DB_STEP (+0.5)

/* Rise-up time of the VCOM pin is 1.5ms (max)
 * See Control Sequence, Clock Set up.
 */
#define AK4954_PMVCM_RISE_UP_TIME_IN_MILLIS (2ms)

/* Pulse width for PDN reset. */
#define AK4954_RESET_HOLD_TIME_IN_MILLIS (1ms)

typedef struct ak4954_mcki_fs_map ak4954_mcki_fs_map_t;
typedef struct ak4954_fs_map ak4954_fs_map_t;
typedef struct ak4954_mcki_freq_map ak4954_mcki_freq_map_t;
typedef struct ak4954_dbl_range ak4954_dbl_range_t;

struct ak4954_mcki_fs_map
{
    uint32_t fs1, fs2;
    uint16_t mult;
    uint8_t cm;
};

struct ak4954_fs_map
{
    uint32_t fs;
    uint8_t mc2fs;
};

struct ak4954_mcki_freq_map
{
    uint32_t mcki;
    uint8_t pll;
    size_t sz;
    const uint32_t *fs;
};

struct ak4954_dbl_range
{
    double min;
    double max;
    double step;

    /* The range is inverted: descending from position 0. */
    bool inv;
};

static const ak4954_mcki_fs_map_t mcki_fs_map[] =
    {
        {8000, 96000, 256, AK4954_CM_256FS},
        {11025, 48000, 384, AK4954_CM_384FS},
        {11025, 48000, 512, AK4954_CM_512FS},
        {8000, 24000, 1024, AK4954_CM_1024FS},
};

static const ak4954_fs_map_t fs_map[] =
    {
        {8000, AK4954_FS_8KHZ},
        {11025, AK4954_FS_11P025KHZ},
        {12000, AK4954_FS_12KHZ},
        {16000, AK4954_FS_16KHZ},
        {22050, AK4954_FS_22P05KHZ},
        {24000, AK4954_FS_24KHZ},
        {32000, AK4954_FS_32KHZ},
        {44100, AK4954_FS_44P1KHZ},
        {48000, AK4954_FS_48KHZ},
        {64000, AK4954_FS_64KHZ},
        {88200, AK4954_FS_88P2KHZ},
        {96000, AK4954_FS_96KHZ},
};

static const uint32_t mcki_8[8] = {
    8000, 12000, 16000, 24000, 32000, 48000, 64000, 96000};
static const uint32_t mcki_12[12] = {
    8000, 12000, 16000, 24000, 32000, 48000, 64000, 96000, 11025, 22050, 44100, 88200};

/* Removed values that don't round. */
static const ak4954_mcki_freq_map_t mcki_freq_map[] =
    {
        {11289600, AK4954_PLL_11P2896MHZ, 12, mcki_12},
        {12288000, AK4954_PLL_12P288MHZ, 12, mcki_12},
        {12000000, AK4954_PLL_12MHZ, 8, mcki_8},
        {24000000, AK4954_PLL_24MHZ, 8, mcki_8},
        {13500000, AK4954_PLL_13P5MHZ, 0, 0},
        {27000000, AK4954_PLL_27MHZ, 0, 0},
};

const static ak4954_dbl_range_t ak4954_dbl_range_dvl =
    {
        .min = AK4954_DVL_GAIN_IN_DB_MIN,
        .max = AK4954_DVL_GAIN_IN_DB_MAX,
        .step = AK4954_DVL_GAIN_IN_DB_STEP,
        .inv = true,
};

I2C i2c(MBED_CONF_APP_AUDIO_I2C_SDA, MBED_CONF_APP_AUDIO_I2C_SCL);
// DigitalOut AUDIO_MPWR1(MBED_CONF_APP_GPIO13);
// DigitalOut AUDIO_MPWR2(MBED_CONF_APP_GPIO12);
DigitalOut AUDIO_CODEC_PDN(MBED_CONF_APP_AUDIO_CODEC_RST, 0);
DigitalOut AUDIO_AMP_CTRL(MBED_CONF_APP_AUDIO_AMP_MUTE, 0);
DigitalOut AUDIO_SPK_CTRL(MBED_CONF_APP_AUDIO_TPA_MUTE, 0);

#define AUDIO_STABLE_TIME_SEC 10s
#define SLAVE_ADDRESS (0x12 << 1)

static int ak4954_i2c_reg_write(uint8_t reg, uint8_t value)
{
    int result;
    struct i2c_ak4954_payload
    {
        uint8_t addr;
        uint8_t data;
    };
    struct i2c_ak4954_payload payload;

    payload.addr = reg;
    payload.data = value;

    result = i2c.write(SLAVE_ADDRESS, (char *)&payload, 2);
    printf("reg write(%02X, %02X) =>  %d\n", ((char *)&payload)[0], ((char *)&payload)[1], result);

    return result;
}

static int ak4954_i2c_reg_read(uint8_t reg, uint8_t *value)
{
    int result;
    static uint8_t msg[2];

    *value = 0;
    result = i2c.write(SLAVE_ADDRESS, (char *)&reg, 1);

    if (result == 0)
    {
        result = i2c.read(SLAVE_ADDRESS, (char *)value, 1);
    }

    printf("reg read(%2X) => %d\n", *value, result);

    return result;
}
static int ak4954_reg_write(uint8_t address, uint8_t reg_data)
{
    return ak4954_i2c_reg_write(address, reg_data);
}

static int ak4954_reg_read(uint8_t address, uint8_t *reg_data)
{
    return ak4954_i2c_reg_read(address, reg_data);
}

static int ak4954_upd_bits(uint8_t reg, uint8_t mask, uint8_t val)
{
    int result;
    uint8_t old, _new;

    result = ak4954_reg_read(reg, &old);
    if (result == 0)
    {
        _new = (old & ~mask) | val;
        if (_new != old)
            result = ak4954_reg_write(reg, _new);
    }

    return result;
}

static uint8_t ak4954_double_range_to_index(double val, const ak4954_dbl_range_t *r)
{
    uint8_t idx;

    if (val > r->max)
        val = r->max;
    else if (val < r->min)
        val = r->min;

    if (r->inv == true)
        idx = (r->max - val) / r->step;
    else
        idx = (val - r->min) / r->step;

    return idx;
}

static int ak4954_reset(void)
{
    int result = 1;
    printf("%s\n", __func__);

    AUDIO_CODEC_PDN = 0;
    ThisThread::sleep_for(AK4954_RESET_HOLD_TIME_IN_MILLIS);
    AUDIO_CODEC_PDN = 1;

    ThisThread::sleep_for(100ms);
    /* Issue dummy command. */
    int retry = 3;
    while (retry-- > 0 && result != 0)
    {
        result = ak4954_reg_write(AK4954_REG_PM1, 0);
    }
    return result;
}

static int ak4954_init(void)
{
    int result;
    printf("%s\n", __func__);

    result = ak4954_reset();

    /* Power-up. */
    if (result == 0)
        result = ak4954_reg_write(AK4954_REG_PM1, AK4954_PMVCM);

    if (result == 0)
    {
        uint8_t pm2 = 0;

        ThisThread::sleep_for(AK4954_PMVCM_RISE_UP_TIME_IN_MILLIS);
        result = ak4954_reg_write(AK4954_REG_PM2, pm2);
    }

    return result;
}

static int ak4954_deinit(void)
{
    int result;
    printf("%s\n", __func__);

    //    LOCK_RTD(rtd);
    //
    //    /* Power-down audio route. */
    //    if (result == WICED_SUCCESS)
    //    {
    //        if (dd->route->fn)
    //            result = (*dd->route->fn)(ak4954, WICED_FALSE);
    //    }
    //
    //    /* This audio route is no longer configured. */
    //    if (result == WICED_SUCCESS)
    //    {
    //        /* Remove in-use flags. */
    //        rtd->cfg &= ~(1<<ak4954_type(dd));
    //        rtd->init &= ~(1<<ak4954_type(dd));
    //
    //        /* No other initializations; clean-up. */
    //        if (!(rtd->init & ~(1<<ak4954_type(dd))))
    //        {
    //            /* Disable PLL. */
    //            if (result == WICED_SUCCESS)
    //            {
    //                if (ak4954->ck.pll_enab)
    //                    result = ak4954_upd_bits(ak4954, AK4954_REG_PM2, AK4954_PMPLL_MASK, 0);
    //            }
    //
    //            /* Disable VCM. */
    //            if (result == WICED_SUCCESS)
    //                result = ak4954_upd_bits(ak4954, AK4954_REG_PM1, AK4954_PMVCM_MASK, 0);
    //
    //            /* Power-down chip. */
    //            if (result == WICED_SUCCESS)
    //            {
    //                if (ak4954->pdn != WICED_GPIO_MAX)
    //                {
    //                    result = wiced_gpio_output_low(ak4954->pdn);
    //                }
    //            }
    //        }
    //    }
    //
    //    /* Don't deinitialize I2C since it might be used by other modules.
    //     * Diddo for IOE.
    //     */
    //
    //    UNLOCK_RTD(rtd);

    return result;
}

int ak4954_spll(uint32_t mclk)
{
    int result;

    result = ak4954_upd_bits(AK4954_REG_MODE_CTRL_1, AK4954_PLL_MASK, AK4954_PLL_64FS);

    return result;
}

int ak4954_spkr(bool is_pwr_up)
{
    int result;
    if (is_pwr_up)
    {
        /* Set-up path: DAC->SPK amp. */
        result = ak4954_upd_bits(AK4954_REG_SIG_SEL_1, AK4954_DACSL_MASK, AK4954_DACSL);

        /* Set-up SPK amp gain. */
        /* Set-up digital output volume control. */
        /* Set-up DRC control. */
        ;

        /* Power-up DRC. */
        if (result == 0)
            result = ak4954_upd_bits(AK4954_REG_DIG_FILTER_MODE, AK4954_PMDRC_MASK, AK4954_PMDRC);

        /* Power-up DAC and SPK amp. */
        if (result == 0)
            result = ak4954_upd_bits(AK4954_REG_PM1, AK4954_PMDAC_MASK, AK4954_PMDAC);
        if (result == 0)
            result = ak4954_upd_bits(AK4954_REG_PM2, AK4954_PMSL_MASK, AK4954_PMSL);

        /* Exit SPK amp power save mode. */
        if (result == 0)
            result = ak4954_upd_bits(AK4954_REG_SIG_SEL_1, AK4954_SLPSN_MASK, AK4954_SLPSN);
    }
    else
    {
        /* Enter SPKR amp power save mode. */
        result = ak4954_upd_bits(AK4954_REG_SIG_SEL_1, AK4954_SLPSN_MASK, 0);

        /* Disable DAC to output amp. */
        /* Set separately from SLPSN because datasheet shows it that way. */
        if (result == 0)
            result = ak4954_upd_bits(AK4954_REG_SIG_SEL_1, AK4954_DACSL_MASK, 0);

        /* Power-down DAC and SPK amp. */
        if (result == 0)
            result = ak4954_upd_bits(AK4954_REG_PM2, AK4954_PMSL_MASK, 0);
        if (result == 0)
            result = ak4954_upd_bits(AK4954_REG_PM1, AK4954_PMDAC_MASK, 0);

        /* Power-down DRC. */
        if (result == 0)
            result = ak4954_upd_bits(AK4954_REG_DIG_FILTER_MODE, AK4954_PMDRC_MASK, 0);
    }

    return result;
}

static int ak4954_set_volume(double decibels, const ak4954_dbl_range_t *r, uint8_t reg)
{
    uint8_t val;

    val = ak4954_double_range_to_index(decibels, r);

    /* Volume is full width of register. */
    /* Set it. */
    return ak4954_reg_write(reg, val);
}

static int ak4954_set_playback_volume(double decibels)
{
    /* Setting left volume also sets right as long as defaults are maintained. */
    return ak4954_set_volume(decibels, &ak4954_dbl_range_dvl, AK4954_REG_DVL_CTRL);
}

I2S i2s(MBED_CONF_APP_AUDIO_I2S_SD, MBED_CONF_APP_AUDIO_I2S_CK,
        MBED_CONF_APP_AUDIO_I2S_WS, NC, MBED_CONF_APP_AUDIO_I2S_MCK);

volatile int callback_called = 0;
void i2s_callback(int arg)
{
    callback_called = arg;
}

#define WAVFILE_SAMPLES_PER_SECOND SAMPLE_RATE
#define NUM_SAMPLES (1349 * 2)
#define SAMPLE_PERIOD (1000000.0 / WAVFILE_SAMPLES_PER_SECOND)
static short waveform[NUM_SAMPLES] = {
    0,
};
int make_wave_form(double frequency)
{
    int volume = 30000;
    int length = (int)((1000000.0 / frequency) / SAMPLE_PERIOD);

    int i, j = 0;
    for (i = 0; i < length; i++)
    {
        double t = (double)i / WAVFILE_SAMPLES_PER_SECOND;
        waveform[j++] = volume * sin(frequency * t * 2 * M_PI);
        waveform[j++] = 0;
    }

    return length;
}

int main()
{
    printf("Audio Test %d\n", SAMPLE_RATE);

    AUDIO_CODEC_PDN = 1;
    AUDIO_SPK_CTRL = 1;
    AUDIO_AMP_CTRL = 1;

    i2s.mode(MASTER_TX, true);
    i2s.format(16, 16, 0);
    i2s.audio_frequency(SAMPLE_RATE);
    i2s.protocol(PHILIPS);

    ak4954_reset();
    ak4954_reg_write(AK4954_REG_MODE_CTRL_1, 0x23); // 11.2896MHz, Philips
#if (SAMPLE_RATE == 8000)
    ak4954_reg_write(AK4954_REG_MODE_CTRL_2, 0x00); // 8KHz
#elif (SAMPLE_RATE == 44100)
    ak4954_reg_write(AK4954_REG_MODE_CTRL_2, 0x09); // 44.1KHz
#endif
    ak4954_reg_write(AK4954_REG_PM1, AK4954_PMVCM);
    ThisThread::sleep_for(2ms);

    ak4954_upd_bits(AK4954_REG_SIG_SEL_1, AK4954_DACSL_MASK, AK4954_DACSL);
    // ak4954_upd_bits(AK4954_REG_SIG_SEL_1, AK4954_MGAIN_MASK, AK4954_MGAIN_0DB);
    ak4954_upd_bits(AK4954_REG_SIG_SEL_2, 0xC0, 0xC0);
    ak4954_reg_write(AK4954_REG_DVL_CTRL, 0x30);    // L
    ak4954_reg_write(AK4954_REG_DVR_CTRL, 0x90);    // R
    ak4954_upd_bits(AK4954_REG_PM1, AK4954_PMDAC_MASK, AK4954_PMDAC);
    ak4954_upd_bits(AK4954_REG_PM2, AK4954_PMSL_MASK, AK4954_PMSL);
    ThisThread::sleep_for(30ms);
    ak4954_upd_bits(AK4954_REG_SIG_SEL_1, AK4954_SLPSN_MASK, AK4954_SLPSN);
#ifndef USE_MAKE_SINE_WAVE
    int ret = i2s.transfer(pcm2, sizeof(pcm2), (uint8_t *)nullptr, 0, i2s_callback, I2S_EVENT_ALL);
#endif

#if 0 // Beep control
    ak4954_reg_write(AK4954_REG_BEEP_FREQ, 0x00);
    ak4954_reg_write(AK4954_REG_BEEP_ON_TIME, 0x80);
    ak4954_reg_write(AK4954_REG_BEEP_OFF_TIME, 0x80);
    ak4954_reg_write(AK4954_REG_BEEP_REPEAT_CNT, 0x05);
    ak4954_reg_write(AK4954_REG_BEEP_VOL_CTRL, 0x00);

    ak4954_upd_bits(AK4954_REG_PM2, AK4954_PMSL_MASK, AK4954_PMSL); 
    ak4954_upd_bits(AK4954_REG_PM1, AK4954_PMBP_MASK, AK4954_PMBP); 
    ThisThread::sleep_for(1ms);
    ak4954_upd_bits(AK4954_REG_SIG_SEL_1, AK4954_SLPSN_MASK, AK4954_SLPSN); 
    ak4954_upd_bits(AK4954_REG_BEEP_VOL_CTRL, 0x80, 0x80);
#endif

#ifdef USE_MAKE_SINE_WAVE
#if 0
    int length = make_wave_form(880);
    int ret = i2s.transfer(waveform, length*4, (short int*)nullptr, 0, i2s_callback, I2S_EVENT_ALL);
#else
    //double tone[7] = { 32.7032, 36.7081, 41.2034, 43.6535, 48.9994, 55.0000, 61.7354 };
    double tone[7] = {2093.0048, 2349.3184, 2637.0176, 2793.824, 3135.9616, 3520, 3951.0656};
    //for(int i = 0; i < 7; i++)
    {
        for (int j = 0; j < 7; j++)
        {
            printf("Tone: %fhz\n", tone[j]);
            int length = make_wave_form(tone[j]);
            int ret = i2s.transfer(waveform, length * 4, (short int *)nullptr, 0, i2s_callback, I2S_EVENT_ALL);
            tone[j] *= 2;
            ThisThread::sleep_for(1s);
            i2s.abort_all_transfers();
        }
    }
    AUDIO_CODEC_PDN = 0;
    AUDIO_SPK_CTRL = 0;
    AUDIO_AMP_CTRL = 0;
#endif
#endif
    while (1)
    {
        ThisThread::sleep_for(AUDIO_STABLE_TIME_SEC);
    }
}

#else // H/W ver02

/* mbed Microcontroller Library
 * Copyright (c) 2019 ARM Limited
 * SPDX-License-Identifier: Apache-2.0
 */

#include "mbed.h"
#include "ko_kick_44100.pcm.h"
#include "ko_hello.pcm.h"
#include "I2S.h"

#define AUDIO_I2C_ADDR (0x18 << 1)

I2S i2s(MBED_CONF_APP_AUDIO_I2S_SD, MBED_CONF_APP_AUDIO_I2S_CK, MBED_CONF_APP_AUDIO_I2S_WS, NC, MBED_CONF_APP_AUDIO_I2S_MCK);
I2C i2c(MBED_CONF_APP_AUDIO_I2C_SDA, MBED_CONF_APP_AUDIO_I2C_SCL);
DigitalOut codecReset(MBED_CONF_APP_AUDIO_CODEC_RST, 0);
DigitalOut ampOn(MBED_CONF_APP_AUDIO_AMP_MUTE, 0);
DigitalOut spkOn(MBED_CONF_APP_AUDIO_TPA_MUTE, 0);

// DigitalOut dpin(MBED_CONF_APP_AUDIO_I2S_SD, 0);

int main()
{
    printf("Start Application\n");

    i2s.mode(MASTER_TX, true);
    i2s.format(16, 16, 0);
    i2s.audio_frequency(44100);
    i2s.protocol(PHILIPS);

    i2c.frequency(100000);

    wait_us(100);
    codecReset = 1;
    wait_us(100);
    spkOn = 1;
    ampOn = 1;

#if 1
    /* 1. Define starting point */
    /* (b) Set register page to 0 */
    if (i2c.write(AUDIO_I2C_ADDR, "\x00\x00", 2))
    {
        printf("I2C write failed.\n");
    }

    /* (c) Initiate SW reset */
    if (i2c.write(AUDIO_I2C_ADDR, "\x01\x01", 2))
    {
        printf("I2C write failed.\n");
    }

    /* 2. Program clock settings */
    /* (a) Program PLL clock dividers P,J, D, R (if PLL is used) */
    /* PLL_clkin = MCLK, codec_clkin = PLL_CLK */
    if (i2c.write(AUDIO_I2C_ADDR, "\x04\x03", 2))
    {
        printf("I2C write failed.\n");
    }

    /* J = 8 */
    if (i2c.write(AUDIO_I2C_ADDR, "\x06\x08", 2))
    {
        printf("I2C write failed.\n");
    }

    /* D = 0000, D(13:8) = 0, D(7:0) = 0 */
    if (i2c.write(AUDIO_I2C_ADDR, "\x07\x00\x00", 3))
    {
        printf("I2C write failed.\n");
    }

    /* (b) Power up PLL (if PLL is used) */
    /* PLL Power up, P = 1, R = 1 */
    if (i2c.write(AUDIO_I2C_ADDR, "\x05\x91", 2))
    {
        printf("I2C write failed.\n");
    }

    /* (c) Program and power up NDAC */
    /* NDAC is powered up and set to 8 */
    if (i2c.write(AUDIO_I2C_ADDR, "\x0B\x88", 2))
    {
        printf("I2C write failed.\n");
    }

    /* (d) Program and power up MDAC */
    /* MDAC is powered up and set to 2 */
    if (i2c.write(AUDIO_I2C_ADDR, "\x0C\x82", 2))
    {
        printf("I2C write failed.\n");
    }

    /* (e) Program OSR value */
    /* DOSR = 128, DOSR(9:8) = 0, DOSR(7:0) = 128 */
    if (i2c.write(AUDIO_I2C_ADDR, "\x0D\x00\x80", 3))
    {
        printf("I2C write failed.\n");
    }

    /* (f) Program I2S word length if required (16, 20, 24, 32 bits) and master mode (BCLK and WCLK are outputs) */
    /* mode is i2s, wordlength is 16, slave mode */
    if (i2c.write(AUDIO_I2C_ADDR, "\x1B\x00", 2))
    {
        printf("I2C write failed.\n");
    }

    /* (g) Program the processing block to be used */
    /* Select DAC DSP Processing Block PRB_P16 */
    // if (i2c.write(AUDIO_I2C_ADDR, "\x3C\x04", 2))
    // if (i2c.write(AUDIO_I2C_ADDR, "\x3C\x05", 2))
    // if (i2c.write(AUDIO_I2C_ADDR, "\x3C\x06", 2))
    // if (i2c.write(AUDIO_I2C_ADDR, "\x3C\x0C", 2))
    // if (i2c.write(AUDIO_I2C_ADDR, "\x3C\x0D", 2))
    // if (i2c.write(AUDIO_I2C_ADDR, "\x3C\x0E", 2))
    // if (i2c.write(AUDIO_I2C_ADDR, "\x3C\x0F", 2))
    // if (i2c.write(AUDIO_I2C_ADDR, "\x3C\x14", 2))
    // if (i2c.write(AUDIO_I2C_ADDR, "\x3C\x15", 2))
    // if (i2c.write(AUDIO_I2C_ADDR, "\x3C\x16", 2))
    // if (i2c.write(AUDIO_I2C_ADDR, "\x3C\x19", 2))
    if (i2c.write(AUDIO_I2C_ADDR, "\x3C\x10", 2))
    {
        printf("I2C write failed.\n");
    }

    /* Set register page to 8 */
    if (i2c.write(AUDIO_I2C_ADDR, "\x00\x08", 2))
    {
        printf("I2C write failed.\n");
    }

    /* Adaptive filtering enabled in DAC */
    if (i2c.write(AUDIO_I2C_ADDR, "\x01\x04", 2))
    {
        printf("I2C write failed.\n");
    }

    /* Set register page to 0 */
    if (i2c.write(AUDIO_I2C_ADDR, "\x00\x00", 2))
    {
        printf("I2C write failed.\n");
    }

    /* 3. Program analog blocks */
    /* (a) Set register page to 1 */
    if (i2c.write(AUDIO_I2C_ADDR, "\x00\x01", 2))
    {
        printf("I2C write failed.\n");
    }

    /* (b) Program common-mode voltage (defalut = 1.35 V) */
    if (i2c.write(AUDIO_I2C_ADDR, "\x1F\x04", 2))
    {
        printf("I2C write failed.\n");
    }

    /* (c) Program headphone-specific depop settings (in case headphone driver is used) */
    /* De-pop, Power on = 800 ms, Step time = 4 ms() */
    if (i2c.write(AUDIO_I2C_ADDR, "\x21\x4E", 2))
    {
        printf("I2C write failed.\n");
    }

    /* (d) Program routing of DAC output to the output amplifier (headphone/lineout or speaker) */
    /* DAC routed to HPOUT(X) */
    /* DAC routed to mixer amplifier */
    if (i2c.write(AUDIO_I2C_ADDR, "\x23\x40", 2))               // 얘 40 -> 00으로 바꾸면(route 끊으면) 노이즈만 나옴
    {
        printf("I2C write failed.\n");
    }

    /* (e) Unmute and set gain of output driver */
    /* Unmute HPOUT, set gain = 0 db */
    // if (i2c.write(AUDIO_I2C_ADDR, "\x28\x06", 2))
    // {
    //     printf("I2C write failed.\n");
    // }

    /* Unmute Class-D, set gain = 18 dB */
    // if (i2c.write(AUDIO_I2C_ADDR, "\x2A\x04", 2))               // 6dB
    // if (i2c.write(AUDIO_I2C_ADDR, "\x2A\x0C", 2))               // 12dB
    // if (i2c.write(AUDIO_I2C_ADDR, "\x2A\x14", 2))               // 18dB
    if (i2c.write(AUDIO_I2C_ADDR, "\x2A\x1C", 2))               // 24dB
    {
        printf("I2C wr0ite failed.\n");
    }

    /* (f) Power up output drivers */
    /* HPOUT powered up */
    // if (i2c.write(AUDIO_I2C_ADDR, "\x1F\x82", 2))
    // {
    //     printf("I2C write failed.\n");
    // }

    /* Power-up Class-D drivers */                              // 이놈
    if (i2c.write(AUDIO_I2C_ADDR, "\x20\x86", 2))               // C6을 86으로 바꿈.
    {
        printf("I2C write failed.\n");
    }

    /* Enable HPOUT output analog volume, set = -9 dB */        // 이거 틀림
    // if (i2c.write(AUDIO_I2C_ADDR, "\x24\x92", 2)) 
    // {
    //     printf("I2C write failed.\n");
    // }

    /* Enable Class-D output analog volume, set = -9 dB */
    if (i2c.write(AUDIO_I2C_ADDR, "\x26\x92", 2))
    {
        printf("I2C write failed.\n");
    }

    /* 4. Apply waiting time determined by the de-pop settings and the soft-stepping settings of the driver gain or poll page 1 / register 63 */
    wait_us(1000000); // 1000ms

    /* 5. Power up DAC */
    /* (a) Set register page to 0 */
    if (i2c.write(AUDIO_I2C_ADDR, "\x00\x00", 2))
    {
        printf("I2C write failed.\n");
    }

    /* (b) Power up DAC channels and set digital gain */
    /* Power up DAC (soft step enabled) */
    if (i2c.write(AUDIO_I2C_ADDR, "\x3F\x94", 2))
    {
        printf("I2C write failed.\n");
    }
    
    /* DAC gain = -22 dB */
    if (i2c.write(AUDIO_I2C_ADDR, "\x41\xD4", 2))       // -22dB, Original
    // if (i2c.write(AUDIO_I2C_ADDR, "\x41\x81", 2))    // 24dB, Max
    // if (i2c.write(AUDIO_I2C_ADDR, "\x41\x01", 2))    // -63.5dB, Min
    // if (i2c.write(AUDIO_I2C_ADDR, "\x41\xAC", 2))
    // if (i2c.write(AUDIO_I2C_ADDR, "\x41\x50", 2))
    {
        printf("I2C write failed.\n");
    }

    /* (c) Unmute digital volume control */
    /* Unmute DAC */
    if (i2c.write(AUDIO_I2C_ADDR, "\x40\x04", 2))
    {
        printf("I2C write failed.\n");
    }
#endif

    wait_us(100000); // 100ms

#if 1
    int ret = i2s.transfer(pcm, sizeof(pcm), (uint8_t *)nullptr, 0, nullptr, 0);
#endif

    while (true)
    {
        printf("Toggle\n");
        ThisThread::sleep_for(5s);
    }
}

#endif
