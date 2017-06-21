#include <stdio.h>
#include "tlv.h"

int main()
{
	uint8_t ret;
	int i;
	uint16_t size;
	tlvs tlv[10];
	uint8_t buff[1024] = {0};
	uint8_t data[2];
	data[0] = 0xda;
	data[1] = 0x12;

	uint8_t tmpdata[2];
	tlvs fetch;
	fetch.value = tmpdata;

	for(i = 0;i < 10;i ++){
		tlv[i].type = i;
		tlv[i].length = 2;
		tlv[i].value = data;
		data[0]++;
		data[1]++;
		size = i*5;
		tlv_array_append(buff, 1024, &size, &tlv[i]);
	}
	tlv_array_delete(buff, &size, 3);
	tlv_array_show_all(buff, &size);
	ret = tlv_array_fetch(buff, &size, 8, &fetch);

	if(ret) {
		printf("fetch fail!\n");
	} else {
		printf("\n======= main =======\n");
		printf("%02x\t", fetch.type);
		printf("%02x", (uint8_t)(fetch.length >> 8));
		printf("%02x\t", (uint8_t)fetch.length);
		printf("%02x", (uint8_t)fetch.value[0]);
		printf("%02x", (uint8_t)fetch.value[1]);
		printf("\n");
	}

	return 0;
}
