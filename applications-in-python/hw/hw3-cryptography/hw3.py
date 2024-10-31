'''
Name: Dhruv Chakraborty
UID: 204-962-098
Prof. Ryu
PIC 16: HW 3
'''

# Problem 1:

from hashlib import sha256

with open('hw3_unsalted_db.txt', 'r') as reader:
	unsalted_list = reader.read().splitlines() # read in each line of database into list

unsalted_db = dict() 

for entry in unsalted_list:
	record = entry.split(', ')
	unsalted_db[record[0]] = record[1] # create an actual database using a dictionary

word_list = open("words.txt").read().splitlines()

hash_to_word = {sha256(word.lower()).hexdigest(): word.lower() for word in word_list} # create a dictionary from hashes back to words

# check if any hashes in our dictionary match. if so, return those users with the word that the given hash maps to
hacked_user_logins = [(user,hash_to_word[hash]) for user,hash in unsalted_db.iteritems() if hash in hash_to_word]
print hacked_user_logins


#======================================================#

# Problem 2:

'''
Time to run: 
Essentially, this program takes the amount of time taken to run by problem 1, multiplied by the number of records in the database.
In our case, (using the time module and noting there's 10,000 records) this is 1.16023111343*10000 = 11602.3111343 seconds.
I also ran this program with 50 random records from the salted file, and the time in this case is actually lower at 48.4903099537*200 = 9698.06199074 seconds.
'''

from hashlib import sha256

with open('hw3_salted_db.txt', 'r') as reader:
	salted_list = reader.read().splitlines()

salted_db = dict()

for entry in salted_list:
	record = entry.split(', ')
	salted_db[record[0]] = record[1] # create database of users with their salted passwords

word_list = open("words.txt").read().splitlines()

hash_to_word = dict() # create a unique hash to word dictionary for each user
for user in salted_db.iterkeys():
	hash_to_word[user] = {sha256(user + word).hexdigest(): word for word in word_list} # adds the username in front of each word to create personal hash to word dict

# check if any hashes in the user's personal hash to word dictionary match. if so, return those users with the word that the given hash maps to
hacked_users = [(user, hash_to_word[user][hash]) for user, hash in salted_db.iteritems() if hash in hash_to_word[user]]
print hacked_users


#======================================================#

# Problem 3:

'''
The first thing to note is that even minor corruptions of the the original text return completely different md5 hashes. For example if I change the beginning 'there are'
of the original provided text to 'there bre', the hash changes from bb1ae33a0a9d01394c152ad4d3c6c40d to 7f5f50668ffeac1acf4665f9cf9f606a. Note that there are no 
similarities between these hashes. Also, changing 'Internet' to 'internet' changes the hash from bb1ae33a0a9d01394c152ad4d3c6c40d to 6bf2a97b701e946110626a07fea77d54.
We also note that the corruptions we make the original file are necessarily different from the original. This means that there is no way to get the original file back
through random corruption.

Now consider that md5 is a 128 bit hash function. This means that theoretically, it has a 2^128 security level against collisons -- since there are 2^128 possible hashes.
Therefore, an estimate is that the program will iterate through the loop 2^128 times. Using the time module, we measure that running the program once takes 
0.000171899795532 seconds. Thus, I estimate that the program will take 2^128 * 0.000171899795532 seconds = 1.8548474536039549 × 10^27 years. For comparison, the universe 
is supposed to have existed for 13.8 * 10^9 years. 
'''

#======================================================#

# Problem 4:

'''
Is it possible to detect this attack?
There are a few things to consider here. First of all, there are precautions we could take to avoid these attacks, like associating each entry with it's own unique 
identifier. An example of this is what we've done using the counter in the following program. Without any such precautions to protect against such an attack, one
way I see to avoid such an attack would be by comparing the timestamp inside the entry to the actual time the entries were added. Another other way I see is to prompt 
further investigation when multiple entries with the exact same contents are made. Also, we could hash the entire previous entry (including the hash) to ensure that each
message has a UNIQUE previous message.
'''

# NOTE: I was unable to debug the verify_entry() function in time, which although seems logically coherent, does not work as wanted

from Crypto.PublicKey import RSA
from hashlib import sha256

with open('hw3_ledger.txt', 'r') as reader:
	ledger = reader.read().splitlines() # ledger is a list of each entry

counter = 0
verification_keys = {}

with open('hw3_signed_ledger.txt', 'w') as writer:
	for i, record in enumerate(ledger): 
		key_pair = RSA.generate(1024)
		sign_key = key_pair.publickey() # use this key to encrypt
		verification_keys[str(counter)] = key_pair # use this key to decrypt

		# create entry encoding the encryted hash, and writing that to the file
		if counter == 0:
			# if the counter is 0, use 'Starting dummy entry' as prev_message for the first entry
			cipherhash = sign_key.encrypt(sha256(str(counter)).hexdigest() + sha256('Starting dummy entry').hexdigest() + sha256(record).hexdigest(), None)
			entry = (record, str(counter), cipherhash[0].encode('hex'))
		else:
			cipherhash = sign_key.encrypt(sha256(str(counter)).hexdigest() + sha256(ledger[i-1]).hexdigest() + sha256(record).hexdigest(), None)
			entry = (record, str(counter), cipherhash[0].encode('hex'))

		writer.write('\n'.join(entry) + '\n') # each entry is split across 3 lines. the first has the message, the second the counter and the third the cipherhash

		counter = counter + 1 # incerement counter


def verify_entry(entry, prev_message, verification_keys):
	message = entry[0]
	counter = entry[1]
	cipherhash = entry[2].decode('hex') # decoding to get the cipherhash
	veri_key = verification_keys[counter] # get veri_key associated with this entry

	# check if decrypted cipherhash is the same as the hash
	return veri_key.decrypt(cipherhash) == (sha256(counter).hexdigest() + sha256(prev_message).hexdigest() + sha256(message).hexdigest()) 


with open('hw3_signed_ledger.txt', 'r') as reader:
	records = reader.read().splitlines() 

	for i, record in enumerate(records):
		if i%3 == 0:
			entry = (record, records[i+1], records[i+2]) # at each 3rd index, get the full entry tuple

			prev_message = 'Starting dummy entry' # set prev_message to 'Starting dummy entry', changing it immediately after if this isn't the first entry
			if i != 0:
				prev_message = records[i-3]

			print verify_entry(entry, prev_message, verification_keys) # verify each entry

