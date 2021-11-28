#include "header.h"

#define BUFFER_SIZE 100000

int main(int argc, char const *argv[])
{
    if (argc != 2)
    {
        printf("Usage: ./a.out <file>\n");
        return 1;
    }
    FILE *fp = fopen(argv[1], "r");
    if (fp == NULL)
    {
        printf("File not found\n");
        return 1;
    }
    char *buffer = (char *)malloc(sizeof(char) * BUFFER_SIZE);
    int read_size = fread(buffer, sizeof(char), BUFFER_SIZE, fp);
    byte output[32];
    SHA256((byte *)buffer, read_size, output);

    cout << "The Hash is : ";
    for (int i = 0; i < 32; i++)
    {
        printf("%02x", output[i]);
    }
    cout << endl;

    return 0;
}