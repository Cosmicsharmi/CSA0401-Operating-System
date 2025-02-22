#include <stdio.h>
void firstFit(int blockSize[], int m, int processSize[], int n) 
{
    int allocation[n];
    for (int i = 0; i < n; i++) allocation[i] = -1;

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            if (blockSize[j] >= processSize[i]) {
                allocation[i] = j;
                blockSize[j] -= processSize[i];
                break;
            }
        }
    }
    printf("\nFirst Fit Allocation:\n");
    printf("Process No.\tProcess Size\tBlock No.\n");
    for (int i = 0; i < n; i++) {
        printf("%d\t\t%d\t\t", i + 1, processSize[i]);
        if (allocation[i] != -1)
            printf("%d\n", allocation[i] + 1);
        else
            printf("Not Allocated\n");
    }
}
void bestFit(int blockSize[], int m, int processSize[], int n) 
{
    int allocation[n];
    for (int i = 0; i < n; i++) allocation[i] = -1;
    for (int i = 0; i < n; i++) 
	{
        int bestIdx = -1;
        for (int j = 0; j < m; j++) 
		{
            if (blockSize[j] >= processSize[i]) 
			{
                if (bestIdx == -1 || blockSize[j] < blockSize[bestIdx]) 
				{
                    bestIdx = j;
                }
            }
        }
        if (bestIdx != -1) 
		{
            allocation[i] = bestIdx;
            blockSize[bestIdx] -= processSize[i];
        }
    }
    printf("\nBest Fit Allocation:\n");
    printf("Process No.\tProcess Size\tBlock No.\n");
    for (int i = 0; i < n; i++) {
        printf("%d\t\t%d\t\t", i + 1, processSize[i]);
        if (allocation[i] != -1)
            printf("%d\n", allocation[i] + 1);
        else
            printf("Not Allocated\n");
    }
}
void worstFit(int blockSize[], int m, int processSize[], int n) 
{
    int allocation[n];
    for (int i = 0; i < n; i++) allocation[i] = -1;

    for (int i = 0; i < n; i++) 
	{
        int worstIdx = -1;
        for (int j = 0; j < m; j++) 
		{
            if (blockSize[j] >= processSize[i]) 
			{
                if (worstIdx == -1 || blockSize[j] > blockSize[worstIdx]) 
				{
                    worstIdx = j;
                }
            }
        }
        if (worstIdx != -1) 
		{
            allocation[i] = worstIdx;
            blockSize[worstIdx] -= processSize[i];
        }
    }
    printf("\nWorst Fit Allocation:\n");
    printf("Process No.\tProcess Size\tBlock No.\n");
    for (int i = 0; i < n; i++) {
        printf("%d\t\t%d\t\t", i + 1, processSize[i]);
        if (allocation[i] != -1)
            printf("%d\n", allocation[i] + 1);
        else
            printf("Not Allocated\n");
    }
}
int main() 
{
    int m, n;
    printf("Enter number of memory blocks: ");
    scanf("%d", &m);
    int blockSize[m], blockCopy1[m], blockCopy2[m], blockCopy3[m];
    printf("Enter sizes of blocks: ");
    for (int i = 0; i < m; i++) 
	{
        scanf("%d", &blockSize[i]);
        blockCopy1[i] = blockCopy2[i] = blockCopy3[i] = blockSize[i];
    }
    printf("Enter number of processes: ");
    scanf("%d", &n);
    int processSize[n];
    printf("Enter sizes of processes: ");
    for (int i = 0; i < n; i++) {
        scanf("%d", &processSize[i]);
    }
    firstFit(blockCopy1, m, processSize, n);
    bestFit(blockCopy2, m, processSize, n);
    worstFit(blockCopy3, m, processSize, n);
    return 0;
}
