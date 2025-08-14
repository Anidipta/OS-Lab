#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

long long fact(int n) {
    long long f = 1;
    for (int i = 2; i <= n; i++) f *= i;
    return f;
}

int main(int argc, char *argv[]) {
    if (argc != 2) return 1;
    int num = atoi(argv[1]);

    pid_t p1 = fork();

    if (p1 == 0) {
        printf("[P1] PID: %d, PPID: %d, Child: None\n", getpid(), getppid());
        printf("%d! = %lld\n\n", num, fact(num));
        exit(0);
    }

    pid_t p2 = fork();

    if (p2 == 0) {
        long long sum = 0;
        for (int i = 1; i <= num; i++) sum += fact(i);
        printf("[P2] PID: %d, PPID: %d, Child: None\n", getpid(), getppid());
        printf("Sum = %lld\n\n", sum);
        exit(0);
    }

    wait(NULL);
    wait(NULL);
    printf("[Parent] PID: %d, Children: %d, %d\n", getpid(), p1, p2);
    return 0;
}

// Example usage: ./p1 5
// [P1] PID: 25765, PPID: 25764, Child: None
// 5! = 120

// [P2] PID: 25766, PPID: 25764, Child: None
// Sum = 153

// [Parent] PID: 25764, Children: 25765, 25766