/*
 * my_panel3.c
 *
 *  Created on: 2014��4��3��
 *      Author: Administrator
 */

#include <includes.h>


static void button_return_menu(struct rtgui_object *object,
		struct rtgui_event *event)
{
	rtgui_notebook_set_current(the_notebook, RTGUI_WIDGET(Container[0]));
}

static void button_view_state(struct rtgui_object *object,
		struct rtgui_event *event)
{
	rtgui_notebook_set_current(the_notebook, RTGUI_WIDGET(Container[4]));
}


static void button_previous_page(struct rtgui_object *object,
		struct rtgui_event *event)
{
	uint16_t num;

	if (listctrl_allnode->current_item < listctrl_allnode->page_items)
		num = 0;
	else
		num = listctrl_allnode->current_item - listctrl_allnode->page_items;
	rtgui_listctrl_set_current_item(listctrl_allnode,num);
}

static void button_next_page(struct rtgui_object *object,
		struct rtgui_event *event)
{
	uint16_t num;
	num = listctrl_allnode->current_item + listctrl_allnode->page_items;
	if (num >= listctrl_allnode->items_count)
		num = listctrl_allnode->items_count -1;
	rtgui_listctrl_set_current_item(listctrl_allnode,num);
}

static void _rtgui_listctrl_item_draw(struct rtgui_listctrl *list,
		struct rtgui_dc *dc, rtgui_rect_t *rect, rt_uint16_t index)
{
	char show_str[8];
	rtgui_rect_t item_rect;
	NODE_DATA *item,*items;

	item_rect = *rect;
	item_rect.x1 += 5;
	items = list->items;
	item = &items[index];

	/* draw text */
	rt_snprintf(show_str, sizeof(show_str), "%d", item->num);
	rtgui_dc_draw_text(dc, show_str, &item_rect);
	item_rect.x1 = 55;
	rtgui_dc_draw_vline(dc, item_rect.x1, item_rect.y1, item_rect.y2);

	item_rect.x1 = 60;
	rt_snprintf(show_str, sizeof(show_str), "%d", item->temperature);
	rtgui_dc_draw_text(dc, show_str, &item_rect);
	item_rect.x1 = 115;
	rtgui_dc_draw_vline(dc, item_rect.x1, item_rect.y1, item_rect.y2);

	item_rect.x1 += 5;
	rt_snprintf(show_str, sizeof(show_str), "%d", item->state);
	rtgui_dc_draw_text(dc, show_str, &item_rect);
	item_rect.x1 = 175;
	rtgui_dc_draw_vline(dc, item_rect.x1, item_rect.y1, item_rect.y2);

	item_rect.x1 += 5;
	rt_snprintf(show_str, sizeof(show_str), "%d", item->signal_intensity);
	rtgui_dc_draw_text(dc, show_str, &item_rect);
}

static rt_bool_t on_items(struct rtgui_object *object,
		struct rtgui_event *event)
{
	rtgui_listctrl_t *ctrl;
	/* get listctrl */
	ctrl = RTGUI_LISTCTRL(object);

	NodeList->current = ctrl->current_item;

	/* ��ӡ��ǰ���� */
	rt_kprintf("current item: %d\n", ctrl->current_item);

	return RT_TRUE;
}


rtgui_container_t *my_view3(void)
{
	rtgui_rect_t rect;
	rtgui_container_t *container;
	rtgui_label_t *label;
	struct rtgui_widget *widget;
	struct rtgui_dc *dc;
	rtgui_button_t *button;
	struct rtgui_staticline *line;

	/*�������ҳ������������ڹ��������ؼ�*/
	container = rtgui_container_create();
	if (container == RT_NULL)
		return RT_NULL;
	/*�����ҳ����������뵽notebook�У��Ա��ڷ�ҳ*/
	rtgui_notebook_add(the_notebook, "State Inquery", RTGUI_WIDGET(container));
	{
		/*��ȡҳ��Ļ�ͼ����*/
		rtgui_widget_get_rect(RTGUI_WIDGET(container), &rect);
		rtgui_widget_rect_to_device(RTGUI_WIDGET(container), &rect);
		rect.x1 += 5;
		rect.x2 -= 5;
		rect.y1 += 10;
		rect.y2 = rect.y1 + 20;
		label = rtgui_label_create("��ӭʹ�����߲���ϵͳ");
		RTGUI_WIDGET_TEXTALIGN(label) = RTGUI_ALIGN_CENTER_HORIZONTAL;	//���Ķ���
		rtgui_widget_set_rect(RTGUI_WIDGET(label), &rect);
		/* container��һ��container�ؼ�������add_child����������label�ؼ� */
		rtgui_container_add_child(container, RTGUI_WIDGET(label));

		rect.x1 = 5;
		rect.x2 = 235;
		rect.y1 = 30, rect.y2 = 35;
		line = rtgui_staticline_create(RTGUI_HORIZONTAL);
		/* ���þ�̬�ߵ�λ����Ϣ */
		rtgui_widget_set_rect(RTGUI_WIDGET(line), &rect);
		/* ��Ӿ�̬�ߵ���ͼ�� */
		rtgui_container_add_child(container, RTGUI_WIDGET(line));
	}
	{
		rect.x1 = 0, rect.x2 = 47;
		rect.y1 = 0;
		rect.y2 = rect.y1 + 20;
		rtgui_rect_moveto(&rect, 0, 45);
		label = rtgui_label_create("�ڵ�");
		RTGUI_WIDGET_TEXTALIGN(label) = RTGUI_ALIGN_CENTER_HORIZONTAL;	//���Ķ���
		rtgui_widget_set_rect(RTGUI_WIDGET(label), &rect);
		/* container��һ��container�ؼ�������add_child����������label�ؼ� */
		rtgui_container_add_child(container, RTGUI_WIDGET(label));
	}
	{
		rect.x1 = 0, rect.x2 = 47;
		rect.y1 = 0;
		rect.y2 = rect.y1 + 20;
		rtgui_rect_moveto(&rect, 48, 45);
		label = rtgui_label_create("����");
		RTGUI_WIDGET_TEXTALIGN(label) = RTGUI_ALIGN_CENTER_HORIZONTAL;	//���Ķ���
		rtgui_widget_set_rect(RTGUI_WIDGET(label), &rect);
		/* container��һ��container�ؼ�������add_child����������label�ؼ� */
		rtgui_container_add_child(container, RTGUI_WIDGET(label));
	}
	{
		rect.x1 = 0, rect.x2 = 47;
		rect.y1 = 0;
		rect.y2 = rect.y1 + 20;
		rtgui_rect_moveto(&rect, 96, 45);
		label = rtgui_label_create("ĸ��");
		RTGUI_WIDGET_TEXTALIGN(label) = RTGUI_ALIGN_CENTER_HORIZONTAL;	//���Ķ���
		rtgui_widget_set_rect(RTGUI_WIDGET(label), &rect);
		/* container��һ��container�ؼ�������add_child����������label�ؼ� */
		rtgui_container_add_child(container, RTGUI_WIDGET(label));
	}
	{
		rect.x1 = 0, rect.x2 = 47;
		rect.y1 = 0;
		rect.y2 = rect.y1 + 20;
		rtgui_rect_moveto(&rect, 144, 45);
		label = rtgui_label_create("״̬");
		RTGUI_WIDGET_TEXTALIGN(label) = RTGUI_ALIGN_CENTER_HORIZONTAL;	//���Ķ���
		rtgui_widget_set_rect(RTGUI_WIDGET(label), &rect);
		/* container��һ��container�ؼ�������add_child����������label�ؼ� */
		rtgui_container_add_child(container, RTGUI_WIDGET(label));
	}
	{
		rect.x1 = 0, rect.x2 = 47;
		rect.y1 = 0;
		rect.y2 = rect.y1 + 20;
		rtgui_rect_moveto(&rect, 192, 45);
		label = rtgui_label_create("�ź�");
		RTGUI_WIDGET_TEXTALIGN(label) = RTGUI_ALIGN_CENTER_HORIZONTAL;	//���Ķ���
		rtgui_widget_set_rect(RTGUI_WIDGET(label), &rect);
		/* container��һ��container�ؼ�������add_child����������label�ؼ� */
		rtgui_container_add_child(container, RTGUI_WIDGET(label));
	}

	/* �����ͼ��λ����Ϣ */
	rect.x1 = 5;
	rect.x2 = 235;
	rect.y1 = 75;
	rect.y2 = 250;
	listctrl_allnode = rtgui_listctrl_create(NodeList->node, NodeList->count,
			&rect,
			_rtgui_listctrl_item_draw);
	rtgui_listctrl_set_onitem(listctrl_allnode, on_items);
	/* container��һ��container�ؼ�������add_child����������listctrl�ؼ� */
	rtgui_container_add_child(container, RTGUI_WIDGET(listctrl_allnode));

	{
		rect.x1 = 0;
		rect.x2 = 40;
		rect.y1 = 0;
		rect.y2 = rect.y1 + 30;
		rtgui_rect_moveto(&rect, 5, 280);
		/* ����һ��button�ؼ� */
		button = rtgui_button_create("��ҳ");
		/* ����onbutton������button_view_state���� */
		rtgui_button_set_onbutton(button, button_previous_page);
		/* ����button��λ�� */
		rtgui_widget_set_rect(RTGUI_WIDGET(button), &rect);
		rtgui_container_add_child(container, RTGUI_WIDGET(button));
	}

	{
		rect.x1 = 0;
		rect.x2 = 40;
		rect.y1 = 0;
		rect.y2 = rect.y1 + 30;
		rtgui_rect_moveto(&rect, 69, 280);
		/* ����һ��button�ؼ� */
		button = rtgui_button_create("��ҳ");
		/* ����onbutton������button_view_state���� */
		rtgui_button_set_onbutton(button, button_next_page);
		/* ����button��λ�� */
		rtgui_widget_set_rect(RTGUI_WIDGET(button), &rect);
		rtgui_container_add_child(container, RTGUI_WIDGET(button));
	}

	{
		rect.x1 = 0;
		rect.x2 = 40;
		rect.y1 = 0;
		rect.y2 = rect.y1 + 30;
		rtgui_rect_moveto(&rect, 132, 280);
		/* ����һ��button�ؼ� */
		button = rtgui_button_create("�鿴");
		/* ����onbutton������button_view_state���� */
		rtgui_button_set_onbutton(button, button_view_state);
		/* ����button��λ�� */
		rtgui_widget_set_rect(RTGUI_WIDGET(button), &rect);
		rtgui_container_add_child(container, RTGUI_WIDGET(button));
	}

	{
		rect.x1 = 0;
		rect.x2 = 40;
		rect.y1 = 0;
		rect.y2 = rect.y1 + 30;
		rtgui_rect_moveto(&rect, 195, 280);
		/* ����һ��button�ؼ� */
		button = rtgui_button_create("����");
		/* ����onbutton������button_view_state���� */
		rtgui_button_set_onbutton(button, button_return_menu);
		/* ����button��λ�� */
		rtgui_widget_set_rect(RTGUI_WIDGET(button), &rect);
		rtgui_container_add_child(container, RTGUI_WIDGET(button));
	}

	return container;
}
