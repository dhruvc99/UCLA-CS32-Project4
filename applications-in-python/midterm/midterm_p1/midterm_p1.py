'''
Dhruv Chakraborty
UID: 204962098
Solution for Midterm Problem 1
'''

import re

# webpages of all articles to find DOIs of
namelist = ['boyer', 'budoff', 'green', 'heber', 'horvath', 'osher', 'pearl', 'sayed', 'shapley', 'tao', 'wright']

for name in namelist:
	filename = name + '.html'
	with open('/users/dhruv/desktop/pic16/midterm/midterm_p1_files/data/' + filename, 'r') as reader:
		text = reader.read()
	print re.findall(r'10[.]\d{4,}(?:[.]\d+)*/[a-zA-Z0-9-_()]+(?:[.][a-zA-Z0-9-_()]+)*', text)[0] # regex to capture all dois