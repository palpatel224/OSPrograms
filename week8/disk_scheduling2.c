#include <stdio.h>
#include <stdlib.h>

#define MAX 100

void sort(int arr[], int n)
{
    int i, j, temp;
    for (i = 0; i < n - 1; i++)
        for (j = 0; j < n - i - 1; j++)
            if (arr[j] > arr[j + 1])
            {
                temp = arr[j];
                arr[j] = arr[j + 1];
                arr[j + 1] = temp;
            }
}

void c_scan(int requests[], int n, int head, int disk_size)
{
    int i, total_movement = 0;
    int left[MAX], right[MAX];
    int l = 0, r = 0;

    for (i = 0; i < n; i++)
    {
        if (requests[i] < head)
            left[l++] = requests[i];
        else
            right[r++] = requests[i];
    }

    sort(left, l);
    sort(right, r);

    printf("C-SCAN Order:\n");
    for (i = 0; i < r; i++)
    {
        printf("%d ", right[i]);
        total_movement += abs(head - right[i]);
        head = right[i];
    }

    if (l > 0)
    {
        total_movement += abs(head - (disk_size - 1));
        head = 0;
        total_movement += (disk_size - 1);
        for (i = 0; i < l; i++)
        {
            printf("%d ", left[i]);
            total_movement += abs(head - left[i]);
            head = left[i];
        }
    }

    printf("\nTotal head movement: %d\n", total_movement);
}

void look(int requests[], int n, int head)
{
    int i, total_movement = 0;
    int left[MAX], right[MAX];
    int l = 0, r = 0;

    for (i = 0; i < n; i++)
    {
        if (requests[i] < head)
            left[l++] = requests[i];
        else
            right[r++] = requests[i];
    }

    sort(left, l);
    sort(right, r);

    printf("LOOK Order:\n");
    for (i = 0; i < r; i++)
    {
        printf("%d ", right[i]);
        total_movement += abs(head - right[i]);
        head = right[i];
    }

    for (i = l - 1; i >= 0; i--)
    {
        printf("%d ", left[i]);
        total_movement += abs(head - left[i]);
        head = left[i];
    }

    printf("\nTotal head movement: %d\n", total_movement);
}

void c_look(int requests[], int n, int head)
{
    int i, total_movement = 0;
    int left[MAX], right[MAX];
    int l = 0, r = 0;

    for (i = 0; i < n; i++)
    {
        if (requests[i] < head)
            left[l++] = requests[i];
        else
            right[r++] = requests[i];
    }

    sort(left, l);
    sort(right, r);

    printf("C-LOOK Order:\n");
    for (i = 0; i < r; i++)
    {
        printf("%d ", right[i]);
        total_movement += abs(head - right[i]);
        head = right[i];
    }

    if (l > 0)
    {
        total_movement += abs(head - left[0]);
        head = left[0];
        for (i = 0; i < l; i++)
        {
            printf("%d ", left[i]);
            total_movement += abs(head - left[i]);
            head = left[i];
        }
    }

    printf("\nTotal head movement: %d\n", total_movement);
}

void lifo(int requests[], int n, int head)
{
    int i, total_movement = 0;
    int stack[MAX], top = -1;

    for (i = 0; i < n; i++)
        stack[++top] = requests[i];

    printf("LIFO Order:\n");
    while (top >= 0)
    {
        printf("%d ", stack[top]);
        total_movement += abs(head - stack[top]);
        head = stack[top--];
    }

    printf("\nTotal head movement: %d\n", total_movement);
}

int main()
{
    int n, i, head, disk_size;
    int requests[MAX];
    int choice;

    printf("Enter number of requests: ");
    scanf("%d", &n);

    printf("Enter the requests: ");
    for (i = 0; i < n; i++)
        scanf("%d", &requests[i]);

    printf("Enter initial head position: ");
    scanf("%d", &head);

    printf("Enter total disk size: ");
    scanf("%d", &disk_size);

    printf("\nChoose Disk Scheduling Algorithm:\n");
    printf("1. C-SCAN\n2. LOOK\n3. C-LOOK\n4. LIFO\n");
    printf("Enter your choice: ");
    scanf("%d", &choice);

    switch (choice)
    {
    case 1:
        c_scan(requests, n, head, disk_size);
        break;
    case 2:
        look(requests, n, head);
        break;
    case 3:
        c_look(requests, n, head);
        break;
    case 4:
        lifo(requests, n, head);
        break;
    default:
        printf("Invalid choice.\n");
    }

    return 0;
}
