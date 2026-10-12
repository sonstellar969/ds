#include <stdio.h>
#include <stdlib.h>

struct Node {
    int data;
    struct Node *next;
};

struct Node *head = NULL;

// ---------- INSERT ----------

void insertAtBeginning(int value) {
    struct Node *newNode = (struct Node *)malloc(sizeof(struct Node));
    newNode->data = value;

    if (head == NULL) {             // empty list
        newNode->next = newNode;    // the only node points to itself
        head = newNode;
        return;
    }

    struct Node *temp = head;
    while (temp->next != head) {
        temp = temp->next;          // walk to the last node
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
        temp = temp->next;          // walk to the last node
    }
    temp->next = newNode;           // last node points to the new node
    newNode->next = head;           // new node points back to head, keeping the circle
}

void insertAtPosition(int value, int position) {
    if (position == 1) {
        insertAtBeginning(value);
        return;
    }
    if (head == NULL) {
        printf("Position out of range\n");
        return;
    }

    struct Node *temp = head;
    int count = 1;
    while (count < position - 1 && temp->next != head) {
        temp = temp->next;          // walk to the node before the position
        count++;
    }

    if (count < position - 1) {     // ran out of nodes before reaching the position
        printf("Position out of range\n");
        return;
    }

    struct Node *newNode = (struct Node *)malloc(sizeof(struct Node));
    newNode->data = value;
    newNode->next = temp->next;     // new node points to the next node
    temp->next = newNode;           // previous node points to the new node
}

// ---------- DELETE ----------

void deleteFirst() {
    if (head == NULL) {
        printf("List is empty\n");
        return;
    }
    if (head->next == head) {       // only one node
        free(head);
        head = NULL;
        return;
    }

    struct Node *temp = head;
    while (temp->next != head) {
        temp = temp->next;          // walk to the last node
    }
    struct Node *nodeToDelete = head;   // save the first node
    head = head->next;                  // head moves to the second node
    temp->next = head;                  // last node points to the new first node
    free(nodeToDelete);
}

void deleteLast() {
    if (head == NULL) {
        printf("List is empty\n");
        return;
    }
    if (head->next == head) {       // only one node
        free(head);
        head = NULL;
        return;
    }

    struct Node *temp = head;
    while (temp->next->next != head) {
        temp = temp->next;          // stop at the second-last node
    }
    free(temp->next);               // delete the last node
    temp->next = head;              // second-last node now points back to head
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
    int count = 1;
    while (count < position - 1 && temp->next != head) {
        temp = temp->next;          // walk to the node before the one to delete
        count++;
    }

    if (temp->next == head) {       // the node to delete does not exist
        printf("Position out of range\n");
        return;
    }

    struct Node *nodeToDelete = temp->next;
    temp->next = nodeToDelete->next;    // skip over the deleted node
    free(nodeToDelete);
}

// ---------- DISPLAY ----------

void display() {
    if (head == NULL) {
        printf("List is empty\n");
        return;
    }
    struct Node *temp = head;
    do {
        printf("%d -> ", temp->data);
        temp = temp->next;
    } while (temp != head);         // stop when we are back at head
    printf("(back to head)\n");
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
