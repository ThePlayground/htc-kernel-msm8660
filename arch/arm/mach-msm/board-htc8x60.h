/* linux/arch/arm/mach-msm/board-htc8x60.h
 *
 * Copyright (C) 2010-2011 HTC Corporation.
 *
 * This software is licensed under the terms of the GNU General Public
 * License version 2, as published by the Free Software Foundation, and
 * may be copied, distributed, and modified under those terms.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 */

#ifndef __ARCH_ARM_MACH_MSM_BOARD_HTC8X60_H
#define __ARCH_ARM_MACH_MSM_BOARD_HTC8X60_H

#include <mach/board.h>
#include <mach/msm_memtypes.h>

#ifdef CONFIG_MACH_SHOOTER
#define HTC8X60_PROJECT_NAME	"shooter"
#elif defined(CONFIG_MACH_SHOOTER_U)
#define HTC8X60_PROJECT_NAME	"shooter_u"
#elif defined(CONFIG_MACH_PYRAMID)
#define HTC8X60_PROJECT_NAME	"pyramid"
#elif defined(CONFIG_MACH_RUBY)
#define HTC8X60_PROJECT_NAME	"ruby"
#endif

/* deal with memory allocation */

#define MSM_SHARED_RAM_PHYS		0x40000000
#define MSM_RAM_CONSOLE_BASE		0x40300000
#define MSM_RAM_CONSOLE_SIZE		SZ_1M

#ifdef CONFIG_FB_MSM_LCDC_DSUB
/* VGA = 1440 x 900 x 4(bpp) x 2(pages)
   prim = 1024 x 600 x 4(bpp) x 2(pages)
   This is the difference. */
#define MSM_FB_DSUB_PMEM_ADDER (0xA32000-0x4B0000)
#else
#define MSM_FB_DSUB_PMEM_ADDER (0)
#endif

#ifdef CONFIG_FB_MSM_TRIPLE_BUFFER
#define MSM_FB_PRIM_BUF_SIZE (960 * ALIGN(540, 32) * 4 * 3) /* 4 bpp x 3 pages */
#else
#define MSM_FB_PRIM_BUF_SIZE (960 * ALIGN(540, 32) * 4 * 2) /* 4 bpp x 2 pages */
#endif

#ifdef CONFIG_FB_MSM_HDMI_MSM_PANEL
#define MSM_FB_EXT_BUF_SIZE  (1920 * 1080 * 2 * 1) /* 2 bpp x 1 page */
#elif defined(CONFIG_FB_MSM_TVOUT)
#define MSM_FB_EXT_BUF_SIZE  (720 * 576 * 2 * 2) /* 2 bpp x 2 pages */
#else
#define MSM_FB_EXT_BUF_SIZE	0
#endif

#ifdef CONFIG_FB_MSM_HDMI_AS_PRIMARY
/* 4 bpp x 2 page HDMI case */
#define MSM_FB_SIZE roundup((1920 * 1088 * 4 * 2), 4096)
#else
/* Note: must be multiple of 4096 */
#define MSM_FB_SIZE roundup(MSM_FB_PRIM_BUF_SIZE + MSM_FB_EXT_BUF_SIZE + \
				MSM_FB_DSUB_PMEM_ADDER, 4096)
#endif

#ifdef CONFIG_FB_MSM_HDMI_AS_PRIMARY
#define MSM_PMEM_SF_SIZE 0x8000000 /* 128 Mbytes */
#else
#define MSM_PMEM_SF_SIZE 0x4000000 /* 64 Mbytes */
#endif

#ifdef CONFIG_FB_MSM_OVERLAY0_WRITEBACK
#define MSM_FB_OVERLAY0_WRITEBACK_SIZE roundup((1376 * 768 * 3 * 2), 4096)
#else
#define MSM_FB_OVERLAY0_WRITEBACK_SIZE (0)
#endif  /* CONFIG_FB_MSM_OVERLAY0_WRITEBACK */

#ifdef CONFIG_FB_MSM_OVERLAY1_WRITEBACK
#define MSM_FB_OVERLAY1_WRITEBACK_SIZE roundup((1920 * 1088 * 3 * 2), 4096)
#else
#define MSM_FB_OVERLAY1_WRITEBACK_SIZE (0)
#endif  /* CONFIG_FB_MSM_OVERLAY1_WRITEBACK */

#define MSM_PMEM_KERNEL_EBI1_SIZE  0xC7000
#define MSM_PMEM_ADSP_SIZE         0x2000000
#define MSM_PMEM_AUDIO_SIZE        0x28B000

#define MSM_SMI_BASE          0x38000000
#define MSM_SMI_SIZE          0x4000000

#define KERNEL_SMI_BASE       (MSM_SMI_BASE)
#define KERNEL_SMI_SIZE       0x600000

#define USER_SMI_BASE         (KERNEL_SMI_BASE + KERNEL_SMI_SIZE)
#define USER_SMI_SIZE         (MSM_SMI_SIZE - KERNEL_SMI_SIZE)
#define MSM_PMEM_SMIPOOL_SIZE USER_SMI_SIZE

#define MSM_ION_SF_SIZE		0x4000000 /* 64MB */
#define MSM_ION_CAMERA_SIZE     MSM_PMEM_ADSP_SIZE
#define MSM_ION_MM_FW_SIZE	0x200000 /* (2MB) */
#define MSM_ION_MM_SIZE		0x3600000 /* (54MB) */
#define MSM_ION_MFC_SIZE	SZ_8K
#define MSM_ION_WB_SIZE		0x600000 /* 6MB */
#define MSM_ION_QSECOM_SIZE	0x600000 /* (6MB) */
#define MSM_ION_AUDIO_SIZE	MSM_PMEM_AUDIO_SIZE

#ifdef CONFIG_MSM_MULTIMEDIA_USE_ION
#define MSM_ION_HEAP_NUM	9
#else
#define MSM_ION_HEAP_NUM	1
#endif
/* end deal with memory allocation */

/* GPIO definition */

/*Gyro*/
#ifdef CONFIG_MACH_RUBY
#define HTC8X60_GPIO_PANA_GYRO_SLEEP	(70)
#define HTC8X60_GPIO_GYRO_ID		(130)
#define HTC8X60_GPIO_GYRO_DIAG		(41)
#endif

/* Direct Keys */
#define HTC8X60_GPIO_SW_LCM_3D       (64)
#define HTC8X60_GPIO_SW_LCM_2D       (68)
#ifdef CONFIG_MACH_PYRAMID
#define HTC8X60_GPIO_KEY_VOL_DOWN	(189)
#define HTC8X60_GPIO_KEY_VOL_UP		(188)
#elif defined(CONFIG_MACH_SHOOTER) || defined(CONFIG_MACH_SHOOTER_U) || defined(CONFIG_MACH_RUBY)
#define HTC8X60_GPIO_KEY_VOL_DOWN    (103)
#define HTC8X60_GPIO_KEY_VOL_UP      (104)
#ifndef CONFIG_MACH_RUBY
#define HTC8X60_GPIO_KEY_CAM_STEP2   (115)
#define HTC8X60_GPIO_KEY_CAM_STEP1   (123)
#else
#define HTC8X60_GPIO_KEY_CAPTURE     (94)
#endif
#endif
#define HTC8X60_GPIO_KEY_POWER       (125)

/* Battery */
#define HTC8X60_GPIO_MBAT_IN		   (61)
#define HTC8X60_GPIO_CHG_INT		   (126)

/* Wifi */
#define HTC8X60_GPIO_WIFI_IRQ              (46)
#define HTC8X60_GPIO_WIFI_SHUTDOWN_N       (96)

/* WiMax */
#define HTC8X60_GPIO_WIMAX_UART_SIN        (41)
#define HTC8X60_GPIO_WIMAX_UART_SOUT       (42)
#define HTC8X60_GPIO_V_WIMAX_1V2_RF_EN     (43)
#define HTC8X60_GPIO_WIMAX_EXT_RST         (49)
#define HTC8X60_GPIO_V_WIMAX_DVDD_EN       (94)
#define HTC8X60_GPIO_V_WIMAX_PVDD_EN       (105)
#define HTC8X60_GPIO_WIMAX_SDIO_D0         (143)
#define HTC8X60_GPIO_WIMAX_SDIO_D1         (144)
#define HTC8X60_GPIO_WIMAX_SDIO_D2         (145)
#define HTC8X60_GPIO_WIMAX_SDIO_D3         (146)
#define HTC8X60_GPIO_WIMAX_SDIO_CMD        (151)
#define HTC8X60_GPIO_WIMAX_SDIO_CLK_CPU    (152)
#define HTC8X60_GPIO_CPU_WIMAX_SW          (156)
#define HTC8X60_GPIO_CPU_WIMAX_UART_EN     (157)

/* Sensors */
#ifndef CONFIG_MACH_RUBY
#define HTC8X60_SENSOR_I2C_SDA		(72)
#define HTC8X60_SENSOR_I2C_SCL		(73)
#define HTC8X60_GYRO_INT		(127)
#else
#define HTC8X60_SENSOR_I2C_SCL	(115)
#define HTC8X60_SENSOR_I2C_SDA	(116)
#define HTC8X60_GYRO_INT		(126)
#define HTC8X60_COMPASS_INT	(128)
#define HTC8X60_GSENSOR_INT_N	(127)

#define HTC8X60_LAYOUTS	{ \
			{ { 0,  1, 0}, {-1,  0,  0}, {0, 0, 1} }, \
			{ { 0, -1, 0}, { 1,  0,  0}, {0, 0, -1} }, \
			{ {-1,  0, 0}, { 0, -1,  0}, {0, 0,  1} }, \
			{ {-1,  0, 0}, { 0,  0, -1}, {0, 1,  0} }   \
			}
#endif

/* General */
#define HTC8X60_GENERAL_I2C_SDA		(59)
#define HTC8X60_GENERAL_I2C_SCL		(60)

/* Microp */

/* TP */
#define HTC8X60_TP_I2C_SDA           (51)
#define HTC8X60_TP_I2C_SCL           (52)
#ifdef CONFIG_TOUCHSCREEN_ATMEL
#ifdef CONFIG_MACH_RUBY
#define HTC8X60_TP_ATT_N                (117)
#else
#define HTC8X60_TP_ATT_N             (57)
#endif
#elif defined(CONFIG_TOUCHSCREEN_CYPRESS_TMA)
#define HTC8X60_TP_ATT_N             (65)
#define HTC8X60_TP_ATT_N_XB          (50)
#endif

/* LCD */
#ifndef CONFIG_MACH_RUBY
#define GPIO_LCM_ID	50
#define GPIO_LCM_RST_N	66
#else
#define GPIO_LCM_RST_N		(137)
#define GPIO_LCM_ID0		(64)
#define GPIO_LCM_ID1		(65)
#endif

/* Audio */
#ifndef CONFIG_MACH_RUBY
#define HTC8X60_AUD_CODEC_RST        (67)
#define HTC8X60_AUD_CDC_LDO_SEL      (116)
#else
#define HTC8X60_AUD_CODEC_RST        (118)
#define HTC8X60_AUD_QTR_RESET        (158)
#endif

/* BT */
#define HTC8X60_GPIO_BT_HOST_WAKE      (45)
#define HTC8X60_GPIO_BT_UART1_TX       (53)
#define HTC8X60_GPIO_BT_UART1_RX       (54)
#define HTC8X60_GPIO_BT_UART1_CTS      (55)
#define HTC8X60_GPIO_BT_UART1_RTS      (56)
#define HTC8X60_GPIO_BT_SHUTDOWN_N     (100)
#define HTC8X60_GPIO_BT_CHIP_WAKE      (130)
#define HTC8X60_GPIO_BT_RESET_N        (142)

/* USB */
#define HTC8X60_GPIO_USB_ID             (63)
#define HTC8X60_GPIO_MHL_RESET          (70)
#define HTC8X60_GPIO_MHL_INT            (71)
#define HTC8X60_GPIO_MHL_USB_EN        (139)
#define HTC8X60_GPIO_MHL_USB_SW         (99)

/* USB and UART */
#ifdef CONFIG_MACH_RUBY
#define HTC8X60_GPIO_UART_RX           (105)
#define HTC8X60_GPIO_UART_TX           (106)
#endif

/* Camera */

/* Flashlight */
#ifndef CONFIG_MACH_RUBY
#define HTC8X60_FLASH_EN             (29)
#else
#define HTC8X60_FLASH_EN             (138)
#endif
#define HTC8X60_TORCH_EN             (30)

/* Accessory */
#define HTC8X60_GPIO_AUD_HP_DET        (31)

/* SPI */
#define HTC8X60_SPI_DO                 (33)
#define HTC8X60_SPI_DI                 (34)
#define HTC8X60_SPI_CS                 (35)
#define HTC8X60_SPI_CLK                (36)

/* SD */
#ifdef CONFIG_MACH_RUBY
#define HTC8X60_SD_DETECT_PIN		(37)
#define HTC8X60_PSNENOR_INTz		(123)
#endif

/* LCM */
#if defined(CONFIG_MACH_SHOOTER) || defined(CONFIG_MACH_SHOOTER_U)
#define HTC8X60_CTL_3D_1		(131)
#define HTC8X60_CTL_3D_2		(132)
#define HTC8X60_CTL_3D_3		(133)
#define HTC8X60_CTL_3D_4		(134)
#define HTC8X60_LCM_3D_PDz		(135)
#endif

/* CAMERA SPI */
#ifdef CONFIG_MACH_SHOOTER
#define HTC8X60_SP3D_SPI_DO                 (37)
#define HTC8X60_SP3D_SPI_DI                 (38)
#define HTC8X60_SP3D_SPI_CS                 (39)
#define HTC8X60_SP3D_SPI_CLK                (40)
#elif defined(CONFIG_MACH_SHOOTER_U)
#define HTC8X60_SP3D_SPI_DO                 (41)
#define HTC8X60_SP3D_SPI_DI                 (42)
#define HTC8X60_SP3D_SPI_CS                 (43)
#define HTC8X60_SP3D_SPI_CLK                (44)
#endif

/* CAMERA GPIO */
#define HTC8X60_CAM_I2C_SDA           (47)
#define HTC8X60_CAM_I2C_SCL           (48)

#if defined(CONFIG_MACH_SHOOTER) || defined(CONFIG_MACH_SHOOTER_U)
#define HTC8X60_SP3D_GATE              (107)
#define HTC8X60_SP3D_CORE_GATE         (58)
#define HTC8X60_SP3D_SYS_RST           (102)
#define HTC8X60_SP3D_PDX               (137)

#define HTC8X60_S5K4E1_PD				(137)
#define HTC8X60_S5K4E1_INTB				(102)
#define HTC8X60_S5K4E1_VCM_PD			(58)

#define HTC8X60_SP3D_MCLK		(32)
#define HTC8X60_WEBCAM_STB		(140)
#define HTC8X60_WEBCAM_RST		(138)
#define HTC8X60_CAM_SEL			(141)
#endif


/* PMIC */

/* PMIC GPIO definition */
#define PMGPIO(x) (x-1)

#ifndef CONFIG_MACH_RUBY
#define HTC8X60_AUD_HP_EN          PMGPIO(18)
#define HTC8X60_AUD_QTR_RESET      PMGPIO(21)
#define HTC8X60_TP_RST             PMGPIO(23)
#define HTC8X60_GREEN_LED          PMGPIO(24)
#define HTC8X60_AMBER_LED          PMGPIO(25)
#define HTC8X60_CHG_STAT           PMGPIO(33)
#define HTC8X60_SDC3_DET           PMGPIO(34)
#define HTC8X60_AUD_REMO_PRES      PMGPIO(37)
#define HTC8X60_WIFI_BT_SLEEP_CLK  PMGPIO(38)

#if defined(CONFIG_MACH_SHOOTER) || defined(CONFIG_MACH_SHOOTER_U)
#define HTC8X60_VOL_UP             (104)
#define HTC8X60_VOL_DN             (103)
#define HTC8X60_AUD_MIC_SEL        PMGPIO(14)
#define HTC8X60_AUD_REMO_EN        PMGPIO(15)
#define HTC8X60_WIMAX_DEBUG12      PMGPIO(16)
#define HTC8X60_WIMAX_HOST_WAKEUP  PMGPIO(17)
#define HTC8X60_AUD_SPK_ENO        PMGPIO(19)
#define HTC8X60_3DLCM_PD           PMGPIO(20)
#define HTC8X60_PS_VOUT            PMGPIO(22)
#define HTC8X60_3DCLK              PMGPIO(26)
#define HTC8X60_WIMAX_DEBUG14_XA   PMGPIO(28)
#define HTC8X60_WIMAX_DEBUG15_XA   PMGPIO(30)
#define HTC8X60_TORCH_SET2         PMGPIO(31)
#define HTC8X60_WIMAX_DEBUG14      PMGPIO(35)
#define HTC8X60_WIMAX_DEBUG15      PMGPIO(36)
#ifdef CONFIG_MACH_SHOOTER
#define HTC8X60_TORCH_SET1         PMGPIO(32)
#elif defined(CONFIG_MACH_SHOOTER_U)
#define HTC8X60_TORCH_SET1         PMGPIO(40)
#endif
#elif defined (CONFIG_MACH_PYRAMID)
#define HTC8X60_VOL_UP             PMGPIO(16)
#define HTC8X60_VOL_DN             PMGPIO(17)
#define HTC8X60_HAP_ENABLE         PMGPIO(19)
#define HTC8X60_AUD_MIC_SEL        PMGPIO(26)
#define HTC8X60_PS_VOUT            PMGPIO(35)
#endif

#else
#define HTC8X60_VOL_UP			(104)
#define HTC8X60_VOL_DN			(103)
#define HTC8X60_AUD_REMO_PRES		PMGPIO(7)
#define HTC8X60_WIFI_BT_FAST_CLK	PMGPIO(8)
#define HTC8X60_H2W_CABLE_IN2		PMGPIO(9)
#define HTC8X60_H2W_IO2_DAT		PMGPIO(10)
#define HTC8X60_PSENSOR_PVT_INTz	PMGPIO(15)
#define HTC8X60_AUD_HANDSET_ENO		PMGPIO(18)
#define HTC8X60_GPIO_KEY_CAMCODER	PMGPIO(22)
#define HTC8X60_TP_RST			PMGPIO(23)
#define HTC8X60_LED_3V3			PMGPIO(24)
#define HTC8X60_CHG_STAT		PMGPIO(33)
#define HTC8X60_H2W_IO1_CLK		PMGPIO(34)
#define HTC8X60_GPIO_KEY_CAMAF		PMGPIO(35)
#define HTC8X60_AUD_MIC_SEL		PMGPIO(37)
#define HTC8X60_WIFI_BT_SLEEP_CLK	PMGPIO(38)
#define HTC8X60_H2W_CABLE_IN1		PMGPIO(36)
#endif

/* NFC */
#ifdef CONFIG_MACH_RUBY
#define HTC8X60_NFC_I2C_SDA             (43)
#define HTC8X60_NFC_I2C_SCL             (44)
#define HTC8X60_GPIO_NFC_VEN		(20)
#define HTC8X60_GPIO_NFC_INT		(58)
#define HTC8X60_GPIO_NFC_DL		(21)
#endif

void __init htc8x60_init_mmc(void);
void __init htc8x60_audio_init(void);
void __init htc8x60_init_keypad(void);
int __init htc8x60_wifi_init(void);
void __init htc8x60_init_panel(void);
void __init htc8x60_init_cam(unsigned eid);
void msm8x60_allocate_fb_region(void);
void msm8x60_mdp_writeback(struct memtype_reserve *reserve_table);

#endif /* __ARCH_ARM_MACH_MSM_BOARD_HTC8X60_H */
