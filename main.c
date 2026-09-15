#include <stdio.h>
#include <stdlib.h>

int main()
{
   //Doctor specialized data
   char specialtyName[4][50]={"General Practice(OPD)","Paediatrics ","Cardiology","Neurology"};
   float consultationFee[4]={1500.00,2500.00,4500.00,5000.00};
   int consultationTimeInMinute[4]={15,20,30,30};
   int dailyPatientCapacity[4]={30,20,12,10};
   //Hospital wards data
   char wardName[4][50]={"General Ward","Paediatric Ward","Surgical Ward","ICU(Intensive Care Unit)"};
   float dailyBedRate[4]={3000.00,6000.00,12000.00,25000.00};
   int totalBedCapacity[4]={20,10,10,5};

   //Test step 1
    printf("Specialty Name ID 1: %s\n", specialtyName[0]);
    printf("Base Consultation Fee: %.2f\n", consultationFee[0]);
    printf("Consultation Time: %d mins\n",consultationTimeInMinute[0]);
    printf("Daily Patient Capacity: %d\n",dailyPatientCapacity[0]);
    printf("\n");
    printf("Ward Name ID 4: %s\n", wardName[3]);
    printf("Daily Bed Rate: %.2f\n",dailyBedRate[3]);
    printf("Total Bed Capacity: %02d\n",totalBedCapacity[3]);


    return 0;
}
