#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_NAME 100
#define MAX_INPUT 150

 
typedef struct Node {
    char name[MAX_NAME];
    int isFile;  
    struct Node *child;  
    struct Node *sibling;  
    struct Node *parent;  
} Node;

 
Node* createNode(const char *name, int isFile, Node* parent) {
    Node *newNode = (Node*)malloc(sizeof(Node));
    if (!newNode) {
        perror("Memory allocation error");
        exit(EXIT_FAILURE);
    }
    strncpy(newNode->name, name, MAX_NAME);
    newNode->name[MAX_NAME - 1] = '\0';
    newNode->isFile = isFile;
    newNode->child = NULL;
    newNode->sibling = NULL;
    newNode->parent = parent;
    return newNode;
}

 
void addChild(Node *parent, Node *child) {
    if (!parent->child) {
        parent->child = child;
    } else {
         
        Node *temp = parent->child;
        while (temp->sibling)
            temp = temp->sibling;
        temp->sibling = child;
    }
}

 
Node* findChild(Node *parent, const char *name) {
    Node *temp = parent->child;
    while (temp) {
        if (strcmp(temp->name, name) == 0 && temp->isFile == 0)
            return temp;
        temp = temp->sibling;
    }
    return NULL;
}

 
void printTree(Node *root, int level) {
    if (!root)
        return;
    
     
    for (int i = 0; i < level; i++) {
         
        printf("| ");
    }
     
    if (level == 0)
        printf("%s/\n", root->name);
    else {
        if(root->isFile)
            printf("|-- %s\n", root->name);
        else
            printf("|-- %s\n", root->name);
    }
    
     
    printTree(root->child, level + 1);
    
     
    if (level > 0) {  
        printTree(root->sibling, level);
    }
}

 
void freeTree(Node *root) {
    if (!root)
        return;
    freeTree(root->child);
    freeTree(root->sibling);
    free(root);
}

 
void printPath(Node *current) {
    if (current == NULL) {
        printf("/ (root not created)");
        return;
    }
    
     
    char path[MAX_INPUT] = "";
    Node *temp = current;
    
    while (temp != NULL) {
        char tempPath[MAX_INPUT];
        strcpy(tempPath, temp->name);
        strcat(tempPath, "/");
        strcat(tempPath, path);
        strcpy(path, tempPath);
        temp = temp->parent;
    }
    
    printf("/%s", path);
}

 
void processCommand(char *command, char *argument, Node **root, Node **current) {
     
    if (strcmp(command, "mkdir") == 0) {
        if (*root == NULL) {
            *root = createNode(argument, 0, NULL);
            *current = *root;
        } else {
            Node *dir = createNode(argument, 0, *current);
            addChild(*current, dir);
        }
    }
     
    else if (strcmp(command, "create") == 0) {
        if (*current == NULL) {
            printf("Error: No root directory exists. Create one with 'mkdir' first.\n");
        } else {
            Node *file = createNode(argument, 1, *current);
            addChild(*current, file);
        }
    }
     
    else if (strcmp(command, "cd") == 0) {
        if (*current == NULL) {
            printf("Error: No root directory exists. Create one with 'mkdir' first.\n");
        } else {
            if (strcmp(argument, "..") == 0) {
                if ((*current)->parent != NULL)
                    *current = (*current)->parent;
                else
                    printf("Already at root directory.\n");
            } else {
                Node *nextDir = findChild(*current, argument);
                if (nextDir)
                    *current = nextDir;
                else
                    printf("Directory %s not found in current directory.\n", argument);
            }
        }
    }
    else if (strcmp(command, "pwd") == 0) {
        printf("Current path: ");
        printPath(*current);
        printf("\n");
    }
    else {
        printf("Unknown command: %s\n", command);
    }
}

int main() {
    char input[MAX_INPUT];
    char command[MAX_NAME], argument[MAX_NAME];
    Node *root = NULL;
    Node *current = NULL;
    
    printf("Simple File System Shell\n");
    printf("Available commands: mkdir, create, cd, pwd, ls, exit\n");
    
    while (1) {
        printPath(current);

        if (!fgets(input, sizeof(input), stdin)) break;
         
        input[strcspn(input, "\n")] = '\0';

         
        if (strcmp(input, "exit") == 0)
            break;
        
         
        if (sscanf(input, "%s %s", command, argument) < 1) {
            strcpy(command, input);
            argument[0] = '\0';  
        }
        
        processCommand(command, argument, &root, &current);
    }
    
     
    if (root != NULL) {
        printf("\nFile Structure:\n");
        printTree(root, 0);
    } else {
        printf("No file system created.\n");
    }
    
     
    freeTree(root);
    return 0;
}
