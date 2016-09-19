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
	unsigned char tmp_iv[AES_BLOCK_SIZE];
	memcpy(tmp_iv, iv, AES_BLOCK_SIZE);
	if (AES_set_encrypt_key(key, 128, &aes) < 0)
		return false;
	AES_cbc_encrypt(inbuf, outbuf, len, &aes, tmp_iv, AES_ENCRYPT);
	
	return true;
}

bool aes_decrypt(const BYTE *inbuf, UINT len, BYTE *outbuf)
{
	AES_KEY aes;
	unsigned char tmp_iv[AES_BLOCK_SIZE];
	memcpy(tmp_iv, iv, AES_BLOCK_SIZE);
	if (AES_set_decrypt_key(key, 128, &aes) < 0)
		return false;
	AES_cbc_encrypt(inbuf, outbuf, len, &aes, tmp_iv, AES_DECRYPT);
	
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
	
	//printf("STRICT_ALIGNMENT = %d\n", STRICT_ALIGNMENT);

	unsigned char plaintext[AES_BLOCK_SIZE*2] = {
		'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h',
		'i', 'j', 'k', 'l', 'm', 'n', 'o', 'p'
	};
	unsigned char ciphertext[AES_BLOCK_SIZE*2];
	memset(plaintext+16, 16, 16);
	memset(ciphertext, 0, AES_BLOCK_SIZE*2);
	show("==plaintext==", plaintext, AES_BLOCK_SIZE*2);
	if (!aes_encrypt((unsigned char *)plaintext, AES_BLOCK_SIZE*2, ciphertext))
		printf("encrypt error\n");
	show("==ciphertext==", ciphertext, AES_BLOCK_SIZE*2);
	if (!aes_decrypt(ciphertext, AES_BLOCK_SIZE*2, (unsigned char *)plaintext))
		printf("decrypt error\n");
	show("==plaintext==", plaintext, AES_BLOCK_SIZE*2);


	unsigned char plaintext1[AES_BLOCK_SIZE*2] = {
		'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h',
		'i', 'j', 'k', 'l', 'm', 'n', 'o', 'p', 'q'
	};
	unsigned char ciphertext1[AES_BLOCK_SIZE*2];
	unsigned char checktext1[AES_BLOCK_SIZE*2];
	memset(plaintext1+17, 15, 15);
	memset(ciphertext1, 0, AES_BLOCK_SIZE*2);
	memset(checktext1, 0, AES_BLOCK_SIZE*2);
	show("==plaintext1==", plaintext1, AES_BLOCK_SIZE*2);
	if (!aes_encrypt((unsigned char *)plaintext1, AES_BLOCK_SIZE*2, ciphertext1))
		printf("encrypt error\n");
	show("==ciphertext1==", ciphertext1, AES_BLOCK_SIZE*2);
	if (!aes_decrypt(ciphertext1, AES_BLOCK_SIZE*2, (unsigned char *)checktext1))
		printf("decrypt error\n");
	show("==checktext1==", checktext1, AES_BLOCK_SIZE*2);


	unsigned char plaintext2[AES_BLOCK_SIZE+1] = {
		'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h',
		'i', 'j', 'k', 'l', 'm', 'n', 'o', 'p', 'q'
	};
	unsigned char ciphertext2[AES_BLOCK_SIZE*2];
	unsigned char checktext2[AES_BLOCK_SIZE*2];
	memset(ciphertext2, 0, AES_BLOCK_SIZE*2);
	memset(checktext2, 0, AES_BLOCK_SIZE*2);
	show("==plaintext2==", plaintext2, AES_BLOCK_SIZE+1);
	if (!aes_encrypt((unsigned char *)plaintext2, AES_BLOCK_SIZE*2, ciphertext2))
		printf("encrypt error\n");
	show("==ciphertext1==", ciphertext2, AES_BLOCK_SIZE*2);
	if (!aes_decrypt(ciphertext2, AES_BLOCK_SIZE*2, (unsigned char *)checktext2))
		printf("decrypt error\n");
	show("==checktext2==", checktext2, AES_BLOCK_SIZE*2);
}
