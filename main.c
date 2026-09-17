#include <stdio.h>
#include <string.h>

#define MAX_PATIENTS 100
#define SPECIALTY_ID 4
#define WARD_ID 4
#define MAX_BEDS 20



//Doctor specialized data
const char specialtyName[SPECIALTY_ID][50]= {"General Practice(OPD)","Paediatrics ","Cardiology","Neurology"};
const float consultationFee[SPECIALTY_ID]= {1500.00,2500.00,4500.00,5000.00};
const int consultationTimeInMinute[SPECIALTY_ID]= {15,20,30,30};
const int dailyPatientCapacity[SPECIALTY_ID]= {30,20,12,10};
//Hospital wards data
const char wardName[WARD_ID][50]= {"General Ward","Paediatric Ward","Surgical Ward","ICU(Intensive Care Unit)"};
const float dailyBedRate[WARD_ID]= {3000.00,6000.00,12000.00,25000.00};
const int totalBedCapacity[WARD_ID]= {20,10,10,5};

/*Test step 1
 printf("Specialty Name ID 1: %s\n", specialtyName[0]);
 printf("Base Consultation Fee: %.2f\n", consultationFee[0]);
 printf("Consultation Time: %d mins\n",consultationTimeInMinute[0]);
 printf("Daily Patient Capacity: %d\n",dailyPatientCapacity[0]);
 printf("\n");
 printf("Ward Name ID 4: %s\n", wardName[3]);
 printf("Daily Bed Rate: %.2f\n",dailyBedRate[3]);
 printf("Total Bed Capacity: %02d\n",totalBedCapacity[3]);*/

//Bed Status Tracking
int bedOccupancy[WARD_ID][MAX_BEDS]= {0};
int specialtyQueueCount[SPECIALTY_ID]= {0};


int readValidInteger(const char *userPrompt, int minimumValue, int maximumValue)
{
    int inputValue;

    int valid=0;
    do
    {
        printf("%s",userPrompt);

        scanf("%d", &inputValue);

        if (inputValue < minimumValue|| inputValue > maximumValue)
        {
            printf("Invalid input. Please enter a value between %d and %d.\n",
                   minimumValue, maximumValue);
        }
        else
        {
            valid = 1;
        }
    }
    while (valid == 0);

    return inputValue;
}

void displaySpecialties()
{
    printf("\n");
    printf("=========================================================================================================\n");
    printf("                                      DOCTOR SPECIALTIES DATA\n");
    printf("=========================================================================================================\n");


    printf("|%-12s | %-25s | %-21s | %-17s | %s|\n",
           "Specialty ID", "Specialty Name", "Consultation Fee(LKR)", "Consultation Time", "Patient Capacity");

    printf("---------------------------------------------------------------------------------------------------------\n");

    for (int i = 0; i < SPECIALTY_ID; i++)
    {

        printf("|     %2d      | %-25s | %21.2f | %12d mins | %d (Reserved: %d)|\n",
               i + 1,
               specialtyName[i],
               consultationFee[i],
               consultationTimeInMinute[i],
               dailyPatientCapacity[i],
               specialtyQueueCount[i]);
    }

    printf("=========================================================================================================\n");
}

void displayWards()
{

    printf("\n");
    printf("========================================================================================\n");
    printf("                                     HOSPITAL WARDS\n");
    printf("========================================================================================\n");

    printf("|Ward ID | %-25s | %-26s | %s|\n",
           "Ward Name", "Daily Bed Rate (LKR / Day)", "Total Bed Capacity");

    printf("----------------------------------------------------------------------------------------\n");
    for (int i = 0; i < WARD_ID; i++)
        {
        int occupiedCount = 0;
        for (int bed = 0; bed < totalBedCapacity[i]; bed++)
        {
            if (bedOccupancy[i][bed] == 1)
            {
                occupiedCount++;
            }
        }
        printf("|   %2d   | %-25s | %26.2f |    %02d (Occupied: %d)|\n",
               i + 1,
               wardName[i],
               dailyBedRate[i],
               totalBedCapacity[i],
               occupiedCount);
    }

    printf("========================================================================================\n");
}

void displayBedAvailability()
{
    printf("\n");
    printf("============================================================\n");
    printf("                    BED AVAILABILITY\n");
    printf("============================================================\n");

    for (int i = 0; i < WARD_ID; i++)
    {
    printf("\n%d.%s\n",i+1,wardName[i]);
    printf("============================================================\n");

        for (int j = 0; j < totalBedCapacity[i]; j++)
        {
            if (bedOccupancy[i][j] == 0)
            {
                printf("Bed #%02d : Available\n", j + 1);
            }
            else
            {
                printf("Bed #%02d : Occupied\n", j + 1);
            }
        }
    }

    printf("\n============================================================\n");
}




int main()
{
    /*Test readValidInteger function
    int age = readValidInteger("Enter your age: ", 1, 60);
    printf(" Your age is: %d\n", age);*/

    /*Test displaySpecialties function
    displaySpecialties();*/

    /*Test displayWards function
     displayWards();*/

    /*Test displayBedAvailability function
    displayBedAvailability();*/

    return 0;
}
