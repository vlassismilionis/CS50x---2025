#include <cs50.h>
#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char encrypting(char c, int key);

int main(int argc, string argv[])
{
    // Make sure program was run with just one command-line argument
    if (argc != 2)
    {
        printf("Usage: ./caesar key\n");
        return 1;
    }

    // Make sure argv[1] contains only digits
    for (int i = 0; argv[1][i] != '\0'; i++)
    {
        if (!isdigit(argv[1][i]))
        {
            printf("Usage: ./caesar key\n");
            return 1;
        }
    }

    // Prompt user for plaintext
    string text = get_string("plaintext:  ");

    // Convert argv[1] from a `string` to an `int`
    int key = atoi(argv[1]);

    // For each character in the plaintext:
    printf("ciphertext: ");
    for (int i = 0, n = strlen(text); i < n; i++)
    {
        char c = text[i];
        if (isalpha(c))
        {
            char cipherchar = encrypting(c, key);
            printf("%c", cipherchar);
        }
        else
        {
            printf("%c", c);
        }
    }
    printf("\n");
}

// Encryption proccess
char encrypting(char c, int key)
{
    if (isupper(c))
    {
        c -= 65; // Converting ASCII (A=65 B=66 ...) to Alphabetical index (A=0 B=1 ...)
        char e = (c + key) % 26; // Formula so Z wraps around to A
        e += 65;                 // Converting encrypted character back to ASCII format
        return e;
    }
    else if (islower(c))
    {
        c -= 97; // Converting ASCII (a=97 b=98 ...) to Alphabetical index (a=0 b=1 ...)
        char e = (c + key) % 26; // Formula so z wraps around to a
        e += 97;                 // Converting encrypted character back to ASCII format
        return e;
    }
    return c;
}
