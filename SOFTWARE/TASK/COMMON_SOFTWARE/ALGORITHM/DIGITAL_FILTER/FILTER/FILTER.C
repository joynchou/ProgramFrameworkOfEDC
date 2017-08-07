#include <math.h>

#include "FILTER.H"


//中位值平均滤波法（防脉冲干扰平均滤波法）
//方法解析：
//相当于中位值滤波+算术平均滤波，连续采样N个数据，去掉一个最大值和一个最小值，然后计算N-2个数据的算术平均值。
//N值的选取：3-14
//优点：融合了两种滤波法的优点
//对于偶然出现的脉冲性干扰，可消除由于脉冲干扰所引起的采样值偏差。
//缺点：
//测量速度较慢，和算法平均滤波一样，浪费RAM。

float filter(float *ary, u8 num, float MaxValue, float MinValue)
{
	u8 angleDataloopTemp2; //取平均的个数
	float finalData = 0;
	float maxValue = MinValue;
	float minValue = MaxValue;
	for (angleDataloopTemp2 = 0; angleDataloopTemp2 < num; angleDataloopTemp2++) //找出最大值和最小值
	{
		if (ary[angleDataloopTemp2] > maxValue) //去掉最大值最小值
		{
			maxValue = ary[angleDataloopTemp2];
		}
		if (ary[angleDataloopTemp2] < minValue) //去掉最大值最小值
		{
			minValue = ary[angleDataloopTemp2];
		}
		finalData += ary[angleDataloopTemp2];
	}
	finalData -= (maxValue + minValue);  //去掉最大值最小值
	finalData /= (num - 2);	 //取平均值
	return finalData;
}
//卡尔曼滤波算法
double KalmanFilter(const double ResrcData, double ProcessNiose_Q, double MeasureNoise_R, double InitialPrediction)
{
	double R = MeasureNoise_R;
	double Q = ProcessNiose_Q;

	static        double x_last;

	double x_mid = x_last;
	double x_now;

	static        double p_last;

	double p_mid;
	double p_now;
	double kg;

	x_mid = x_last; //x_last=x(k-1|k-1),x_mid=x(k|k-1)
	p_mid = p_last + Q; //p_mid=p(k|k-1),p_last=p(k-1|k-1),Q=噪声
	kg = p_mid / (p_mid + R); //kg为kalman filter，R为噪声
	x_now = x_mid + kg*(ResrcData - x_mid);//估计出的最优值

	p_now = (1 - kg)*p_mid;//最优值对应的covariance       

	p_last = p_now; //更新covariance值
	x_last = x_now; //更新系统状态值

	return x_now;
}
//1.限幅滤波算法（程序判断滤波算法）
//方法解析：
//根据经验判断，确定两次采样允许的最大偏差值（设定为A），每次检测到新值时判断：
//如果本次值与上次值之差 <= A，则本次值有效，
//如果本次值与上次值只差 > A, 则本次值无效，放弃本次值，用上次值代替本次值。
//优点：
//能有效克服因偶然因素引起的脉冲干扰
//缺点：
//无法抑制那种周期性的干扰，平滑度差
//************************************
// Method:    limitingFilter
// FullName:  limitingFilter
// Access:    public 
// Returns:   float
// Qualifier: 
// Parameter: float value:需要滤波的数据
// Parameter: float A：可接受的最大数据差
//************************************
float limitingFilter(float value, float A)
{
	static float   lastValue =0;
	if (fabs(value - lastValue) > A)//本次值无效
	{
		return lastValue;
	}
	else//本次值有效
	{

		lastValue = value;
		return value;

	}
}
//滑动平均滤波
//方法解析：
//把连续取N个采样值看成一个队列，队列的长度固定为N，每次采样到一个新数据放入队尾，并扔掉原来队首的一次数据（先进先出）。
//把队列中的N个数据进行算术平均运算，就可获得新的滤波结果。N值的选取：一般12.
//优点：
//对周期性干扰有良好的抑制作用，平滑度高，适应于高频振荡的系统
//缺点：
//灵敏度低，对偶然出现的脉冲性干扰的抑制作用较差。不易消除由于脉冲干扰所引起打的采样值偏差，不适用于脉冲干扰比较严重的场合
//浪费RAM
//************************************
// Method:    movingAverageFilter
// FullName:  movingAverageFilter
// Access:    public 
// Returns:   float
// Qualifier: 此滤波器自动记录上一次的结果
// Parameter: float value：需要滤波的数值
//************************************
float movingAverageFilter(float value)
{
#define FILTER_N 100
	static float filter_buf[FILTER_N + 1];
	u8 i;
	float filter_sum = 0;
	filter_buf[FILTER_N] = value;
	for (i = 0; i < FILTER_N; i++) {
		filter_buf[i] = filter_buf[i + 1]; // 所有数据左移，低位仍掉
		filter_sum += filter_buf[i];
	}
	return (float)(filter_sum / FILTER_N);
}


/*
A、名称：消抖滤波法
B、方法：
设置一个滤波计数器，将每次采样值与当前有效值比较：
如果采样值=当前有效值，则计数器清零；
如果采样值<>当前有效值，则计数器+1，并判断计数器是否>=上限N（溢出）；
如果计数器溢出，则将本次值替换当前有效值，并清计数器。
C、优点：
对于变化缓慢的被测参数有较好的滤波效果；
可避免在临界值附近控制器的反复开/关跳动或显示器上数值抖动。
D、缺点：
对于快速变化的参数不宜；
如果在计数器溢出的那一次采样到的值恰好是干扰值,则会将干扰值当作有效值导入系统。
 */
 //************************************
 // Method:    shudderingFilter
 // FullName:  shudderingFilter
 // Access:    public 
 // Returns:   float
 // Qualifier:
 // Parameter: float value：传进来的数值，如果不是float请强制转换成float
 // Parameter: u8 filter_n：计数器的上限值，值越大滤波的结果越稳定，越小越不稳定，但是值太大数据会失真
 //************************************
float shudderingFilter(float value, u8 filter_n)
{

	static u16 i = 0;//计数器
	static float lastValue;//上一次的结果
	int newValue;//这一次的新的结果;
	newValue = value;//传值
	if (!(fabs(newValue - lastValue) < 0.0001f))//如果上一次的结果不等于这一次的结果
	{
		i++;
		if (i > filter_n) {
			i = 0;
			lastValue = newValue;
		}
	}
	else//如果上一次的结果等于这一次的结果
	{
		i = 0;
	}
	return lastValue;

}
