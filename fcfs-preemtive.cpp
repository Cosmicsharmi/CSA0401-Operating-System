#include<stdio.h>
struct Process
{
	int id,arrival,burst,remaining,completion,waiting,turnaround;
};
void fcfs_preemptive(struct Process processes[],int n)
{
	int currenttime=0,completed=0;
	while(completed<n)
	{
		int selected=-1;
		for(int i=0;i<n;i++)
		{
			if(processes[i].arrival<=currenttime&&processes[i].remaining>0)
			{
				selected=i;
				break;
			}
		}
		if(selected==-1)
		{
			currenttime++;
		}
		else
		{
		processes[selected].remaining--;
		if(processes[selected].remaining==0)
		{
			processes[selected].completion=currenttime+1;
			processes[selected].turnaround=processes[selected].completion-processes[selected].arrival;
			processes[selected].waiting=processes[selected].turnaround-processes[selected].burst;
			completed++;
			}	
			currenttime++;
		}
	}
}
void printprocessdetails(struct Process processes[],int n)
{
	printf("\nProcess Table:\n");
	printf("PID\tArrival\tBurst\tTurnaround\tWaiting\n");
	for(int i=0;i<n;i++)
	{
		printf("%d\t%d\t%d\t%d\t\t%d\t\t%d\n",processes[i].id,processes[i].arrival,processes[i].burst,processes[i].completion,processes[i].turnaround,processes[i].waiting);
	}
}
int main()
{
	int n;
	printf("Enter number of processes: ");
	scanf("%d",&n);
	struct Process processes[n];
	printf("Enter Arrival time and Burst time for each process:\n");
	for(int i=0;i<n;i++)
	{
		processes[i].id=i+1;
		printf("Process%d:",i+1);
		scanf("%d %d",&processes[i].arrival,&processes[i].burst);
		processes[i].remaining=processes[i].burst;
	}
	fcfs_preemptive(processes,n);
	printprocessdetails(processes,n);
	return 0;
}