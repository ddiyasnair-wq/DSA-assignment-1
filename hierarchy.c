/*
 * Q5: Organisational Hierarchy - Tree Representation + Department Search
 * PCCST303 - Data Structures and Algorithms - Assignment 2
 *
 * Hierarchy:
 *   CEO -> HR, Finance, IT
 *   IT  -> Development, Testing
 *   Development -> Frontend, Backend
 *
 * Part a) General (n-ary) tree built with linked child lists, displayed
 *         using Level-Order Traversal (BFS).
 * Part b) Department names stored in an array; Linear Search and
 *         Binary Search compared for locating a department, with
 *         comparison counts recorded for at least 3 searches.
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_CHILDREN 5
#define MAX_NAME 30
#define MAX_NODES 20

/* ---------- Tree Node ---------- */
typedef struct TreeNode {
    char name[MAX_NAME];
    struct TreeNode *children[MAX_CHILDREN];
    int childCount;
} TreeNode;

TreeNode* createNode(const char *name) {
    TreeNode *node = (TreeNode*)malloc(sizeof(TreeNode));
    strcpy(node->name, name);
    node->childCount = 0;
    return node;
}

void addChild(TreeNode *parent, TreeNode *child) {
    parent->children[parent->childCount++] = child;
}

/* ---------- Level Order Traversal (BFS) ---------- */
void levelOrderTraversal(TreeNode *root) {
    if (root == NULL) return;

    TreeNode *queue[MAX_NODES];
    int front = 0, rear = 0;
    queue[rear++] = root;

    printf("Level-Order Traversal of Organisational Hierarchy:\n");
    while (front < rear) {
        int levelSize = rear - front;
        for (int i = 0; i < levelSize; i++) {
            TreeNode *curr = queue[front++];
            printf("%s ", curr->name);
            for (int j = 0; j < curr->childCount; j++) {
                queue[rear++] = curr->children[j];
            }
        }
        printf("\n");
    }
}

/* Utility: compute height of tree (for analysis) */
int treeHeight(TreeNode *root) {
    if (root == NULL || root->childCount == 0) return 1;
    int maxH = 0;
    for (int i = 0; i < root->childCount; i++) {
        int h = treeHeight(root->children[i]);
        if (h > maxH) maxH = h;
    }
    return 1 + maxH;
}

/* ---------- Linear Search ---------- */
int linearSearch(char arr[][MAX_NAME], int n, const char *key, int *comparisons) {
    *comparisons = 0;
    for (int i = 0; i < n; i++) {
        (*comparisons)++;
        if (strcmp(arr[i], key) == 0) return i;
    }
    return -1;
}

/* ---------- Binary Search (array must be sorted) ---------- */
int binarySearch(char arr[][MAX_NAME], int n, const char *key, int *comparisons) {
    *comparisons = 0;
    int low = 0, high = n - 1;
    while (low <= high) {
        int mid = (low + high) / 2;
        (*comparisons)++;
        int cmp = strcmp(arr[mid], key);
        if (cmp == 0) return mid;
        else if (cmp < 0) low = mid + 1;
        else high = mid - 1;
    }
    return -1;
}

/* ---------- Comparator for qsort ---------- */
int cmpFunc(const void *a, const void *b) {
    return strcmp((const char*)a, (const char*)b);
}

int main() {
    /* ---- Build the hierarchy tree ---- */
    TreeNode *CEO = createNode("CEO");
    TreeNode *HR = createNode("HR");
    TreeNode *Finance = createNode("Finance");
    TreeNode *IT = createNode("IT");
    TreeNode *Development = createNode("Development");
    TreeNode *Testing = createNode("Testing");
    TreeNode *Frontend = createNode("Frontend");
    TreeNode *Backend = createNode("Backend");

    addChild(CEO, HR);
    addChild(CEO, Finance);
    addChild(CEO, IT);
    addChild(IT, Development);
    addChild(IT, Testing);
    addChild(Development, Frontend);
    addChild(Development, Backend);

    printf("===== Part (a): Tree Construction & Level-Order Traversal =====\n");
    levelOrderTraversal(CEO);
    printf("Tree height: %d\n\n", treeHeight(CEO));

    /* ---- Part b: searchable representation ---- */
    char departments[][MAX_NAME] = {
        "CEO", "HR", "Finance", "IT", "Development",
        "Testing", "Frontend", "Backend"
    };
    int n = 8;

    char sortedDept[8][MAX_NAME];
    memcpy(sortedDept, departments, sizeof(departments));
    qsort(sortedDept, n, MAX_NAME, cmpFunc);

    printf("===== Part (b): Linear Search vs Binary Search =====\n");
    printf("Unsorted array (for Linear Search): ");
    for (int i = 0; i < n; i++) printf("%s ", departments[i]);
    printf("\nSorted array (for Binary Search):  ");
    for (int i = 0; i < n; i++) printf("%s ", sortedDept[i]);
    printf("\n\n");

    /* At least three searches: one hit early/mid/late in unsorted order,
       plus one miss, to exercise both algorithms meaningfully */
    char *searchKeys[] = {"Testing", "HR", "Backend", "Sales"};
    int numSearches = 4;

    printf("%-12s %-18s %-18s\n", "Key", "Linear (comparisons)", "Binary (comparisons)");
    for (int i = 0; i < numSearches; i++) {
        int lc, bc;
        int li = linearSearch(departments, n, searchKeys[i], &lc);
        int bi = binarySearch(sortedDept, n, searchKeys[i], &bc);
        printf("%-12s %-18d %-18d %s\n", searchKeys[i], lc, bc,
               (li == -1 && bi == -1) ? "(not found)" : "");
    }

    return 0;
}
