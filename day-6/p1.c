#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#define BUFFER_SIZE 25
#define READ_END 0
#define WRITE_END 1

int main() {
    char wr_msg[BUFFER_SIZE] = "his last wish";
    char rd_msg[BUFFER_SIZE];
    int fd[2];
    pid_t p1;

    // create pipe
    if (pipe(fd) == -1) {
        fprintf(stderr, "Pipe failed\n");
        return 1;
    }

    // fork a child process
    p1 = fork();
    if (p1 < 0) {
        fprintf(stderr, "Fork failed\n");
        return 1;
    }

    if (p1 > 0) {  
        // parent process
        close(fd[READ_END]);  // close unused read end
        write(fd[WRITE_END], wr_msg, strlen(wr_msg) + 1);
        close(fd[WRITE_END]);
    } else {  
        // child process
        close(fd[WRITE_END]);  // close unused write end
        read(fd[READ_END], rd_msg, BUFFER_SIZE);
        printf("Child tells: %s\nPID: %d\n", rd_msg, getpid());
        close(fd[READ_END]);
    }

    return 0;
}


// ./p1
// Child tells: his last wish
// PID: 25638