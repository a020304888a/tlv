#ifndef _TLV_OO_H
#define _TLV_OO_H

#include <stdint.h>

#define d_tlv_ok					0x00
#define d_tlv_shortage_of_buffer	0x01
#define d_tlv_type_not_found		0x02
#define d_tlv_append_found_type		0x03
#define d_tlv_malloc_fail			0x04


typedef struct TLV *tlv_p;

typedef struct __TLV_TOKEN__ {
	uint8_t type;
	uint8_t length; // 0~255 bytes
	uint8_t *value; // allocat by user
} TLV_TOKEN;

extern struct __TLV_API__ {
	/**
	 *
	 */
	tlv_p (*create)();
	
	/**
	 *
	 */
	uint8_t (*append)(tlv_p tlv, const TLV_TOKEN *tlv_token);
	
	/**
	 *
	 */
	uint8_t (*fetch)(tlv_p tlv, TLV_TOKEN *tlv_token);
	
	/**
	 *
	 */
	uint8_t (*delete)(tlv_p tlv, uint8_t type);
	
	/**
	 *
	 */
	void (*finish)(tlv_p tlv);

	/** 
	 * get tlv array 
	 * return length
	 * allocate uint8_t *out by user
	 */
	uint32_t (*get_array)(tlv_p tlv, uint32_t length, uint8_t *out);


} TLV;

#endif
