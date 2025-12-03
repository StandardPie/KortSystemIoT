#include "card_system.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define INITIAL_CAPACITY 10

void card_system_init(CardSystem* system) {
system->cards = NULL;
system->count = 0;
system->capacity = 0;
}



void card_system_free(CardSystem* system) {
if (system->cards != NULL) {
    free(system->cards);
}
system->cards = NULL;
system->count = 0;
system->capacity = 0;
}

// add card to system
int card_system_add_card(CardSystem* system, const char* card_number, int has_access) {
if (system->count >= system->capacity) {
size_t new_capacity = (system->capacity == 0) ? INITIAL_CAPACITY : system->capacity * 2;
Card* new_cards = realloc(system->cards, new_capacity * sizeof(Card));

if (new_cards == NULL) {
    return 0;
}

system->cards = new_cards;
system->capacity = new_capacity;
}








// Check if card already exists
Card* existing = card_system_find_card(system, card_number);
if (existing != NULL) {
    existing->has_access = has_access;
    return 1;
}

// Add new card 
Card* new_card = &system->cards[system->count];
strncpy(new_card->card_number, card_number, sizeof(new_card->card_number) - 1);
new_card->card_number[sizeof(new_card->card_number) - 1] = '\0';
new_card->has_access = has_access;
new_card->added_date = time(NULL);

system->count++;
return 1;
}

// Remove card (by card number )
int card_system_remove_card(CardSystem* system, const char* card_number) {
for (size_t i = 0; i < system->count; i++) {
if (strcmp(system->cards[i].card_number, card_number) == 0) {
    for (size_t j = i; j < system->count - 1; j++) {
        system->cards[j] = system->cards[j + 1];
    }
    system->count--;
    return 1;
}
}
return 0;
}


// find card 
Card* card_system_find_card(CardSystem* system, const char* card_number) {
for (size_t i = 0; i < system->count; i++) {
    if (strcmp(system->cards[i].card_number, card_number) == 0) {
        return &system->cards[i];
    }
}
return NULL;
}


// List all cards
void card_system_list_cards(CardSystem* system) {
if (system->count == 0) {
    printf("No cards in system.\n");
    return;
}

for (size_t i = 0; i < system->count; i++) {
Card* card = &system->cards[i];
struct tm* time_info = localtime(&card->added_date);
char date_str[20];
strftime(date_str, sizeof(date_str), "%Y-%m-%d", time_info);

printf("%s (%s) (added: %s)\n", 
        card->card_number,
        card->has_access ? "access" : "No access",
        date_str);
}
}

// Save
int card_system_save_to_file(CardSystem* system, const char* filename) {
FILE* file = fopen(filename, "w");
if (file == NULL) {
    return 0;
}

for (size_t i = 0; i < system->count; i++) {
    Card* card = &system->cards[i];
    fprintf(file, "%s,%d,%ld\n", card->card_number, card->has_access, card->added_date);
}

fclose(file);
return 1;
}

int card_system_load_from_file(CardSystem* system, const char* filename) {
FILE* file = fopen(filename, "r");
if (file == NULL) {
    return 0;
}

card_system_free(system);

char line[100];
while (fgets(line, sizeof(line), file) != NULL) {
    char card_number[20];
    int has_access;
    time_t added_date;
    
    if (sscanf(line, "%19[^,],%d,%ld", card_number, &has_access, &added_date) == 3) {
        card_system_add_card(system, card_number, has_access);
        system->cards[system->count - 1].added_date = added_date;
    }
}

fclose(file);
return 1;
}