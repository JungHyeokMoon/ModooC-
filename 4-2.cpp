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
    // Date()=default; //����Ʈ �����ڸ� �����϶�� �����Ϸ����� �˷��ִ� �� c11++�������� �߰���

    //�⺻������
    Date(){
        year=2020;
        month=12;
        day=2;
    }
    //������ �����ε�
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

        //���ص� �������� ���
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
        return 29; //����
    else
        return 28;
}
void Date::ShowDate()
{
    std::cout << "������ " << year << "�� " << month << " �� " << day << " �� �Դϴ�." << std::endl;
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

    day.SetDate(2012, 1, 31); // ����
    day.AddDay(29);
    day.ShowDate();

    day.SetDate(2012, 8, 4);
    day.AddDay(2500);
    day.ShowDate();
    return 0;
}