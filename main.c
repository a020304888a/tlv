#include <stdio.h>
#include "tlv.h"

int main()
{
	tlv_uint8 ret;
	int i;
	tlv_uint16 size;
	tlvs tlv[10];
	tlv_uint8 buff[1024] = {0};
	tlv_uint8 data[2];
	data[0] = 0xda;
	data[1] = 0x12;

	tlv_uint8 tmpdata[2];
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
		printf("%02x", (tlv_uint8)(fetch.length >> 8));
		printf("%02x\t", (tlv_uint8)fetch.length);
		printf("%02x", (tlv_uint8)fetch.value[0]);
		printf("%02x", (tlv_uint8)fetch.value[1]);
		printf("\n");
	}

	return 0;
}
