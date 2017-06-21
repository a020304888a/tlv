#include <stdio.h>
#include <string.h>
#include "tlv_typedef.h"
#include "tlv.h"

#define d_sizeof_uint8_uint16 	(3)

uint8_t tlv_array_append(uint8_t *buff, uint16_t maxsize, uint16_t *buffsize, const tlvs *tlv)
{
	uint16_t offset = 0;
	uint16_t currsize = *buffsize;

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
	buff[currsize ++] = (uint8_t)(tlv->length >> 8);
	buff[currsize ++] = (uint8_t)tlv->length;
	memcpy(&buff[currsize], tlv->value, tlv->length);
	currsize += tlv->length;
	*buffsize = currsize;

	return d_tlv_ok;
}


/* this function do not allocate memory for tlv value, please assign in advance */
uint8_t tlv_array_fetch(uint8_t *buff, const uint16_t *buffsize, uint8_t type, tlvs *tlv)
{
	uint16_t offset = 0;

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

uint8_t tlv_array_delete(uint8_t *buff, uint16_t *buffsize, uint8_t type)
{
	uint16_t offset = 0;
	uint16_t currsize = *buffsize;
	uint16_t blocksize = 0;

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

uint8_t tlv_array_show_all(uint8_t *buff, const uint16_t *buffsize)
{
	int i = 0;
	uint16_t offset = 0;
	uint16_t currsize = *buffsize;
	uint16_t length = 0;

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


