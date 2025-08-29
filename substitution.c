#include <cs50.h>
#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, string argv[])
{
    // Make sure program was run with just one command-line argument
    if (argc != 2)
    {
        printf("Usage: ./substitution key\n");
        return 1;
    }

    // Make sure key insists of 26 characters
    if (strlen(argv[1]) != 26)
    {
        printf("Key must contain 26 characters.\n");
        return 1;
    }

    // Make sure all characters all alphabetic
    for (int i = 0; argv[1][i] != '\0'; i++)
    {
        if (!isalpha(argv[1][i]))
        {
            printf("Key must only contain alphabetic characters.\n");
            return 1;
        }
    }

    // Make sure there is no repeated letters in the key
    for (int i = 0; argv[1][i] != '\0'; i++)
    {
        for (int j = i + 1; argv[1][j] != '\0'; j++)
        {
            // Converting everything to lowercase or uppercase to check for mixed duplicates (e.g. ..Pp...)
            if (tolower(argv[1][i]) == tolower(argv[1][j]))
            {
                printf("Key must not contain repeated characters.\n");
                return 1;
            }
        }
    }

    // Prompt user for plaintext
    string text = get_string("plaintext:  ");

    // Encipher
    printf("ciphertext: ");
    for (int i = 0, n = strlen(text); i < n; i++)
    {
        char c = text[i];
        if (isalpha(c))
        {
            if (isupper(c))
            {
                int index = c - 65; // Converting ASCII (A=65 B=66 ...) to Alphabetical index (A=0 B=1 ...)
                char e = toupper(argv[1][index]); // Locating corresponding letter
                printf("%c", e);
            }
            else if (islower(c))
            {
                int index = c - 97; // Converting ASCII (a=97 b=98 ...) to Alphabetical index (a=0 b=1 ...)
                char e = tolower(argv[1][index]); // Locating corresponding letter
                printf("%c", e);
            }
        }
        else
        {
            printf("%c", c);
        }
    }
    printf("\n");
}
