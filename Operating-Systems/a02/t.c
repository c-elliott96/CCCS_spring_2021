#include <stdio.h>
#include "thread_lib/thread.h"

static thread_t thread1;
static thread_t thread2;

static void t1(int n);
static void t2();

int main(int argc, char **argv) {
    thread_create(&thread1, &t1, 0);
    thread_create(&thread2, &t2, 0);

    thread_join(thread1);
    thread_join(thread2);
    printf("Exiting main ....\n");
    return 0;
}

void t1(int n) {
    printf("In t1\n");
    while (1) {
        ++n;
        if (n % 10000000 == 0) {
            printf(".");
        }
    }
    thread_exit(n);
}

void t2(int n) {
    printf("In t2\n");
    while (1) {
        printf("Give me some text: ");
        char inp[10];
        fgets(inp, 10, stdin);
        printf("Thank you for your input.\n");
    }
    thread_exit(n);
}
