#include <cs50.h>
#include <ctype.h>
#include <math.h>
#include <stdio.h>
#include <string.h>

int count_letters(string text);
int count_words(string text);
int count_sentences(string text);

int main(void)
{
    // Prompt the user for some text
    string text = get_string("Text: ");

    // Count the number of letters, words, and sentences in the text
    int letters = count_letters(text);
    int words = count_words(text);
    int sentences = count_sentences(text);

    // Compute the Coleman-Liau index
    float L = ((float) letters / words) * 100.0;
    float S = ((float) sentences / words) * 100.0;
    float index = 0.0588 * L - 0.296 * S - 15.8;

    // Print the grade level
    if (index >= 16)
    {
        printf("Grade 16+\n");
    }
    else if (index < 1)
    {
        printf("Before Grade 1\n");
    }
    else
    {
        printf("Grade %d\n", (int) round(index));
    }
}

int count_letters(string text)
{
    // Return the number of letters in text
    int n = 0;
    for (int i = 0; i < strlen(text); i++)
    {
        char c = text[i];
        if (isupper(c) || islower(c))
        {
            n++;
        }
    }
    return n;
}

int count_words(string text)
{
    // Return the number of words in text
    int n = 0;
    for (int i = 0; i < strlen(text); i++)
    {
        char c = text[i];
        if (isspace(c))
        {
            n++;
        }
    }
    return n + 1;
}

int count_sentences(string text)
{
    // Return the number of sentences in text
    int n = 0;
    for (int i = 0; i < strlen(text); i++)
    {
        char c = text[i];
        if (c == '.' || c == '!' || c == '?')
        {
            n++;
        }
    }
    return n;
}
