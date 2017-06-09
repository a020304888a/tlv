#ifndef TLV_H
#define TLV_H

#define uint_8						unsigned char			
#define uint_16						unsigned short			
#define uint_32						unsigned int			

#define d_tlv_ok					0x00
#define d_tlv_shortage_of_buffer	0x01
#define d_tlv_type_not_found		0x02
#define d_tlv_append_found_type		0x03

typedef struct _tlvs {
	uint_8 type;
	uint_16 length;
	uint_8 *value;
} tlvs;

uint_8 tlv_array_append(uint_8 *buff, uint_16 maxsize, uint_16 *buffsize, const tlvs *tlv);
uint_8 tlv_array_fetch(uint_8 *buff, const uint_16 *buffsize, uint_8 type, tlvs *tlv);
uint_8 tlv_array_delete(uint_8 *buff, uint_16 *buffsize, uint_8 type);
uint_8 tlv_array_show_all(uint_8 *buff, const uint_16 *buffsize);

#endif
