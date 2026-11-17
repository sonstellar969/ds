
#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

// Structure for each linked-list node
struct Node {
    int vertex;
    int weight;
    struct Node *next;
};

// Insert a weighted edge into the adjacency list
void addEdge(struct Node *adj[], int from, int to, int weight) {

    struct Node *newNode = malloc(sizeof(struct Node));

    newNode->vertex = to;
    newNode->weight = weight;
    newNode->next = adj[from];

    adj[from] = newNode;
}

// Prim's algorithm
void prim(struct Node *adj[], int n) {

    // Store the minimum edge weight to connect each vertex
    int key[n];

    // Store the parent of each vertex in the MST
    int parent[n];

    // Keep track of vertices already included in MST
    int inMST[n];

    // Initialize all arrays
    for (int i = 0; i < n; i++) {
        key[i] = INT_MAX;
        parent[i] = -1;
        inMST[i] = 0;
    }

    // Start from vertex 0
    key[0] = 0;

    // Repeat until all vertices are included
    for (int count = 0; count < n; count++) {

        int min = INT_MAX;
        int u = -1;

        // Find the vertex with minimum key value
        for (int i = 0; i < n; i++) {

            if (inMST[i] == 0 && key[i] < min) {
                min = key[i];
                u = i;
            }
        }

        // Check whether the graph is disconnected
        if (u == -1) {
            printf("Graph is not connected. MST cannot be formed.\n");
            return;
        }

        // Include the selected vertex in MST
        inMST[u] = 1;

        // Visit all neighbours of selected vertex
        struct Node *temp = adj[u];

        while (temp != NULL) {

            int v = temp->vertex;
            int weight = temp->weight;

            // Update key if a smaller edge is found
            if (inMST[v] == 0 && weight < key[v]) {

                key[v] = weight;
                parent[v] = u;
            }

            temp = temp->next;
        }
    }

    // Display Minimum Spanning Tree
    int totalWeight = 0;

    printf("\nMinimum Spanning Tree:\n");
    printf("Edge\tWeight\n");

    for (int i = 1; i < n; i++) {

        printf("%d - %d\t%d\n", parent[i], i, key[i]);

        totalWeight += key[i];
    }

    printf("Total Weight = %d\n", totalWeight);
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

    // Read weighted undirected edges
    for (int i = 0; i < e; i++) {

        int from, to, weight;

        printf("Enter edge (from to weight): ");
        scanf("%d %d %d", &from, &to, &weight);

        if (from < 0 || from >= n || to < 0 || to >= n) {
            printf("Invalid vertex. Try again.\n");
            i--;
            continue;
        }

        // Add weighted edge in both directions
        addEdge(adj, from, to, weight);
        addEdge(adj, to, from, weight);
    }

    // Perform Prim's algorithm
    prim(adj, n);

    // Free allocated memory
    freeGraph(adj, n);

    return 0;
}
