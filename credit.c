#include <cs50.h>
#include <stdio.h>

int length(long number);
int checksum(long card, char str[]);

int main(void)
{
    // Getting card number from user
    long card;
    card = get_long("Number: ");

    // Converting long variable to string
    char str[16];
    sprintf(str, "%ld", card);

    // Pinpointing card type
    if (str[0] == '4' && (length(card) == 13 || length(card) == 16))
    {
        checksum(card, str);
    }
    else if ((str[0] == '3' && str[1] == '4' && length(card) == 15) ||
             (str[0] == '3' && str[1] == '7' && length(card) == 15))
    {
        printf("AMEX\n");
    }
    else if (str[0] == '5' && length(card) == 16 &&
             (str[1] == '1' || str[1] == '2' || str[1] == '3' || str[1] == '4' || str[1] == '5'))
    {
        printf("MASTERCARD\n");
    }
    else
    {
        printf("INVALID\n");
    }
}

// Function for calculating length of card number
int length(long number)
{
    int count = 0;
    while (number > 0)
    {
        number /= 10;
        count++;
    }
    return count;
}

// Checking validation of "visa" card
int checksum(long card, char str[])
{
    int len = length(card);
    if (len == 13 || len == 16)
    {
        int sum_multiply = 0;
        int sum_other = 0;

        for (int i = 0; i < len; i++)
        {
            int digit = str[i] - '0';

            if (i % 2 == (len % 2 == 0 ? 0 : 1))
            {
                int product = digit * 2;
                sum_multiply += (product / 10) + (product % 10);
            }
            else
            {
                sum_other += digit;
            }
        }

        int total = sum_multiply + sum_other;

        if (total % 10 == 0)
        {
            printf("VISA\n");
            return 1;
        }
        else
        {
            printf("INVALID\n");
        }
    }
    return 0;
}
