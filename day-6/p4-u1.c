#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/stat.h>

int main() {
    char str1[100], str2[100];
    int fd1, fd2;

    // Clean any old FIFOs
    unlink("fifo1");
    unlink("fifo2");

    // Create fresh FIFOs
    mkfifo("fifo1", 0666);
    mkfifo("fifo2", 0666);

    while (1) {
        // User1 writes message
        fd1 = open("fifo1", O_WRONLY);
        printf("User1: ");
        fgets(str1, sizeof(str1), stdin);
        write(fd1, str1, sizeof(str1));
        close(fd1);

        // Exit if "bye"
        if (strncmp(str1, "bye", 3) == 0) break;

        // User1 reads reply
        fd2 = open("fifo2", O_RDONLY);
        read(fd2, str2, sizeof(str2));
        printf("User2: %s", str2);
        close(fd2);

        if (strncmp(str2, "bye", 3) == 0) break;
    }

    // Clean up
    unlink("fifo1");
    unlink("fifo2");

    return 0;
}
