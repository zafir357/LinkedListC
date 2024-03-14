#ifndef AGENDA_H
#define AGENDA_H

// Save the agenda to a file
#define MAX_FILENAME_LENGTH 50


// Define the structure for an event
typedef struct {
    char date[11];       // Date of the event (format: YYYY-MM-DD)
    char time[6];        // Time of the event (format: HH:MM)
    char comment[100];   // Comment or description of the event
} Event;

// Define the structure for a node in the linked list
typedef struct Node {
    Event event;         // Event associated with the node
    struct Node* next;   // Pointer to the next node in the linked list
} Node;

// Function prototypes

/**
 * @brief Display the menu options for the agenda program.
 */
void displayMenu();

/**
 * @brief Add an event to the agenda.
 * 
 * @param head Pointer to the head of the linked list.
 * @return Pointer to the head of the linked list after adding the event.
 */
Node* addEvent(Node* head);

/**
 * @brief Delete an event from the agenda.
 * 
 * @param head Pointer to the head of the linked list.
 * @return Pointer to the head of the linked list after deleting the event.
 */
Node* deleteEvent(Node* head);

/**
 * @brief Save the agenda to a file.
 * 
 * @param head Pointer to the head of the linked list.
 */
void saveAgenda(Node* head);

/**
 * @brief Load the agenda from a file.
 * 
 * @return Pointer to the head of the linked list loaded from the file.
 */
Node* loadAgenda();

/**
 * @brief Display the events in the agenda.
 * 
 * @param head Pointer to the head of the linked list.
 */
void displayAgenda(Node* head);

/**
 * @brief Free the memory allocated for the agenda.
 * 
 * @param head Pointer to the head of the linked list.
 */
void freeAgenda(Node* head);

#endif  // AGENDA_H

