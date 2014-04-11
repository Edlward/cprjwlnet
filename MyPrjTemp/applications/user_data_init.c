/*
 * user_data_init.c
 *
 *  Created on: 2014��4��5��
 *      Author: Administrator
 */

#include <includes.h>

void user_data_init(void)
{
	uint16_t i;
	int fd, size;
	uint8_t buffer[80], data, *ps[2], *buf, *sptr;
	char num;
	long pos;

	NodeList = (NODE_LIST*) rt_malloc(sizeof(NODE_LIST));

	if (NodeList == RT_NULL)
	{
		rt_kprintf("�ڴ治�㣡");
	}

	fd = open("/config.ini", O_RDONLY, 0);
	if (fd < 0)
	{
		rt_kprintf("û�������ļ�!");
	}
	else
	{
		pos = lseek(fd,0,DFS_SEEK_CUR);
		size = f_gets(fd, buffer);	//���ļ��ж�ȡһ���ַ�
		buf = buffer;
		while (size > 0)
		{
			//���ַ������зָ���ps[0]Ϊ���ƣ�ps[1]Ϊ��ֵ
			ps[0] = strtok_r(buf, " = ", &sptr);
			ps[1] = strtok_r(NULL, " = ", &sptr);
//			rt_kprintf("p[0]%s:[p1]%s",ps[0],ps[1]);
			if (strcmp(ps[0], "�ڵ���") == 0)
			{
				i = str2num(ps[1]);
				NodeList->node[i].num = i;
				rt_kprintf("�ڵ��ţ�%d\n", i);
			}
			else if (strcmp(ps[0], "��Ա����¶�") == 0)
			{
				num = str2num(ps[1]);
				NodeList->node[i].relative_alarm_value = num;
				rt_kprintf("��Ա����¶ȣ�%d\n", num);
			}
			else if (strcmp(ps[0], "���Ա����¶�") == 0)
			{
				num = str2num(ps[1]);
				NodeList->node[i].abs_alram_value = num;
				rt_kprintf("���Ա����¶ȣ�%d\n", num);
			}
			else if (strcmp(ps[0], "�ڵ��ַ") == 0)
			{
//				lseek(fd,pos,DFS_SEEK_SET);
//				f_gets(fd, buffer);
//				rt_kprintf("%s",buffer);
				NodeList->node[i].address = pos;
			}
			else if (strcmp(ps[0], "�ڵ�����") == 0)
			{
//				lseek(fd,pos,DFS_SEEK_SET);
//				f_gets(fd, buffer);
//				rt_kprintf("%s",buffer);
				NodeList->node[i].name = pos;
			}
			else if (strcmp(ps[0], "�ڵ���Ŀ") == 0)
			{
				num = str2num(ps[1]);
				NodeList->count = num;
			}
			pos = lseek(fd,0,DFS_SEEK_CUR);
			size = f_gets(fd, buffer);
			buf = buffer;
		}
		close(fd);
	}

	NodeList->current = 0;
	NodeList->error_num = 0;

	for (i = 0; i < NodeList->count; i++)
	{
		NodeList->node[i].num = i;
		NodeList->node[i].state = 0;
		NodeList->node[i].temperature = 25;
		NodeList->node[i].signal_intensity = 0;
		NodeList->error_node[i] = &NodeList->node[i];
	}

	fd = open("/data.dat", O_CREAT|O_RDWR, 0);
	rt_sprintf(buffer,"�ڵ�\t�¶�\t״̬\t��Ա����¶�\t���Ա����¶�\tʱ��\n");
	num = strlen(buffer);
	write(fd,buffer,num);
	rt_sprintf(buffer,"--------------------------------------------------------------\n");
	num = strlen(buffer);
	write(fd,buffer,num);
	close(fd);

	fd = open("/alarm.dat", O_CREAT|O_RDWR, 0);
	rt_sprintf(buffer,"�ڵ�\t�¶�\t״̬\t��Ա����¶�\t���Ա����¶�\tʱ��\n");
	num = strlen(buffer);
	write(fd,buffer,num);
	rt_sprintf(buffer,"--------------------------------------------------------------\n");
	num = strlen(buffer);
	write(fd,buffer,num);
	close(fd);
}
