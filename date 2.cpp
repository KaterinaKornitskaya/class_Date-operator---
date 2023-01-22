// date 2.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//

#include <iostream>

/* Создайте класс Date, который содержит информацию о дате (день, месяц, год).
 С помощью перегрузки операторов определите операцию разности двух дат
 (результат - это количество дней между датами), а также операцию увеличения 
 даты на определенное количество дней.
*/

class Date
{
    int day;    
    int month;  
    int year;   
public:
    Date() : day{ 0 }, month{ 0 }, year{ 0 } {}

    Date(int dayP, int monthP, int yearP)
        : day{ dayP }, month{ monthP }, year{ yearP } {}

    // метод для вычисления кол-ва дней в полных годах
    int days_in_years(Date x)  
    {
        // накопительная переменная "дней в полных годах"  
        int days_in_years = 0;      
        // цикл от 1го полного года до последнего полного года
        for (int i = x.year + 1; i < year; ++i)  
        {
            if (i % 4 == 0 && i % 100 != 0 || i % 400 == 0) 
            {                          // если год високосный
                days_in_years += 366;  // += 366 дней
            }                          //
            else {                     // либо
                days_in_years += 365;  // += 365 дней
            }
        }
        return days_in_years;
    }

    // метод для вычисления кол-ва дней в полных месяцах начальной даты
    int days_in_months_start(Date x)
    {
        // накопительная переменная "дней в полных месяцах начальной даты" 
        int days_in_months_start = 0;  
        // массив - 12 месяцев с соответствующим кол-вом дней
        int arr[12] { 31,28,31,30,31,30,31,31,30,31,30,31 };  
        for (int i = x.month; i <= 11; ++i)  // цикл по массивы месяцев
        {                                     
            days_in_months_start += arr[i];  // += дни в месяцах
        }
        if (x.year % 4 == 0 && x.year % 100 != 0  // если год високосный и 
            && x.month < 2 || x.year % 400 == 0)  // месяц 01 или 02
        {                                                   
            days_in_months_start += 1;            // + 29-ый день февраля
        }                                               
        return days_in_months_start;
    }

    // метод для вычисления кол-ва дней в полных месяцах конечной даты
    int days_in_months_end()
    {
        // накопительная переменная "дней в полных месяцах конечной даты"
        int days_in_months_end = 0;
        // массив - 12 месяцев с соответствующим кол-вом дней
        int arr[12] { 31,28,31,30,31,30,31,31,30,31,30,31 };
        for (int i = 0; i < month - 1; ++i)   // цикл по массивы месяцев
        {
            days_in_months_end += arr[i];     // += дни в месяцах
        }
        if (year % 4 == 0 && year % 100 != 0  // если год високосный и
            && month > 1 || year % 400 == 0)  // месяц 01 или 02
        {         
            days_in_months_end += 1;          // + 29-ый день февраля
        }      
        return days_in_months_end;
    }

    // метод для вычисления кол-ва дней в первом неполном месяце
    int days_in_days_start(Date x)
    {
        // накопительная переменная "дней в первом неполном месяце"
        int days_in_days_start = 0;
        // массив - 12 месяцев с соответствующим кол-вом дней
        int arr[12] = { 31,28,31,30,31,30,31,31,30,31,30,31 };
        // тернарный оператор
        // если год високосный и начальный месяц = 02 (февраль)
        (x.year % 4 == 0 && x.year % 100 != 0
            && x.month == 2 || x.year % 400 == 0)
            // возврат (всего дней в месяце - уже прошедших дней + 1 день февраля)
            ? days_in_days_start = arr[x.month - 1] - x.day + 1
            // или возврат (всего дней в месяце - уже прошедших дней) 
            : days_in_days_start = arr[x.month - 1] - x.day;
      
        return days_in_days_start;
    }

    // метод для вычисления кол-ва дней в первом неполном месяце
    int days_in_days_end()
    {
        // накопительная переменная "дней в последнем неполном месяце"
        int days_in_days_end = 0;
        days_in_days_end = day;
        return days_in_days_end;
    }

    // перегрузка оператора -
    int operator-(Date& x)
    {
        // разница между датами = сумма результатов всех предыдущих методов
        int res = days_in_years(x) + days_in_months_start(x)
            + days_in_months_end() + days_in_days_start(x) + 
            days_in_days_end();
        return res;
    }

    // метод для вывода кол-ва дней в месяце
    int maxday()
    {
        int days[12] = { 31,28,31,30,31,30,31,31,30,31,30,31 };
        // если год високосный и месяц - февраль
        if (year % 4 == 0 && year % 100 != 0
            && month > 1 || year % 400 == 0) 
        {
            days[1] = 29;  // выводим 29
        }
        // в остальных случаях - выводим соответствующее месяцу кол-ву дней
        return days[month - 1];  
    }

    // перегрузка оепратора += (добавление дней к дате)
    Date& operator+=(int Day)
    {
        if (day + Day > maxday())
        {
            Day -= maxday() - day;
            if (++month > 12)
            {
                month = 1;
                year++;
            }
            while (Day / maxday())
            {
                if (++month > 12)
                {
                    month = 1;
                    year++;
                }
                Day -= maxday();
            }
            day = Day;         
        }
        else
        {
            day += Day;
        }
        return *this;
    }
    // дружественная ф-ия - перегрузка оператора вывода <<
    friend std::ostream& operator<<(std::ostream&, const Date&);  
};

std::ostream& operator<<(std::ostream& outStream, const Date& date)
{
    outStream << date.day << " " << date.month << " " << date.year;
    return outStream;
}

int main()
{
    int d1, m1, y1, d2, m2, y2, d3, m3, y3;  // для ввода пользователем
   
    std::cout << "Difference between dates: \n";
    std::cout << "Enter 1st date (smaller): ";
    std::cin >> d1 >> m1 >> y1;
    std::cout << "Enter 2nd date (larger): ";
    std::cin >> d2 >> m2 >> y2;

    Date  obj1(d1, m1, y1);
    Date obj2(d2, m2, y2);
    int res = obj2 - obj1;

    std::cout << "Difference between dates is " << res << " days.\n";
    std::cout << "Increase the date by n-days: \n";
    std::cout << "Enter date: ";
    std::cin >> d3 >> m3 >> y3;
    std::cout << "Enter number of days: ";
    int increment;
    std::cin >> increment;

    Date obj3(d3,m3,y3);    
    obj3 += increment;
    std::cout << "\nDate new = " << obj3;

    return 0;
}
