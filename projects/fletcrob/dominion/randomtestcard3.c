/***********************************************************************************************
 * Robert Fletcher
 * randomtestcard3.c
 * CS362 - Summer 2019
 * Due: 07-28-2019
 * Description: This is the random test for the tribute card function
 ***********************************************************************************************/


#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include <assert.h>
#include "rngs.h"
#include <stdlib.h>

int main() {

	printf("***********************************\n");
	printf("Random Test Card 3: Tribute Card Function\n");
	printf("***********************************\n\n");

	int i;
	int j = 0;
	int m = 0;
	int q = 0;
	int handpos = 0, choice1 = 0, choice2 = 0, choice3 = 0, bonus = 0;
	int seed = 1000;
	int numPlayers = 2;
	int thisPlayer = 0;
	struct gameState G, testG;
	int k[10] = { baron, ambassador, village, minion, mine, cutpurse,
			sea_hag, tribute, smithy, council_room };
	int randomSeed = rand() % 100;
	int failed[500];
	int numberOfActionsBefore = 0; //used to count the number of actions before the card is played
	int numberOfCardsBefore = 0; //used to count the number of cards in hand before the card is played
	int numberOfCoinsBefore = 0; //used to count the number of coins in hand before the card is played

	G.hand[thisPlayer][0] = tribute;
	G.hand[thisPlayer][1] = gold;
	G.hand[thisPlayer][2] = mine;
	G.hand[thisPlayer][3] = copper;
	G.hand[thisPlayer][4] = copper;

	//run the test 500 times
	for (i = 0; i < 500; i++) {
		failed[i] = 0;
		numberOfActionsBefore = 0;
		numberOfCardsBefore = 0;
		numberOfCoinsBefore = 0;

		//set up a random seed between 0 and 1000
		seed = rand() % 1000;

		// initialize a game state and player cards
		initializeGame(numPlayers, k, seed, &G);

		//copy the gamestate to testG for testing
		memcpy(&testG, &G, sizeof(struct gameState));

		//player 2 draws five cards or three cards
		for (q = 0; q < 5; q++) {
			drawCard(1, &testG);
		}

		//number of coins before the card is played
		numberOfCoinsBefore = testG.coins;

		//number of cards before the card is played
		numberOfCardsBefore = testG.handCount[thisPlayer];

		//number of actions before the card is played
		numberOfActionsBefore = testG.numActions;

		/**************************************************************************
		//play the card
		**************************************************************************/
		tributeCard(&testG);
		
		//makes sure number of coins is within an appropriate range after card is played
		if (testG.coins > numberOfCoinsBefore + 4 || testG.coins < numberOfCoinsBefore) {
			failed[i] = 1;
		}

		//makes sure number of cards is within an appropriate range after card is played
		if (testG.handCount[thisPlayer] > numberOfCardsBefore + 2 || testG.handCount < numberOfCardsBefore - 1) {
			failed[i] = 1;
		}

		//makes sure number of actions is within an appropriate range after card is played
		if (testG.numActions > numberOfActionsBefore + 4 || testG.numActions < numberOfActionsBefore - 1) {
			failed[i] = 1;
		}


		if (failed[i] > 0) {
			printf("****************\n");
			printf("TEST %d Failed\n", i + 1);
			printf("****************\n");
			printf("SEED: %d\n", seed);
			printf("Number of Coins Before: %d\n", numberOfCoinsBefore);
			printf("Number of Coins After: %d\n", testG.coins);
			printf("Number of Cards Before: %d\n", numberOfCardsBefore);
			printf("Number of Cards After: %d\n", testG.handCount[thisPlayer]);
			printf("Number of Actions Before: %d\n", numberOfActionsBefore);
			printf("Number of Actions After: %d\n\n", testG.numActions);
			m++;
		}
		else {
			j++;
		}
	}


	return 0;
}