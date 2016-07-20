import pyDes

data = b"Please encrypt my data"
k = pyDes.des(b"DESCRYPT", pyDes.CBC, b"\0\0\0\0\0\0\0\0", pad=None, padmode=pyDes.PAD_PKCS5)
d = k.encrypt(data)
print("Encrypted: %r" % d)
print("Decrypted: %r" % k.decrypt(d))
assert(k.decrypt(d) == data)
