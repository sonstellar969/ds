#include <stdio.h>
#include <stdlib.h>

struct Node {
    int data;
    struct Node *next;
};

struct Node *front = NULL;
struct Node *rear = NULL;

// ---------- IS EMPTY ----------

int isEmpty() {
    return front == NULL;
}

// ---------- ENQUEUE ----------

void enqueue(int value) {
    struct Node *newNode = (struct Node *)malloc(sizeof(struct Node));
    newNode->data = value;
    newNode->next = NULL;

    if (rear == NULL) {
        front = newNode;
        rear = newNode;
    } else {
        rear->next = newNode;
        rear = newNode;
    }
    printf("Enqueued %d\n", value);
}

// ---------- DEQUEUE ----------

void dequeue() {
    if (isEmpty()) {
        printf("Queue Underflow\n");
        return;
    }
    struct Node *temp = front;
    printf("Dequeued %d\n", temp->data);
    front = front->next;

    if (front == NULL) {
        rear = NULL;
    }
    free(temp);
}

// ---------- PEEK ----------

void peek() {
    if (isEmpty()) {
        printf("Queue is empty\n");
        return;
    }
    printf("Front element: %d\n", front->data);
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
        temp = temp->next;
    }
    printf("\n");
}

// ---------- MAIN ----------

int main() {
    enqueue(10);
    enqueue(20);
    enqueue(30);

    display();

    peek();

    dequeue();

    display();

    if (isEmpty()) {
        printf("Queue is empty\n");
    } else {
        printf("Queue is not empty\n");
    }

    return 0;
}
