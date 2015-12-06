/*
 * APF_Define.h
 *
 *  Created on: 2015��2��3��
 *      Author: Administrator
 */

#ifndef APF_DEFINE_H_
#define APF_DEFINE_H_


#define APF_SWITCH_FREQ				(256*50)	//APF�Ŀ���Ƶ��
#define GID_FREQUENCE				(50)		//����Ƶ��
#define FFT_LENGTH					256
#define DC_MIN_VOLTAGE				200			//ֱ��ĸ����͵�ѹ
#define DC_REF_DEFAULT				330			//Ĭ��ֱ��ĸ�߸�����ѹ
#define Q_REF_DEFAULT				1			//�޹�����Ĭ�ϸ���ֵ

#define APF_SWITCH_PERIOD			(1.0 / APF_SWITCH_FREQ)
#define POINT_NUM					(APF_SWITCH_FREQ / GID_FREQUENCE)
#define APF_STATE_BIT_STOP			1	//APF����ֹͣ��־λ 0:APF����
#define APF_STATE_BIT_SWSTOP		2	//APF��ֹͣ��־λ	1:APFֹͣ
#define APF_STATE_BIT_OC			4	//APF������־λ		1:APF����
#define APF_STATE_BIT_OV			8	//APFֱ��ĸ�߹�ѹ��־λ	1:APF��ѹ


#define DISABLE			0
#define ENABLE			(!DISABLE)
#define SET				1
#define RESET			0




#endif /* APF_DEFINE_H_ */
