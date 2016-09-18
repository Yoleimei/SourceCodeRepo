#include <stdio.h>
#include <string.h>

#include <openssl/sha.h>

void SHA1_OneStep(const unsigned char *d, size_t n, unsigned char *md)
{
	SHA1(d, n, md);
}

void SHA1_ThreeStep(const unsigned char *d, size_t n, unsigned char *md)
{
	SHA_CTX shactx;
	SHA1_Init(&shactx);
	SHA1_Update(&shactx, d, n);
	SHA1_Final(md, &shactx);
}

void show(const unsigned char *d)
{
	for (int i = 0; i < SHA_DIGEST_LENGTH; i++)
		printf("%02x", d[i]);
	printf("\n");
}

int main()
{
	char data[] = "abcdefghijklmnopqrst";
	unsigned char md1[SHA_DIGEST_LENGTH];
	unsigned char md2[SHA_DIGEST_LENGTH];
	unsigned char res[SHA_DIGEST_LENGTH + 1];
	memset(res, 0, SHA_DIGEST_LENGTH + 1);
	
	SHA1_OneStep((unsigned char *)data, strlen(data), md1);
	SHA1_ThreeStep((unsigned char *)data, strlen(data), md2);
	
	printf("SHA_DIGEST_LENGTH = %d\n", SHA_DIGEST_LENGTH);
	show(md1);
	show(md2);
}
