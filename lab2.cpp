//ивановская олеся 9 группа
// 8. Создать класс Time для работы со временем в формате «час:минута:секунда». Класс
//должен включать в себя не менее четырех способов инициализации : 
// числами,
// строкой(например, «23:59 : 59»), 
// секундами, 
// встроенным типом времени.
//Обязательными операциями являются : 
// вычисление разности между двумя моментами времени в секундах, 
// сложение времени и заданного количества секунд (также в виде перегрузки операторов + и - )
// вычитание из времени заданного количества секунд, 
// сравнение моментов времени, 
// перевод в секунды, 
// перевод в минуты(с округлением до целой минуты).
// 
// 
//Во всех упражнениях, помимо указанных методов, обязательно должны быть
//реализованы функции ввода данных с клавиатуры и из файла, функции вывода данных
//на экран и в файл, метод преобразования в строку to_string.Для класса необходимо
//выполнить перегрузку операторов(+, -, *, / , битовые операторы, операторы
//сравнения — <=> и == ), если это возможно. Реализовывая операции нельзя использовать приведение к другим, более
// вместительным типам.Например, нельзя просто засунуть два long - а в longlong,сложить, а 
// затем разделить обратно на лонги в задаче №17 на класс LongLong.
// Аналогично, нельзя загонять массивы в большие числа или в тип string.
// Задача должна демонстрировать работу всех методов, для этого пользователь
//  должен мочь ввести Объект_A и Объект_B.

import Time;
#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <ctime>
#include <compare>
#include <regex>
#include <Windows.h>

template<typename T>
T get_file();
bool condition(int x, int border);
void read_and_check(int& x, bool(*condition)(int, int), int border);
int menu(const char* message, bool(*condition)(int, int), int border);
int exit();
template<typename T> 
void print_time(T obj, std::ostream& ostr);
Time time_in_num(std::istream& istr);
Time time_in_str(std::istream& istr);
Time time_in_sec(std::istream& istr);
Time time_in_tm(std::istream& istr);
void time_in(int option, Time& time, std::istream& istr);

int main()
{
    SetConsoleOutputCP(1251);
    Time time, time2;
    int equal;
    std::string answer;
    short option{};
    do
    {
        option = menu("\nЗадачи:\n1. Вычисление разности между двумя моментами времени в секундах.\n"
            "2. Сложение времени и заданного количества секунд\n"
            "3. Вычитание из времени заданного количества секунд\n"
            "4. Сравнение 2 моментов времени\n5. Перевод в секунды\n6. Перевод в минуты\n"
            "7. Простой вывод времени\n8. Завершение работы", condition, 9);
        if (option != 8)
        {
            short option2 = menu("Как вводить?\n1. Ввод из файла\n2. Ввод с клавиатуры", condition, 3);
            short option3 = menu("Как выводить?\n1. Вывод в файл\n2. Вывод в консоль", condition, 3);
            short option4 = menu("Задание времени:\n1. Числами (ввод через пробел)\n2. Строкой\n"
                "3. Секундами\n4. Встроенным типом данных", condition, 5);

            switch (option2)
            {
            case 1:
            {
                std::ifstream file = get_file<std::ifstream>();
                time_in(option4, time, file);
                if (option == 1 || option == 4)
                {
                    short option5 = menu("\nЗадание нового времени:\n1. Числами (ввод через пробел)\n"
                        "2. Строкой\n3. Секундами\n4. Встроенным типом данных", condition, 5);
                    time_in(option5, time2, file);
                }
                break;
            }
            case 2:
            {
                time_in(option4, time, std::cin);
                if (option == 1 || option == 4)
                {
                    short option5 = menu("\nЗадание нового времени:\n1. Числами (ввод через пробел)\n"
                        "2. Строкой\n3. Секундами\n4. Встроенным типом данных", condition, 5);
                    time_in(option5, time2, std::cin);
                }
                break;
            }
            default:
                break;
            }      

            switch (option)
            {
            case 1: //Вычисление разности между двумя моментами времени в секундах
            {
                short choice = menu("\nКак вычислять?\n1. Методом\n2. Перегрузкой", condition, 3);
                if (choice == 1)
                    equal = time.seconds_between(time2);
                else
                    equal = time - time2;
                if(option3 == 2) std::cout << "Разница составляет: ";
                break;
            }
            case 2://Сложение времени и заданного количества секунд
            {
                int sec;
                std::cout << "Сколько секунд прибавить?\n-> ";
                std::cin >> sec;
                short choice = menu("\nКак вычислять?\n1. Методом\n2. Перегрузкой", condition, 3);
                if (choice == 1)
                    time = time.seconds_plus(sec);
                else
                    time = time + sec;
                break;
            }
            case 3://Вычитание из времени заданного количества секунд
            {
                int sec;
                std::cout << "Сколько секунд вычесть?\n-> ";
                std::cin >> sec;
                short choice = menu("\nКак вычислять?\n1. Методом\n2. Перегрузкой", condition, 3);
                if (choice == 1)
                    time = time.seconds_minus(sec);
                else
                    time = time - sec;
                break;
            }
            case 4://Сравнение 2 моментов времени
            {
                int t = time.compare(time2);
                if (t == 0)
                    answer = "Данные моменты времени равны";
                else
                    if (t == 1)
                        answer = "Первый момент произошёл позже, чем второй";
                    else
                        answer = "Первый момент произошёл раньше, чем второй";
                break;
            }
            case 5://Перевод в секунды
            {
                equal = time.to_seconds();
                break;
            }
            case 6://Перевод в минуты
            {
                equal = time.to_minutes();
                break;
            }
            case 8:
            {
                break;
            }
            default:
                break;
            }

            switch (option3)
            {
            case 1:
            {
                std::ofstream file = get_file<std::ofstream>();
                if (option == 1 || option == 5 || option == 6)
                    print_time(equal, file);
                else
                    if (option == 4)
                        print_time(answer, file);
                    else
                        print_time(time, file);
                break;
            }
            case 2:
            {
                if (option == 1 || option == 5 || option == 6)
                    print_time(equal, std::cout);
                else
                    if (option == 4)
                        print_time(answer, std::cout);
                    else
                        if (option == 3 && time.get_hours() < 0)
                        {
                            std::cout << "Время закончилось!\n";
                        }
                        else
                            print_time(time, std::cout);
                break;
            }
            default:
                break;
            }
        }
        option = exit();
    } while (option != 8);

	std::cin.get();
}

int exit()
{
	std::cout << "\nЗавершить работу? (Y/любая клавиша): ";
	char is_exit;
	short option_exit{};
	std::cin >> is_exit;
	if (is_exit == 'Y' || is_exit == 'y')
		option_exit = 8;
	return option_exit;
}

Time time_in_num(std::istream& istr)
{
    int h, m, s;
    if (&istr == &std::cin) std::cout << "Введите время (часы, минуты, секунды через пробел): ";
    istr >> h >> m >> s;
    while (istr.fail() || h < 0 || m < 0 || s < 0) {
        std::cout << "Некорректный ввод. Пожалуйста, введите целые числа.\n->";
        istr.clear();
        istr.ignore(std::cin.rdbuf()->in_avail());
        istr >> h >> m >> s;
    }
    Time time(h, m, s);
    return time;
}

Time time_in_str(std::istream& istr)
{
    std::string str;
    if (&istr == &std::cin)
    {
        std::cout << "Введите время (часы, минуты, секунды, разделённые двоеточием): ";
        istr.ignore(std::cin.rdbuf()->in_avail());
    }
    std::getline(istr, str);
    std::regex time_regex(R"(\s*(\d+)\s*:\s*(\d+)\s*:\s*(\d+)\s*)");
    std::smatch matches;
    while (!std::regex_match(str, matches, time_regex))
    {
        std::cout << "Некорректный ввод. Пожалуйста, введите время без лишних символов.\n->";
        istr.clear();
        istr.ignore(std::cin.rdbuf()->in_avail());
        std::getline(istr, str);
    }
    Time time(str);
    return time;
}

Time time_in_sec(std::istream& istr)
{
    int sec;
    if (&istr == &std::cin) std::cout << "Введите время в секундах: ";
    istr >> sec;
    while (istr.fail() || sec < 0) {
        std::cout << "Некорректный ввод. Пожалуйста, введите целое число.\n->";
        istr.clear();
        istr.ignore(std::cin.rdbuf()->in_avail());
        istr >> sec;
    }
    Time time(sec);
    return time;
}

Time time_in_tm(std::istream& istr)
{
    struct tm time = {};
    int h, m, s;
    if (&istr == &std::cin) std::cout << "Введите время (часы, минуты, секунды через пробел): ";
    istr >> h >> m >> s;
    while (istr.fail() || h < 0 || m < 0 || s < 0) {
        std::cout << "Некорректный ввод. Пожалуйста, введите целые числа.\n->";
        istr.clear();
        istr.ignore(std::cin.rdbuf()->in_avail());
        istr >> h >> m >> s;
    }
    time.tm_hour = h;          
    time.tm_min = m;        
    time.tm_sec = s;
    Time t(&time);
    return t;
}

void time_in(int option, Time& time, std::istream& istr)
{
    switch (option)
    {
    case 1:
        time = time_in_num(istr);
        break;
    case 2:
        time = time_in_str(istr);
        break;
    case 3:
        time = time_in_sec(istr);
        break;
    default:
        time = time_in_tm(istr);
        break;
    }
}

template<typename T>
void print_time(T obj, std::ostream& ostr)
{
    ostr << obj;
}

template<typename T>
T get_file()
{
    std::cout << "Введите имя файла:\n>";
    std::string file_name;
    std::cin >> file_name;
    T file(file_name);
    while (!file)
    {
        std::cout << "Файл не найден! Введите корректное название файла!\n-> ";
        std::cin.clear();
        std::string file_name;
        std::cin >> file_name;
        file.open(file_name);
    }
    return file;
}

bool condition(int x, int border)
{
    return x > 0 && x < border;
}

void read_and_check(int& x, bool(*condition)(int, int), int border)
{
    std::cout << "\n->";
    while (!(std::cin >> x && condition(x, border))) {
        std::cout << "Ошибка! Введите корректное значение:\n";
        std::cin.clear();
        std::cin.ignore(std::cin.rdbuf()->in_avail());
        std::cout << "\n->";
    }
}

int menu(const char* message, bool(*condition)(int, int), int border)
{
    std::cout << message;
    int option{};
    read_and_check(option, condition, border);
    std::cout << "\n";
    return option;
}