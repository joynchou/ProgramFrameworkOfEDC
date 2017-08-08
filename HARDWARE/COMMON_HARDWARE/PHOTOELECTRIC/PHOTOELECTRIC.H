#ifndef __PHOTOELECTRIC_H__
#define __PHOTOELECTRIC_H__

#include "../BSP/BSP.H"

/*************************************************使用前需设定各光电门所对应的引脚********************************************/
#define ELECTRTIC_1 P50//各光电设备对应的引脚
#define ELECTRTIC_2 P31//
#define ELECTRTIC_3 P32//
#define ELECTRTIC_4 P33//
#define ELECTRTIC_5 P34//
#define ELECTRTIC_6 P35//
#define ELECTRTIC_7 P36//
#define ELECTRTIC_8 P37//
#define PHOTOELE_NUM 1//光电设备总数，禁止超过8
#define PHOTOELE_1 0//
#define PHOTOELE_2 1//
#define PHOTOELE_3 2//
#define PHOTOELE_4 3//
#define PHOTOELE_5 4//
#define PHOTOELE_6 5//
#define PHOTOELE_7 6//
#define PHOTOELE_8 7//

/*
使用方法:

  PhotoElectricScan(void);//此函数加入实时运行进程
	例：
	void task_N(void) _task_ PhotoElectScan
	{
		while(1)
		{
			PhotoElectricScan();
			os_wait(K_TMO,5,0);
		}
	}
	
	加入扫描后使用启用函数openPhotoEleMod()或openAllPhotoEleMod(u8 PHOTOELE_N)否则数据无效
	
*/

void PhotoElectricScan(void);//光电设备状态扫描
u8 getNightEleState(void);//获取全部光电设备的状态
u8 getPhotoEleState(u8 PHOTOELE_N);//获取某个光电门的状态
void closeAllPhotoEleMod();//禁用所有光电门
void openAllPhotoEleMod();//启用所有光电门
void closePhotoEleMod(u8 PHOTOELE_N);//禁用单个光电门
void openPhotoEleMod(u8 PHOTOELE_N);//启用某个光电门
