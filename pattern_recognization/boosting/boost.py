"""
Robert Werthman
CSCI 5622
Homework 4: Boosting
"""
import argparse
import numpy as np 
from sklearn.tree import DecisionTreeClassifier
from sklearn.linear_model import Perceptron
from sklearn.base import clone 
import matplotlib.pyplot as plt
import math
import sys

np.random.seed(1234)

class FoursAndNines:
    """
    Class to store MNIST data
    """

    def __init__(self, location):

        import pickle, gzip

        # Load the dataset
        f = gzip.open(location, 'rb')

        # Split the data set 
        train_set, valid_set, test_set = pickle.load(f)

        # Extract only 4's and 9's for training set 
        self.x_train = train_set[0][np.where(np.logical_or( train_set[1]==4, train_set[1] == 9))[0],:]
        self.y_train = train_set[1][np.where(np.logical_or( train_set[1]==4, train_set[1] == 9))[0]]
        self.y_train = np.array([1 if y == 9 else -1 for y in self.y_train])
        
        # Shuffle the training data 
        shuff = np.arange(self.x_train.shape[0])
        np.random.shuffle(shuff)
        self.x_train = self.x_train[shuff,:]
        self.y_train = self.y_train[shuff]

        # Extract only 4's and 9's for validation set 
        self.x_valid = valid_set[0][np.where(np.logical_or( valid_set[1]==4, valid_set[1] == 9))[0],:]
        self.y_valid = valid_set[1][np.where(np.logical_or( valid_set[1]==4, valid_set[1] == 9))[0]]
        self.y_valid = np.array([1 if y == 9 else -1 for y in self.y_valid])
        
        # Extract only 4's and 9's for test set 
        self.x_test  = test_set[0][np.where(np.logical_or( test_set[1]==4, test_set[1] == 9))[0],:]
        self.y_test  = test_set[1][np.where(np.logical_or( test_set[1]==4, test_set[1] == 9))[0]]
        self.y_test = np.array([1 if y == 9 else -1 for y in self.y_test])
        
        f.close()

class AdaBoost:
    def __init__(self, n_learners=20, base=DecisionTreeClassifier(max_depth=1)):
        """
        Create a new adaboost classifier.
        
        Args:
            n_learners (int, optional): Number of weak learners in classifier.
            base (BaseEstimator, optional): Your general weak learner 

        Attributes:
            base (estimator): Your general weak learner 
            n_learners (int): Number of weak learners in classifier.
            alpha (ndarray): Coefficients on weak learners. 
            learners (list): List of weak learner instances. 
        """
        
        self.n_learners = n_learners 
        self.base = base
        self.alpha = np.zeros(self.n_learners)
        self.learners = []
        
    def fit(self, X_train, y_train):
        """
        Train AdaBoost classifier on data. Sets alphas and learners. 
        
        Args:
            X_train (ndarray): [n_samples x n_features] ndarray of training data   
            y_train (ndarray): [n_samples] ndarray of data 
        """

        # Initialize the weights so that they act like a probability
        # distribution.
        w = np.full(y_train.shape[0], 1.0/y_train.shape[0])

        for k in range(self.n_learners):
            # print 'Fitting learner...', k
            h = clone(self.base)

            # Fit a weak learner to the training data
            h.fit(X_train, y_train, sample_weight=w)

            # Pre-compute the predictions of the training samples
            predictions = np.zeros(w.shape[0])
            for i in range(w.shape[0]):
                predictions[i] = h.predict(X_train[i].reshape(1, -1))

            # Compute the weighted error of the weak learner 
            err = 0.0 
            for i in range(w.shape[0]):
                err += w[i]*(y_train[i] != predictions[i])
            err = err/np.sum(w)

            # Compute how good the weak learner is at prediction (weight)
            # Learners that make accurate predictions have higher weight
            # Small error = high alpha
            try:
                self.alpha[k] = .5*math.log((1 - err)/err)
            except (ValueError, ZeroDivisionError):
                print ('There was an error calculating the alpha.')
                sys.exit(1)

            # Re-compute the weights of the samples
            # Misclassified sample weight goes up 
            for i in range(w.shape[0]):
                w[i] = w[i]*math.exp(
                    -self.alpha[k]*y_train[i]*predictions[i])

            self.learners.append(h)
            
    def predict(self, X):
        """
        Adaboost prediction for new data X.
        
        Args:
            X (ndarray): [n_samples x n_features] ndarray of data 
            
        Returns: 
            [n_samples] ndarray of predicted labels {-1,1}
        """

        # For each sample sum up the prediction*weight (weighted vote) 
        # of each learner
        predictions = np.zeros(X.shape[0])
        for i in range(X.shape[0]):
            prediction = 0
            for k in range(len(self.learners)):
                prediction += self.alpha[k]*self.learners[k].predict(
                    X[i].reshape(1, -1))

            # Classify the sample as first class if sum is positive
            # Classify the sample as the second class if the sum is negative
            if prediction >= 0:
                y = 1
            else:
                y = -1
            predictions[i] = y

        return predictions
    
    def score(self, X, y):
        """
        Computes prediction accuracy of classifier.  
        
        Args:
            X (ndarray): [n_samples x n_features] ndarray of data 
            y (ndarray): [n_samples] ndarray of true labels  
            
        Returns: 
            Prediction accuracy (between 0.0 and 1.0).
        """

        # Accuracy = total correct/total samples
        num_samples = X.shape[0]
        num_correctly_predicted_samples = 0.0
        predictions = self.predict(X)

        for i in range(predictions.shape[0]):
            if predictions[i] == y[i]:
                num_correctly_predicted_samples += 1

        return num_correctly_predicted_samples/num_samples
    
    def staged_score(self, X, y):
        """
        Computes the ensemble score after each iteration of boosting 
        for monitoring purposes, such as to determine the score on a 
        test set after each boost.
        
        Args:
            X (ndarray): [n_samples x n_features] ndarray of data 
            y (ndarray): [n_samples] ndarray of true labels  
            
        Returns: 
            [n_learners] ndarray of scores 
        """

        # Each iteration has the addition of a weak learner
        # First iteration 1 learner, 2nd iteration 2 learners
        staged_scores = np.zeros(self.n_learners)
        learners = self.learners
        for k in range(self.n_learners):
            # print 'Calculating staged score at iteration %d...' % k
            self.learners = learners[:(k+1)]
            staged_scores[k] = self.score(X, y)

        return staged_scores


def mnist_digit_show(flatimage, outname=None):

	import matplotlib.pyplot as plt

	image = np.reshape(flatimage, (-1,28))

	plt.matshow(image, cmap=plt.cm.binary)
	plt.xticks([])
	plt.yticks([])
	if outname: 
	    plt.savefig(outname)
	else:
	    plt.show()

if __name__ == "__main__":

    parser = argparse.ArgumentParser(description='AdaBoost classifier options')
    parser.add_argument('--limit', type=int, default=-1,
                        help="Restrict training to this many examples")
    parser.add_argument('--n_learners', type=int, default=50,
                        help="Number of weak learners to use in boosting")
    args = parser.parse_args()

    data = FoursAndNines("../data/mnist.pklz")

    # An example of how your classifier might be called 
    clf = AdaBoost(n_learners=50, base=DecisionTreeClassifier(max_depth=1, criterion="entropy"))
    clf.fit(data.x_train[:args.limit], data.y_train[:args.limit])

    X = data.x_valid[:5]
    y = data.y_valid[:5]

    # A prediction of 1 means the digit is a 9
    # A prediction of -1 means the digit is a 4
    predictions = clf.predict(X)
    for i in range(predictions.shape[0]):
        if predictions[i] == y[i]:
            print( 'prediction is correct', y[i])
        else:
            print ('prediction is incorrect', y[i])
            # mnist_digit_show(sample[i])
    print ('Accuracy', clf.score(X, y))
