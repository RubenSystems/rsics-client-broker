//
//  main.c
//  rsics_client_broker
//
//  Created by Ruben Ticehurst-James on 27/10/2022.
//

#include <stdio.h>
#include "RSiCS/definition/observe.h"

#include "RSiCS/definition/transmit.h"
#include "RSiCS/definition/models.h"


static void new_client(void * context, struct Computer from_computer, const char * message, int message_size) {
	printf("%s\n", message);
	transmit("hello there!", 12, &from_computer);
}

int main(int argc, const char * argv[]) {
	// insert code here...
	
	struct Computer server;
	create_listener("5253", &server);
	char is_active = 1;
	observe(&server, &is_active, new_client);
	
	return 0;
}
