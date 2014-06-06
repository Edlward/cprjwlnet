/*
 * halSpi.c
 *
 *  Created on: 2014��3��27��
 *      Author: Administrator
 */

#include <includes.h>

static void io_port_init(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;
	RCC_AHB1PeriphClockCmd(
			RCC_AHB1Periph_GPIOB | RCC_AHB1Periph_GPIOE, ENABLE);

	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;

	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_8;
	GPIO_Init(GPIOB, &GPIO_InitStructure);

	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_9;
	GPIO_Init(GPIOB, &GPIO_InitStructure);

	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0;
	GPIO_Init(GPIOE, &GPIO_InitStructure);

	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN;
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_7;
	GPIO_Init(GPIOB, &GPIO_InitStructure);

	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_6;
	GPIO_Init(GPIOB, &GPIO_InitStructure);
	{
		EXTI_InitTypeDef EXTI_InitStructure;
		NVIC_InitTypeDef NVIC_InitStructure;

		RCC_APB2PeriphClockCmd(RCC_APB2Periph_SYSCFG, ENABLE);

		/* Enable the EXTI0 Interrupt */
		NVIC_InitStructure.NVIC_IRQChannel = EXTI9_5_IRQn;
		NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 1;
		NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;
		NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
		NVIC_Init(&NVIC_InitStructure);

		/* Configure  EXTI  */
		EXTI_InitStructure.EXTI_Line = EXTI_Line7;
		EXTI_InitStructure.EXTI_Mode = EXTI_Mode_Interrupt;
		EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Falling;
		EXTI_InitStructure.EXTI_LineCmd = ENABLE;
		EXTI_ClearITPendingBit(EXTI_Line7);
		EXTI_Init(&EXTI_InitStructure);

		SYSCFG_EXTILineConfig(EXTI_PortSourceGPIOB, EXTI_PinSource7);
	}
}

void halWait(uint16_t timeout)
{
	do
	{
		timeout++;
		timeout--;
		timeout++;
		timeout--;
		timeout++;
		timeout--;
		timeout++;
		timeout--;
		timeout++;
		timeout--;
		timeout++;
		timeout--;
	} while (--timeout);
}

void SpiInit(void)
{
	/* SPI3 config */
	GPIO_InitTypeDef GPIO_InitStructure;
	SPI_InitTypeDef SPI_InitStructure;

	/* Enable SPI2 Periph clock */
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOB, ENABLE);
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_SPI3, ENABLE);

	GPIO_PinAFConfig(GPIOB, GPIO_PinSource3, GPIO_AF_SPI3);
	GPIO_PinAFConfig(GPIOB, GPIO_PinSource4, GPIO_AF_SPI3);
	GPIO_PinAFConfig(GPIOB, GPIO_PinSource5, GPIO_AF_SPI3);

	/* Configure SPI2 pins: PB10-SCK, PC2-RF_MISO() and PC3-MOSI */
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_DOWN;

	/*!< SPI SCK pin configuration */
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_3 | GPIO_Pin_4 | GPIO_Pin_5;
	GPIO_Init(GPIOB, &GPIO_InitStructure);

	SPI_InitStructure.SPI_Direction = SPI_Direction_2Lines_FullDuplex;
	SPI_InitStructure.SPI_Mode = SPI_Mode_Master;
	SPI_InitStructure.SPI_DataSize = SPI_DataSize_8b;
	SPI_InitStructure.SPI_CPOL = SPI_CPOL_Low;
	SPI_InitStructure.SPI_CPHA = SPI_CPHA_1Edge;
	SPI_InitStructure.SPI_NSS = SPI_NSS_Soft;
	SPI_InitStructure.SPI_BaudRatePrescaler = SPI_BaudRatePrescaler_64;
	SPI_InitStructure.SPI_FirstBit = SPI_FirstBit_MSB;
	SPI_InitStructure.SPI_CRCPolynomial = 7;
	SPI_Init(SPI3, &SPI_InitStructure);

	/* Enable SPI_MASTER */
	SPI_Cmd(SPI3, ENABLE);
	SPI_CalculateCRC(SPI3, DISABLE);
}

/*****************************************************************************************
 //��������rf_init()
 //���룺��
 //�������
 //����������SPI��ʼ������
 /*****************************************************************************************/
void rf_init(void)
{
	io_port_init();
	halRfSyncPinINTCmd(DISABLE);
	SpiInit();
	rt_delay_us(200);
	Power_Up_Reset_CC1100();
	halRfWriteRfSettings();
}

//*****************************************************************************************
//��������SpisendByte(uint8_t dat)
//���룺���͵�����
//�������
//����������SPI����һ���ֽ�
//*****************************************************************************************
uint8_t SpiTxRxByte(uint8_t byte)
{
	/*!< Loop while DR register in not emplty */
	while (SPI_I2S_GetFlagStatus(SPI3, SPI_I2S_FLAG_TXE) == RESET)
		;

	/*!< Send byte through the SPI peripheral */
	SPI_I2S_SendData(SPI3, byte);

	/*!< Wait to receive a byte */
	while (SPI_I2S_GetFlagStatus(SPI3, SPI_I2S_FLAG_RXNE) == RESET)
		;

	/*!< Return the byte read from the SPI bus */
	return SPI_I2S_ReceiveData(SPI3);
}

//*****************************************************************************************
//��������void RESET_CC1100(void)
//���룺��
//�������
//������������λCC1100
//*****************************************************************************************
void Reset_CC1100(void)
{
	RF_CSn(0);
	while (RF_MISO())
		;
	SpiTxRxByte(CCxxx0_SRES); 		//д�븴λ����
	while (RF_MISO())
		;
	RF_CSn(1);
}

//*****************************************************************************************
//��������void POWER_UP_RESET_CC1100(void)
//���룺��
//�������
//�����������ϵ縴λCC1100
//*****************************************************************************************
void Power_Up_Reset_CC1100(void)
{
	RF_CSn(1);
	rt_delay_us(100);
	RF_CSn(0);
	rt_delay_us(100);
	RF_CSn(1);
	rt_delay_us(100);
	Reset_CC1100();   		//��λCC1100
}

//*****************************************************************************************
//��������void halSpiWriteReg(uint8_t addr, uint8_t value)
//���룺��ַ��������
//�������
//����������SPIд�Ĵ���
//*****************************************************************************************
void halSpiWriteReg(uint8_t addr, uint8_t value)
{
	RF_CSn(0);
	while (RF_MISO())
		;
	SpiTxRxByte(addr);		//д��ַ
	SpiTxRxByte(value);		//д������
	RF_CSn(1);
}

//*****************************************************************************************
//��������void halSpiWriteBurstReg(uint8_t addr, uint8_t *buffer, uint8_t count)
//���룺��ַ��д�뻺������д�����
//�������
//����������SPI����д���üĴ���
//*****************************************************************************************
void halSpiWriteBurstReg(uint8_t addr, uint8_t *buffer, uint8_t count)
{
	uint8_t i, temp;
	temp = addr | WRITE_BURST;
	RF_CSn(0);
	while (RF_MISO())
		;
	SpiTxRxByte(temp);
	for (i = 0; i < count; i++)
	{
		SpiTxRxByte(buffer[i]);
	}
	RF_CSn(1);
}

//*****************************************************************************************
//��������void halSpiStrobe(uint8_t strobe)
//���룺����
//�������
//����������SPIд����
//*****************************************************************************************
void halSpiStrobe(uint8_t strobe)
{
	RF_CSn(0);
	while (RF_MISO())
		;
	SpiTxRxByte(strobe);		//д������
	RF_CSn(1);
}

//*****************************************************************************************
//��������uint8_t halSpiReadReg(uint8_t addr)
//���룺��ַ
//������üĴ�����������
//����������SPI���Ĵ���
//*****************************************************************************************
uint8_t halSpiReadReg(uint8_t addr)
{
	uint8_t temp, value;
	temp = addr | READ_SINGLE;		//���Ĵ�������
	RF_CSn(0);
	while (RF_MISO())
		;
	SpiTxRxByte(temp);
	value = SpiTxRxByte(0);
	RF_CSn(1);
	return value;
}

//*****************************************************************************************
//��������void halSpiReadBurstReg(uint8_t addr, uint8_t *buffer, uint8_t count)
//���룺��ַ���������ݺ��ݴ�Ļ��������������ø���
//�������
//����������SPI����д���üĴ���
//*****************************************************************************************
void halSpiReadBurstReg(uint8_t addr, uint8_t *buffer, uint8_t count)
{
	uint8_t i, temp;
	temp = addr | READ_BURST;		//д��Ҫ�������üĴ�����ַ�Ͷ�����
	RF_CSn(0);
	while (RF_MISO())
		;
	SpiTxRxByte(temp);
	for (i = 0; i < count; i++)
	{
		buffer[i] = SpiTxRxByte(0);
	}
	RF_CSn(1);
}

//*****************************************************************************************
//��������uint8_t halSpiReadReg(uint8_t addr)
//���룺��ַ
//�������״̬�Ĵ�����ǰֵ
//����������SPI��״̬�Ĵ���
//*****************************************************************************************
uint8_t halSpiReadStatus(uint8_t addr)
{
	uint8_t value, temp;
	temp = addr | READ_BURST;		//д��Ҫ����״̬�Ĵ����ĵ�ַͬʱд�������
	RF_CSn(0);
	while (RF_MISO())
		;
	SpiTxRxByte(temp);
	value = SpiTxRxByte(0);
	RF_CSn(1);
	return value;
}

void halRfTransmitEnable(void)
{
	GPIO_ResetBits(GPIOE, GPIO_Pin_0);
	GPIO_SetBits(GPIOB, GPIO_Pin_9);
}

void halRfReceiveEnable(void)
{
	GPIO_ResetBits(GPIOB, GPIO_Pin_9);
	GPIO_SetBits(GPIOE, GPIO_Pin_0);
}

