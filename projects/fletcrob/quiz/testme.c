#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<time.h>

char inputChar()
{
	//20-126
	char characterToReturn = rand() % 95 + 32;

	return characterToReturn;
}

char *inputString()
{
	char *sendBackString = malloc(6 * sizeof(char));

	sendBackString[0] = 'r';
	sendBackString[1] = rand() % 26 + 97;
	sendBackString[2] = rand() % 26 + 97;
	sendBackString[3] = rand() % 26 + 97;
	sendBackString[4] = rand() % 26 + 97;
	sendBackString[5] = '\0';

	// TODO: rewrite this function
	return sendBackString;
}

void testme()
{
	int tcCount = 0;
	char c;
	int state = 0;
	while (1)
	{
		tcCount++;
		c = inputChar();
		char* s = inputString();
		printf("Iteration %d: c = %c, s = %s, state = %d\n", tcCount, c, s, state);

		if (c == '[' && state == 0) state = 1;
		if (c == '(' && state == 1) state = 2;
		if (c == '{' && state == 2) state = 3;
		if (c == ' '&& state == 3) state = 4;
		if (c == 'a' && state == 4) state = 5;
		if (c == 'x' && state == 5) state = 6;
		if (c == '}' && state == 6) state = 7;
		if (c == ')' && state == 7) state = 8;
		if (c == ']' && state == 8) state = 9;
		if (s[0] == 'r' && s[1] == 'e'
			&& s[2] == 's' && s[3] == 'e'
			&& s[4] == 't' && s[5] == '\0'
			&& state == 9)
		{
			printf("error ");
			free(s);
			exit(200);
		}
		free(s);
	}
}


int main(int argc, char *argv[])
{

	srand(time(NULL));
	testme();
	return 0;
}