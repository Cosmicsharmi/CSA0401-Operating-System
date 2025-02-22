#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
int main() 
{
    int fd;
    char buffer[100];
    fd = open("example.txt", O_CREAT | O_WRONLY, 0644);
    if (fd == -1) 
	{
        perror("Error opening file");
        return 1;
    }
    write(fd, "Hello, UNIX System Calls!", 25);
    close(fd);
    fd = open("example.txt", O_RDONLY);
    if (fd == -1) 
	{
        perror("Error opening file");
        return 1;
    }
    read(fd, buffer, 25);
    buffer[25] = '\0';
    printf("File Content: %s\n", buffer);
    lseek(fd, 0, SEEK_SET);
    close(fd);
    return 0;
}
