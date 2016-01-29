/*
 * APF_Variables.h
 *
 *  Created on: 2015��2��3��
 *      Author: Administrator
 */

#ifndef APF_VARIABLES_H_
#define APF_VARIABLES_H_

#ifndef APF
#define APF_EXT extern
#else
#define APF_EXT
#endif

#include <includes.h>

/******************************************************************************/
/*                        APF Configuration	Variables						  */
/******************************************************************************/

APF_EXT int16 UdcRef;					//ֱ��ĸ�ߵ�ѹ����ֵ����λV
APF_EXT int16 QRef;					//�޹����ʸ�������λA
APF_EXT int16 CmpsateSet;				//г�������ʣ���λ%

/******************************************************************************/
/*                        APF Control Paramets								  */
/******************************************************************************/
APF_EXT float RpGain;
APF_EXT float RpKr;
APF_EXT char RpLeadingBeat;


/******************************************************************************/
/*                        APF internal State Variables						  */
/******************************************************************************/
APF_EXT Uint16 APF_State;				//APF״̬
APF_EXT Uint16 Carrier_Wave_Count;
APF_EXT float Iapf_a,Iapf_b,Iapf_c;		//APF�������ߵ�������λA
APF_EXT float Iload_a,Iload_b,Iload_c;	//���ص��ߵ�������λA
APF_EXT float Upcc_ab,Upcc_bc,Upcc_ca;	//PCC���ߵ�ѹ����λV
APF_EXT float Upcc_a,Upcc_b,Upcc_c;		//PCC�����ѹ����λV
APF_EXT float UdcA,UdcB,UdcC,Udc;		//ֱ����ĸ�ߵ�ѹ����λV
APF_EXT float Udc_average;				//ֱ��ĸ��ƽ����ѹ����λV
APF_EXT float VectorAngle;				//��ѹʸ���Ƕȣ���λrad
APF_EXT float GridFrequence;			//����Ƶ�ʣ���λHz
APF_EXT float Iload_d[POINT_NUM],Iload_q[POINT_NUM];
APF_EXT Uint16 PointCnt;
//APF_EXT float RpBuffer[2][POINT_NUM];

APF_EXT iir_filter_instance IIR_for_Rpcontroller[2];
APF_EXT iir_filter_instance IIR_for_Id[2];
APF_EXT iir_filter_instance IIR_for_Iq[2];
APF_EXT iir_filter_instance IIR_for_Pll;
//APF_EXT float FFT_DataBuffer[FFT_LENGTH];
//APF_EXT float FFT_CalBuffer[FFT_LENGTH];
//APF_EXT float FFT_OutBuffer[FFT_LENGTH];
//APF_EXT struct rt_mailbox mb_fft;


APF_EXT pid_instance pid_instance_Ialfa;		//����������PID
APF_EXT pid_instance pid_instance_Ibeta;
APF_EXT pid_instance pid_instance_Udcp;		//ƽ����ѹ������PID
APF_EXT pid_instance pid_instance_Udcn_d;	//ƽ���ѹ������PID
APF_EXT pid_instance pid_instance_Udcn_q;
APF_EXT pid_instance pid_instance_Pll;



/******************************************************************************/
/*                        APF ��ѹ������Чֵ								  */
/******************************************************************************/
APF_EXT float Uab_rms;
APF_EXT float Ubc_rms;
APF_EXT float IloadA_rms;
APF_EXT float IloadB_rms;
APF_EXT float IapfA_rms;
APF_EXT float IapfB_rms;

APF_EXT char MainTskTrigger;
APF_EXT tCANMsgObject sTXCANMessage;
APF_EXT tCANMsgObject sRXCANMessage;
APF_EXT unsigned char ucTXMsgData[8];
APF_EXT unsigned char ucRXMsgData[8];
APF_EXT char FlagRxCAN;

#endif /* APF_VARIABLES_H_ */
