"""
Author      : Yi-Chieh Wu, Sriram Sankararaman
Description : Famous Faces
"""

# python libraries
import collections
import time

# numpy libraries
import numpy as np

# matplotlib libraries
import matplotlib.pyplot as plt

# libraries specific to project
import util
from util import *
from cluster import *

######################################################################
# helper functions
######################################################################

def build_face_image_points(X, y) :
    """
    Translate images to (labeled) points.
    
    Parameters
    --------------------
        X     -- numpy array of shape (n,d), features (each row is one image)
        y     -- numpy array of shape (n,), targets
    
    Returns
    --------------------
        point -- list of Points, dataset (one point for each image)
    """
    
    n,d = X.shape
    
    images = collections.defaultdict(list) # key = class, val = list of images with this class
    for i in xrange(n) :
        images[y[i]].append(X[i,:])
    
    points = []
    for face in images :
        count = 0
        for im in images[face] :
            points.append(Point(str(face) + '_' + str(count), face, im))
            count += 1

    return points


def plot_clusters(clusters, title, average) :
    """
    Plot clusters along with average points of each cluster.

    Parameters
    --------------------
        clusters -- ClusterSet, clusters to plot
        title    -- string, plot title
        average  -- method of ClusterSet
                    determines how to calculate average of points in cluster
                    allowable: ClusterSet.centroids, ClusterSet.medoids
    """
    
    plt.figure()
    np.random.seed(20)
    label = 0
    colors = {}
    centroids = average(clusters)
    for c in centroids :
        coord = c.attrs
        plt.plot(coord[0],coord[1], 'ok', markersize=12)
    for cluster in clusters.members :
        label += 1
        colors[label] = np.random.rand(3,)
        for point in cluster.points :
            coord = point.attrs
            plt.plot(coord[0], coord[1], 'o', color=colors[label])
    plt.title(title)
    plt.show()


def generate_points_2d(N, seed=1234) :
    """
    Generate toy dataset of 3 clusters each with N points.
    
    Parameters
    --------------------
        N      -- int, number of points to generate per cluster
        seed   -- random seed
    
    Returns
    --------------------
        points -- list of Points, dataset
    """
    np.random.seed(seed)
    
    mu = [[0,0.5], [1,1], [2,0.5]]
    sigma = [[0.1,0.1], [0.25,0.25], [0.15,0.15]]
    
    label = 0
    points = []
    for m,s in zip(mu, sigma) :
        label += 1
        for i in xrange(N) :
            x = util.random_sample_2d(m, s)
            points.append(Point(str(label)+'_'+str(i), label, x))
    
    return points


######################################################################
# k-means and k-medoids
######################################################################

def random_init(points, k) :
    """
    Randomly select k unique elements from points to be initial cluster centers.
    
    Parameters
    --------------------
        points         -- list of Points, dataset
        k              -- int, number of clusters
    
    Returns
    --------------------
        initial_points -- list of k Points, initial cluster centers
    """
    ### ========== TODO : START ========== ###
    # part 2c: implement (hint: use np.random.choice)
    return np.random.choice(points, k, replace=False)
    ### ========== TODO : END ========== ###


def cheat_init(points) :
    """
    Initialize clusters by cheating!
    
    Details
    - Let k be number of unique labels in dataset.
    - Group points into k clusters based on label (i.e. class) information.
    - Return medoid of each cluster as initial centers.
    
    Parameters
    --------------------
        points         -- list of Points, dataset
    
    Returns
    --------------------
        initial_points -- list of k Points, initial cluster centers
    """
    ### ========== TODO : START ========== ###
    # part 2f: implement
    initial_points = []

    clusters_dict = {}

    for point in points:
        if point.label in clusters_dict:
            clusters_dict[point.label].append(point)
        else:
            clusters_dict[point.label] = [point]

    for key, val in clusters_dict.items():
        cluster = Cluster(val)
        initial_points.append(cluster.medoid())

    return initial_points
    ### ========== TODO : END ========== ###


def kAverages(points, k, average, init='random', plot=False):
    cluster_centers = random_init(points, k) if init == 'random' else cheat_init(points)
    old_clusters, i = None, 0

    while True:
        i += 1
        clusters = ClusterSet()
        centers_dict = {}

        for point in points:
            min_index, min_dist = -1, np.inf

            for j in range(len(cluster_centers)):
                if point.distance(cluster_centers[j]) < min_dist:
                    min_index = j
                    min_dist = point.distance(cluster_centers[min_index])

            if min_index in centers_dict:
                centers_dict[min_index].append(point)
            else:
                centers_dict[min_index] = [point]

        for key, val in centers_dict.items():
            clusters.add(Cluster(val))

        if plot:
            plot_clusters(clusters, 'iteration: '+str(i), average)

        if old_clusters is not None and clusters.equivalent(old_clusters):
            return clusters 
        else:
            old_clusters = clusters 
            if average == ClusterSet.centroids:
                cluster_centers = clusters.centroids()
            else:
                cluster_centers = clusters.medoids()

    return []

def kMeans(points, k, init='random', plot=False) :
    """
    Cluster points into k clusters using variations of k-means algorithm.
    
    Parameters
    --------------------
        points  -- list of Points, dataset
        k       -- int, number of clusters
        average -- method of ClusterSet
                   determines how to calculate average of points in cluster
                   allowable: ClusterSet.centroids, ClusterSet.medoids
        init    -- string, method of initialization
                   allowable: 
                       'cheat'  -- use cheat_init to initialize clusters
                       'random' -- use random_init to initialize clusters
        plot    -- bool, True to plot clusters with corresponding averages
                         for each iteration of algorithm
    
    Returns
    --------------------
        k_clusters -- ClusterSet, k clusters
    """
    
    ### ========== TODO : START ========== ###
    # part 2c: implement
    # Hints:
    #   (1) On each iteration, keep track of the new cluster assignments
    #       in a separate data structure. Then use these assignments to create
    #       a new ClusterSet object and update the centroids.
    #   (2) Repeat until the clustering no longer changes.
    #   (3) To plot, use plot_clusters(...).

    return kAverages(points, k, ClusterSet.centroids, init, plot)

    ### ========== TODO : END ========== ###


def kMedoids(points, k, init='random', plot=False) :
    """
    Cluster points in k clusters using k-medoids clustering.
    See kMeans(...).
    """
    ### ========== TODO : START ========== ###

    return kAverages(points, k, ClusterSet.medoids, init, plot)

    ### ========== TODO : END ========== ###


######################################################################
# main
######################################################################

def main() :
    ### ========== TODO : START ========== ###
    # part 1: explore LFW data set
    
    X, y = get_lfw_data()
    show_image(X[0])
    show_image(X[1])
    show_image(X[2])
    show_image(np.mean(X, axis=0))

    U, mu = util.PCA(X)
    plot_gallery([vec_to_image(U[:,i]) for i in xrange(12)])

    dimensions = [1, 10, 50, 100, 500, 1288]
    for l in dimensions:
        Z, Ul = apply_PCA_from_Eig(X, U, l, mu)
        X_rec = reconstruct_from_PCA(Z, Ul, mu)
        plot_gallery([vec_to_image(X_rec[i]) for i in xrange(12)], title=str(l))

    ### ========== TODO : END ========== ###
    
    
    
    ### ========== TODO : START ========== ###
    # part 2d-2f: cluster toy dataset
    
    np.random.seed(1234)
    points = generate_points_2d(20)
    clusters = kMeans(points, 3, init='cheat', plot=True)
    medoids = kMedoids(points, 3, init='cheat', plot=True)

    ### ========== TODO : END ========== ###
    
    
    
    ### ========== TODO : START ========== ###    
    # part 3a: cluster faces

    np.random.seed(1234)
    X1, y1 = util.limit_pics(X, y, [4, 6, 13, 16], 40)
    points = build_face_image_points(X1, y1)

    k_means_scores, k_means_times, k_medoids_scores, k_medoids_times = [], [], [], []

    for _ in xrange(10):
        start = time.time()
        clusters = kMeans(points, 4, init='random', plot=False)
        k_means_scores.append(clusters.score())
        k_means_times.append(time.time()-start)

        start = time.time()
        clusters = kMedoids(points, 4, init='random', plot=False)
        k_medoids_scores.append(clusters.score())
        k_medoids_times.append(time.time()-start)

    print('k-means average: {}'.format(np.mean(k_means_scores)))
    print('k-means min: {}'.format(np.min(k_means_scores)))
    print('k-means max: {}'.format(np.max(k_means_scores)))
    print('k-means average runtime: {}'.format(np.mean(k_means_times)))
    print('k-medoids average: {}'.format(np.mean(k_medoids_scores)))
    print('k-medoids min: {}'.format(np.min(k_medoids_scores)))
    print('k-medoids max: {}'.format(np.max(k_medoids_scores)))
    print('k-medoids average runtime: {}'.format(np.mean(k_medoids_times)))
        
    # part 3b: explore effect of lower-dimensional representations on clustering performance
   
    np.random.seed(1234)
    X2, y2 = util.limit_pics(X, y, [4, 13], 40)
    k_means_scores, k_medoids_scores = [], []
    l_range = list(range(1, 42, 2))

    for l in range(1, 42, 2):
        Z, Ul = apply_PCA_from_Eig(X2, U, l, mu)
        X2_rec = reconstruct_from_PCA(Z, Ul, mu)
        points = build_face_image_points(X2_rec, y2)

        k_means_clusters = kMeans(points, 2, init='cheat')
        k_medoids_clusters = kMedoids(points, 2, init='cheat')

        k_means_scores.append(k_means_clusters.score())
        k_medoids_scores.append(k_medoids_clusters.score())

    plt.plot(l_range, k_means_scores, label='kMeans')
    plt.plot(l_range, k_medoids_scores, label='kMedoids')
    plt.legend()
    plt.title('Performance vs Number of Principle Components')
    plt.xlabel('Number of Principle Components')
    plt.ylabel('K-Means/K-Medoids Clustering Score')
    plt.show()

    
    # part 3c: determine ``most discriminative'' and ``least discriminative'' pairs of images
    
    np.random.seed(1234)
    min_score, max_score = (np.inf, None, None), (-1, None, None)

    for i in xrange(19):
        for j in xrange(19):
            if i != j:
                X3, y3 = limit_pics(X, y, [i, j], 40)
                points = build_face_image_points(X3, y3)
                clusters = kMeans(points, 2, init='cheat')
                if clusters.score() < min_score[0]:
                    min_score = (clusters.score(), i, j)
                if clusters.score() > max_score[0]:
                    max_score = (clusters.score(), i, j)

    print(min_score)
    plot_representative_images(X, y, [min_score[1], min_score[2]], title='Hard to Discriminate')
    print(max_score)
    plot_representative_images(X, y, [max_score[1], max_score[2]], title='Easy to Discriminate')
    
    ### ========== TODO : END ========== ###


if __name__ == "__main__" :
    main()














