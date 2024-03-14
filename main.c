#include "agenda.h"   // Include the header file for the agenda functions
#include <stdio.h>     // Include this line to resolve the undeclared identifier issues
#include <stddef.h>    // Include this line to use NULL

int main() {
    Node* agenda = NULL;  // Initialize the agenda as an empty linked list
    int choice;           // Variable to store user's menu choice
    char filename[50];    // Array to store the filename for loading/saving

    // Display the menu and process user input until the user chooses to exit
    do {
        displayMenu();  // Display the menu options
        printf("Enter your choice: ");
        if (scanf("%d", &choice) != 1) {//returns 1 only if input is an integer
        // Clear input buffer in case of invalid input
        //verify if input is not a number
        while (getchar() != '\n');
        printf("Invalid input. Please enter a number.\n");
        continue;  // Skip to next iteration of the loop
        }
        // Perform actions based on user's choice
        switch (choice) {
            case 1:
                // Add an event to the agenda
                agenda = addEvent(agenda);
                break;
            case 2:
                // Delete an event from the agenda
                agenda = deleteEvent(agenda);
                break;
            case 3:
                // Save the agenda to a file
                saveAgenda(agenda);
                break;
            case 4:
                // Load agenda from a file
                printf("Enter the filename to load the agenda: ");
                scanf("%s", filename);    
                agenda = loadAgenda(filename, agenda);
                break;
            case 5:
                // Display the agenda
                displayAgenda(agenda);
                break;
            case 6:
                // Free the memory allocated for the agenda
                freeAgenda(agenda);
                break;
            case 7:
                // Exit the program
                printf("Exiting the agenda. Goodbye!\n");
                break;
            default:
                // Invalid choice
                printf("Invalid choice. Please try again.\n");
        }
    } while (choice != 7);  // Continue until the user chooses to exit

    return 0;  // Return 0 to indicate successful program execution
}

