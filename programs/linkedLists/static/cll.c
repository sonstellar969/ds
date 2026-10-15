#include <stdio.h>
#include <stdlib.h>

// A node holds a value and the address of the next node
struct Node {
    int data;
    struct Node *next;
};

// head holds the address of the first node. NULL means the list is empty
// In a circular list the last node points back to head, never to NULL
struct Node *head = NULL;

// ---------- INSERT ----------

void insertAtBeginning(int value) {
    struct Node *newNode = (struct Node *)malloc(sizeof(struct Node));  // ask memory for one node
    newNode->data = value;          // store the value in the new node

    if (head == NULL) {             // empty list
        newNode->next = newNode;    // the only node points to itself
        head = newNode;
        return;
    }

    struct Node *temp = head;       // temp walks the list, so head never moves
    while (temp->next != head) {
        temp = temp->next;          // keep moving until temp is the last node
    }
    newNode->next = head;           // new node points to the old first node
    temp->next = newNode;           // last node points to the new node
    head = newNode;                 // head now points to the new node
}

void insertAtEnd(int value) {
    if (head == NULL) {             // empty list: same as inserting at the beginning
        insertAtBeginning(value);
        return;
    }

    struct Node *newNode = (struct Node *)malloc(sizeof(struct Node));
    newNode->data = value;

    struct Node *temp = head;
    while (temp->next != head) {
        temp = temp->next;          // keep moving until temp is the last node
    }
    temp->next = newNode;           // last node points to the new node
    newNode->next = head;           // new node points back to head, keeping the circle
}

void insertAtPosition(int value, int position) {
    if (position == 1) {                // position 1 is the same as inserting at the beginning
        insertAtBeginning(value);
        return;
    }
    if (head == NULL) {                 // empty list, so no position beyond 1 exists
        printf("Position out of range\n");
        return;
    }

    struct Node *temp = head;
    int count = 1;
    while (count < position - 1 && temp->next != head) {
        temp = temp->next;              // walk to the node just BEFORE the position
        count++;
    }

    if (count < position - 1) {         // ran out of nodes before reaching the position
        printf("Position out of range\n");
        return;
    }

    struct Node *newNode = (struct Node *)malloc(sizeof(struct Node));
    newNode->data = value;
    newNode->next = temp->next;         // step 1: new node points to the node after temp
    temp->next = newNode;               // step 2: temp now points to the new node
}

// ---------- DELETE ----------

void deleteFirst() {
    if (head == NULL) {                 // nothing to delete
        printf("List is empty\n");
        return;
    }
    if (head->next == head) {           // only one node in the list
        free(head);
        head = NULL;                    // list is now empty
        return;
    }

    struct Node *temp = head;
    while (temp->next != head) {
        temp = temp->next;              // walk to the last node
    }
    struct Node *nodeToDelete = head;   // save the first node so we can free it
    head = head->next;                  // head moves to the second node
    temp->next = head;                  // last node points to the new first node
    free(nodeToDelete);                 // give the old first node's memory back
}

void deleteLast() {
    if (head == NULL) {
        printf("List is empty\n");
        return;
    }
    if (head->next == head) {           // only one node in the list
        free(head);
        head = NULL;                    // list is now empty
        return;
    }

    struct Node *temp = head;
    while (temp->next->next != head) {
        temp = temp->next;              // stop at the second-last node
    }
    free(temp->next);                   // delete the last node
    temp->next = head;                  // second-last node now points back to head
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
    int count = 1;
    while (count < position - 1 && temp->next != head) {
        temp = temp->next;              // walk to the node just BEFORE the one to delete
        count++;
    }

    if (temp->next == head) {           // the node to delete does not exist
        printf("Position out of range\n");
        return;
    }

    struct Node *nodeToDelete = temp->next;     // the node we want to remove
    temp->next = nodeToDelete->next;            // skip over it
    free(nodeToDelete);                         // give its memory back
}

// ---------- DISPLAY ----------

void display() {
    if (head == NULL) {
        printf("List is empty\n");
        return;
    }
    struct Node *temp = head;           // start at the first node
    do {
        printf("%d -> ", temp->data);   // print the current node's value
        temp = temp->next;              // move to the next node
    } while (temp != head);             // stop when we are back at head
    printf("(back to head)\n");
}

// ---------- MAIN ----------

int main() {
    // Insert elements at the beginning
    insertAtBeginning(20);
    insertAtBeginning(10);

    // Insert an element at the end
    insertAtEnd(40);

    // Insert 30 at position 3
    insertAtPosition(30, 3);

    // Display the original circular list
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
