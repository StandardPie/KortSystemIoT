#include "door_control.h"
#include "card_system.h"
#include "input.h"
#include <stdio.h>
#include <unistd.h>
#include <string.h>

void remote_open_door(void) {
    printf("Currently lamp is: green\n");
    printf("Door is open for 3 seconds...\n");
    sleep(3);
    printf("Door closed.\n");
}

void simulate_card_scan(CardSystem* system) {
    char card_number[20];
    get_string_input("Enter Card: ", card_number, sizeof(card_number));

    Card* card = card_system_find_card(system, card_number);
    if (card != NULL && card->has_access) {
        printf("Currently lamp is: green\n");
        printf("Access granted! Door is open for 3 seconds...\n");
        sleep(3);
        printf("Door closed.\n");
    } else {
        printf("Currently lamp is: red\n");
        printf("Access denied!\n");
    }
}