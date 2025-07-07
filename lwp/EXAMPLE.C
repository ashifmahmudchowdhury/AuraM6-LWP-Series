#include "lwp.h"
#include <stdio.h>
#include <dpmi.h>
#include <dos.h>
#include <conio.h>

#define MAX_PROC 4 

void proc(void *p)
{
    int id = *((int *)p);
    char *vidmem = (char *)0xB8000;
    int row = id;  // line per thread
    int col = 0;
    char ch = '0' + id;

    while(1)
    {
        volatile int i;
        // Write "PROC <id>" on its own line
        int offset = (row * 80 + col) * 2;
        // vidmem[offset] = ch;
        // vidmem[offset + 1] = 0x1F; // white on blue
        lwpEnterCriticalSection();
        cprintf("Thread %d running\r\n", id);
        lwpLeaveCriticalSection();
        col = (col + 1) % 70;      // wrap within line
        for (i = 0; i < 5000; i++); // delay
    }
}

int main()
{
    volatile int i;
    int ids[MAX_PROC];
    int a = 1, b = 2, c = 3, d = 4;

    clrscr();
    printf("\nLWP: Diagnostic Version of Example1.\n");
    printf("Each thread writes to a unique screen line.\n");
    printf("Press any key to start....");
    fflush(stdout);
    getch();

    if (!lwpInit(RTC1024, 1)) {
        printf("LWP INIT FAILED!\n");
        return 1;
    }

    ids[0] = lwpSpawn(proc, &a, 4096, 1, TRUE);
    ids[1] = lwpSpawn(proc, &b, 4096, 1, TRUE);
    ids[2] = lwpSpawn(proc, &c, 4096, 1, TRUE);
    ids[3] = lwpSpawn(proc, &d, 4096, 1, TRUE);

    // main thread shows "M" moving on line 0
    int col = 0;
    while(!kbhit())
    {
        char *vidmem = (char *)0xB8000;
        int offset = (0 * 80 + col) * 2;
        // vidmem[offset] = 'M';
        // vidmem[offset + 1] = 0x2E; // cyan on black
        lwpEnterCriticalSection();
        cprintf("MAIN\r\n");
        lwpLeaveCriticalSection();
        col = (col + 1) % 70;
        for (i = 0; i < 5000; i++);
    }

    getch();
    for (i = 0; i < MAX_PROC; i++)
        lwpKill(ids[i]);

    return 0;
}
