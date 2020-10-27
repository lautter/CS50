#include <stdio.h>
#include <cs50.h>

//made by edye lautter

long get_number(void);
int count_number(long n);
bool luh_alg(long n, int size);
string get_flag(long n);

int main(void)
{
    long n = get_number();
    int size = count_number(n);

    if (size != 13 && size != 15 && size != 16)
    {
        printf("INVALID\n");
    }
    else
    {
        if (luh_alg(n, size))
        {
            printf("%s", get_flag(n));
        }

        else
        {
            printf("INVALID\n");
        }
    }

    return 0;
}

string get_flag(long n)
{
    while (n > 100)
    {
        n /= 10;
    }

    if (n / 10 == 4)
    {
        return "VISA\n";
    }
    else if (n == 34 || n == 37)
    {
        return "AMEX\n";
    }
    else if (n == 51 || n == 52 || n == 53 || n == 54 || n == 55)
    {
        return "MASTERCARD\n";
    }
    else
    {
        return "INVALID\n";
    }
}

bool luh_alg(long n, int size)
{
    long mult = 1;
    long sum = 0;
    long sum1 = 0;
    long temp;
    for (int i = 0; i < size; i++)
    {
        temp = 0;
        if (i % 2 != 0)
        {
            temp = 2 * ((n / mult) % 10);
            if (temp >= 10)
            {
                temp = temp % 10 + temp / 10;
            }

            sum += temp;

        }
        else
        {
            temp = (n / mult) % 10;
            sum1 += temp;
        }
        mult *= 10;
    }

    if ((sum + sum1) % 10 == 0)
    {
        return true;
    }
    else
    {
        return false;
    }
}

int count_number(long n)
{
    int count = 0;
    while (n != 0)
    {
        n /= 10;
        count++;
    }
    return count;
}

long get_number(void)
{
    long n = get_long("Number: ");

    return n;
}
