/***********************************************************************************************
 * Robert Fletcher
 * unittest1.c
 * CS362 - Summer 2019
 * Due: 07-21-2019
 * Description: This is the test for the Baron card function
 ***********************************************************************************************/



#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include <assert.h>
#include "rngs.h"
#include <stdlib.h>

#define TESTCARD "baron"


int main() {
	int numberOfEstatesBefore = 0;	//used to count number of estates before card is played
	int numberOfEstatesAfter = 0;	//used to count number of estates after for compare
	int discardedEstatesBefore = 0;	//used to count number of discarded estates before card is played
	int discardedEstatesAfter = 0;	//used to count the number of discarded estates
	int numberOfCoinsBefore = 0;

	int i;
	int handpos = 0, choice1 = 0, choice2 = 0, choice3 = 0, bonus = 0;
	int seed = 1000;
	int numPlayers = 2;
	int thisPlayer = 0;
	struct gameState G, testG;
	int k[10] = { baron, ambassador, village, minion, mine, cutpurse,
			sea_hag, tribute, smithy, council_room };

	int previousBuys = 0;

	// initialize a game state and player cards
	initializeGame(numPlayers, k, seed, &G);

	printf("----------------- Testing Card: %s ----------------\n", TESTCARD);

	// TEST 1: Player should get +1 Buy after playing the baron card

	printf("TEST 1: Player gets +1 Buy\n");

	//copy the game state to test case
	memcpy(&testG, &G, sizeof(struct gameState));

	//choice1 = 1, player is discarding an estate
	printf("Player chooses to discard an estate.\n");
	choice1 = 1;

	//number of buys before the card is played
	printf("Number of buys before played card: %d\n", testG.numBuys);
	previousBuys = testG.numBuys;

	//play the card
	cardEffect(baron, choice1, choice2, choice3, &testG, handpos, &bonus);

	//number of buys after the card is played
	printf("Number of buys after played card: %d\n\n", testG.numBuys);

	assertTrue(previousBuys, testG.numBuys - 1);


	//copy the game state to test case
	memcpy(&testG, &G, sizeof(struct gameState));

	//choice1 = 2, player is gaining an estate
	printf("Player chooses to gain an estate.\n");
	choice1 = 0;

	//number of buys before the card is played
	printf("Number of buys before played card: %d\n", testG.numBuys);
	previousBuys = testG.numBuys;

	//play the card
	cardEffect(baron, choice1, choice2, choice3, &testG, handpos, &bonus);

	//number of buys after the card is played
	printf("Number of buys after played card: %d\n\n", testG.numBuys);
	assertTrue(previousBuys, testG.numBuys - 1);


	// TEST 2: Player has an estate and chooses to discard an estate
	// Player should gain four coins
	// One estate should leave the player's hand
	// One estate should enter the player's discard pile

	printf("TEST 2: Player has an estate in hand and chooses to discard an estate and gain four coins\n");

	//before playing the card and making this choice, player has an estate in hand
	G.hand[thisPlayer][0] = baron;
	G.hand[thisPlayer][1] = gold;
	G.hand[thisPlayer][2] = mine;
	G.hand[thisPlayer][3] = estate;
	G.hand[thisPlayer][4] = copper;

	//copy the game state to the test case
	memcpy(&testG, &G, sizeof(struct gameState));
	choice1 = 1;

	//count number of estates in hand
	for (i = 1; i < testG.handCount[thisPlayer]; i++) {
		//if an estate is found, set numberOfEstatesBefore to true
		if (testG.hand[thisPlayer][i - 1] == estate) {
			numberOfEstatesBefore += 1;
		}
	}

	//counts number of discarded estates before card is played
	discardedEstatesBefore = 0;
	for (i = 0; i < testG.discardCount[thisPlayer]; i++) {
		if (testG.deck[thisPlayer][i] == estate) {
			discardedEstatesBefore += 1;
		}
	}

	//prints number of estates
	printf("Number of estates in hand before card is played: %d\n", numberOfEstatesBefore);
	//prints number of coins before the card is played
	printf("Number of coins before the card is played: %d\n", testG.coins);
	numberOfCoinsBefore = testG.coins;
	//prints number of estates in discard pile before the card is played
	printf("Number of estates in discard pile before the card is played: %d\n", discardedEstatesBefore);

	//play card
	cardEffect(baron, choice1, choice2, choice3, &testG, handpos, &bonus);

	//count number of estates in hand after card is played
	numberOfEstatesAfter = 0;
	for (i = 1; i < testG.handCount[thisPlayer]; i++) {
		if (testG.hand[thisPlayer][i - 1] == estate) {
			numberOfEstatesAfter += 1;
		}
	}

	//counts number of discarded estates after card is played
	discardedEstatesAfter = 0;
	for (i = 0; i < testG.discardCount[thisPlayer]; i++) {
		if (testG.deck[thisPlayer][i] == estate) {
			discardedEstatesAfter += 1;
		}
	}
	//prints number of estates after card is played
	printf("Number of estates in hand after card is played: %d\n", numberOfEstatesAfter);
	assertTrue(numberOfEstatesBefore, numberOfEstatesAfter + 1);
	//prints number of coins after the card is played
	printf("Number of coins after the card is played: %d\n", testG.coins);
	assertTrue(testG.coins, numberOfCoinsBefore + 4);
	//prints number of estates in discard pile after the card is played
	printf("Number of estates in discard pile after the card is played: %d\n\n", discardedEstatesAfter);
	assertTrue(discardedEstatesBefore, discardedEstatesAfter - 1);



	// TEST 3: Player does not have an estate and chooses to discard an estate
	// Player should gain an estate and not gain four coins

	printf("TEST 3: Player does not have an estate and chooses to discard an estate and gain four coins\n");

	//before playing the card and making this choice, player does not have an estate in hand
	G.hand[thisPlayer][0] = baron;
	G.hand[thisPlayer][1] = baron;
	G.hand[thisPlayer][2] = gold;
	G.hand[thisPlayer][3] = mine;
	G.hand[thisPlayer][4] = copper;

	//copy the game state to the test case
	memcpy(&testG, &G, sizeof(struct gameState));
	choice1 = 0;

	//reset card counter
	numberOfEstatesBefore = 0;
	//count number of estates in hand
	for (i = 1; i < testG.handCount[thisPlayer]; i++) {
		if (testG.hand[thisPlayer][i - 1] == estate) {
			numberOfEstatesBefore += 1;
		}
	}

	//counts number of discarded estates before card is played
	discardedEstatesBefore = 0;
	for (i = 0; i < testG.discardCount[thisPlayer]; i++) {
		if (testG.deck[thisPlayer][i] == estate) {
			discardedEstatesBefore += 1;
		}
	}

	//prints number of estates before
	printf("Number of estates before card is played: %d\n", numberOfEstatesBefore);
	//prints number of coins before the card is played
	printf("Number of coins before the card is played: %d\n", testG.coins);
	numberOfCoinsBefore = testG.coins;
	//prints number of estates in discard pile before the card is played
	printf("Number of estates in discard pile before the card is played: %d\n", discardedEstatesBefore);

	//play card
	cardEffect(baron, choice1, choice2, choice3, &testG, handpos, &bonus);

	//count number of estates in hand after card is played
	numberOfEstatesAfter = 0;
	for (i = 1; i < testG.handCount[thisPlayer]; i++) {
		if (testG.hand[thisPlayer][i - 1] == estate) {
			numberOfEstatesAfter += 1;
		}
	}

	//counts number of discarded estates after card is played
	discardedEstatesAfter = 0;
	for (i = 0; i < testG.discardCount[thisPlayer]; i++) {
		if (testG.deck[thisPlayer][i] == estate) {
			discardedEstatesAfter += 1;
		}
	}

	//prints number of estates after card is played
	printf("Number of estates in hand after card is played: %d\n", numberOfEstatesAfter);
	assertTrue(numberOfEstatesBefore, numberOfEstatesAfter - 1);
	//prints number of coins after the card is played
	printf("Number of coins after the card is played: %d\n", testG.coins);
	assertTrue(numberOfCoinsBefore, testG.coins);
	//prints number of estates in discard pile after the card is played
	printf("Number of estates in discard pile after the card is played: %d\n\n", discardedEstatesAfter);
	assertTrue(discardedEstatesBefore, discardedEstatesAfter);


	// TEST 4: Player chooses to gain an estate

	printf("TEST 4: Player chooses to gain an estate and NOT discard a card\n");

	//copy the game state to the test case
	memcpy(&testG, &G, sizeof(struct gameState));

	//reset card counter
	numberOfEstatesBefore = 0;
	//count number of estates in hand
	for (i = 1; i < testG.handCount[thisPlayer]; i++) {
		if (testG.hand[thisPlayer][i - 1] == estate) {
			numberOfEstatesBefore += 1;
		}
	}

	//counts number of discarded estates before card is played
	discardedEstatesBefore = 0;
	for (i = 0; i < testG.discardCount[thisPlayer]; i++) {
		if (testG.deck[thisPlayer][i] == estate) {
			discardedEstatesBefore += 1;
		}
	}


	//prints number of estates
	printf("Number of estates in hand before card is played: %d\n", numberOfEstatesBefore);
	//prints number of coins before the card is played
	printf("Number of coins before the card is played: %d\n", testG.coins);
	//prints number of estates in discard pile before
	printf("Number of estates in the discard pile before card is played: %d\n", numberOfEstatesBefore);

	//play card
	choice1 = 0;
	cardEffect(baron, choice1, choice2, choice3, &testG, handpos, &bonus);

	//count number of estates in hand after card is played
	numberOfEstatesAfter = 0;
	for (i = 1; i < testG.handCount[thisPlayer]; i++) {
		if (testG.hand[thisPlayer][i - 1] == estate) {
			numberOfEstatesAfter += 1;
		}
	}

	//counts number of discarded estates after card is played
	discardedEstatesAfter = 0;
	for (i = 0; i < testG.discardCount[thisPlayer]; i++) {
		if (testG.deck[thisPlayer][i] == estate) {
			discardedEstatesAfter += 1;
		}
	}

	//prints number of estates after card is played
	printf("Number of estates after card is played: %d\n", numberOfEstatesAfter);
	assertTrue(numberOfEstatesBefore, numberOfEstatesAfter - 1);
	//prints number of coins after the card is played
	printf("Number of coins after the card is played: %d\n", testG.coins);
	assertTrue(numberOfCoinsBefore, testG.coins);
	//prints number of estates in discard pile after the card is played
	printf("Number of estates in discard pile after the card is played: %d\n\n\n", numberOfEstatesAfter);
	assertTrue(numberOfEstatesBefore, numberOfEstatesAfter - 1);


	return 0;
}