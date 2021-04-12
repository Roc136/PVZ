#pragma once
//初始化窗口
void initWindow();
//设置光标状态
void setCursorHide(bool visible);
//设置光标位置，左上角为（0,0）
void setCursorPos(int x, int y);
//设置字体颜色，无实参时恢复默认，只有一个实参时设置前景色，两个参数第一个前景色，第二个背景色
void setColor(int font_color = 0xf, int background_color = 0);