/***********************************************************************************************
 * Robert Fletcher
 * randomtestcard2.c
 * CS362 - Summer 2019
 * Due: 07-28-2019
 * Description: This is the random test for the minion card function
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
	printf("Random Test Card 2: Minion Card Function\n");
	printf("***********************************\n\n");

	int i;
	int j = 0;
	int m = 0;
	int q = 0;
	int handpos = 0, choice1 = 0, choice2 = 0, choice3 = 0, bonus = 0;
	int seed = 1000;
	int numPlayers = 2;
	int thisPlayer = 0;
	int nextPlayer = 1;
	struct gameState G, testG;
	int k[10] = { baron, ambassador, village, minion, mine, cutpurse,
			sea_hag, tribute, smithy, council_room };
	int randomSeed = rand() % 100;
	int failed[500];
	int numberOfCoinsBefore = 0; //used to count number of coins before card is played
	int numberOfCardsBeforeP1 = 0; //player1 number of cards in hand before card is played
	int numberOfCardsBeforeP2 = 0; //player2 number of cards in hand before card is played
	int numberOfCardsAfterP1 = 0; //player1 number of cards in hand after card is played
	int numberOfCardsAfterP2 = 0; //player1 number of cards in hand after card is played
	int numberOfSimilarCards = 0; //check for similar cards in hand

	G.hand[thisPlayer][0] = minion;
	G.hand[thisPlayer][1] = gold;
	G.hand[thisPlayer][2] = mine;
	G.hand[thisPlayer][3] = copper;
	G.hand[thisPlayer][4] = copper;

	//running 500 tests
	for (i = 0; i < 500; i++) {

		numberOfSimilarCards = 0;
		failed[i] = 0;

		//set up a random seed between 0 and 1000
		seed = rand() % 1000;

		// initialize a game state and player cards
		initializeGame(numPlayers, k, seed, &G);

		//copy the gamestate to testG for testing
		memcpy(&testG, &G, sizeof(struct gameState));

		//50-50 chance of choosing first option vs second option
		if (rand() % 2 == 0) {
			//+2 coins
			choice1 = 0;
		}
		else {
			//discard hand, +4 cards, each other player with 5+ cards discards hand and gets +4 cards
			choice1 = 1;
		}

		//player 2 draws five cards or three cards
		for (q = 0; q < 5; q++) {
			drawCard(1, &testG);
		}

		//checks before the card is played

		//number of coins before the card is played
		numberOfCoinsBefore = testG.coins;

		//number of cards in hand before the card is played
		numberOfCardsBeforeP1 = testG.handCount[thisPlayer];
		numberOfCardsBeforeP2 = testG.handCount[nextPlayer];


		/**************************************************************************
		//play the card
		**************************************************************************/
		minionCard(choice1, &testG, handpos);



		//checks after the card is played
		numberOfCardsAfterP1 = testG.handCount[thisPlayer];
		numberOfCardsAfterP2 = testG.handCount[nextPlayer];

		//if player has more than four cards when they're supposed to have four cards
		if (choice1 == 1 && numberOfCardsAfterP1 != 4) {
			failed[i] = 1;
		}

		//if the player has the exact same hand in the same order which should be extremely rare, test fails
		for (q = 0; q < testG.discardCount[thisPlayer]; q++) {
			//if an estate is found in the discard pile, add one to discardedEstatesBefore
			if (testG.deck[thisPlayer][q] == G.deck[thisPlayer][q + 1]) {
				numberOfSimilarCards += 1;
			}
		}
		if (numberOfSimilarCards == 4) {
			failed[i] = 1;
		}

		if (failed[i] > 0) {
			printf("****************\n");
			printf("TEST %d Failed\n", i + 1);
			printf("****************\n");
			printf("SEED: %d\n", seed);
			printf("Choice1: %d\n", choice1);
			printf("Player 1 # of Cards After: %d\n", numberOfCardsAfterP1);
			printf("Number of similar cards: %d\n\n", numberOfSimilarCards);

			m++;
		}
		else {
			printf("****************\n");
			printf("TEST %d Passed!\n", i + 1);
			printf("****************\n\n");
			j++;
		}
	}
	return 0;
}