#include "StdAfx.h"
#include "PBDate.h"

//节气相关
const double PBDate::x_1900_1_6_2_5 = 693966.08680556;
const int PBDate::termInfo[] = {  
		0      ,21208 ,42467 ,63836 ,85337 ,107014,  
		128867,150921,173149,195551,218072,240693,  
		263343,285989,308563,331033,353350,375494,  
		397447,419210,440795,462224,483532,504758  
	}; 
const TCHAR* PBDate::solar_term_name[] = {  
		_T("小寒"),_T("大寒"),_T("立春"),_T("雨水"),  
		_T("惊蛰"),_T("春分"),_T("清明"),_T("谷雨"),  
		_T("立夏"),_T("小满"),_T("芒种"),_T("夏至"),  
		_T("小暑"),_T("大暑"),_T("立秋"),_T("处暑"),  
		_T("白露"),_T("秋分"),_T("寒露"),_T("霜降"),  
		_T("立冬"),_T("小雪"),_T("大雪"),_T("冬至")  
	}; 

DWORD PBDate::lunarInfo[]={
 0x04bd8,0x04ae0,0x0a570,0x054d5,0x0d260,0x0d950,0x16554,0x056a0,0x09ad0,0x055d2,
 0x04ae0,0x0a5b6,0x0a4d0,0x0d250,0x1d255,0x0b540,0x0d6a0,0x0ada2,0x095b0,0x14977,
 0x04970,0x0a4b0,0x0b4b5,0x06a50,0x06d40,0x1ab54,0x02b60,0x09570,0x052f2,0x04970,
 0x06566,0x0d4a0,0x0ea50,0x06e95,0x05ad0,0x02b60,0x186e3,0x092e0,0x1c8d7,0x0c950,
 0x0d4a0,0x1d8a6,0x0b550,0x056a0,0x1a5b4,0x025d0,0x092d0,0x0d2b2,0x0a950,0x0b557,
 0x06ca0,0x0b550,0x15355,0x04da0,0x0a5d0,0x14573,0x052d0,0x0a9a8,0x0e950,0x06aa0,
 0x0aea6,0x0ab50,0x04b60,0x0aae4,0x0a570,0x05260,0x0f263,0x0d950,0x05b57,0x056a0,
 0x096d0,0x04dd5,0x04ad0,0x0a4d0,0x0d4d4,0x0d250,0x0d558,0x0b540,0x0b5a0,0x195a6,
 0x095b0,0x049b0,0x0a974,0x0a4b0,0x0b27a,0x06a50,0x06d40,0x0af46,0x0ab60,0x09570,
 0x04af5,0x04970,0x064b0,0x074a3,0x0ea50,0x06b58,0x055c0,0x0ab60,0x096d5,0x092e0,
 0x0c960,0x0d954,0x0d4a0,0x0da50,0x07552,0x056a0,0x0abb7,0x025d0,0x092d0,0x0cab5,
 0x0a950,0x0b4a0,0x0baa4,0x0ad50,0x055d9,0x04ba0,0x0a5b0,0x15176,0x052b0,0x0a930,
 0x07954,0x06aa0,0x0ad50,0x05b52,0x04b60,0x0a6e6,0x0a4e0,0x0d260,0x0ea65,0x0d530,
 0x05aa0,0x076a3,0x096d0,0x04bd7,0x04ad0,0x0a4d0,0x1d0b6,0x0d250,0x0d520,0x0dd45,
 0x0b5a0,0x056d0,0x055b2,0x049b0,0x0a577,0x0a4b0,0x0aa50,0x1b255,0x06d20,0x0ada0
};
UINT PBDate::solarmonth[]={31,28,31,30,31,30,31,31,30,31,30,31};

PBDate::PBDate(void)
	:year(1900),month(1),day(1)
{
}
PBDate::PBDate(int y,int m,int d)
	:year(y),month(m),day(d)//对日期赋值，判断有效的日期。
{
	if((y<=0)||(m<=0 || m>12)||(d<=0 || d>DayOfMonth(y,m)))
	{
		year = 1900;
		month = 1;
		day = 1;
	}
}
int PBDate::GetYear() const
{
	return year;
}
int PBDate::GetMonth()const
{
	return month;
}
int PBDate::GetDay() const
{
	return day;
}
int PBDate::DayOfWeek()
{
	/*
	算法如下： 
	基姆拉尔森计算公式
	W= (d+2*m+3*(m+1)/5+y+y/4-y/100+y/400) mod 7
	在公式中d表示日期中的日数，m表示月份数，y表示年数。
	注意：在公式中有个与其他公式不同的地方：
	把一月和二月看成是上一年的十三月和十四月，例：如果是2004-1-10则换算成：2003-13-10来代入公式计算。
	*/
	int y =year;
	int m = month;
	int d = day;
	if(m==1||m==2) {
	m+=12;
	y--;
	}
	return (d+2*m+3*(m+1)/5+y+y/4-y/100+y/400+1)%7; 

	/*
	char *cWeekName[]  = {"星期日","星期一","星期二","星期三","星期四","星期五","星期六"};

 if(date.month==1||date.month==2)
 {
  date.month+=12;
  date.year--;
 }
 return cWeekName[(date.day+1+2*date.month+3*(date.month+1)/5+date.year+date.year/4-date.year/100+date.year/400)%7];
	*/
}
int PBDate::DayOfMonth(int y,int m)const
{
	int d = 0; 
	switch(m) 
	{ 
	case 1: 
	case 3: 
	case 5: 
	case 7: 
	case 8: 
	case 10: 
	case 12: 
		d = 31; 
	break; 
	case 4: 
	case 6: 
	case 9: 
	case 11: 
		d = 30; 
	break; 
	case 2: 
		d = 28 + (IsLeapyear(y)== true ? 1:0); 
	break; 
	} 
	return d; 
}
bool PBDate::IsLeapyear() const
{
	return year%400?(year%100?(year%4?(false):(true)):(false)):true;
}
bool PBDate::IsLeapyear(int y) const
{
	return y%400?(y%100?(y%4?(false):(true)):(false)):true;
}
//std::string PBDate::ToString(const std::string formaterStr)
//{
//}
LONG PBDate::CLCDaysFrom1900(int y,int m,int d)
{

	LONG days;
	days=365*y+(y-1)/4-(y-1)/100+(y-1)/400-
			(365*1900+(1900-1)/4-(1900-1)/100+(1900-1)/400);

	for(int i=0;i<m-1;i++)
	{
		days+=solarmonth[i];
	}

	days+=d;

	if((y%4==0&&y%100!=0)||y%400==0)
	{
		if(m>2)
		{
			days++;
		}
	}
return days;
}
UINT PBDate::CLCYearDays(UINT y)
{
   UINT i, sum = 348;
   for(i=0x8000; i>0x8; i>>=1)
   {
		sum += (lunarInfo[y-1900] & i)? 1: 0;
   }
   return(sum+CLCLeapDays(y));
}
UINT PBDate::CLCLeapDays(UINT y)
{
   if(CLCLeapMonth(y))
   {
    return (lunarInfo[y-1900] & 0x10000)? 30: 29;
   }
   else
   {
    return 0;
   }
}
UINT PBDate::CLCLeapMonth(UINT y)
{
	if(y<1900)return 0;
	return lunarInfo[y-1900] & 0xf;
}
UINT PBDate::CLCMonthDays(UINT y,UINT m)
{
	if(y<1900)return 0;
	return (lunarInfo[y-1900] & (0x10000>>m))? 30: 29;
}
bool PBDate::CLCLunar(const int y,const int m,const int d,PBDate& retdate)
{
	LONG offset;
	int i, leap=0, temp=0;

	offset=CLCDaysFrom1900(y,m,d)-30;
	for(i=1900; i<2050 && offset>0; i++)
	{
		temp = CLCYearDays(i);
		offset -= temp;
	}

	if(offset<0)
	{
		offset += temp;
		i--;
	}
	retdate.year = i;
	
	leap = CLCLeapMonth(i);
	bool isLeap = false;
	for(i=1; i<13 && offset>0; i++)
	{
		if(leap>0 && i==(leap+1) && isLeap==false)
		{
			--i;
			isLeap = true;
			temp = CLCLeapDays(retdate.year);
		}
		else
		{
			temp = CLCMonthDays(retdate.year, i);
		}
		if(isLeap==true && i==(leap+1))
		{
			isLeap = false;
		}
		offset -= temp;
	}
	if(offset==0 && leap>0 && i==leap+1)
	{
		if(isLeap)
		{
			isLeap = false;
		}
		else
		{
			isLeap = true;
			--i;
		}
	}
	if(offset<=0)
	{
		offset += temp;
		--i;
	}
	retdate.month = i;
	retdate.day = offset ;
	retdate.isRunYue=isLeap;
	return isLeap;
}
void PBDate::CLCGetLunarString (const int y,const int m,const int d,bool runYue,TCHAR nongLiStr[])
{
	TCHAR szNongli[30], szNongliDay[10],szShuXiang[10];
	const TCHAR *cTianGan[]  = {_T("甲"),_T("乙"),_T("丙"),_T("丁"),_T("戊"),
								_T("己"),_T("庚"),_T("辛"),_T("壬"),_T("癸")}; /*天干名称*/
	const TCHAR *cDiZhi[]    = {_T("子"),_T("丑"),_T("寅"),_T("卯"),_T("辰"),_T("巳"),
								_T("午"),_T("未"),_T("申"),_T("酉"),_T("戌"),_T("亥")}; /*地支名称*/
	const TCHAR *cShuXiang[] = {_T("鼠"),_T("牛"),_T("虎"),_T("兔"),_T("龙"),_T("蛇"),
								_T("马"),_T("羊"),_T("猴"),_T("鸡"),_T("狗"),_T("猪")}; /*属相名称*/
	const TCHAR *cDayName[]  = { _T("*"),_T("初一"),_T("初二"),_T("初三"),_T("初四"),_T("初五"), /*农历日期名*/
        _T("初六"),_T("初七"),_T("初八"),_T("初九"),_T("初十"),
        _T("十一"),_T("十二"),_T("十三"),_T("十四"),_T("十五"),
        _T("十六"),_T("十七"),_T("十八"),_T("十九"),_T("二十"),
        _T("廿一"),_T("廿二"),_T("廿三"),_T("廿四"),_T("廿五"),
        _T("廿六"),_T("廿七"),_T("廿八"),_T("廿九"),_T("三十")};
	const TCHAR *cMonName[]  = {_T("*"),_T("正"),_T("二"),_T("三"),_T("四"),_T("五"),_T("六"),
								_T("七"),_T("八"),_T("九"),_T("十"),_T("十一"),_T("腊")};

 /*--生成农历天干、地支、属相 ==> wNongli--*/

	int nShuXiang = ((y - 4) % 60) % 12;
	if ( nShuXiang < 0 || nShuXiang >= sizeof(cShuXiang)/sizeof(cShuXiang[0]) )
	{
		return  ;
	}
	wsprintf(szShuXiang,_T("%s"),cShuXiang[nShuXiang]);

	int nTianGan = ((y - 4) % 60) % 10;
	if ( nTianGan < 0 || nTianGan >= sizeof(cTianGan)/sizeof(cTianGan[0]) )
	{
		return ;
	}
	int nDiZhi = ((y - 4) % 60) % 12;
	if ( nDiZhi < 0 || nDiZhi >= sizeof(cDiZhi)/sizeof(cDiZhi[0]) )
	{
		return ;
	}
	wsprintf(szNongli,_T("%s(%s%s)年"),szShuXiang,cTianGan[nTianGan],cDiZhi[nDiZhi]);

	/*--生成农历月、日 ==> wNongliDay--*/
	if ( m < 0 || m >= sizeof(cMonName)/sizeof(cMonName[0]) )
	{
		return ;
	}
	if (runYue)
	{
		wsprintf(szNongliDay,_T("闰%s"),cMonName[m]);
	}
	else
	{
		_tcscpy_s (szNongliDay,cMonName[m]);
	}
	_tcscat_s(szNongliDay,_T("月"));
	if ( d < 0 || d >= sizeof(cDayName)/sizeof(cDayName[0]) )
	{
		return ;
	}
	_tcscat_s(szNongliDay,cDayName[d]);
	_tcscat_s(szNongli,szNongliDay);
	//wsprintf(m_slunar,szNongli);
	_tcscpy(nongLiStr,szNongli);
	//return m_slunar;
}

UINT PBDate::CLCSolarDays(UINT y,UINT m)

{

 if(m==1)//2月
 {
  return(((y%4 == 0) && (y%100 != 0) || (y%400 == 0))? 29: 28);
 }
 else
 {
  return(solarmonth[m]);
 }
}

double PBDate::get_solar_term( int y , int n )
{ 
	n = n- 1;//由于素组是从0开始，1对于数组就是1-1=0
	return x_1900_1_6_2_5+365.2422*(y-1900)+termInfo[n]/(60.*24);  
}
void PBDate::parse_jq_date( unsigned _days , int& y,int& m,int& d )
{
	static const int mdays[] = {0, 31, 59, 90, 120, 151, 181, 212, 243, 273, 304, 334, 365};
    int diff;
    unsigned days;    
    days = 100 * (_days - _days/(3652425L/(3652425L-3652400L)) );
    y    = days / 36524; days %= 36524;
    m    = 1 + days/3044;        /* [1..12] */
    d    = 1 + (days%3044)/100;    /* [1..31] */
    diff =y*365+y/4-y/100+y/400+mdays[m-1]+d-((m<=2&&((y&3)==0)&&((y%100)!=0||y%400==0))) - _days;
    if( diff > 0 && diff >= d )    /* ~0.5% */
    {
        if( m == 1 )
        {
            --y; m = 12;
            d = 31 - ( diff - d );
        }
        else 
        {            
            d = mdays[m-1] - ( diff - d );
            if( --m == 2 )
                d += ((y&3)==0) && ((y%100)!=0||y%400==0);
        }
    }
    else
    {
        if( (d -= diff) > mdays[m] )    /* ~1.6% */
        {
            if( m == 2 )
            {
                if(((y&3)==0) && ((y%100)!=0||y%400==0))
                {
                    if( d != 29 )
                        m = 3 , d -= 29;
                }
                else
                {
                    m = 3 , d -= 28;
                }
            }
            else
            {
                d -= mdays[m];
                if( m++ == 12 )
                    ++y , m = 1;
            }
        }
    }    
}
void PBDate::JQ_Parse_Date(int _y , int n,int& y,int& m,int& d)
{
	unsigned int _days = (unsigned)get_solar_term( _y , n );
	parse_jq_date(_days, y, m, d );  
}
PBDate::~PBDate(void)
{
}
