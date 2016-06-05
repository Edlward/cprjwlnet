/*
 * apc.c
 *
 *  Created on: 2015-9-27
 *      Author: Administrator
 */

#define APF
#include <includes.h>

/* ���ྲֹ����ϵ�±��� *******************************************************/
static float Iapf_alfa, Iapf_beta;
static float Iload_alfa, Iload_beta;
/* ������ת����ϵ�±��� *******************************************************/
static float Iapf_d, Iapf_q;
static float Iload_d, Iload_q;
static float UdcRampRef;

static float GetPllAngle(float ua, float ub);
static void Para_Init(void);
static void PID_Init(void);
static float AverageFilter(float ui, average_filter_instance* filter);
static void HarmonicDetection(float ia, float ib, float *pifa, float *pifb,
		float *pihd, float *pihq);

#ifdef _FLASH
#pragma CODE_SECTION(APF_Main, "ramfuncs");
#pragma CODE_SECTION(GetPllAngle, "ramfuncs");
#pragma CODE_SECTION(CheckPwrState, "ramfuncs");
//#pragma CODE_SECTION(AverageFilter, "ramfuncs");
#pragma CODE_SECTION(HarmonicDetection, "ramfuncs");
#pragma CODE_SECTION(DCL_runDF22, "ramfuncs");
#pragma CODE_SECTION(DCL_runPI,"ramfuncs")
#endif
#pragma DATA_SECTION(graph_data1,"Filter1_RegsFile");
#pragma DATA_SECTION(graph_data2,"Filter2_RegsFile");
#pragma DATA_SECTION(graph_data3,"Filter3_RegsFile");

interrupt void FaultProcess(void)
{

	EPwm2Regs.TZCLR.bit.OST = 1;
	EPwm3Regs.TZCLR.bit.OST = 1;
	EPwm4Regs.TZCLR.bit.OST = 1;
	EPwm6Regs.TZCLR.bit.OST = 1;
	EPwm7Regs.TZCLR.bit.OST = 1;
	EPwm8Regs.TZCLR.bit.OST = 1;

	EALLOW;
	EPwm2Regs.TZCLR.bit.CBC = 1;
	EPwm2Regs.TZCLR.bit.INT = 1;
	EDIS;

	// Acknowledge this interrupt to receive more interrupts from group 2
	PieCtrlRegs.PIEACK.all = PIEACK_GROUP2;

}

interrupt void APF_Main(void)
{
	static float compensatepercentage = 0;
	float udcp_out;
	float temp_alfa, temp_beta;
	float error_alfa, error_beta;
	float temp_d = 0, temp_q = 0;
	float temp_a, temp_b, temp_c;
	float sinVal, cosVal;
	float pwm_a, pwm_b, pwm_c;
	float ihd, ihq, ifa, ifb, id, iq, iha, ihb;
	float ux, uy, upccd_average;
	Uint16 temp;
	static Uint16 i;

	GPIO_WritePin(58, 1);
	MainTskTrigger = 1;		//���������񴥷�
	ADValueConvert();
	VectorAngle = GetPllAngle(Upcc_a, Upcc_b);	//�õ���ѹʸ���ļн�
	Udc_average = (UdcA + UdcB + UdcC) / 3.0;
	sincos(VectorAngle, &sinVal, &cosVal);
	clarke(Iapf_a, Iapf_b, &Iapf_alfa, &Iapf_beta);
	park(Iapf_alfa, Iapf_beta, &Iapf_d, &Iapf_q, sinVal, cosVal);

	HarmonicDetection(Iload_a, Iload_b, &ifa, &ifb, &ihd, &ihq);
	iha = Iload_a - ifa;
	ihb = Iload_b - ifb;
	/****************************������ѹ����******************************/
	clarke(Upcc_a, Upcc_b, &ux, &uy);
	park(ux, uy, &ux, &uy, sinVal, cosVal);
	UpccDm = DCL_runDF22(&DF22_Udaverage, ux);
//	GPIO_WritePin(58,0);
	/******************************���APF�Ƿ��й��Ϸ���**************************************/
	if (GPIO_ReadPin(70) == DISABLE || UdcA > DC_LINK_WARNING_VALUE
			|| UdcB > DC_LINK_WARNING_VALUE || UdcC > DC_LINK_WARNING_VALUE)
	{
		APF_State |= APF_STATE_BIT_OV | APF_STATE_BIT_STOP;
	}
	else
	{
		APF_State &= ~ APF_STATE_BIT_OV;
	}
	if (GPIO_ReadPin(68) == DISABLE)
	{
		APF_State |= APF_STATE_BIT_OC1 | APF_STATE_BIT_STOP;
	}
	else
	{
		APF_State &= ~ APF_STATE_BIT_OC1;
	}
	if (GPIO_ReadPin(69) == DISABLE)
	{
		APF_State |= APF_STATE_BIT_OC2 | APF_STATE_BIT_STOP;
	}
	else
	{
		APF_State &= ~ APF_STATE_BIT_OC2;
	}
//	if (GPIO_ReadPin(71) == DISABLE)	//TODO ����IGBT�����⣬������·����
//	{
//		APF_State |= APF_STATE_BIT_IGBT_ERR;
//	}
//	else
//	{
//		APF_State &= ~ APF_STATE_BIT_IGBT_ERR;
//	}

	/*****************���APF�Ƿ��������л�����IGBT���************************/
//���ڿ��ؼ��ʱ��ʱ�������������������λ��ȷ��
//	if (APF_STATE_BIT_STOP == APF_State || APF_STATE_BIT_SWSTOP == APF_State
//			|| APF_STATE_BIT_TEST == APF_State || 0 == APF_State)
//	{
//		if (GPIO_ReadPin(54) == SET)	//���APF������ť�Ƿ���
//		{
//			APF_State = 0;
//			GPIO_WritePin(GPIO_LED33, 0);
//		}
//		else
//		{
//			APF_State = APF_STATE_BIT_STOP;
//			GPIO_WritePin(GPIO_LED33, 1);
//		}
//		if (GPIO_ReadPin(53) == SET)	//���APF�Ƿ�����IGBT���
//		{
//			APF_State = APF_STATE_BIT_TEST;
//			GPIO_WritePin(GPIO_LED34, 0);
//		}
//		else
//		{
//			APF_State = APF_STATE_BIT_STOP;
//			GPIO_WritePin(GPIO_LED34, 1);
//		}
//	}
	/*****************************����APF��״̬���в���*************************************/
	if (0 == APF_State)	//���APF������
	{
		/*
		 * ֱ��ĸ��ƽ����ѹ����
		 */
		UdcRampRef += 20.0 * APF_SAMPLE_PERIOD;	//1s�ڸ���ֵ������20V
		if (UdcRampRef > UdcRef)
		{
			UdcRampRef = UdcRef;
		}
		PI_Udcp.Umax = 30;	//����ֱ��ĸ�ߵ�ѹ���ڵĵ������ɳ���30A
		PI_Udcp.Umin = -30;
		udcp_out = DCL_runPI(&PI_Udcp, Udc_average, UdcRampRef);

		if ((UdcRampRef == UdcRef) && ((UdcRef - Udc_average) < 30)
				&& ((UdcRef - Udc_average) > -30))	//ֻ����ѹ�����󣬲Ż����г������
		{
			compensatepercentage += 30.0 * APF_SAMPLE_PERIOD;	//1s�ڰٷֱȻ�������30%
			if (compensatepercentage > CmpsateSet)
			{
				compensatepercentage = CmpsateSet;
			}
		}

//#if 1	//1��dq���½���г����������

		/******************ֱ��ĸ�����ƽ����������������********************/
		clarke(Udc_average - UdcA, Udc_average - UdcB, &temp_alfa, &temp_beta);
		//����ֱ��ĸ�ߵ�ѹƽ����ڵĵ��������Գ���30A
		PI_Udcn_d.Umax = 30;
		PI_Udcn_d.Umin = -30;
		PI_Udcn_q.Umax = 30;
		PI_Udcn_q.Umin = -30;
		temp_alfa = DCL_runPI(&PI_Udcn_d, temp_alfa, 0);
		temp_beta = DCL_runPI(&PI_Udcn_q, temp_beta, 0);
		sincos(VectorAngle * 2, &sinVal, &cosVal);
		inv_park(temp_alfa, temp_beta, &temp_alfa, &temp_beta, sinVal, cosVal);
		/****************************dq���������******************************/
		//����������ֵ����
//		ihd = ihq = 0;
		temp_d = udcp_out - temp_alfa + ihd * 0.01 * compensatepercentage;
		temp_q = temp_beta + ihq * compensatepercentage * 0.01
				+ QRef * compensatepercentage * 0.01 * 1.414213562f;
		//PI����
		PI_Ialfa.Umax = Udc_average;
		PI_Ialfa.Umin = -Udc_average;
		PI_Ibeta.Umax = Udc_average;
		PI_Ibeta.Umin = -Udc_average;
		temp_alfa = DCL_runPI(&PI_Ialfa, temp_d, Iapf_d);
		temp_beta = DCL_runPI(&PI_Ibeta, temp_q, Iapf_q);

		//�ظ�����
		temp_d -= Iapf_d;
		temp_q -= Iapf_q;
//		DispData1 = temp_d;
//		DispData2 = temp_q;
		RpBuffer[0][PointCnt] = temp_d + RpKr * RpBuffer[0][PointCnt];
		RpBuffer[1][PointCnt] = temp_q + RpKr * RpBuffer[1][PointCnt];

		temp = (PointCnt + PointNum - RpLeadingBeat) % PointNum;
		//�ظ��������Ľ����Ҫ�˲���ȥ����Ƶ����
		error_alfa = DCL_runDF22(&DF22_RpFilter0, RpBuffer[0][temp]);
		error_beta = DCL_runDF22(&DF22_RpFilter1, RpBuffer[1][temp]);

		temp_alfa += error_alfa * RpGain + UpccDm;
		temp_beta += error_beta * RpGain;

		/*****************************������任*******************************/
		sincos(VectorAngle, &sinVal, &cosVal);
		inv_park(temp_alfa, temp_beta, &temp_alfa, &temp_beta, sinVal, cosVal);
		inv_clarke(temp_alfa, temp_beta, &pwm_a, &pwm_b);
		pwm_c = -pwm_a - pwm_b;
		/*************************���������ʱ�䲹��***************************/
		float dtcmpsena, dtcmpsenb, dtcmpsenc;
		//A������ʱ�䲹��
		if (Iapf_a > 0.3)
			dtcmpsena = UdcA * 2 * APF_SWITCH_FREQ * DEAD_TIME_VALUE
					* DeadTimeCmpSet * 0.01;
		else if (Iapf_a < -0.3)
			dtcmpsena = -UdcA * 2 * APF_SWITCH_FREQ * DEAD_TIME_VALUE
					* DeadTimeCmpSet * 0.01;
		else
			dtcmpsena = UdcA * 2 * APF_SWITCH_FREQ * DEAD_TIME_VALUE
					* DeadTimeCmpSet * 0.01 * Iapf_a * 3.333;
		//B������ʱ�䲹��
		if (Iapf_b > 0.3)
			dtcmpsenb = UdcB * 2 * APF_SWITCH_FREQ * DEAD_TIME_VALUE
					* DeadTimeCmpSet * 0.01;
		else if (Iapf_b < -0.3)
			dtcmpsenb = -UdcB * 2 * APF_SWITCH_FREQ * DEAD_TIME_VALUE
					* DeadTimeCmpSet * 0.01;
		else
			dtcmpsenb = UdcB * 2 * APF_SWITCH_FREQ * DEAD_TIME_VALUE
					* DeadTimeCmpSet * 0.01 * Iapf_b * 3.333;
		//C������ʱ�䲹��
		if (Iapf_c > 0.3)
			dtcmpsenc = UdcC * 2 * APF_SWITCH_FREQ * DEAD_TIME_VALUE
					* DeadTimeCmpSet * 0.01;
		else if (Iapf_c < -0.3)
			dtcmpsenc = -UdcC * 2 * APF_SWITCH_FREQ * DEAD_TIME_VALUE
					* DeadTimeCmpSet * 0.01;
		else
			dtcmpsenc = UdcC * 2 * APF_SWITCH_FREQ * DEAD_TIME_VALUE
					* DeadTimeCmpSet * 0.01 * Iapf_c * 3.333;
		pwm_a += dtcmpsena;
		pwm_b += dtcmpsenb;
		pwm_c += dtcmpsenc;
		/*
		 * ���PWM���������Ա�ƵPWM����
		 */
//		if (UdcA < DC_MIN_VOLTAGE)	//ֱ��ĸ�ߵĵ�ѹֵ����Ӧ����������ѹֵ
//		{
//			UdcA = DC_MIN_VOLTAGE;
//		}
//		if (UdcB < DC_MIN_VOLTAGE)
//		{
//			UdcB = DC_MIN_VOLTAGE;
//		}
//		if (UdcC < DC_MIN_VOLTAGE)
//		{
//			UdcC = DC_MIN_VOLTAGE;
//		}
		pwm_a = pwm_a / UdcA * 0.5;
		pwm_b = pwm_b / UdcB * 0.5;
		pwm_c = pwm_c / UdcC * 0.5;

		if (pwm_a > 0.5)
		{
			pwm_a = 0.5;
		}
		else if (pwm_a < -0.5)
		{
			pwm_a = -0.5;
		}

		if (pwm_b > 0.5)
		{
			pwm_b = 0.5;
		}
		else if (pwm_b < -0.5)
		{
			pwm_b = -0.5;
		}

		if (pwm_c > 0.5)
		{
			pwm_c = 0.5;
		}
		else if (pwm_c < -0.5)
		{
			pwm_c = -0.5;
		}

		temp_a = (0.5 + pwm_a) * Carrier_Wave_Count;
		temp_b = (0.5 + pwm_b) * Carrier_Wave_Count;
		temp_c = (0.5 + pwm_c) * Carrier_Wave_Count;

		EPwm2Regs.CMPA.bit.CMPA = temp_a;
		EPwm3Regs.CMPA.bit.CMPA = temp_b;
		EPwm4Regs.CMPA.bit.CMPA = temp_c;

		temp_a = (0.5 - pwm_a) * Carrier_Wave_Count;
		temp_b = (0.5 - pwm_b) * Carrier_Wave_Count;
		temp_c = (0.5 - pwm_c) * Carrier_Wave_Count;

		EPwm6Regs.CMPA.bit.CMPA = temp_a;
		EPwm7Regs.CMPA.bit.CMPA = temp_b;
		EPwm8Regs.CMPA.bit.CMPA = temp_c;

		/* Main Output Enable */
		EALLOW;
		EPwm2Regs.TZCLR.bit.OST = 1;
		EPwm3Regs.TZCLR.bit.OST = 1;
		EPwm4Regs.TZCLR.bit.OST = 1;
		EPwm6Regs.TZCLR.bit.OST = 1;
		EPwm7Regs.TZCLR.bit.OST = 1;
		EPwm8Regs.TZCLR.bit.OST = 1;
		EDIS;

	}
	else
	{
		if (APF_STATE_BIT_TEST == APF_State)
		{
			/* Main Output Enable */
			EALLOW;
			EPwm2Regs.TZCLR.bit.OST = 1;
			EPwm3Regs.TZCLR.bit.OST = 1;
			EPwm4Regs.TZCLR.bit.OST = 1;
			EPwm6Regs.TZCLR.bit.OST = 1;
			EPwm7Regs.TZCLR.bit.OST = 1;
			EPwm8Regs.TZCLR.bit.OST = 1;
			EDIS;
			EPwm2Regs.CMPA.bit.CMPA = 500;
			EPwm3Regs.CMPA.bit.CMPA = 1000;
			EPwm4Regs.CMPA.bit.CMPA = 1500;
			EPwm6Regs.CMPA.bit.CMPA = 2000;
			EPwm7Regs.CMPA.bit.CMPA = 2500;
			EPwm8Regs.CMPA.bit.CMPA = 3000;
		}
		else
		{
			APF_State |= APF_STATE_BIT_STOP;
			/* Main Output Disable */
			EALLOW;
			EPwm2Regs.TZFRC.bit.OST = 1;
			EPwm3Regs.TZFRC.bit.OST = 1;
			EPwm4Regs.TZFRC.bit.OST = 1;
			EPwm6Regs.TZFRC.bit.OST = 1;
			EPwm7Regs.TZFRC.bit.OST = 1;
			EPwm8Regs.TZFRC.bit.OST = 1;
			EDIS;

			//PI�����������Ҫ����
			PI_Udcp.i10 = 0;
			PI_Udcp.i6 = 0;
			PI_Udcn_d.i10 = 0;
			PI_Udcn_d.i6 = 0;
			PI_Udcn_q.i10 = 0;
			PI_Udcn_q.i6 = 0;
			PI_Ialfa.i10 = 0;
			PI_Ialfa.i6 = 0;
			PI_Ibeta.i10 = 0;
			PI_Ibeta.i6 = 0;

			if (4000 == RpCutoffFreqence)
			{
				DF22 df = DF22_4000Hz;
				DF22_RpFilter0 = df;
				DF22_RpFilter1 = df;
			}
			else if (2500 == RpCutoffFreqence)
			{
				DF22 df = DF22_2500Hz;
				DF22_RpFilter0 = df;
				DF22_RpFilter1 = df;
			}
			else
			{
				DF22 df = DF22_3000Hz;
				DF22_RpFilter0 = df;
				DF22_RpFilter1 = df;
			}

			memset_fast(RpBuffer[0], 0, POINT_NUM * 2);	//����������ȽϺ�ʱ
			memset_fast(RpBuffer[1], 0, POINT_NUM * 2);
		}
		UdcRampRef = Udc_average;
		compensatepercentage = 0;
	} /*end if (0 == APF_State)*/
	PointCnt = (PointCnt + 1) % PointNum;

//	DispData1 = UpccDm;
//	DispData2 = Iload_b;
	graph_data1[i] = DispData1;
	graph_data2[i] = DispData2;
//	graph_data3[i] = Iload_a;
//	graph_data4[i] = Iapf_b;
	i++;
	if (i >= 500)
		i = 0;

#define DAC_IK_100mV_1A	 (4096/30)
#define DAC_IK_10mV_1A	 (4096/300)

	ExtDA_Output(0, VectorAngle * 500 + 4096);  //DA8
	ExtDA_Output(1, Iload_a * DAC_IK_10mV_1A * 10 + 4096);		//DA7
	ExtDA_Output(2, Iload_b * DAC_IK_10mV_1A * 10 + 4096);		//DA6
	ExtDA_Output(3, ifa * DAC_IK_10mV_1A * 10 + 4096);		//DA5
	ExtDA_Output(4, iha * DAC_IK_10mV_1A * 10 + 4096);		//DA4
	ExtDA_Output(5, ifb * DAC_IK_10mV_1A * 10 + 4096);			//DA3
	ExtDA_Output(6, ihb * DAC_IK_10mV_1A * 10 + 4096);		//DA2
	ExtDA_Output(7, DispData2 * DAC_IK_10mV_1A * 20 + 4096);		//DA1

	GPIO_WritePin(58, 0);	//�鿴�¸����Ƴ�����ж�ʱ��
	AdcaRegs.ADCINTFLGCLR.bit.ADCINT1 = 1; //clear INT1 flag
	PieCtrlRegs.PIEACK.all = PIEACK_GROUP1;

}
void APF_Init(void)
{
	Para_Init();
	PID_Init();
	memset_fast(&RpBuffer[0][0], 0, POINT_NUM * 2);
	memset_fast(&RpBuffer[1][0], 0, POINT_NUM * 2);
}

static void Para_Init(void)
{
	Carrier_Wave_Count = 200000000 / 2 * 0.5 * APF_SWITCH_PERIOD - 1;

	UdcRef = DC_REF_DEFAULT;
	QRef = Q_REF_DEFAULT;
	CmpsateSet = 0;
	APF_State = APF_STATE_BIT_STOP;
	DeadTimeCmpSet = 50;

	RpGain = 0;
	RpKr = 0.98;
	RpLeadingBeat = 2;
	RpCutoffFreqence = 3000;
	{
		DF22 df22 = DF22_3000Hz;
		DF22_RpFilter0 = df22;
		DF22_RpFilter1 = df22;
	}
	{
		DF22 df22 = DF22_500Hz;
		DF22_UdcA = df22;
		DF22_UdcB = df22;
		DF22_UdcC = df22;
	}
	{
		DF22 df22 = DF22_70Hz;
		DF22_Ihpd = df22;
		DF22_Ihpq = df22;
		DF22_Ihnd = df22;
		DF22_Ihnq = df22;
	}
	{
		DF22 df22 = DF22_15Hz;
		DF22_Udaverage = df22;
	}
	DF22_Pll = (DF22
			) DF22_5Hz;
//	UdFilter.sum = 0;
//	memset_fast(UdFilter.data, 0, 256 * 2);
//	IhdFilter.sum = 0;
//	memset_fast(IhdFilter.data, 0, 256 * 2);
//	IhqFilter.sum = 0;
//	memset_fast(IhqFilter.data, 0, 256 * 2);

	MainTskTrigger = 0;

}

static void PID_Init(void)
{
	PI_Ialfa = (PI
			) PI_CUR_DEFALUT;
	PI_Ibeta = (PI
			) PI_CUR_DEFALUT;
	PI_Udcn_d = (PI
			) PI_VLT_DEFALUT;
	PI_Udcn_q = (PI
			) PI_VLT_DEFALUT;
	PI_Udcp = (PI
			) PI_VLT_DEFALUT;
	PI_Pll = (PI
			) PI_PLL_DEFALUT;
}

static float GetPllAngle(float ua, float ub)
{
	static float theta = 0;
	float w;
	float ud, uq, ux, uy;
	float valsin, valcos;

	clarke(ua, ub, &ux, &uy);
	sincos(theta, &valsin, &valcos);
	park(ux, uy, &ud, &uq, valsin, valcos);

	if (ud <= 0)
	{
		ud = -ud + 0.001;
	}
	uq = uq / ud;
	w = DCL_runPI(&PI_Pll, uq, 0);
	DCL_runDF22(&DF22_Pll, w);
	GridFrequence = w * 0.5 / PI_CONST;
	PointNum = APF_SAMPLE_FREQ / GridFrequence;

	theta += w * APF_SAMPLE_PERIOD;
	if (theta > 2 * PI_CONST)
	{
		theta -= 2 * PI_CONST;
	}
	else if (theta < 0)
	{
		theta += 2 * PI_CONST;
	}

	return theta;
}

char CheckPwrState(float uab, float ubc, float uca, float udc)
{
	float u;
	char ans;
	static DF22 filter =
	{ 5.41589311124356e-07, 1.08317862224871e-06, 5.41589311124356e-07,
			-1.99791739975065, 0.997919566107898, 0, 0 };

	if (uab < 0)
		uab = -uab;
	if (ubc < 0)
	{
		ubc = -ubc;
	}
	if (uca < 0)
	{
		uca = -uca;
	}
	if (uab < ubc)
	{
		uab = ubc;
	}
	if (uab < uca)
	{
		uab = uca;
	}

	UacRectifier = DCL_runDF22(&filter, uab);
	if (UacRectifier > 20 && udc >= UacRectifier)

		ans = 1;
	else
		ans = 0;

	return ans;
}

static float AverageFilter(float ui, average_filter_instance* filter)
{
	float avr;
	/*
	 * mem[0] = sum(mem[2..2+cnt];
	 * mem[1] = i;
	 */
	filter->sum += ui;
	avr = filter->sum / 256;
	filter->data[filter->Cnt] = ui;
	filter->Cnt++;
	if (filter->Cnt >= 256)
		filter->Cnt = 0;
	filter->sum -= filter->data[filter->Cnt];

	return avr;
}

static void HarmonicDetection(float ia, float ib, float *pifa, float *pifb,
		float *pihd, float *pihq)
{
	float sinval, cosval;
	float ipd, ipq, ind, inq, ialfa, ibeta, tpa, tpb, tna, tnb;
	static float ipx = 0, ipy = 0, inx = 0, iny = 0;

	clarke(ia, ib, &ialfa, &ibeta);
	sincos(VectorAngle, &sinval, &cosval);	//����PARK�任
	park(ialfa, ibeta, &ipd, &ipq, sinval, cosval);
#if 1
	sincos(-VectorAngle, &sinval, &cosval);	//����PARK�任
	park(ialfa, ibeta, &ind, &inq, sinval, cosval);
	sincos(2 * VectorAngle, &sinval, &cosval);	//����2W-PARK�任
	park(inx, iny, &tpa, &tpb, sinval, cosval);
	sincos(-2 * VectorAngle, &sinval, &cosval);	//����2W-PARK�任
	park(ipx, ipy, &tna, &tnb, sinval, cosval);

	ipx = DCL_runDF22(&DF22_Ihpd, ipd - tpa);
	ipy = DCL_runDF22(&DF22_Ihpq, ipq - tpb);
	inx = DCL_runDF22(&DF22_Ihnd, ind - tna);
	iny = DCL_runDF22(&DF22_Ihnq, inq - tnb);

	*pihd = ipd - tpa - ipx;
	*pihq = ipq - tpb - ipy;
#else
	ipx = DCL_runDF22(&DF22_Ihpd, ipd);
	ipy = DCL_runDF22(&DF22_Ihpq, ipq);
	*pihd = ipd - ipx;
	*pihq = ipq - ipy;
#endif

//	DispData1 = ix;
//	DispData2 = iy;

	sincos(VectorAngle, &sinval, &cosval);	//����PARK�任
	inv_park(tpa + ipx, tpb + ipy, &ialfa, &ibeta, sinval, cosval);
	inv_clarke(ialfa, ibeta, pifa, pifb);
}

