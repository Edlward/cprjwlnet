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
APF_EXT int16 QRef;						//�޹����ʸ�������λA
APF_EXT int16 CmpsateSet;				//г�������ʣ���λ%

/******************************************************************************/
/*                        APF Control Paramets								  */
/******************************************************************************/
APF_EXT float RpGain;
APF_EXT float RpKr;
APF_EXT char RpLeadingBeat;
APF_EXT Uint16 RpCutoffFreqence;


/******************************************************************************/
/*                        APF internal State Variables						  */
/******************************************************************************/
APF_EXT Uint16 APF_State;				//APF״̬
APF_EXT Uint16 Carrier_Wave_Count;
APF_EXT float Iapf_a,Iapf_b,Iapf_c;		//APF�������ߵ�������λA
APF_EXT float Iload_a,Iload_b,Iload_c;	//���ص��ߵ�������λA
APF_EXT float Upcc_ab,Upcc_bc,Upcc_ca;	//PCC���ߵ�ѹ����λV
APF_EXT float Upcc_a,Upcc_b,Upcc_c;		//PCC�����ѹ����λV
APF_EXT float UdcA,UdcB,UdcC;			//ֱ����ĸ�ߵ�ѹ����λV
APF_EXT float Udc_average;				//ֱ��ĸ��ƽ����ѹ����λV
APF_EXT float UacRectifier;				//������ѹ����ֵ����λV
APF_EXT float VectorAngle;				//��ѹʸ���Ƕȣ���λrad
APF_EXT float GridFrequence;			//����Ƶ�ʣ���λHz
APF_EXT Uint16 PointCnt;
APF_EXT float RpBuffer[2][POINT_NUM];
APF_EXT float UpccDm;

APF_EXT PI PI_Ialfa;	//����������PID
APF_EXT PI PI_Ibeta;
APF_EXT PI PI_Udcp;		//ƽ����ѹ������PID
APF_EXT PI PI_Udcn_d;	//ƽ���ѹ������PID
APF_EXT PI PI_Udcn_q;
APF_EXT PI PI_Pll;

/******************************************************************************/
/*                        APF ��ѹ������Чֵ								  */
/******************************************************************************/
APF_EXT float Uab_rms;
APF_EXT float Ubc_rms;
APF_EXT float IloadA_rms;
APF_EXT float IloadB_rms;
APF_EXT float IapfA_rms;
APF_EXT float IapfB_rms;

//APF_EXT average_filter_instance UdFilter;
//APF_EXT average_filter_instance IhdFilter;
//APF_EXT average_filter_instance IhqFilter;

APF_EXT DF22 DF22_Udaverage;
APF_EXT DF22 DF22_Ihpd;
APF_EXT DF22 DF22_Ihpq;
APF_EXT DF22 DF22_Ihnd;
APF_EXT DF22 DF22_Ihnq;

APF_EXT DF22 DF22_RpFilter0;
APF_EXT DF22 DF22_RpFilter1;
APF_EXT DF22 DF22_UdcA;
APF_EXT DF22 DF22_UdcB;
APF_EXT DF22 DF22_UdcC;

APF_EXT char MainTskTrigger;
APF_EXT tCANMsgObject sTXCANMessage;
APF_EXT tCANMsgObject sRXCANMessage;
APF_EXT unsigned char ucTXMsgData[8];
APF_EXT unsigned char ucRXMsgData[8];
APF_EXT char FlagRxCAN;

APF_EXT float graph_data1[500];
APF_EXT float graph_data2[500];
APF_EXT float graph_data3[500];
//APF_EXT float graph_data4[500];
APF_EXT float DispData1,DispData2,DispData3;

#endif /* APF_VARIABLES_H_ */
