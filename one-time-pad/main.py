from encrypt import encrypt
from decrypt import decrypt
from random_key import generate_key

plaintext = input("Enter plaintext: ")
key = generate_key(len(plaintext))
ciphertext = encrypt(plaintext, key)
print("Ciphertext:", ciphertext)
random = decrypt(key, ciphertext)
print("Plaintext:", random)


