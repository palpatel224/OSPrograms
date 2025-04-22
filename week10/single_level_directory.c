#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAX_FILES 100
#define NAME_LEN 20

struct Directory
{
    char dirName[NAME_LEN];
    char fileNames[MAX_FILES][NAME_LEN];
    int fileCount;
};

int main()
{
    struct Directory dir;
    int choice, i;
    char temp[NAME_LEN];

    dir.fileCount = 0;
    printf("Enter directory name: ");
    scanf("%19s", dir.dirName);

    while (1)
    {
        printf(
            "\nOperations:\n"
            "1. Create File\n"
            "2. Delete File\n"
            "3. Search File\n"
            "4. List Files\n"
            "5. Exit\n"
            "Enter choice: ");
        if (scanf("%d", &choice) != 1)
            break;

        switch (choice)
        {
        case 1:
            if (dir.fileCount >= MAX_FILES)
            {
                printf("Error: Directory is full.\n");
                break;
            }
            printf("Enter new file name: ");
            scanf("%19s", temp);

            for (i = 0; i < dir.fileCount; i++)
            {
                if (strcmp(temp, dir.fileNames[i]) == 0)
                {
                    printf("Error: '%s' already exists.\n", temp);
                    break;
                }
            }
            if (i == dir.fileCount)
            {
                strcpy(dir.fileNames[dir.fileCount++], temp);
                printf("File '%s' created.\n", temp);
            }
            break;

        case 2:
            if (dir.fileCount == 0)
            {
                printf("Directory is empty.\n");
                break;
            }
            printf("Enter file name to delete: ");
            scanf("%19s", temp);
            for (i = 0; i < dir.fileCount; i++)
            {
                if (strcmp(temp, dir.fileNames[i]) == 0)
                {

                    strcpy(dir.fileNames[i],
                           dir.fileNames[--dir.fileCount]);
                    printf("File '%s' deleted.\n", temp);
                    break;
                }
            }
            if (i == dir.fileCount)
            {
                printf("File '%s' not found.\n", temp);
            }
            break;

        case 3:
            printf("Enter file name to search: ");
            scanf("%19s", temp);
            for (i = 0; i < dir.fileCount; i++)
            {
                if (strcmp(temp, dir.fileNames[i]) == 0)
                {
                    printf("File '%s' found at position %d.\n",
                           temp, i + 1);
                    break;
                }
            }
            if (i == dir.fileCount)
            {
                printf("File '%s' not found.\n", temp);
            }
            break;

        case 4:
            if (dir.fileCount == 0)
            {
                printf("Directory '%s' is empty.\n", dir.dirName);
            }
            else
            {
                printf("\nDirectory: %s\n", dir.dirName);
                for (i = 0; i < dir.fileCount; i++)
                {
                    printf("  %s\n", dir.fileNames[i]);
                }
                printf("Total files: %d\n", dir.fileCount);
            }
            break;

        case 5:
            printf("Exiting.\n");
            exit(0);

        default:
            printf("Invalid choice. Try again.\n");
        }
    }
    return 0;
}
