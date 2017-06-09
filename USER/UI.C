/************************************************************
* 文件名称: UI.C
* 作者: 周晨阳
* 版本: 1.0
* 日期: 2017/5/21
* 描述: // 菜单的ui界面绘制文件
* 历史修改记录: // 历史修改记录
* <作者> <时间> <版本 > <描述>
* 周晨阳 2017/5/21 添加了此文件说明注释
***********************************************************/

#include "UI.H"
//初始界面绘制函数
void uiDraw(void)
{
	WINDOWS  test;    //新建一个窗口ui

	test.x = 0;
	test.y = 0;
	test.with = 100;
	test.hight = 50;
	test.title = "this";
	test.state = "test";
	GUI_SetColor(1, 0);  //设置前景色和背景色
//	GUI_Rectangle(30,30,60,60,1);
//GUI_PutString(0,0,"12345");
	GUI_WindowsDraw(&test); //绘制窗口ui
  // GUI_Button_OK(1,1);
	LCD_UpdateAll();//更新lcd

}
