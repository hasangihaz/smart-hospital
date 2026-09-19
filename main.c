#include <stdio.h>
#include <string.h>

#define MAX_PATIENTS 100
#define SPECIALTY_ID 4
#define WARD_ID 4
#define MAX_BEDS 20



//Doctor specialized data
const char specialtyName[SPECIALTY_ID][50]= {"General Practice(OPD)",
             "Paediatrics ","Cardiology","Neurology"};
const float consultationFee[SPECIALTY_ID]= {1500.00,2500.00,4500.00,5000.00};
const int consultationTimeInMinute[SPECIALTY_ID]= {15,20,30,30};
const int dailyPatientCapacity[SPECIALTY_ID]= {30,20,12,10};
//Hospital wards data
const char wardName[WARD_ID][50]= {"General Ward","Paediatric Ward",
               "Surgical Ward","ICU(Intensive Care Unit)"};
const float dailyBedRate[WARD_ID]= {3000.00,6000.00,12000.00,25000.00};
const int totalBedCapacity[WARD_ID]= {20,10,10,5};
\

//Bed Status Tracking
int bedOccupancy[WARD_ID][MAX_BEDS]= {0};
int specialtyQueueCount[SPECIALTY_ID]= {0};

//Patient Data
int assignedBed[MAX_PATIENTS];
int admissionStatus[MAX_PATIENTS];
int assignedWard[MAX_PATIENTS];
int stayDuration[MAX_PATIENTS];
int assignedSpecialty[MAX_PATIENTS];
int patientWaitTime[MAX_PATIENTS];
int emergencyLevel[MAX_PATIENTS];
float consultationBaseFee[MAX_PATIENTS];
float emergencySurcharge[MAX_PATIENTS];
float wardStayCost[MAX_PATIENTS];
int patientAge[MAX_PATIENTS];
float ageSubsidyDiscount[MAX_PATIENTS];
float grossTotalBill[MAX_PATIENTS];
float finalPayableAmount[MAX_PATIENTS];
int patientIndex[MAX_PATIENTS];
char patientName[MAX_PATIENTS][50];

int readValidInteger(const char *userPrompt,
                     int minimumValue, int maximumValue)
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
    printf("---------------------------------------------------------------------------------------------------------\n");


    printf("|%-12s | %-25s | %-21s | %-17s | %s|\n",
           "Specialty ID", "Specialty Name", "Consultation Fee(LKR)",
            "Consultation Time", "Patient Capacity");

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
    printf("----------------------------------------------------------------------------------------\n");

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
    printf("------------------------------------------------------------\n");

    for (int i = 0; i < WARD_ID; i++)
    {
        printf("\n%d.%s\n",i+1,wardName[i]);
        printf("------------------------------------------------------------\n");

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



int getAvailableBed(int wardIndex)
{
    for (int bed = 0; bed < totalBedCapacity[wardIndex]; bed++)
    {
        if (bedOccupancy[wardIndex][bed] == 0)
        {
            return bed;
        }

    }

    return -1;
}

void assignPatientBed(int patientId)
{
    int wardIndex= assignedWard[patientId];
    int bed = getAvailableBed(wardIndex);

    if (bed != -1)
    {
        assignedBed[patientId] = bed;
        bedOccupancy[wardIndex][bed] = 1;

        printf("\nBed allocated successfully.\n");
        printf("Assigned Bed : #%02d\n", bed + 1);
    }
    else
    {
        assignedBed[patientId]=-1;
        assignedWard[patientId]=-1;
        stayDuration[patientId]=0;
        admissionStatus[patientId]=0;

        printf("\nNo available bed in selected ward.\n");

    }
}

void calculateWaitingTime(int patientId)
{
    int specialtyIndex = assignedSpecialty[patientId];
    int currentQueueCountForSpecialty = specialtyQueueCount[specialtyIndex];
    int averageTimePerPatient = consultationTimeInMinute[specialtyIndex];


    int totalWaitTime = currentQueueCountForSpecialty*averageTimePerPatient;
    patientWaitTime[patientId] = totalWaitTime;

    specialtyQueueCount[specialtyIndex]++;
}

float calculateSurcharge(int patientId)
{
    float surcharge=0.0;
    float baseFee=consultationBaseFee[patientId];
    int urgencyLevel=emergencyLevel[patientId];

    switch(urgencyLevel)
    {
    case 1:
        surcharge=0.0;
        break;

    case 2:
        surcharge=baseFee*0.2;
        break;
    case 3:
        surcharge=baseFee*0.5;
        break;

    default:
        surcharge=0.0;
        break;
    }

    return surcharge;
}

float calculateWardCost(int patientId)
{
    float totalWardStayCost = 0.0;


    if (admissionStatus[patientId] == 1)
    {
        int wardIndex = assignedWard[patientId];
        int daysAdmitted = stayDuration[patientId];
        float wardDailyRate = dailyBedRate[wardIndex];

        totalWardStayCost = daysAdmitted*wardDailyRate;
    }

    return totalWardStayCost;
}
float calculateDiscountAmount(int patientId)
{
    float discountAmount = 0.0;

    float grossTotal = grossTotalBill[patientId];
    int age = patientAge[patientId];


    if (age < 5 || age > 65)
    {
        discountAmount = grossTotal * 0.15;
    }

    return discountAmount;
}

void calculateFinalBill(int patientId)
{
    int specialtyIndex= assignedSpecialty[patientId];

    consultationBaseFee[patientId]= consultationFee[specialtyIndex];
    emergencySurcharge[patientId]= calculateSurcharge(patientId);
    wardStayCost[patientId]= calculateWardCost(patientId);

    grossTotalBill[patientId]=consultationBaseFee[patientId]
                              +emergencySurcharge[patientId]+wardStayCost[patientId];

    ageSubsidyDiscount[patientId]=calculateDiscountAmount(patientId);

    finalPayableAmount[patientId]=grossTotalBill[patientId]-ageSubsidyDiscount[patientId];

}


void displayPatient(int patientId)
{
    char urgencyType[30];
    int urgencyLevel = emergencyLevel[patientId];
    int age = patientAge[patientId];
    int admittedWard = admissionStatus[patientId];
    float discountAmount = ageSubsidyDiscount[patientId];
    int waitTime = patientWaitTime[patientId];


    printf("\n");
    printf("====================================================================\n");
    printf("                 SMART HOSPITAL ADMISSION & BILL\n");
    printf("--------------------------------------------------------------------\n");

    printf("%-29s : PAT-%d\n", "Patient ID", patientIndex[patientId]);
    printf("%-29s : %s\n", "Patient Name", patientName[patientId]);


    if (age < 5 || age > 65)
    {
        printf("%-29s : %d Years (15%% Subsidy Eligible)\n", "Age", age);
    }
    else
    {
        printf("%-29s : %d Years\n", "Age", age);
    }

    printf("%-29s : %s\n", "Specialty", specialtyName[assignedSpecialty[patientId]]);


    if (admittedWard == 1)
    {
        int wardIndex = assignedWard[patientId];
        int bedNumber = assignedBed[patientId] + 1;
        printf("%-29s : %s (Bed #%02d)\n", "Assigned Ward", wardName[wardIndex], bedNumber);
    }
    else
    {
        printf("%-25s : Non-Admitted Patient\n", "Assigned Ward");
    }

    switch(urgencyLevel)
    {
    case 1:
        strcpy(urgencyType, "Level 1 (Normal)");
        break;
    case 2:
        strcpy(urgencyType, "Level 2 (Urgent)");
        break;
    case 3:
        strcpy(urgencyType, "Level 3 (Critical)");
        break;
    }

    printf("%-29s : %s\n", "Urgency Level", urgencyType);
    printf("--------------------------------------------------------------------\n");

    printf("%-29s : LKR %10.2f\n", "Base Consultation Fee", consultationBaseFee[patientId]);
    printf("%-29s : LKR %10.2f", "Emergency Surcharge", emergencySurcharge[patientId]);



    if (urgencyLevel== 1)
    {
        printf(" (0%%)\n");
    }
    else if (urgencyLevel == 2)
    {
        printf(" (20%%)\n");
    }
    else
    {
        printf(" (50%%)\n");
    }

    if (admittedWard== 1)
    {
        printf("Ward Stay Cost (%d Days)       : LKR %10.2f\n", stayDuration[patientId], wardStayCost[patientId]);
    }

    printf("--------------------------------------------------------------------\n");

    printf("%-29s : LKR %10.2f\n", "Gross Total Bill", grossTotalBill[patientId]);

    if (discountAmount > 0)
    {
        printf("%-29s : LKR %10.2f (15%%)\n", "Age Subsidy Discount", -discountAmount);
    }
    else
    {
        printf("%-29s : LKR %10.2f\n", "Age Subsidy Discount", 0.00);
    }

    printf("--------------------------------------------------------------------\n");

    printf("%-29s : LKR %10.2f\n", "Final Payable Amount", finalPayableAmount[patientId]);


    if (waitTime== 0)
    {
        printf("%-29s : %.2f mins (Immediate Attention)\n", "Estimated Waiting Time", (float)waitTime);
    }
    else
    {
        printf("%-29s : %d mins\n", "Estimated Waiting Time", waitTime);
    }

    printf("====================================================================\n");
}



















int main()
{


    return 0;
}
