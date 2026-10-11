#include <stdio.h>
#include <stdlib.h>

struct Node {
    int data;
    struct Node *next;
};

struct Node *front = NULL;      // front points to the first node (we remove from here)
struct Node *rear = NULL;       // rear points to the last node (we add here)

// ---------- IS EMPTY ----------

int isEmpty() {
    return front == NULL;       // 1 if empty, 0 if not
}

// ---------- ENQUEUE ----------

void enqueue(int value) {
    struct Node *newNode = (struct Node *)malloc(sizeof(struct Node));
    newNode->data = value;
    newNode->next = NULL;       // the new node will be the last node

    if (rear == NULL) {         // empty queue: new node is both front and rear
        front = newNode;
        rear = newNode;
    } else {
        rear->next = newNode;   // old last node points to the new node
        rear = newNode;         // rear moves to the new node
    }
    printf("Enqueued %d\n", value);
}

// ---------- DEQUEUE ----------

void dequeue() {
    if (isEmpty()) {
        printf("Queue Underflow\n");
        return;
    }
    struct Node *temp = front;  // save the front node so we can free it
    printf("Dequeued %d\n", temp->data);
    front = front->next;        // front moves to the next node

    if (front == NULL) {        // queue became empty
        rear = NULL;            // rear must be reset too
    }
    free(temp);
}

// ---------- PEEK ----------

void peek() {
    if (isEmpty()) {
        printf("Queue is empty\n");
        return;
    }
    printf("Front element: %d\n", front->data);     // just look, don't remove
}

// ---------- DISPLAY ----------

void display() {
    if (isEmpty()) {
        printf("Queue is empty\n");
        return;
    }
    struct Node *temp = front;
    printf("Queue (front to rear): ");
    while (temp != NULL) {
        printf("%d ", temp->data);
        temp = temp->next;      // move toward the rear
    }
    printf("\n");
}

// ---------- MAIN ----------

int main() {
    int choice, value;

    while (1) {
        printf("\n1.Enqueue  2.Dequeue  3.Peek  4.Is Empty  5.Display  6.Exit\n");
        printf("Enter choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                printf("Enter value: ");
                scanf("%d", &value);
                enqueue(value);
                break;
            case 2:
                dequeue();
                break;
            case 3:
                peek();
                break;
            case 4:
                if (isEmpty())
                    printf("Queue is empty\n");
                else
                    printf("Queue is not empty\n");
                break;
            case 5:
                display();
                break;
            case 6:
                exit(0);
            default:
                printf("Invalid choice\n");
        }
    }
    return 0;
}
