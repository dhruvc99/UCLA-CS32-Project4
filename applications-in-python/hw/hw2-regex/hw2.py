'''
Name: Dhruv Chakraborty
UID: 204-962-098
Prof. Ryu
PIC 16: HW 2
'''

import re

'''
Problem 1: 
'''
print "=========="
print "Problem 1:"


f = open("hw2_names.txt")
names = f.read()
f.close()

lastnames = re.findall(r'[-.a-zA-Z.\[\]]+ (?:[a-zA-Z.\[\]]+ )*([\'a-zA-Z.\[\]]+)[\r\r\n\n]', names) # use [\r\r\n\n] for all possible newline chars
print "Number of distinct last names: ", len(set(lastnames)) # part 1

def getMostCommon(lst):
	count = 0
	mostCommon = lst[0]

	for lastname in lst:
		freq = lst.count(lastname)
		if (freq > count):
			count = freq
			mostCommon = lastname

	return mostCommon

print "Most common lastname is :", getMostCommon(lastnames) # part 2

middlenames = re.findall(r'[-.a-zA-Z.\[\]]+ (?:[a-zA-Z.\[\]]+ )+[a-zA-Z.\[\]]+\s+', names) # outputs list with all names that have middle names
print "Number of names with one or more middle names: ", len(middlenames) # part 3

'''
Problem 2: 
'''
print "=========="
print "Problem 2:"

f = open("hw2_email_short.txt") # using short version of corpus for testing
corpus = f.read()
f.close()


emails = re.findall(r'[\w\.-]+@[\w\.-]+\.\w+', corpus)
print emails # part 1

phonenums = re.findall(r'(?:\d{3}-|\(\d{3}\) |d{3}/)\d{3}-\d{4}\w?', corpus)
print phonenums # part 2

websites = re.findall(r'http[s]?://(?:[a-zA-Z]|[0-9]|[$-_@.&+]|[!*\(\),]|(?:%[0-9a-fA-F][0-9a-fA-F]))+|www\.(?:[a-zA-Z]|[0-9]|[$-_@.&+]|[!*\(\),]|(?:%[0-9a-fA-F][0-9a-fA-F]))+', corpus) # to get urls that start with www and with http
print websites # part 3

'''
Problem 3: 
'''
print "=========="
print "Problem 3:"

f = open("hw2_ucla-catalog2018-19.txt")
catalog = f.read()
f.close()

catalog_phone_nums = re.findall(r'\d{3}-(?:\s.*)?\d{3}-(?:\s.*)?\d{4}', catalog)
print catalog_phone_nums
























