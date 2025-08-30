#include <cs50.h>
#include <stdio.h>
#include <string.h>

// Max number of candidates
#define MAX 9

// Candidates have name and vote count
typedef struct
{
    string name;
    int votes;
} candidate;

// Array of candidates
candidate candidates[MAX];

// Number of candidates
int candidate_count;

// Function prototypes
bool vote(string name);
void print_winner(void);

int main(int argc, string argv[])
{
    // Check for invalid usage
    if (argc < 2)
    {
        printf("Usage: plurality [candidate ...]\n");
        return 1;
    }

    // Populate array of candidates
    candidate_count = argc - 1;
    if (candidate_count > MAX)
    {
        printf("Maximum number of candidates is %i\n", MAX);
        return 2;
    }
    for (int i = 0; i < candidate_count; i++)
    {
        candidates[i].name = argv[i + 1];
        candidates[i].votes = 0;
    }

    int voter_count = get_int("Number of voters: ");

    // Loop over all voters
    for (int i = 0; i < voter_count; i++)
    {
        string name = get_string("Vote: ");

        // Check for invalid vote
        if (!vote(name))
        {
            printf("Invalid vote.\n");
        }
    }

    // Display winner of election
    print_winner();
}

// Update vote totals given a new vote
bool vote(string name)
{
    // Searching for a name match
    for (int i = 0; i < candidate_count; i++)
    {
        if (strcmp(name, candidates[i].name) == 0)
        {
            // If matching, increment candidate's votes and return true
            candidates[i].votes++;
            return true;
        }
    }
    return false;
}

// Print the winner (or winners) of the election
void print_winner(void)
{
    int winner_votes[MAX] = {0};
    string winners[MAX];

    // Find the first candidate with the max votes
    for (int i = 0; i < candidate_count; i++)
    {
        if (winner_votes[0] < candidates[i].votes)
        {
            winner_votes[0] = candidates[i].votes;
            winners[0] = candidates[i].name;
            candidates[i].votes = 0; // Eliminating amount of votes of the first candidate with the
                                     // max votes so it doesnt affect the "duplicate proccess"
        }
    }

    // Find canditates with the same ammount of max votes ("Duplicate Proccess")
    int duplicate_count = 1; // Initializing a counter
    for (int i = 0; i < candidate_count; i++)
    {
        if (winner_votes[0] == candidates[i].votes)
        {
            winner_votes[duplicate_count] = candidates[i].votes;
            winners[duplicate_count] = candidates[i].name;
            duplicate_count++;
        }
    }

    // Print the candidate (or candidates) with maximum votes
    for (int i = 0; i < duplicate_count; i++)
    {
        printf("%s\n", winners[i]);
    }
    return;
}
