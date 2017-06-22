#include <stdio.h>
#include "tlv_oo.h"

int main()
{
	uint8_t ret;

	/* array of tlv */
	uint8_t tlv_array[2048];
	uint32_t length = 2048;

	/* token of tlv */
	uint8_t value[256];
	TLV_TOKEN token = {
		.type = 0,
		.length = 256,
		.value = value,
	};

	/* Create my tlv */
	tlv_p mytlv = TLV.create();

	token.value[0] = 0x0f;
	token.value[1] = 0x01;
	token.length = 0x02;
	/* append */
	TLV.append(mytlv, &token);
	token.type = 1;
	TLV.append(mytlv, &token);
	token.type = 2;
	TLV.append(mytlv, &token);
	token.type = 3;
	token.value[1] = 0xdd;
	token.length = 0x03;
	TLV.append(mytlv, &token);

	length = TLV.get_array(mytlv, 2048, tlv_array);
	printf("tlv_array = ");
	for(int i = 0;i < length;i ++)
		printf("%02x", tlv_array[i]);

	printf("\n");

	ret = TLV.delete(mytlv, 2);
	printf("ret = %02x\n", ret);
	length = TLV.get_array(mytlv, 2048, tlv_array);
	printf("tlv_array = ");
	for(int i = 0;i < length;i ++)
		printf("%02x", tlv_array[i]);

	printf("\n");

	TLV.finish(mytlv);

	return 0;
}
