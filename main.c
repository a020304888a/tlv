#include <stdio.h>
#include "tlv.h"

int main()
{
	int i;
	uint_16 size;
	tlvs tlv[10] = {0};
	uint_8 buff[1024] = {0};
	uint_8 data[2];
	data[0] = 0xda;
	data[1] = 0x12;

	tlvs fetch;

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
	tlv_array_fetch(buff, &size, 8, &fetch);

	printf("\n======= main =======\n");
	printf("%02x\t", fetch.type);
	printf("%02x", (uint_8)(fetch.length >> 8));
	printf("%02x\t", (uint_8)fetch.length);
	printf("%02x", (uint_8)fetch.value[0]);
	printf("%02x", (uint_8)fetch.value[1]);
	printf("\n");

	return 0;
}
