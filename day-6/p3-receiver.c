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
    char buffer[BUFFER_SIZE];

    // create the named pipe (FIFO) if not already existing
    mkfifo(FIFO_NAME, 0666);

    // open FIFO for reading
    fd = open(FIFO_NAME, O_RDONLY);
    if (fd < 0) {
        perror("open");
        exit(1);
    }

    // read message
    read(fd, buffer, BUFFER_SIZE);
    printf("Receiver got: %s\n", buffer);

    close(fd);
    return 0;
}
