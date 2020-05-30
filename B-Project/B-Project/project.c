#include <locale.h>
#include "project.h"

void Create_Project(Project* p, int project_amount)
{
    char ch;

    p->number = project_amount;
    printf_s("\t\t\tПроект №%d\n", p->number);
    input_project_name(p);
    p->task_amount = 0;
    p->begin_data = (Data*)malloc(sizeof(Data));
    p->end_data = (Data*)malloc(sizeof(Data));
    add_task_to_project(p);
    do
    {
        printf_s("\nХотите добавить еще задачу? 1 - да, любая клавиша - нет: ");
        ch = getch();
        if (ch == '1')
        {
            printf_s("\n");
            add_task_to_project(p);
        }
    } while (ch == '1');
    printf_s("\n\n..............Проект создан............\n\n");
}

void input_project_name(Project* p)
{
    int len;

    printf_s("Введите название проекта: ");
    fgets(p->name, MAX_NAME_LEN, stdin);
    len = strlen(p->name);
    p->name[len - 1] = '\0';
}

void add_task_to_project(Project* p)
{
    if (p->task_amount == 0)
    {
        p->begin_data = (Data*)malloc(sizeof(Data));
        p->end_data = (Data*)malloc(sizeof(Data));
    }
    p->task_amount++;
    p->tasks[p->task_amount - 1] = (Task*)malloc(sizeof(Task));
    Create_Task(p->tasks[p->task_amount - 1], p->task_amount);
    calculate_begin_data(p);
    calculate_end_data(p);
    calculate_cost(p);
    calculate_resources_amount(p);
}

void calculate_begin_data(Project* p)
{
    int i;
    Data*  min;

    min = p->tasks[0]->begin_data;
    for (i = 0; i < p->task_amount; i++)
    {
        if (min->year > p->tasks[i]->begin_data->year)
            min = p->tasks[i]->begin_data;
        else if (min->year == p->tasks[i]->begin_data->year)
        {
            if (min->month > p->tasks[i]->begin_data->month)
                min = p->tasks[i]->begin_data;
        }
        else if (min->year == p->tasks[i]->begin_data->year)
        {
            if (min->month == p->tasks[i]->begin_data->month)
            {
                if (min->day > p->tasks[i]->begin_data->day)
                    min = p->tasks[i]->begin_data;
            }
        }
    }
    p->begin_data->year = min->year;
    p->begin_data->month = min->month;
    p->begin_data->day = min->day;
}

void calculate_end_data(Project* p)
{
    int i;
    Data* max;

    max = p->tasks[0]->end_data;
    for (i = 0; i < p->task_amount; i++)
    {
        if (max->year < p->tasks[i]->end_data->year)
            max = p->tasks[i]->end_data;
        else if (max->year == p->tasks[i]->end_data->year)
        {
            if (max->month < p->tasks[i]->end_data->month)
                max = p->tasks[i]->end_data;
        }
        else if (max->year == p->tasks[i]->end_data->year)
        {
            if (max->month == p->tasks[i]->end_data->month)
            {
                if (max->day < p->tasks[i]->end_data->day)
                    max = p->tasks[i]->end_data;
            }
        }
    }
    p->end_data->year = max->year;
    p->end_data->month = max->month;
    p->end_data->day = max->day;
}

void calculate_cost(Project* p)
{
    int i, j;

    p->cost = 0;
    for (i = 0; i < p->task_amount; i++)
    {
        for (j = 0; j < p->tasks[i]->resource_amount; j++)
        {
            p->cost += p->tasks[i]->needed_resources[j]->cost * 
                (double)p->tasks[i]->needed_resources[j]->amount;
        }
    }
}

void calculate_resources_amount(Project* p)
{
    int i;

    p->resources_amount = 0;
    for (i = 0; i < p->task_amount; i++)
        p->resources_amount += p->tasks[i]->resource_amount;
}

void Print_Project(Project* p)
{
    int i;

    printf_s("\t\tПроект №%d\n", p->number);
    printf_s("Название проекта: %s\n", p->name);
    printf_s("Количество задач: %d\n", p->task_amount);
    if (p->task_amount != 0)
    {
        printf_s("\t\tЗадачи:\n");
        printf_s("-----------------------------------\n");
        for (i = 0; i < p->task_amount; i++)
            Print_Task(p->tasks[i]);
        printf_s("-----------------------------------\n");
        printf_s("Дата начала проекта: %02d.%02d.%d\n", p->begin_data->day,
            p->begin_data->month, p->begin_data->year);
        printf_s("Дата завершения проекта: %02d.%02d.%d\n", p->end_data->day,
            p->end_data->month, p->end_data->year);
        printf_s("Общее количество ресурсов: %d\n", p->resources_amount);
        printf_s("Общая стоимость ресурсов: %.2lf бел.руб.\n", p->cost);
        if (p->cost != 0)
        {
            printf_s("\n\tВсе ресурсы проекта:\n");
            printf_s("---------------------------------------------------\n");
        }
        print_all_resourses(p);
    }
}

void print_all_resourses(Project* p)
{
    int i, j, count = 0;

    if (p->cost != 0)
    {
        printf_s("Тип: т - трудовой, м - материальный\n");
        printf_s("    Тип\t      Название\t  Количество\tЦена(бел.руб.)\n");
        for (i = 0; i < p->task_amount; i++)
            if (p->tasks[i]->resource_amount != 0)
            {
                for (j = 0; j < p->tasks[i]->resource_amount; j++)
                {
                    printf_s("%d: ", ++count);
                    print_for_project(p->tasks[i]->needed_resources[j]);
                }
            }
    }
}

void Delete_Project(Project* p)
{
    int i;

    for (i = 0; i < p->task_amount; i++)
        Delete_Task(p->tasks[i]);
    if (p->task_amount != 0)
    {
        free(p->begin_data);
        free(p->end_data);
    }
    free(p);
}

void Change_Project(Project* p)
{
    char ch;
    int stop = 1;

    Print_Project(p);
    do
    {
        printf_s("\n\n\nЧто хотите изменить в проекте?\n1 - название\n2 - задачи\n0 - выход\n");
        do
        {
            stop = 1;
            ch = getch();
            switch (ch)
            {
                case '1':
                {
                    input_project_name(p);
                    break;
                }
                case '2':
                {
                    change_project_tasks(p);
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

void change_project_tasks(Project* p)
{
    char ch, c;
    int i, stop = 1;

    do
    {
        printf_s("\n\nЗадачу: 1 - добавить, 2 - изменить, 3 - удалить, 0 - выход\n");
        do
        {
            stop = 1;
            ch = getch();
            switch (ch)
            {
                case '1':
                {
                    printf_s("\n");
                    add_task_to_project(p);
                    break;
                }
                case '2':
                {
                    if (p->task_amount != 0)
                    {
                        printf_s("\nКакую задачу хотите изменить?\n");
                        for (i = 0; i < p->task_amount; i++)
                            printf_s("%d - Задача №%d (Название: %s)\n", i + 1, i + 1, p->tasks[i]->name);
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
                        if (i > 0 && i <= p->task_amount)
                        {
                            Change_Task(p->tasks[i - 1]);
                        }
                        else printf_s("Такой задачи нет");
                    }
                    else printf_s("В проекте задач нет");
                    break;
                }
                case '3':
                {
                    if (p->task_amount != 0)
                    {
                        printf_s("\nКакую задачу хотите удалить?\n");
                        for (i = 0; i < p->task_amount; i++)
                            printf_s("%d - Задача №%d (Название: %s)\n", i + 1, i + 1, p->tasks[i]->name);
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
                            for (i = 0; i < p->task_amount; i++)
                                Delete_Task(p->tasks[i]);
                            p->task_amount = 0;
                            printf_s("Все задачи удалены\n");
                        }
                        else if (i > p->task_amount || i < 0)
                            printf_s("Данная задача не найдена");
                        else
                        {
                            Delete_Task(p->tasks[i - 1]);
                            for (i = i - 1; i < p->task_amount - 1; i++)
                            {
                                p->tasks[i] = p->tasks[i + 1];
                                p->tasks[i]->number--;
                            }
                            printf_s("Задача удалена\n");
                            p->task_amount--;
                        }
                    }
                    else printf_s("В проекте задач нет");
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
    if (p->task_amount != 0)
    {
        calculate_begin_data(p);
        calculate_end_data(p);
        calculate_cost(p);
        calculate_resources_amount(p);
    }
}
