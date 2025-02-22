#include <stdio.h>
#include <string.h>
#define MAX_FILES 10
#define MAX_FILE_NAME 50
typedef struct 
{
    char files[MAX_FILES][MAX_FILE_NAME];
    int fileCount;
} Directory;
void initializeDirectory(Directory *dir)
{
    dir->fileCount = 0;
}
void addFile(Directory *dir, const char *fileName) 
{
    if (dir->fileCount < MAX_FILES) {
        strcpy(dir->files[dir->fileCount], fileName);
        dir->fileCount++;
        printf("File '%s' added to the directory.\n", fileName);
    } else {
        printf("Directory is full, cannot add more files.\n");
    }
}
void removeFile(Directory *dir, const char *fileName) 
{
    int i, j;
    for (i = 0; i < dir->fileCount; i++) {
        if (strcmp(dir->files[i], fileName) == 0) {
            for (j = i; j < dir->fileCount - 1; j++) {
                strcpy(dir->files[j], dir->files[j + 1]);
            }
            dir->fileCount--;
            printf("File '%s' removed from the directory.\n", fileName);
            return;
        }
    }
    printf("File '%s' not found in the directory.\n", fileName);
}
void listFiles(Directory *dir) 
{
    if (dir->fileCount == 0) 
	{
        printf("No files in the directory.\n");
        return;
    }
    printf("Files in the directory:\n");
    for (int i = 0; i < dir->fileCount; i++) 
	{
        printf("%d. %s\n", i + 1, dir->files[i]);
    }
}
int main() 
{
    Directory dir;
    int choice;
    char fileName[MAX_FILE_NAME];
    initializeDirectory(&dir);
    while (1) {
        printf("\nSingle Level Directory Operations:\n");
        printf("1. Add a file\n");
        printf("2. Remove a file\n");
        printf("3. List files\n");
        printf("4. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);
        getchar();
        switch (choice) 
		{
            case 1:
                printf("Enter file name to add: ");
                fgets(fileName, sizeof(fileName), stdin);
                fileName[strcspn(fileName, "\n")] = '\0';
                addFile(&dir, fileName);
                break;
            case 2:
                printf("Enter file name to remove: ");
                fgets(fileName, sizeof(fileName), stdin);
                fileName[strcspn(fileName, "\n")] = '\0';
                removeFile(&dir, fileName);
                break;
            case 3:
                listFiles(&dir);
                break;
            case 4:
                printf("Exiting...\n");
                return 0;
            default:
                printf("Invalid choice. Please try again.\n");
        }
    }
    return 0;
}
