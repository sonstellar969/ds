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
    struct Node *newNode = (struct Node *)malloc(sizeof(struct Node));  // ask memory for one node
    newNode->data = value;
    newNode->left = NULL;       // new node has no children yet
    newNode->right = NULL;
    return newNode;             // give back the address of the new node
}

// ---------- INSERT ----------

struct Node* insert(struct Node *root, int value) {
    if (root == NULL) {
        return createNode(value);                 // found an empty spot, place the new node here
    }
    if (value < root->data) {
        root->left = insert(root->left, value);   // smaller value, go to the left subtree
    } else if (value > root->data) {
        root->right = insert(root->right, value); // bigger value, go to the right subtree
    } else {
        printf("Value %d already exists (no duplicates allowed)\n", value);
    }
    return root;                                  // root of this subtree stays the same
}

// ---------- SEARCH ----------

struct Node* search(struct Node *root, int value) {
    if (root == NULL || root->data == value) {
        return root;                              // found it, or reached a dead end (NULL)
    }
    if (value < root->data) {
        return search(root->left, value);         // smaller, look left
    }
    return search(root->right, value);            // bigger, look right
}

// ---------- FIND MINIMUM ----------

struct Node* findMin(struct Node *root) {
    struct Node *current = root;
    while (current->left != NULL) {
        current = current->left;                  // smallest value is the leftmost node
    }
    return current;
}

// ---------- FIND MAXIMUM ----------

struct Node* findMax(struct Node *root) {
    struct Node *current = root;
    while (current->right != NULL) {
        current = current->right;                 // largest value is the rightmost node
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
        root->left = deleteNode(root->left, value);     // target is in the left subtree
    } else if (value > root->data) {
        root->right = deleteNode(root->right, value);   // target is in the right subtree
    } else {
        // this is the node to delete, 3 cases:

        // Case 1: no left child (leaf, or only a right child)
        if (root->left == NULL) {
            struct Node *temp = root->right;   // save the right child (may be NULL)
            free(root);                        // delete the node
            return temp;                       // right child takes its place
        }

        // Case 2: no right child (only a left child)
        if (root->right == NULL) {
            struct Node *temp = root->left;    // save the left child
            free(root);
            return temp;                       // left child takes its place
        }

        // Case 3: two children
        struct Node *successor = findMin(root->right);          // smallest node in the right subtree
        root->data = successor->data;                            // copy successor's value into this node
        root->right = deleteNode(root->right, successor->data);  // delete the original successor node
    }
    return root;
}

// ---------- TRAVERSALS ----------

void inorder(struct Node *root) {            // Left, Root, Right (gives sorted order)
    if (root == NULL) return;
    inorder(root->left);
    printf("%d ", root->data);
    inorder(root->right);
}

void preorder(struct Node *root) {           // Root, Left, Right
    if (root == NULL) return;
    printf("%d ", root->data);
    preorder(root->left);
    preorder(root->right);
}

void postorder(struct Node *root) {          // Left, Right, Root
    if (root == NULL) return;
    postorder(root->left);
    postorder(root->right);
    printf("%d ", root->data);
}

void levelOrder(struct Node *root) {         // level by level, left to right
    if (root == NULL) return;

    struct Node *queue[100];                 // simple array used as a queue
    int front = 0, rear = 0;

    queue[rear] = root;                      // put root in the queue
    rear++;

    while (front < rear) {
        struct Node *current = queue[front]; // take the node at the front
        front++;
        printf("%d ", current->data);

        if (current->left != NULL) {         // add children to the back of the queue
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
    if (root == NULL) return -1;             // empty tree has height -1
    int leftHeight = height(root->left);
    int rightHeight = height(root->right);
    if (leftHeight > rightHeight)
        return leftHeight + 1;
    else
        return rightHeight + 1;
}

// ---------- COUNT NODES ----------

int countNodes(struct Node *root) {
    if (root == NULL) return 0;
    return 1 + countNodes(root->left) + countNodes(root->right);
}

// ---------- COUNT LEAF NODES ----------

int countLeaves(struct Node *root) {
    if (root == NULL) return 0;
    if (root->left == NULL && root->right == NULL) return 1;   // no children = leaf
    return countLeaves(root->left) + countLeaves(root->right);
}

// ---------- DISPLAY (prints the tree sideways) ----------

void display(struct Node *root, int space) {
    if (root == NULL) return;

    space = space + 5;                    // each level goes 5 spaces further right

    display(root->right, space);          // print the right subtree first (it shows on top)

    for (int i = 5; i < space; i++) {     // print spaces to push this value right
        printf(" ");
    }
    printf("%d\n", root->data);           // print this node

    display(root->left, space);           // then the left subtree (it shows at the bottom)
}

// ---------- MAIN MENU ----------

int main() {
    struct Node *root = NULL;     // empty tree to start with
    int choice, value;

    while (1) {
        printf("\n===== BST MENU =====\n");
        printf("1.Insert      2.Delete       3.Search\n");
        printf("4.Inorder     5.Preorder     6.Postorder\n");
        printf("7.Level Order 8.Height       9.Count Nodes\n");
        printf("10.Count Leaves 11.Find Min  12.Find Max\n");
        printf("13.Display    14.Exit\n");
        printf("Enter choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                printf("Enter value to insert: ");
                scanf("%d", &value);
                root = insert(root, value);
                break;

            case 2:
                printf("Enter value to delete: ");
                scanf("%d", &value);
                root = deleteNode(root, value);
                break;

            case 3: {
                printf("Enter value to search: ");
                scanf("%d", &value);
                struct Node *result = search(root, value);
                if (result != NULL)
                    printf("%d found in the tree\n", value);
                else
                    printf("%d not found\n", value);
                break;
            }

            case 4:
                printf("Inorder: ");
                inorder(root);
                printf("\n");
                break;

            case 5:
                printf("Preorder: ");
                preorder(root);
                printf("\n");
                break;

            case 6:
                printf("Postorder: ");
                postorder(root);
                printf("\n");
                break;

            case 7:
                printf("Level Order: ");
                levelOrder(root);
                printf("\n");
                break;

            case 8:
                printf("Height: %d\n", height(root));
                break;

            case 9:
                printf("Total nodes: %d\n", countNodes(root));
                break;

            case 10:
                printf("Leaf nodes: %d\n", countLeaves(root));
                break;

            case 11:
                if (root == NULL) printf("Tree is empty\n");
                else printf("Minimum value: %d\n", findMin(root)->data);
                break;

            case 12:
                if (root == NULL) printf("Tree is empty\n");
                else printf("Maximum value: %d\n", findMax(root)->data);
                break;

            case 13:
                if (root == NULL) {
                    printf("Tree is empty\n");
                } else {
                    printf("Tree (rotated left, root on the left edge):\n");
                    display(root, 0);
                }
                break;

            case 14:
                printf("Exiting...\n");
                exit(0);

            default:
                printf("Invalid choice\n");
        }
    }
    return 0;
}
