#include "Sensor_functions.c"
int main()
{
    printf("******************************************************************************************************************************************\n");
    printf("                                       WELCOME TO SERVER SYSTEM MANAGEMENT SOFTWARE\n");
    printf("******************************************************************************************************************************************\n");
    int option = 1;
    while (option)
    {
        printf("\nChoose the operation to be performed :\n\n");
        printf("Press 0 to exit\n");
        printf("Press 1 : Install new sensor\n");
        printf("Press 2 : Delete Idel sensor\n");
        printf("Press 3 : To retrieve information\n");
        printf("Press 4 : To print Communicating neighbours\n");
        printf("Press 5 : Input data\n"); //Just for testing
        printf("Press 6 : to view server database\n");
        printf("Press 7 : to view dates with hazardous status\n");
        printf("Press 8 : to find month with maximum pollution\n");
        printf("Press 9 : to find all dates with perticular health condition on a specific sensor station\n");
        printf("\nChoice : ");
        scanf("%d", &option);
        switch (option)
        {
            int SID_start, SID_end, SID, data, SDistance;
            char SType[SIZE_TYPE], SStation[SIZE_LOCATION];
            date d_default, d_today;
            time t, t_start, t_end;
        case 1:
            printf("Press 1 : to install at the end of sensors\n");
            printf("Press 2 : to install between two different sensors\n");
            int choice;
            scanf("%d", &choice);
            if (choice == 1)
            {
                printf("Enter sensor station : ");
                scanf("%s", SStation);
                printf("Enter sensor type : ");
                scanf("%s", SType);
                printf("Enter Sensor ID : ");
                scanf("%d", &SID);
                printf("Enter distance from previous sensor(in metres) : ");
                scanf("%d", &SDistance);
                printf("Enter time interval between successive fetching data(in hour<space>min<space>sec format) : ");
                scanf("%d%d%d", &t.hour, &t.min, &t.sec);
                create_sensor_list(create_sensor_node(SID, SDistance, SType, SStation, t));
            }
            else if (choice == 2)
            {
                printf("Enter sensor type of sensor to be installed : ");
                scanf("%s", SType);
                printf("Enter sensor IDs of sensors between which you want to install sensor : ");
                scanf("%d%d", &SID_start, &SID_end);
                Install_new_Sensor(SID_start, SID_end, SType);
            }
            else
                printf("Invalid key, please try again\n");
            break;
        case 2:
            printf("Enter todays date (in day<space>month<space>year format) : ");
            scanf("%d%d%d", &d_today.day, &d_today.month, &d_today.year);
            Idle_sensors(d_today);
            break;
        case 3:
            printf("Enter sensor type : ");
            scanf("%s", SType);
            printf("\nPress 1 : Retrieve information Depending on sensor type (retrieves till date data)\n");
            printf("\nPress 2 : Retrieve information Depending on specified date range (multiple dates) for specific sensor type\n");
            printf("\nPress 3 : Retrieve information Depending on specified time and date range (multiple dates) for specific sensor type\n");
            printf("\nPress 4 : Retrieve information Depending on specified time range (multiple dates) for specific sensor type and specific date\n");
            scanf("%d", &choice);
            if (choice == 1)
            {
                d_default.day = 0;
                d_default.month = 0;
                d_default.year = 0;
                t_start.hour = 0;
                t_start.min = 0;
                t_start.sec = 0;
                t_end.hour = 23;
                t_end.min = 59;
                t_end.sec = 59;
                printf("Enter todays date (in day<space>month<space>year format) : ");
                scanf("%d%d%d", &d_today.day, &d_today.month, &d_today.year);
                printf("Sensor ID\tSensor type\tDate\t\tTime\t\tData\n");
                Retrieve_info(SType, d_default, d_today, t_start, t_end);
            }
            else if (choice == 2)
            {
                date d_start, d_end;
                t_start.hour = 0;
                t_start.min = 0;
                t_start.sec = 0;
                t_end.hour = 23;
                t_end.min = 59;
                t_end.sec = 59;
                printf("Enter starting date (in day<space>month<space>year format) : ");
                scanf("%d%d%d", &d_start.day, &d_start.month, &d_start.year);
                printf("Enter ending date (in day<space>month<space>year format) : ");
                scanf("%d%d%d", &d_end.day, &d_end.month, &d_end.year);
                printf("Sensor ID\tSensor type\tDate\t\tTime\t\tData\n");
                Retrieve_info(SType, d_start, d_end, t_start, t_end);
            }
            else if (choice == 3)
            {
                date d_start, d_end;
                printf("Enter starting date (in day<space>month<space>year format) : ");
                scanf("%d%d%d", &d_start.day, &d_start.month, &d_start.year);
                printf("Enter ending date (in day<space>month<space>year format) : ");
                scanf("%d%d%d", &d_end.day, &d_end.month, &d_end.year);
                printf("Enter starting time (in hour<space>min<space>sec format) : ");
                scanf("%d%d%d", &t_start.hour, &t_start.min, &t_start.sec);
                printf("Enter ending time (in hour<space>min<space>sec format) : ");
                scanf("%d%d%d", &t_end.hour, &t_end.min, &t_end.sec);
                printf("Sensor ID\tSensor type\tDate\t\tTime\t\tData\n");
                Retrieve_info(SType, d_start, d_end, t_start, t_end);
            }
            else if (choice == 4)
            {
                date d;
                printf("Enter the date (in day<space>month<space>year format) : ");
                scanf("%d%d%d", &d.day, &d.month, &d.year);
                printf("Enter starting time (in hour<space>min<space>sec format) : ");
                scanf("%d%d%d", &t_start.hour, &t_start.min, &t_start.sec);
                printf("Enter ending time (in hour<space>min<space>sec format) : ");
                scanf("%d%d%d", &t_end.hour, &t_end.min, &t_end.sec);
                printf("Sensor ID\tSensor type\tDate\t\tTime\t\tData\n");
                Retrieve_info(SType, d, d, t_start, t_end);
            }
            else
                printf("Invalid choice, Please try again\n");
            break;
        case 4:
            find_communicating_neighbours();
            break;
        case 5:
            printf("Enter Sensor id : ");
            scanf("%d", &SID);
            date d;
            printf("Enter date (in day<space>month<space>year format) : ");
            scanf("%d%d%d", &d.day, &d.month, &d.year);
            printf("Enter time (in hour<space>min<space>sec format) : ");
            scanf("%d%d%d", &t.hour, &t.min, &t.sec);
            printf("Enter data : ");
            scanf("%d", &data);
            central_repository(create_central_repo_node(SID, data, d, t));
            break;
        case 6:
            printf("Sensor ID\tSensor type\tSensor station\tDuration\tDistance from previous station\n");
            print_database();
            break;
        case 7:
            printf("Enter the health condition : ");
            char status[30];
            scanf("%s", status);
            sensor_node *temp = headDB;
            while (temp)
            {
                if (!strcmp(temp->sensor_type, "AQI"))
                    AQI_status_date(status, temp->sensor_station);
                temp = temp->next;
            }
            break;
        case 8:
            month_max_pollution();
            break;
        case 9:
            printf("Enter sensor station : ");
            scanf("%s", SStation);
            AQI_status_date("hazardous", SStation);
            break;
        default:
            if (option)
                printf("Invalid key, Please try again\n");
            break;
        }
    }
    return 0;
}