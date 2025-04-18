#ifndef _HAPTIC_HV_H_
#define _HAPTIC_HV_H_

#include <linux/regmap.h>
#include <linux/timer.h>
#include <linux/workqueue.h>
#include <linux/hrtimer.h>
#include <linux/mutex.h>
#include <linux/cdev.h>
#include <linux/version.h>
#include <sound/control.h>
#include <sound/soc.h>
#ifdef CONFIG_VENDOR_ZTE_DEV_MONITOR_SYSTEM
#include <vendor/comdef/zlog_common_base.h>
#endif
/*********************************************************
 *
 * Haptic_HV CHIPID
 *
 *********************************************************/
#define AW_REG_CHIPID				(0x00) /* AW869X/XX */
#define AW_REG_CHIPIDH				(0x57) /* AW8692X */
#define AW_REG_CHIPIDL				(0x58) /* AW8692X */
#define AW8695_CHIPID				(0x95)
#define AW8697_CHIPID				(0x97)
#define AW86905_CHIPID				(0x05)
#define AW86907_CHIPID				(0x04)
#define AW86915_CHIPID				(0x07)
#define AW86917_CHIPID				(0x06)
#define AW86715_CHIPID				(0x7150)
#define AW86716_CHIPID				(0x7170)
#define AW86717_CHIPID				(0x7171)
#define AW86718_CHIPID				(0x7180)
#define AW86925_CHIPID				(0x9250)
#define AW86926_CHIPID				(0x9260)
#define AW86927_CHIPID				(0x9270)
#define AW86928_CHIPID				(0x9280)

/*********************************************************
 *
 * Marco
 *
 *********************************************************/
#define AW_I2C_NAME				"haptic_hv"
#define AW_I2C_RETRIES				(5)
#define AW_I2C_RETRY_DELAY			(2)
#define AW_READ_CHIPID_RETRIES			(5)
#define AW_READ_CHIPID_RETRY_DELAY		(2)
#define AW_SEQUENCER_SIZE			(8)
#define AW_I2C_BYTE_ONE				(1)
#define AW_I2C_BYTE_TWO				(2)
#define AW_I2C_BYTE_THREE			(3)
#define AW_I2C_BYTE_FOUR			(4)
#define AW_I2C_BYTE_FIVE			(5)
#define AW_I2C_BYTE_SIX				(6)
#define AW_I2C_BYTE_SEVEN			(7)
#define AW_I2C_BYTE_EIGHT			(8)

#define AW_SEQUENCER_LOOP_SIZE			(4)
#define AW_RTP_NAME_MAX				(64)
#define AW_PM_QOS_VALUE_VB			(400)
#define AW_VBAT_REFER				(4500)
#define AW_VBAT_MIN				(3000)
#define AW_RAM_WORK_DELAY_INTERVAL		(8000)
#define AW_OSC_TRIM_PARAM			(50)
#define AW_OSC_CALI_ACCURACY			(24)
#define AW_OSC_CALI_MAX_LENGTH			(5100000)
#define AW_TRIG_NUM				(3)
#define AW_RAMDATA_RD_BUFFER_SIZE		(1024)
#define AW_RAMDATA_WR_BUFFER_SIZE		(2048)

#define AW_GLBRD_STATE_MASK			(15<<0)
#define AW_STATE_STANDBY			(0x00)
#define AW_STATE_RTP				(0x08)
#define AW_BIT_RESET				(0xAA)
#define AW_I2C_ADDR				(0x5A)

#define AW_CHECK_RAM_DATA
#define AW_READ_BIN_FLEXBALLY
#define AW_CHECK_QUALIFY
#define CPU_LATENCY_QOC_VALUE (0)

#define AW_DURATION_DECIDE_WAVEFORM
/* #define AW_OSC_MULTI_CALI */
/* #define AW_BOOT_OSC_CALI */
/* #define AW_ENABLE_RTP_PRINT_LOG */
/* #define AW_ENABLE_PIN_CONTROL */
/* #define AW_SND_SOC_CODEC */
/* #define AW869X_MUL_GET_F0 */
//[PIKE-1043] Upgrade richtap vibrator paramters by luoming0812 at 20210918
#define AAC_RICHTAP_SUPPORT
/*********************************************************
 *
 * Conditional Marco
 *
 *********************************************************/
#if LINUX_VERSION_CODE <= KERNEL_VERSION(4, 4, 1)
#define TIMED_OUTPUT
#endif

#if LINUX_VERSION_CODE >= KERNEL_VERSION(4, 19, 1)
#define KERNEL_OVER_4_19
#endif

#ifdef TIMED_OUTPUT
#include <../../../drivers/staging/android/timed_output.h>
typedef struct timed_output_dev cdev_t;
#else
typedef struct led_classdev cdev_t;
#endif

#ifdef KERNEL_OVER_4_19
typedef struct snd_soc_component aw_snd_soc_codec_t;
typedef struct snd_soc_component_driver aw_snd_soc_codec_driver_t;
#else
typedef struct snd_soc_codec aw_snd_soc_codec_t;
typedef struct snd_soc_codec_driver aw_snd_soc_codec_driver_t;
#endif

struct aw_componet_codec_ops {
	aw_snd_soc_codec_t *(*aw_snd_soc_kcontrol_codec)(struct snd_kcontrol *
			     kcontrol);
	void *(*aw_snd_soc_codec_get_drvdata)(aw_snd_soc_codec_t *codec);
	int (*aw_snd_soc_add_codec_controls)(aw_snd_soc_codec_t *codec,
		const struct snd_kcontrol_new *controls, uint32_t num_controls);
	void (*aw_snd_soc_unregister_codec)(struct device *dev);
	int (*aw_snd_soc_register_codec)(struct device *dev,
		const aw_snd_soc_codec_driver_t *codec_drv,
		struct snd_soc_dai_driver *dai_drv, int num_dai);
};

/*********************************************************
 *
 * AW869X
 *
 *********************************************************/
#define AW869X_TRG1_ENABLE			(1)
#define AW869X_TRG2_ENABLE			(1)
#define AW869X_TRG3_ENABLE			(1)
#define AW869X_TRG1_DISABLE			(0)
#define AW869X_TRG2_DISABLE			(0)
#define AW869X_TRG3_DISABLE			(0)
#define AW869X_TRG1_DUAL_EDGE			(1)
#define AW869X_TRG2_DUAL_EDGE			(1)
#define AW869X_TRG3_DUAL_EDGE			(1)
#define AW869X_TRG1_DEFAULT_LEVEL		(1)
#define AW869X_TRG2_DEFAULT_LEVEL		(1)
#define AW869X_TRG3_DEFAULT_LEVEL		(1)
#define AW869X_TRG1_FIRST_EDGE_SEQ		(1)
#define AW869X_TRG1_SECOND_EDGE_SEQ		(2)
#define AW869X_TRG2_FIRST_EDGE_SEQ		(1)
#define AW869X_TRG2_SECOND_EDGE_SEQ		(2)
#define AW869X_TRG3_FIRST_EDGE_SEQ		(1)
#define AW869X_TRG3_SECOND_EDGE_SEQ		(2)
#define AW869X_VBAT_MAX				(4500)
#define AW869X_MUL_GET_F0_RANGE			(100)
#define AW869X_MUL_GET_F0_NUM			(3)
#define AW869X_LRA_FORMULA(lra_code)		(298 * lra_code)
#define AW869X_VBAT_FORMULA(vbat_code)		(6100 * vbat_code / 256)
#define AW869X_RAM_ADDR_H(base_addr)		(base_addr >> 8)
#define AW869X_RAM_ADDR_L(base_addr)		(base_addr & 0x00FF)
#define AW869X_FIFO_AE_ADDR_H(base_addr)	((base_addr >> 1) >> 8)
#define AW869X_FIFO_AE_ADDR_L(base_addr)	((base_addr >> 1) & 0x00ff)
#define AW869X_FIFO_AF_ADDR_H(base_addr)	((base_addr - (base_addr >> 2)) >> 8)
#define AW869X_FIFO_AF_ADDR_L(base_addr)	((base_addr - (base_addr >> 2)) & 0x00ff)

/*********************************************************
 *
 * AW869XX
 *
 *********************************************************/
#define AW869XX_VBAT_MAX			(5500)
#define AW869XX_LRA_FORMULA(lra_code)		((lra_code * 678 * 1000) / \
						(1024 * 10))
#define AW869XX_VBAT_FORMULA(vbat_code)		(6100 * vbat_code / 1024)
#define AW869XX_RAM_ADDR_H(base_addr)		(base_addr >> 8)
#define AW869XX_RAM_ADDR_L(base_addr)		(base_addr & 0x00FF)
#define AW869XX_FIFO_AE_ADDR_H(base_addr)	(((base_addr >> 1) >> 4) & 0xF0)
#define AW869XX_FIFO_AE_ADDR_L(base_addr)	((base_addr >> 1) & 0x00ff)
#define AW869XX_FIFO_AF_ADDR_H(base_addr)	(((base_addr - (base_addr >> 2)) >> 8) & 0x0F)
#define AW869XX_FIFO_AF_ADDR_L(base_addr)	((base_addr - (base_addr >> 2)) & 0x00ff)
#define AW869XX_RATES				SNDRV_PCM_RATE_8000_48000
#define AW869XX_FORMATS				(SNDRV_PCM_FMTBIT_S16_LE | \
						SNDRV_PCM_FMTBIT_S24_LE | \
						SNDRV_PCM_FMTBIT_S32_LE)

/*********************************************************
 *
 * AW8671X
 *
 *********************************************************/
#define AW8671X_VBAT_MAX			(5500)
#define AW8671X_F0_FARMULA(f0_reg)		(384000 * 10 / f0_reg)
#define AW8671X_VBAT_FORMULA(vbat)		(6115 * vbat / 4096)
#define AW8671X_LRA_FORMULA(lra, d2s_gain)	((1210 * 1000 * 10 * lra) / \
						(2047 * 36 * d2s_gain))
#define AW8671X_FIFO_AE_ADDR_H(base_addr)	(((base_addr >> 1) >> 4) & 0xF0)
#define AW8671X_FIFO_AE_ADDR_L(base_addr)	((base_addr >> 1) & 0x00ff)
#define AW8671X_FIFO_AF_ADDR_H(base_addr)	((base_addr - (base_addr >> 2)) >> 8 & 0x0F)
#define AW8671X_FIFO_AF_ADDR_L(base_addr)	((base_addr - (base_addr >> 2)) & 0x00ff)
#define AW8671X_RATES				SNDRV_PCM_RATE_8000_48000
#define AW8671X_FORMATS				(SNDRV_PCM_FMTBIT_S16_LE | \
						SNDRV_PCM_FMTBIT_S24_LE | \
						SNDRV_PCM_FMTBIT_S32_LE)

/*********************************************************
 *
 * AW8692X
 *
 *********************************************************/
#define AW8692X_VBAT_MAX			(5500)
#define AW8692X_LRA_FORMULA(lra, d2s_gain)	((6075 * 100 * lra) / \
						(1024 * d2s_gain))
#define AW8692X_VBAT_FORMULA(vbat)		(5 * 1215 * vbat / 1024)
#define AW8692X_RAMADDR_H(base_addr)		(base_addr >> 8)
#define AW8692X_RAMADDR_L(base_addr)		(base_addr & 0x00FF)
#define AW8692X_BASEADDR_H(base_addr)		(base_addr >> 8)
#define AW8692X_BASEADDR_L(base_addr)		(base_addr & 0x00FF)
#define AW8692X_FIFO_AE_ADDR_H(base_addr)	(((base_addr >> 1) >> 4) & 0xF0)
#define AW8692X_FIFO_AE_ADDR_L(base_addr)	((base_addr >> 1) & 0x00ff)
#define AW8692X_FIFO_AF_ADDR_H(base_addr)	(((base_addr - (base_addr >> 2)) >> 8) & 0x0F)
#define AW8692X_FIFO_AF_ADDR_L(base_addr)	((base_addr - (base_addr >> 2)) & 0x00ff)

/*********************************************************
 *
 * Log Format
 *
 *********************************************************/
#define aw_err(format, ...) \
	pr_err("[%s][%04d]%s: " format "\n", AW_I2C_NAME, __LINE__, __func__, ##__VA_ARGS__)

#define aw_info(format, ...) \
	pr_info("[%s][%04d]%s: " format "\n", AW_I2C_NAME, __LINE__, __func__, ##__VA_ARGS__)

#define aw_dbg(format, ...) \
	pr_debug("[%s][%04d]%s: " format "\n", AW_I2C_NAME, __LINE__, __func__, ##__VA_ARGS__)

/*********************************************************
 *
 * Enum Define
 *
 *********************************************************/

enum {
	LEFT_FOPS = 1,
	RIGHT_FOPS = 2,
};
enum aw_haptic_flags {
	AW_FLAG_NONR = 0,
	AW_FLAG_SKIP_INTERRUPTS = 1,
};

enum aw_haptic_work_mode {
	AW_STANDBY_MODE = 0,
	AW_RAM_MODE = 1,
	AW_RTP_MODE = 2,
	AW_TRIG_MODE = 3,
	AW_CONT_MODE = 4,
	AW_RAM_LOOP_MODE = 5,
};

enum aw_haptic_bst_mode {
	AW_BST_BYPASS_MODE = 0,
	AW_BST_BOOST_MODE = 1,
};

enum aw_haptic_bst_pc {
	AW_BST_PC_L1 = 0,
	AW_BST_PC_L2 = 1,
};

enum aw_haptic_cont_vbat_comp_mode {
	AW_CONT_VBAT_SW_COMP_MODE = 0,
	AW_CONT_VBAT_HW_COMP_MODE = 1,
};

enum aw_haptic_ram_vbat_comp_mode {
	AW_RAM_VBAT_COMP_DISABLE = 0,
	AW_RAM_VBAT_COMP_ENABLE = 1,
};

enum aw_haptic_f0_flag {
	AW_LRA_F0 = 0,
	AW_CALI_F0 = 1,
};

enum aw_haptic_pwm_mode {
	AW_PWM_48K = 0,
	AW_PWM_24K = 1,
	AW_PWM_12K = 2,
};

enum aw_haptic_play {
	AW_PLAY_NULL = 0,
	AW_PLAY_ENABLE = 1,
	AW_PLAY_STOP = 2,
	AW_PLAY_GAIN = 8,
};

enum aw_haptic_cmd {
	AW_CMD_NULL = 0,
	AW_CMD_ENABLE = 1,
	AW_CMD_HAPTIC = 0x0f,
	AW_CMD_TP = 0x10,
	AW_CMD_SYS = 0xf0,
	AW_CMD_STOP = 255,
};

enum aw_haptic_cali_lra {
	AW_WRITE_ZERO = 0,
	AW_F0_CALI_LRA = 1,
	AW_OSC_CALI_LRA = 2,
};

enum aw_haptic_awrw_flag {
	AW_SEQ_WRITE = 0,
	AW_SEQ_READ = 1,
};

/*********************************************************
 *
 * Enum aw8692x
 *
 *********************************************************/
enum aw8692x_haptic_rck_fre {
	AW8692X_RCK_FRE_24K,
	AW8692X_RCK_FRE_32K,
	AW8692X_RCK_FRE_48K,
	AW8692X_RCK_FRE_96K,
};

enum aw8692x_haptic_trig {
	AW8692X_TRIG1,
	AW8692X_TRIG2,
	AW8692X_TRIG3,
};
#ifdef AAC_RICHTAP_SUPPORT
enum {
    RICHTAP_UNKNOWN = -1,
    RICHTAP_AW_8697 = 0x05,
};

enum {
    MMAP_BUF_DATA_VALID = 0x55,
    MMAP_BUF_DATA_FINISHED = 0xAA,
    MMAP_BUF_DATA_INVALID = 0xFF,
};

#define RICHTAP_IOCTL_GROUP 0x52
#define RICHTAP_GET_HWINFO          _IO(RICHTAP_IOCTL_GROUP, 0x03)
#define RICHTAP_SET_FREQ            _IO(RICHTAP_IOCTL_GROUP, 0x04)
#define RICHTAP_SETTING_GAIN        _IO(RICHTAP_IOCTL_GROUP, 0x05)
#define RICHTAP_OFF_MODE            _IO(RICHTAP_IOCTL_GROUP, 0x06)
#define RICHTAP_TIMEOUT_MODE        _IO(RICHTAP_IOCTL_GROUP, 0x07)
#define RICHTAP_RAM_MODE            _IO(RICHTAP_IOCTL_GROUP, 0x08)
#define RICHTAP_RTP_MODE            _IO(RICHTAP_IOCTL_GROUP, 0x09)
#define RICHTAP_STREAM_MODE         _IO(RICHTAP_IOCTL_GROUP, 0x0A)
#define RICHTAP_UPDATE_RAM          _IO(RICHTAP_IOCTL_GROUP, 0x10)
#define RICHTAP_GET_F0              _IO(RICHTAP_IOCTL_GROUP, 0x11)
#define RICHTAP_STOP_MODE           _IO(RICHTAP_IOCTL_GROUP, 0x12)

#define RICHTAP_MMAP_BUF_SIZE   1000
#define RICHTAP_MMAP_PAGE_ORDER   2
#define RICHTAP_MMAP_BUF_SUM    16

#pragma pack(4)
struct mmap_buf_format {
    uint8_t status;
    uint8_t bit;
    int16_t length;
    uint32_t reserve;
    struct mmap_buf_format *kernel_next;
    struct mmap_buf_format *user_next;
    uint8_t data[RICHTAP_MMAP_BUF_SIZE];
};
#pragma pack()

#endif

/*********************************************************
 *
 * Struct Define
 *
 *********************************************************/
struct trig {
	/* AW869X */
	uint8_t enable;
	uint8_t dual_edge;
	uint8_t frist_seq;
	uint8_t second_seq;
	uint8_t default_level;

	/* AW869XX AW8671X AW8692X */
	uint8_t trig_brk;
	uint8_t trig_bst;
	uint8_t trig_level;
	uint8_t trig_polar;
	uint8_t pos_enable;
	uint8_t neg_enable;
	uint8_t pos_sequence;
	uint8_t neg_sequence;
};

struct aw_haptic_ram {
	uint32_t len;
	uint32_t check_sum;
	uint32_t base_addr;
	uint8_t ram_num;
	uint8_t version;
	uint8_t ram_shift;
	uint8_t baseaddr_shift;
};

struct aw_haptic_ctr {
	uint8_t cnt;
	uint8_t cmd;
	uint8_t play;
	uint8_t loop;
	uint8_t gain;
	uint8_t wavseq;
	struct list_head list;
};

struct aw_i2c_info {
	uint32_t flag;
	uint32_t reg_num;
	uint8_t *reg_data;
};

struct aw_haptic_audio {
	int tz_num;
	int tz_cnt_thr;
	int tz_cnt_max;
	int tz_high_num;
	int delay_val;
	int timer_val;
	uint32_t uevent_report_flag;
	uint32_t hap_cnt_outside_tz;
	uint32_t hap_cnt_max_outside_tz;
	struct mutex lock;
	struct hrtimer timer;
	struct work_struct work;
	struct list_head list;
	struct list_head ctr_list;
	struct aw_haptic_ctr ctr;
};

struct aw_haptic_dts_info {
	/* COMMON */
	uint8_t mode;
	uint8_t max_bst_vol;
	uint8_t f0_cali_percent;
	uint8_t bst_vol_default;
	uint8_t duration_time[3];
	uint32_t f0_pre;

	/* AW869X */
	uint8_t tset;
	uint8_t r_spare;
	uint8_t cont_drv_lvl;
	uint8_t cont_num_brk;
	uint8_t cont_drv_lvl_ov;
	uint8_t bstdbg[6];
	uint8_t bemf_config[4];
	uint8_t f0_trace_parameter[4];
	uint32_t f0_coeff;
	uint32_t cont_td;
	uint32_t cont_zc_thr;

	/* AW869XX */
	uint8_t bstcfg[5];
	uint8_t sine_array[4];

	/* AW869XX AW8671X AW8692X */
	uint8_t d2s_gain;
	uint8_t brk_bst_md;
	uint8_t bst_vol_ram;
	uint8_t bst_vol_rtp;
	uint8_t cont_tset;
	uint8_t cont_drv1_lvl;
	uint8_t cont_drv2_lvl;
	uint8_t cont_wait_num;
	uint8_t cont_brk_time;
	uint8_t cont_bemf_set;
	uint8_t cont_brk_gain;
	uint8_t cont_drv1_time;
	uint8_t cont_drv2_time;
	uint8_t cont_drv_width;
	uint8_t cont_track_margin;
	uint8_t cont_bst_brk_gain;
	uint8_t trig_cfg[24];
	bool is_enabled_auto_bst;
	bool is_enabled_i2s;
	bool is_enabled_one_wire;
};

struct aw_haptic {
	/* AW869X */
	uint32_t interval_us;

	/* AW869XX */
	bool i2s_config;
	bool rtp_init;
	bool ram_init;
	aw_snd_soc_codec_t *codec;

	/* COMMON */
	uint8_t flags;
	uint8_t bst_pc;
	uint8_t play_mode;
	uint8_t auto_boost;
	uint8_t max_pos_beme;
	uint8_t max_neg_beme;
	uint8_t activate_mode;
	uint8_t ram_vbat_comp;
	uint8_t rtp_routine_on;
	uint8_t seq[AW_SEQUENCER_SIZE];
	uint8_t loop[AW_SEQUENCER_SIZE];

	int vmax;
	int gain;
	int rate;
	int width;
	int state;
	int index;
	int chipid;
	int sysclk;
	int irq_gpio;
	int duration;
	int amplitude;
	int reset_gpio;

	uint32_t f0;
	uint32_t lra;
	uint32_t vbat;
	uint32_t pre_f0;
	uint32_t cont_f0;
	uint32_t rtp_cnt;
	uint32_t rtp_len;
	uint32_t gun_type;
	uint32_t bullet_nr;
	uint32_t theory_time;
	uint32_t f0_cali_data;
	uint32_t rtp_file_num;
	uint32_t timeval_flags;
	uint32_t osc_cali_data;
	uint64_t microsecond;

	cdev_t vib_dev;

	ktime_t kend;
	ktime_t kstart;
	ktime_t kcurrent_time;
	ktime_t kpre_enter_time;

	struct device *dev;
	struct i2c_client *i2c;
	struct mutex lock;
	struct hrtimer timer;
	struct mutex rtp_lock;
	struct work_struct rtp_work;
	struct delayed_work ram_work;
	struct work_struct vibrator_work;
	struct workqueue_struct *work_queue;
	struct aw_haptic_ram ram;
	struct aw_haptic_dts_info info;
	struct aw_haptic_audio haptic_audio;
	struct pinctrl *pinctrl;
	struct pinctrl_state *pinctrl_state;
	struct aw_haptic_func *func;
	struct aw_i2c_info i2c_info;
	struct trig trig[AW_TRIG_NUM];
#ifdef AAC_RICHTAP_SUPPORT
	uint8_t *rtp_ptr;
	struct mmap_buf_format *start_buf;
	struct mmap_buf_format *curr_buf;
	struct work_struct richtap_rtp_work;
	struct work_struct richtap_stop_work;
	int16_t pos;
	atomic_t richtap_rtp_mode;
#endif
};

struct aw_haptic_container {
	int len;
	uint8_t data[];
};

struct aw_haptic_func {
	int (*get_f0)(struct aw_haptic *);
	int (*creat_node)(struct aw_haptic *);
	int (*get_irq_state)(struct aw_haptic *);
	int (*check_qualify)(struct aw_haptic *);
	int (*juge_rtp_going)(struct aw_haptic *);
	int (*container_update)(struct aw_haptic *,
				struct aw_haptic_container *);
	void (*play_stop)(struct aw_haptic *);
	void (*get_vbat)(struct aw_haptic *);
	void (*cont_config)(struct aw_haptic *);
	void (*offset_cali)(struct aw_haptic *);
	void (*read_f0)(struct aw_haptic *);
	void (*play_go)(struct aw_haptic *, bool);
	void (*ram_init)(struct aw_haptic *, bool);
	void (*set_bst_peak_cur)(struct aw_haptic *);
	void (*get_lra_resistance)(struct aw_haptic *);
	void (*set_pwm)(struct aw_haptic *, uint8_t);
	void (*set_gain)(struct aw_haptic *, uint8_t);
	void (*enable_gain)(struct aw_haptic *);
	void (*play_mode)(struct aw_haptic *, uint8_t);
	void (*set_bst_vol)(struct aw_haptic *, uint8_t);
	void (*set_repeat_seq)(struct aw_haptic *, uint8_t);
	void (*auto_bst_enable)(struct aw_haptic *, uint8_t);
	void (*vbat_mode_config)(struct aw_haptic *, uint8_t);
	void (*set_wav_seq)(struct aw_haptic *, uint8_t, uint8_t);
	void (*set_wav_loop)(struct aw_haptic *, uint8_t, uint8_t);
	void (*set_rtp_data)(struct aw_haptic *, uint8_t *, uint32_t);
	void (*protect_config)(struct aw_haptic *, uint8_t, uint8_t);
	void (*parse_dt)(struct device *, struct aw_haptic *,
			 struct device_node *);
	void (*trig_init)(struct aw_haptic *);
	void (*irq_clear)(struct aw_haptic *);
	void (*set_ram_addr)(struct aw_haptic *);
	void (*misc_para_init)(struct aw_haptic *);
	void (*interrupt_setup)(struct aw_haptic *);
	void (*set_rtp_aei)(struct aw_haptic *, bool);
	void (*upload_lra)(struct aw_haptic *, uint32_t);
	void (*get_wav_seq)(struct aw_haptic *, uint32_t);
	void (*bst_mode_config)(struct aw_haptic *, uint8_t);
	void (*get_first_wave_addr)(struct aw_haptic *, uint8_t *);
	size_t (*get_wav_loop)(struct aw_haptic *, char *);
	ssize_t (*get_ram_data)(struct aw_haptic *, char *);
	ssize_t (*get_reg)(struct aw_haptic *, ssize_t, char *);
	uint8_t (*get_prctmode)(struct aw_haptic *);
	uint8_t (*get_trim_lra)(struct aw_haptic *);
	uint8_t (*get_glb_state)(struct aw_haptic *);
	uint8_t (*get_osc_status)(struct aw_haptic *);
	uint8_t (*rtp_get_fifo_afs)(struct aw_haptic *);
	uint8_t (*rtp_get_fifo_afi)(struct aw_haptic *);
	uint64_t (*get_theory_time)(struct aw_haptic *);

#ifdef AW_SND_SOC_CODEC
	int (*snd_soc_init)(struct device *);
#endif
};

/*********************************************************
 *
 * Function Call
 *
 *********************************************************/
extern char *aw_ram_name;
extern char aw_rtp_name[][AW_RTP_NAME_MAX];
extern struct aw_haptic_func aw869x_func_list;
extern struct aw_haptic_func aw869xx_func_list;
extern struct aw_haptic_func aw8671x_func_list;
extern struct aw_haptic_func aw8692x_func_list;
extern struct pm_qos_request aw_pm_qos_req_vb;
extern struct aw_haptic_container *aw_rtp;

extern int i2c_r_bytes(struct aw_haptic *, uint8_t, uint8_t *, uint32_t);
extern int i2c_w_bytes(struct aw_haptic *, uint8_t, uint8_t *, uint32_t);
extern int i2c_w_bits(struct aw_haptic *, uint8_t, uint32_t, uint8_t);

#endif
