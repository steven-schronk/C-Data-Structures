#include <stdio.h>
#include <string.h>

#define MAX_CANDIDATES 7
#define MAX_NAME_LENGTH 30

typedef struct {
	char name[MAX_NAME_LENGTH + 1];
	int numVotes;
} PersonData;

typedef struct {
	int valid, spoilt;
} VoteCount;

int main()
{
	void initalize(PersonData[], int, FILE *);
	VoteCount processVotes(PersonData[], int, FILE *, FILE *);
	void printResults(PersonData[], int, VoteCount, FILE *);

	PersonData candidate[MAX_CANDIDATES + 1];
	VoteCount count;
	FILE *in = fopen("votes.txt", "r");
	FILE *out = fopen("results.txt", "w");

	initalize(candidate, MAX_CANDIDATES, in);
	count = processVotes(candidate, MAX_CANDIDATES, in, out);
	printResults(candidate, MAX_CANDIDATES, count, out);

	fclose(in);
	fclose(out);
}

void initalize(PersonData person[], int max, FILE *in)
{
	char lastName[MAX_NAME_LENGTH];
	int j;

	for(j = 1; j < max; j++)
	{
		fscanf(in, "%s %s", person[j].name, lastName);
		strcat(person[j].name, " ");
		strcat(person[j].name, lastName);
		person[j].numVotes = 0;
	}
}

VoteCount processVotes(PersonData person[], int max, FILE *in, FILE 
*out)
{
	int v;
	VoteCount temp;
	temp.valid = temp.spoilt = 0;

	while(v != 0)
	{
		if(v < 1 || v > max)
		{
			fprintf(out, "Invalid vote: %d\n", v);
			++temp.spoilt;
		} else {
			++person[v].numVotes;
			++temp.valid;
		}
		fscanf(in, "%d", &v);
	}
	return temp;
}

int getLargest(PersonData person[], int lo, int hi)
{
	int j, big = lo;
	for(j = lo; j <= hi; j++)
		if(person[j].numVotes > person[big].numVotes)big = j;
	return big;
}

void printResults(PersonData person[], int max, VoteCount c, FILE *out)
{
	int j, getLargest(PersonData[], int, int);
	fprintf(out, "\nNumber of voters: %d\n", c.valid + c.spoilt);
	fprintf(out, "Number of valid voters: %d\n", c.valid);
	fprintf(out, "Number of spolit votes: %d\n", c.spoilt);
	fprintf(out, "\nCandidate Score\n\n");
	
	for(j = 1; j <= max; j++)
		fprintf(out, "%-15s %3d\n", person[j].name, person[j].numVotes);

	fprintf(out, "\nThe winner(s):\n");
	int winningVote = getLargest(person, 1, max);
	for(j = 1; j <= max; j++)
		if(person[j].numVotes == winningVote)
			fprintf(out, "%s\n", person[j].name);
}

void sortByVote(PersonData person[], int lo, int hi)
{
	int j, k;
	PersonData insertItem;

	for(j = lo + 1; j <= hi; j++)
	{
		insertItem = person[j];
		k = j - 1;
		while(k >= lo && insertItem.numVotes > 
person[k].numVotes)
		{
			person[k+1] = person[k];
			--k;
		}
	person[k+1] = insertItem;
	}
}

void sortByName(PersonData person[], int lo, int hi)
{
	int j, k;
	PersonData insertItem;

	for(j = lo; j <= hi; j++)
	{
		insertItem = person[j];
		k = j - 1;
		while(k > 0 && strcmp(insertItem.name, person[k].name) < 
0)
		{
			person[k+1] = person[k];
			--k;
		}
	person[k+1] = person[k];
	--k;
	}
}
