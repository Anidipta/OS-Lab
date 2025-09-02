#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <string.h>

int main() {
    char str1[100], str2[100];
    int fd1, fd2;

    while (1) {
        // User2 reads first
        fd1 = open("fifo1", O_RDONLY);
        read(fd1, str1, sizeof(str1));
        printf("User1: %s", str1);
        close(fd1);

        if (strncmp(str1, "bye", 3) == 0) break;

        // User2 writes reply
        fd2 = open("fifo2", O_WRONLY);
        printf("User2: ");
        fgets(str2, sizeof(str2), stdin);
        write(fd2, str2, sizeof(str2));
        close(fd2);

        if (strncmp(str2, "bye", 3) == 0) break;
    }

    // Clean up
    unlink("fifo1");
    unlink("fifo2");

    return 0;
}
