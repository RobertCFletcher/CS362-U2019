/***********************************************************************************************
 * Robert Fletcher
 * unittest3.c
 * CS362 - Summer 2019
 * Due: 07-21-2019
 * Description: This is the test for the Ambassador card function
 ***********************************************************************************************/


#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include <assert.h>
#include "rngs.h"
#include <stdlib.h>

#define TESTCARD "ambassador"

int main() {

	int i;
	int handpos = 0, choice1 = 0, choice2 = 0, choice3 = 0, bonus = 0;
	int seed = 1000;
	int numPlayers = 2;
	int thisPlayer = 0;
	struct gameState G, testG;
	int k[10] = { baron, ambassador, village, minion, mine, cutpurse,
			sea_hag, tribute, smithy, council_room };


	// initialize a game state and player cards
	initializeGame(numPlayers, k, seed, &G);

	printf("----------------- Testing Card: %s ----------------\n", TESTCARD);

	// TEST 1: Testing whether entering anything greater than 2 for choice2 works

	printf("TEST 1: Value for choice2 greater than two should return an error\n\n");

	choice2 = 3;
	
	if (ambassadorCard(choice1, choice2, &testG, handpos) == -1) {
		printf("Choice generated an error as expected\n\n");
	}
	else {
		printf("Choice did not generate an error as expected\n\n");
	}


	memcpy(&testG, &G, sizeof(struct gameState));


	return 0;
}