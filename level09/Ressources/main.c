#include <stdio.h>
#include <fcntl.h>

int main(int ac, char** av)
{
        if (ac != 2)
                return 0;
        char buf[256];
        int fd = open(av[1], O_RDONLY);
        read(fd, buf, 255);
        buf[256] = '\0';
        for (int i = 0; buf[i]; i++)
                buf[i] -= i;
        printf("%s\n", buf);
}