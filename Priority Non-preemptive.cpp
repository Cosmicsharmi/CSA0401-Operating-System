#include <stdio.h>
#define MAX_PROCESSES 10
struct Process 
{
    int pid;
    int bt;
    int at;
    int pr;
    int ct;
    int wt;
    int tat;
};
void sortByPriority(struct Process p[], int n) 
{
    for (int i = 0; i < n - 1; i++) 
	{
        for (int j = i + 1; j < n; j++) 
		{
            if (p[i].pr > p[j].pr) 
			{
               struct Process temp = p[i];
                p[i] = p[j];
                p[j] = temp;
            }
        }
    }
}

void calculateTimes(struct Process p[], int n) 
{
    int currentTime = 0;
    for (int i = 0; i < n; i++) 
	{
        if (currentTime < p[i].at) 
		{
            currentTime = p[i].at;
        }
        p[i].ct = currentTime + p[i].bt;
        p[i].tat = p[i].ct - p[i].at;
        p[i].wt = p[i].tat - p[i].bt;
        currentTime = p[i].ct;
    }
}
void displayResults(struct Process p[], int n) 
{
    float avg_wt = 0, avg_tat = 0;
    printf("\nProcess\tPriority\tArrival Time\tBurst Time\tWaiting Time\tTurnaround Time\n");
    for (int i = 0; i < n; i++) 
	{
        printf("P%d\t%d\t\t%d\t\t%d\t\t%d\t\t%d\n", p[i].pid, p[i].pr, p[i].at, p[i].bt, p[i].wt, p[i].tat);
        avg_wt += p[i].wt;
        avg_tat += p[i].tat;
    }
    printf("\nAverage Waiting Time: %.2f\n", avg_wt / n);
    printf("Average Turnaround Time: %.2f\n", avg_tat / n);
}
int main() 
{
    int n;
    printf("Enter number of processes: ");
    scanf("%d", &n);
    struct Process p[MAX_PROCESSES];
    for (int i = 0; i < n; i++) 
	{
        p[i].pid = i + 1;
        printf("Enter Arrival Time, Burst Time, and Priority for Process P%d: ", p[i].pid);
        scanf("%d %d %d", &p[i].at, &p[i].bt, &p[i].pr);
    }
    sortByPriority(p, n);
    calculateTimes(p, n);
    displayResults(p, n);
    return 0;
}
