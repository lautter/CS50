#include <cs50.h>
#include <stdio.h>
//made by Edye Lautter
int get_height(void);
int print_pyramid(int n);

int main(void)
{
    int n;
    n = get_height();

    print_pyramid(n);

    return 0;
}

int print_pyramid(int n)
{
    int i, j, k, spaces, spaceL, spaceR;
    spaces = n-1;

    for(i = 0; i < n; i++)
    {
        spaceL = spaces;
        spaceR = n - spaces;
        for(j = 0; j < n; j++)
        {
            if(spaceL == 0) printf("#");
            else{
                printf(" ");
                spaceL--;
            }
        }
        printf("  ");
        for(k = 0; k < spaceR; k++)
        {
            printf("#");
        }
        printf("\n");
        spaces--;
    }

    return 0;
}

int get_height(void)
{
    int n;
    do
    {
      n = get_int("height:\n");
    }while(n > 8 || n < 1);

    return n;
}
