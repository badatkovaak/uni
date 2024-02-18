#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>

typedef unsigned long un;

const size_t SIZE = 64;

char *read_file(const char *path, size_t size) {
    char *buffer = (char *)malloc(1024);
    FILE *f = fopen(path, "r");
    if (f == NULL) return 0;
    fread(buffer, size, 1, f);
    fclose(f);
    return buffer;
}

un write_to_file(const char *path, char *data, size_t size) {
    FILE *f = fopen(path, "w");
    if (f == 0) return 0;
    fwrite(data, size, 1, f);
    fclose(f);
    return 1;
}

void print_as_int(char *data, size_t size) {
    for (un i = 0; i < size; i++) {
        if (data[i] == 10)
            printf("\n");
        else if (data[i] != 0)
            printf("%d ", data[i] + 128);
    }
    printf("\n");
}

// void process_data(char *data, size_t size)
// {
//     for (un i = 0; i < size; i++)
//     {
// if (data[i] != 0 && data[i] != 10)
//             // data[i] += 128;
//     }
// }

int main(int argc, char *argv[]) {
    char *buffer = read_file("data.txt", SIZE);
    printf("%s\n", buffer);
    // process_data(buffer, SIZE);
    // write_to_file("data.txt", buffer, SIZE);
    // print_as_int(buffer, 64);
    return 0;
}
