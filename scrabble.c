#include <cs50.h>
#include <ctype.h>
#include <stdio.h>
#include <string.h>

int score(string s);

int main(void)
{
    // Promtpt the user for two words

    string words[2];
    int scores[2];

    words[0] = get_string("Player 1: \n");
    words[1] = get_string("Player 2: \n");

    scores[0] = score(words[0]);
    scores[1] = score(words[1]);

    if (scores[0] > scores[1])
    {
        printf("Player 1 wins!\n");
    }
    else if (scores[0] < scores[1])
    {
        printf("Player 2 wins!\n");
    }
    else
    {
        printf("Tie!\n");
    }
}

int score(string s)
{
    // Calculating scores

    int sum = 0;
    for (int i = 0; i < strlen(s); i++)
    {
        char c = toupper(s[i]);
        switch (c)
        {
            case 'A':
            case 'E':
            case 'I':
            case 'L':
            case 'N':
            case 'O':
            case 'R':
            case 'S':
            case 'T':
            case 'U':
                sum += 1;
                break;
            case 'D':
            case 'G':
                sum += 2;
                break;
            case 'B':
            case 'C':
            case 'M':
            case 'P':
                sum += 3;
                break;
            case 'F':
            case 'H':
            case 'V':
            case 'W':
            case 'Y':
                sum += 4;
                break;
            case 'K':
                sum += 5;
                break;
            case 'J':
            case 'X':
                sum += 8;
                break;
            case 'Q':
            case 'Z':
                sum += 10;
                break;
        }
    }
    return sum;
}