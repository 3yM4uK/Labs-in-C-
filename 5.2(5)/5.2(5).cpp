#include <stdio.h>
#include <malloc.h>

typedef struct Node {
    char data;
    Node* parent;
    Node* left;
    Node* right;
}Node;

char* enterString();
Node* addNode(Node*, char);
void insertNode(Node**, char);
void createTreeFromString(Node** tree);
void showTree(Node*, const char*, int);
void deleteTree(Node*&);
int leavesCount(Node*);

int main() {
    Node* tree = NULL;
    createTreeFromString(&tree);
    showTree(tree, "root", 0);
    printf("Number of leaves in tree: %d", leavesCount(tree));
    deleteTree(tree);
}

char* enterString() {
    char* str = (char*)malloc(sizeof(char));
    int i = 0;
    while ((str[i] = getchar()) != '\n') {
        str = (char*)realloc(str, (++i + 1) * sizeof(char));
    }
    str[i] = '\0';
    return str;
}
Node* addNode(Node* parent, char data) {
    Node* tmp = NULL;
    if (!(tmp = (Node*)malloc(sizeof(Node)))) {
        return 0;
    }
    tmp->left = tmp->right = NULL;
    tmp->data = data;
    tmp->parent = parent;
    return tmp;
}

void insertNode(Node** head, char data) {
    Node* tmp = NULL;
    if (*head == NULL) {
        *head = addNode(NULL, data);
        return;
    }
    tmp = *head;
    while (tmp) {
        if (data > tmp->data) {
            if (tmp->right != NULL) {
                tmp = tmp->right;
                continue;
            }
            else {
                tmp->right = addNode(tmp, data);
                return;
            }
        }
        else if (data < tmp->data) {
            if (tmp->left != NULL) {
                tmp = tmp->left;
                continue;
            }
            else {
                tmp->left = addNode(tmp, data);
                return;
            }
        }
        else {
            return;
        }
    }
}

void createTreeFromString(Node** head) {
    printf("Enter string which should be inserted in tree: ");
    rewind(stdin);
    char* strToInsert = enterString();
    int i = 0;
    while (strToInsert[i] != '\0') {
        insertNode(head, strToInsert[i]);
        i++;
    }
    free(strToInsert);
}

void showTree(Node* parent, const char* location, int depthLevel) {
    if (parent) {
        printf("Depth level = %d, %s = %c\n", depthLevel, location, parent->data);
        showTree(parent->left, "left", depthLevel + 1);
        showTree(parent->right, "right", depthLevel + 1);
    }
}

int leavesCount(Node* root) {
    int result;
    if ((root->left == NULL) && (root->right == NULL)) {
        result = 1;
    }
    else {
        result = 0;
    }
    if (root->left != NULL) {
        result += leavesCount(root->left);
    }
    if (root->right != NULL) {
        result += leavesCount(root->right);
    }
    return result;
}
void deleteTree(Node*& tree) {
    if (tree->left) {
        deleteTree(tree->left);
    }
    if (tree->right) {
        deleteTree(tree->right);
    }
    free(tree);
    tree = NULL;
}