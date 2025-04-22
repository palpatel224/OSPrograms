#include <stdio.h>

int main()
{
    int n;
    printf("Enter the number of processes\n");
    scanf("%d", &n);
    int arrivalTime[n];
    int burstTime[n];
    printf("Enter the arrival time and burst time of each process where arrival time is in increasing order\n");
    for (int i = 0; i < n; i++)
    {
        printf("Enter the arrival time of process %d : ", i);
        scanf("%d", &arrivalTime[i]);
        printf("Enter the burst time of process %d : ", i);
        scanf("%d", &burstTime[i]);
    }
    int completionTime[n];
    int wt[n];
    int tat[n];

    completionTime[0] = arrivalTime[0] + burstTime[0];
    for (int i = 1; i < n; i++)
    {
        if (arrivalTime[i] > completionTime[i - 1])
            completionTime[i] = arrivalTime[i] + burstTime[i];
        else
            completionTime[i] = completionTime[i - 1] + burstTime[i];
    }

    for (int i = 0; i < n; i++)
    {
        tat[i] = completionTime[i] - arrivalTime[i];
        wt[i] = tat[i] - burstTime[i];
    }

    int total_wt = 0, total_tat = 0;
    printf("\nProcess\tArrival\tBurst\tComplete\tTAT\tWait");
    printf("\nNo.\tTime\tTime\tTime\t\tTime\tTime\n");

    for (int i = 0; i < n; i++)
    {
        total_wt += wt[i];
        total_tat += tat[i];
        printf("%d\t%d\t%d\t%d\t\t%d\t%d\n",
               i + 1, arrivalTime[i], burstTime[i],
               completionTime[i], tat[i], wt[i]);
    }

    float avg_wt = (float)total_wt / n;
    float avg_tat = (float)total_tat / n;
    printf("\nAverage waiting time = %.2f", avg_wt);
    printf("\nAverage turn around time = %.2f\n", avg_tat);

    return 0;
}