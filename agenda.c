#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "agenda.h"
#include <stdbool.h> // Include this line to use boolean data type

// Display the menu options
void displayMenu() {
    printf("\nMenu:\n");
    printf("1. Add an event\n");
    printf("2. Delete an event\n");
    printf("3. Save agenda\n");
    printf("4. Load agenda\n");
    printf("5. Display agenda\n");
    printf("6. Free agenda (delete all events)\n");
    printf("7. Quit\n");
}

// Function to check if a date is valid
int isValidDate(const char* date) {
  
    if (strlen(date) != 10) {
        return 0; // Invalid length
    }

    // Validate the format (YYYY-MM-DD)
    if (date[4] != '-' || date[7] != '-') {
        return 0; // Invalid format
    }

    // Validate the range of each component (year, month, day)
    int year, month, day;
    if (sscanf(date, "%4d-%2d-%2d", &year, &month, &day) != 3) {
        return 0; // Invalid components
    }

    if (year < 1000 || month < 1 || month > 12 || day < 1 || day > 31) {
        return 0; // Invalid range
    }

    return 1; // Valid date
}

// Function to check if a time is valid
int isValidTime(const char* time) {
  
    if (strlen(time) != 5) {
        return 0; // Invalid length
    }

    // Validate the format (HH:MM)
    if (time[2] != ':') {
        return 0; // Invalid format
    }

    // Validate the range of each component (hour, minute)
    int hour, minute;
    if (sscanf(time, "%2d:%2d", &hour, &minute) != 2) {
        return 0; // Invalid components
    }

    if (hour < 0 || hour > 23 || minute < 0 || minute > 59) {
        return 0; // Invalid range
    }

    return 1; // Valid time
}

// Function to compare two events based on date and time
int compareEvents(const Event event1, const Event event2) {
  
    int dateComparison = strcmp(event1.date, event2.date);

    if (dateComparison != 0) {
        return dateComparison; // Different dates, no need to check time
    }

    return strcmp(event1.time, event2.time); // Same date, compare based on time
}

// Add an event to the agenda with basic validation
Node* addEvent(Node* head) {
    // Allocate memory for a new node
    Node* newNode = (Node*)malloc(sizeof(Node));

    // Prompt the user to enter date (YYYY-MM-DD)
    printf("Enter date (YYYY-MM-DD): ");
    if (scanf("%10s", newNode->event.date) != 1 || !isValidDate(newNode->event.date)) {
        printf("Invalid date format. Event not added.\n");
        free(newNode); // Free the allocated memory
        return head;   // Return the original list
    }

    // Prompt the user to enter time (HH:MM)
    printf("Enter time (HH:MM): ");
    if (scanf("%5s", newNode->event.time) != 1 || !isValidTime(newNode->event.time)) {
        printf("Invalid time format. Event not added.\n");
        free(newNode); // Free the allocated memory
        return head;   // Return the original list
    }

    // Prompt the user to enter comment
    printf("Enter comment: ");
    getchar(); // Consume the newline character from previous input
    fgets(newNode->event.comment, sizeof(newNode->event.comment), stdin);

    // Remove trailing newline character from comment, if present
    size_t len = strlen(newNode->event.comment);
    if (len > 0 && newNode->event.comment[len - 1] == '\n') {
        newNode->event.comment[len - 1] = '\0';
    }

    // Validate date and time ranges
    if (!isValidDate(newNode->event.date) || !isValidTime(newNode->event.time)) {
        printf("Invalid date or time. Event not added.\n");
        free(newNode); // Free the allocated memory
        return head;   // Return the original list
    }

    // Set the next pointer of the new node to NULL
    newNode->next = NULL;

    // Insert the event in sorted order based on date and time

    // Case 1: Insert at the beginning if the list is empty
    // or the new event is earlier than the first event
    if (head == NULL || compareEvents(newNode->event, head->event) < 0) {
        newNode->next = head;
        printf("Event added successfully.\n");
        return newNode;
    }

    // Case 2: Insert in the middle or at the end of the list
    Node* current = head;
    while (current->next != NULL && compareEvents(newNode->event, current->next->event) > 0) {
        current = current->next;
    }

    // Insert the new node into the list
    newNode->next = current->next;
    current->next = newNode;

    // Print a success message
    printf("Event added successfully.\n");

    // Return the head of the updated list
    return head;
}


// Delete an event from the agenda with validation
Node* deleteEvent(Node* head) {
    // Check if the agenda is empty
    if (head == NULL) {
        printf("Agenda is empty.\n");
        return NULL;
    }

    // Variables to store user input for event to delete
    char deleteDate[11];
    char deleteTime[6];

    // Prompt the user to enter date (YYYY-MM-DD) of the event to delete
    printf("Enter date (YYYY-MM-DD) of the event to delete: ");
    if (scanf("%10s", deleteDate) != 1 || !isValidDate(deleteDate)) {
        printf("Invalid date format. Event not deleted.\n");
        return head; // Return the original list
    }

    // Prompt the user to enter time (HH:MM) of the event to delete
    printf("Enter time (HH:MM) of the event to delete: ");
    if (scanf("%5s", deleteTime) != 1 || !isValidTime(deleteTime)) {
        printf("Invalid time format. Event not deleted.\n");
        return head; // Return the original list
    }

    // Initialize pointers for traversing the list
    Node* current = head;
    Node* prev = NULL;

    // Traverse the list to find the event to delete
    while (current != NULL &&
           (strcmp(deleteDate, current->event.date) != 0 ||
            strcmp(deleteTime, current->event.time) != 0)) {
        prev = current;
        current = current->next;
    }

    // Check if the event to delete was not found
    if (current == NULL) {
        printf("Event not found.\n");
        return head;
    }

    // Remove the event from the list
    if (prev == NULL) {
        // Case 1: Deleting the first node in the list
        head = current->next;
    } else {
        // Case 2: Deleting a node from the middle or end of the list
        prev->next = current->next;
    }

    // Print a success message
    printf("Event deleted successfully.\n");

    // Free the memory allocated for the deleted node
    free(current);

    // Return the updated head of the list
    return head;
}

// Save the agenda to a file with validation
void saveAgenda(Node* head) {
    // Check if the agenda is empty
    if (head == NULL) {
        printf("Agenda is empty. Nothing to save.\n");
        return;
    }

    // Variable to store the filename entered by the user
    char filename[50];

    // Prompt the user to enter the filename to save the agenda
    printf("Enter the filename to save the agenda: ");
    if (scanf("%49s", filename) != 1) {
        printf("Invalid filename. Agenda not saved.\n");
        return;
    }

    // Open the file for writing
    FILE* file = fopen(filename, "w");

    // Check if the file opening was successful
    if (file == NULL) {
        printf("Error opening the file for writing.\n");
        return;
    }

    // Initialize a pointer for traversing the list
    Node* current = head;

    // Traverse the list and write each event to the file
    while (current != NULL) {
        // Use fprintf to write formatted data to the file
        fprintf(file, "%s %s %s\n", current->event.date, current->event.time, current->event.comment);
        current = current->next;
    }

    // Close the file after writing
    fclose(file);

    // Print a success message
    printf("Agenda saved successfully.\n");
}

// Load agenda from a file into a linked list with validation
Node* loadAgenda(const char* filename, Node* head) {
    // Open the file for reading
    FILE* file = fopen(filename, "r");

    // Check if the file opening was unsuccessful
    if (file == NULL) {
        printf("Error opening the file for reading.\n");
        return head;  // Do not modify the existing agenda
    }

    Event tempEvent;
    Node* tempHead = NULL;  // Temporary head for storing loaded events

    // Read events from the file until the end is reached
    while (fscanf(file, "%s %s", tempEvent.date, tempEvent.time) == 2) {
        // Adjust the size for fgets, including space for null terminator
        if (fgets(tempEvent.comment, sizeof(tempEvent.comment), file) == NULL) {
            printf("Error reading comment from the file.\n");
            fclose(file);
            freeAgenda(head);  // Free previously allocated nodes
            freeAgenda(tempHead);  // Free temporary nodes
            return NULL;
        }

        // Remove trailing newline character, if present
        size_t len = strlen(tempEvent.comment);
        if (len > 0 && tempEvent.comment[len - 1] == '\n') {
            tempEvent.comment[len - 1] = '\0';
        }

        // Allocate memory for the loaded event
        Node* newNode = (Node*)malloc(sizeof(Node));
        if (newNode == NULL) {
            printf("Memory allocation error.\n");
            fclose(file);
            freeAgenda(head);  // Free previously allocated nodes
            freeAgenda(tempHead);  // Free temporary nodes
            return NULL;
        }

        // Assign the loaded event to the new node
        newNode->event = tempEvent;
        newNode->next = NULL;

        // Add the loaded event to the temporary list
        if (tempHead == NULL) {
            tempHead = newNode;
        } else {
            Node* tempCurrent = tempHead;
            while (tempCurrent->next != NULL) {
                tempCurrent = tempCurrent->next;
            }
            tempCurrent->next = newNode;
        }

        // Print a message indicating the successful loading of an event
        printf("Loaded: %s %s %s\n", newNode->event.date, newNode->event.time, newNode->event.comment);
    }

    // Check for errors during file reading
    if (ferror(file)) {
        printf("Error reading from the file.\n");
        fclose(file);
        freeAgenda(head);  // Free previously allocated nodes
        freeAgenda(tempHead);  // Free temporary nodes
        return NULL;
    }

    // Close the file after reading
    fclose(file);

    // Merge the temporary list into the main list
    if (tempHead != NULL) {
        Node* tempCurrent = tempHead;
        while (tempCurrent->next != NULL) {
            tempCurrent = tempCurrent->next;
        }
        tempCurrent->next = head;
        head = tempHead;
    } else {
        freeAgenda(tempHead);  // Free only if not merged
    }

    // Print a success message
    printf("Agenda loaded successfully.\n");

    // Return the head of the updated linked list
    return head;
}


// Check if the linked list is sorted based on date and time
bool isSorted(Node* head) {
    if (head == NULL || head->next == NULL) {
        return true;  // An empty list or a single-node list is considered sorted
    }

    Node* current = head;
    while (current->next != NULL) {
        // Compare the current event with the next event
        if (strcmp(current->event.date, current->next->event.date) > 0 ||
            (strcmp(current->event.date, current->next->event.date) == 0 &&
             strcmp(current->event.time, current->next->event.time) > 0)) {
            return false;  // The list is not sorted
        }
        current = current->next;
    }

    return true;  // The list is sorted
}

// Sort the linked list based on date and time
Node* sortAgenda(Node* head) {
    if (head == NULL || head->next == NULL) {
        return head;  // An empty list or a single-node list is already sorted
    }

    Node* sortedList = NULL;

    while (head != NULL) {
        Node* current = head;
        head = head->next;

        // Insert the current node into the sorted list
        if (sortedList == NULL || strcmp(current->event.date, sortedList->event.date) < 0 ||
            (strcmp(current->event.date, sortedList->event.date) == 0 &&
             strcmp(current->event.time, sortedList->event.time) < 0)) {
            current->next = sortedList;
            sortedList = current;
        } else {
            Node* temp = sortedList;
            while (temp->next != NULL &&
                   (strcmp(current->event.date, temp->next->event.date) > 0 ||
                    (strcmp(current->event.date, temp->next->event.date) == 0 &&
                     strcmp(current->event.time, temp->next->event.time) > 0))) {
                temp = temp->next;
            }
            current->next = temp->next;
            temp->next = current;
        }
    }

    return sortedList;
}

// Display the agenda, ensuring it is sorted before displaying
void displayAgenda(Node* head) {
    // Check if the agenda is empty
    if (head == NULL) {
        printf("Agenda is empty.\n");
        return;
    }

    // Check if the agenda is sorted; if not, sort it
    if (!isSorted(head)) {
        printf("Sorting agenda...\n");
        head = sortAgenda(head);
    }

    // Print the header for the agenda
    printf("\nAgenda:\n");
    printf("Date       Time  Comment\n");
    printf("---------- ----- ----------------------------------------\n");

    // Initialize a pointer for traversing the list
    Node* current = head;

    // Traverse the list and print each event
    while (current != NULL) {
        // Print the date, time, and comment for the current event
        printf("%s %s %s\n", current->event.date, current->event.time, current->event.comment);
        
        // Move to the next node in the list
        current = current->next;
    }

    // Print an extra newline for better formatting
    printf("\n");
}



// Free the memory allocated for the agenda with validation
void freeAgenda(Node* head) {
    // Check if the agenda is already empty
    if (head == NULL) {
        printf("Agenda is already empty. No memory to free.\n");
        return;
    }

    // Initialize pointers for traversing the list
    Node* current = head;
    Node* nextNode;

    // Traverse the list and free memory for each node
    while (current != NULL) {
        // Save the next node's address before freeing the current node
        nextNode = current->next;

        // Free the memory allocated for the current node
        free(current);

        // Move to the next node in the list
        current = nextNode;
    }

    // Print a message indicating successful freeing of memory
    printf("Agenda freed. All events deleted.\n");
}

