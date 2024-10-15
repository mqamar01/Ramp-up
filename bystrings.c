//01005E000009C201172300000800

#include <stdio.h>

void parseheader(char arr[28])
{
    char *temp = arr;
    printf("Destination MAC: ");
    for (int i = 0; i <= 11; i++)
    {
        printf("%c",*temp);
        temp++;
    }
    printf("\nSource MAC: ");
    for (int i = 0; i<=11 ; i++)
    {
        printf("%c",*temp);
        temp++;
    }
    printf("\nHeader: ");
    while (*temp != NULL)
    {
        printf("%c",*temp);
        temp++;
    }
    printf("\n");
}

void typecheck(char arr[28])
{
    char *temp = arr;
    temp++;
    if (*temp % 2 || *temp == 0)
    {
        printf("Header is for unicast.\n");
    }
    else
    {
        printf("Header is for multicast.\n");
    }
}

int main()
{
    char header[28] = "01005E000009C201172300000800";
    parseheader(header);
    typecheck(header);
}
