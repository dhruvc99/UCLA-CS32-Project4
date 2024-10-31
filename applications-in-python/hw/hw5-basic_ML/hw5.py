'''
Name: Dhruv Chakraborty
UID: 204-962-098
PIC 16
Prof. Ryu

HW #5
'''

import csv
import numpy as np
from sklearn import neighbors
from sklearn.cluster import KMeans
from sklearn import svm

# setup np arrays
names = np.array([])
parties = np.array([])
votes = np.zeros((0,599))

with open('senate_votes.csv') as csv_file:
	reader = csv.DictReader(csv_file)
	for row in reader:
		# get all senators's names, their parties and their voting records
		names = np.append(names, row['first_name'] + ' ' + row['last_name']) 
		parties = np.append(parties, row['party'])
		vote_record = [row[str(vote)] for vote in range(1, 600)]
		votes = np.append(votes, [vote_record], axis = 0)


# use mask to only get non-independent senators's names, parties and voting records
mask = np.ones(len(names), dtype = bool)
mask[39] = False # remove King
mask[94] = False # remove Sanders
c_names = names[mask]
c_parties = parties[mask]
c_votes = votes[mask,:]

# Problem 1:

i_votes = votes[~mask,:] # get Sanders's and King's voting records

nbrs = neighbors.KNeighborsClassifier(5) # using 5 nearest neighbors
nbrs.fit(c_votes, c_parties) # fit non-independent senators's votes to their parties
i_predict = nbrs.predict(i_votes) # predict Sanders's and King's party based on votes
print "According to KNN, Senator King votes more like " + i_predict[0] + "."
print "According to KNN, Senator Sanders votes more like " + i_predict[1] + "."

# get and print the 5 senators that vote most like King
closest_king = nbrs.kneighbors([i_votes[0,:]])
king_five = {c_names[closest_king[1][0][i]]: closest_king[0][0][i] for i in range(5)}
print "Senators that vote most like King are:"
for name in king_five.iterkeys():
	print name

# get and print the 5 senators that vote most like Sanders
closest_sanders = nbrs.kneighbors([i_votes[1,:]])
sanders_five = {c_names[closest_sanders[1][0][i]]: closest_sanders[0][0][i] for i in range(5)}
print "Senators that vote most like Sanders are:"
for name in sanders_five.iterkeys():
	print name



print ""
# Problem 2:

kmeans = KMeans(2) 
kmeans.fit(votes) # cluster data into 2 sets
labels = kmeans.labels_
Rcluster = labels[35] # set Mitch Mcconnell's cluster to be Republican
print "Cluster " + str(Rcluster) + " represents Republicans."
Dcluster = 1 if Rcluster == 0 else 0
for i in range(105):
	if parties[i] == 'R' and labels[i] == Rcluster:
		continue
	if parties[i] == 'D' and labels[i] == Dcluster:
		continue
	# get and print all anomalies
	print "Anamoly: Senator {} of party {} was classified into cluster {}.".format(names[i], parties[i], str(labels[i]))

'''
Only two anomalies are consistently present: Sanders and King are classified as democrat, which is expected.
An unexpected anomaly that is only sometimes present is that Senator Jeff Sessions of the republican party is sometimes classified as democrat.
'''

print ""
# Problem 3:

# create mask2 for to get names, parties and votes of all senators except indepents, Feinstein and Harris to train SVM
mask2 = np.ones(len(c_names), dtype = bool)
mask2[11] = False # remove Harris
mask2[12] = False # remove Feinstein
non_ca_names = c_names[mask2]
non_ca_parties = c_parties[mask2]
non_ca_votes = c_votes[mask2,:]

clf = svm.SVC(gamma = 0.001, C = 100) # setup SVM
clf.fit(non_ca_votes, non_ca_parties) # train SVM for all non-CA and non-independent senators
print "Support Vector Machine predicts that Senator Harris is " + clf.predict([c_votes[11,:]])[0] + " based on her voting record." 
print "Support Vector Machine predicts that Senator Feinstein is " + clf.predict([c_votes[12,:]])[0] + " based on her voting record."

