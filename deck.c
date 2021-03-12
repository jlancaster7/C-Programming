#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "deck.h"
void print_card(card_t c);
card_t card_from_num(unsigned c);
void free_deck(deck_t * deck);

void add_card_to(deck_t * deck, card_t c) {
  deck->n_cards++;
  deck->cards = realloc(deck->cards, deck->n_cards * sizeof(*deck->cards));
  deck->cards[deck->n_cards - 1] = malloc(sizeof(c));
  deck->cards[deck->n_cards - 1]->suit = c.suit;
  deck->cards[deck->n_cards - 1]->value = c.value;
}

card_t * add_empty_card(deck_t * deck) {
  deck->n_cards++;
  deck->cards = realloc(deck->cards, deck->n_cards * sizeof(*deck->cards));
  deck->cards[deck->n_cards - 1] = malloc(sizeof(card_t));
  deck->cards[deck->n_cards - 1]->value = 0;
  deck->cards[deck->n_cards - 1]->suit = 0;
  return deck->cards[deck->n_cards - 1];
}

deck_t * make_deck_exclude(deck_t * excluded_cards) {
  card_t temp;
  int exclude;
  deck_t * deck = malloc(sizeof(*deck));
  deck->cards = malloc(sizeof(*deck->cards));
  deck->n_cards = 0;
  for (int i=0; i<52; i++) {
    temp = card_from_num(i);
    exclude = 0;
    for (int j=0; j<excluded_cards->n_cards; j++) {
      if (temp.suit == excluded_cards->cards[j]->suit && temp.value == excluded_cards->cards[j]->value) {
        exclude = 1;
        break;
      }
    }
    if (exclude != 1) {
      add_card_to(deck, temp);
    }
  }
  free_deck(excluded_cards);
  return deck;
}

deck_t * build_remaining_deck(deck_t ** hands, size_t n_hands) {
  deck_t * temp = malloc(sizeof(deck_t));
  temp->cards = NULL;
  temp->n_cards = 0;
  for (int i=0; i < n_hands; i++) {
    for (int j=0; j < hands[i]->n_cards; j++) {
      add_card_to(temp, *hands[i]->cards[j]);
    }
  }
  return make_deck_exclude(temp);
}
void free_deck(deck_t * deck) {
  for (int i=0; i<deck->n_cards; i++) {
    free(deck->cards[i]);
  }
  free(deck->cards);
  free(deck);
}

void print_hand(deck_t * hand){

  for (int i=0; i < hand->n_cards; i++) {
    print_card(*hand->cards[i]);
  }
}

int deck_contains(deck_t * d, card_t c) {
  for (int i=0; i < d->n_cards; i++) {
    if ((d->cards[i]->value == c.value) && (d->cards[i]->suit == c.suit)) {
      return 1;
    }
  }
  return 0;
}

void shuffle(deck_t * d){
  //int randnum = random() % (d->n_cards/3);                                                                                                                             
  int randnum = 0;
  int shufpos;
  card_t * temp;
  for (int i=randnum; i<d->n_cards; i++) {
    shufpos = random() % d->n_cards;
    temp = d->cards[shufpos];
    d->cards[shufpos] = d->cards[i];
    d->cards[i] = temp;
  }
}

void assert_full_deck(deck_t * d) {
  card_t temp;
  for (int i=2; i<15; i++) {
    temp.value = i;
    for (int j=0; j<4; j++) {
      temp.suit = j;
      assert(deck_contains(d, temp) == 1);
    }
  }
}
