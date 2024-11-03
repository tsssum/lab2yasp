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

#include "Time.h"

int menu(const char* message);
int exit();
template<typename T> void print_time(T obj, std::ostream& ostr);
Time time_in_num(std::istream& istr);
Time time_in_str(std::istream& istr);
Time time_in_sec(std::istream& istr);
Time time_in_tm();
void time_in(int option, Time& time, std::istream& istr);

int main()
{
    SetConsoleOutputCP(1251);
    Time time;
    Time time2;
    int equal;
    std::string answer;
    short option{};
    do
    {
        option = menu("\nЗадачи:\n1. Вычисление разности между двумя моментами времени в секундах.\n2. Сложение времени и заданного количества секунд\n3. Вычитание из времени заданного количества секунд\n4. Сравнение 2 моментов времени\n5. Перевод в секунды\n6. Перевод в минуты\n7. Завершение работы");
        if (option != 7)
        {
            short option2 = menu("Как вводить?\n1. Ввод из файла\n2. Ввод с клавиатуры");
            short option3 = menu("Как выводить?\n1. Вывод в файл\n2. Вывод в консоль");
            short option4 = menu("Задание времени:\n1. Числами (ввод через пробел)\n2. Строкой\n3. Секундами\n4. Встроенным типом данных");

            switch (option2)
            {
            case 1:
            {
                std::cout << "Введите имя файла для ввода:\n>";
                std::string file_name;
                std::cin >> file_name;
                std::ifstream file(file_name);
                time_in(option4, time, file);
                if (option == 1 || option == 3 || option == 4)
                {
                    short option5 = menu("\nЗадание нового времени:\n1. Числами (ввод через пробел)\n2. Строкой\n3. Секундами\n4. Встроенным типом данных");
                    time_in(option5, time2, file);
                }
                break;
            }
            case 2:
            {
                time_in(option4, time, std::cin);
                if (option == 1 || option == 3 || option == 4)
                {
                    short option5 = menu("\nЗадание нового времени:\n1. Числами (ввод через пробел)\n2. Строкой\n3. Секундами\n4. Встроенным типом данных");
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
                short choice = menu("\nКак вычислять?\n1. Методом\n2. Перегрузкой");
                if (choice == 1)
                    equal = time.seconds_between(time2);
                else
                    equal = time - time2;
                std::cout << "Разница составляет: ";
                break;
            }
            case 2://Сложение времени и заданного количества секунд
            {
                int sec;
                std::cout << "Сколько секунд прибавить?\n-> ";
                std::cin >> sec;
                short choice = menu("\nКак вычислять?\n1. Методом\n2. Перегрузкой");
                if (choice == 1)
                    time.seconds_plus(sec);
                else
                    time = time + sec;
                break;
            }
            case 3://Вычитание из времени заданного количества секунд
            {
                int sec;
                std::cout << "Сколько секунд вычесть?\n-> ";
                std::cin >> sec;
                time.seconds_minus(sec);
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
            default:
                break;
            }

            switch (option3)
            {
            case 1:
            {
                std::cout << "Введите имя файла для вывода:\n>";
                std::string file_name;
                std::cin >> file_name;
                std::ofstream file(file_name);
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
                        print_time(time, std::cout);
                break;
            }
            default:
                break;
            }
        }
        option = exit();
    } while (option != 7);

	std::cin.get();
}

int menu(const char* message)
{
	std::cout << message <<"\n-> ";
	int option{};
    std::cin >> option;
	std::cout << "\n";
	return option;
}

int exit()
{
	std::cout << "\nЗавершить работу? (Y/любая клавиша): ";
	char is_exit;
	short option_exit{};
	std::cin >> is_exit;
	if (is_exit == 'Y' || is_exit == 'y')
		option_exit = 7;
	return option_exit;
}

Time time_in_num(std::istream& istr)
{
    int h, m, s;
    if (&istr == &std::cin) std::cout << "Введите время (часы, минуты, секунды через пробел): ";
    istr >> h >> m >> s;
    Time time(h, m, s);
    return time;
}

Time time_in_str(std::istream& istr)
{
    std::string str;
    if (&istr == &std::cin) std::cout << "Введите время (часы, минуты, секунды, разделённые двоеточием): ";
    istr >> str;
    Time time(str);
    return time;
}

Time time_in_sec(std::istream& istr)
{
    int sec;
    if (&istr == &std::cin) std::cout << "Введите время в секундах: ";
    istr >> sec;
    Time time(sec);
    return time;
}

Time time_in_tm()
{
    time_t now = time(0);
    tm time{};
    localtime_s(&time, &now);
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
        time = time_in_tm();
        break;
    }
}

template<typename T>
void print_time(T obj, std::ostream& ostr)
{
    ostr << obj;
}
