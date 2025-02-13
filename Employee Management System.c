#include <stdio.h>
#include <stdlib.h>
#include <string.h> // Include string.h for strcpy

// Structure to represent an employee
struct Employee {
    int empId;
    char empName[50];
    float empSalary;
    struct Employee* next;
    struct Employee* prev;
};

// Function to create a new employee node
struct Employee* createEmployee(int id, const char* name, float salary) {
    struct Employee* newEmployee = (struct Employee*)malloc(sizeof(struct Employee));
    if (!newEmployee) {
        printf("Memory allocation failed\n");
        return NULL;
    }
    newEmployee->empId = id;
    strcpy(newEmployee->empName, name);
    newEmployee->empSalary = salary;
    newEmployee->next = NULL;
    newEmployee->prev = NULL;
    return newEmployee;
}

// Function to add an employee to the linked list
void addEmployee(struct Employee** head, struct Employee* newEmployee) {
    if (*head == NULL) {
        *head = newEmployee;
    } else {
        struct Employee* current = *head;
        while (current->next != NULL) {
            current = current->next;
        }
        current->next = newEmployee;
        newEmployee->prev = current;
    }
}

// Function to remove an employee by ID
void removeEmployee(struct Employee** head, int id) {
    struct Employee* current = *head;
    while (current != NULL) {
        if (current->empId == id) {
            if (current->prev != NULL) {
                current->prev->next = current->next;
            }
            if (current->next != NULL) {
                current->next->prev = current->prev;
            }
            if (current == *head) {
                *head = current->next;
            }
            free(current);
            printf("Employee with ID %d removed successfully.\n", id);
            return;
        }
        current = current->next;
    }
    printf("Employee with ID %d not found.\n", id);
}

// Function to search for an employee by ID
struct Employee* searchEmployee(struct Employee* head, int id) {
    struct Employee* current = head;
    while (current != NULL) {
        if (current->empId == id) {
            return current;
        }
        current = current->next;
    }
    return NULL;
}

// Function to display all employees
void displayEmployees(struct Employee* head) {
    struct Employee* current = head;
    if (current == NULL) {
        printf("No employees found.\n");
        return;
    }
    while (current != NULL) {
        printf("ID: %d, Name: %s, Salary: %.2f\n", current->empId, current->empName, current->empSalary);
        current = current->next;
    }
}

// Function to compute the total salary of all employees
float computeTotalSalary(struct Employee* head) {
    float totalSalary = 0.0;
    struct Employee* current = head;
    while (current != NULL) {
        totalSalary += current->empSalary;
        current = current->next;
    }
    return totalSalary;
}

int main() {
    struct Employee* head = NULL;
    int choice, empId;
    
    while (1) {
        printf("\nEmployee Management System\n");
        printf("1. Add Employee\n");
        printf("2. Remove Employee\n");
        printf("3. Search Employee\n");
        printf("4. Display Employees\n"); 
        printf("5. Compute Total Salary\n");
        printf("6. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);
        
        switch (choice) {
            case 1: {
                int id;
                char name[50];
                float salary;
                printf("Enter Employee ID: ");
                scanf("%d", &id);
                printf("Enter Employee Name: ");
                scanf("%s", name); // Remove '&' before name
                printf("Enter Employee Salary: ");
                scanf("%f", &salary);
                struct Employee* newEmployee = createEmployee(id, name, salary);
                if (newEmployee)
                    addEmployee(&head, newEmployee);
                break;
            }
            case 2:
                printf("Enter Employee ID to remove: ");
                scanf("%d", &empId);
                removeEmployee(&head, empId);
                break;
            case 3:
                printf("Enter Employee ID to search: ");
                scanf("%d", &empId);
                struct Employee* emp = searchEmployee(head, empId);
                if (emp != NULL) {
                    printf("ID: %d, Name: %s, Salary: %.2f\n", emp->empId, emp->empName, emp->empSalary);
                } else {
                    printf("Employee not found.\n");
                }
                break;
            case 4:
                displayEmployees(head);
                break;            
            case 5:
                printf("Total Salary: %.2f\n", computeTotalSalary(head));
                break;
            case 6:
                printf("Exiting program...\n");
                exit(0);
            default:
                printf("Invalid choice. Please try again.\n");
        }
    }
    
    return 0;
}


