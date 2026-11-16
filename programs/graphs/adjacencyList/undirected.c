#include <stdio.h>
#include <stdlib.h>

// One node represents one neighbour
struct Node {
    int vertex;
    struct Node *next;
};

// Insert a neighbour into a vertex's linked list
void addEdge(struct Node *adjacencyList[], int from, int to) {

    struct Node *newNode = malloc(sizeof(struct Node));

    newNode->vertex = to;
    newNode->next = NULL;

    // If the linked list is empty
    if (adjacencyList[from] == NULL) {
        adjacencyList[from] = newNode;
        return;
    }

    // Move to the end of the linked list
    struct Node *temp = adjacencyList[from];

    while (temp->next != NULL) {
        temp = temp->next;
    }

    // Attach the new node
    temp->next = newNode;
}

// Display the adjacency list
void display(struct Node *adjacencyList[], int vertexCount) {

    for (int i = 0; i < vertexCount; i++) {

        printf("Vertex %d: ", i);

        struct Node *temp = adjacencyList[i];

        while (temp != NULL) {
            printf("%d -> ", temp->vertex);
            temp = temp->next;
        }

        printf("NULL\n");
    }
}

// Free dynamically allocated memory
void freeGraph(struct Node *adjacencyList[], int vertexCount) {

    for (int i = 0; i < vertexCount; i++) {

        struct Node *temp = adjacencyList[i];

        while (temp != NULL) {

            struct Node *nodeToDelete = temp;
            temp = temp->next;

            free(nodeToDelete);
        }
    }

    free(adjacencyList);
}

int main() {

    int vertexCount, edgeCount;

    printf("Enter number of vertices: ");
    scanf("%d", &vertexCount);

    printf("Enter number of edges: ");
    scanf("%d", &edgeCount);

    if (vertexCount < 1 || edgeCount < 0) {
        printf("Invalid input\n");
        return 1;
    }

    // Dynamically allocate an array of linked-list head pointers
    struct Node **adjacencyList =
        malloc(vertexCount * sizeof(struct Node *));

    if (adjacencyList == NULL) {
        printf("Memory allocation failed\n");
        return 1;
    }

    // Initially, every vertex has an empty linked list
    for (int i = 0; i < vertexCount; i++) {
        adjacencyList[i] = NULL;
    }

    // Read edges
    printf("Enter edges (from to):\n");

    for (int i = 1; i <= edgeCount; i++) {

        int from, to;

        printf("Edge %d: ", i);
        scanf("%d %d", &from, &to);

        if (from < 0 || from >= vertexCount ||
            to < 0 || to >= vertexCount) {

            printf("Invalid vertex. Try again.\n");
            i--;
            continue;
        }

        // Add from -> to
        addEdge(adjacencyList, from, to);

        // Add to -> from because the graph is undirected
        addEdge(adjacencyList, to, from);
    }

    printf("\nUndirected Adjacency List:\n");

    display(adjacencyList, vertexCount);

    freeGraph(adjacencyList, vertexCount);

    return 0;
}
