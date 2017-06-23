
#include <string.h>
#include <stdint.h>
#include <stdlib.h>
#include "tlv_oo.h"

struct tlv_node {
	struct tlv_node *next;
	uint8_t type;
	uint8_t length;
	uint8_t value[];
};

struct TLV {
	struct tlv_node *volatile head;
	uint8_t total_type;
	uint32_t total_length;
};

static tlv_p tlv_create()
{
	tlv_p tlv = malloc(sizeof(*tlv));
	if(tlv == NULL) {
		return NULL;
	}

	tlv->head = NULL;
	tlv->total_length = 0;
	tlv->total_type = 0;
	return tlv;
}

static uint8_t tlv_append(tlv_p tlv, const TLV_TOKEN *tlv_token)
{
	struct tlv_node *node = malloc(sizeof(*node) + (tlv_token->length * sizeof(uint8_t)));
	struct tlv_node *curr = tlv->head, *prev = NULL;

	if(node == NULL) {
		return d_tlv_malloc_fail;
	}

	node->next = NULL;
	node->type = tlv_token->type;
	node->length = tlv_token->length;
	memcpy(node->value, tlv_token->value, tlv_token->length);

	while(curr != NULL) {
		if(curr->type == tlv_token->type) {
			node->next = curr->next;
			prev->next = node;
			free(curr);
			return d_tlv_ok;
		}
		prev = curr;
		curr = curr->next;
	}

	if(tlv->head == NULL) {
		/* First node */
		tlv->head = node;
	} else {
		prev->next = node;
	}

	tlv->total_type ++;
	tlv->total_length += tlv_token->length;

	return d_tlv_ok;
}

static uint8_t tlv_fetch(tlv_p tlv, TLV_TOKEN *tlv_token)
{
	struct tlv_node *curr = tlv->head;

	while(curr != NULL) {
		if(curr->type == tlv_token->type) {
			if(tlv_token->length >= curr->length) {
				tlv_token->length = curr->length;
				memcpy(tlv_token->value, curr->value, curr->length);
				return d_tlv_ok;
			} else {
				return d_tlv_shortage_of_buffer;
			}
			
		}
		curr = curr->next;
	}
	
	return d_tlv_type_not_found;
}

static uint8_t tlv_delete(tlv_p tlv, uint8_t type)
{
	struct tlv_node *curr = tlv->head, *prev = NULL;

	while(curr != NULL) {
		if(curr->type == type) {
			if(prev == NULL) {
				/* First node */
				tlv->head = curr->next;
			} else {
				prev->next = curr->next;
			}

			tlv->total_type --;
			tlv->total_length -= curr->length;
			free(curr);
			return d_tlv_ok;
		}
		prev = curr;
		curr = curr->next;
	}

	return d_tlv_type_not_found;
}

static void tlv_finish(tlv_p tlv)
{
	struct tlv_node *curr = tlv->head, *next = NULL;

	while(curr != NULL) {
		next = curr->next;
		free(curr);
		curr = next;
	}

	free(tlv);
}

static uint32_t tlv_get_array(tlv_p tlv, uint32_t length, uint8_t *out)
{
	uint32_t ret = 0;
	struct tlv_node *curr;

	if(tlv->total_length > length) {
		return d_tlv_shortage_of_buffer;
	}

	for(curr = tlv->head;curr != NULL;curr = curr->next) {
		out[ret ++] = curr->type;
		out[ret ++] = curr->length;
		memcpy(out+ret, curr->value, curr->length);
		ret += curr->length;
	}

	return ret;
}

/* API gateway */
struct __TLV_API__ TLV = {
	.create = tlv_create,
	.append = tlv_append,
	.fetch = tlv_fetch,
	.delete = tlv_delete,
	.finish = tlv_finish,
	.get_array = tlv_get_array,
};
