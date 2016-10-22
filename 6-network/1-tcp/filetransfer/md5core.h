
#ifndef __MD5CORE_H__
#define __MD5CORE_H__

#include <sys/types.h>

typedef u_int32_t uint32;

struct MD5Context {
	uint32 buf[4];
	uint32 bits[2];
	unsigned char in[64];
	int doByteReverse;
};

void MD5_Init(struct MD5Context *);
void MD5_Update(struct MD5Context *, unsigned const char *, unsigned);
void MD5_Final(unsigned char digest[16], struct MD5Context *);

/*
 * This is needed to make RSAREF happy on some MS-DOS compilers.
 */

typedef struct MD5Context MD5_CTX;

#endif				/* __MD5CORE_H__ */
