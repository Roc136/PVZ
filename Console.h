#pragma once
//��ʼ������
void initWindow();
//���ù��״̬
void setCursorHide(bool visible);
//���ù��λ�ã����Ͻ�Ϊ��0,0��
void setCursorPos(int x, int y);
//����������ɫ����ʵ��ʱ�ָ�Ĭ�ϣ�ֻ��һ��ʵ��ʱ����ǰ��ɫ������������һ��ǰ��ɫ���ڶ�������ɫ
void setColor(int font_color = 0xf, int background_color = 0);