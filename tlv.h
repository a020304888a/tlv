#ifndef TLV_H
#define TLV_H

#include "tlv_typedef.h"

typedef struct _tlvs {
	uint8_t type;
	uint16_t length;
	uint8_t *value;
} tlvs;

uint8_t tlv_array_append(uint8_t *buff, uint16_t maxsize, uint16_t *buffsize, const tlvs *tlv);
uint8_t tlv_array_fetch(uint8_t *buff, const uint16_t *buffsize, uint8_t type, tlvs *tlv);
uint8_t tlv_array_delete(uint8_t *buff, uint16_t *buffsize, uint8_t type);
uint8_t tlv_array_show_all(uint8_t *buff, const uint16_t *buffsize);

#endif
