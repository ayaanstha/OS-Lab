#include <stdio.h>
#include <stdlib.h>

#define MAX 50

void printFrames(int frames[], int n) {
    for (int i = 0; i < n; i++) {
        if (frames[i] == -1)
            printf("- ");
        else
            printf("%d ", frames[i]);
    }
    printf("\n");
}

int isHit(int page, int frames[], int n) {
    for (int i = 0; i < n; i++) {
        if (frames[i] == page)
            return 1;
    }
    return 0;
}

void fifo(int ref[], int n, int frameCount) {
    int frames[frameCount];
    int index = 0, faults = 0;

    for (int i = 0; i < frameCount; i++) frames[i] = -1;

    printf("\nFIFO Page Replacement Process:\n");
    for (int i = 0; i < n; i++) {
        if (!isHit(ref[i], frames, frameCount)) {
            frames[index] = ref[i];
            index = (index + 1) % frameCount;
            faults++;
        }
        printf("PF No. %d: ", i + 1);
        printFrames(frames, frameCount);
    }
    printf("FIFO Page Faults: %d\n", faults);
}

void lru(int ref[], int n, int frameCount) {
    int frames[frameCount];
    int time[frameCount];
    int faults = 0;

    for (int i = 0; i < frameCount; i++) {
        frames[i] = -1;
        time[i] = 0;
    }

    printf("\nLRU Page Replacement Process:\n");
    for (int i = 0; i < n; i++) {
        int found = 0;
        for (int j = 0; j < frameCount; j++) {
            if (frames[j] == ref[i]) {
                time[j] = i;
                found = 1;
                break;
            }
        }
        if (!found) {
            int lruIndex = 0;
            for (int j = 1; j < frameCount; j++) {
                if (time[j] < time[lruIndex])
                    lruIndex = j;
            }
            frames[lruIndex] = ref[i];
            time[lruIndex] = i;
            faults++;
        }
        printf("PF No. %d: ", i + 1);
        printFrames(frames, frameCount);
    }
    printf("LRU Page Faults: %d\n", faults);
}

int predict(int ref[], int frames[], int n, int index, int frameCount) {
    int res = -1, farthest = index;

    for (int i = 0; i < frameCount; i++) {
        int j;
        for (j = index; j < n; j++) {
            if (frames[i] == ref[j]) {
                if (j > farthest) {
                    farthest = j;
                    res = i;
                }
                break;
            }
        }
        if (j == n)
            return i;
    }

    return (res == -1) ? 0 : res;
}

void optimal(int ref[], int n, int frameCount) {
    int frames[frameCount];
    int faults = 0;

    for (int i = 0; i < frameCount; i++) frames[i] = -1;

    printf("\nOptimal Page Replacement Process:\n");
    for (int i = 0; i < n; i++) {
        if (!isHit(ref[i], frames, frameCount)) {
            int j;
            for (j = 0; j < frameCount; j++) {
                if (frames[j] == -1) {
                    frames[j] = ref[i];
                    break;
                }
            }
            if (j == frameCount) {
                int pos = predict(ref, frames, n, i + 1, frameCount);
                frames[pos] = ref[i];
            }
            faults++;
        }
        printf("PF No. %d: ", i + 1);
        printFrames(frames, frameCount);
    }
    printf("Optimal Page Faults: %d\n", faults);
}

int main() {
    int frameCount, len;
    int ref[MAX];

    printf("Enter the number of Frames: ");
    scanf("%d", &frameCount);

    printf("Enter the length of reference string: ");
    scanf("%d", &len);

    printf("Enter the reference string: ");
    for (int i = 0; i < len; i++)
        scanf("%d", &ref[i]);

    fifo(ref, len, frameCount);
    lru(ref, len, frameCount);
    optimal(ref, len, frameCount);

    return 0;
}
