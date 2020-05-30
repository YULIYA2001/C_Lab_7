#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <time.h>
#include <locale.h>
#include "List.h"

void Rrogram_Show(void);
void Show_Menu(void);
void Open_File_Add_To_List(void);
void Save_Before_Exit(void);

#define CLEAN {\
    int i;\
    printf_s("\nНажмите любую клавишу ");\
    i = _getch();\
    system("cls");\
}\

int main(void)
{
    char ch, c;
    int stop = 1;

    system("chcp 1251");
    system("cls");

    Rrogram_Show();
    printf_s("\n\t\t\tЗагрузка базы данных...\n");
    /*Resource* r = (Resource*)malloc(sizeof(Resource));
    if (r != NULL)
    {
        r->type = PEOPLE;
        printf("%d", r->type);
    }
    else puts("ghjk");*/
    Open_File_Add_To_List();
    CLEAN;
    do
    {
        Show_Menu();
        do
        {
            stop = 1;
            scanf_s("%c", &ch, 1);
            while ((c = getchar()) != '\n')  /* очистка потока ввода + адекватность */
                if (c != ' ')
                    stop = 0;
            if (stop == 0)
                printf_s("Неверный ввод. Попробуйте снова: ");
        } while (stop == 0);
        switch (ch)
        {
            case '1':
            {
                system("cls");
                add_project_to_list();
                break;
            }
            case '2':
            {
                system("cls");
                if (project_amount != 0)
                    change_project_in_list();
                else printf_s("Список проектов пуст\n");
                break;
            }
            case '3':
            {
                system("cls");
                if (project_amount != 0)
                    delete_project_from_list();
                else printf_s("Список проектов пуст\n");
                break;
            }
            case '4':
            {
                system("cls");
                if (project_amount != 0)
                    Display_Project();
                else printf_s("Список проектов пуст\n");
                break;
            }
            case '5':
            {
                system("cls");
                Display_All();
                break;
            }
            case '6':
            {
                system("cls");
                printf_s("\nРазработчик:\nГолубович Ю.И. гр.953501\n\n");
                break;
            }
            case '0':
            {
                system("cls");
                printf_s("\tВы точно хотите выйти?\n1 - да\nлюбая клавиша - нет\n");
                c = _getch();
                if (c == '1')
                {
                    Save_Before_Exit();
                    printf_s("\nИзменения сохранены\n");
                }
                else ch = '6';                
                break;
            }
            default:
            {
                stop = 0;
                printf_s("Неверный ввод. Попробуйте снова\n\n");
                break;
            }
        }
        CLEAN;
    } while (ch != '0');
    return 0;
}

void Open_File_Add_To_List(void)
{    
    int i, j, k;
    FILE* fp;
    Project* pr;
    
    fp = fopen("Database.txt", "rb");
    if (!fp)
    {
        printf_s("\nОшибка открытия файла\n");
        return;
    }
    printf_s("База данных загружена\n");
    fread(&project_amount, sizeof(int), 1, fp);
    for (i = 0; i < project_amount; i++)
    {
        pr = (Project*)malloc(sizeof(Project));
        pr->number = i + 1;
        fread(pr->name, sizeof(char), MAX_NAME_LEN - 1, fp);
        fread(&pr->task_amount, sizeof(int), 1, fp);
        for (j = 0; j < pr->task_amount; j++)
        {
            pr->tasks[j] = (Task*)malloc(sizeof(Task));
            pr->tasks[j]->number = j + 1;
            fread(pr->tasks[j]->name, sizeof(char), MAX_NAME_LEN - 1, fp);
            pr->tasks[j]->begin_data = (Data*)malloc(sizeof(Data));
            fread(&pr->tasks[j]->begin_data->year, sizeof(int), 1, fp);
            fread(&pr->tasks[j]->begin_data->month, sizeof(int), 1, fp);
            fread(&pr->tasks[j]->begin_data->day, sizeof(int), 1, fp);
            pr->tasks[j]->end_data = (Data*)malloc(sizeof(Data));
            fread(&pr->tasks[j]->end_data->year, sizeof(int), 1, fp);
            fread(&pr->tasks[j]->end_data->month, sizeof(int), 1, fp);
            fread(&pr->tasks[j]->end_data->day, sizeof(int), 1, fp);
            fread(&pr->tasks[j]->needed_time_in_days, sizeof(int), 1, fp);
            fread(&pr->tasks[j]->resource_amount, sizeof(int), 1, fp);
            for (k = 0; k < pr->tasks[j]->resource_amount; k++)
            {
                pr->tasks[j]->needed_resources[k] = (Resource*)malloc(sizeof(Resource));
                fread(&pr->tasks[j]->needed_resources[k]->type, sizeof(int), 1, fp);
                fread(pr->tasks[j]->needed_resources[k]->name, sizeof(char), 49, fp);
                fread(&pr->tasks[j]->needed_resources[k]->amount, sizeof(int), 1, fp);
                fread(&pr->tasks[j]->needed_resources[k]->cost, sizeof(double), 1, fp);
            }
        }
        if (pr->task_amount != 0)
        {
            fread(&pr->resources_amount, sizeof(int), 1, fp);
            pr->begin_data = (Data*)malloc(sizeof(Data));
            if (pr->begin_data != NULL)
            {
                fread(&pr->begin_data->year, sizeof(int), 1, fp);
                fread(&pr->begin_data->month, sizeof(int), 1, fp);
                fread(&pr->begin_data->day, sizeof(int), 1, fp);
            }
            pr->end_data = (Data*)malloc(sizeof(Data));
            if (pr->end_data != NULL)
            {
                fread(&pr->end_data->year, sizeof(int), 1, fp);
                fread(&pr->end_data->month, sizeof(int), 1, fp);
                fread(&pr->end_data->day, sizeof(int), 1, fp);
            }
            fread(&pr->cost, sizeof(double), 1, fp);
        }
        Add(pr);
    }
    fclose(fp);
}

void Save_Before_Exit(void)
{
    int j, k;
    FILE* fp;
    List* p = head;
    
    fp = fopen("Database.txt", "wb");
    if (!fp)
    {
        printf_s("\nОшибка открытия файла\n");
        return;
    }
    fwrite(&project_amount, sizeof(int), 1, fp);
    while(p != NULL)
    {
        fwrite(p->project->name, sizeof(char), MAX_NAME_LEN - 1, fp);
        fwrite(&p->project->task_amount, sizeof(int), 1, fp);
        for (j = 0; j < p->project->task_amount; j++)
        {
            fwrite(p->project->tasks[j]->name, sizeof(char), MAX_NAME_LEN - 1, fp);
            fwrite(&p->project->tasks[j]->begin_data->year, sizeof(int), 1, fp);
            fwrite(&p->project->tasks[j]->begin_data->month, sizeof(int), 1, fp);
            fwrite(&p->project->tasks[j]->begin_data->day, sizeof(int), 1, fp);
            fwrite(&p->project->tasks[j]->end_data->year, sizeof(int), 1, fp);
            fwrite(&p->project->tasks[j]->end_data->month, sizeof(int), 1, fp);
            fwrite(&p->project->tasks[j]->end_data->day, sizeof(int), 1, fp);
            fwrite(&p->project->tasks[j]->needed_time_in_days, sizeof(int), 1, fp);
            fwrite(&p->project->tasks[j]->resource_amount, sizeof(int), 1, fp);
            for (k = 0; k < p->project->tasks[j]->resource_amount; k++)
            {
                fwrite(&p->project->tasks[j]->needed_resources[k]->type, sizeof(int), 1, fp);
                fwrite(p->project->tasks[j]->needed_resources[k]->name, sizeof(char), 49, fp);
                fwrite(&p->project->tasks[j]->needed_resources[k]->amount, sizeof(int), 1, fp);
                fwrite(&p->project->tasks[j]->needed_resources[k]->cost, sizeof(double), 1, fp);
            }
        }
        if (p->project->task_amount != 0)
        {
            fwrite(&p->project->resources_amount, sizeof(int), 1, fp);
            fwrite(&p->project->begin_data->year, sizeof(int), 1, fp);
            fwrite(&p->project->begin_data->month, sizeof(int), 1, fp);
            fwrite(&p->project->begin_data->day, sizeof(int), 1, fp);
            fwrite(&p->project->end_data->year, sizeof(int), 1, fp);
            fwrite(&p->project->end_data->month, sizeof(int), 1, fp);
            fwrite(&p->project->end_data->day, sizeof(int), 1, fp);
            fwrite(&p->project->cost, sizeof(double), 1, fp);
        }
        p = p->next;
    }
    Delete_All();
}

void Show_Menu(void)
{
    printf_s("-----------------------Меню--------------------------\n");
    printf_s("        1 - Создать новый проект\n");
    printf_s("        2 - Редактировать проект\n");
    printf_s("        3 - Удалить проект\n");
    printf_s("        4 - Просмотреть проект\n");
    printf_s("        5 - Просмотреть базу данных\n");
    printf_s("        6 - Информация о разработчике\n");
    printf_s("        0 - Сохранить все и выйти\n");
    printf_s("-----------------------------------------------------\n");
}


void Rrogram_Show(void)
{
    printf_s("\t--------------------------------------------------------------------\n");
    printf_s("\t|                                                                  |\n");
    printf_s("\t|     BBBBB                                                        |\n");
    printf_s("\t|    B     B        ooooo                o                  o      |\n");
    printf_s("\t|    B     B        o    o                                 ooo     |\n");
    printf_s("\t|    BBBBBBB   --   ooooo  o ooo   ooo   o   oooo    oooo   o      |\n");
    printf_s("\t|    B      B       o      oo     o   o  o  oooooo  o       o      |\n");
    printf_s("\t|    B      B       o      o      o   o  o  o       o       o      |\n");
    printf_s("\t|    BBBBBBB        o      o       ooo   o   oooo    oooo   oo     |\n");
    printf_s("\t|                                      ooo                         |\n");
    printf_s("\t|                                                                  |\n");
    printf_s("\t|                                                                  |\n");
    printf_s("\t|       Vercion 1.0                                                |\n");
    printf_s("\t|                                                                  |\n");
    printf_s("\t--------------------------------------------------------------------\n");
    CLEAN;
}



