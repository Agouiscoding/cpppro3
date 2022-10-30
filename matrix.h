#pragma once

typedef struct
{
    long row;
    long col;
    float *data;
} Matrix;

Matrix *createMatrix_default(Matrix *matrix, long row, long col);               //声明一个m*n的矩阵并初始化为0
Matrix *createMatrix_initial(Matrix *matrix, long row, long col, float *array); //声明一个矩阵并用数组初始化
void valueMatrix_array(Matrix *matrix, float *array);                         //用数组给矩阵赋值
void valueMatrix_console(Matrix *matrix);                                     //用控制台给矩阵赋值
void deleteMatrix(Matrix **matrix);                                           //删除一个矩阵 释放空间 指针置NULL
void copyMatrix(Matrix *matrixToBeCopied, Matrix *matrix);                    //将一个矩阵里的数拷贝到另一个矩阵里
long  sizeMatrix(Matrix *matrix);                                               //返回矩阵的大小row*col
Matrix *addMatrix(Matrix *matrix_addend1, Matrix *matrix_addend2);            //矩阵相加
Matrix *subtractMatrix(Matrix *matrix_minuend, Matrix *matrix_subtrahend);    //矩阵相减
Matrix *mulMatrix(Matrix *matrix_multiplicand, Matrix *matrix_multiplier);    //矩阵相乘
Matrix *addScalar(Matrix *matrix, float scalar);                              //给矩阵内的每个参数加上一个常数
Matrix *subtractScalar(Matrix *matrix, float scalar);                         //给矩阵内的每个参数减去一个常数
Matrix *mulByScalar(Matrix *matrix, float scalar);                            //给矩阵内的每个参数乘上一个常数
float findMaxValue(Matrix *matrix);                                           //找到矩阵内所有参数里的最大值
float findMinValue(Matrix *matrix);                                           //找到矩阵内所有参数的最小值
void exchangeRows(Matrix *matrix, long row1, long row2);                        //将矩阵内的任意两行交换位置
void exchangeCols(Matrix *matrix, long  col1, long col2);                        //将矩阵内的任意两列交换位置
void rowMinus(Matrix *matrix, long row1, long  row2, float multiple);            //两行相减(第row1行减去第row2行的multiple倍)
void colMinus(Matrix *matrix, long  col1, long  col2, float multiple);            //两列相减(第col1列减去第col2列的multiple倍)
void transposeMatrix(Matrix **matrix);                                        //将传入的矩阵转置
void printMatrix(Matrix *matrix);                                             //打印矩阵