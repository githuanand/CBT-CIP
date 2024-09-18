#include <stdio.h>
#include <string.h>

#define MAX_SUBJECTS 10
#define MAX_STUDENTS 100

// Define the structure for storing student information
typedef struct {
    char name[50];
    float scores[MAX_SUBJECTS];
    int numSubjects;
} Student;

// Define the structure for managing a list of students
typedef struct {
    Student students[MAX_STUDENTS];
    int numStudents;
} StudentList;

// Function to add a new student to the list
void addStudent(StudentList *list) {
    if (list->numStudents >= MAX_STUDENTS) {
        printf("Student list is full! Cannot add more students.\n");
        return;
    }

    Student *newStudent = &list->students[list->numStudents];
    printf("Enter student name: ");
    fgets(newStudent->name, sizeof(newStudent->name), stdin);
    newStudent->name[strcspn(newStudent->name, "\n")] = '\0'; // Remove newline character

    printf("Enter number of subjects (max %d): ", MAX_SUBJECTS);
    scanf("%d", &newStudent->numSubjects);
    while (getchar() != '\n'); // Clear the input buffer

    if (newStudent->numSubjects > MAX_SUBJECTS) {
        printf("Number of subjects exceeds the limit. Setting to %d.\n", MAX_SUBJECTS);
        newStudent->numSubjects = MAX_SUBJECTS;
    }

    for (int i = 0; i < newStudent->numSubjects; i++) {
        printf("Enter score for subject %d: ", i + 1);
        scanf("%f", &newStudent->scores[i]);
    }
    while (getchar() != '\n'); // Clear the input buffer

    list->numStudents++;
}

// Function to display a summary of all students' information
void displaySummary(StudentList *list) {
    if (list->numStudents == 0) {
        printf("No student data available to display.\n");
        return;
    }

    for (int i = 0; i < list->numStudents; i++) {
        Student *student = &list->students[i];
        printf("\nStudent Name: %s\n", student->name);
        printf("Scores:\n");
        for (int j = 0; j < student->numSubjects; j++) {
            printf("  Subject %d: %.2f\n", j + 1, student->scores[j]);
        }
    }
}

// Function to calculate and display the average score for each student
void calculateAverage(StudentList *list) {
    if (list->numStudents == 0) {
        printf("No student data available to calculate averages.\n");
        return;
    }

    for (int i = 0; i < list->numStudents; i++) {
        Student *student = &list->students[i];
        float sum = 0.0;
        for (int j = 0; j < student->numSubjects; j++) {
            sum += student->scores[j];
        }
        float average = student->numSubjects > 0 ? sum / student->numSubjects : 0;
        printf("\nStudent Name: %s\n", student->name);
        printf("Average Score: %.2f\n", average);
    }
}

// Function to find and display the highest and lowest scores for each student
void findHighestLowestScores(StudentList *list) {
    if (list->numStudents == 0) {
        printf("No student data available to determine highest and lowest scores.\n");
        return;
    }

    for (int i = 0; i < list->numStudents; i++) {
        Student *student = &list->students[i];
        float highest = student->scores[0];
        float lowest = student->scores[0];

        for (int j = 1; j < student->numSubjects; j++) {
            if (student->scores[j] > highest) {
                highest = student->scores[j];
            }
            if (student->scores[j] < lowest) {
                lowest = student->scores[j];
            }
        }

        printf("\nStudent Name: %s\n", student->name);
        printf("Highest Score: %.2f\n", highest);
        printf("Lowest Score: %.2f\n", lowest);
    }
}

// Main function to drive the application
int main() {
    StudentList list = { .numStudents = 0 };
    int choice;

    do {
        // Display menu options
        printf("\nStudent Grade Management System\n");
        printf("1. Add Student\n");
        printf("2. Display Summary\n");
        printf("3. Calculate Average Scores\n");
        printf("4. Find Highest and Lowest Scores\n");
        printf("5. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);
        while (getchar() != '\n'); // Clear the input buffer

        // Process user choice
        switch (choice) {
            case 1:
                addStudent(&list);
                break;
            case 2:
                displaySummary(&list);
                break;
            case 3:
                calculateAverage(&list);
                break;
            case 4:
                findHighestLowestScores(&list);
                break;
            case 5:
                printf("Exiting program.\n");
                break;
            default:
                printf("Invalid choice. Please enter a number between 1 and 5.\n");
                break;
        }
    } while (choice != 5);

    return 0;
}
