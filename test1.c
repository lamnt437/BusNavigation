#include <stdio.h>
#include <string.h>
int nextHandle(char *token)
{
    char *token0 = strdup(token);
    char *ptr, *ptr2;
    char *token1 = strtok_r(token0, ";", &ptr);
    int i = 0;
    while (token1 != NULL)
    {
        i++;
        if (i >= 2 && i <= 3)
        {
            char *token2 = strtok_r(token1, "-", &ptr2);
            while (token2 != NULL)
            {
                printf("test: %s\n", token2);
                token2 = strtok_r(NULL, "-", &ptr2);
            }
        }
        // printf(" test: %s\n", token1); //printing each token
        token1 = strtok_r(NULL, ";", &ptr);
    }
}
int main(int argc, char **argv)
{
    FILE *fp;
    char *buffer[150000];
    char *ptr1;
    fp = fopen("test12.txt", "r");
    fread(buffer, 1500000, 1, fp);
    //char *token = strtok_r(buffer, "\n\n", &ptr1);
    printf("test: %s\n", buffer);
    fclose(fp);
    // while (token != NULL)
    // {
    //     // loop through the string to extract all other tokens
    //     // char *token1 = strtok(token, ";");
    //     // while (token1 != NULL)
    //     // {
    //     //     printf(" %s\n", token1); //printing each token
    //     //     token1 = strtok(NULL, ";");
    //     // }
    //     // token = strtok(NULL, "\n\n");
    //     // char *token1 = strtok(token, ";");
    //     // printf(" tadat: %s\n", token1);
    //     // printf(" data: %s\n", token);
    //     nextHandle(token);
    //     //printf(" data: %s\n", token);
    //     token = strtok_r(NULL, "\n\n", &ptr1);
    //}
    return 0;
}