#include "future.h"
#include<stdio.h>
#include<stdlib.h>


void add_future_card(future_cards_t * fc, size_t index, card_t * ptr) {
  if (index >= fc->n_decks) {
    //fc->decks = realloc(fc->decks, (index+1) * sizeof(*fc->decks));                                                                                                    
    for (int i = fc->n_decks; i<= (index); i++) {
      fc->decks = realloc(fc->decks, (i+1) * sizeof(*fc->decks));
      //fc->decks[i] = malloc(sizeof(*fc->decks[i]));                                                                                                                    
      fc->decks[i].n_cards = 0;
      fc->decks[i].cards = NULL;
    }
    fc->n_decks = index+1;
  }
  fc->decks[index].n_cards++;
  fc->decks[index].cards = realloc(fc->decks[index].cards, (fc->decks[index].n_cards) * sizeof(*fc->decks[index].cards));
  fc->decks[index].cards[fc->decks[index].n_cards-1] = ptr;
}


void future_cards_from_deck(deck_t * deck, future_cards_t * fc) {
  int counter=0;
  if (fc->decks != NULL) {
    for (int i=0; i < fc->n_decks; i++) {
      if (fc->decks[i].cards != NULL) {
        for (int j=0; j < fc->decks[i].n_cards; j++) {
          if (deck->n_cards > counter) {
            (*fc->decks[i].cards[j]).value = (*deck->cards[counter]).value;
            (*fc->decks[i].cards[j]).suit = (*deck->cards[counter]).suit;
          }
          else {
            perror("Not enough cards in the deck!");
            exit(42);
          }
        }
        counter++;
      }
    }
  }
}
