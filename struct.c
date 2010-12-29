#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

typedef struct {
	char name [31];
	int age;
	char gender;
} Student;

int main()
{
	Student pupil[100];
	char aName[31];
	int j;
	void getString(FILE *, char[]);
	int getData(FILE *, Student[]);
	int search(char[], Student[], int);
	void sort(Student[], int);
	void printStudent(Student);
	void getString(FILE *, char[]);
	FILE *in = fopen("struct.txt", "r");
	if(in == NULL)
	{
		printf("input file not found\n");
		exit(1);
	}

	int numStudents = getData(in, pupil);
	if(numStudents == 0)
	{
		printf("No data supplied for students\n");
		exit(1);
	}

	printf("\n");
	for(j = 0; j < numStudents; j++)
		printStudent(pupil[j]);
	printf("\n");

	getString(in, aName);
	while(strcmp(aName, "END")!= 0)
	{
		int ans = search(aName, pupil, numStudents);
		if(ans == -1)
			printf("%s not found\n", aName);
		else
			printf("%s found at location %d\n", aName, ans);
		getString(in, aName);
	}

	sort(pupil, numStudents);
	printf("\n");
	for(j = 0; j < numStudents; j++)
		printStudent(pupil[j]);
	}

	void printStudent(Student t)
	{
		printf("Name: %s Age: %d Gender:%c\n", t.name, t.age, t.gender);
	}

	int getData(FILE *in, Student list[])
	{
		int n = 0;
		char temp[31];
		void getString(FILE *, char[]);
		char readChar(FILE *);
	
		getString(in, temp);
		while(strcmp(temp, "END") != 0 )
 		{
			strcpy(list[n].name, temp);
			fscanf(in, "%d", &list[n].age);
			list[n].gender = readChar(in);
			n++;
			getString(in, temp);
		}
		return n;
}

	int search(char key[], Student list[], int n)
	{
		int j;
		for(j = 0; j < n; j++)
			if(strcmp(key, list[j].name)== 0)
				return j;
		return -1;
	}

	void sort(Student list[], int n)
	{
		Student temp;
		int j, k;
		for(j = 1; j < n; j++)
		{
			temp = list[j];
			k = j - 1;
			while(k >= 0 && strcmp(temp.name, list[k].name) < 0)
			{
				list[k+1] = list[k];
				k = k - 1;
			}
			list[k+1] = temp;
		}
	}

	void getString(FILE *in, char str[])
	{
		char ch, delim;
		int n = 0;
		str[0] = '\0';
		while(isspace(ch = getc(in))); /* empty while body */
		if(ch == EOF) { return; }

		delim = ch;
		while(((ch = getc(in)) != delim) && (ch != EOF))
			str[n++] = ch;
		str[n] = '\0';
	}

	char readChar(FILE *in)
	{
		char ch;
		while(isspace(ch = getc(in))); /* empty while body */
		return ch;
	}
