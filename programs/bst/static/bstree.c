#include <stdio.h>
#include <stdlib.h>

// A node holds a value and two pointers: one to the left child, one to the right child
struct Node {
    int data;
    struct Node *left;
    struct Node *right;
};

// ---------- CREATE NODE ----------

struct Node* createNode(int value) {
    struct Node *newNode = (struct Node *)malloc(sizeof(struct Node));
    newNode->data = value;
    newNode->left = NULL;
    newNode->right = NULL;
    return newNode;
}

// ---------- INSERT ----------

struct Node* insert(struct Node *root, int value) {
    if (root == NULL) {
        return createNode(value);
    }

    if (value < root->data) {
        root->left = insert(root->left, value);
    } else if (value > root->data) {
        root->right = insert(root->right, value);
    } else {
        printf("Value %d already exists (no duplicates allowed)\n", value);
    }

    return root;
}

// ---------- SEARCH ----------

struct Node* search(struct Node *root, int value) {
    if (root == NULL || root->data == value) {
        return root;
    }

    if (value < root->data) {
        return search(root->left, value);
    }

    return search(root->right, value);
}

// ---------- FIND MINIMUM ----------

struct Node* findMin(struct Node *root) {
    struct Node *current = root;

    while (current->left != NULL) {
        current = current->left;
    }

    return current;
}

// ---------- FIND MAXIMUM ----------

struct Node* findMax(struct Node *root) {
    struct Node *current = root;

    while (current->right != NULL) {
        current = current->right;
    }

    return current;
}

// ---------- DELETE ----------

struct Node* deleteNode(struct Node *root, int value) {
    if (root == NULL) {
        printf("Value %d not found\n", value);
        return NULL;
    }

    if (value < root->data) {
        root->left = deleteNode(root->left, value);
    } else if (value > root->data) {
        root->right = deleteNode(root->right, value);
    } else {
        // Case 1: No left child
        if (root->left == NULL) {
            struct Node *temp = root->right;
            free(root);
            return temp;
        }

        // Case 2: No right child
        if (root->right == NULL) {
            struct Node *temp = root->left;
            free(root);
            return temp;
        }

        // Case 3: Two children
        struct Node *successor = findMin(root->right);
        root->data = successor->data;
        root->right = deleteNode(root->right, successor->data);
    }

    return root;
}

// ---------- TRAVERSALS ----------

void inorder(struct Node *root) {
    if (root == NULL) {
        return;
    }

    inorder(root->left);
    printf("%d ", root->data);
    inorder(root->right);
}

void preorder(struct Node *root) {
    if (root == NULL) {
        return;
    }

    printf("%d ", root->data);
    preorder(root->left);
    preorder(root->right);
}

void postorder(struct Node *root) {
    if (root == NULL) {
        return;
    }

    postorder(root->left);
    postorder(root->right);
    printf("%d ", root->data);
}

void levelOrder(struct Node *root) {
    if (root == NULL) {
        return;
    }

    struct Node *queue[100];
    int front = 0, rear = 0;

    queue[rear] = root;
    rear++;

    while (front < rear) {
        struct Node *current = queue[front];
        front++;

        printf("%d ", current->data);

        if (current->left != NULL) {
            queue[rear] = current->left;
            rear++;
        }

        if (current->right != NULL) {
            queue[rear] = current->right;
            rear++;
        }
    }
}

// ---------- HEIGHT ----------

int height(struct Node *root) {
    if (root == NULL) {
        return -1;
    }

    int leftHeight = height(root->left);
    int rightHeight = height(root->right);

    if (leftHeight > rightHeight) {
        return leftHeight + 1;
    } else {
        return rightHeight + 1;
    }
}

// ---------- COUNT NODES ----------

int countNodes(struct Node *root) {
    if (root == NULL) {
        return 0;
    }

    return 1 + countNodes(root->left) + countNodes(root->right);
}

// ---------- COUNT LEAF NODES ----------

int countLeaves(struct Node *root) {
    if (root == NULL) {
        return 0;
    }

    if (root->left == NULL && root->right == NULL) {
        return 1;
    }

    return countLeaves(root->left) + countLeaves(root->right);
}

// ---------- DISPLAY ----------

void display(struct Node *root, int space) {
    if (root == NULL) {
        return;
    }

    space = space + 5;

    display(root->right, space);

    for (int i = 5; i < space; i++) {
        printf(" ");
    }

    printf("%d\n", root->data);

    display(root->left, space);
}

// ---------- MAIN ----------

int main() {
    struct Node *root = NULL;

    // INSERT
    root = insert(root, 50);
    root = insert(root, 30);
    root = insert(root, 70);
    root = insert(root, 20);
    root = insert(root, 40);
    root = insert(root, 60);
    root = insert(root, 80);

    // DISPLAY
    printf("Binary Search Tree:\n");
    display(root, 0);

    // DELETE
    root = deleteNode(root, 20);

    // SEARCH
    if (search(root, 40) != NULL) {
        printf("40 found in the tree\n");
    } else {
        printf("40 not found\n");
    }

    // MINIMUM
    printf("Minimum: %d\n", findMin(root)->data);

    // MAXIMUM
    printf("Maximum: %d\n", findMax(root)->data);

    // INORDER
    printf("Inorder: ");
    inorder(root);
    printf("\n");

    // PREORDER
    printf("Preorder: ");
    preorder(root);
    printf("\n");

    // POSTORDER
    printf("Postorder: ");
    postorder(root);
    printf("\n");

    // LEVEL ORDER
    printf("Level Order: ");
    levelOrder(root);
    printf("\n");

    return 0;
}
