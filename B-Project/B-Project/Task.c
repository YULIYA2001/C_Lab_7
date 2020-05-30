/* для определения текущей даты */
#define _CRT_SECURE_NO_WARNINGS
#include <time.h>
#include <conio.h>
#include <string.h>
#include "Task.h"

#define LIMIT 2100 /* самый далекий год, в который можно начать планирование */

void Create_Task(Task* t, int task_amount)
{
    t->number = task_amount;
    printf_s("\t\tЗадача №%d\n", t->number);
    input_task_name(t);

    t->begin_data = (Data*)malloc(sizeof(Data));
    input_task_begin_data(t->begin_data);

    input_task_needed_time_in_days(t);

    t->resource_amount = 0;
    add_needed_resource(t);
    calculate_task_end_data(t);
}

void add_needed_resource(Task* t)
{
    char ch;

    do
    {
        printf_s("Хотите добавить ресурс? 1 - да, любая клавиша - нет: ");
        ch = _getch();
        if(ch == '1')
        {
            t->resource_amount++;
            t->needed_resources[t->resource_amount - 1] = (Resource*)malloc(sizeof(Resource));
            Create_Resource(t->needed_resources[t->resource_amount - 1]);
        }
    } while (ch == '1');
}

void input_task_name(Task* t)
{
    int len;

    printf_s("Введите название задачи: ");
    fgets(t->name, MAX_NAME_LEN, stdin);
    len = strlen(t->name);
    t->name[len - 1] = '\0';
}

void input_task_needed_time_in_days(Task* t)
{
    char ch;
    int stop, month_or_days;    /* для хранения введенных месяцев */

    printf_s("Время на решение задачи(в днях либо в месецах(30дн.) и днях).\n");
    do
    {
        stop = 1;
        printf_s("Введите временной промежуток (пр1. 12m3d, пр2. 45d, пр3.1m0d): ");
        scanf_s("%d", &month_or_days);
        scanf_s("%c", &ch, 1);
        if(tolower(ch) == 'm')
        {
            month_or_days *= 30;
            scanf_s("%d", &(t->needed_time_in_days));
            scanf_s("%c", &ch, 1);
            if (tolower(ch) == 'd')
                t->needed_time_in_days += month_or_days;
            else stop = 0;
        }
        else if (tolower(ch) == 'd')
        {
            t->needed_time_in_days = month_or_days;
            while ((ch = getchar()) != '\n')  /* очистка потока ввода + адекватность */
                if (ch != ' ')
                    stop = 0;
        }
        else
            stop = 0;
        if(stop == 0)
            printf("Неверный ввод. Попробуйте снова. ");
    } while (stop == 0);
}

void input_task_begin_data(Data* bd)
{
    int stop, i;  /* stop для повторного ввода, i - итератор (и для проверки числа) */
    int day, month, year;  /* day - для текущего дня, month - для текущего месяца, year - для года */
    char strdata[11];  /* strdata - для чтения даты начала проекта с клавиатуры */
    char convert1[5], convert2[5];  /* для хранения текущей и введенной даты */
    struct tm* u;
    char str[12] = { 0 };
    const time_t timer = time(NULL);

    /* определение текущей даты для проверки ввода пользователя */
    u = localtime(&timer);
    strftime(str, 12, "%d.%m.%Y", u);

    do
    {
        printf_s("Введите дату начала выполнения (пр. 25.08.2020): ");
        do
        {
            stop = 1;
            scanf_s("%10s", strdata, (unsigned)_countof(strdata));
            while (getchar() != '\n');  /* очистка потока ввода */
            for (i = 0; i < 10; i++)
            {
                if (strdata[i] >= '0' && strdata[i] <= '9');
                else if (strdata[i] == '.' && (i == 2 || i == 5));
                else
                {
                    stop = 0;
                    break;
                }
            }
            if (stop == 0)
                printf_s("Неверный ввод. Попробуйте снова: ");
        } while (stop == 0);

        stop = 1;
        /* логическая проверка ввода года */
        for (i = 0; i < 4; i++)
        {
            convert1[i] = str[i + 6];
            convert2[i] = strdata[i + 6];
        }
        convert1[4] = convert2[4] = '\0';
        year = atoi(convert1);
        bd->year = atoi(convert2);
        if (bd->year < year || bd->year > LIMIT)
        {
            stop = 0;
            printf_s("ОШИБКА! Нельзя назначить прошедший год или год больше 2040.\n");
        }
        /* логическая проверка ввода месяца */
        convert1[0] = str[3];
        convert1[1] = str[4];
        convert2[0] = strdata[3];
        convert2[1] = strdata[4];
        convert1[2] = convert2[2] = '\0';
        month = atoi(convert1);
        bd->month = atoi(convert2);
        if (bd->month > 12 || bd->month < 1 || (bd->year == year && bd->month < month))
        {
            stop = 0;
            printf_s("ОШИБКА! Неверно введен месяц (или уже прошел).\n");
        }
        /* логическая проверка ввода числа */
        i = 1;
        convert1[0] = str[0];
        convert1[1] = str[1];
        convert2[0] = strdata[0];
        convert2[1] = strdata[1];
        convert1[2] = convert2[2] = '\0';
        day = atoi(convert1);
        bd->day = atoi(convert2);
        if (bd->day < 1 || bd->day > 31)
            i = 0;
        if ((bd->month == 4 || bd->month == 6 || bd->month == 9 || bd->month == 11) && bd->day > 30)
            i = 0;
        /* проверка на февраль */
        if (bd->year % 4 != 0 && bd->month == 2 && bd->day > 28)
            i = 0;
        if (bd->year % 4 == 0 && bd->month == 2 && bd->day > 29)
            i = 0;
        if (bd->year == year && bd->month == month && bd->day < day)
            i = 0;
        if (i == 0)
        {
            printf_s("ОШИБКА! Неверный день. Сверьте календарь (возможно, "
                "такого дня нет или он прошел).\n");
            stop = 0;
        }
    } while (stop == 0);
}

void calculate_task_end_data(Task* t)
{
    time_t next;
    const time_t timer = time(NULL);

    cur_time = localtime(&timer);
    cur_time->tm_year = t->begin_data->year - 1900;
    cur_time->tm_mon = t->begin_data->month - 1;
    cur_time->tm_mday = t->begin_data->day;
    cur_time->tm_mday += t->needed_time_in_days;

    next = mktime(cur_time);
    cur_time = localtime(&next);

    t->end_data = (Data*)malloc(sizeof(Data));
    if (t->end_data != NULL)
    {
        t->end_data->year = cur_time->tm_year + 1900;
        t->end_data->month = cur_time->tm_mon + 1;
        t->end_data->day = cur_time->tm_mday;
    }
}

void Print_Task(Task* t)
{
    int i;  /* итератор */

    printf_s("Задача №%d\n", t->number);
    printf_s("Название задачи: %s\n", t->name);
    printf_s("Дата начала: %02d.%02d.%d\n", t->begin_data->day, t->begin_data->month, t->begin_data->year);
    printf_s("Продолжительность %d дней\n", t->needed_time_in_days);
    printf_s("Дата конца: %02d.%02d.%d\n", t->end_data->day, t->end_data->month, t->end_data->year);
    printf_s("Количество ресурсов: %d\n", t->resource_amount);
    if (t->resource_amount != 0)
    {
        printf_s("\t\tРесурсы:\n");
        for (i = 0; i < t->resource_amount; i++)
            Print_Resourse(t->needed_resources[i]);
    }
}

void Change_Task(Task* t)
{
    char ch;
    int stop = 1;

    printf_s("\n\n");
    Print_Task(t);
    printf_s("\n");
    do
    {
        printf_s("\n\nЧто хотите изменить?\n1 - название\n2 - дату начала\n3 - продолжительность\n"
            "4 - ресурсы\n0 - выход\n");
        do
        {
            stop = 1;
            ch = _getch();
            switch (ch)
            {
                case '1':
                {
                    input_task_name(t);
                    break;
                }
                case '2':
                {
                    input_task_begin_data(t->begin_data);
                    calculate_task_end_data(t);
                    break;
                }
                case '3':
                {
                    input_task_needed_time_in_days(t);
                    calculate_task_end_data(t);
                    break;
                }
                case '4':
                {
                    change_task_resourses(t);
                    break;
                }
                case '0':
                {
                    break;
                }
                default:
                {
                    printf_s("Неверный ввод. Попробуйте снова: ");
                    stop = 0;
                    break;
                }
            }
        } while (stop == 0);
    } while (ch != '0');
}

void Delete_Task(Task* t)
{
    int i;

    for (i = 0; i < t->resource_amount; i++)
        Delete_Resourse(t->needed_resources[i]);
    free(t->begin_data);
    free(t->end_data);
    free(t);
}

void change_task_resourses(Task* t)
{
    char ch, c;
    int i, stop = 1;

    if (t->resource_amount == 0)
    {
        printf_s("\n\nУ данной задачи нет ресурсов.\n");
        add_needed_resource(t);
    }
    else
    {
        do
        {
            printf_s("\nРесурсы: 1 - добавить, 2 - изменить, 3 - удалить, 0 - выход\n");
            do
            {
                stop = 1;
                ch = _getch();
                switch (ch)
                {
                case '1':
                {
                    add_needed_resource(t);
                    break;
                }
                case '2':
                {
                    printf_s("Какой ресурс хотите изменить?\n");
                    for (i = 0; i < t->resource_amount; i++)
                        printf_s("%d - %s\n", i + 1, t->needed_resources[i]->name);
                    do
                    {
                        stop = 1;
                        scanf_s("%d", &i);
                        while ((c = getchar()) != '\n')  /* очистка потока ввода + адекватность */
                            if (c != ' ')
                                stop = 0;
                        if (stop == 0)
                            printf_s("Неверный ввод. Попробуйте снова: ");
                    } while (stop == 0);
                    if (i > 0 && i <= t->resource_amount)
                        Change_Resourse(t->needed_resources[i - 1]);
                    else printf_s("Данный ресурс не найден\n");
                    break;
                }
                case '3':
                {
                    printf_s("Какой ресурс хотите удалить?\n");
                    for (i = 0; i < t->resource_amount; i++)
                        printf_s("%d - %s\n", i + 1, t->needed_resources[i]->name);
                    printf_s("0 - все\n");
                    do
                    {
                        stop = 1;
                        scanf_s("%d", &i);
                        while ((c = getchar()) != '\n')  /* очистка потока ввода + адекватность */
                            if (c != ' ')
                                stop = 0;
                        if (stop == 0)
                            printf_s("Неверный ввод. Попробуйте снова: ");
                    } while (stop == 0);
                    if (i == 0)
                    {
                        for (i = 0; i < t->resource_amount; i++)
                            Delete_Resourse(t->needed_resources[i]);
                        printf_s("Все ресурсы удалены\n");
                        t->resource_amount = 0;
                    }
                    else if (i > t->resource_amount || i < 0)
                        printf_s("Данный ресурс не найден\n");
                    else
                    {
                        Delete_Resourse(t->needed_resources[i - 1]);
                        for (i = i - 1; i < t->resource_amount - 1; i++)
                        {
                            t->needed_resources[i] = t->needed_resources[i + 1];
                        }
                        printf_s("Ресурс удален\n");
                        t->resource_amount--;
                    }
                    break;
                }
                case '0':
                {
                    break;
                }
                default:
                {
                    printf_s("Неверный ввод. Попробуйте снова: ");
                    stop = 0;
                    break;
                }
                }
            } while (stop == 0);
        } while (ch != '0');
    }
}