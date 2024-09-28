#include <cs50.h>
#include <stdio.h>
#include <string.h>

#define MAX_VOTERS 100
#define MAX_CANDIDATES 9
int preferences[MAX_VOTERS][MAX_CANDIDATES];
typedef struct
{
    string name;
    int votes;
    bool eliminated;
} candidate;
candidate candidates[MAX_CANDIDATES];
int voter_count;
int candidate_count;
bool vote(int voter, int rank, string name);
void tabulate(void);
bool print_winner(void);
int find_min(void);
bool is_tie(int min);
void eliminate(int min);
int main(int argc, string argv[])
{
    if (argc < 2)
    {
        printf("Usage: runoff [candidate ...]\n");
        return 1;
    }
    candidate_count = argc - 1;
    if (candidate_count > MAX_CANDIDATES)
    {
        printf("Maximum number of candidates is %i\n", MAX_CANDIDATES);
        return 2;
    }
    for (int i = 0; i < candidate_count; i++)
    {
        candidates[i].name = argv[i + 1];
        candidates[i].votes = 0;
        candidates[i].eliminated = false;
    }
    voter_count = get_int("Number of voters: ");
    if (voter_count > MAX_VOTERS)
    {
        printf("Maximum number of voters is %i\n", MAX_VOTERS);
        return 3;
    }
    // loop thorugh every voter to ask them to vote
    for (int i = 0; i < voter_count; i++)
    {
        // loop through each rank, ask them which candidate they vote for
        for (int j = 0; j < candidate_count; j++)
        {
            string name = get_string("Rank %i: ", j + 1);
            // then vote with that name
            // pass down, i as voter, j as rank, and name
            // if nothing wrong then we have a 2-D array of preferences
            if (!vote(i, j, name))
            {
                // if that vote not valid then quit
                printf("Invalid vote.\n");
                return 4;
            }
        }
        printf("\n");
    }
    // continuously ask question until the the winner is defined
    while (true)
    {
        // update candidates' votes base on preferences
        tabulate();
        // then print winner and return true if there's actually is a winner
        // else continue the while loop
        bool won = print_winner();
        // then the program will be stoped
        if (won)
        {
            break;
        }
        // get the minumum vote of the candidate that still in the election
        int min = find_min();
        // pass down the min vote
        bool tie = is_tie(min);
        // if it's a tie
        if (tie)
        {
            // loop through each candidate
            for (int i = 0; i < candidate_count; i++)
            {
                // if candidate is not eliminated
                if (!candidates[i].eliminated)
                {
                    // print candidate as winner
                    printf("%s\n", candidates[i].name);
                }
            }
            // then break and quit
            break;
        }
        // if it's not tie, then eliminate every candidate with min votes
        eliminate(min);
        // then loop through each candidate
        for (int i = 0; i < candidate_count; i++)
        {
            // reset their vote
            candidates[i].votes = 0;
        }
    }
    return 0;
}
bool vote(int voter, int rank, string name)
{
    // loop through array of candidates
    for (int i = 0; i < candidate_count; i++)
    {
        // if candidate existed in array
        if (strcmp(candidates[i].name, name) == 0)
        {
            // the mark the preferences to be the candidate index 
            preferences[voter][rank] = i;
            // then return vote success
            return true;
        }
    }
    // else return vote fail
    return false;
}
void tabulate(void)
{
    // loop through each voter 
    for (int i = 0; i < voter_count; i++)
    {
        // loop through each rank of each voter
        for (int j = 0; j < candidate_count; j++)
        {
            // index of candidates array
            int index = preferences[i][j];
            // if that candidate is not eliminated yet
            if (!candidates[index].eliminated)
            {
                // increase votes
                ++candidates[index].votes;
                // then break out of loop and go to next voter to count
                break;
            }
            // else continue until we find the one that is not eliminated
        }
    }
    return;
}
bool print_winner(void)
{
    // loop through every candidate
    for (int i = 0; i < candidate_count; i++)
    {
        // get current candidate
        candidate current = candidates[i];
        int doubleVotes = current.votes + current.votes;
        // if the candidate's votes greater than 50% of the vote_count
        if (doubleVotes > voter_count)
        {
            // then declare as a winner
            printf("%s\n", current.name);
            // and return true
            return true;
        }
    }
    // else return false and continue the finding winner
    return false;
}
// return the minimum vote total for any candidates who is still in the election
int find_min(void)
{
    // init, probably greater than max candidates
    int min = 1000; 
    // loop through each candidate
    for (int i = 0; i < candidate_count; i++)
    {
        // get candidate's vote
        candidate current = candidates[i];
        // compare with min, if less than
        if (current.votes < min && !current.eliminated)
        {
            // then assign to new min
            min = current.votes;
        }
    }
    // return new min
    return min;
}
bool is_tie(int min)
{
    // loop through every candidate
    for (int i = 0; i < candidate_count; i++)
    {
        candidate current = candidates[i];
        // if current candidate's votes not min 
        // and current candidate is still in the election
        if (current.votes != min && !current.eliminated)
        {
            // then it's not a tie
            return false;
        }
    }
    // else it's a tie
    return true;
}
void eliminate(int min)
{
    // loop through each candidate
    for (int i = 0; i < candidate_count; i++)
    {
        // if candidate's votes is min then eliminate them
        if (candidates[i].votes == min && !candidates[i].eliminated)
        {
            candidates[i].eliminated = true;
            // don't break because there could be more than 1 candidate
        }
    }
    return;
}
