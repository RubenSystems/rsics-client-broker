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
#include "crypto/salt.h"
#include <time.h>
#include <unistd.h>
#include <string.h>



static void new_client(const void * context, struct Computer from_computer, void * message, int message_size) {
	struct Cache * cache = (struct Cache *)context;
	struct CacheNode connector;
	memset(&connector, 0, sizeof(struct CacheNode));
	
	if (message_size > UID_SIZE - 1) {
		return;
	}
	printf("%s\n", (const char *)message);
	if (cache_invalidate(cache, &connector, (char *)message) == INVALIDATION_NOTFOUND) {
		printf("IN CAACHE\n");
		struct CacheNode new_client = {
			.transaction_creator = from_computer,
			.ttl = time(NULL) + 5 // In cache for n seconds
		};
		strncpy(new_client.transaction_id, message, UID_SIZE - 1);
		
		cache_add(cache, &new_client);
	} else {
		printf("JOINING\n");
		// Send connection info about joiner to creator
		printf("%i %i", connector.transaction_creator.socket_address_size, from_computer.socket_address_size);
		transmit((char *)&(connector.transaction_creator), sizeof(struct Computer), &from_computer);
		
		// Send connection info about joiner to creator
		transmit((char *)&from_computer, sizeof(struct Computer), &connector.transaction_creator);
		memset(&connector, 0, sizeof(struct CacheNode));
	}
}


int main(int argc, const char * argv[]) {
	// insert code here...

	struct Cache pending_clients;
	init_cache(&pending_clients);
	
	struct Computer server;
	create_listener("5254", &server);
	char is_active = 1;
	observe_with_context(&server, &is_active, &pending_clients, new_client);
	
	
	
	
	return 0;
}
