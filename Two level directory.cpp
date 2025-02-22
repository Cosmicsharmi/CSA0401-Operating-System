#include <stdio.h>
#include <string.h>
#define MAX_USERS 5
#define MAX_FILES 10
#define MAX_NAME_LEN 50
typedef struct 
{
    char files[MAX_FILES][MAX_NAME_LEN];
    int fileCount;
} Directory;
typedef struct 
{
    char name[MAX_NAME_LEN];
    Directory dir;
} User;
User users[MAX_USERS];
int userCount = 0;
int findUser(const char *name) 
{
    for (int i = 0; i < userCount; i++)
        if (strcmp(users[i].name, name) == 0) return i;
    return -1;
}
void createUser(const char *name) 
{
    if (userCount < MAX_USERS) 
	{
        strcpy(users[userCount].name, name);
        users[userCount].dir.fileCount = 0;
        userCount++;
        printf("User '%s' created.\n", name);
    } 
	else
	{
        printf("User limit reached.\n");
    }
}
void addFile(int userIdx, const char *file) 
{
    Directory *d = &users[userIdx].dir;
    if (d->fileCount < MAX_FILES) 
	{
        strcpy(d->files[d->fileCount++], file);
        printf("File '%s' added to %s.\n", file, users[userIdx].name);
    } 
	else 
	{
        printf("Directory full.\n");
    }
}
void removeFile(int userIdx, const char *file) 
{
    Directory *d = &users[userIdx].dir;
    for (int i = 0; i < d->fileCount; i++) 
	{
        if (strcmp(d->files[i], file) == 0) 
		{
            for (int j = i; j < d->fileCount - 1; j++)
                strcpy(d->files[j], d->files[j + 1]);
            d->fileCount--;
            printf("File '%s' removed from %s.\n", file, users[userIdx].name);
            return;
        }
    }
    printf("File not found.\n");
}
void listFiles(int userIdx) 
{
    Directory *d = &users[userIdx].dir;
    printf("Files in %s's directory:\n", users[userIdx].name);
    if (d->fileCount == 0) printf("No files.\n");
    for (int i = 0; i < d->fileCount; i++)
        printf("%d. %s\n", i + 1, d->files[i]);
}
int main() 
{
    char name[MAX_NAME_LEN], file[MAX_NAME_LEN];
    int choice, userIdx;
    while (1) 
	{
        printf("\n1. Create User\n2. Add File\n3. Remove File\n4. List Files\n5. Exit\nChoice: ");
        scanf("%d", &choice);
        getchar();  
        if (choice == 5) break;
        printf("Enter username: ");
        fgets(name, sizeof(name), stdin);
        name[strcspn(name, "\n")] = '\0';
        userIdx = findUser(name);
        if (choice == 1) 
		{
            if (userIdx == -1) createUser(name);
            else printf("User already exists.\n");
        } 
		else if (userIdx != -1) 
		{
            if (choice == 2) {
                printf("Enter file name: ");
                fgets(file, sizeof(file), stdin);
                file[strcspn(file, "\n")] = '\0';
                addFile(userIdx, file);
            } 
			else if (choice == 3) 
			{
                printf("Enter file name: ");
                fgets(file, sizeof(file), stdin);
                file[strcspn(file, "\n")] = '\0';
                removeFile(userIdx, file);
            } 
			else if (choice == 4) 
			{
                listFiles(userIdx);
            } 
			else 
			{
                printf("Invalid choice.\n");
            }
        } 
		else 
		{
            printf("User not found.\n");
        }
    }
    return 0;
}