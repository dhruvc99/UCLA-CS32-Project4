'''
Name: Dhruv Chakraborty
UID: 204-962-098
Solutions for Final

NOTE: Due to time constraints of the final, problem 1 and problem 2 are incomplete.
'''

# final problem 3:

import sympy as sp
sp.init_printing(use_unicode = True, use_latex="mathjax")
from IPython.display import display

[x0,x1,x2,x3,x4,x5,x6,x7,x8] = sp.symbols('x0 x1 x2 x3 x4 x5 x6 x7 x8') # there are 9 compounds

            # x0,x1,x2,x3,x4,x5,x6,x7,x8,zero augemented column
M=sp.Matrix([[4,1,0,-1,0,0,0,0,0,0], # K
             [1,0,0,0,-2,0,0,0,0,0], # Fe
             [6,0,0,0,0,0,0,-1,0,0], # C
             [6,0,0,0,0,0,-1,0,0,0], # N
             [0,1,0,0,0,-1,0,0,0,0], # Mn
             [0,4,4,-4,-12,-4,-3,-2,-1,0], #O
             [0,0,2,-1,0,0,-1,0,-2,0], #H
             [0,0,1,0,-3,-1,0,0,0,0]]) # S

sols = sp.solve_linear_system(M,x0,x1,x2,x3,x4,x5,x6,x7,x8) # solve equation
display(M)
display(sols) # solutions in terms of x8

# get coefficients when x8 = 1
coeffs = sp.Matrix([sp.Rational(-1,46),
                   sp.Rational(85,46),
                   sp.Rational(167,92),
                   sp.Rational(81,46),
                   sp.Rational(-1,92),
                   sp.Rational(85,46),
                   sp.Rational(-3,23),
                   sp.Rational(-3,23),
                   1])

# ideally would automate below and above by using subs and indexing to get denominators from rationals

f = sp.lcm([46,46,92,46,92,46,23,23,1]) # find lcm of denominators
coeffs_final = coeffs*f
display(coeffs_final) # get the final coefficients

print "-2 K4Fe(CN)6 + 170 KMnO4 + 167 H2SO4 = 162 KHSO4 - 1 Fe2(SO4)3 + 170 MnSO4 - 12 HNO3 = 12 CO2 + 92 H2O"



# final problem 2:

import matplotlib.pyplot as plt
import numpy as np
from scipy.optimize import minimize

val_land = 100
val_river = 100

# fix the river bank at y = 0 (so a is 0) and let (a,b), (c,d) and (a,e) be the where the stakes are planted
# Dido(x) takes input array and spits out b,c,d,e
def Dido(x):
    b = x[0]
    c = x[1]
    d = x[2]
    e = x[3]
    return (b,c,d,e)

# want to reduce objFunc
def objFunc(x):
    (b,c,d,e) = Dido(x)
    
    river_length = e-b 
    River_val = val_river*river_length # get value associated with river
    
    area = 0.5*river_length*d # calculate area, treating river_length as base and (c,d) as height
    Land_val = val_land*area # get value associated with land
    
    rope_length = np.sqrt(c**2+(d-e)**2) + np.sqrt(c**2+(d-b)**2) # calculate expected rope length
    rope_dev = 1 - rope_length # to ensure rope length is very close to 1
    
    # weigh inputs differently
    # we do val_river - River_val bc river_length < 1 and similarly for val_land - Land_val
    return (val_river - River_val) + 2*(val_land - Land_val) + 10*rope_dev

x = np.array([0, 1/2.82, 1/2.82, 1/1.41]) # intialize our values 

# optimize
sol = minimize(objFunc, x, method = 'BFGS', options = {'disp': True})
print sol
    
# plot results

a = 0
(b,c,d,e) = Dido(x)

plt.plot([0,c,0],[b,d,e]) # where y = 0 is the right bank of the river
plt.title("The river is at y = 0")
plt.show()
    
# I'm not sure if this answer is correct. If I had more time, I would've tried to calculate area
# and the other key factors using theta and fixing the length of the rope. I believe the rope_dev 
# parameter causes the optimization to fail. I think the answer is what my input array suggests.





# final problem 4:

import csv
import numpy as np
from sklearn import neighbors

# setup np arrays
names = np.array([])
parties = np.array([])
votes = np.zeros((0,1207))

with open('/Users/dhruv/Desktop/pic16/house_votes.csv') as csv_file:
	reader = csv.DictReader(csv_file)
	for row in reader:
		# get all representative's names, their parties and their voting records
		names = np.append(names, row['first_name'] + ' ' + row['last_name']) 
		parties = np.append(parties, row['party'])
		vote_record = [row[str(vote)] for vote in range(1, 1208)]
		votes = np.append(votes, [vote_record], axis = 0)
        
# 56th entry is Ted Lieu: get his votes
print names[56] 
ted_votes = votes[56,:]

# get the names and votes of all representatives that aren't Ted Lieu
mask = np.ones(len(names), dtype = bool)
mask[56] = False # don't want Ted Lieu
o_names = names[mask]
o_votes = votes[mask,:]

# the following bit of code gets all the votes that ted abstained from
# then it gets what everyone else did for that vote
# then it gets rid of everyone that abstained from the vote using voted_mask
# then it gets their votes for all votes except vote i using y_mask
# then train knn = 10 for other votes to yield given vote
# then predict what ted would've done according to other votes
for i, vote in enumerate(ted_votes):
    if vote == '0.5':
        print 'Ted Lieu abstained from vote ' + str(i)    
        
        other_votes = o_votes[:,i]      
        voted_mask = np.ones(len(o_names), dtype = bool)
        for j, other_vote in enumerate(other_votes):
            if other_vote == '0.5':
                voted_mask[j] = False
                
        this_vote = other_votes[voted_mask]
        
        x_votes = o_votes[voted_mask,:]
        
        y_mask = np.ones(1207, dtype = bool)
        y_mask[i] = False
        y_votes = x_votes[:,y_mask]
        print y_votes.shape
        
        # setup k-nearest neighbors classifier with k = 10
        nbrs = neighbors.KNeighborsClassifier(10)
        
        nbrs.fit(y_votes, this_vote)
        ted = nbrs.predict([ted_votes[y_mask]])
        print "Ted Lieu would've voted: " + str(ted[0])
        




# final problem 1:

import matplotlib.pyplot as plt
import matplotlib.image as mpimg
import numpy as np

n = 64
r = n/32

im = [[[255,209,0]]*n]*n
board = np.array(im, dtype = float)

for i in range(4):
    mask = (((2*i+1)*8) < x < ((2*i+2)*8)) & (((2*i+1)*8) < y < ((2*i+2)*8))

board[mask] = [39,116,174]

plt.imshow(board)
# plt.axis('off')
plt.show()
