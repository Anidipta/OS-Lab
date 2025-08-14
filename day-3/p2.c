#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

int main() {
    pid_t c1 = fork();

    if (c1 == 0) {
        pid_t c2 = fork();

        if (c2 == 0) {
            printf("[P3] PID: %d, PPID: %d, Child: None\n", getpid(), getppid());
            printf("Relation: Grandchild\n");
        } else {
            wait(NULL);
            printf("[P2] PID: %d, PPID: %d, Child: %d\n", getpid(), getppid(), c2);
            printf("Relation: Child/Parent\n");
        }
    } else {
        wait(NULL);
        printf("[P1] PID: %d, Child: %d\n", getpid(), c1);
        printf("Relation: Parent/Grandparent\n");
    }

    return 0;
}

// [P3] PID: 25000, PPID: 24999, Child: None
// Relation: Grandchild
// [P2] PID: 24999, PPID: 24998, Child: 25000
// Relation: Child/Parent
// [P1] PID: 24998, Child: 24999
// Relation: Parent/Grandparent