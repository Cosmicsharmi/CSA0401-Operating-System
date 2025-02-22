#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define FILE_NAME "employee.dat"
typedef struct 
{
    int id;
    char name[50];
    float salary;
} Employee;
void addEmployee() 
{
    FILE *file = fopen(FILE_NAME, "ab");
    if (!file) 
	{
        printf("Error opening file!\n");
        return;
    }
    Employee emp;
    printf("Enter Employee ID: ");
    scanf("%d", &emp.id);
    getchar();
    printf("Enter Employee Name: ");
    fgets(emp.name, sizeof(emp.name), stdin);
    emp.name[strcspn(emp.name, "\n")] = '\0';
    printf("Enter Salary: ");
    scanf("%f", &emp.salary);
    fwrite(&emp, sizeof(Employee), 1, file);
    fclose(file);
    printf("Employee record added successfully!\n");
}
void displayEmployees() 
{
    FILE *file = fopen(FILE_NAME, "rb");
    if (!file) 
	{
        printf("No employee records found.\n");
        return;
    }
    Employee emp;
    printf("\nEmployee Details:\n");
    while (fread(&emp, sizeof(Employee), 1, file)) 
	{
        printf("ID: %d, Name: %s, Salary: %.2f\n", emp.id, emp.name, emp.salary);
    }
    fclose(file);
}
void searchEmployee() 
{
    FILE *file = fopen(FILE_NAME, "rb");
    if (!file) 
	{
        printf("No employee records found.\n");
        return;
    }
    int id;
    printf("Enter Employee ID to search: ");
    scanf("%d", &id);
    Employee emp;
    while (fread(&emp, sizeof(Employee), 1, file)) 
	{
        if (emp.id == id) 
		{
            printf("Employee Found - ID: %d, Name: %s, Salary: %.2f\n", emp.id, emp.name, emp.salary);
            fclose(file);
            return;
        }
    }
    printf("Employee not found.\n");
    fclose(file);
}
void updateEmployee() 
{
    FILE *file = fopen(FILE_NAME, "r+b");
    if (!file) 
	{
        printf("No employee records found.\n");
        return;
    }
    int id;
    printf("Enter Employee ID to update: ");
    scanf("%d", &id);
    getchar();
    Employee emp;
    while (fread(&emp, sizeof(Employee), 1, file)) 
	{
        if (emp.id == id) 
		{
            printf("Enter New Name: ");
            fgets(emp.name, sizeof(emp.name), stdin);
            emp.name[strcspn(emp.name, "\n")] = '\0';
            printf("Enter New Salary: ");
            scanf("%f", &emp.salary);
            fseek(file, -sizeof(Employee), SEEK_CUR);
            fwrite(&emp, sizeof(Employee), 1, file);
            fclose(file);
            printf("Employee record updated successfully!\n");
            return;
        }
    }
    printf("Employee not found.\n");
    fclose(file);
}
int main() 
{
    int choice;
    while (1) 
	{
        printf("\nEmployee Management System:\n");
        printf("1. Add Employee\n");
        printf("2. Display Employees\n");
        printf("3. Search Employee\n");
        printf("4. Update Employee\n");
        printf("5. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);
        getchar();
        switch (choice) 
		{
            case 1: addEmployee(); break;
            case 2: displayEmployees(); break;
            case 3: searchEmployee(); break;
            case 4: updateEmployee(); break;
            case 5: printf("Exiting...\n"); return 0;
            default: printf("Invalid choice, try again.\n");
        }
    }
}
