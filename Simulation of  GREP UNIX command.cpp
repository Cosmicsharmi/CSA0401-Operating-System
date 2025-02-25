#include <stdio.h>
#include <string.h>

int main(int argc, char *argv[]) {
    FILE *file;
    char line[256];

    if (argc != 3) {
        printf("Usage: %s <word> <filename>\n", argv[0]);
        return 1;
    }

    file = fopen(argv[2], "r");
    if (file == NULL) {
        perror("Error opening file");
        return 1;
    }

    while (fgets(line, sizeof(line), file))
        if (strstr(line, argv[1]))
            printf("%s", line);

    fclose(file);
    return 0;
}
