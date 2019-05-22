import unittest
from boost import AdaBoost
from boost import FoursAndNines
import numpy as np 
from sklearn.tree import DecisionTreeClassifier

np.random.seed(1234)

X = np.array([
[6,9.5],
[4,8.5],
[9,8.75],
[8,8.0],
[3,7],
[1,6.5],
[5,6.5],
[1.5,2.5],
[2,1],
[9,2],
])
y = np.array([1,1,-1,1,-1,1,-1,1,-1,-1])

class TestBoost(unittest.TestCase):
    def setUp(self):
        self.clf = AdaBoost(n_learners=3)
        self.clf.fit(X, y)

    def testAll(self):

        # ===================================================== 
        # prediction test 
        # ===================================================== 
        pred = self.clf.predict(X)
        for (p, yi) in zip(pred, y):
            self.assertAlmostEqual(p, yi)

        # ===================================================== 
        # score test 
        # ===================================================== 
        score = self.clf.score(X, y)
        self.assertAlmostEqual(score, 1.0)

        # ===================================================== 
        # alphas test 
        # ===================================================== 
        alphas = self.clf.alpha
        self.assertAlmostEqual(alphas[0], 0.42364893019360172)
        self.assertAlmostEqual(alphas[1], 0.64964149206513044)
        self.assertAlmostEqual(alphas[2], 0.92291334524916524)

        # ===================================================== 
        # stage_score test 
        # ===================================================== 
        staged_score = self.clf.staged_score(X, y)
        self.assertAlmostEqual(staged_score[0], 0.7)
        self.assertAlmostEqual(staged_score[1], 0.7)
        self.assertAlmostEqual(staged_score[2], 1.0)


if __name__ == '__main__':
    unittest.main()

