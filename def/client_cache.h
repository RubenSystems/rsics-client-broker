//
//  client_cache.h
//  rsics_client_broker
//
//  Created by Ruben Ticehurst-James on 29/10/2022.
//

#ifndef client_cache_h
#define client_cache_h

#include <stdlib.h>
#include <stdio.h>
#include "../RSiCS/definition/models.h"

#define UID_SIZE 36
typedef char key_type[UID_SIZE];
typedef struct Computer value_type;


struct CacheNode {
	key_type transaction_id;
	value_type transaction_creator;
	unsigned long ttl;
};

struct Cache {
	struct CacheNode * 	data;
	unsigned int 		size;
	unsigned int 		allocated_size;
};

enum CacheInvalidationResult {
	INVALIDATION_SUCCESS,
	INVALIDATION_NOTFOUND
};

void init_cache(struct Cache *);

void cache_add(struct Cache *, struct CacheNode *);

struct CacheNode * cache_get(struct Cache *, key_type);

enum CacheInvalidationResult cache_invalidate(struct Cache *, struct CacheNode *, key_type);


#endif /* client_cache_h */
