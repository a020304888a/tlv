#include <stdio.h>
#include <string.h>
#include "tlv_typedef.h"
#include "tlv.h"

#define d_sizeof_uint8_uint16 	(3)

tlv_uint8 tlv_array_append(tlv_uint8 *buff, tlv_uint16 maxsize, tlv_uint16 *buffsize, const tlvs *tlv)
{
	tlv_uint16 offset = 0;
	tlv_uint16 currsize = *buffsize;

	if(maxsize < currsize + tlv->length)
		return d_tlv_shortage_of_buffer;

	while(offset < currsize) {
		//found
		if(buff[offset] == tlv->type)
			return d_tlv_append_found_type;

		offset += ((buff[offset + 1] << 8) + buff[offset + 2] + d_sizeof_uint8_uint16);
	}

	//not found
	buff[currsize ++] = tlv->type;
	buff[currsize ++] = (tlv_uint8)(tlv->length >> 8);
	buff[currsize ++] = (tlv_uint8)tlv->length;
	memcpy(&buff[currsize], tlv->value, tlv->length);
	currsize += tlv->length;
	*buffsize = currsize;

	return d_tlv_ok;
}


/* this function do not allocate memory for tlv value, please assign in advance */
tlv_uint8 tlv_array_fetch(tlv_uint8 *buff, const tlv_uint16 *buffsize, tlv_uint8 type, tlvs *tlv)
{
	tlv_uint16 offset = 0;

	while(offset < *buffsize) {
		//found
		if(buff[offset] == type) {
			tlv->type = buff[offset];
			tlv->length = (buff[offset + 1] << 8) + buff[offset + 2];
			memcpy(tlv->value, &buff[offset + 3], tlv->length);

			return d_tlv_ok;
		}
			
		offset += ((buff[offset + 1] << 8) + buff[offset + 2] + d_sizeof_uint8_uint16);
	}

	//not found
	return d_tlv_type_not_found;
}

tlv_uint8 tlv_array_delete(tlv_uint8 *buff, tlv_uint16 *buffsize, tlv_uint8 type)
{
	tlv_uint16 offset = 0;
	tlv_uint16 currsize = *buffsize;
	tlv_uint16 blocksize = 0;

	while(offset < currsize) {

		blocksize = ((buff[offset + 1] << 8) + buff[offset + 2] + d_sizeof_uint8_uint16);
		
		//found
		if(buff[offset] == type) {
			memmove(&buff[offset], &buff[offset + blocksize], currsize - (offset + blocksize));
			*buffsize = currsize - blocksize;
			return d_tlv_ok;
		}
		
		offset += blocksize;
	}

	//not found
	return d_tlv_type_not_found;
}

tlv_uint8 tlv_array_show_all(tlv_uint8 *buff, const tlv_uint16 *buffsize)
{
	int i = 0;
	tlv_uint16 offset = 0;
	tlv_uint16 currsize = *buffsize;
	tlv_uint16 length = 0;

	printf("Type\tLength\tValue\n");

	while(offset < currsize) {
		length = (buff[offset + 1] << 8) + buff[offset + 2];
		
		printf("%02x\t", buff[offset ++]);
		printf("%02x", buff[offset ++]);
		printf("%02x\t", buff[offset ++]);

		for(i = 0;i < length;i ++)
			printf("%02x", buff[offset ++]);

		printf("\n");
	}

	return d_tlv_ok;
}


