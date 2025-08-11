#include <cs50.h>
#include <stdio.h>

void print_row(int bricks);
void print_spaces(int j);

int main(void)
{
    // Getting height from user
    int height;
    do
    {
        height = get_int("Type your desired height: ");
    }
    while (height <= 0 || height >= 9);

    // Printing the pyramid
    for (int i = 0; i < height; i++)
    {
        print_spaces((height - 1) - i);
        print_row(i + 1);
    }
}

// Function for printing required amount of spaces *based on given height
void print_spaces(int j)
{
    for (int a = 0; a < j; a++)
    {
        printf(" ");
    }
}

// Function for printing required amount of bricks
void print_row(int bricks)
{
    for (int i = 0; i < bricks; i++)
    {
        printf("#");
    }
    printf("  ");
    for (int i = 0; i < bricks; i++)
    {
        printf("#");
    }
    printf("\n");
}
