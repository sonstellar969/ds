#include <stdio.h>
#include <stdlib.h>

struct Node {
    int data;
    struct Node *next;
};

struct Node *top = NULL;

// ---------- IS EMPTY ----------

int isEmpty() {
    return top == NULL;
}

// ---------- PUSH ----------

void push(int value) {
    struct Node *newNode = (struct Node *)malloc(sizeof(struct Node));
    newNode->data = value;
    newNode->next = top;
    top = newNode;
    printf("Pushed %d\n", value);
}

// ---------- POP ----------

void pop() {
    if (isEmpty()) {
        printf("Stack Underflow\n");
        return;
    }
    struct Node *temp = top;
    printf("Popped %d\n", temp->data);
    top = top->next;
    free(temp);
}

// ---------- PEEK ----------

void peek() {
    if (isEmpty()) {
        printf("Stack is empty\n");
        return;
    }
    printf("Top element: %d\n", top->data);
}

// ---------- DISPLAY ----------

void display() {
    if (isEmpty()) {
        printf("Stack is empty\n");
        return;
    }
    struct Node *temp = top;
    printf("Stack (top to bottom): ");
    while (temp != NULL) {
        printf("%d ", temp->data);
        temp = temp->next;
    }
    printf("\n");
}

// ---------- MAIN ----------

int main() {
    push(10);
    push(20);
    push(30);

    display();

    peek();

    pop();

    display();

    if (isEmpty()) {
        printf("Stack is empty\n");
    } else {
        printf("Stack is not empty\n");
    }

    return 0;
}
