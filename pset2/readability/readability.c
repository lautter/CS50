#include <cs50.h>
#include <stdio.h>
#include <ctype.h>
#include <math.h>

//counting sentences
float count_sentences(string s);
float count_words(string s);
float count_letters(string s);
float get_index(float L, float S);

//made by edye lautter

int main(void)
{
    string s = get_string("Text: ");

    float letters = count_letters(s);
    float words = count_words(s) + 1;
    float sentences = count_sentences(s);
    float L = (letters * 100) / words;
    float S = (sentences * 100) / words;
    int index = round(get_index(L, S));

    if (index > 16)
    {
        printf("Grade 16+\n");

        return 0;
    }

    else if (index < 1)
    {
        printf("Before Grade 1\n");

        return 0;
    }

    printf("Grade %i\n", index);

    return 0;
}

// Function that gets the Coleman-Liau index
float get_index(float L, float S)
{
    float index = 0.0588 * L - 0.296 * S - 15.8;

    return index;
}

//function that counts sentences
float count_sentences(string s)
{
    int count = 0;
    int n = 0;
    while (s[n] != '\0')
    {
        if (s[n] == '.' || s[n] == '!' || s[n] == '?')
        {
            count++;
        }
        n++;
    }
    return count;
}

//function that counts words
float count_words(string s)
{
    int count = 0;
    int n = 0;

    while (s[n] != '\0')
    {
        if (isspace(s[n]))
        {
            count++;
        }
        n++;
    }

    return count;
}

//function that counts letters
float count_letters(string s)
{
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

    return count;
}