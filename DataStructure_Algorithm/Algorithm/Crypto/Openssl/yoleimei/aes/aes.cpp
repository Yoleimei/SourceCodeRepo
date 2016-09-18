#include <stdio.h>
#include <string.h>

#include <openssl/aes.h>

typedef unsigned char BYTE;
typedef unsigned int  UINT;

static unsigned char key[AES_BLOCK_SIZE];
static unsigned char iv[AES_BLOCK_SIZE];

bool aes_encrypt(const BYTE *inbuf, UINT len, BYTE *outbuf)
{
	AES_KEY aes;
	if (AES_set_encrypt_key(key, 128, &aes) < 0)
		return false;
	AES_cbc_encrypt(inbuf, outbuf, len, &aes, iv, AES_ENCRYPT);
	
	return true;
}

bool aes_decrypt(const BYTE *inbuf, UINT len, BYTE *outbuf)
{
	AES_KEY aes;
	if (AES_set_decrypt_key(key, 128, &aes) < 0)
		return false;
	AES_cbc_encrypt(inbuf, outbuf, len, &aes, iv, AES_DECRYPT);
	
	return true;
}

int main()
{
	for (int i = 0; i < AES_BLOCK_SIZE; ++i) 
		key[i] = 32 + i;
	for (int i = 0; i < AES_BLOCK_SIZE; ++i) 
		iv[i] = 0;
	
	char plaintext[256];
	unsigned char ciphertext[256];
	memset(plaintext, 0, 256);
	memset(ciphertext, 0, 256);
	strcpy(plaintext, "Hello world");
	if (!aes_encrypt((unsigned char *)plaintext, 256, ciphertext))
		printf("encrypt error\n");
	if (!aes_decrypt(ciphertext, 256, (unsigned char *)plaintext))
		printf("decrypt error\n");
	printf("%s\n", plaintext);
}
