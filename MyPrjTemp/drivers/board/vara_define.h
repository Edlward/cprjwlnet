/*
 * vara_define.h
 *
 *  Created on: 2013��12��9��
 *      Author: Administrator
 */

#ifndef VARA_DEFINE_H_
#define VARA_DEFINE_H_

#ifdef   APP_GLOBALS
	#define  APP_EXT
#else
	#define  APP_EXT extern
#endif

typedef struct node_data
{
	uint16_t num;
	uint16_t temperature;
	long address;
	long name;
	uint8_t state;
	uint8_t signal_intensity;
	uint8_t relative_alarm_value;
	uint8_t abs_alram_value;
} NODE_DATA;

typedef struct node_list
{
	NODE_DATA node[1024];
	uint16_t count;
	uint16_t current;
	NODE_DATA *error_node[1024];
	uint16_t error_num;
} NODE_LIST;

typedef struct rf_packet{
	uint16_t dst_addr;
	uint16_t src_addr;
	uint16_t temperature;
	uint8_t state;
}RF_DATA;

APP_EXT uint16_t NodeNums;			//���½ڵ����
APP_EXT uint16_t ErrorNodeNums;		//�쳣�ڵ����
APP_EXT uint16_t NodeInNets;		//���������Ľڵ�
APP_EXT volatile NODE_LIST * NodeList;

APP_EXT struct rt_semaphore rf_sem;



#endif /* VARA_DEFINE_H_ */
