
#ifndef __AD7793_H
#define __AD7793_H

#include "soft_spi.h"

/* AD7793 GPIO */
#define AD7793_RDY_STATE    GPIO_ReadInputDataBit(SOFT_SPI_MISO_GPIO_PORT, SOFT_SPI_MISO_PIN)


/*AD7793 Registers*/
#define AD7793_REG_COMM			0 /* Communications Register(WO, 8-bit) */
#define AD7793_REG_STAT	    0 /* Status Register	    	(RO, 8-bit) */
#define AD7793_REG_MODE	    1 /* Mode Register	     		(RW, 16-bit */
#define AD7793_REG_CONF	    2 /* Configuration Register (RW, 16-bit)*/
#define AD7793_REG_DATA	    3 /* Data Register	     		(RO, 16-/24-bit) */
#define AD7793_REG_ID	    	4 /* ID Register	     			(RO, 8-bit) */
#define AD7793_REG_IO	    	5 /* IO Register	     			(RW, 8-bit) */
#define AD7793_REG_OFFSET   6 /* Offset Register	    	(RW, 24-bit */
#define AD7793_REG_FULLSALE	7 /* Full-Scale Register		(RW, 24-bit */

/* Communications Register Bit Designations (AD7793_REG_COMM) */
#define AD7793_COMM_WEN			(1 << 7) 						/* Write Enable */
#define AD7793_COMM_WRITE		(0 << 6) 						/* Write Operation */
#define AD7793_COMM_READ    (1 << 6) 						/* Read Operation */
#define AD7793_COMM_ADDR(x)	(((x) & 0x7) << 3)	/* Register Address */
#define AD7793_COMM_CREAD		(1 << 2) 						/* Continuous Read of Data Register */

/* Status Register Bit Designations (AD7793_REG_STAT) */
#define AD7793_STAT_RDY		(1 << 7) /* Ready */
#define AD7793_STAT_ERR		(1 << 6) /* Error (Overrange, Underrange) */
#define AD7793_STAT_CH3		(1 << 2) /* Channel 3 */
#define AD7793_STAT_CH2		(1 << 1) /* Channel 2 */
#define AD7793_STAT_CH1		(1 << 0) /* Channel 1 */

/* Mode Register Bit Designations (AD7793_REG_MODE) */
#define AD7793_MODE_SEL(x)		(((x) & 0x7) << 13)	/* Operation Mode Select */
#define AD7793_MODE_CLKSRC(x)	(((x) & 0x3) << 6) 	/* ADC Clock Source Select */
#define AD7793_MODE_RATE(x)		((x) & 0xF) 				/* Filter Update Rate Select */

/* AD7793_MODE_SEL(x) options */
#define AD7793_MODE_CONT		     0 /* Continuous Conversion Mode */
#define AD7793_MODE_SINGLE		 	 1 /* Single Conversion Mode */
#define AD7793_MODE_IDLE				 2 /* Idle Mode */
#define AD7793_MODE_PWRDN				 3 /* Power-Down Mode */
#define AD7793_MODE_CAL_INT_ZERO 4 /* Internal Zero-Scale Calibration */
#define AD7793_MODE_CAL_INT_FULL 5 /* Internal Full-Scale Calibration */
#define AD7793_MODE_CAL_SYS_ZERO 6 /* System Zero-Scale Calibration */
#define AD7793_MODE_CAL_SYS_FULL 7 /* System Full-Scale Calibration */

/* AD7793_MODE_CLKSRC(x) options */
#define AD7793_CLK_INT				0 /* Internal 64 kHz Clk not available at the CLK pin */
#define AD7793_CLK_INT_CO			1 /* Internal 64 kHz Clk available at the CLK pin */
#define AD7793_CLK_EXT				2 /* External 64 kHz Clock */
#define AD7793_CLK_EXT_DIV2		3 /* External Clock divided by 2 */

/* AD7793_MODE_RATE(x) options */
#define AD7793_RATE_xHz						0
#define AD7793_RATE_470Hz					1
#define AD7793_RATE_242Hz					2
#define AD7793_RATE_123Hz					3
#define AD7793_RATE_62Hz					4
#define AD7793_RATE_50Hz					5
#define AD7793_RATE_39Hz					6
#define AD7793_RATE_33_2Hz				7
#define AD7793_RATE_19_6Hz				8
#define AD7793_RATE_16_7Hz_80dB		9
#define AD7793_RATE_16_7Hz_65dB		10
#define AD7793_RATE_12_5Hz				11
#define AD7793_RATE_10Hz					12
#define AD7793_RATE_8_33Hz				13
#define AD7793_RATE_6_25Hz				14
#define AD7793_RATE_4_17Hz				15

/* Configuration Register Bit Designations (AD7793_REG_CONF) */
#define AD7793_CONF_VBIAS(x)  (((x) & 0x3) << 14) 	/* Bias Voltage Generator Enable */
#define AD7793_CONF_BO_EN	  	(1 << 13) 						/* Burnout Current Enable */
#define AD7793_CONF_UNIPOLAR  (1 << 12) 						/* Unipolar/Bipolar Enable */
#define AD7793_CONF_BOOST	  	(1 << 11) 						/* Boost Enable */
#define AD7793_CONF_GAIN(x)	  (((x) & 0x7) << 8) 		/* Gain Select */
#define AD7793_CONF_REFSEL(x) (((x) & 0x1) << 7) 		/* INT/EXT Reference Select */
#define AD7793_CONF_BUF		  	(1 << 4) 							/* Buffered Mode Enable */
#define AD7793_CONF_CHAN(x)	  ((x) & 0x7) 					/* Channel select */

/* AD7793_CONF_GAIN(x) options */
#define AD7793_GAIN_1       0
#define AD7793_GAIN_2       1
#define AD7793_GAIN_4       2
#define AD7793_GAIN_8       3
#define AD7793_GAIN_16      4
#define AD7793_GAIN_32      5
#define AD7793_GAIN_64      6
#define AD7793_GAIN_128     7

/* AD7793_CONF_REFSEL(x) options */
#define AD7793_REFSEL_INT   1	/* Internal Reference Selected. */
#define AD7793_REFSEL_EXT   0	/* External Reference Applied between REFIN(+) and REFIN(?. */

/* AD7793_CONF_CHAN(x) options */
#define AD7793_CH_AIN1P_AIN1M		0 /* AIN1(+) - AIN1(-) */
#define AD7793_CH_AIN2P_AIN2M		1 /* AIN2(+) - AIN2(-) */
#define AD7793_CH_AIN3P_AIN3M		2 /* AIN3(+) - AIN3(-) */
#define AD7793_CH_AIN1M_AIN1M		3 /* AIN1(-) - AIN1(-) */
#define AD7793_CH_TEMP					6	/* Temp Sensor */
#define AD7793_CH_AVDD_MONITOR	7 /* AVDD Monitor */

/* ID Register Bit Designations (AD7793_REG_ID) */
#define AD7793_ID					0xB
#define AD7793_ID_MASK		0xF

/* IO (Excitation Current Sources) Register Bit Designations (AD7793_REG_IO) */
#define AD7793_IEXCDIR(x)	(((x) & 0x3) << 2)
#define AD7793_IEXCEN(x)	(((x) & 0x3) << 0)

/* AD7793_IEXCDIR(x) options*/
#define AD7793_DIR_IEXC1_IOUT1_IEXC2_IOUT2	0  /* IEXC1 connect to IOUT1, IEXC2 connect to IOUT2 */
#define AD7793_DIR_IEXC1_IOUT2_IEXC2_IOUT1	1  /* IEXC1 connect to IOUT2, IEXC2 connect to IOUT1 */
#define AD7793_DIR_IEXC1_IEXC2_IOUT1				2  /* Both current sources IEXC1,2 connect to IOUT1  */
#define AD7793_DIR_IEXC1_IEXC2_IOUT2				3  /* Both current sources IEXC1,2 connect to IOUT2 */

/* AD7793_IEXCEN(x) options*/
#define AD7793_EN_IXCEN_10uA				1  /* Excitation Current 10uA */
#define AD7793_EN_IXCEN_210uA				2  /* Excitation Current 210uA */
#define AD7793_EN_IXCEN_1mA					3  /* Excitation Current 1mA */

uint8_t AD7793CS_addr(uint8_t Channel);
uint8_t AD7793_Internal_CH(uint8_t Channel);

void AD7793_Config(void);

/* check if the device is present and Initialize AD7793 */
void AD7793_Init(void);

/* Sends 32 consecutive 1's on SPI in order to reset the part. */
void AD7793_Reset(void);

/* Reads the value of the selected register. */
uint32_t AD7793_GetRegisterValue(uint8_t regAddress,
																 uint8_t size);

/* Writes a value to the register. */
void AD7793_SetRegisterValue(uint8_t regAddress, uint32_t regValue, uint8_t size);

/* Waits for RDY pin to go low. */
void AD7793_WaitRdyGoLow(void);

/* Sets the operating mode of AD7793. */
void AD7793_SetMode(uint8_t mode);

/*Sets the Filter Update Rate of AD7793. */
void AD7793_SetFURate(uint8_t RATE);

/*Sets the Unipolar/Bipolar of AD7793.*/
void AD7793_SetUNIPOLAR(uint8_t unipolarEN);

/* Selects the channel of AD7793. */
void AD7793_SetChannel(uint8_t channel);

/* Sets the gain of the In-Amp. */
void AD7793_SetGain(uint32_t gain);

/* Sets the excitation currents for the ADC. */
void AD7793_SetIEXC(uint8_t DIR, uint8_t EN);

/* Sets the reference source for the ADC. */
void AD7793_SetIntReference(uint8_t type);

/* Performs the given calibration to the specified channel. */
void AD7793_Calibrate(uint8_t mode, uint8_t In_channel);

/* Returns the result of a single conversion. */
uint32_t AD7793_SingleConversion(void);

/* Returns the average of several conversion results. */
uint32_t AD7793_ContinuousReadAvg(uint8_t sampleNumber);

static void AD_delay(u8 time);

#endif	// _AD7793_H_

