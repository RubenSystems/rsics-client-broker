//
//  client_cache.c
//  rsics_client_broker
//
//  Created by Ruben Ticehurst-James on 29/10/2022.
//

#include "../def/client_cache.h"
#include <time.h>
#include <string.h>

/*
 Impl similar to python's dictionary.
 https://github.com/python/cpython/blob/main/Objects/dictobject.c#L745
 */

static int initial_size = 8;
static int growth_rate = 3;
static int probe_shift = 5;

// MARK: - Helper Defs
unsigned long hash(key_type);

char keys_equal (key_type, key_type);

// MARK: - Impl
void init_cache(struct Cache * cache) {
	cache->data = calloc(initial_size, initial_size);
	memset(cache->data, 0, sizeof(struct CacheNode) * initial_size);
	cache->size = 0;
	cache->allocated_size = initial_size;
}

void cache_add(struct Cache * cache, struct CacheNode * node) {
	unsigned int mask = cache->allocated_size - 1;
	unsigned long index = hash(node->transaction_id) & mask;
	unsigned long probe = hash(node->transaction_id);
	long current_time = time(NULL);
	while (1) {
		if (cache->data[index].transaction_id[0] == 0) {
			// value is not set as it starts with null term
			cache->data[index] = *node;
			cache->size++;
			return;
		} else if (strcmp(cache->data[index].transaction_id, node->transaction_id) == 0) {
			// Same ids, override node in current position.
			cache->data[index] = *node;
			return;
		} else if (cache->data[index].ttl < current_time) {
			// There is a value but it has expired so can be replaced
			// No need to increment size as it has been incremented already;
			cache->data[index] = *node;
			return;
		}
		
		probe >>= probe_shift;
		index = mask & (index * 5 + probe + 1);
		printf("CLASH %i\n", index);
	}
}

struct CacheNode * cache_get(struct Cache * cache, key_type key) {
	unsigned int mask = cache->allocated_size - 1;
	unsigned long index = hash(key) & mask;
	unsigned long probe = hash(key);
	unsigned long begin_index = index;
	long current_time = time(NULL);
	unsigned long prev_index = index;

	while (1) {
		if (strcmp(key, cache->data[index].transaction_id) == 0 && current_time <= cache->data[index].ttl ) {
			// there is a value in that has the exact same index AND it has not expired
			return &cache->data[index];
		} else if (strcmp(key, cache->data[index].transaction_id) == 0 && current_time > cache->data[index].ttl ) {
			// There is a val that has the exact same index AND it has expired
			cache->data[index].transaction_id[0] = 0;
			return NULL;
		}
		prev_index = index;
		probe >>= probe_shift;
		index = mask & (index * 5 + probe + 1);
		if (index == begin_index && prev_index != begin_index) {
			return NULL;
		}

	}
}


// MARK: - Helper Impl
unsigned long hash(key_type key) {
	unsigned long hash;
	
	hash = 5381;
	for (int i = 0; i < UID_SIZE; i ++) {
		if (key[i] == 0) {
			break;
		}
		hash = ((hash << 5) + hash) + key[i];
	}
	return hash;
}
