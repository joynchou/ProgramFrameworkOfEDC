通用硬件层
BSP为下一层
上层代码只需要引入common_HD.h即可

注：TM1638模块的5个引脚与单片机的连接方式为
DIO = P1.0;
CLK = P1.1;
STB = P1.2;
VCC = VCC;
GND = GND;