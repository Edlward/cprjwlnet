/*
 * rf_app.c
 *
 *  Created on: 2014��3��25��
 *      Author: Administrator
 */

#include <includes.h>

#define PKTSTATUS_CCA	1 << 4
#define PKTSTATUS_CS	1 << 6

// RF_SETTINGS is a data structure which contains all relevant CCxxx0 registers
typedef struct S_RF_SETTINGS
{
	uint8_t FSCTRL2;		//���Ѽӵ�
	uint8_t FSCTRL1;   // Frequency synthesizer control.
	uint8_t FSCTRL0;   // Frequency synthesizer control.
	uint8_t FREQ2;     // Frequency control word, high uint8_t.
	uint8_t FREQ1;     // Frequency control word, middle uint8_t.
	uint8_t FREQ0;     // Frequency control word, low uint8_t.
	uint8_t MDMCFG4;   // Modem configuration.
	uint8_t MDMCFG3;   // Modem configuration.
	uint8_t MDMCFG2;   // Modem configuration.
	uint8_t MDMCFG1;   // Modem configuration.
	uint8_t MDMCFG0;   // Modem configuration.
	uint8_t CHANNR;    // Channel number.
	uint8_t DEVIATN; // Modem deviation setting (when FSK modulation is enabled).
	uint8_t FREND1;    // Front end RX configuration.
	uint8_t FREND0;    // Front end RX configuration.
	uint8_t MCSM1;
	uint8_t MCSM0;     // Main Radio Control State Machine configuration.
	uint8_t FOCCFG;    // Frequency Offset Compensation Configuration.
	uint8_t BSCFG;     // Bit synchronization Configuration.
	uint8_t AGCCTRL2;  // AGC control.
	uint8_t AGCCTRL1;  // AGC control.
	uint8_t AGCCTRL0;  // AGC control.
	uint8_t FSCAL3;    // Frequency synthesizer calibration.
	uint8_t FSCAL2;    // Frequency synthesizer calibration.
	uint8_t FSCAL1;    // Frequency synthesizer calibration.
	uint8_t FSCAL0;    // Frequency synthesizer calibration.
	uint8_t FSTEST;    // Frequency synthesizer calibration control
	uint8_t TEST2;     // Various test settings.
	uint8_t TEST1;     // Various test settings.
	uint8_t TEST0;     // Various test settings.
	uint8_t IOCFG2;    // GDO2 output pin configuration
	uint8_t IOCFG0;    // GDO0 output pin configuration
	uint8_t PKTCTRL1;  // Packet automation control.
	uint8_t PKTCTRL0;  // Packet automation control.
	uint8_t ADDR;      // Device address.
	uint8_t PKTLEN;    // Packet length.
} RF_SETTINGS;

/////////////////////////////////////////////////////////////////
const RF_SETTINGS rfSettings =
{ 0x00, 0x08,   // FSCTRL1   Frequency synthesizer control.
		0x00,   // FSCTRL0   Frequency synthesizer control.
		0x10,   // FREQ2     Frequency control word, high byte.
		0xA7,   // FREQ1     Frequency control word, middle byte.
		0x62,   // FREQ0     Frequency control word, low byte.
		0x5B,   // MDMCFG4   Modem configuration.
		0xF8,   // MDMCFG3   Modem configuration.
		0x03,   // MDMCFG2   Modem configuration.
		0x22,   // MDMCFG1   Modem configuration.
		0xF8,   // MDMCFG0   Modem configuration.

		0x00,   // CHANNR    Channel number.
		0x47, // DEVIATN   Modem deviation setting (when FSK modulation is enabled).
		0xB6,   // FREND1    Front end RX configuration.
		0x10,   // FREND0    Front end RX configuration.
		0x3C,	// MCSM1
		0x18,   // MCSM0     Main Radio Control State Machine configuration.
		0x1D,   // FOCCFG    Frequency Offset Compensation Configuration.
		0x1C,   // BSCFG     Bit synchronization Configuration.
		0xC7,   // AGCCTRL2  AGC control.XXX C7 -> 0XFF
		0x00,   // AGCCTRL1  AGC control. XXX 00->0X40
		0xB2,   // AGCCTRL0  AGC control.

		0xEA,   // FSCAL3    Frequency synthesizer calibration.
		0x2A,   // FSCAL2    Frequency synthesizer calibration.
		0x00,   // FSCAL1    Frequency synthesizer calibration.
		0x11,   // FSCAL0    Frequency synthesizer calibration.
		0x59,   // FSTEST    Frequency synthesizer calibration.
		0x81,   // TEST2     Various test settings.
		0x35,   // TEST1     Various test settings.
		0x09,   // TEST0     Various test settings.
		0x0E,   // IOCFG2    GDO2 output pin configuration.
		0x06, // IOCFG0    GDO0 output pin configuration. Refer to SmartRF?Studio User Manual for detailed pseudo register explanation.

		0x04,   // PKTCTRL1  Packet automation control.
		0x05,   // PKTCTRL0  Packet automation control.
		0x00,   // ADDR      Device address.
		0x0C    // PKTLEN    Packet length.
//    0XFF	// PKTLEN    Packet length.
		};
//*****************************************************************************************
//��������delay(unsigned int s)
//���룺ʱ��
//�������
//������������ͨ͢ʱ,�ڲ���
//*****************************************************************************************
static void delay(unsigned int s)
{
	unsigned int i;
	for (i = 0; i < s; i++)
		;
	for (i = 0; i < s; i++)
		;
}

//*****************************************************************************************
//��������void halRfWriteRfSettings(RF_SETTINGS *pRfSettings)
//���룺��
//�������
//��������������CC1100�ļĴ���
//*****************************************************************************************
void halRfWriteRfSettings(void)
{

//	halSpiWriteReg(CCxxx0_FSCTRL0,  rfSettings.FSCTRL2);//���Ѽӵ�
	// Write register settings
	halSpiWriteReg(CCxxx0_FSCTRL1, rfSettings.FSCTRL1);
	halSpiWriteReg(CCxxx0_FSCTRL0, rfSettings.FSCTRL0);
	halSpiWriteReg(CCxxx0_FREQ2, rfSettings.FREQ2);
	halSpiWriteReg(CCxxx0_FREQ1, rfSettings.FREQ1);
	halSpiWriteReg(CCxxx0_FREQ0, rfSettings.FREQ0);
	halSpiWriteReg(CCxxx0_MDMCFG4, rfSettings.MDMCFG4);
	halSpiWriteReg(CCxxx0_MDMCFG3, rfSettings.MDMCFG3);
	halSpiWriteReg(CCxxx0_MDMCFG2, rfSettings.MDMCFG2);
	halSpiWriteReg(CCxxx0_MDMCFG1, rfSettings.MDMCFG1);
	halSpiWriteReg(CCxxx0_MDMCFG0, rfSettings.MDMCFG0);
	halSpiWriteReg(CCxxx0_CHANNR, rfSettings.CHANNR);
	halSpiWriteReg(CCxxx0_DEVIATN, rfSettings.DEVIATN);
	halSpiWriteReg(CCxxx0_FREND1, rfSettings.FREND1);
	halSpiWriteReg(CCxxx0_FREND0, rfSettings.FREND0);
	halSpiWriteReg(CCxxx0_MCSM1, rfSettings.MCSM1);	//XXX ����ط������¼ӵ�
	halSpiWriteReg(CCxxx0_MCSM0, rfSettings.MCSM0);
	halSpiWriteReg(CCxxx0_FOCCFG, rfSettings.FOCCFG);
	halSpiWriteReg(CCxxx0_BSCFG, rfSettings.BSCFG);
	halSpiWriteReg(CCxxx0_AGCCTRL2, rfSettings.AGCCTRL2);
	halSpiWriteReg(CCxxx0_AGCCTRL1, rfSettings.AGCCTRL1);
	halSpiWriteReg(CCxxx0_AGCCTRL0, rfSettings.AGCCTRL0);
	halSpiWriteReg(CCxxx0_FSCAL3, rfSettings.FSCAL3);
	halSpiWriteReg(CCxxx0_FSCAL2, rfSettings.FSCAL2);
	halSpiWriteReg(CCxxx0_FSCAL1, rfSettings.FSCAL1);
	halSpiWriteReg(CCxxx0_FSCAL0, rfSettings.FSCAL0);
	halSpiWriteReg(CCxxx0_FSTEST, rfSettings.FSTEST);
	halSpiWriteReg(CCxxx0_TEST2, rfSettings.TEST2);
	halSpiWriteReg(CCxxx0_TEST1, rfSettings.TEST1);
	halSpiWriteReg(CCxxx0_TEST0, rfSettings.TEST0);
	halSpiWriteReg(CCxxx0_IOCFG2, rfSettings.IOCFG2);
	halSpiWriteReg(CCxxx0_IOCFG0, rfSettings.IOCFG0);
	halSpiWriteReg(CCxxx0_PKTCTRL1, rfSettings.PKTCTRL1);
	halSpiWriteReg(CCxxx0_PKTCTRL0, rfSettings.PKTCTRL0);
	halSpiWriteReg(CCxxx0_ADDR, rfSettings.ADDR);
	halSpiWriteReg(CCxxx0_PKTLEN, rfSettings.PKTLEN);
}

//*****************************************************************************************
//��������void halRfSendPacket(uint8_t *txBuffer, uint8_t size)
//���룺���͵Ļ��������������ݸ���
//�������
//����������CC1100����һ������
//*****************************************************************************************

void halRfSendPacket(uint8_t *txBuffer, uint8_t size)
{
	uint32_t event;
	halRfTransmitEnable();
	halSpiStrobe(CCxxx0_SFTX);	//���Tx FIFO
	halSpiWriteReg(CCxxx0_TXFIFO, size);
	halSpiWriteBurstReg(CCxxx0_TXFIFO, txBuffer, size);	//д��Ҫ���͵�����
	RfState = RFSTATE_TX;
	halRfSyncPinINTCmd(ENABLE);	//��ͬ���ж�
	halSpiStrobe(CCxxx0_STX);		//���뷢��ģʽ��������
	rt_event_recv(&event_rf, RFSTATE_TX,
	RT_EVENT_FLAG_AND | RT_EVENT_FLAG_CLEAR, RT_WAITING_FOREVER, &event);//�ȴ������ж�
	halRfSyncPinINTCmd(DISABLE);	//��ͬ���ж�
	RfState = RFSTATE_IDLE;
}

uint8_t halRfReceivePacket(uint8_t *rxBuffer, uint8_t *status)
{
	uint8_t packetLength;

	if ((halSpiReadStatus(CCxxx0_RXBYTES) & BYTES_IN_RXFIFO)) //����ӵ��ֽ�����Ϊ0
	{
		packetLength = halSpiReadReg(CCxxx0_RXFIFO); //������һ���ֽڣ����ֽ�Ϊ��֡���ݳ���
		halSpiReadBurstReg(CCxxx0_RXFIFO, rxBuffer, packetLength); //�������н��յ�������

		// Read the 2 appended status bytes (status[0] = RSSI, status[1] = LQI)
		halSpiReadBurstReg(CCxxx0_RXFIFO, status, 2); 	//����CRCУ��λ
		halSpiStrobe(CCxxx0_SFRX);		//��ϴ���ջ�����
		return packetLength;			//���У��ɹ����ؽ��ճɹ�
	}
	halSpiStrobe(CCxxx0_SFRX);		//��ϴ���ջ�����
	return 0;
}

void halRfSyncPinINTCmd(uint8_t state)
{
	if (state == 0)
	{
		EXTI->IMR &= ~EXTI_Line7;	//�����λ
	}
	else
	{
		EXTI->IMR |= EXTI_Line7;	//ʹ�ܸ�λ
	}
}

void halRfRxModeOn(void)
{
	RfState = RFSTATE_RX;
	halRfReceiveEnable();
	halRfSyncPinINTCmd(ENABLE);	//������ͬ���ж�
	halSpiStrobe(CCxxx0_SRX);		//�������״̬
}

void halRfRxModeOff(void)
{
	/* disable receive interrupts */
	halRfSyncPinINTCmd(DISABLE);
	/* turn off radio */
	halSpiStrobe(CCxxx0_SIDLE);	//�������״̬
	/* flush the receive FIFO of any residual data */
	halSpiStrobe( CCxxx0_SFRX);
}

void halRfPrepareToTx(uint8_t *txBuffer, uint8_t size)
{
	halSpiStrobe( CCxxx0_SFTX); // flush the tx fifo
	halSpiWriteReg(CCxxx0_TXFIFO, size);
	halSpiWriteBurstReg(CCxxx0_TXFIFO, txBuffer, size);	//д��Ҫ���͵�����
}

uint8_t halRfTransmit(uint8_t *txBuffer, uint8_t size)
{
	uint8_t state = 0, i;
	uint32_t event;
	/* turn off radio */
	halRfSyncPinINTCmd(DISABLE);	//��ͬ���ж�
	rt_hw_led_on(2);
	for (;;)
	{
		halSpiStrobe(CCxxx0_SIDLE);		//�������״̬
		while (state != 0x01)	//����Ƿ�������״̬
		{
			rt_delay_us(100);
			state = halSpiReadStatus(CCxxx0_MARCSTATE);
		}
		halSpiStrobe(CCxxx0_SFRX);	//���RX FIFO
		halRfPrepareToTx(txBuffer, size);	//д�����ݵ�Tx FIFO
		halRfReceiveEnable();			//ʹ�ܽ���LNA
		RfState = RFSTATE_RX;
		halSpiStrobe(CCxxx0_SRX);		//�������״̬
		while (state != 13 && state != 14 && state != 15)	//ȷ�����뷢��״̬
		{
			rt_delay_us(60);
			state = halSpiReadStatus(CCxxx0_MARCSTATE);
		}
		rt_delay_us(500);	//��ʱһ��ʱ�䣬�ȴ�Rx״̬�ȶ�
//		for (;;)
//		{
//			state = halSpiReadStatus(CCxxx0_PKTSTATUS);
//			if (state & PKTSTATUS_CCA)
//			{
//				rt_hw_led_on(2);
//			}
//			else
//			{
//				rt_hw_led_off(2);
//				break;
//			}
//		}
				//���CCA��CS�����ݷ���ǰ���뱣֤CCA = 1��CS=0������ά��һ��ʱ��
		for (i = 4; i > 0; i--)
		{
			state = halSpiReadStatus(CCxxx0_PKTSTATUS);
			if ((state & PKTSTATUS_CS) && (state & PKTSTATUS_CCA) == 0)
			{
				rt_thread_delay(2);	//���CCA����CSΪ1������ʱ10ms�������¼��CCA
				break;
			}
			rt_delay_us(100);
		}
		if (i == 0)		//���1ms��CCA��CSΪ0��˵�����㷢�͵��������˳�for(;;)
			break;
	}
	rt_hw_led_off(2);

	RfState = RFSTATE_TX;
	halRfTransmitEnable();
	rt_event_recv(&event_rf, RFSTATE_TX,
	RT_EVENT_FLAG_AND | RT_EVENT_FLAG_CLEAR, RT_WAITING_NO, &event);	//�ȴ������ж�
	halRfSyncPinINTCmd(ENABLE);	//��ͬ���ж�
	halSpiStrobe(CCxxx0_STX);		//���뷢��ģʽ��������
	state = rt_event_recv(&event_rf, RFSTATE_TX,
	RT_EVENT_FLAG_AND | RT_EVENT_FLAG_CLEAR, 10, &event);		//�ȴ������ж�
	halRfSyncPinINTCmd(DISABLE);	//��ͬ���ж�
	RfState = RFSTATE_IDLE;
	if (state == RT_EOK)
		return 1;
	else
		return 0;
}
