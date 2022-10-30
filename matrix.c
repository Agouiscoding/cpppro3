#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include "matrix.h"

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

//声明一个m*n的矩阵并初始化为0
Matrix *createMatrix_default(Matrix *matrix, long  row, long col)
{
    if (row > 0 && col > 0)
    {
        matrix = (Matrix *)malloc(sizeof(Matrix));
        matrix->row = row;
        matrix->col = col;
        matrix->data = (float *)malloc(sizeof(float) * row * col);
        memset(matrix->data, 0, sizeof(float) * row * col);
        return matrix;
    }
    else
    {
        printf("Error in createMatrix_default:The value of row or col must be greater than zero!\n");
        return NULL;
    }
}

//声明一个矩阵并用数组初始化
Matrix *createMatrix_initial(Matrix *matrix, long  row, long  col, float *array)
{
    if (row > 0 && col > 0)
    {
        matrix = (Matrix *)malloc(sizeof(Matrix));
        matrix->row = row;
        matrix->col = col;
        matrix->data = (float *)malloc(sizeof(float) * row * col);
        memcpy(matrix->data, array, matrix->row * matrix->col * sizeof(float));
        return matrix;
    }
    else
    {
        printf("Error in createMatrix_initial:The value of row or col must be greater than zero!\n");
        return NULL;
    }
}

//用数组给矩阵赋值
void valueMatrix_array(Matrix *matrix, float *array)
{
    if (matrix == NULL)
    {
        printf("Error in valueMatrix_array:The matrix does not exist or has been deleted!\n");
    }
    else
    {
        memcpy(matrix->data, array, matrix->row * matrix->col * sizeof(float));
    }
}

//用控制台给矩阵赋值
void valueMatrix_console(Matrix *matrix)
{
    if (matrix == NULL)
    {
        printf("Error in valueMatrix_console:The matrix does not exist or has been deleted!\n");
    }
    else
    {
        printf("matrix(%ld, %ld)  input element:\n", matrix->row, matrix->col);
        for (long  i = 0; i < matrix->row; i++)
        {
            for (long  j = 0; j < matrix->col; j++)
            {
                long  ret;
                char c;
                do
                {
                    ret = scanf("%f", &matrix->data[i * matrix->col + j]);
                    if (ret < 1)
                    {
                        while ((c = getchar()) != EOF && c != '\n')
                            ;
                        i = 0;
                        j = 0;
                        printf("invalid input! Please restart the input\n");
                    }
                } while (ret < 1);
            }
        }
    }
}

//删除一个矩阵 释放空间 指针置NULL
void deleteMatrix(Matrix **matrix)
{
    if (*matrix == NULL)
    {
        printf("Error in deleteMatrix:This matrix has already been deleted!\n");
        return;
    }
    free((*matrix)->data);
    (*matrix)->data = NULL;
    free(*matrix);
    *matrix = NULL;
}

//返回矩阵的大小row*col
long  sizeMatrix(Matrix *matrix)
{
    return matrix->row * matrix->col;
}

//将一个矩阵里的数拷贝到另一个矩阵里
void copyMatrix(Matrix *matrixToBeCopied, Matrix *matrix)
{
    if (matrixToBeCopied == NULL || matrix == NULL)
    {
        printf("Error in copyMatrix:one of the matrix does not exist or has been deleted!\n");
    }
    else
    {
        matrix->row = matrixToBeCopied->row;
        matrix->col = matrixToBeCopied->col;
        memcpy(matrix->data, matrixToBeCopied->data, sizeMatrix(matrixToBeCopied) * sizeof(float));
    }
}

//矩阵相加
Matrix *addMatrix(Matrix *matrix_addend1, Matrix *matrix_addend2)
{
    if (matrix_addend1 == NULL || matrix_addend2 == NULL)
    {
        printf("Error in addMatrix:one of the matrix does not exist or has been deleted!\n");
        return NULL;
    }
    else if (matrix_addend1->row == matrix_addend2->row && matrix_addend1->col == matrix_addend2->col)
    {
        Matrix *matrix_sum = createMatrix_default(matrix_sum, matrix_addend1->row, matrix_addend1->col);
        for (long  i = 0; i < matrix_addend1->row; i++)
        {
            for (long  j = 0; j < matrix_addend1->col; j++)
            {
                matrix_sum->data[i * matrix_sum->col + j] =
                    matrix_addend1->data[i * matrix_addend1->col + j] + matrix_addend2->data[i * matrix_addend1->col + j];
            }
        }
        return matrix_sum;
    }
    else
    {
        printf("Error in addMatrix:Matrices that are not homogenous cannot be added!\n");
        return NULL;
    }
}

//矩阵相减
Matrix *subtractMatrix(Matrix *matrix_minuend, Matrix *matrix_subtrahend)
{
    if (matrix_minuend == NULL || matrix_subtrahend == NULL)
    {
        printf("one of the matrix does not exist or has been deleted!\n");
        return NULL;
    }
    else if (matrix_minuend->row == matrix_subtrahend->row && matrix_minuend->col == matrix_subtrahend->col)
    {
        Matrix *matrix_dif = createMatrix_default(matrix_dif, matrix_minuend->row, matrix_minuend->col);
        for (long  i = 0; i < matrix_minuend->row; i++)
        {
            for (long  j = 0; j < matrix_minuend->col; j++)
            {
                matrix_dif->data[i * matrix_dif->col + j] =
                    matrix_minuend->data[i * matrix_minuend->col + j] - matrix_subtrahend->data[i * matrix_minuend->col + j];
            }
        }
        return matrix_dif;
    }
    else
    {
        printf("Error in subtractMatrix:Matrices that are not homogenous cannot be added!\n");
        return NULL;
    }
}

//给矩阵内的每个参数加上一个常数
Matrix *addScalar(Matrix *matrix, float scalar)
{
    if (matrix == NULL)
    {
        printf("Error in addScalar:The matrix does not exist or has been deleted!\n");
        return NULL;
    }
    else
    {

        for (long  i = 0; i < matrix->col * matrix->row; i++)
        {
            matrix->data[i] = matrix->data[i] + scalar;
        }
    }

    return matrix;
}

//给矩阵内的每个参数减去一个常数
Matrix *subtractScalar(Matrix *matrix, float scalar)
{
    if (matrix == NULL)
    {
        printf("Error in subtractScalar:The matrix does not exist or has been deleted!\n");
        return NULL;
    }
    else
    {

        for (long  i = 0; i < matrix->col * matrix->row; i++)
        {
            matrix->data[i] = matrix->data[i] - scalar;
        }
    }

    return matrix;
}

//给矩阵内的每个参数乘上一个常数
Matrix *mulByScalar(Matrix *matrix, float scalar)
{
    if (matrix == NULL)
    {
        printf("Error in mulByScalar:The matrix does not exist or has been deleted!\n");
        return NULL;
    }
    else
    {

        for (long  i = 0; i < matrix->col * matrix->row; i++)
        {
            matrix->data[i] = matrix->data[i] * scalar;
        }
    }

    return matrix;
}

//矩阵相乘
Matrix *mulMatrix(Matrix *matrix_multiplicand, Matrix *matrix_multiplier)
{
    if (matrix_multiplicand == NULL || matrix_multiplier == NULL)
    {
        printf("Error in mulMatrix:one of the matrix does not exist or has been deleted!\n");
        return NULL;
    }
    else if (matrix_multiplicand->col == matrix_multiplier->row)
    {
        Matrix *matrix_product = createMatrix_default(matrix_product, matrix_multiplicand->row, matrix_multiplier->col);
        for (long  i = 0; i < matrix_multiplicand->row; i++)
        {
            for (long  j = 0; j < matrix_multiplier->col; j++)
            {
                for (long  k = 0; k < matrix_multiplicand->col; k++)
                {
                    matrix_product->data[i * matrix_product->col + j] += matrix_multiplicand->data[i * matrix_multiplicand->col + k] * matrix_multiplier->data[k * matrix_multiplier->col + j];
                }
            }
        }
        return matrix_product;
    }
    else
    {
        printf("Error in mulMatrix:matrix_multiplicand's column must equal to matrix_multiplier's row!\n");
        return NULL;
    }
}

//找到矩阵内所有参数里的最大值
float findMaxValue(Matrix *matrix)
{
    if (matrix == NULL)
    {
        printf("Error in findMaxValue:The matrix does not exist or has been deleted!\n");
        return -1;
    }
    else
    {
        float max = -__FLT_MAX__;
        for (long  i = 0; i < (matrix->col * matrix->row); i++)
        {
            float tem = matrix->data[i];
            max = (tem > max ? tem : max);
        }
        return max;
    }
}

//找到矩阵内所有参数的最小值
float findMinValue(Matrix *matrix)
{
    if (matrix == NULL)
    {
        printf("Error in findMinValue:The matrix does not exist or has been deleted!\n");
        return -1;
    }
    else
    {
        float min = __FLT_MAX__;
        for (long  i = 0; i < (matrix->col * matrix->row); i++)
        {
            float tem = matrix->data[i];
            min = (min < tem ? min : tem);
        }
        return min;
    }
}

//将矩阵内的任意两行交换位置
void exchangeRows(Matrix *matrix, long  row1, long  row2)
{
    if (matrix == NULL)
    {
        printf("Error in exchangeRows:The matrix does not exist or has been deleted!\n");
    }
    else if ((row1 < 1 || row1 > matrix->row) || (row2 < 1 || row2 > matrix->row))
    {
        printf("Error in exchangeRows:one of the rows is out of bound\n");
    }
    else
    {
        float tem;
        for (long  i = 0; i < matrix->col; i++)
        {
            tem = matrix->data[(row1 - 1) * matrix->col + i];
            matrix->data[(row1 - 1) * matrix->col + i] = matrix->data[(row2 - 1) * matrix->col + i];
            matrix->data[(row2 - 1) * matrix->col + i] = tem;
        }
    }
}

//将矩阵内的任意两列交换位置
void exchangeCols(Matrix *matrix, long  col1, long  col2)
{

    if (matrix == NULL)
    {
        printf("Error in exchangeCols:The matrix does not exist or has been deleted!\n");
    }
    else if ((col1 < 1 || col1 > matrix->col) || (col2 < 1 || col2 > matrix->col))
    {
        printf("Error in exchangeCols:one of the rows is out of bound\n");
    }
    else
    {
        float tem;
        for (long  i = 0; i < matrix->col; i++)
        {
            tem = matrix->data[i * matrix->col + (col1 - 1)];
            matrix->data[i * matrix->col + (col1 - 1)] = matrix->data[i * matrix->col + (col2 - 1)];
            matrix->data[i * matrix->col + (col2 - 1)] = tem;
        }
    }
}

//两行相减(第row1行减去第row2行的multiple倍)
void rowMinus(Matrix *matrix, long  row1, long  row2, float multiple)
{
    if (matrix == NULL)
    {
        printf("Error in rowMinus:The matrix does not exist or has been deleted!\n");
    }
    else if ((row1 < 1 || row1 > matrix->row) || (row2 < 1 || row2 > matrix->row))
    {
        printf("Error in rowMinus:one of the rows is out of bound\n");
    }
    else
    {
        for (long  i = 0; i < matrix->col; i++)
        {
            matrix->data[(row1 - 1) * matrix->col + i] -= matrix->data[(row2 - 1) * matrix->col + i] * multiple;
            if (fabs(matrix->data[(row1 - 1) * matrix->col + i]) < __FLT_EPSILON__)
            {
                matrix->data[(row1 - 1) * matrix->col + i] = 0;
            }
        }
    }
}

//两列相减(第col1列减去第col2列的multiple倍)
void colMinus(Matrix *matrix, long  col1, long  col2, float multiple)
{
    if (matrix == NULL)
    {
        printf("Error in colMinus:The matrix does not exist or has been deleted!\n");
    }
    else if ((col1 < 1 || col1 > matrix->col) || (col2 < 1 || col2 > matrix->col))
    {
        printf("Error in colMinus:one of the cols is out of bound\n");
    }
    else
    {
        for (long  i = 0; i < matrix->col; i++)
        {
            matrix->data[i * matrix->col + (col1 - 1)] -= matrix->data[i * matrix->col + (col2 - 1)] * multiple;
            if (fabs(matrix->data[i * matrix->col + (col1 - 1)]) < __FLT_EPSILON__)
            {
                matrix->data[i * matrix->col + (col1 - 1)] = 0;
            }
        }
    }
}

//将传入的矩阵转置
void transposeMatrix(Matrix **matrix)
{
    if (*matrix == NULL)
    {
        printf("Error in transposeMatrix:The matrix does not exist or has been deleted!\n");
    }
    Matrix tem = **matrix;
    Matrix *tem1 = createMatrix_default(*matrix, (*matrix)->col, (*matrix)->row);
    for (long  i = 0; i < tem1->row; i++)
    {
        for (long  j = 0; j < tem1->col; j++)
        {
            tem1->data[i * tem1->col + j] = tem.data[j * tem1->col + i];
        }
    }
    deleteMatrix(matrix);
    *matrix = tem1;
}

//打印矩阵
void printMatrix(Matrix *matrix)
{
    if (matrix == NULL)
    {
        printf("Error in printMatrix:The matrix does not exist or has been deleted!\n");
    }
    else
    {

        for (long  i = 0; i < (matrix->col * matrix->row); i++)
        {
            printf("%lf\t", matrix->data[i]);
            if ((i + 1) % matrix->col == 0)
                printf("\n");
        }
        printf("\n");
    }
}
