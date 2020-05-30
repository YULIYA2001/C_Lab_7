#pragma once

#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <time.h>
#include "Resource.h"

#define MAX_RESOURCES_AMOUNT 10
#define MAX_NAME_LEN 100

struct tm* cur_time;    /* для подсчета даты окончания задачи */

typedef struct data
{
    int day;
    int month;
    int year;
} Data;

typedef struct task
{
    int number;                                                          
    char name[MAX_NAME_LEN];                                                         
    Data* begin_data;                                                       
    Data* end_data;                                            
    int needed_time_in_days;                                                
    int resource_amount;                                                 
    Resource* needed_resources[MAX_RESOURCES_AMOUNT];                       
} Task;

void input_task_name(Task* t);
void input_task_begin_data(Data* bd);
void input_task_needed_time_in_days(Task* t);

void Create_Task(Task* t, int task_amount);
void Print_Task(Task* t);
void Change_Task(Task* t);
void Delete_Task(Task* t);

void add_needed_resource(Task* t);
void calculate_task_end_data(Task *t);
void change_task_resourses(Task* t);

//    scanf_s("%c", &ch, 1);
//    while ((c = getchar()) != '\n')  /* очистка потока ввода + адекватность */
//        if (c != ' ')
//            stop = 0;