/*
* PBDate.h
*
*  Created on: 2015.05.23
*      Author: wxj
*		EMAIL: wxj_wz@qq.com
*/
#pragma once
//万年历http://c.chinaitlab.com/cc/example/200903/779989.html
//Chinese lunisolar calendar 简写CLC
//信息来源：中华农历网：http://www.nongli.com/doc/0701/0614330.htm

//c++ date http://www.douban.com/note/174074422/
class PBDate
{
public:
	PBDate(void); //构造函数，初始化默认的日期
	PBDate(int y,int m,int d);
	~PBDate(void);
public:
	int GetYear() const;//获取此实例所表示日期的年份部分。
	int GetMonth()const;//获取此实例所表示日期的年份部分。
	int GetDay() const;// 获取此实例所表示的日期为该月中的第几天。
	int DayOfWeek(); //获取此实例所表示的日期是星期几。0表示星期天，依次类推
	bool IsLeapyear() const; //判断是否为闰年。
	bool IsLeapyear(int y) const; //判断是否为闰年。
	//std::string ToString(const std::string formaterStr);//转换为字符串

	//以下为农历信息
	static LONG CLCDaysFrom1900(int year,int month,int day);//date与1900年相差的天数
	static UINT CLCYearDays(UINT y);//农历y年的总天数
	static UINT CLCLeapDays(UINT y);//传回农历 y年闰月的天数
	static UINT CLCLeapMonth(UINT y);// 传回农历 y年闰哪个月 1-12 , 没闰传回 0
	static UINT CLCMonthDays(UINT y,UINT m);//传回农历 y年m月的总天数
	static bool CLCLunar(const int y,const int m,const int d,PBDate& date);//输入阳历日期，返回阴历日期
	//char* dayOfWeek(const int y,const int m,const int d);//输入阳历日期，返回星期几
	static void CLCGetLunarString (const int y,const int m,const int d,bool runYue,TCHAR nongLiStr[]);// 输入阴历日期,得到表示农历的字串
	static UINT CLCSolarDays(UINT y,UINT m);//传回国历 y年某m+1月的天数
private:
	int year,month,day;//
	bool isRunYue;
private:
	int DayOfMonth(int y,int m)const;//返回一个月的天数。
	int ToInt()const;//
	static DWORD   lunarInfo[];//万年历信息
	static UINT    solarmonth[];


	//节气,http://blog.csdn.net/fengrx/article/details/4331043
	static const double x_1900_1_6_2_5;
	static const int termInfo[];
	static const TCHAR* solar_term_name[];
	static double get_solar_term( int y , int n );//计算y年第n个节气
	static void parse_jq_date( unsigned _days , int& y,int& m,int& d );
public:
	static void JQ_Parse_Date(int _y , int n,int& y,int& m,int& d);//计算y年第n个节气返回的时间
};

