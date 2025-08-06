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
