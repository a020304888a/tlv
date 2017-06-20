#ifndef TLV_OO_H
#define TLV_OO_H

#include "tlv_typedef.h"

typedef struct _tlvs {
	tlv_uint8 type;
	tlv_uint16 length;
	tlv_uint8 *value;
} tlvs;

tlv_uint8 tlv_array_append(tlv_uint8 *buff, tlv_uint16 maxsize, tlv_uint16 *buffsize, const tlvs *tlv);
tlv_uint8 tlv_array_fetch(tlv_uint8 *buff, const tlv_uint16 *buffsize, tlv_uint8 type, tlvs *tlv);
tlv_uint8 tlv_array_delete(tlv_uint8 *buff, tlv_uint16 *buffsize, tlv_uint8 type);
tlv_uint8 tlv_array_show_all(tlv_uint8 *buff, const tlv_uint16 *buffsize);

#endif
