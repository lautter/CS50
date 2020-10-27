#include <cs50.h>
#include <stdio.h>
#include <ctype.h>
#include <math.h>
#include <string.h>

bool key_validation(string key);
void encrypt(string s, string key);

int main(int argc, string argv[])
{
    string key = argv[1];

    if (argc != 2)
    {
        printf("Usage: ./substitution key\n");

        return 1;
    }

    if (!key_validation(key))
    {
        return 1;
    }

    string s = get_string("plaintext: ");

    encrypt(s, key);

    return 0;
}

void encrypt(string s, string key)
{
    int k = 0;
    printf("ciphertext: ");
    for (int n = 0; s[n] != '\0'; n++)
    {
        if (!isalpha(s[n]))
        {
            printf("%c", s[n]);
            continue;
        }

        if (isupper(s[n]))
        {
            s[n] = tolower(s[n]);
            k = (int)s[n] - 97;
            printf("%c", toupper(key[k]));
        }

        else
        {
            k = (int)s[n] - 97;
            printf("%c", tolower(key[k]));
        }
    }
    printf("\n");
}

bool key_validation(string key)
{
    for (int n = 0; key[n] != '\0'; n++)
    {
        if (!isalpha(key[n]))
        {
            printf("Usage: ./substitution key\n");

            return false;
        }
        for (int j = n + 1; key[j] != '\0'; j++)
        {
            if (key[n] == key[j])
            {
                printf("Key char's can't be repeated\n");
                return false;
            }
        }
    }

    if (strlen(key) != 26)
    {
        printf("Key must contain 26 characters.\n");

        return false;
    }

    return true;
}