/*
 *  https://gist.githubusercontent.com/ccbrown/9722406/raw/05202cd8f86159ff09edc879b70b5ac6be5d25d0/DumpHex.c
 */
#include <stdio.h>
#include <unistd.h>

void DumpHex(const void* data, size_t size)
{
    char ascii[17];
    size_t i, j;
    ascii[16] = '\0';
    for (i = 0; i < size; ++i)
    {
        printf("%02X ", ((unsigned char*)data)[i]);
        if (((unsigned char*)data)[i] >= ' ' && ((unsigned char*)data)[i] <= '~')
        {
            ascii[i % 16] = ((unsigned char*)data)[i];
        }
        else
        {
            ascii[i % 16] = '.';
        }
        if ((i+1) % 8 == 0 || i+1 == size)
        {
            printf(" ");
            if ((i+1) % 16 == 0)
            {
                printf("|  %s \n", ascii);
            }
            else if (i+1 == size)
            {
                ascii[(i+1) % 16] = '\0';
                if ((i+1) % 16 <= 8)
                {
                    printf(" ");
                }
                for (j = (i+1) % 16; j < 16; ++j)
                {
                    printf("   ");
                }
                printf("|  %s \n", ascii);
            }
        }
    }
}


int main( int argc, char** argv )
{
    char buffer[4096];
    int len = 0;
    while( (len = read(STDIN_FILENO, buffer, sizeof(buffer))) > 0 )
    {
        DumpHex( buffer, len );
    }
    return 0;
}

