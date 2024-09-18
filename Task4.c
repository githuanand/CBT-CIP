#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_EXPENSES 100
#define CATEGORY_LENGTH 50
#define DESCRIPTION_LENGTH 100

// Structure to represent an expense
typedef struct {
    char category[CATEGORY_LENGTH];
    char description[DESCRIPTION_LENGTH];
    float amount;
} Expense;

// Array to store expenses and count of expenses
Expense expenses[MAX_EXPENSES];
int expenseCount = 0;

/*
 * Function to add a new expense
 */
void addExpense() {
    if (expenseCount >= MAX_EXPENSES) {
        printf("Expense limit reached. Cannot add more expenses.\n");
        return;
    }

    Expense newExpense;
    printf("Enter expense category: ");
    scanf(" %[^\n]", newExpense.category); // Read string with spaces
    printf("Enter expense description: ");
    scanf(" %[^\n]", newExpense.description); // Read string with spaces
    printf("Enter expense amount: ");
    scanf("%f", &newExpense.amount);

    expenses[expenseCount++] = newExpense;
    printf("Expense added successfully.\n");
}

/*
 * Function to generate a summary report of expenses
 */
void generateReport() {
    float totalAmount = 0.0;

    printf("\nExpense Summary Report:\n");
    for (int i = 0; i < expenseCount; i++) {
        totalAmount += expenses[i].amount;
        printf("Category: %s\n", expenses[i].category);
        printf("Description: %s\n", expenses[i].description);
        printf("Amount: %.2f\n\n", expenses[i].amount);
    }
    printf("Total Expenses: %.2f\n", totalAmount);
}

/*
 * Function to display expenses by category
 */
void displayByCategory() {
    char category[CATEGORY_LENGTH];
    float totalCategoryAmount = 0.0;

    printf("Enter category to filter: ");
    scanf(" %[^\n]", category);

    printf("\nExpenses in category '%s':\n", category);
    for (int i = 0; i < expenseCount; i++) {
        if (strcmp(expenses[i].category, category) == 0) {
            totalCategoryAmount += expenses[i].amount;
            printf("Description: %s\n", expenses[i].description);
            printf("Amount: %.2f\n\n", expenses[i].amount);
        }
    }
    if (totalCategoryAmount > 0) {
        printf("Total for '%s': %.2f\n", category, totalCategoryAmount);
    } else {
        printf("No expenses found for this category.\n");
    }
}

/*
 * Main function to display menu and handle user choices
 */
int main() {
    int choice;

    while (1) {
        printf("\nExpense Tracker\n");
        printf("1. Add Expense\n");
        printf("2. Generate Report\n");
        printf("3. Display Expenses by Category\n");
        printf("4. Exit\n");
        printf("Enter your choice: ");
        
        // Validate input for menu choice
        if (scanf("%d", &choice) != 1) {
            // Handle invalid input
            printf("Invalid input. Please enter a number.\n");
            while (getchar() != '\n'); // Clear the input buffer
            continue;
        }

        // Handle user choices
        switch (choice) {
            case 1:
                addExpense();
                break;
            case 2:
                generateReport();
                break;
            case 3:
                displayByCategory();
                break;
            case 4:
                printf("Exiting...\n");
                exit(0);
            default:
                printf("Invalid choice. Please try again.\n");
        }
    }

    return 0;
}
