#include <stdio.h>
#include <stdlib.h>
#include <time.h>


// --- Typedefs --- //

typedef enum {false, true} bool;

typedef enum {none, dealer_c, lblind, bblind} Role;

typedef enum {spades, clubs, hearts, diamonds} Suit;

typedef enum {ace, two, three, four, five, six, seven, eight, nine, ten, jack, queen, king} Face; 

typedef enum {fold, call, raise, check} Action;

struct Card {
	Face face;
	Suit suit;
} ;


struct Player {
	struct Card card[2]; // Array of the player's cards
	// struct Card card1; // The player's first card
	// struct Card card2; // The player's second card
	int chips; // The number of chips the player has remaining

	Role role; // The players role in the game (little blind, dealer, etc.)
	Action action; // The last committed action (fold, raise, etc.)
	int bet; // The player's current bet.

	struct Player* next; // The player to my left
	struct Player* prev; // The player to my right

} ;


// ---------------- //


// --- Function Declaration --- //
const char* num2face(int in);
const char* num2suit(int in);
const char* num2role(int in);
const char* num2action(int in);
// ---------------------------- //



// --- Global Variables --- //

// ------------------------ //




int main (int argc, char* argv[]) {
	srand(24); int i, j, tmp;
	



	// --- Take user input --- //
	// Number of players.
	// Blinds or ante
	// Blinds/ante increasing rate
	// Look to Jacobi_06.c for a better way to handle user input.

	int players_remaining = 3;
	int small_blind = 5;
	int big_blind = 10;
	int starting_chip_count = 200;


printf("\n---- Output for the parameters setup ----\n");
printf("The number of players: %d\n", players_remaining);
printf("The small blind: %d\n", small_blind);
printf("The big blind: %d\n", big_blind);
printf("Starting number of chips for each player: %d\n", starting_chip_count);
getchar();





	// --- Create the deck --- //

	int* deck = (int*) malloc(52*sizeof(int));
	for (i = 0; i < 52; i++) {
		deck[i] = i;
	}

	// This is a pre-shuffle. Not really necessary because we shuffle at the start of each round
	// Fisher-Yates shuffle
	for (i = 51; i > 0; i--) {
		j = rand() % i;
		tmp = deck[i];
		deck[i] = deck[j];
		deck[j] = tmp;
	}




printf("\n---- Output for the deck setup ----\n");
printf("Cards at the top of the deck:\n");
for (i = 0; i < players_remaining*2 + 8; i++) {
// printf("Face: %d \t Suit: %d\n", deck[i] % 13, deck[i] % 4);
printf("%s of %s\n", num2face(deck[i] % 13), num2suit(deck[i] % 4));
}
getchar();




	// --- Setup the Players --- //

	// Setup the first player
	struct Player* players = (struct Player*) calloc(1, sizeof(struct Player));
	struct Player* dealer = players; // Set a dealer reference to the first player
	// players -> card1 = deck[top++];
	// players -> card2 = deck[top++];
	players -> chips = starting_chip_count;
	players -> prev = NULL;

	// Setup all the other players
	for (i = 1; i < players_remaining ; i++) {
		players -> next = (struct Player*) calloc(1, sizeof(struct Player));
		// players -> next -> card1 = deck[top++];
		// players -> next -> card2 = deck[top++];
		players -> next -> chips = starting_chip_count;
		players -> next -> prev = players;
		players = players -> next;
	}
	players -> next = dealer;
	dealer -> prev = players;
	players = players -> next;


	// Set the default roles for each player
dealer -> role = dealer_c;
dealer -> next -> role = lblind;
dealer -> next -> next -> role = bblind;



while (players -> next != dealer) {
printf("\n---- Output for the Player Setup ----\n");
printf("Player ID: %p\n", players);
printf("Player Card array memory address: %p\n", players->card);
printf("Player First Card Face: %d\t Suit: %d\n", players->card[0].face, players->card[0].suit);
printf("Player Second Card Face: %d\t Suit: %d\n", players->card[1].face, players->card[1].suit);
printf("Player Chip Count: %d\n", players->chips);
printf("Player Role: %d\n", players->role);
printf("Player Action: %d\n", players->action);
printf("Player Bet: %d\n", players->bet);
printf("Player to my right: %p\n", players->next);
printf("Player to my right: %p\n", players->prev);
getchar();
players = players -> next;
}

printf("\n---- Output for the Player Setup ----\n");
printf("Player ID: %p\n", players);
printf("Player Card array memory address: %p\n", players->card);
printf("Player First Card Face: %d\t Suit: %d\n", players->card[0].face, players->card[0].suit);
printf("Player Second Card Face: %d\t Suit: %d\n", players->card[1].face, players->card[1].suit);
printf("Player Chip Count: %d\n", players->chips);
printf("Player Role: %d\n", players->role);
printf("Player Action: %d\n", players->action);
printf("Player Bet: %d\n", players->bet);
printf("Player to my right: %p\n", players->next);
printf("Player to my right: %p\n", players->prev);
getchar();
players = players -> next;




	// --- Start the game! --- //

	int pot;

	// while(players_remaining > 1 ) {


		// --- (1) Clean up --- //
		pot = 0;



		// --- (2) Determine each players role and ante up--- //
		
		// The dealer
		dealer -> role = none;
		dealer = dealer -> next;
		dealer -> role = dealer_c;

		// The little blind
		players = dealer -> next ;
		players -> role = lblind;
		players -> bet = small_blind;
		pot += small_blind;
		players -> action = check;

		// The big blind
		players = players -> next;
		players -> role = bblind;
		players -> bet = big_blind;
		pot += big_blind;
		players -> action = raise;



		// Need to design a data structure to handle side-pots and the players active on
		// each pot. Need to recognize when a bet exceeds the number of chips in a player's hand
		// and use that to trigger the generation of a side pot.





		// --- (3) Shuffle the cards --- //

		for (i = 51; i > 0; i--) {
			j = rand() % i;
			tmp = deck[i];
			deck[i] = deck[j];
			deck[j] = tmp;
		}


printf("\n---- Output for the deck setup ----\n");
printf("Cards at the top of the deck:\n");
for (i = 0; i < players_remaining*2 + 8; i++) {
// printf("Face: %d \t Suit: %d\n", deck[i] % 13, deck[i] % 4);
printf("%s of %s\n", num2face(deck[i] % 13), num2suit(deck[i] % 4));
}
getchar();




		// --- (4) Deal cards to each player --- //

		players = dealer -> next; // Deal the first card to the little blind
		for (i = 0; i < 2*players_remaining; i++) {
			players -> card[i / players_remaining].face = deck[i] % 13;
			players -> card[i / players_remaining].suit = deck[i] % 4 ;
			players = players -> next;
		}


players = dealer;
while (players -> next != dealer) {
printf("\n---- Output for the Player Setup ----\n");
printf("Player ID: %p\n", players);
printf("Player Card array memory address: %p\n", players->card);
printf("Player First Card:  %s of %s\n", num2face(players->card[0].face), num2suit(players->card[0].suit));
printf("Player Second Card: %s of %s\n", num2face(players->card[1].face), num2suit(players->card[1].suit));
printf("Player Chip Count: %d\n", players->chips);
printf("Player Role: %s\n", num2role(players->role));
printf("Player Action: %s\n", num2action(players->action));
printf("Player Bet: %d\n", players->bet);
printf("Player to my right: %p\n", players->next);
printf("Player to my right: %p\n", players->prev);
getchar();
players = players -> next;
}

printf("\n---- Output for the Player Setup ----\n");
printf("Player ID: %p\n", players);
printf("Player Card array memory address: %p\n", players->card);
printf("Player First Card:  %s of %s\n", num2face(players->card[0].face), num2suit(players->card[0].suit));
printf("Player Second Card: %s of %s\n", num2face(players->card[1].face), num2suit(players->card[1].suit));
printf("Player Chip Count: %d\n", players->chips);
printf("Player Role: %s\n", num2role(players->role));
printf("Player Action: %s\n", num2action(players->action));
printf("Player Bet: %d\n", players->bet);
printf("Player to my right: %p\n", players->next);
printf("Player to my right: %p\n", players->prev);
getchar();
players = players -> next;






		// --- (5) *Calculate Dealt Probabilities* --- //





		// --- (6) First Round of Betting --- //


	// }







	return 0;

}





/*





	}




	// --- First round of betting --- //
	// Ante or blinds
	// Bets can be made according to betting rules
	// Suggest bet according to probability and opponents

	// --- The Flop --- ///
	// Burn one and flop three cards
	// Calculate probabilities

	// --- Second round of betting --- //
	// Starting with little blind, go around betting according to rules
	// Suggest bet

	// --- The turn --- //
	// Burn one and turn one card
	// Calculate probabilities

	// --- Third round of betting --- //

	// --- The River --- //
	// Burn one and turn one card 

	// --- Last Round of Betting --- //

	// --- Reveal cards --- //
	// Determine best five card each person has
	// Determine the winner


	free(player);
	free(used_cards);

	return 0;
}
*/




// --- Functions --- ///

const char* num2face(int in) {
	switch(in) {
		case 0:
			return "Ace";
			break;
		case 1:
			return "Two";
			break;
		case 2:
			return "Three";
			break;
		case 3:
			return "Four";
			break;
		case 4:
			return "Five";
			break;
		case 5:
			return "Six";
			break;
		case 6:
			return "Seven";
			break;
		case 7:
			return "Eight";
			break;
		case 8:
			return "Nine";
			break;
		case 9:
			return "Ten";
			break;
		case 10:
			return "Jack";
			break;
		case 11:
			return "Queen";
			break;
		case 12:
			return "King";
			break;
		default:
			printf("Bad call to function.\n");
			exit(EXIT_FAILURE);
	}
}



const char* num2suit(int in) {
	switch(in) {
		case 0:
			return "Spades";
			break;
		case 1:
			return "Clovers";
			break;
		case 2:
			return "Hearts";
			break;
		case 3:
			return "Diamonds";
		default:
			printf("Bad call to function.\n");
			exit(EXIT_FAILURE);
	}
}



const char* num2role(int in) {
	switch(in) {
		case 0:
			return "none";
			break;
		case 1:
			return "dealer";
			break;
		case 2:
			return "small blind";
			break;
		case 3:
			return "big blind";
		default:
			printf("Bad call to function.\n");
			exit(EXIT_FAILURE);
	}
}



const char* num2action(int in) {
	switch(in) {
		case 0:
			return "fold";
			break;
		case 1:
			return "call";
			break;
		case 2:
			return "raise";
			break;
		case 3:
			return "check";
		default:
			printf("Bad call to function.\n");
			exit(EXIT_FAILURE);
	}
}


