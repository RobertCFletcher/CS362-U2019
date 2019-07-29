/***********************************************************************************************
 * Robert Fletcher
 * randomtestcard1.c
 * CS362 - Summer 2019
 * Due: 07-28-2019
 * Description: This is the random test for the Baron card function
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
	printf ("Random Test Card 1: Baron Card Function\n");
	printf("***********************************\n");

	int i;
	int j = 0;	//used to count number of passed tests
	int m = 0;	//used to count number of failed tests
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
	int numberOfEstatesBefore = 0;	//used to count number of estates before card is played
	int numberOfEstatesAfter = 0;	//used to count number of estates after for compare
	int discardedEstatesBefore = 0;	//used to count number of discarded estates before card is played
	int discardedEstatesAfter = 0;	//used to count number of discarded estates
	int numberOfCoinsBefore = 0;	//used to count number of coins before card is played
	int numberOfBuysBefore = 0;		//used to hold number of buys before card is played

	//running 500 tests
	for (i = 0; i < 500; i++) {
		numberOfEstatesBefore = 0;
		numberOfEstatesAfter = 0;
		discardedEstatesBefore = 0;
		discardedEstatesAfter = 0;
		numberOfCoinsBefore = 0;
		numberOfBuysBefore = 0;
		failed[i] = 0;
		//set up a random seed between 0 and 1000
		seed = rand() % 1000;

		// initialize a game state and player cards
		initializeGame(numPlayers, k, seed, &G);

		//50-50 chance of player having an estate in hand
		if (rand() % 2 == 0) {
			//50-50 chance of player choosing to discard an estate or not discard an estate
			if (rand() % 2 == 0) {
				choice1 = 1;
			}
			else {
				choice1 = 0;
			}

			//set up player's hand
			G.hand[thisPlayer][0] = baron;
			G.hand[thisPlayer][1] = gold;
			G.hand[thisPlayer][2] = mine;
			G.hand[thisPlayer][3] = estate;
			G.hand[thisPlayer][4] = copper;
		}
		//50-50 chance of a player NOT having an estate in hand
		else {
			//50-50 chance of player choosing to discard an estate or not discard an estate
			if (rand() % 2 == 0) {
				choice1 = 1;
			}
			else {
				choice1 = 0;
			}

			//set up player's hand
			G.hand[thisPlayer][0] = baron;
			G.hand[thisPlayer][1] = gold;
			G.hand[thisPlayer][2] = mine;
			G.hand[thisPlayer][3] = copper;
			G.hand[thisPlayer][4] = copper;
		}

		//copy the gamestate to testG for testing
		memcpy(&testG, &G, sizeof(struct gameState));


		//checks before the card is played
		
		//number of buys before card is played
		numberOfBuysBefore = testG.numBuys;

		//number of coins before the card is played
		numberOfCoinsBefore = testG.coins;

		//number of estates in hand before card is played
		for (q = 1; q < testG.handCount[thisPlayer]; q++) {
			//if an estate is found add one to numberOfEstatesBefore
			if (testG.hand[thisPlayer][q - 1] == estate) {
				numberOfEstatesBefore += 1;
			}
		}

		//counts number of discarded estates before card is played
		discardedEstatesBefore = 0;
		for (q = 0; q < testG.discardCount[thisPlayer]; q++) {
			//if an estate is found in the discard pile, add one to discardedEstatesBefore
			if (testG.deck[thisPlayer][q] == estate) {
				discardedEstatesBefore += 1;
			}
		}

		if (i == 0) {
			choice1 = 1;
			testG.supplyCount[estate] = 1;
			testG.hand[thisPlayer][0] = baron;
			testG.hand[thisPlayer][1] = gold;
			testG.hand[thisPlayer][2] = mine;
			testG.hand[thisPlayer][3] = copper;
			testG.hand[thisPlayer][4] = copper;
		}

		if (i == 1) {
			choice1 = 0;
			testG.supplyCount[estate] = 1;
			testG.hand[thisPlayer][0] = baron;
			testG.hand[thisPlayer][1] = gold;
			testG.hand[thisPlayer][2] = mine;
			testG.hand[thisPlayer][3] = copper;
			testG.hand[thisPlayer][4] = copper;
		}
		

		/**************************************************************************
		//play the card
		**************************************************************************/
		playCard(handpos, choice1, choice2, choice3, &testG);
		

		//verification after the card is played

		//number of estates in hand after card is played
		numberOfEstatesAfter = 0;
		for (q = 1; q < testG.handCount[thisPlayer]; q++) {
			if (testG.hand[thisPlayer][q - 1] == estate) {
				numberOfEstatesAfter += 1;
			}
		}

		//number of discarded estates after card is played
		discardedEstatesAfter = 0;
		for (q = 0; q < testG.discardCount[thisPlayer]; q++) {
			if (testG.deck[thisPlayer][q] == estate) {
				discardedEstatesAfter += 1;
			}
		}

		//if player is discarding an estate and number of estates in hand doesn't decrease by 1, test failed
		if (choice1 == 1 && numberOfEstatesBefore >= 1 && numberOfEstatesAfter != numberOfEstatesBefore - 1) {
			failed[i] = 1;
		}

		//if player is discarding an estate and player doesn't gain 4 coins, test failed
		if (choice1 == 1 && numberOfEstatesBefore >= 1 && numberOfCoinsBefore != numberOfCoinsBefore + 4) {
			failed[i] = 1;
		}

		//if player chooses to discard an estate but doesn't have an estate, player should gain an estate or test fails
		if (choice1 == 1 && numberOfEstatesBefore == 0 && numberOfEstatesAfter != numberOfEstatesBefore + 1) {
			failed[i] = 1;
		}

		//if player is not discarding an estate and number of estates in hand does not increase by 1, test failed
		if (choice1 == 0 && numberOfEstatesAfter != numberOfEstatesBefore + 1) {
			failed[i] = 1;
		}

		//if player is not discarding an estate and player doesn't keep the same number of coins, test failed
		if (choice1 == 0 && numberOfCoinsBefore != numberOfCoinsBefore) {
			failed[i] = 1;
		}

		//if number of buys before doesn't increase by 1, test failed
		if (testG.numBuys != numberOfBuysBefore + 1) {
			failed[i] = 1;
		}

		//if the test failed, print out test info
		if (failed[i] > 0) {
			printf("****************\n");
			printf("TEST %d Failed\n", i + 1);
			printf("****************\n\n");
			printf("SEED: %d\n", seed);
			printf("Choice1: %d\n", choice1);
			printf("Number of estates before card was played: %d\n", numberOfEstatesBefore);
			printf("Number of estates after card was played: %d\n", numberOfEstatesAfter);
			printf("Number of coins before card was played: %d\n", numberOfCoinsBefore);
			printf("Number of coins after card was played: %d\n", testG.coins);
			printf("Number of buys before card was played: %d\n", numberOfBuysBefore);
			printf("Number of buys after card was played: %d\n\n", testG.numBuys);

			m++;
		}
		else {
			j++;
		}
	}


	return 0;
}