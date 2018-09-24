#ifndef SMO_H
#define SMO_H
#include<iostream>
#include<fstream>
#include "ctype.h"
#include "math.h"
#include "stdlib.h"
#include "time.h"

#define N 27//样本数总数
#define end_support_i 27
#define first_test_i 27
#define d 13//维数

int C=100;//惩罚参数
double tolerance=0.001;//ui与边界0,C之间的公差范围
double eps=1e-3;//一个近似0的小数
int two_sigma_squared=100;//RBF(Radial-Basis Function)核函数中的参数。sigma==(10/2)^1/2。
double alph[end_support_i];//Lagrange multipiers
double b;//threshold
double error_cache[end_support_i];//存放non-bound样本误差
int target[N];//训练与测试样本的目标值
//double precomputed_self_dot_product[N];//预存dot_product_func(i,i)的值，以减少计算量
double dense_points[N][d];//存放训练与测试样本，0-end_support_i-1训练;first_test_i-N测试

int takeStep(int,int);
int examineNonBound(int);
int examineBound(int);
int examineFirstChoice(int,double);
int examineExample(int);
double kernel_func(int,int);
double learned_func(int);
double dot_product_func(int,int);
double error_rate();
void setX();//设置样本值矩阵
void setT();//设置目标值向量
void initialize();

//class SMO
//{
//public:
//    SMO();



//};

#endif // SMO_H
