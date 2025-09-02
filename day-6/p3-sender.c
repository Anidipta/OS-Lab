#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

#define FIFO_NAME "myfifo"
#define BUFFER_SIZE 100

int main() {
    int fd;
    char message[BUFFER_SIZE] = "his last wish";

    // create the named pipe (FIFO)
    mkfifo(FIFO_NAME, 0666);

    // open FIFO for writing
    fd = open(FIFO_NAME, O_WRONLY);
    if (fd < 0) {
        perror("open");
        exit(1);
    }

    // write message
    write(fd, message, strlen(message) + 1);
    printf("Sender sent: %s\n", message);

    close(fd);
    return 0;
}
