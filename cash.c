#include <cs50.h>
#include <stdio.h>

int cal_quarters(int change);
int cal_dimes(int change);
int cal_nickels(int change);
int cal_pennies(int change);

int main(void)
{
    // Getting amount of change from user, in cents
    int change;
    do
    {
        change = get_int("Change owed: ");
    }
    while (change <= 0);

    int quarters = cal_quarters(change);
    change = change - (quarters * 25);
    int dimes = cal_dimes(change);
    change = change - (dimes * 10);
    int nickels = cal_nickels(change);
    change = change - (nickels * 5);
    int pennies = cal_pennies(change);
    change = change - pennies;

    // Printing output
    printf("quarters:%d , dimes:%d , nickels:%d , pennies:%d\n", quarters, dimes, nickels, pennies);
}

// Calculating amount of quarters
int cal_quarters(int change)
{
    int quarters = 0;
    while (change >= 25)
    {
        quarters++;
        change = change - 25;
    }
    return quarters;
}

// Calculating amount of dimes
int cal_dimes(int change)
{
    int dimes = 0;
    while (change >= 10)
    {
        dimes++;
        change = change - 10;
    }
    return dimes;
}

// Calculating amount of nickels
int cal_nickels(int change)
{
    int nickels = 0;
    while (change >= 5)
    {
        nickels++;
        change = change - 5;
    }
    return nickels;
}

// Calculating amount of quarters
int cal_pennies(int change)
{
    int pennies = 0;
    while (change >= 1)
    {
        pennies++;
        change--;
    }
    return pennies;
}
