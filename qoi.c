#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

typedef unsigned char unchar;

typedef unsigned long un;

typedef struct
{
    unchar *data;
    un len;
} vec;

typedef struct
{
    char magic[4];      // magic bytes "qoif"
    uint32_t width;     // image width in pixels (BE)
    uint32_t height;    // image height in pixels (BE)
    uint8_t channels;   // 3 = RGB, 4 = RGBA
    uint8_t colorspace; // 0 = sRGB with linear alpha, 1 = all channels linear
} qoi_header;

char *read_file(const char *path)
{
    FILE *f = fopen(path, "r");
    if (f == NULL)
        return 0;

    fseek(f, 0, SEEK_END);
    size_t size = ftell(f);
    fseek(f, 0, SEEK_SET);

    char *buffer = (char *)malloc(size);

    fread(buffer, size, 1, f);
    fclose(f);

    return buffer;
}

vec read_file_bin(const char *path)
{
    FILE *f = fopen(path, "rb");
    if (f == NULL)
    {
        vec r = {0, 0};
        return r;
    }

    fseek(f, 0, SEEK_END);
    size_t size = ftell(f);
    fseek(f, 0, SEEK_SET);

    unchar *buffer = (unchar *)malloc(size);

    fread(buffer, size, 1, f);
    fclose(f);

    vec res = {buffer, size};
    return res;
}

un write_to_file(const char *path, char *data, size_t size)
{
    FILE *f = fopen(path, "w");
    if (f == 0)
        return 0;
    fwrite(data, size, 1, f);
    fclose(f);
    return 1;
}

void print_unchar(unchar *d, size_t len)
{
    for (un i = 0; i < len; i++)
    {
        printf("%i ", d[i]);
    }
    printf("\n");
}

// unchar *qoi_encode(unchar *data) {}

// unchar* qoi_decode() {}

// unchar* qoi_read() {}

// unchar* qoi_write() {}

int main(int argc, char *argv[])
{
    char *a = read_file("data.txt");
    if (a == 0)
    {
        printf("Null Pointer!\n");
        return 1;
    }

    vec b = read_file_bin("data.txt");
    if (b.data == 0)
    {
        printf("Null Pointer!\n");
        return 1;
    }

    print_unchar(b.data, b.len);
    printf("%s\n", a);
    return 0;
}
