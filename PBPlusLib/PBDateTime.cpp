#include "StdAfx.h"
#include "PBDateTime.h"

PBDateTime::PBDateTime(const time_t seconds)
{
    this->seconds = seconds;
    this->date = *localtime(&this->seconds);
}
PBDateTime::PBDateTime(int year,int month,int day)
{
    tm t;
    t.tm_year = year-1900;
    t.tm_mon = month-1;
    t.tm_mday = day;
    t.tm_hour = 0;
    t.tm_min = 0;
    t.tm_sec = 0;
    this->seconds = mktime(&t);
    this->date = *localtime(&this->seconds);

}
PBDateTime::PBDateTime(int year,int month,int day,int hour,int minute,int second)
{
    tm t;
    t.tm_year = year-1900;
    t.tm_mon = month-1;
    t.tm_mday = day;
    t.tm_hour = hour;
    t.tm_min = minute;
    t.tm_sec = second;
    this->seconds = mktime(&t);
    this->date = *localtime(&this->seconds);

}

PBDateTime::PBDateTime(std::string datetimeStr) //日期字符串格式 月/日/年 时:分:秒 例:02/03/2008 9:30:20 出错返回 01/01/1970 00:00:00
{
    this->InitByStr(datetimeStr,"%d/%d/%d %d:%d:%d");
}
PBDateTime::PBDateTime(std::string datetimeStr,std::string formaterStr)
{
    this->InitByStr(datetimeStr,formaterStr);
}
PBDateTime PBDateTime::Parse(std::string datetimeStr)
{

    PBDateTime datetime(datetimeStr);
    return datetime;
}
PBDateTime PBDateTime::Parse(const std::string datetimeStr,const std::string formaterStr)
{
    PBDateTime datetime(datetimeStr,formaterStr);
    return datetime;
}


void PBDateTime::InitByStr(std::string dateTimeStr,std::string formaterStr)
{
    int year,month,day,hour,minutes,seconds;
    sscanf(dateTimeStr.c_str(),formaterStr.c_str(),&year,&month,&day,&hour,&minutes,&seconds);    
    if(year <1900) year = 1970;
    if(month <0) month = 1;
    if(day <0) day = 1;
    if(hour <0) hour = 0;
    if(minutes <0) minutes = 0;
    if(seconds <0) seconds = 0;
    tm t;
    t.tm_year = year-1900;
    t.tm_mon = month-1;
    t.tm_mday = day;
    t.tm_hour = hour;
    t.tm_min = minutes;
    t.tm_sec = seconds;
    this->seconds = mktime(&t);
    this->date = *localtime(&this->seconds);
}
int PBDateTime::DayOfWeek()
{
    return this->date.tm_wday;
}
int PBDateTime::DayOfYear()
{
    return this->date.tm_yday;
}
int PBDateTime::DaysInMonth(const int year,const int months)
{
    return 0;
}

//bool DateTime::Equals(const Object *object)
//{
//    DateTime *dateTime = (DateTime *)object;
//    if(this->seconds == dateTime->seconds)
//        return true;
//    return false;
//}

bool PBDateTime::Equals(const PBDateTime *dateTime)
{
	if(this->seconds == dateTime->seconds)
		return true;
	else
		return false;
}

bool PBDateTime::Equals(const PBDateTime *value1,const PBDateTime *value2)
{
    if(value1->seconds == value2->seconds)
        return true;
    return false;
}
int PBDateTime::GetDay()
{    
    return this->date.tm_mday;;
}

int PBDateTime::GetHour()
{
    return this->date.tm_hour;
}
int PBDateTime::GetMinute()
{
    return this->date.tm_min;
}
int PBDateTime::GetMonth()
{
    return this->date.tm_mon;
}

PBDateTime PBDateTime::GetNow()
{
    PBDateTime datetime(time(0));
    return datetime;
}

int PBDateTime::GetSecond()
{
    return this->date.tm_sec;
}

int PBDateTime::GetYear()
{
    return this->date.tm_year+1900;
}

void PBDateTime::AddYears(const int years)
{
    this->date.tm_year = this->date.tm_year+years;
    this->seconds = mktime(&this->date);
}
void PBDateTime::AddMonths(const time_t months)
{
    int a  =(int)((this->date.tm_mon+months)/12);
            
    this->date.tm_year = this->date.tm_year+a;
    this->date.tm_mon = this->date.tm_mon+(int)((this->date.tm_mon+months)%12)-1;
    this->seconds = mktime(&this->date);
}

void PBDateTime::AddDays(const time_t days)
{    
    this->AddHours(days*24);
}
void PBDateTime::AddHours(const time_t hours)
{
    this->AddMinutes(hours*60);
}
void PBDateTime::AddMinutes(const time_t minutes)
{
    this->AddSeconds(minutes *60);
}

void PBDateTime::AddSeconds(const time_t seconds)
{
    this->seconds = this->seconds+seconds;
    this->date = *localtime(&this->seconds);
}
void PBDateTime::AddWeeks(const time_t weeks)
{
    this->AddDays(weeks*7);
}


int PBDateTime::Compare(const PBDateTime *t1,const PBDateTime *t2)
{
    if( t1->seconds == t2->seconds)
        return 0;
    if(t1->seconds < t2->seconds)
        return -1;
    return 1;

}


//int PBDateTime::CompareTo(const Object *value)
//{
//    DateTime * dateTime =  (DateTime *)value;
//    if( dateTime->seconds == this->seconds)
//        return 0;
//    if(this->seconds < dateTime->seconds)
//        return -1;
//    return 1;
//}

int PBDateTime::CompareTo(const PBDateTime *value)
{
    if(this->seconds == value->seconds)
        return 0;
    if(this->seconds <value->seconds)
        return -1;
    return 1;
}


std::string PBDateTime::ToShortDateString()
{
    return this->ToString("%Y-%m-%d");
}

std::string PBDateTime::ToString()
{
    return this->ToString("%Y-%m-%d %H:%M:%S");
}
std::string PBDateTime::ToString(const std::string formaterStr)
{
    //strftime(s, sizeof(s), "%Y-%m-%d %H:%M:%S", localtime(&t)); 
    char s[256];
    strftime(s, sizeof(s), formaterStr.c_str(), &this->date);
    std::string str(s);
    return str;

}

bool PBDateTime::operator ==( PBDateTime &dateTime)
{
    return this->Equals(&dateTime);

}
bool PBDateTime::operator != (PBDateTime &datetime)
{
    if(this->seconds != datetime.seconds)
        return true;
    return false;
}
bool PBDateTime::operator > (PBDateTime &dateTime)
{
    if(this->seconds > dateTime.seconds)
        return true;
    return false;
}
bool PBDateTime::operator < (PBDateTime &datetime)
{
    if(this->seconds <datetime.seconds)
        return true;
    return false;
}
bool PBDateTime::operator >=(PBDateTime &datetime)
{
    if(this->seconds >= datetime.seconds)
        return true;
    return false;
}

bool PBDateTime::operator <=(PBDateTime &datetime)
{
    if(this->seconds <= datetime.seconds)
        return true;
    return false;
}

PBDateTime::~PBDateTime(void)
{

}
