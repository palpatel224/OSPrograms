#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAX_NODES 100
#define NAME_LEN 32
#define INDENT_STEP 2

char names[MAX_NODES][NAME_LEN];
int is_directory[MAX_NODES];
int adj[MAX_NODES][MAX_NODES];
int node_count = 0;

int find_index(const char *name)
{
    for (int i = 0; i < node_count; i++)
    {
        if (strcmp(names[i], name) == 0)
            return i;
    }
    return -1;
}

void add_node(int parent_idx, const char *new_name, int dir_flag)
{
    if (node_count >= MAX_NODES)
    {
        printf("Error: node limit reached.\n");
        return;
    }

    int idx = node_count++;
    strncpy(names[idx], new_name, NAME_LEN - 1);
    names[idx][NAME_LEN - 1] = '\0';
    is_directory[idx] = dir_flag;

    adj[parent_idx][idx] = 1;
}

void display_subtree(int idx, int level)
{

    for (int i = 0; i < level * INDENT_STEP; i++)
        putchar(' ');

    printf("|-- %s%s\n", names[idx], is_directory[idx] ? "/" : "");

    for (int child = 0; child < node_count; child++)
    {
        if (adj[idx][child])
        {
            display_subtree(child, level + 1);
        }
    }
}

int main()
{

    strncpy(names[0], "root", NAME_LEN);
    is_directory[0] = 1;
    node_count = 1;
    memset(adj, 0, sizeof(adj));

    while (1)
    {
        printf("\n1. Create Directory\n");
        printf("2. Create File\n");
        printf("3. Display Tree\n");
        printf("4. Exit\n");
        printf("Enter choice: ");

        int choice;
        if (scanf("%d", &choice) != 1)
            break;

        if (choice == 4)
        {
            break;
        }
        else if (choice == 1 || choice == 2)
        {
            char parent_name[NAME_LEN], new_name[NAME_LEN];
            printf("Enter parent directory name: ");
            scanf("%s", parent_name);
            printf("Enter new %s name: ",
                   (choice == 1) ? "directory" : "file");
            scanf("%s", new_name);

            int pidx = find_index(parent_name);
            if (pidx < 0 || !is_directory[pidx])
            {
                printf("Error: parent directory '%s' not found.\n",
                       parent_name);
            }
            else
            {

                if (find_index(new_name) >= 0)
                {
                    printf("Error: a node named '%s' already exists.\n",
                           new_name);
                }
                else
                {
                    add_node(pidx, new_name, (choice == 1));
                    printf("%s '%s' created under '%s'.\n",
                           (choice == 1) ? "Directory" : "File",
                           new_name, parent_name);
                }
            }
        }
        else if (choice == 3)
        {
            printf("\nCurrent File Tree:\n");
            display_subtree(0, 0);
        }
        else
        {
            printf("Invalid choice. Try again.\n");
        }
    }

    printf("Exiting.\n");
    return 0;
}
