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

void show(const char *title, unsigned char *data, int len)
{
	printf("%s\n", title);
	for (int i = 0; i < len; i++)
		printf(" %02x", (unsigned int)data[i]);
	printf("\n");
}

int main()
{
	for (int i = 0; i < AES_BLOCK_SIZE; ++i) 
		key[i] = 32 + i;
	for (int i = 0; i < AES_BLOCK_SIZE; ++i) 
		iv[i] = 0;
	
	char plaintext[AES_BLOCK_SIZE];
	unsigned char ciphertext[AES_BLOCK_SIZE];
	memset(plaintext, 0, AES_BLOCK_SIZE);
	memset(ciphertext, 0, AES_BLOCK_SIZE);
	strcpy(plaintext, "abcdefg");
	show("==plaintext==", plaintext);
	if (!aes_encrypt((unsigned char *)plaintext, AES_BLOCK_SIZE, ciphertext))
		printf("encrypt error\n");
	show("==ciphertext==", ciphertext);
	if (!aes_decrypt(ciphertext, AES_BLOCK_SIZE, (unsigned char *)plaintext))
		printf("decrypt error\n");
	show("==plaintext==", plaintext);
}
