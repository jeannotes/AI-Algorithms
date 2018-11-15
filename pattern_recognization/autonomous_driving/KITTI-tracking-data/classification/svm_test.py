import numpy as np
from sklearn.svm import SVC
from sklearn.model_selection import GridSearchCV
from sklearn.model_selection import train_test_split
import argparse
from features_extraction import *
from sklearn.externals import joblib
import os
import sklearn.metrics


    # For each point, downsample to 200 points
    # generate 28 dimensional features 
def test(filenames, classifier):
	classes = []
	laser_data = np.zeros((len(filenames), NUM_FEATURES))
	labels = np.zeros((len(filenames)))
	for i, pt in enumerate(filenames):
		class_name = os.path.basename(os.path.dirname(pt))
		if class_name not in classes:
			classes.append(class_name)

		class_index = classes.index(class_name)

		print('Processing {} as class {}'.format(pt, class_index))

		laser_data[i] = feature_extraction(pt)
		labels[i] = class_index

	# Loading the classifier passed as input
	classify = joblib.load(classifier)
	# obtaining accuracy on the test set
	result = classify.score(laser_data, labels)
	print("Accuracy of the model on test data is : {}".format(result*100))
	# Computing the confusion matrix
	y_pred = classify.predict(laser_data)
	conf_mat = sklearn.metrics.confusion_matrix(labels, y_pred)
	print(conf_mat)
	return result
        

def main():
    parser = argparse.ArgumentParser()
    parser.add_argument('source', nargs='+', help='list of .txt objects for testing')
    parser.add_argument('classifier', help='Please provide the classifer .pkl file')
    args = parser.parse_args()
    
    f = test(args.source, args.classifier)
    print(f)
    return 


if __name__ == '__main__':
    main()
