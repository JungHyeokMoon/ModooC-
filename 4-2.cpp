#include <iostream>
class Date
{
private:
    int year;
    int month;
    int day;

public:
    void SetDate(int _year, int _month, int _date);
    void AddDay(int inc);
    void AddMonth(int inc);
    void AddYear(int inc);

    int GetCurrentMonthTotalDays(int _year, int month);

    void ShowDate();
    // Date()=default; //디폴트 생성자를 정의하라고 컴파일러에게 알려주는 것 c11++에서부터 추가됨

    //기본생성자
    Date(){
        year=2020;
        month=12;
        day=2;
    }
    //생성자 오버로딩
    Date(int _year, int _month, int _date){
        year=_year;
        month=_month;
        day=_date;
    }
};

void Date::SetDate(int _year, int _month, int _date)
{
    year = _year;
    month = _month;
    day = _date;
}
void Date::AddDay(int inc)
{
    while (1)
    {
        int currentMonthTotalDays = GetCurrentMonthTotalDays(year, month);

        //더해도 같은달일 경우
        if (day + inc <= currentMonthTotalDays)
        {
            day += inc;
            return;
        }
        else
        {
            inc -= (currentMonthTotalDays - day + 1);
            day = 1;
            AddMonth(1);
        }
    }
}
void Date::AddMonth(int inc)
{
    AddYear((month + inc - 1) / 12);
    month = month + inc % 12;
    month = (month == 12 ? 12 : month % 12);
}
void Date::AddYear(int inc)
{
    year += inc;
}
int Date::GetCurrentMonthTotalDays(int year, int month)
{
    static int monthOfday[12] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
    if (month != 2)
        return monthOfday[month - 1];
    else if (year % 4 == 0 && year % 100 != 0)
        return 29; //윤년
    else
        return 28;
}
void Date::ShowDate()
{
    std::cout << "오늘은 " << year << "년 " << month << " 월 " << day << " 일 입니다." << std::endl;
}

int main()
{
    Date day;
    day.SetDate(2011, 3, 1);
    day.ShowDate();

    day.AddDay(30);
    day.ShowDate();

    day.AddDay(2000);
    day.ShowDate();

    day.SetDate(2012, 1, 31); // 윤년
    day.AddDay(29);
    day.ShowDate();

    day.SetDate(2012, 8, 4);
    day.AddDay(2500);
    day.ShowDate();
    return 0;
}