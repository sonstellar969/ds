#include <stdio.h>
#include <stdlib.h>

// A node holds data, the next address, and the previous address
struct Node {
    int data;
    struct Node *next;
    struct Node *prev;
};

// head points to the first node
struct Node *head = NULL;

// ---------- INSERT ----------

void insertAtBeginning(int value) {
    struct Node *newNode = (struct Node *)malloc(sizeof(struct Node));

    newNode->data = value;
    newNode->prev = NULL;       // first node has no previous node
    newNode->next = head;       // point to the old first node

    if (head != NULL) {
        head->prev = newNode;   // old first node points back to new node
    }

    head = newNode;             // head points to the new node
}

void insertAtEnd(int value) {
    struct Node *newNode = (struct Node *)malloc(sizeof(struct Node));

    newNode->data = value;
    newNode->next = NULL;       // new node will be the last node

    if (head == NULL) {
        newNode->prev = NULL;
        head = newNode;
        return;
    }

    struct Node *temp = head;

    while (temp->next != NULL) {
        temp = temp->next;      // move to the last node
    }

    temp->next = newNode;       // last node points to new node
    newNode->prev = temp;       // new node points back to last node
}

void insertAtPosition(int value, int position) {
    if (position == 1) {
        insertAtBeginning(value);
        return;
    }

    struct Node *temp = head;

    for (int count = 1; count < position - 1 && temp != NULL; count++) {
        temp = temp->next;      // move to the node before the position
    }

    if (temp == NULL || position < 1) {
        printf("Position out of range\n");
        return;
    }

    struct Node *newNode = (struct Node *)malloc(sizeof(struct Node));

    newNode->data = value;
    newNode->next = temp->next; // point forward
    newNode->prev = temp;       // point backward

    if (temp->next != NULL) {
        temp->next->prev = newNode;
    }

    temp->next = newNode;       // connect previous node to new node
}

// ---------- DELETE ----------

void deleteFirst() {
    if (head == NULL) {
        printf("List is empty\n");
        return;
    }

    struct Node *temp = head;

    head = head->next;          // move head to the next node

    if (head != NULL) {
        head->prev = NULL;      // new first node has no previous node
    }

    free(temp);
}

void deleteLast() {
    if (head == NULL) {
        printf("List is empty\n");
        return;
    }

    if (head->next == NULL) {
        free(head);
        head = NULL;
        return;
    }

    struct Node *temp = head;

    while (temp->next != NULL) {
        temp = temp->next;      // move to the last node
    }

    temp->prev->next = NULL;    // second-last node becomes last
    free(temp);
}

void deleteAtPosition(int position) {
    if (head == NULL) {
        printf("List is empty\n");
        return;
    }

    if (position < 1) {
        printf("Position out of range\n");
        return;
    }

    if (position == 1) {
        deleteFirst();
        return;
    }

    struct Node *temp = head;

    for (int count = 1; count < position && temp != NULL; count++) {
        temp = temp->next;      // move to the node to delete
    }

    if (temp == NULL) {
        printf("Position out of range\n");
        return;
    }

    temp->prev->next = temp->next; // previous node skips this node

    if (temp->next != NULL) {
        temp->next->prev = temp->prev; // next node skips back over this node
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
    // Insert at beginning
    insertAtBeginning(20);
    insertAtBeginning(10);

    // Insert at end
    insertAtEnd(40);

    // Insert 30 at position 3
    insertAtPosition(30, 3);

    printf("Original list: ");
    display();

    // Delete the first node
    deleteFirst();
    printf("After deleting first: ");
    display();

    // Delete the last node
    deleteLast();
    printf("After deleting last: ");
    display();

    // Delete the node at position 2
    deleteAtPosition(2);
    printf("After deleting position 2: ");
    display();

    return 0;
}
