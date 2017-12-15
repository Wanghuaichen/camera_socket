
#include "AD7793.h"

extern __IO	int32_t			CH_Sample[16];
extern __IO	uint8_t				CH_Sensor_Sel[9];
extern __IO uint8_t       CH_Sampling[9];


//由通道值4-15得到7793的片选地址
uint8_t AD7793CS_addr(uint8_t Channel)
{
	uint8_t chipSelect = 0x80;
	switch(Channel)
	{
		case 5:	 case 4:  chipSelect = 0x82; break;
		case 7:  case 6:  
			chipSelect = 0x81; 
		break;
		case 9:  case 8:  chipSelect = 0x83; break;
		case 11: case 10: chipSelect = 0x84; break;
		case 13: case 12: chipSelect = 0x85; break;
		case 15: case 14: chipSelect = 0x86; break;
		default : chipSelect = 0x80; break;
	}
	return (chipSelect);
}
//由通道值4-15得到7793内部的哪个通道被AD
uint8_t AD7793_Internal_CH(uint8_t Channel)
{
	uint8_t Int_Channel = 0x00;
	if(Channel > 15 || Channel < 4)
		return AD7793_CH_AIN1M_AIN1M;
	if((Channel%2) == 0)	//4,6,8,10,12,14
		Int_Channel = AD7793_CH_AIN1P_AIN1M;
	else									//5.7,9,11,13,15
		Int_Channel = AD7793_CH_AIN2P_AIN2M;
	return (Int_Channel);
}

// uint32_t Debugcode1 ;
void AD7793_Config(void)
{
//**********************7793 0*************************//	
		Delayms(10);
		AD7793_CS_L;      
		AD7793_SetChannel(AD7793_CH_AIN1P_AIN1M);
		AD7793_SetGain(AD7793_GAIN_1);
		AD7793_SetUNIPOLAR(1);
		AD7793_SetMode(AD7793_MODE_CONT);
		AD7793_CS_H;
	
//**********************7793 1*************************//
		Delayms(10);
		AD7793_CS1_L;
		AD7793_SetChannel(AD7793_CH_AIN1P_AIN1M);
		AD7793_SetGain(AD7793_GAIN_1);
		AD7793_SetUNIPOLAR(1);
		AD7793_SetMode(AD7793_MODE_CONT);
		AD7793_CS1_H;	
}
/***************************************************************************//**
 * @brief check if the device is present and Initialize AD7793.
 *
 * @return  None.
*******************************************************************************/
void AD7793_Init(void)
{
		AD7793_CS_L;
		AD7793_CS1_L;	
		AD7793_Reset();		//复位所有器件
		AD7793_CS_H;
		AD7793_CS1_H;	

		AD7793_CS_L;
		if((AD7793_GetRegisterValue(AD7793_REG_ID, 1) & 0x0F) == AD7793_ID)
		{
				AD7793_SetMode(AD7793_MODE_PWRDN);
				AD7793_SetFURate(AD7793_RATE_470Hz);
		}
		AD7793_CS_H;
		
		AD7793_CS1_L;
		if((AD7793_GetRegisterValue(AD7793_REG_ID, 1) & 0x0F) == AD7793_ID)
		{
				AD7793_SetMode(AD7793_MODE_PWRDN);
				AD7793_SetFURate(AD7793_RATE_470Hz);
		}
		AD7793_CS1_H;	
}

/***************************************************************************//**
 * @brief Sends 32 consecutive 1's on SPI in order to reset the part.
 *
 * @return  None.    
*******************************************************************************/
void AD7793_Reset(void)
{
	uint8_t dataToSend[4] = {0xff, 0xff, 0xff, 0xff};
	
	Soft_SPI_Transfer(dataToSend,3);
}
/***************************************************************************//**
 * @brief Reads the value of the selected register
 *
 * @param regAddress - The address of the register to read.
 * @param size - The size of the register to read.
 *
 * @return data - The value of the selected register register.
*******************************************************************************/
uint32_t AD7793_GetRegisterValue(uint8_t regAddress,
                                 uint8_t size)
{
	uint8_t  data[4]      = {0x00, 0x00, 0x00, 0x00};//One Byte Comm register,Three Bytes data value
	uint32_t receivedData = 0x00;
  uint8_t  i            = 0x00;
  
	data[0] = AD7793_COMM_READ | AD7793_COMM_ADDR(regAddress);
	Soft_SPI_Transfer(data, size);
	for(i = 0;i < size; i ++)
  {
		receivedData = (receivedData << 8) + data[i+1];
	}
	return (receivedData);
}
/***************************************************************************//**
 * @brief Writes the value to the register
 *
 * @param -  regAddress - The address of the register to write to.
 * @param -  regValue - The value to write to the register.
 * @param -  size - The size of the register to write.(1--3)
 *
 * @return  None.
*******************************************************************************/
void AD7793_SetRegisterValue(uint8_t 	regAddress,
                             uint32_t regValue, 
                             uint8_t 	size)
{
	uint8_t  data[4]      = {0x00, 0x00, 0x00, 0x00};//One Byte Comm register,Three Bytes data value
	uint8_t* dataPointer  = (uint8_t*)&regValue;
  uint8_t  bytesNr      = size;
   
  data[0] = AD7793_COMM_WRITE | AD7793_COMM_ADDR(regAddress);
  while(bytesNr > 0)
  {
		data[bytesNr] = *dataPointer;
		dataPointer ++;
		bytesNr --;
	}
	Soft_SPI_Transfer(data, size);
}
/***************************************************************************//**
 * @brief  Waits for RDY pin to go low.
 *
 * @return None.
*******************************************************************************/
void AD7793_WaitRdyGoLow(void)
{
	if(AD7793_RDY_STATE)//数据未准备好
	{
		AD_delay(200);
		if(AD7793_RDY_STATE)
		Delayms(2);		// 1000 / 470 = 2.12ms 延时一个周期
// 		AD_delay(200);
	}
//   while( AD7793_RDY_STATE )
//   {}
}

/***************************************************************************//**
 * @brief Sets the operating mode of AD7793.
 *
 * @param mode - Mode of operation.
 *
 * @return  None.    
*******************************************************************************/
void AD7793_SetMode(uint8_t mode)
{
    uint32_t command;
    
    command = AD7793_GetRegisterValue(AD7793_REG_MODE,2);
    command &= ~AD7793_MODE_SEL(0xFF);
    command |= AD7793_MODE_SEL(mode);
    AD7793_SetRegisterValue(AD7793_REG_MODE,command,2);
	command = AD7793_GetRegisterValue(AD7793_REG_MODE,2);
	command++;
}

/***************************************************************************//**
 * @brief Sets the Filter Update Rate of AD7793.
 *
 * @param RATE - RATE of operation.
 *
 * @return  None.    
*******************************************************************************/
void AD7793_SetFURate(uint8_t RATE)
{
		uint32_t command;
		
		command = AD7793_GetRegisterValue(AD7793_REG_MODE,2);
		command &= ~AD7793_MODE_RATE(0xFF);
		command |= AD7793_MODE_RATE(RATE);
		AD7793_SetRegisterValue(AD7793_REG_MODE,command,2);
}

/***************************************************************************//**
 * @brief Sets the Unipolar/Bipolar of AD7793.
 *
 * @param  unipolarEN - Unipolar ENABLE operation.
 *
 * @return  None.    
*******************************************************************************/
void AD7793_SetUNIPOLAR(uint8_t unipolarEN)
{
    uint32_t command;
    
    command = AD7793_GetRegisterValue(AD7793_REG_CONF,2);
		if(unipolarEN == 1)
    {
			command &= ~AD7793_CONF_UNIPOLAR;
			command |= AD7793_CONF_UNIPOLAR;
		}
		else
		{
			command &= ~AD7793_CONF_UNIPOLAR;
		}
    AD7793_SetRegisterValue(AD7793_REG_CONF,command,2);
}

/***************************************************************************//**
 * @brief Selects the channel of AD7793.
 *
 * @param  channel - ADC channel selection.
 *
 * @return  None.    
*******************************************************************************/
void AD7793_SetChannel(uint8_t channel)
{
    uint32_t command;
    
    command = AD7793_GetRegisterValue(AD7793_REG_CONF,2);
    command &= ~AD7793_CONF_CHAN(0xFF);
    command |= AD7793_CONF_CHAN(channel);
    AD7793_SetRegisterValue(AD7793_REG_CONF,command,2);
}

/***************************************************************************//**
 * @brief  Sets the gain of the In-Amp.
 *
 * @param  gain - Gain.
 *
 * @return  None.    
*******************************************************************************/
void AD7793_SetGain(uint32_t gain)
{
    uint32_t command;
    
    command = AD7793_GetRegisterValue(AD7793_REG_CONF,2);
    command &= ~AD7793_CONF_GAIN(0xFF);
    command |= AD7793_CONF_GAIN(gain);
    AD7793_SetRegisterValue(AD7793_REG_CONF,command,2); // CS is modified by SPI read/write functions.
}
/***************************************************************************//**
 * @brief Sets the excitation currents for the ADC.
 *
 * @param DIR - AD7793_IEXCDIR.
 * @param EN - AD7793_IEXCEN.
 *               Example: AD7793_DIR_IEXC1_IOUT1_IEXC2_IOUT2
 *                        AD7793_EN_IXCEN_10uA
 *
 * @return None.    
*******************************************************************************/
void AD7793_SetIEXC(uint8_t DIR, uint8_t EN)
{
	uint32_t command;
	
	command = AD7793_IEXCDIR(DIR) | AD7793_IEXCEN(EN);
	
  AD7793_SetRegisterValue(AD7793_REG_IO, command, 1);
}
/***************************************************************************//**
 * @brief Sets the reference source for the ADC.
 *
 * @param type - Type of the reference.
 *               Example: AD7793_REFSEL_EXT	- External Reference Selected
 *                        AD7793_REFSEL_INT	- Internal Reference Selected.
 *
 * @return None.    
*******************************************************************************/
void AD7793_SetIntReference(uint8_t type)
{
    uint32_t command = 0;
    
    command = AD7793_GetRegisterValue(AD7793_REG_CONF,2);
    command &= ~AD7793_CONF_REFSEL(AD7793_REFSEL_INT);
    command |= AD7793_CONF_REFSEL(type);
    AD7793_SetRegisterValue(AD7793_REG_CONF,command,2);
}

/***************************************************************************//**
 * @brief Performs the given calibration to the specified channel.
 *
 * @param mode - Calibration type.
 * @param channel - Channel to be calibrated.
 *
 * @return none.
*******************************************************************************/
void AD7793_Calibrate(uint8_t mode, uint8_t In_channel)
{
    uint16_t oldRegValue = 0x0;
    uint16_t newRegValue = 0x0;
    
    AD7793_SetChannel(In_channel);
    oldRegValue &= AD7793_GetRegisterValue(AD7793_REG_MODE, 2);
    oldRegValue &= ~AD7793_MODE_SEL(0x7);
    newRegValue = oldRegValue | AD7793_MODE_SEL(mode);
//    ADI_PART_CS_LOW; 
    AD7793_SetRegisterValue(AD7793_REG_MODE, newRegValue, 2);
    AD7793_WaitRdyGoLow();
//    ADI_PART_CS_HIGH;
    
}

/***************************************************************************//**
 * @brief Returns the result of a single conversion.
 *
 * @return regData - Result of a single analog-to-digital conversion.
*******************************************************************************/
uint32_t AD7793_SingleConversion(void)
{
    uint32_t command = 0x0;
    uint32_t regData = 0x0;
    
    command  = AD7793_MODE_SEL(AD7793_MODE_SINGLE);
    AD7793_SetRegisterValue(AD7793_REG_MODE,command,2);
    AD7793_WaitRdyGoLow();
    regData = AD7793_GetRegisterValue(AD7793_REG_DATA,3);

    return(regData);
}

/***************************************************************************//**
 * @brief Returns the average of several conversion results.
 *
 * @return samplesAverage - The average of the conversion results.
*******************************************************************************/
uint32_t AD7793_ContinuousReadAvg(uint8_t sampleNumber)
{
    uint32_t samplesAverage = 0x0;
    uint32_t command        = 0x0;
    uint8_t  count          = 0x0;
    
    command = AD7793_MODE_SEL(AD7793_MODE_CONT);
//    ADI_PART_CS_LOW;
    AD7793_SetRegisterValue(AD7793_REG_MODE,
                            command, 
                            2);// CS is not modified by SPI read/write functions.
    for(count = 0;count < sampleNumber;count ++)
    {
        AD7793_WaitRdyGoLow();
        samplesAverage += AD7793_GetRegisterValue(AD7793_REG_DATA, 3);  // CS is not modified by SPI read/write functions.
    }
//    ADI_PART_CS_HIGH;
    samplesAverage = samplesAverage / sampleNumber;
    
    return(samplesAverage);
}
static void AD_delay(u8 time)
{
	while(time)
		time--;
}
