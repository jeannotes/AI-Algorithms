import numpy as np
from sklearn import svm
from sklearn.model_selection import GridSearchCV
from sklearn.model_selection import train_test_split
import argparse
from features_extraction import *
from sklearn.externals import joblib
import os


'''  References: 
http://scikit-learn.org/stable/modules/generated/sklearn.model_selection.GridSearchCV.html#sklearn.model_selection.GridSearchCV
http://scikit-learn.org/stable/auto_examples/model_selection/plot_grid_search_digits.html
'''

def train(filenames, output):
    classes = []
    laser_data = np.zeros((len(filenames), NUM_FEATURES))
    labels = np.zeros((len(filenames)))

    # For each point, downsample to 200 points
    # generate 28 dimensional features 
    for i, pt in enumerate(filenames):
        class_name = os.path.basename(os.path.dirname(pt))

        if class_name not in classes:
            classes.append(class_name)

        class_index = classes.index(class_name)

        print('Processing {} as class {}'.format(pt, class_index))

        laser_data[i] = feature_extraction(pt)
        labels[i] = class_index
    # parameters on which to perform grid search
    parameter_candidates = [{'C': [1, 10, 100, 1000], 
        'gamma': [0.001, 0.0001], 'kernel': ['rbf', 'linear', 'poly']}]

    # calling the SVM grid search function to be used on the training set 
    classifier = GridSearchCV(estimator=svm.SVC(), param_grid=parameter_candidates, n_jobs=-1, cv=2)

    # Training the classifier on the training data
    classifier.fit(laser_data, labels)

    best_C = classifier.best_params_['C']
    best_kernel = classifier.best_params_['kernel']
    best_gamma = classifier.best_params_['gamma']

    # Reporting the best parameters found on 2-fold cross validation
    print("Best C : {}".format(best_C))
    print("Best kernel : {}".format(best_kernel))
    print("Best gamma : {}".format(best_gamma))

    # Saving the model
    if output:
        print("Saving the classifier to {}".format(output))
        joblib.dump(classifier, '/home/ramrao/velodyne/velo_code/classification/' + output)
    else:
        print("Saving the classifier to trained_classifier.pkl")
        joblib.dump(classifier, '/home/ramrao/velodyne/velo_code/classification/trained_classifier.pkl')

    return best_C, best_gamma


def main():
    parser = argparse.ArgumentParser()
    parser.add_argument('source', nargs='+', help='list of .txt objects for training')
    parser.add_argument('-o', '--output', default='trained_classifier.pkl', 
        help='Please provide name to store the trained_classifier, default to trained_classifier.pkl')
    args = parser.parse_args()
    
    f = train(args.source, args.output)
    return 


if __name__ == '__main__':
    main()
