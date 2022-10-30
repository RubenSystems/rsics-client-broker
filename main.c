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

#include "def/client_cache.h"
#include <time.h>
#include <unistd.h>

static void new_client(void * context, struct Computer from_computer, const char * message, int message_size) {
	printf("%s\n", message);
	transmit("hello there!", 12, &from_computer);
}

int main(int argc, const char * argv[]) {
	// insert code here...
	
//	struct Computer server;
//	create_listener("5253", &server);
//	char is_active = 1;
//	observe(&server, &is_active, new_client);
	
	struct Cache client_broker;
	init_cache(&client_broker);
	
	struct CacheNode node = {
		.transaction_id = "hello there",
		.transaction_creator = 1,
		.ttl = time(NULL) + 1000
	};
	
	struct CacheNode node2 = {
		.transaction_id = "hello there2",
		.transaction_creator = 2,
		.ttl = time(NULL)
	};
	
	cache_add(&client_broker, &node);
	cache_add(&client_broker, &node2);
	
	printf("size: %i\n", client_broker.size);
	sleep(10);
	struct CacheNode * val =  cache_get(&client_broker, "hello there");
	if (val) {
		printf("%i\n", val->transaction_creator);
	} else {
		printf("NOT IN\n");
	}
	
	
	return 0;
}
