
#include <stdio.h>
#include <stdlib.h>

// Structure for each linked-list node
struct Node {
    int vertex;
    struct Node *next;
};

// Insert an edge into the adjacency list
void addEdge(struct Node *adj[], int from, int to) {

    struct Node *newNode = malloc(sizeof(struct Node));

    newNode->vertex = to;
    newNode->next = adj[from];

    adj[from] = newNode;
}

// BFS traversal
void BFS(struct Node *adj[], int n, int start) {

    // Array to keep track of visited vertices
    int visited[n];

    // Initially, no vertex is visited
    for (int i = 0; i < n; i++) {
        visited[i] = 0;
    }

    // Queue to store vertices
    int queue[n];

    int front = 0;
    int rear = 0;

    // Mark starting vertex as visited
    visited[start] = 1;

    // Insert starting vertex into queue
    queue[rear++] = start;

    printf("BFS Traversal: ");

    // Continue until the queue becomes empty
    while (front < rear) {

        // Remove a vertex from the front of queue
        int current = queue[front++];

        // Print the current vertex
        printf("%d ", current);

        // Visit all neighbours of current vertex
        struct Node *temp = adj[current];

        while (temp != NULL) {

            int neighbour = temp->vertex;

            // If neighbour is not visited
            if (visited[neighbour] == 0) {

                // Mark it as visited
                visited[neighbour] = 1;

                // Insert neighbour into queue
                queue[rear++] = neighbour;
            }

            temp = temp->next;
        }
    }

    printf("\n");
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

    // Initially all adjacency lists are empty
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

        // Add edge in both directions
        addEdge(adj, from, to);
        addEdge(adj, to, from);
    }

    int start;

    printf("Enter starting vertex: ");
    scanf("%d", &start);

    if (start < 0 || start >= n) {
        printf("Invalid starting vertex\n");
        freeGraph(adj, n);
        return 1;
    }

    // Perform BFS traversal
    BFS(adj, n, start);

    // Free allocated memory
    freeGraph(adj, n);

    return 0;
}
