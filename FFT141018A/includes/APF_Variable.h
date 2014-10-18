/*
//###########################################################################
//
// FILE:  Variable.c
//
// DESCRIPTION:
//
//         including those variables used in the Communication test program
//
//###########################################################################
// $Author: Han bofoster $
// $Date: May  11, 2011$
// $Target System: DF28335 APF $
// $Version: v2.0 $
//###########################################################################

*/
//********************��ѹ���õ��ı���**************************
int     Reset=0;
float   CS=0;
float   x1=1;//��Ư
float   y1=1;//��ֵ
float   x2=1;
//float   y2=1;
float   A1=0;
float   A3=0;
float   A5=0;
float   A7=0;
float   A9=0;
float   A11=0;
float   A13=0;
float   A15=0;
float   A17=0;
float   A19=0;
float   A21=0;
float   A23=0;
float   A25=0;
int     graph=2;
int     FFT_Flag=0;
int     FFT=1;
int 	UDCADRF=0;             //ֱ�����ѹ������Ư��ֵ
float  	UDC_R=0;            //������Ӧ��ʵ�ʵ�ѹֵ
float  	UDC_Rf1=140;
float	UDC_Rf2=140;
			
float	UDC_Kp=200;
float	UDC_Ki=50;
float   I_Kp=8;
float   I_Ki=0;
float	UDC_erro_old=0;
float	UDC_erro_new=0;
float	Udc_slip=140;
float	Id_slip=0; 
float	Idref=0;		//Udc_PI������������Id_ref
float   Inref=0;        //Udc�������޷�
float   T_cout=0;
//float   Error_IA=0;
//float   Error_IB=0;
//float   Error_IC=0;
//********************��λ�����õ��ı���*************************
float	THETA_C=0;
float 	THETA_C_B = 0.0;
float	THETA_C_C = 0.0;
float   Omiga_t=0;
//float   Omiga_t2=0;
int     PLL=1;
float   invented_integral=0;
float  	UAADRF=0;
float	UBADRF=0;
float	UCADRF=0;

float	U1_a=0;		//������ѹ
float	U1_b=0;
float	U1_c=0;

float   Ua_APF=0;
float   Ub_APF=0;
float   Uc_APF=0; 
float   U0_APF = 0;

float	LS1=0;		//���ྲֹ�����µ���ʱ�洢����
float	LS2=0;
float	LS3=0;

float I_temp1=0;    //����һ��
float I_temp2=0;
float temp3=0;
float temp4=0;

float Ih_a=0;       //�������ֵ
float Ih_b=0;
float Ih_c=0;
float I1_aqf_f = 0;
float I1_bqf_f = 0;
float I1_cqf_f = 0;
float Ihw_a = 0;
float Ihw_b = 0;
float Ihw_c = 0; 
float Ih_0=0;
float If_a=0;
float If_b=0;
float If_c=0;
float If_0=0;
float In_d=0;


float I1d[3] = {0};
float I1df[2] = {0};
float I1q[3] = {0};
float I1qf[2] = {0};
float IA_d[30]={0};
float IA_q[30]={0};
float IB_d[30]={0};
float IB_q[30]={0};
float IC_d[30]={0};
float IC_q[30]={0};
float IA3=0;
float IA5=0;
float IA7=0;
float IA9=0;
float IA11=0;
float IA13=0;
float IA15=0;
float IA17_25=0;
float IB3=0;
float IB5=0;
float IB7=0;
float IB9=0;
float IB11=0;
float IB13=0;
float IB15=0;
float IB17_25=0;
float IC3=0;
float IC5=0;
float IC7=0;
float IC9=0;
float IC11=0;
float IC13=0;
float IC15=0;
float IC17_25=0;
float I03=0;
float I05=0;
float I07=0;
float I09=0;
float I011=0;
float I013=0;
float I015=0;
float IAh_Vector=0;
float IBh_Vector=0;
float ICh_Vector=0;
float I0h_Vector=0;
int flag_0=0;
float IA1=0;
float IB1=0;
float IC1=0;
float IA_Vector=0;
float IB_Vector=0;
float IC_Vector=0;
float I0_Vector=0;
float I_Limit=0;
float I01_d=0;
float I01_q=0;
float I01=0;
//*******************ȫ�������������������*******************************


float reactive_filter_buffer[3][4]={0};

	//**************�ִβ������ñ���**********************(��������)
	float IAh = 0;
	float IAdh = 0;
	float IAqh = 0;
	float IBh = 0;
	float IBdh = 0;
	float IBqh = 0;
	float ICh = 0;
	float ICdh = 0;
	float ICqh = 0;
	float IAh_Sum = 0;
	float IBh_Sum = 0;
	float ICh_Sum = 0;
	float IAh_Sum1 = 0;
	float IBh_Sum1 = 0;
	float ICh_Sum1 = 0;
	float IAh_Part_Sum = 0;
	float IBh_Part_Sum = 0;
	float ICh_Part_Sum = 0;

	float FilterPara1[6] = {0}; //�ִβ����˲����ֵ��¼����
	float FilterPara2[6] = {0};
//	float FilterPara3[6] = {0};
//	float FilterPara4[6] = {0};
//	float FilterPara5[6] = {0};

//***********�ִβ����˲�ʱ����¼�˲�����ֵ����ǰһ����ǰ2�������˲����ֵ��ǰ2����***
//float In1_d[3] = {0};
//float In1_df[2] = {0};
//float In1_q[3] = {0};
//float In1_qf[2] = {0};

//float In2_d[3] = {0};
//float In2_df[2] = {0};
//float In2_q[3] = {0};
//float In2_qf[2] = {0};

//float In3_d[3] = {0};
//float In3_df[2] = {0};
//float In3_q[3] = {0};
//float In3_qf[2] = {0};

//float In4_d[3] = {0};
//float In4_df[2] = {0};
//float In4_q[3] = {0};
//float In4_qf[2] = {0};
//***********************�ִβ����˲����������������***************

float In_q=0;
float cosVal=0;
float sinVal=0;
float In_a=0;
float In_b=0;
float In_df=0;
float In_qf=0;
float Irm[25]={0};
float Ih_d=0;
float Ih_q=0;

float I1_a=0; //���ྲֹ����ϵ�µ���ʱ����
float I1_b=0; 
float I1_adf=0;
float I1_aqf=0;
float I1_bdf=0;
float I1_bqf=0; 
float I1_cdf=0;
float I1_cqf=0;
float I1_d=0;
float I1_q=0;



int 	CROSS_IH=0; 
int 	CROSS_TOTAL=0; 
int 	CROSS_SUM=0; 
int 	CROSS_ZERO=0;
int		CROSS_FLAG=0;
int     THETA_0=0;
int     THETA_1=0; 
int 	n_cycle=0;
int 	m_cycle=0;
//int     j_cycle=0;
int 	EXT_count=2;  
float	I_H_A[361]={0};
float	I_H_B[361]={0};
float	I_H_C[361]={0};
//float   I_H_0[270]={0};
int Leading_Comp_Flag = 1; 

//float Ih5_CF;
float Ih_beta=0;
float Ih_alpha=0;
float Ih_0x = 0;
int AD_result[8]={0};
int DA_date[8]={0};
float IAADRF=0;
float IBADRF=0;
float ICADRF=0;
float I0ADRF=0;
float IAAPF=0;
float IBAPF=0;
float ICAPF=0;
float I0APF=0;
int Com_rate1=0;
/*
int com=0;
int Run_Stop_Flag=0;
int display_date_one[10]={0xAA,0x55,0x01,0x02,0x03,0x04,0x05,0x06,0x07,0x08};
int display_date_two[10]={0xAA,0x55,0x01,0x02,0x03,0x04,0x05,0x06,0x07,0x08};
int Parameters[10]={0};

int m=0;        //
int n=0;    	//��delay_t����ʹ��
int i=0;*/

//float graph_data[300]={0};
int ReceivedChar=0;
//float graph_data1[300]={0};
//float graph_data2[300]={0};
float graph_data[500]={0};
float graph_data1[500]={0};
float graph_data2[500]= {0}; 




float UDC_Max = 0;
float Ih_Max = 0;
float U_FtoI = 0;
float UDCREF = 0;
float Ih_Limit = 0;		//��������޷�ֵ
//int Limit_Flag = 0.0;		//�������б��λ
//float If_Limit = 0.0;		//�޹����������޷�
//float If_alpha = 0.0;		//�޹�ָ��ֵ
//float If_beta = 0.0;
float Ih_d_Limit=0;
float Ih_q_Limit=0;
float I1_d_square=0;
float I1_q_square=0;
float I1_Square = 0.0;
float Ih_Limit_square = 0.0;
float I1_Value = 0.0;
float Phi_Limit = 0.0;



//ͨ�����
int com=0;
int com1=0;
int Run_Stop_Flag=0;
int Reactive_Power=0;
int Para_SET=0;
//int Fault_flag=0;
int Receive_date_error=0;
int Com_date[30]={0};
int Read_control[7]={0x1B,0x52,0x00,0x64,0x00,0x01,0xD3};
int display_date_one[14]={0x01,0x7C,0x01,0x7C,0x01,0x7C,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00};
int display_date_two[40]={0x00,0x00,0x00,0x00,0x00,0x00,0x01,0x00,0x00,0x32,0x00,0x00};
int Para1_set[9]={0x1B,0x57,0x00,0xAA,0x00,0x01,0x00,0x01,0x8D};
int Para2_set[9]={0x1B,0x57,0x00,0xAA,0x00,0x01,0x00,0x02,0x8D};
int Para1_Intdate[40]={0x1B,0x57,0x00,0x96,0x00,0x05,0x00,0xC8,0x00,0xFA,0x00,0x02,0x00,0x3C,0x00,0x00,0x8D};
int Para2_Intdate[15]={0x1B,0x57,0x00,0xC8,0x00,0x04,0x00,0x64,0x00,0x32,0x01,0x40,0x00,0x8C,0x8D};
//int Current_IA[202]={0};
//int Current_IB[202]={0};
//int Current_IC[202]={0};
//int Current_I0[202]={0}; 
int C_data_count1=0;
int C_data_count2=0;
int C_data_count3=0;
int COM_UDCREF=0; //150
int COM_Ih_max=0;	//151
int C_way=0;	//152  .1=1ȫ����1=0�ִβ�  ��3=1 ���������޹�
int COM_ALL_rate=0;	//153
int COM_EXT_count=0; //154
int COM_IHB_RATE=0;  //155
int COM_UDC_Max=0;	//156
int COM_IH1=0;		//157
int COM_IH1_RATE=0;	//158
int COM_IH2=0;		//159
int COM_IH2_RATE=0;	//160 
int COM_IH3=0;		//161
int COM_IH3_RATE=0;	//162
int COM_IH4=0;		//163
int COM_IH4_RATE=0;	//164
int COM_Kp=0;	//200
int COM_ki=0;	//201 
int COM_Udb=0;	//202
int COM_Ua=0;	//203
int COM_Tu=0;	//204
int COM_Ti=0;
//int Current_Kp=0; 	//205
int COM_Iz=0;	//206
int COM_Uz=0; 	//207
int COM_U=0;    //UABC 
int COM_UAB=0; 	//������ѹa  
int COM_UBC=0;	//������ѹb
int COM_UCA=0;	//������ѹc
int COM_IA=0;	//
int COM_IB=0;
int COM_IC=0;
int COM_I0=0;
int COM_Udc=0;
float COM_Udc1=0;
int ERROR_flag=0;
int Wrong_Flag = 0;
int Wrong_Temp = 0;
int INRL_data=0;
int Current_flag=0;
int Init_para_flag=0;
//********************THDֵ��ʾ���ñ���*************************
int  THD_IA=0;
int  THD_IB=0;
int  THD_IC=0;
int  THD_I0=0;
int  THD_IA3=0;
int  THD_IA5=0;
int  THD_IA7=0;
int  THD_IA9=0;
int  THD_IA11=0;
int CompensateA= 0;//�������������Чֵ
int CompensateB= 0;
int CompensateC= 0;
//********************����ֵ��ʾ��ñ���************************* 


int m=0;        //
int n=0;    	//��delay_t����ʹ��
int i=0;

int display_flag=0;

float I1_df=0;
float I1_qf=0;

int T_Flag=0;
float T_cout_U=0;
//***********************�˵�����ѹ�漰���ı���******************************
int BiCount=0; //�ö��ַ����㿪���ŵļ���ֵ
float LineVolSquare=0;  //�������ѹ��ƽ��
float BiVari=0;  //�ö��ַ����㿪ƽ��ʱ��м����
float BiMinInitial=0; //�ö��ַ����㿪ƽ��ʱ����С��ʼֵ
float BiMaxInitial=1000; // �ö��ַ����㿪ƽ��ʱ������ʼֵ
float alpha=0;   //��3/2�任�õ���ֵ��ƽ��
float belta=0;   //��3/2�任�õ���ֵ��ƽ��
//**********************end****************************888
float tempIdref = 0;

//*******************��Ư����****************************
/*float UAB_Fx[3] = {0};
float UAB_Fy[2] = {0};
float UBC_Fx[3] = {0};
float UBC_Fy[2] = {0};
float UCA_Fx[3] = {0};
float UCA_Fy[2] = {0};

float IA_Fx[3] = {0};
float IA_Fy[2] = {0};
float IB_Fx[3] = {0};
float IB_Fy[2] = {0};
float IC_Fx[3] = {0};
float IC_Fy[2] = {0};

float IAF_Fx[3] = {0};
float IAF_Fy[2] = {0};
float IBF_Fx[3] = {0};
float IBF_Fy[2] = {0};
float ICF_Fx[3] = {0};
float ICF_Fy[2] = {0};
float I0F_Fx[3] = {0};
float I0F_Fy[2] = {0};
*/
float UAB_Sum = 0;
float UBC_Sum = 0;
float UCA_Sum = 0;
float IA_Sum = 0;
float IB_Sum = 0;
float IC_Sum = 0;
float IAF_Sum = 0;
float IBF_Sum = 0;
float ICF_Sum = 0;
float I0F_Sum = 0;

//float UA_Z = 0;
//float UB_Z = 0;
//float UC_Z = 0;
//float IA_Z = 0;
//float IB_Z = 0;
//float IC_Z = 0;
//float IAF_Z = 0;
//float IBF_Z = 0;
//float ICF_Z = 0;
//float I0F_Z = 0;

unsigned CountCmpar2 = 0;
unsigned CountCmpar1 = 0;

//**************************APF�������ݿ�**************************
struct SystemPara 
{
   const unsigned int  DramAddr;//������Dram�еĵ�ַ
   const unsigned int  Rom_P_Addr;//������E2PROM��ҳ��ַ
   const unsigned int  Rom_O_Addr;//������E2PROM��ҳ��ƫ�Ƶ�ַ
   const unsigned int  ScreenAddr;//�����ڴ������ϵĵ�ַ
   const int  FactoryDefault;//��������ֵ
   const int  Max;//���������ֵ
   const int  Min;//��������Сֵ           
};
struct SystemPara  UDCREF_Ref = {1,4,0x10,150,650,600,800}; //����UDCREF_RefΪ�ṹ������

//***********************APF�������ݿ����***************************

//*********************EEPROM���***************************
int Factory_Flag = 0;//������־
int EEPROM_Compare = 0;//�ж��Ƿ񽫲���д��EEPROM
//*******************EEPROM��ؽ���*************************

//*************��ABC����ϵ�µ�����PI��Ϊpq����ϵ�µ�����PI���õ��Ĳ���****
float PI_alpha = 0;//alpha��PI���������
float PI_beta = 0;//beta��PI���������
/*float Udc_d = 0;//��ѹָ��d�����
float Udc_q = 0;//��ѹָ��q�����
float Id_apf = 0; //APF���������������d�������
float Iq_apf = 0; //APF���������������q�������
float Ih_d_c = 0; //dq����ϵ��г������ָ��,d��
float Ih_q_c = 0; //dq����ϵ��г������ָ��,q��
float Ih_d_c_new = 0; //��������d�ᵱǰָ��
float Ih_q_c_new = 0; //��������q�ᵱǰָ��
*/
//float I_H_d_c[361] = {0}; //���ڴ洢��ǰ���ڵ�dq��Ĳ���ָ��
//float I_H_q_c[361] = {0};
int   NewCount = 0; //��ǰ��ȡ�Ĳ�����ı��
float Us_d = 0; //�������ѹ��d�����
float Us_q = 0; //�������ѹ��q�����
float ModuComdA = 0;//�����ز��ĵ��Ʋ���A�ࣩ
float ModuComdB = 0;//�����ز��ĵ��Ʋ���B�ࣩ
float ModuComdC = 0;//�����ز��ĵ��Ʋ���C�ࣩ
float ModuComd0 = 0;//�����ز��ĵ��Ʋ���0�ࣩ
float ModuComdA1 = 0; //�����ظ��������
float ModuComdB1 = 0;
float ModuComdC1 = 0;
//******************************����***************************************

//************reboot �Զ�������ز���**************
unsigned int lack_phase_check=0;//����ȱ����
float cycle_point=250;//ÿ����ѹ���ڵĲ�������
float tempp3=0;//ȱ�����õ��ı���
float Rebt_cout_Add=0;
float Rebt_cout_Add1=0;//������
int Rebt_Cout=0;  //
int Reboot_flag=0;//������ÿ���ϵ������ģʽ��ֻ��ģ��帴λһ��
int Ltime_Lack_Phase=0;//��¼�ϴ�ȱ����Ϣ
int Lack_Phase=0;//����ȱ����Ϣ
int L_Reboot_Mode_Set=0;//EEPROM�м�¼���ϴε������趨��Ϣ
int Reboot_Mode_Set=0;//���������Զ�����ģʽ
float Delay_Rebt_Add=0;
float Delay_Rebt_Add1=0;
int WR_Error_Count=0;
int Reset_Count=0;//�����жϵ����Ƿ���ȫ���磬��ȫ��������¿�����������ģʽ�½���λһ��ģ���
float Fault_flag0 = 0;
float Fault_flag = 0;
float L_Fault_flag = 0;
int Fault_Count = 0;//��¼�������ֲ���ȫ����Ĵ���
float Delay_Rebt_Add2 = 0;
float Delay_Rebt_Add3 = 0;
int Reboot_Run = 0;//���ڳ�������
int Reboot_Run_Lamp = 0;
int Initial_Reset = 0;//�����ϵ�ʱ��ģ��帴λһ��

int Reboot_Count_Down=0;
int PowerFailRecord = 0;//��ǰ�������ϼ�¼
int L_PowerFailRecord = 0;//ǰһ�ε������ϼ�¼
int FaultCtrlVari = 0;  //FaultCtrlVari������Ϊ���Ʊ�����Ŀ���Ƿ�������ѭ�����жϵ�������
//int PF_Flag = 0;
//**************************end*********************************//

//************************�ظ����������õ��ı���*******************
//float alpha_New_error = 0; // alpha,beta����ϵ�µ������ĵ�ǰ���
//float beta_New_error = 0;

//int Repiti_Count = 0; //�ظ���������һ�������ڵĵ�ǰ��������
//int Repiti_lead = 3; //�ظ��������ĳ�ǰ����
//int CycleErrorHit = 0;
//float Qz = 0.95; //�ظ����Ƶ�Q(z)����
//float Kr = 0.6;  //�ظ����������������ֲ���
//float Repiti_alpha_CycleOut[251] = {0}; //alpha,beta����ϵ���ظ��������ϸ����ڵ����ֵ
//float Repiti_beta_CycleOut[251] = {0};
//float alpha_Cycle_error[251] = {0}; //alpha,beta����ϵ���ظ��������ϸ����ڵ����ֵ
//float beta_Cycle_error[251] = {0};
float Repiti_alpha_NewOut = 0; //alpha,beta����ϵ���ظ������������ֵ
float Repiti_beta_NewOut = 0;
int Repiti_Sign = 0;//�ظ����Ʊ�־λ
//******************************����*******************************

//***********************������ѹ��ʾֵ�����õ��ı���*****************
float UA_Display = 0;
float UB_Display = 0;
float UC_Display = 0;
//************************����****************************************

//**************���������ѹ��ʾ�õ��ı���****************************
float DisplayLS1 = 0;
float DisplayLS2 = 0;
//*********************����*******************************************


//************************ֱ�����ѹ����ָ��ʱ�����***********
int UDC_Count = 0;
//************************����**********************************


//************************Filter_All****************************
/*float Filter_All_X1[3] = {0};
float Filter_All_X2[3] = {0};
float Filter_All_X3[3] = {0};
float Filter_All_X4[3] = {0};
float Filter_All_X5[3] = {0};
float Filter_All_X6[3] = {0};
float Filter_All_Y1[3] = {0};
float Filter_All_Y2[3] = {0};
float Filter_All_Y3[3] = {0};
float Filter_All_Y4[3] = {0};
float Filter_All_Y5[3] = {0};
float Filter_All_Y6[3] = {0};
*/
//***************************END********************************

//**************************����******************************

//***************�ִβ�����alpha��beta����ϵ����PI�������õ��ı���********
float I_apf_alpha = 0;
float I_apf_beta = 0;
float I_apf_0 = 0;
float Udc_alpha = 0;
float Udc_beta = 0;
float Comd_alpha = 0;
float Comd_beta = 0;
float Comd_0 = 0;
//************************����***************************

//********************���㹦������*************************
float Power_Factor = 99.0;//��������
float Factor = 0.0; 
float I_fundmental = 0.0;
float I_lade_d = 1.0; //���ڼ��㸺�ع�������
float I_lade_q = 1.0;
float I_lade_r = 1.0;
// ********************end*************************
//********************����޹�����*************//

float IA_Past[61]={0};
float IB_Past[61]={0};
float IC_Past[61]={0};
int iqflag=0;
		
float IAADRF_Past=0;
float IBADRF_Past=0;
float ICADRF_Past=0;
// ********************end*************************

