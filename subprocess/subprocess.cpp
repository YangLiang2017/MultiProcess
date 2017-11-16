// subprocess.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"

/*
int _tmain(int argc, _TCHAR* argv[])
{


	
	return 0;
}*/


#define WIN32_LEAN_AND_MEAN
#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include <assert.h>


DWORD WINAPI ThreadFunc(LPVOID);

#define THREAD_POOL_SIZE 3
#define MAX_THREAD_INDEX THREAD_POOL_SIZE-1
#define NUM_TASKS 3

int main()
{
    HANDLE  hThrds[THREAD_POOL_SIZE];
    int     slot = 0;
    DWORD   threadId;
    int     i;
    DWORD   rc;

    for (i=0; i<NUM_TASKS; i++)
    {
        /* Until we've used all threads in *
         * the pool, do not need to wait   *
         * for one to exit                 */
      
        /* Create a new thread in the given
         * available slot */
         hThrds[slot] = CreateThread(NULL,
            0,
            ThreadFunc,
            (LPVOID)slot,
            0,
            &threadId ) ;
        printf("Launched thread #%d (slot %d)\n", i, slot);
        slot++;
    }

    /* Now wait for all threads to terminate */
    rc = WaitForMultipleObjects(
        THREAD_POOL_SIZE,
        hThrds,
        TRUE,
        INFINITE );
    assert( rc >= WAIT_OBJECT_0
             && rc < WAIT_OBJECT_0+THREAD_POOL_SIZE);
    for (slot=0; slot<THREAD_POOL_SIZE; slot++)
         CloseHandle(hThrds[slot]) ;
    printf("All slots terminated\n");

    return EXIT_SUCCESS;
}


DWORD WINAPI ThreadFunc(LPVOID n)
{
    srand( GetTickCount() );

    Sleep((rand()%10)*800+500);
    printf("Slot %d idle %d\n", n,(rand()%10)*800+500);
    return ((DWORD)n);
}
