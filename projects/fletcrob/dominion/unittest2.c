/***********************************************************************************************
 * Robert Fletcher
 * unittest2.c
 * CS362 - Summer 2019
 * Due: 07-21-2019
 * Description: This is the test for the Minion card function
 ***********************************************************************************************/


#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include <assert.h>
#include "rngs.h"
#include <stdlib.h>

#define TESTCARD "minion"

int main() {

	int i;
	int handpos = 0, choice1 = 0, choice2 = 0, choice3 = 0, bonus = 0;
	int seed = 1000;
	int numPlayers = 2;
	int thisPlayer = 0;
	struct gameState G, testG;
	int k[10] = { baron, ambassador, village, minion, mine, cutpurse,
			sea_hag, tribute, smithy, council_room };
	int numberOfActionsBefore = 0;
	int numberOfCoinsBefore = 0;
	int handCountBefore = 0;
	int player2HandCountBefore = 0;

	// initialize a game state and player cards
	initializeGame(numPlayers, k, seed, &G);

	printf("----------------- Testing Card: %s ----------------\n", TESTCARD);

	// TEST 1: Player chooses option 1

	printf("TEST 1: Player chooses first option and gains two coins\n\n");

	//set up game state and copy the game state to test case
	G.hand[thisPlayer][0] = minion;
	G.hand[thisPlayer][1] = gold;
	G.hand[thisPlayer][2] = mine;
	G.hand[thisPlayer][3] = estate;
	G.hand[thisPlayer][4] = copper;
	memcpy(&testG, &G, sizeof(struct gameState));

	//check number of actions before the card is played
	printf("Number of actions before the card is played: %d\n", testG.numActions);
	numberOfActionsBefore = testG.numActions;
	//check number of coins before the card is played
	printf("Number of coins before the card is played: %d\n", testG.coins);
	numberOfCoinsBefore = testG.coins;
	//check number of cards in hand before the card is played
	printf("Number of cards in hand before the card is played: %d\n\n", testG.handCount[thisPlayer]);
	handCountBefore = testG.handCount[thisPlayer];

	//Set choice1 to 1 and choice2 to 0
	choice1 = 1;
	choice2 = 0;

	//play card
	cardEffect(minion, choice1, choice2, choice3, &testG, handpos, &bonus);

	//check number of actions after the card is played
	printf("Number of actions after the card is played: %d\n", testG.numActions);
	assertTrue(testG.numActions, numberOfActionsBefore);
	//check number of coins after the card is played
	printf("Number of coins after the card is played: %d\n", testG.coins);
	assertTrue(testG.coins, numberOfCoinsBefore + 2);
	//check number of cards in hand after the card is played
	printf("Number of cards in hand after the card is played: %d\n", testG.handCount[thisPlayer]);
	assertTrue(testG.handCount[thisPlayer], handCountBefore - 1);


	// TEST 1: Player chooses option 1

	printf("TEST 2: Player chooses second option, discards hand, gains four cards, same with player 2\n\n");

	//set up game state and copy the game state to test case

	//player 1 hand
	G.hand[thisPlayer][0] = minion;
	G.hand[thisPlayer][1] = gold;
	G.hand[thisPlayer][2] = mine;
	G.hand[thisPlayer][3] = estate;
	G.hand[thisPlayer][4] = copper;

	//player 2 hand
	for (i = 0; i < 5; i++)
	{
		drawCard(1, &G);
	}

	memcpy(&testG, &G, sizeof(struct gameState));


	//check number of actions before the card is played
	printf("Number of actions before the card is played: %d\n", testG.numActions);
	numberOfActionsBefore = testG.numActions;
	//check number of coins before the card is played
	printf("Number of coins before the card is played: %d\n", testG.coins);
	numberOfCoinsBefore = testG.coins;
	//check number of cards in hand before the card is played
	printf("Player 1 number of cards in hand before the card is played: %d\n", testG.handCount[thisPlayer]);
	handCountBefore = testG.handCount[thisPlayer];
	//check number of cards in hand before the card is played
	printf("Player 2 number of cards in hand before the card is played: %d\n", testG.handCount[1]);
	player2HandCountBefore = testG.handCount[1];

	//Set choice1 to 0 and choice2 to 1
	choice1 = 0;
	choice2 = 1;

	//play card
	cardEffect(minion, choice1, choice2, choice3, &testG, handpos, &bonus);

	//check number of actions after the card is played
	printf("Number of actions after the card is played: %d\n", testG.numActions);
	assertTrue(testG.numActions, numberOfActionsBefore);
	//check number of coins after the card is played
	printf("Number of coins after the card is played: %d\n", testG.coins);
	assertTrue(testG.coins, numberOfCoinsBefore);
	//check number of cards in hand after the card is played (player 1)
	printf("Player 1 number of cards in hand after the card is played: %d\n", testG.handCount[thisPlayer]);
	assertTrue(handCountBefore, 4);
	//check number of cards in hand before the card is played (player 2)
	printf("Player 2 number of cards in hand after the card is played: %d\n", testG.handCount[1]);
	assertTrue(player2HandCountBefore, 4);

	return 0;
}