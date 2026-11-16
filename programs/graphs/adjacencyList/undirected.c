#include <stdio.h>
#include <stdlib.h>

// Structure for each linked-list node
struct Node {
    int vertex;
    struct Node *next;
};

// Insert a neighbour into the linked list
void addEdge(struct Node *adj[], int from, int to) {

    struct Node *newNode = malloc(sizeof(struct Node));

    newNode->vertex = to;
    newNode->next = adj[from];

    adj[from] = newNode;
}

// Display adjacency list
void display(struct Node *adj[], int n) {

    for (int i = 0; i < n; i++) {

        printf("Vertex %d: ", i);

        struct Node *temp = adj[i];

        while (temp != NULL) {
            printf("%d -> ", temp->vertex);
            temp = temp->next;
        }

        printf("NULL\n");
    }
}

// Free allocated memory
void freeGraph(struct Node *adj[], int n) {

    for (int i = 0; i < n; i++) {

        struct Node *temp = adj[i];

        while (temp != NULL) {
            struct Node *del = temp;
            temp = temp->next;
            free(del);
        }
    }

    free(adj);
}

int main() {

    int n, e;

    printf("Enter number of vertices: ");
    scanf("%d", &n);

    printf("Enter number of edges: ");
    scanf("%d", &e);

    if (n < 1 || e < 0) {
        printf("Invalid input\n");
        return 1;
    }

    // Create an array of linked-list head pointers
    struct Node **adj = malloc(n * sizeof(struct Node *));

    // Initially all lists are empty
    for (int i = 0; i < n; i++) {
        adj[i] = NULL;
    }

    // Read undirected edges
    for (int i = 0; i < e; i++) {

        int from, to;

        printf("Enter edge (from to): ");
        scanf("%d %d", &from, &to);

        if (from < 0 || from >= n || to < 0 || to >= n) {
            printf("Invalid vertex. Try again.\n");
            i--;
            continue;
        }

        // First direction
        addEdge(adj, from, to);

        // Reverse direction
        addEdge(adj, to, from);
    }

    printf("\nUndirected Adjacency List:\n");

    display(adj, n);

    freeGraph(adj, n);

    return 0;
}
