#include <stdio.h>
#include <stdlib.h>

// A node holds a value, the address of the next node, and the address of the previous node
struct Node {
    int data;
    struct Node *next;
    struct Node *prev;
};

// head holds the address of the first node. NULL means the list is empty
struct Node *head = NULL;

// ---------- INSERT ----------

void insertAtBeginning(int value) {
    struct Node *newNode = (struct Node *)malloc(sizeof(struct Node));  // ask memory for one node
    newNode->data = value;          // store the value in the new node
    newNode->prev = NULL;           // first node has nothing before it
    newNode->next = head;           // new node points forward to the old first node

    if (head != NULL) {             // only if the list was not empty
        head->prev = newNode;       // old first node points back to the new node
    }
    head = newNode;                 // head now points to the new node
}

void insertAtEnd(int value) {
    struct Node *newNode = (struct Node *)malloc(sizeof(struct Node));
    newNode->data = value;
    newNode->next = NULL;           // this will be the last node, so nothing comes after it

    if (head == NULL) {             // empty list: the new node becomes the first node
        newNode->prev = NULL;
        head = newNode;
        return;
    }

    struct Node *temp = head;       // temp walks the list, so head never moves
    while (temp->next != NULL) {
        temp = temp->next;          // keep moving until temp is the last node
    }
    temp->next = newNode;           // last node points forward to the new node
    newNode->prev = temp;           // new node points back to the old last node
}

void insertAtPosition(int value, int position) {
    if (position == 1) {                // position 1 is the same as inserting at the beginning
        insertAtBeginning(value);
        return;
    }

    struct Node *temp = head;
    for (int count = 1; count < position - 1 && temp != NULL; count++) {
        temp = temp->next;              // walk to the node just BEFORE the position
    }

    if (temp == NULL) {                 // the list is shorter than the position
        printf("Position out of range\n");
        return;
    }

    struct Node *newNode = (struct Node *)malloc(sizeof(struct Node));
    newNode->data = value;
    newNode->next = temp->next;         // new node points forward to the node after temp
    newNode->prev = temp;               // new node points back to temp

    if (temp->next != NULL) {           // only if there is a node after temp
        temp->next->prev = newNode;     // that node points back to the new node
    }
    temp->next = newNode;               // temp points forward to the new node
}

// ---------- DELETE ----------

void deleteFirst() {
    if (head == NULL) {                 // nothing to delete
        printf("List is empty\n");
        return;
    }
    struct Node *temp = head;           // save the first node so we can free it
    head = head->next;                  // head moves to the second node

    if (head != NULL) {                 // only if there is a second node
        head->prev = NULL;              // new first node has nothing before it
    }
    free(temp);                         // give the old first node's memory back
}

void deleteLast() {
    if (head == NULL) {
        printf("List is empty\n");
        return;
    }
    if (head->next == NULL) {           // only one node in the list
        free(head);
        head = NULL;                    // list is now empty
        return;
    }

    struct Node *temp = head;
    while (temp->next != NULL) {
        temp = temp->next;              // walk to the last node
    }
    temp->prev->next = NULL;            // second-last node becomes the last node
    free(temp);                         // delete the old last node
}

void deleteAtPosition(int position) {
    if (head == NULL) {
        printf("List is empty\n");
        return;
    }
    if (position == 1) {                // position 1 is the same as deleting the first node
        deleteFirst();
        return;
    }

    struct Node *temp = head;
    for (int count = 1; count < position && temp != NULL; count++) {
        temp = temp->next;              // walk directly to the node to delete
    }

    if (temp == NULL) {                 // there is no node at that position
        printf("Position out of range\n");
        return;
    }

    temp->prev->next = temp->next;      // the node before temp skips over temp
    if (temp->next != NULL) {           // only if there is a node after temp
        temp->next->prev = temp->prev;  // the node after temp skips back over temp
    }
    free(temp);                         // give its memory back
}

// ---------- DISPLAY ----------

void display() {
    if (head == NULL) {
        printf("List is empty\n");
        return;
    }
    struct Node *temp = head;           // start at the first node
    while (temp != NULL) {
        printf("%d <-> ", temp->data);  // print the current node's value
        temp = temp->next;              // move to the next node
    }
    printf("NULL\n");                   // end of the list
}

// ---------- MAIN ----------

int main() {
    int choice, value, position;

    while (1) {                         // loop forever, so the menu keeps coming back
        printf("\n1.Insert Beginning  2.Insert End  3.Insert Position\n");
        printf("4.Delete First      5.Delete Last 6.Delete Position\n");
        printf("7.Display           8.Exit\n");
        printf("Enter choice: ");
        scanf("%d", &choice);           // read the user's choice

        switch (choice) {               // jump to the matching case
            case 1:
                printf("Enter value: ");
                scanf("%d", &value);
                insertAtBeginning(value);
                break;
            case 2:
                printf("Enter value: ");
                scanf("%d", &value);
                insertAtEnd(value);
                break;
            case 3:
                printf("Enter value and position: ");
                scanf("%d %d", &value, &position);
                insertAtPosition(value, position);
                break;
            case 4:
                deleteFirst();
                break;
            case 5:
                deleteLast();
                break;
            case 6:
                printf("Enter position: ");
                scanf("%d", &position);
                deleteAtPosition(position);
                break;
            case 7:
                display();
                break;
            case 8:
                exit(0);                // the only way out of the infinite loop
            default:
                printf("Invalid choice\n");
        }
    }
    return 0;
}
