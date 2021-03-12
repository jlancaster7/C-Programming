#include <stdio.h>
#include <stdlib.h>
#include "input.h"
#include <string.h>
void add_future_card(future_cards_t * fc, size_t index, card_t * ptr);
card_t * add_empty_card(deck_t * deck);
card_t card_from_letters(char value_let, char suit_let);
void asserrt_card_valid(card_t c);

deck_t ** read_input(FILE * f, size_t * n_hands, future_cards_t * fc) {
  if (f == NULL) {
    perror("Could not open the file!");
    return NULL;
  }
  //fc->decks = NULL;                                                                                                                                                    
  //fc->n_decks = 0;                                                                                                                                                     
  deck_t ** input_decks = NULL;
  char * line = NULL;
  size_t sz =0;
  while (getline(&line, &sz, f) >0) {
    if (strspn(line, " \r\n\t") != strlen(line)) {
      ++*n_hands;
      input_decks = realloc(input_decks, *n_hands * sizeof(deck_t));
      input_decks[*n_hands-1] = hand_from_string(line, fc);

      if (input_decks[*n_hands-1] == NULL) {
        continue;
      }
    }
  }
  free(line);

  return input_decks;
}

deck_t * hand_from_string(char * str, future_cards_t * fc) {
  deck_t * temp = malloc(sizeof(deck_t));
  char * token = strtok(str, " ");
  temp->cards = NULL;
  temp->n_cards =0;
  size_t n = 0;
  card_t * temp_card;
  card_t temp_card2;
  while (strcmp(token, "\n") != 0) {
    if (token[0] == '?' && (token[1] >= '0' && token[1] <= '9')) {
      RemoveChars(token, '?');
      RemoveChars(token, '\n');
      if (atoi(token) <= 52) {
        n++;
        //temp_card = add_empty_card(temp);                                                                                                                              
        add_future_card(fc, atoi(token), add_empty_card(temp));
      }
    }
    else {
      temp_card2 = card_from_letters(token[0], token[1]);
      if ((temp_card2.value > 1 && temp_card2.value < 15) && (temp_card2.suit >=0 && temp_card2.suit <4)) {
        n++;
        add_card_to(temp, temp_card2);
      }
    }
    token = strtok(NULL," ");
    temp_card = NULL;
    if (token == NULL) {
      break;
    }
  }
  temp->n_cards = n;
  free(temp_card);
  if (n < 5) {
    perror("Not enough cards in this hand!");
    return NULL;
  }
  return temp;
}

void RemoveChars(char *s, char c)
{
  int writer = 0, reader = 0;

  while (s[reader])
    {
      if (s[reader]!=c)
        {
          s[writer++] = s[reader];
        }

      reader++;
    }

  s[writer]=0;
}
