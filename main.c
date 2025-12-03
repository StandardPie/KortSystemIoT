#include <stdio.h>
#include <stdlib.h>
#include "card_system.h"
#include "door_control.h"
#include "input.h"

#define DATA_FILE "cards.dat"

void display_menu(void) {
printf("\nAdmin Menu\n");
printf("1. Remote Open Door\n");
printf("2. List all cards in system\n");
printf("3. Add/remove access\n");
printf("4. Exit\n");
printf("5. Fake test scan card\n");
}

void handle_add_remove_access(CardSystem* system) {
char card_number[20];
get_string_input("Enter Card Number: ", card_number, sizeof(card_number));

Card* existing_card = card_system_find_card(system, card_number);

if (existing_card != NULL) {
printf("Card %s currently has %s\n", 
    card_number, 
    existing_card->has_access ? "ACCESS" : "NO ACCESS");
} else {
printf("Card %s not found. It will be created.\n", card_number);
}

printf("1. Add access\n");
printf("2. Revoke access\n");
printf("q to back to menu\n");

char choice[10];
get_string_input("Choose option: ", choice, sizeof(choice));

if (choice[0] == '1') {
card_system_add_card(system, card_number, 1);
printf("Access granted for card %s\n", card_number);
} else if (choice[0] == '2') {
card_system_add_card(system, card_number, 0);
printf("Access revoked for card %s\n", card_number);
} else if (choice[0] == 'q' || choice[0] == 'Q') {
return;
} else {
printf("Invalid choice.\n");
}
}

int main(void) {
CardSystem system;
card_system_init(&system);

printf("=== Card Access Control System ===\n");

if (card_system_load_from_file(&system, DATA_FILE)) {
printf("Loaded existing card data.\n");
} else {
printf("No existing data found. Starting with empty system.\n");
}











int running = 1;
while (running) {
display_menu();
int choice = get_int_input("Select option:");



// menu

switch (choice) {
case 1:
    remote_open_door();
    break;
    
case 2:
    printf("\nAll cards in system:\n");
card_system_list_cards(&system);
    printf("Press Enter to continue...");
    getchar(); 
    getchar(); // wait for enter
  break;
    
case 3:
handle_add_remove_access(&system);
    break;
    
case 4:
  running = 0;
  break;
    
case 5:
    simulate_card_scan(&system);
  break;
    
default:
  printf("Invalid option. Please try again.\n");
  break;
}
}










// save data on exit


if (card_system_save_to_file(&system, DATA_FILE)) {
printf("Card data saved successfully.\n");
} else {
printf("Warning: Could not save card data!\n");
}

card_system_free(&system);
printf("Exitign\n");

return 0;
}
