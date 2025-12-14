#ifndef CARD_SYSTEM_H
#define CARD_SYSTEM_H

#include <time.h>

typedef struct {
	char card_number[20];
	int has_access;
	time_t added_date;
} Card;

typedef struct {
	Card* cards;
	size_t count;
	size_t capacity;
} CardSystem;

void card_system_init(CardSystem* system);
void card_system_free(CardSystem* system);
int card_system_add_card(CardSystem* system, const char* card_number, int has_access);
int card_system_remove_card(CardSystem* system, const char* card_number);
Card* card_system_find_card(CardSystem* system, const char* card_number);
void card_system_list_cards(CardSystem* system);
int card_system_save_to_file(CardSystem* system, const char* filename);
int card_system_load_from_file(CardSystem* system, const char* filename);

#endif