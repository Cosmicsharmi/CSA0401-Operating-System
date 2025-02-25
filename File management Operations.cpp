#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/stat.h>

int main() {
    int fd;
    char buffer[100];
    struct stat fileStat;

    fd = open("file.txt", O_RDWR | O_CREAT, 0644);
    if (fd == -1) {
        perror("Error opening file");
        return 1;
    }

    write(fd, "Hello, File Management!", 23);
    lseek(fd, 0, SEEK_SET);
    read(fd, buffer, 23);
    buffer[23] = '\0';
    printf("File Content: %s\n", buffer);

    if (stat("file.txt", &fileStat) == 0)
        printf("File Size: %lld bytes\n", (long long)fileStat.st_size);

    close(fd);

    if (rename("file.txt", "new_file.txt") == 0)
        printf("File renamed successfully\n");

    if (remove("new_file.txt") == 0)
        printf("File deleted successfully\n");

    return 0;
}
