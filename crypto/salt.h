//
//  salt.h
//  rsics_client_broker
//
//  Created by Ruben Ticehurst-James on 03/11/2022.
//

#ifndef salt_h
#define salt_h

#include <stdio.h>

#define SALT_LENGTH 16

struct Salt {
	char salt_value[SALT_LENGTH];
	double generation_time;
};

void generate_salt(struct Salt *);


#endif /* salt_h */
