/*
NAME : ADITYA GUPTA
BATCH : R1
ROLL NUMBER : BT19CSE002
*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define SIZE_TYPE 20
#define SIZE_LOCATION 50

typedef struct time
{
    int hour, min, sec;
} time;

typedef struct date
{
    int day, month, year;
} date;

typedef struct sensor_node
{
    int sensor_ID, distance_between_stations;
    char sensor_type[SIZE_TYPE], sensor_station[SIZE_LOCATION];
    time duration;
    struct sensor_node *next;
} sensor_node;

typedef struct record
{
    int sensor_ID;
    float data;
    date d;
    time t;
    struct record *next;
} record;

sensor_node *create_sensor_node(int SID, int distance_between_stations, char sensor_type[], char sensor_station[], time duration)
{
    sensor_node *new_node = (sensor_node *)malloc(sizeof(sensor_node));
    new_node->sensor_ID = SID;
    new_node->distance_between_stations = distance_between_stations;
    strcpy(new_node->sensor_type, sensor_type);
    strcpy(new_node->sensor_station, sensor_station);
    new_node->duration = duration;
    new_node->next = NULL;
    return new_node;
}

record *create_central_repo_node(int SID, float data, date d, time t)
{
    record *new_node = (record *)malloc(sizeof(record));
    new_node->sensor_ID = SID;
    new_node->data = data;
    new_node->d = d;
    new_node->t = t;
    new_node->next = NULL;
    return new_node;
}

sensor_node *headDB = NULL;

record *headCR = NULL;

void create_sensor_list(sensor_node *new_node)
{
    if (!headDB)
        headDB = new_node;
    else
    {
        sensor_node *temp = headDB;
        while (temp->next)
            temp = temp->next;
        temp->next = new_node;
        temp->next = new_node;
    }
}

void central_repository(record *new_node)
{
    if (!headCR)
        headCR = new_node;
    else
    {
        record *temp = headCR;
        while (temp->next)
            temp = temp->next;
        temp->next = new_node;
        temp->next = new_node;
    }
}

int comes_first(int a, int b)
{
    if (headDB->sensor_ID == a)
        return a;
    else if (headDB->sensor_ID == b)
        return b;
    sensor_node *temp = headDB;
    while (temp->sensor_ID != a && temp->sensor_ID != b)
    {
        temp = temp->next;
        if (temp->sensor_ID == a)
        {
            return a;
        }
        else if (temp->sensor_ID == b)
        {
            return b;
        }
    }
    return 0;
}

int comes_second(int a, int b)
{
    if (headDB->sensor_ID == a)
        return b;
    else if (headDB->sensor_ID == b)
        return a;
    sensor_node *temp = headDB;
    while (temp->sensor_ID != a && temp->sensor_ID != b)
    {
        temp = temp->next;
        if (temp->sensor_ID == b)
        {
            return a;
        }
        else if (temp->sensor_ID == a)
        {
            return b;
        }
    }
    return 0;
}

void Install_new_Sensor(int SID1, int SID2, char SType[])
{
    int SID_start = comes_first(SID1, SID2), SID_end = comes_second(SID1, SID2);
    if (!SID_start && !SID_end)
    {
        printf("No such sensors available\n");
        return;
    }
    sensor_node *temp1 = headDB, *temp2;
    int distance = 0;
    while (temp1->sensor_ID != SID_start && temp1)
        temp1 = temp1->next;
    temp2 = temp1;
    while (temp2->sensor_ID != SID_end)
    {
        temp2 = temp2->next;
        if (!strcmp(temp2->sensor_type, SType))
        {
            printf("New sensor can not be installed as sensor of type %s already exits between sensors %d & %d\n", SType, SID_start, SID_end);
            return;
        }
        distance += temp2->distance_between_stations;
    }
    if (distance < 10000)
    {
        printf("New sensor cannot be installed as the distance between sensors %d & %d is less then 10km\n", SID_start, SID_end);
        return;
    }
    else
    {
        int SID, SDistance;
        char SStation[SIZE_LOCATION];
        time t;
        printf("Enter sensor station : ");
        scanf("%s", SStation);
        printf("Enter the sensor ID of sensor to be installed : ");
        scanf("%d", &SID);
        printf("Enter the distance from first sensor : ");
        scanf("%d", &SDistance);
        printf("Enter time duration between fetching of data (in hour<space>min<space>sec format) : ");
        scanf("%d%d%d", &t.hour, &t.min, &t.sec);
        sensor_node *temp2 = create_sensor_node(SID, SDistance, SType, SStation, t);
        temp2->next = temp1->next;
        temp1->next = temp2;
        temp2->distance_between_stations -= SDistance;
    }
}

int day_count(date d1, date d2)
{
    return (d1.day - d2.day) + 31 * (d1.month - d2.month) + 365 * (d1.year - d2.year);
}

void print_database()
{
    sensor_node *temp = headDB;
    while (temp)
    {
        printf("%d\t\t%s\t\t%s\t\t%d:%d:%d\t\t%d\n", temp->sensor_ID, temp->sensor_type, temp->sensor_station, temp->duration.hour, temp->duration.min, temp->duration.sec, temp->distance_between_stations);
        temp = temp->next;
    }
}

void delete_central_repo_node(int SID)
{
    record *prev, *temp = headCR;
    if (headCR->sensor_ID == SID)
    {
        headCR = headCR->next;
    }
    else
    {
        while (temp->sensor_ID != SID && temp)
        {
            prev = temp;
            temp = temp->next;
        }
        if (!temp)
            return;
        prev->next = temp->next;
    }
    free(temp);
}

void delete_database_node(int SID)
{
    sensor_node *prev, *temp = headDB;
    if (headDB->sensor_ID == SID)
    {
        headDB = headDB->next;
    }
    else
    {
        while (temp->sensor_ID != SID && temp)
        {
            prev = temp;
            temp = temp->next;
        }
        if (!temp)
            return;
        prev->next = temp->next;
    }
    free(temp);
}

void Idle_sensors(date d)
{
    sensor_node *tempDB = headDB;
    record *tempCR1 = headCR, *tempCR2 = NULL, *tempCR3 = headCR;
    while (tempDB)
    {
        while (tempCR1)
        {
            if (tempCR1->sensor_ID == tempDB->sensor_ID)
                tempCR2 = tempCR1;
            tempCR1 = tempCR1->next;
        }
        if (day_count(d, tempCR2->d) > 60)
        {
            delete_database_node(tempDB->sensor_ID);
            printf("%d %d\n", day_count(d, tempCR2->d), tempCR2->sensor_ID);
            while (tempCR3 && tempCR3 != tempCR2)
            {
                delete_central_repo_node(tempCR2->sensor_ID);
                tempCR3 = tempCR3->next;
            }
            delete_central_repo_node(tempCR2->sensor_ID);
        }
        else
            tempDB = tempDB->next;
    }
}

int compare_date(date d1, date d2)
{
    if (d1.year > d2.year)
        return 1;
    else if (d1.year < d2.year)
        return -1;
    else
    {
        if (d1.month > d2.month)
            return 1;
        else if (d1.month < d2.month)
            return -1;
        else
        {
            if (d1.day > d2.day)
                return 1;
            else if (d1.day < d2.day)
                return -1;
            else
                return 0;
        }
    }
}

int compare_time(time t1, time t2)
{
    if (t1.hour > t2.hour)
        return 1;
    else if (t1.hour < t2.hour)
        return -1;
    else
    {
        if (t1.min > t2.min)
            return 1;
        else if (t1.min < t2.min)
            return -1;
        else
        {
            if (t1.sec > t2.sec)
                return 1;
            else if (t1.sec < t2.sec)
                return -1;
            else
                return 0;
        }
    }
}

sensor_node *search_database_node(int SID)
{
    if (!headDB)
        return headDB;
    sensor_node *temp = headDB;
    while (temp->sensor_ID != SID)
        temp = temp->next;
    return temp;
}

void Retrieve_info(char SType[], date d_start, date d_end, time t_start, time t_end)
{
    record *temp = headCR;
    while (temp)
    {
        if (!strcmp(search_database_node(temp->sensor_ID)->sensor_type, SType) && compare_date(d_start, temp->d) != 1 && compare_date(d_end, temp->d) != -1)
            printf("%d\t\t%s\t\t%.2d/%.2d/%.2d\t%.2d:%.2d:%.2d\t%f\n", temp->sensor_ID, SType, temp->d.day, temp->d.month, temp->d.year, temp->t.hour, temp->t.min, temp->t.sec, temp->data);
        temp = temp->next;
    }
}

void find_communicating_neighbours()
{
    sensor_node *temp1 = headDB, *temp2;
    int i = 1;
    int g_max_distance = 0;
    while (temp1)
    {
        temp2 = temp1;
        printf("Group %d contains sensor with sensor IDs : ", i);
        while (g_max_distance <= 10000 && temp1)
        {
            printf("%d ", temp1->sensor_ID);
            temp1 = temp1->next;
            if (temp1)
                g_max_distance += temp1->distance_between_stations;
        }
        i++;
        printf("\n");
        while (g_max_distance > 10000)
        {
            temp2 = temp2->next;
            g_max_distance -= temp2->distance_between_stations;
        }
        if (temp1)
        {
            temp1 = temp2;
            g_max_distance = 0;
        }
    }
}

void AQI_status_date(char status[], char SStation[])
{
    if (!headCR)
        return;
    record *tempCR = headCR;
    date d;
    d.day = 0;
    d.month = 0;
    d.year = 0;
    while (tempCR)
    {
        if (!strcmp(search_database_node(tempCR->sensor_ID)->sensor_type, "AQI") && !strcmp(SStation, search_database_node(tempCR->sensor_ID)->sensor_station))
        {
            char str[30];
            switch (1 + (int)tempCR->data / 50)
            {
            case 1:
                strcpy(str, "good");
                break;
            case 2:
                strcpy(str, "satisfactory");
                break;
            case 3:
                strcpy(str, "moderately polluted");
                break;
            case 4:
                strcpy(str, "moderately polluted");
                break;
            case 5:
                strcpy(str, "poor");
                break;
            case 6:
                strcpy(str, "poor");
                break;
            case 7:
                strcpy(str, "may cause respiratory illness");
                break;
            case 8:
                strcpy(str, "may cause respiratory illness");
                break;
            case 9:
                strcpy(str, "severe");
                break;
            case 10:
                strcpy(str, "severe");
                break;
            default:
                strcpy(str, "hazardous");
                break;
            }
            if (!strcmp(str, status) && compare_date(tempCR->d, d) == 1 && !strcmp(SStation, search_database_node(tempCR->sensor_ID)->sensor_station))
            {
                d = tempCR->d;
                printf("Date with %s AQI status : %d/%d/%d\n", status, tempCR->d.day, tempCR->d.month, tempCR->d.year);
            }
        }
        tempCR = tempCR->next;
    }
}

void month_max_pollution()
{
    record *tempCR = headCR;
    while (strcmp(search_database_node(tempCR->sensor_ID)->sensor_type, "AQI") && tempCR)
        tempCR = tempCR->next;

    int max_pollution = tempCR->data, month_with_max_pollution = tempCR->d.month;
    while (tempCR)
    {
        if (tempCR->data > max_pollution && !strcmp(search_database_node(tempCR->sensor_ID)->sensor_type, "AQI"))
        {
            max_pollution = tempCR->data;
            month_with_max_pollution = tempCR->d.month;
        }
        tempCR = tempCR->next;
    }
    printf("The month with maximum polluttion : %d\n", month_with_max_pollution);
}
