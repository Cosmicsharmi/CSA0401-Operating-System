#include <stdio.h>
struct Process 
{
    int id, arrival, burst, remaining, waiting, turnaround, completion;
};
void sjf_preemptive(struct Process p[], int n) 
{
    int completed = 0, time = 0, shortest = -1, minBurst = 9999;
    float total_wt = 0, total_tat = 0;

    for (int i = 0; i < n; i++)
        p[i].remaining = p[i].burst;
    while (completed < n) 
	{
        shortest = -1, minBurst = 9999;
        for (int i = 0; i < n; i++) 
		{
            if (p[i].arrival <= time && p[i].remaining > 0 && p[i].remaining < minBurst) {
                minBurst = p[i].remaining;
                shortest = i;
            }
        }
        if (shortest == -1) 
		{
            time++;
            continue;
        }
        p[shortest].remaining--;
        time++;
        if (p[shortest].remaining == 0) 
		{
            completed++;
            p[shortest].completion = time;
            p[shortest].turnaround = p[shortest].completion - p[shortest].arrival;
            p[shortest].waiting = p[shortest].turnaround - p[shortest].burst;
            total_wt += p[shortest].waiting;
            total_tat += p[shortest].turnaround;
        }
    }
    printf("\nP  A  B  W  T\n");
    for (int i = 0; i < n; i++)
        printf("%d  %d  %d  %d  %d\n", p[i].id, p[i].arrival, p[i].burst, p[i].waiting, p[i].turnaround);
    printf("\nAvg W: %.2f\nAvg T: %.2f\n", total_wt / n, total_tat / n);
}
int main() 
{
    int n;
    printf("Enter number of processes: ");
    scanf("%d", &n);
    struct Process p[n];
    printf("Enter Arrival and Burst time for each process:\n");
    for (int i = 0; i < n; i++) {
        p[i].id = i + 1;
        scanf("%d %d", &p[i].arrival, &p[i].burst);
    }
    sjf_preemptive(p, n);
    return 0;
}