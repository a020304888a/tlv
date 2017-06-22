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
	token.length = 0x01;
	/* append */
	TLV.append(mytlv, &token);



	return 0;
}
