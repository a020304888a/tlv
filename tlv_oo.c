
#include <string.h>
#include <stdint.h>
#include "tlv_oo.h"

struct tlv_node {
	struct tlv_node *next;
	uint8_t type;
	uint8_t length;
	uint8_t value[];
};

struct TLV {
	struct tlv_node *volatile head;
	struct tlv_node *volatile tail;
};

static tlv_p tlv_create()
{
	tlv_p tlv = malloc(sizeof(*tlv);
	if(tlv == NULL) {
		return NULL;
	}

	tlv->head = NULL;
	tlv->tail = NULL;
	return tlv;
}

static uint8_t tlv_append(tlv_p tlv, const TLV_TOKEN *tlv_token)
{
	struct tlv_node *node = malloc(sizeof(*node) + (length * sizeof(uint8_t));
	if(node == NULL) {
		return d_tlv_malloc_fail;
	}

	node->next = NULL;
	node->type = tlv_token->type;
	node->length = tlv_token->length;
	memcpy(node->value, tlv_token->value, tlv_token->length);

	if(tlv->head == NULL) {
		tlv->head = node;
		tlv->tail = node;
	} else {
		tlv->tail->next = node;
		tlv->tail = node;
	}

	return d_tlv_ok;
}

static uint8_t tlv_fetch(tlv_p tlv, TLV_TOKEN *tlv_token)
{
	struct tlv_node *curr;

	for(curr = tlv->head;curr != NULL;curr = curr->next) {
		if(curr->type == tlv_token->type) {
			tlv_token->length = curr->length;
			memcpy(tlv_token->value, curr->value, curr->length);
			return d_tlv_ok;
		}
	}
	
	return d_tlv_type_not_found;
}

static uint8_t tlv_delete(tlv_p tlv, uint8_t type)
{
	struct tlv_node *curr;

	for(curr = tlv->head;curr != NULL;curr = curr->next) {

	}
}

static void tlv_finish()
{

}

static uint32_t tlv_get_array(tlv_p tlv, uint8_t *out)
{

}


/* API gateway */
struct __TLV_API__ TLV {
	.create = tlv_create,
	.append = tlv_append,
	.fetch = tlv_fetch,
	.delete = tlv_delete,
	.finish = tlv_finish,
	.get_array = tlv_get_array,
};
