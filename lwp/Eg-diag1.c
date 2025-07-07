#include "lwp.h"
#include <stdio.h>
#include <conio.h>
#include <dpmi.h>
#include <go32.h>

#define MAX_PROC 4
#define RTC0 0x00

void proc(void *p)
{
    volatile int i;
    int id = *((int *)p);
    while (1) {
        lwpEnterCriticalSection();
        cprintf("Thread %d running\r\n", id);
        lwpLeaveCriticalSection();
        for ( i = 0; i < 20000; i++); // simple delay
    }
}

int main()
{
    int ids[MAX_PROC];
    int thread_ids[MAX_PROC] = {1, 2, 3, 4};
    int i;

    clrscr();
    cprintf("LWP: Simplified Diagnostic Version\r\n");
    cprintf("Using RTC0 for compatibility\r\n");
    cprintf("Press any key to start...\r\n");
    getch();

    if (!lwpInit(RTC0, 1)) {
        cprintf("ERROR: lwpInit() failed!\r\n");
        return 1;
    }

    for (i = 0; i < MAX_PROC; i++) {
        ids[i] = lwpSpawn(proc, &thread_ids[i], 8192, 1, TRUE);
        if (ids[i] < 0) {
            cprintf("ERROR: Failed to spawn thread %d\r\n", i + 1);
        } else {
            cprintf("Spawned thread %d\r\n", thread_ids[i]);
        }
    }

    // Main thread activity
    volatile int j;
    while (!kbhit()) {
        lwpEnterCriticalSection();
        cprintf("MAIN thread active\r\n");
        lwpLeaveCriticalSection();
        for (j = 0; j < 20000; j++);
    }

    getch();

    for (i = 0; i < MAX_PROC; i++) {
        if (ids[i] >= 0) lwpKill(ids[i]);
    }

    cprintf("All threads terminated. Press any key to exit.\r\n");
    getch();
    return 0;
}
