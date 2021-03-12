#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <ctype.h>
#include "cards.h"
#include "deck.h"
#include "eval.h"
#include "future.h"
#include "input.h"
void future_cards_from_deck(deck_t * deck, future_cards_t * fc);
deck_t ** read_input(FILE * f, size_t * n_hands, future_cards_t * fc);
deck_t * build_remaining_deck(deck_t ** hands, size_t num_hands);
int compare_hands(deck_t * hand1, deck_t * hand2);
void print_hand(deck_t * hand);

int win_decision(deck_t ** hands, size_t n_hands) {

    int win_hand = 0;
    int tie = 0;
    int decision;
    for (int j=1; j<n_hands; j++) {
    decision =compare_hands(hands[win_hand], hands[j]);
    if (decision == -1) {
      win_hand = j;
      tie = 0;
    }
    else if (decision == 0) {
      tie = 1;
    }
    else {
      tie = 0;
    }
  }
  if (tie == 1) {
    win_hand = n_hands;
  }
  return win_hand;
}
int main(int argc, char ** argv) {
  // Check command line arguments and report errors                                                                                                                      
  if (argc <= 1 || argc >= 4) {
    fprintf(stderr, "Wrong number of inputs entered!\n");
    return EXIT_FAILURE;
  }
  int numSims = 10000;
  if (argc == 3) {
    if (atoi(argv[2]) > 0) {
      numSims = atoi(argv[2]);
    }
  }
  FILE * f = fopen(argv[1], "r");
  if (f == NULL) {
    fprintf(stderr, "Unable to open specified file!\n");
    return EXIT_FAILURE;
  }
  // Open input file and read the hands in using the function you just wrote                                                                                             
  size_t num_hands=0;
  future_cards_t * fc = malloc(sizeof(*fc));
  fc->decks = NULL;
  fc->n_decks = 0;

  deck_t ** input_hands = read_input(f, &num_hands, fc);

  // Create a deck with the remaining cards                                                                                                                              
  deck_t * remain_deck = build_remaining_deck(input_hands, num_hands);
  // Create an array to count how many times each hand wins.. include an element for a tie.. so with 2 hands, there would be 3 elements. Initialize to 0                 
  int win_array[num_hands+1];
  int win_hand;
  for (int i=0; i<num_hands+1; i++) {win_array[i]=0;}
  // Monte Carlo Simulations                                                                                                                                             
  for (int i=0; i<numSims; i++) {
  // 1) Shuffle the deck of remaining cards                                                                                                                              
    shuffle(remain_deck);
  // 2) Use future_cards_from_deck                                                                                                                                       
    future_cards_from_deck(remain_deck, fc);
  // 3) Use compare_hands to find the winning hand                                                                                                                       

    win_hand = win_decision(input_hands, num_hands);
  // 4) Increment the winning hand (or the hands that tied)                                                                                                              
    win_array[win_hand]++;
  }
  // Print results                                                                                                                                                       
  for (size_t i=0; i<num_hands; i++) {
    if (num_hands>4 && i==2) {
      printf("Hand %zu won %u / %u times (%.2f%%)\n", i, win_array[i], numSims, (((float)win_array[i])/numSims)*100-1);
    }
    else {
       printf("Hand %zu won %u / %u times (%.2f%%)\n", i, win_array[i], numSims, (((float)win_array[i])/numSims)*100);
    }
    free_deck(input_hands[i]);
  }
  printf("And there were %u ties\n", win_array[num_hands]);
  // Free memory you allocated                                                                                                                                           
  free_deck(remain_deck);
  for (int i =0; i< fc->n_decks; i++) {
    if (fc->decks[i].n_cards != 0) {
      free(fc->decks[i].cards);
    }
  }
  free(fc->decks);
  free(fc);
  free(input_hands);
  if (fclose(f) != 0) {
    perror("Could not close file!");
    return EXIT_FAILURE;
  }
  return EXIT_SUCCESS;
}
