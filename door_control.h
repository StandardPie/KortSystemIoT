#ifndef DOOR_CONTROL_H
#define DOOR_CONTROL_H

#include "card_system.h"

void remote_open_door(void);
void simulate_card_scan(CardSystem* system); // Simulate scanning card

#endif