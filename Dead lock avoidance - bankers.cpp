#include <stdio.h>
#define MAX_PROCESSES 5
#define MAX_RESOURCES 3
int available[MAX_RESOURCES];
int maximum[MAX_PROCESSES][MAX_RESOURCES];
int allocation[MAX_PROCESSES][MAX_RESOURCES];
int need[MAX_PROCESSES][MAX_RESOURCES];
int processes[MAX_PROCESSES];
void inputValues(int processes, int resources) 
{
    printf("Enter available resources: ");
    for (int i = 0; i < resources; i++)
        scanf("%d", &available[i]);
    printf("Enter maximum resource matrix:\n");
    for (int i = 0; i < processes; i++)
        for (int j = 0; j < resources; j++)
            scanf("%d", &maximum[i][j]);
    printf("Enter allocation matrix:\n");
    for (int i = 0; i < processes; i++)
        for (int j = 0; j < resources; j++) 
		{
            scanf("%d", &allocation[i][j]);
            need[i][j] = maximum[i][j] - allocation[i][j]; 
        }
}
int isSafe(int processes, int resources) 
{
    int finish[MAX_PROCESSES] = {0}, safeSequence[MAX_PROCESSES], work[MAX_RESOURCES];
    for (int i = 0; i < resources; i++)
        work[i] = available[i];
    int count = 0;
    while (count < processes) 
	{
        int found = 0;
        for (int i = 0; i < processes; i++) 
		{
            if (!finish[i]) 
			{
                int j;
                for (j = 0; j < resources; j++)
                    if (need[i][j] > work[j])
                        break;
                if (j == resources) 
				{
                    for (int k = 0; k < resources; k++)
                        work[k] += allocation[i][k];

                    safeSequence[count++] = i;
                    finish[i] = 1;
                    found = 1;
                }
            }
        }
        if (!found) return 0; 
    }
    printf("System is in a safe state.\nSafe sequence: ");
    for (int i = 0; i < processes; i++)
        printf("%d ", safeSequence[i]);
    printf("\n");
    return 1;
}
int main() 
{
    int processes, resources;
    printf("Enter number of processes: ");
    scanf("%d", &processes);
    printf("Enter number of resources: ");
    scanf("%d", &resources);
    inputValues(processes, resources);
    if (!isSafe(processes, resources))
        printf("System is in an unsafe state (deadlock may occur).\n");
    return 0;
}
