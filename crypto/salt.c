//
//  salt.c
//  rsics_client_broker
//
//  Created by Ruben Ticehurst-James on 03/11/2022.
//

#include "salt.h"
#include <time.h>
#include <stdlib.h>



static const char valid_chars[] = "134567890qwertyuiopasdfghjklzxcvbnmQWERTYUIOPASDFGHJKLZXCVBNM";

void generate_salt(struct Salt * value) {
	srand((unsigned int)time(NULL));
	value->generation_time = time(NULL);
	int valid_chars_size = sizeof(valid_chars) / sizeof(char);
	for (int i = 0; i < SALT_LENGTH; i++) {
		value->salt_value[i] = valid_chars[rand() % (valid_chars_size - 1)];
	}
}
