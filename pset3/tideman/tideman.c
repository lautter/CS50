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
}
pair;

// Array of candidates
string candidates[MAX];
pair pairs[MAX * (MAX - 1) / 2];

int pair_count;
int candidate_count;

// Function prototypes
bool vote(int rank, string name, int ranks[]);
void record_preferences(int ranks[]);
void add_pairs(void);
void sort_pairs(void);
void lock_pairs(void);
void print_winner(void);
bool oroboros(int winner);
bool checker(int index, bool visited[]);

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
    for (int i = 0; i < candidate_count - 1; i++)
    {
        for (int k = i + 1; k < candidate_count; k++)
        {
            preferences[ranks[i]][ranks[k]]++;
        }
    }
}

// Record pairs of candidates where one is preferred over the other
void add_pairs(void)
{
    int index = 0;          //index for pairs

    for (int i = 0; i < candidate_count; i++)
    {
        for (int j = 0; j < candidate_count; j++)
        {
            if (preferences[i][j] > preferences[j][i])
            {
                pairs[index].winner = i;
                pairs[index].loser = j;
                index++;
                pair_count++;
            }
        }
    }
}

// Sort pairs in decreasing order by strength of victory
void sort_pairs(void)
{
    int maximum = pair_count;
    int major = 0;
    pair temp;

    for (int i = 0; i < maximum - 1; i++)
    {
        major = i;
        for (int j = i + 1; j < maximum; j++)
        {
            if (preferences[pairs[major].winner][pairs[major].loser] < preferences[pairs[j].winner][pairs[j].loser])
            {
                major = j;
            }
        }

        if (preferences[pairs[i].winner][pairs[i].loser] < preferences[pairs[major].winner][pairs[major].loser])
        {
            temp = pairs[i];
            pairs[i] = pairs[major];
            pairs[major] = temp;
        }
    }
}

// Lock pairs into the candidate graph in order, without creating cycles
void lock_pairs(void)
{
    for (int i = 0; i < pair_count; i++)
    {
        locked[pairs[i].winner][pairs[i].loser] = true;

        if (oroboros(pairs[i].winner))
        {
            locked[pairs[i].winner][pairs[i].loser] = false;
        }
    }
}

bool oroboros(int winner)
{
    bool visited[candidate_count];

    for (int i = 0; i < candidate_count; i++)
    {
        visited[i] = false;
    }

    return checker(winner, visited);
}

bool checker(int winner, bool visited[])
{
    if (visited[winner])
    {
        return true;
    }

    visited[winner] = true;

    for (int i = 0; i < candidate_count; ++i)
    {
        if (locked[winner][i] && checker(i, visited))
        {
            return true;
        }
    }

    return false;
}

// Print the winner of the election
void print_winner(void)
{
    int count = 0;
    for (int i = 0; i < candidate_count; i++)
    {
        for (int j = 0; j < candidate_count; j++)
        {
            if (locked[j][i] == false)
            {
                count++;
            }
        }
        if (count == candidate_count)
        {
            printf("%s\n", candidates[i]);

            break;
        }
        count = 0;
    }
}

