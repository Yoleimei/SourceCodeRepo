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
		key[i] = 96 + i;
	for (int i = 0; i < AES_BLOCK_SIZE; ++i) 
		iv[i] = i;
	
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

	unsigned char plaintext2[] = {
		'A', 'B', 'C', 'D', 'E', 'F', 'G', 'h',
		'i', 'j', 'k', 'l', 'm', 'n', 'O', 'P', 'Q'
	};
	unsigned char ciphertext2[AES_BLOCK_SIZE*2];
	unsigned char checktext2[AES_BLOCK_SIZE*2];
	memset(ciphertext2, 0, AES_BLOCK_SIZE*2);
	memset(checktext2, 0, AES_BLOCK_SIZE*2);
	show("==plaintext2==", plaintext2, sizeof(plaintext2));
	if (!aes_encrypt((unsigned char *)plaintext2, AES_BLOCK_SIZE*2, ciphertext2))
		printf("encrypt error\n");
	show("==ciphertext2==", ciphertext2, AES_BLOCK_SIZE*2);
	if (!aes_decrypt(ciphertext2, AES_BLOCK_SIZE*2, (unsigned char *)checktext2))
		printf("decrypt error\n");
	show("==checktext2==", checktext2, AES_BLOCK_SIZE*2);

	unsigned char plaintext3[] = {
		'A', '0', 'B', '1', 'C', '2', 'D', '3',
		'E', '4', 'F', '5', 'G', '6', 'H', '7', 'I', '8', 'J', '9'
	};
	unsigned char ciphertext3[AES_BLOCK_SIZE*2];
	unsigned char checktext3[AES_BLOCK_SIZE*2];
	memset(ciphertext3, 0, AES_BLOCK_SIZE*2);
	memset(checktext3, 0, AES_BLOCK_SIZE*2);
	show("==plaintext3==", plaintext3, sizeof(plaintext3));
	if (!aes_encrypt((unsigned char *)plaintext3, AES_BLOCK_SIZE*2, ciphertext3))
		printf("encrypt error\n");
	show("==ciphertext3==", ciphertext3, AES_BLOCK_SIZE*2);
	if (!aes_decrypt(ciphertext3, AES_BLOCK_SIZE*2, (unsigned char *)checktext3))
		printf("decrypt error\n");
	show("==checktext3==", checktext3, AES_BLOCK_SIZE*2);

	char str4[] = "skdbhakjfgbajkshfslah";
	unsigned char plaintext4[strlen(str4)];
	memcpy(plaintext4, str4, strlen(str4));
	unsigned char ciphertext4[AES_BLOCK_SIZE*2];
	unsigned char checktext4[AES_BLOCK_SIZE*2];
	memset(ciphertext4, 0, AES_BLOCK_SIZE*2);
	memset(checktext4, 0, AES_BLOCK_SIZE*2);
	show("==plaintext4==", plaintext4, sizeof(plaintext4));
	if (!aes_encrypt((unsigned char *)plaintext4, AES_BLOCK_SIZE*2, ciphertext4))
		printf("encrypt error\n");
	show("==ciphertext4==", ciphertext4, AES_BLOCK_SIZE*2);
	if (!aes_decrypt(ciphertext4, AES_BLOCK_SIZE*2, (unsigned char *)checktext4))
		printf("decrypt error\n");
	show("==checktext4==", checktext4, AES_BLOCK_SIZE*2);
}
