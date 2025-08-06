#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

int main() {
    pid_t c1 = fork();

    if (c1 == 0) {
        pid_t c2 = fork();

        if (c2 == 0) {
            // Grandchild
            printf("[P3 - Grandchild] PID: %d, PPID: %d, Child: None\n", getpid(), getppid());
            printf("Relation: Grandchild\n");
        } else {
            wait(NULL);
            printf("[P2 - Child] PID: %d, PPID: %d, Child: %d\n", getpid(), getppid(), c2);
            printf("Relation: Child/Parent\n");
        }
    } else {
        wait(NULL);
        printf("[P1 - Parent] PID: %d, Child: %d\n", getpid(), c1);
        printf("Relation: Parent/Grandparent\n");
    }

    return 0;
}
