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
#include <string.h>



static void new_client(void * context, struct Computer from_computer, const char * message, int message_size) {
	struct Cache * cache = (struct Cache *)context;
	struct CacheNode * connector = NULL;
	if (message_size > UID_SIZE - 1) {
		return;
	}
	if (cache_invalidate(cache, connector, (char *)message) == INVALIDATION_NOTFOUND) {
		struct CacheNode new_client = {
			.transaction_creator = from_computer,
			.ttl = time(NULL) + 60 // In cache for 60 seconds
		};
		strncpy(new_client.transaction_id, message, UID_SIZE - 1);
		
		cache_add(cache, &new_client);
	} else {
		// Send connection info about joiner to creator
		transmit((char *)&connector->transaction_creator, sizeof(struct Computer), &from_computer);
		
		// Send connection info about joiner to creator
		transmit((char *)&from_computer, sizeof(struct Computer), &connector->transaction_creator);
		
	}
}


int main(int argc, const char * argv[]) {
	// insert code here...
	
	struct Cache pending_clients;
	init_cache(&pending_clients);
	
	struct Computer server;
	create_listener("5253", &server);
	char is_active = 1;
	observe_with_context(&server, &is_active, &pending_clients, new_client);
	
	
	
	
	
	
	return 0;
}
