#include <stdio.h>
#include <stdlib.h>

struct Node {
    int data;
    struct Node *next;
    struct Node *prev;
};

struct Node *head = NULL;

// ---------- INSERT ----------

void insertAtBeginning(int value) {
    struct Node *newNode = (struct Node *)malloc(sizeof(struct Node));
    newNode->data = value;
    newNode->prev = NULL;           // first node has nothing before it
    newNode->next = head;           // new node points forward to the old first node

    if (head != NULL) {
        head->prev = newNode;       // old first node points back to the new node
    }
    head = newNode;                 // head now points to the new node
}

void insertAtEnd(int value) {
    struct Node *newNode = (struct Node *)malloc(sizeof(struct Node));
    newNode->data = value;
    newNode->next = NULL;

    if (head == NULL) {             // empty list
        newNode->prev = NULL;
        head = newNode;
        return;
    }

    struct Node *temp = head;
    while (temp->next != NULL) {
        temp = temp->next;          // walk to the last node
    }
    temp->next = newNode;           // last node points forward to the new node
    newNode->prev = temp;           // new node points back to the old last node
}

void insertAtPosition(int value, int position) {
    if (position == 1) {
        insertAtBeginning(value);
        return;
    }

    struct Node *temp = head;
    for (int count = 1; count < position - 1 && temp != NULL; count++) {
        temp = temp->next;          // walk to the node before the position
    }

    if (temp == NULL) {
        printf("Position out of range\n");
        return;
    }

    struct Node *newNode = (struct Node *)malloc(sizeof(struct Node));
    newNode->data = value;
    newNode->next = temp->next;     // new node points forward to the next node
    newNode->prev = temp;           // new node points back to temp

    if (temp->next != NULL) {
        temp->next->prev = newNode; // the next node points back to the new node
    }
    temp->next = newNode;           // temp points forward to the new node
}

// ---------- DELETE ----------

void deleteFirst() {
    if (head == NULL) {
        printf("List is empty\n");
        return;
    }
    struct Node *temp = head;       // save the first node
    head = head->next;              // head moves to the second node

    if (head != NULL) {
        head->prev = NULL;          // new first node has nothing before it
    }
    free(temp);
}

void deleteLast() {
    if (head == NULL) {
        printf("List is empty\n");
        return;
    }
    if (head->next == NULL) {       // only one node
        free(head);
        head = NULL;
        return;
    }

    struct Node *temp = head;
    while (temp->next != NULL) {
        temp = temp->next;          // walk to the last node
    }
    temp->prev->next = NULL;        // second-last node becomes the last node
    free(temp);
}

void deleteAtPosition(int position) {
    if (head == NULL) {
        printf("List is empty\n");
        return;
    }
    if (position == 1) {
        deleteFirst();
        return;
    }

    struct Node *temp = head;
    for (int count = 1; count < position && temp != NULL; count++) {
        temp = temp->next;          // walk directly to the node to delete
    }

    if (temp == NULL) {
        printf("Position out of range\n");
        return;
    }

    temp->prev->next = temp->next;  // previous node skips over temp
    if (temp->next != NULL) {
        temp->next->prev = temp->prev;  // next node skips back over temp
    }
    free(temp);
}

// ---------- DISPLAY ----------

void display() {
    if (head == NULL) {
        printf("List is empty\n");
        return;
    }
    struct Node *temp = head;
    while (temp != NULL) {
        printf("%d <-> ", temp->data);
        temp = temp->next;
    }
    printf("NULL\n");
}

// ---------- MAIN ----------

int main() {
    int choice, value, position;

    while (1) {
        printf("\n1.Insert Beginning  2.Insert End  3.Insert Position\n");
        printf("4.Delete First      5.Delete Last 6.Delete Position\n");
        printf("7.Display           8.Exit\n");
        printf("Enter choice: ");
        scanf("%d", &choice);

        switch (choice) {
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
                exit(0);
            default:
                printf("Invalid choice\n");
        }
    }
    return 0;
}
