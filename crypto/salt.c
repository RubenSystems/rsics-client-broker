//
//  salt.c
//  rsics_client_broker
//
//  Created by Ruben Ticehurst-James on 03/11/2022.
//

#include "salt.h"
#include <time.h>
#include <stdlib.h>

static const char valid_chars[] = "134567890qwertyuiopasdfghjklzxcvbnmQWERTYUIOPASDFGHJKLZXCVBNM!@£$%^&*";

void generate_salt(struct Salt * value) {
	value->generation_time = time(NULL);
	for (int i = 0; i < SALT_LENGTH; i++) {
		value->salt_value[i] = valid_chars[rand() % ((sizeof(valid_chars) / sizeof(char)) - 1)];
	}
}
