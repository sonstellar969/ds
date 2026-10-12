#include <stdio.h>
#include <stdlib.h>

struct Node {
    int data;
    struct Node *next;
};

struct Node *top = NULL;        // top holds the address of the top node. NULL means the stack is empty

// ---------- IS EMPTY ----------

int isEmpty() {
    return top == NULL;         // 1 if empty, 0 if not
}

// ---------- PUSH ----------

void push(int value) {
    struct Node *newNode = (struct Node *)malloc(sizeof(struct Node));
    newNode->data = value;
    newNode->next = top;        // new node points to the old top
    top = newNode;              // top now points to the new node
    printf("Pushed %d\n", value);
}

// ---------- POP ----------

void pop() {
    if (isEmpty()) {
        printf("Stack Underflow\n");
        return;
    }
    struct Node *temp = top;    // save the top node so we can free it
    printf("Popped %d\n", temp->data);
    top = top->next;            // top moves down to the next node
    free(temp);
}

// ---------- PEEK ----------

void peek() {
    if (isEmpty()) {
        printf("Stack is empty\n");
        return;
    }
    printf("Top element: %d\n", top->data);     // just look, don't remove
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
        temp = temp->next;      // move down the stack
    }
    printf("\n");
}

// ---------- MAIN ----------

int main() {
    int choice, value;

    while (1) {
        printf("\n1.Push  2.Pop  3.Peek  4.Is Empty  5.Display  6.Exit\n");
        printf("Enter choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                printf("Enter value: ");
                scanf("%d", &value);
                push(value);
                break;
            case 2:
                pop();
                break;
            case 3:
                peek();
                break;
            case 4:
                if (isEmpty())
                    printf("Stack is empty\n");
                else
                    printf("Stack is not empty\n");
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
