'''
Name: Dhruv Chakraborty
UID: 204-962-098
Prof. Ryu
PIC 16: HW 1
'''

'''
Problem 1: 
Write a function duplicates(lst) that returns a list of all elements
appearing twice or more in the input list lst.
Solution:
'''
def duplicates(lst):
	duplicate_elts = [] 
	for i in range(len(lst)): # for each item in lst, check if it has duplicate following it
		for j in range(i + 1, len(lst)): 
			if lst[i] == lst[j] and lst[i] not in duplicate_elts: # ensure that this item isn't already in our output list
				duplicate_elts.append(lst[i])
	return duplicate_elts



'''
Problem 2: 
Write a function primeUpTo(n) that returns a list of all the prime numbers
strictly less than the input number n.
Solution:
'''
def primeUpTo(n):
	primes = []
	# we do not consider 1 to be a prime number
	for i in range(2, n): 
		for j in range(2, int(i**0.5) + 1): # only check till squareroot of number + 1 to prevent repetition
			if i%j == 0:
				break; # if any such number divides i, it is not prime
		else:
			primes.append(i)
	return primes



'''
Problem 3: 
Write a function longestpath(dict) that finds the length of the longest path,
(a:b) -> (b:c) -> ... in a dictionary dict. It counts each pointer from a key
to a value as one step. For example, the path (a:b) -> (b:c) has length 2. To
avoid cycles, we do not allow any key to appear more than once in a path (as
a key). Assume None does not appear as a key or a value.
Solution:
'''
def longestpath(dct):
	longestPath = 0
	for i in dct.keys():
		keysSeen = set() # use a set to keep track of keys we've already encountered
		pathLength = -1 
		while i != None:
			if i in keysSeen:
				break
			keysSeen.add(i)
			pathLength += 1
			i = dct.get(i) # if key is not present, get() returns None, causing the loop to end
		if pathLength > longestPath:
			longestPath = pathLength
	return longestPath



'''
Problem 4:
Consider the game Hangman. Write a function hangman(candidate) that takes in
an incomplete word like p_ck and returns a list of all possible matches like
pack, peck, pick or puck. The matches should be words in the dictionary and
are case insensitive. The input candidate can have 0,1,2 or more underscores.
Solution:
'''
def match(candidate, word):
	if len(candidate) != len(word): # clearly not a match if lengths not equal
		return False
	for i in range(len(candidate)):
		if (candidate[i] != '_' and word[i] != candidate[i]): # unless char at ith index is '_', ensure they match
			return False
	return True

def hangman(candidate):
	f = open("words.txt")
	word_list = f.read().splitlines()
	return [word.lower() for word in word_list if match(candidate, word.lower()) == True] # check with lowercase versions of all words in words.txt


