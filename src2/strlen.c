// Determines the length of a string

#include <cs50.h>
#include <stdio.h>
#include <ctype.h>

int main(void)
{
    // Prompt for user's name
    string s = get_string("Name: ");

    // Count number of characters up until '\0' (aka NUL)
    int n = 0;
    int count = 0;
    while (s[n] != '\0')
    {
        if (isalpha(s[n]))
        {
            count++;
        }
        n++;
    }
    printf("%i\n", count);
}
