#include <stdio.h>
#include <stdlib.h>

#define MAX_FRAMES 100
#define MAX_REFERENCES 1000

int isPageInFrames(int frames[], int n_frames, int page)
{
    for (int i = 0; i < n_frames; i++)
    {
        if (frames[i] == page)
            return i;
    }
    return -1;
}

void MRU(int pages[], int n_pages, int n_frames)
{
    int frames[MAX_FRAMES];
    int last_used[MAX_FRAMES];
    int time = 0;
    int page_faults = 0;

    for (int i = 0; i < n_frames; i++)
    {
        frames[i] = -1;
        last_used[i] = -1;
    }

    for (int i = 0; i < n_pages; i++)
    {
        int page = pages[i];
        int index = isPageInFrames(frames, n_frames, page);

        if (index != -1)
        {

            last_used[index] = time;
        }
        else
        {

            page_faults++;
            int mru_index = -1;
            int max_time = -1;

            for (int j = 0; j < n_frames; j++)
            {
                if (frames[j] != -1 && last_used[j] > max_time)
                {
                    max_time = last_used[j];
                    mru_index = j;
                }
            }

            int empty_index = isPageInFrames(frames, n_frames, -1);
            if (empty_index != -1)
            {
                frames[empty_index] = page;
                last_used[empty_index] = time;
            }
            else if (mru_index != -1)
            {

                frames[mru_index] = page;
                last_used[mru_index] = time;
            }
        }
        time++;
    }

    printf("MRU Page Faults: %d\n", page_faults);
}

void NFU(int pages[], int n_pages, int n_frames)
{
    int frames[MAX_FRAMES];
    int counters[MAX_FRAMES];
    int page_faults = 0;

    for (int i = 0; i < n_frames; i++)
    {
        frames[i] = -1;
        counters[i] = 0;
    }

    for (int i = 0; i < n_pages; i++)
    {
        int page = pages[i];
        int index = isPageInFrames(frames, n_frames, page);

        if (index != -1)
        {

            counters[index]++;
        }
        else
        {

            page_faults++;
            int min_count = __INT_MAX__;
            int replace_index = -1;

            for (int j = 0; j < n_frames; j++)
            {
                if (frames[j] == -1)
                {
                    replace_index = j;
                    break;
                }
                else if (counters[j] < min_count)
                {
                    min_count = counters[j];
                    replace_index = j;
                }
            }

            frames[replace_index] = page;
            counters[replace_index] = 1;
        }
    }

    printf("NFU Page Faults: %d\n", page_faults);
}

int main()
{
    int pages[MAX_REFERENCES];
    int n_pages, n_frames;

    printf("Enter the number of page references: ");
    scanf("%d", &n_pages);

    printf("Enter the page reference sequence:\n");
    for (int i = 0; i < n_pages; i++)
    {
        scanf("%d", &pages[i]);
    }

    printf("Enter the number of frames: ");
    scanf("%d", &n_frames);

    MRU(pages, n_pages, n_frames);
    NFU(pages, n_pages, n_frames);

    return 0;
}
