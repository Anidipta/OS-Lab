#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>

#define BUFFER_SIZE 100
#define READ_END 0
#define WRITE_END 1

int main() {
    char wr_msg[BUFFER_SIZE] = "his last wish";
    char rd_msg[BUFFER_SIZE];
    char send_back[BUFFER_SIZE];
    int fd1[2], fd2[2];
    pid_t p1;

    if (pipe(fd1) == -1 || pipe(fd2) == -1) {
        fprintf(stderr, "Pipe failed\n");
        return 1;
    }

    p1 = fork();
    if (p1 < 0) {
        fprintf(stderr, "Fork failed\n");
        return 1;
    }

    if (p1 > 0) {  
        close(fd1[READ_END]); close(fd2[WRITE_END]);  
        // write to child
        write(fd1[WRITE_END], wr_msg, strlen(wr_msg) + 1);
        close(fd1[WRITE_END]);
        // read response from child
        read(fd2[READ_END], rd_msg, BUFFER_SIZE);
        printf("Parent received from child: %s\n", rd_msg);
        close(fd2[READ_END]);
    } else { 
        close(fd1[WRITE_END]);close(fd2[READ_END]);  
        // read from parent
        read(fd1[READ_END], rd_msg, BUFFER_SIZE);
        printf("Child tells: %s\n", rd_msg);
        close(fd1[READ_END]);
        // prepare response with child PID
        snprintf(send_back, BUFFER_SIZE, "Message: %s | Child PID: %d", rd_msg, getpid());
        // send back to parent
        write(fd2[WRITE_END], send_back, strlen(send_back) + 1);
        close(fd2[WRITE_END]);
    }

    return 0;
}

// ./p2
// Child tells: his last wish
// Parent received from child: Message: his last wish | Child PID: 25907