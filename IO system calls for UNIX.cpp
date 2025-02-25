#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <dirent.h>

int main() {
    int fd;
    struct stat fileStat;
    DIR *dir;
    struct dirent *entry;

    fd = open("example.txt", O_RDWR | O_CREAT, 0644);
    if (fd == -1) {
        perror("Error opening file");
        return 1;
    }

    int flags = fcntl(fd, F_GETFL, 0);
    if (flags == -1) {
        perror("Error getting flags");
        return 1;
    }
    if (fcntl(fd, F_SETFL, flags | O_APPEND) == -1) {
        perror("Error setting flags");
        return 1;
    }

    if (lseek(fd, 10, SEEK_SET) == -1) {
        perror("Error seeking file");
        return 1;
    }

    if (stat("example.txt", &fileStat) == -1) {
        perror("Error getting file stats");
        return 1;
    }
    printf("File size: %lld bytes\n", (long long)fileStat.st_size);

    dir = opendir(".");
    if (dir == NULL) {
        perror("Error opening directory");
        return 1;
    }
    printf("Directory contents:\n");
    while ((entry = readdir(dir)) != NULL) {
        printf("%s\n", entry->d_name);
    }
    closedir(dir);

    close(fd);
    return 0;
}
