# Velodyne

All code is written using python 3.6 version and requires numpy, scipy, matplotlib libraries to be installed to successfuly  run the programs.  

This repository explores Object Detection and Classification on VELODYNE's raw point cloud data (X, Y, Z, I) from KITTI dataset [4] based on research methods by [1].  

The repository contains code for the following aspects requried to classify point cloud data.

#### OBJECT DETECTION

connected.py : Class to extract connected components on a binary matrix

occupancy_grid.py: This program creates an occupancy grid for 3D point cloud data. 

segemntation.py : This program generates 3D bounding boxes on objects detected from connected components.

```
python segmentation.py path/to/one/sequence/of/frames
```

#### CLASSIFICATION

feature_extraction.py: This program extracts object level and point level features from each component and creates a 28 dimensinal vector.

svm_train.py : This program generates a SVM model for the training data provided as input

```
python svm_train.py path/to/training/dataset/*.txt -o path/to/save/trained_model
```

svm_test.py : This program outputs the test accuracy and confusion matrix corresponsing to the test dataset and trained model provided as input. 

```
python svm_test.py path/to/test/dataset/*.txt path/to/trained_model
```


#### VISUALIZATION

read_point.cpp : This c++ file converts point cloud data from txt to pcd format using Point Cloud Library (PCL). Later point clouds can be visualized using MATLAB's pcread() and pcshow() commands.

#### REFERENCE


[1] Himmelsbach, Michael, et al. "LIDAR-based 3D object perception." Proceedings of 1st international workshop on cognition for technical systems. Vol. 1. 2008.

[2] http://pointclouds.org/documentation/tutorials/using_pcl_pcl_config.php#using-pcl-pcl-config 

[4] Geiger, Andreas, Philip Lenz, and Raquel Urtasun. "Are we ready for autonomous driving? the kitti vision benchmark suite." Computer Vision and Pattern Recognition (CVPR), 2012 IEEE Conference on. IEEE, 2012.


