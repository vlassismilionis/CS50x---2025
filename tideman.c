#include <cs50.h>
#include <stdio.h>
#include <string.h>

// Max number of candidates
#define MAX 9

// preferences[i][j] is number of voters who prefer i over j
int preferences[MAX][MAX];

// locked[i][j] means i is locked in over j
bool locked[MAX][MAX];

// Each pair has a winner, loser
typedef struct
{
    int winner;
    int loser;
} pair;

// Array of candidates
string candidates[MAX];
pair pairs[MAX * (MAX - 1) / 2];

int pair_count;
int candidate_count;

// Array of margins between added pairs
int diffs[MAX * (MAX - 1) / 2];

// Function prototypes
bool vote(int rank, string name, int ranks[]);
void record_preferences(int ranks[]);
void add_pairs(void);
void sort_pairs(void);
void lock_pairs(void);
void print_winner(void);
bool cycle(int winner, int loser);

int main(int argc, string argv[])
{
    // Check for invalid usage
    if (argc < 2)
    {
        printf("Usage: tideman [candidate ...]\n");
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
        candidates[i] = argv[i + 1];
    }

    // Clear graph of locked in pairs
    for (int i = 0; i < candidate_count; i++)
    {
        for (int j = 0; j < candidate_count; j++)
        {
            locked[i][j] = false;
        }
    }

    // Set every value of preferences[i][j] to 0
    for (int i = 0; i < candidate_count; i++)
    {
        for (int j = 0; j < candidate_count; j++)
        {
            preferences[i][j] = 0;
        }
    }

    pair_count = 0;
    int voter_count = get_int("Number of voters: ");

    // Query for votes
    for (int i = 0; i < voter_count; i++)
    {
        // ranks[i] is voter's ith preference
        int ranks[candidate_count];

        // Query for each rank
        for (int j = 0; j < candidate_count; j++)
        {
            string name = get_string("Rank %i: ", j + 1);

            if (!vote(j, name, ranks))
            {
                printf("Invalid vote.\n");
                return 3;
            }
        }

        record_preferences(ranks);

        printf("\n");
    }

    add_pairs();
    sort_pairs();
    lock_pairs();
    print_winner();
    return 0;
}

// Update ranks given a new vote
bool vote(int rank, string name, int ranks[])
{
    for (int i = 0; i < candidate_count; i++)
    {
        if (strcmp(name, candidates[i]) == 0)
        {
            ranks[rank] = i;
            return true;
        }
    }
    return false;
}

// Update preferences given one voter's ranks
void record_preferences(int ranks[])
{
    for (int i = 0; i < candidate_count; i++)
    {
        for (int j = i + 1; j < candidate_count; j++)
        {
            preferences[ranks[i]][ranks[j]]++;
        }
    }
    return;
}

// Record pairs of candidates where one is preferred over the other
void add_pairs(void)
{
    pair_count = 0;
    for (int i = 0; i < candidate_count; i++)
    {
        for (int j = i + 1; j < candidate_count; j++)
        {
            if (preferences[i][j] > preferences[j][i])
            {
                pairs[pair_count].winner = i;
                pairs[pair_count].loser = j;
                diffs[pair_count] = preferences[i][j] - preferences[j][i];
                pair_count++;
            }
            else if (preferences[i][j] < preferences[j][i])
            {
                pairs[pair_count].winner = j;
                pairs[pair_count].loser = i;
                diffs[pair_count] = preferences[j][i] - preferences[i][j];
                pair_count++;
            }
        }
    }
    return;
}

// Sort pairs in decreasing order by strength of victory
void sort_pairs(void)
{
    // selection sort
    for (int j = 0; j < pair_count - 1; j++)
    {
        int index_max = j;

        for (int i = j + 1; i < pair_count; i++)
        {
            int strength_i = preferences[pairs[i].winner][pairs[i].loser];
            int strength_max = preferences[pairs[index_max].winner][pairs[index_max].loser];

            // 1) πρωτεύον κριτήριο: strength (ψήφοι υπέρ του winner)
            // 2) δευτερεύον κριτήριο: diff (margin) μόνο αν θες σταθερή ισοβαθμία
            if (strength_i > strength_max ||
                (strength_i == strength_max && diffs[i] > diffs[index_max]))
            {
                index_max = i;
            }
        }

        if (index_max != j)
        {
            // swap diffs
            int tmpdiff = diffs[j];
            diffs[j] = diffs[index_max];
            diffs[index_max] = tmpdiff;

            // swap pairs
            pair tmppair = pairs[j];
            pairs[j] = pairs[index_max];
            pairs[index_max] = tmppair;
        }
    }
}

// Lock pairs into the candidate graph in order, without creating cycles
void lock_pairs(void)
{
    for (int i = 0; i < pair_count; i++)
    {
        if (!cycle(pairs[i].winner, pairs[i].loser))
        {
            locked[pairs[i].winner][pairs[i].loser] = true;
        }
    }
    return;
}

// Checking for cycle
bool cycle(int start, int candidate)
{
    // Αν φτάσαμε πίσω στον αρχικό κόμβο, υπάρχει κύκλος
    if (candidate == start)
    {
        return true;
    }
    for (int i = 0; i < candidate_count; i++)
    {
        if (locked[candidate][i])
        {
            if (cycle(start, i))
            {
                return true;
            }
        }
    }

    return false;
}

// Print the winner(s) of the election
void print_winner(void)
{
    for (int i = 0; i < candidate_count; i++)
    {
        bool has_incoming = false;
        for (int j = 0; j < candidate_count; j++)
        {
            if (locked[j][i])
            {
                has_incoming = true;
                break;
            }
        }
        if (!has_incoming)
        {
            printf("%s\n", candidates[i]);
        }
    }
    return;
}
