/*Victor Shigueo Okuhama N.USP:10724052*/

#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>

int main()
{
    mapFile();
    return 0;
}

int mapFile()
{
    static const char arquivo[] = "grafo01.txt";
    FILE *file = fopen(arquivo, "r");
    if (file != NULL)
    {
        char ch;
        int num;
        char buffer[32];
        int i = 0;
        int j = 0;
        int arr[100];

        while (1)
        {
            ch = fgetc(file);

            if (ch == EOF)
            {
                break;
            }

            else if (ch == ' ' || ch == '\n')
            {
                arr[j] = atoi(buffer);
                j++;
                bzero(buffer, 32);
                i = 0;

                continue;
            }
            else
            {
                buffer[i] = ch;
                i++;
            }
        }

        for (i = 0; i < j; i++)
        {
            printf("Number [%d]: %d\n", i, arr[i]);
        }

        
    }
}