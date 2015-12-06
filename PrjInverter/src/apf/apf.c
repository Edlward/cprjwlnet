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
static float UdcRampRef;

static float GetPllAngle(void);
static void Para_Init(void);
static void PID_Init(void);
static float GetPllAngle(void);

interrupt void FaultProcess(void)
{

	EPwm2Regs.AQCSFRC.bit.CSFA = 1;	//�������ǿ��Ϊ��
	EPwm3Regs.AQCSFRC.bit.CSFA = 1;
	EPwm4Regs.AQCSFRC.bit.CSFA = 1;
	EPwm6Regs.AQCSFRC.bit.CSFA = 1;
	EPwm7Regs.AQCSFRC.bit.CSFA = 1;
	EPwm8Regs.AQCSFRC.bit.CSFA = 1;

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
	float temp_sum_d = 0, temp_sum_q = 0;
	float temp_a, temp_b, temp_c;
	float sinVal, cosVal;
	float pwm_a, pwm_b, pwm_c;
	float iha, ihb;
	Uint16 temp;
	static Uint16 i;

	ADValueConvert();
	VectorAngle = GetPllAngle();	//�õ���ѹʸ���ļн�
	Udc_average = (UdcA + UdcB + UdcC) / 3;
	sincos(VectorAngle, &sinVal, &cosVal);
	clarke(Iapf_a, Iapf_b, &Iapf_alfa, &Iapf_beta);
//	HarmonicDetection(Iload_a, Iload_b, &iha, &ihb);
	GPIO_WritePin(58, 1);
	/******************************���APF�Ƿ��й��Ϸ���**************************************/
	if (GPIO_ReadPin(1) == DISABLE)
	{
		APF_State |= APF_STATE_BIT_OV;
	}
	if (GPIO_ReadPin(2) == DISABLE)
	{
		APF_State |= APF_STATE_BIT_OC;
	}
	/*****************************����APF��״̬���в���*************************************/
	if (0 == APF_State)	//���APF������
	{
		/*
		 * ֱ��ĸ��ƽ����ѹ����
		 */
		UdcRampRef += 60.0 * APF_SWITCH_PERIOD;	//1s�ڸ���ֵ������60V
		if (UdcRampRef > UdcRef)
		{
			UdcRampRef = UdcRef;
		}
		udcp_out = pid_calculate(&pid_instance_Udcp, Udc_average - UdcRampRef);
		/*
		 * �ظ� + PI ���Ͽ���
		 */
		if ((UdcRampRef == UdcRef) && ((UdcRef - Udc_average) < 30)
				&& ((UdcRef - Udc_average) > -30))	//ֻ����ѹ�����󣬲Ż����г������
		{
			compensatepercentage += 100.0 * APF_SWITCH_PERIOD;	//1s�ڰٷֱȻ�������100%
			if (compensatepercentage > CmpsateSet)
			{
				compensatepercentage = CmpsateSet;
			}
		}
		//�����ĸ���������ʱ�������ӣ����ǵ�ѹ�����������������뼴ʱ
		//		temp_d *= compensatepercentage * 0.01;
		//		temp_q *= compensatepercentage * 0.01;
//#if 1	//1��dq���½���г����������
		park(Iapf_alfa, Iapf_beta, &Iapf_d, &Iapf_q, sinVal, cosVal);

		/******************ֱ��ĸ�����ƽ����������������********************/
		clarke(Udc_average - UdcA, Udc_average - UdcB, &temp_alfa, &temp_beta);
		temp_alfa = pid_calculate(&pid_instance_Udcn_d, temp_alfa);
		temp_beta = pid_calculate(&pid_instance_Udcn_q, temp_beta);
		sincos(VectorAngle * 2, &sinVal, &cosVal);
		inv_park(temp_alfa, temp_beta, &temp_alfa, &temp_beta, sinVal, cosVal);
		/****************************dq���������******************************/
		temp_d = udcp_out - temp_alfa - Iapf_d;
		temp_q = temp_beta - Iapf_q
				+ QRef * compensatepercentage * 0.01 * 1.414213562f;
		temp_alfa = pid_calculate(&pid_instance_Ialfa, temp_d);
		temp_beta = pid_calculate(&pid_instance_Ibeta, temp_q);

//		RpBuffer[0][PointCnt] = temp_d + RpKr * RpBuffer[0][PointCnt];
//		RpBuffer[1][PointCnt] = temp_q + RpKr * RpBuffer[1][PointCnt];
//		//PI����
//		temp = (PointCnt + POINT_NUM - RpLeadingBeat) % POINT_NUM;
//		//�ظ��������Ľ����Ҫ�˲���ȥ����Ƶ����
//		iir_filter_calculate(&IIR_for_Rpcontroller[0], RpBuffer[0][temp],
//				&error_alfa);
//		iir_filter_calculate(&IIR_for_Rpcontroller[1], RpBuffer[1][temp],
//				&error_beta);
		temp_alfa += error_alfa * RpGain;
		temp_beta += error_beta * RpGain;
		/*****************************������任*******************************/
		sincos(VectorAngle, &sinVal, &cosVal);
		inv_park(temp_alfa, temp_beta, &temp_alfa, &temp_beta, sinVal, cosVal);
		inv_clarke(temp_alfa, temp_beta, &pwm_a, &pwm_b);

		pwm_a += Upcc_a;
		pwm_b += Upcc_b;
		pwm_c = -pwm_a - pwm_b;

		/*
		 * ���PWM���������Ա�ƵPWM����
		 */
		if (UdcA < DC_MIN_VOLTAGE)	//ֱ��ĸ�ߵĵ�ѹֵ����Ӧ����������ѹֵ
		{
			UdcA = DC_MIN_VOLTAGE;
		}
		if (UdcB < DC_MIN_VOLTAGE)
		{
			UdcB = DC_MIN_VOLTAGE;
		}
		if (UdcC < DC_MIN_VOLTAGE)
		{
			UdcC = DC_MIN_VOLTAGE;
		}
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

//		/* Main Output Enable */
//		EPwm2Regs.AQCSFRC.bit.CSFA = 0;	//�����ǿ��
//		EPwm3Regs.AQCSFRC.bit.CSFA = 0;
//		EPwm4Regs.AQCSFRC.bit.CSFA = 0;
//		EPwm6Regs.AQCSFRC.bit.CSFA = 0;
//		EPwm7Regs.AQCSFRC.bit.CSFA = 0;
//		EPwm8Regs.AQCSFRC.bit.CSFA = 0;

	}
	else
	{
		if ((APF_State & APF_STATE_BIT_STOP) == 0)	//���Է�ֹ�ظ�ִ�г�ʼ��
		{
			APF_State |= APF_STATE_BIT_STOP;
			/* Main Output Disable */
//			EPwm2Regs.AQCSFRC.bit.CSFA = 1;	//�������ǿ��Ϊ��
//			EPwm3Regs.AQCSFRC.bit.CSFA = 1;
//			EPwm4Regs.AQCSFRC.bit.CSFA = 1;
//			EPwm6Regs.AQCSFRC.bit.CSFA = 1;
//			EPwm7Regs.AQCSFRC.bit.CSFA = 1;
//			EPwm8Regs.AQCSFRC.bit.CSFA = 1;
			EPwm2Regs.CMPA.bit.CMPA = 400;
			EPwm3Regs.CMPA.bit.CMPA = 500;
			EPwm4Regs.CMPA.bit.CMPA = 600;
			EPwm6Regs.CMPA.bit.CMPA = 100;
			EPwm7Regs.CMPA.bit.CMPA = 200;
			EPwm8Regs.CMPA.bit.CMPA = 300;

			pid_reset(&pid_instance_Udcp);
			pid_reset(&pid_instance_Udcn_d);
			pid_reset(&pid_instance_Udcn_q);
			pid_reset(&pid_instance_Ialfa);
			pid_reset(&pid_instance_Ibeta);

//			memset_fast(RpBuffer[0], 0, POINT_NUM * 2);
//			memset_fast(RpBuffer[1], 0, POINT_NUM * 2);
		}
		UdcRampRef = Udc_average;
		compensatepercentage = 0;
	} /*end if (0 == APF_State)*/
	PointCnt = (PointCnt + 1) % POINT_NUM;
	GPIO_WritePin(58, 0);	//�鿴�¸����Ƴ�����ж�ʱ��

	DacaRegs.DACVALS.bit.DACVALS = Iapf_a + 2048;
	DacbRegs.DACVALS.bit.DACVALS = Iapf_b + 2048;
	DaccRegs.DACVALS.bit.DACVALS = Upcc_ab + 2048;
	i += 10;
	ExtDA_Output(0,i%8000);
	ExtDA_Output(4,i%8000);
//	ExtDA_Output(2,i++%2000);
//	ExtDA_Output(3,i++%1000);
//	ExtDA_Output(1,Iapf_b+4096);

	AdcaRegs.ADCINTFLGCLR.bit.ADCINT1 = 1; //clear INT1 flag
	PieCtrlRegs.PIEACK.all = PIEACK_GROUP1;

}
void APF_Init(void)
{
	Para_Init();
	PID_Init();
//	iir_filter_init();
//	memset_fast(&RpBuffer[0][0], 0, POINT_NUM * 2);
//	memset_fast(&RpBuffer[1][0], 0, POINT_NUM * 2);
	memset_fast(&Iload_d[0], 0, POINT_NUM * 2);
	memset_fast(&Iload_q[0], 0, POINT_NUM * 2);

}

static void Para_Init(void)
{
	Carrier_Wave_Count = 200000000 / 2 * 0.5 * APF_SWITCH_PERIOD - 1;

	UdcRef = DC_REF_DEFAULT;
	QRef = Q_REF_DEFAULT;
	CmpsateSet = 0;
	APF_State = APF_STATE_BIT_SWSTOP;

	RpGain = 0;
	RpKr = 0.98;
	RpLeadingBeat = 2;

}

static void PID_Init(void)
{
	pid_instance_Pll.Kp = 2;
	pid_instance_Pll.Ki = 5 * APF_SWITCH_PERIOD;
	pid_instance_Pll.Kd = 0;
	pid_init(&pid_instance_Pll, ENABLE);

	pid_instance_Ialfa.Kp = 8;
	pid_instance_Ialfa.Ki = 2 * APF_SWITCH_PERIOD;
	pid_instance_Ialfa.Kd = 0;
	pid_init(&pid_instance_Ialfa, ENABLE);

	pid_instance_Ibeta.Kp = 8;
	pid_instance_Ibeta.Ki = 2 * APF_SWITCH_PERIOD;
	pid_instance_Ibeta.Kd = 0;
	pid_init(&pid_instance_Ibeta, ENABLE);

	pid_instance_Udcp.Kp = 0.5;
	pid_instance_Udcp.Ki = 1 * APF_SWITCH_PERIOD;
	pid_instance_Udcp.Kd = 0;
	pid_init(&pid_instance_Udcp, ENABLE);

	pid_instance_Udcn_d.Kp = 0.5;
	pid_instance_Udcn_d.Ki = 1 * APF_SWITCH_PERIOD;
	pid_instance_Udcn_d.Kd = 0;
	pid_init(&pid_instance_Udcn_d, ENABLE);

	pid_instance_Udcn_q.Kp = 0.5;
	pid_instance_Udcn_q.Ki = 1 * APF_SWITCH_PERIOD;
	pid_instance_Udcn_q.Kd = 0;
	pid_init(&pid_instance_Udcn_q, ENABLE);
}
static float GetPllAngle(void)
{
	static float theta = 0;
	float power, w;

	power = -Upcc_ab * sin(theta) + Upcc_bc * sin(theta + 2.094395102f);
	w = pid_calculate(&pid_instance_Pll, power) + 100 * PI;
	theta += w * APF_SWITCH_PERIOD;
	if (theta > 2 * PI)
	{
		theta -= 2 * PI;
	}
	else if (theta < 0)
	{
		theta += 2 * PI;
	}

	return theta;
}
