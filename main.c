#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include "matrix.h"

void test_case0();
void test_case1();
void test_case2();
void test_case3();
void test_case4();
void test_case5();
void test_case6();
void test_case7();

int main()
{
    printf("In this main function, you can input number 0~7  to see the test case which can help you use it better!\n");
    printf("input -1 to exit\n");
    printf("--------------------------------------------------------------------------------------------\n");
    int testCase = 0;
    while (testCase != -1)
    {
        scanf("%d", &testCase);

        switch (testCase)
        {
        case 0:
        {
            test_case0();
            break;
        }
        case 1:
        {
            test_case1();
            break;
        }
        case 2:
        {
            test_case2();
            break;
        }
        case 3:
        {
            test_case3();
            break;
        }
        case 4:
        {
            test_case4();
            break;
        }
        case 5:
        {
            test_case5();
            break;
        }
        case 6:
        {
            test_case6();
            break;
        }
        case 7:
        {
            test_case7();
            break;
        }
        default:
            break;
        }
    }
    return 0;
}

void test_case0()
{
    printf("In this case, you can see how to creat a matrix\n");
    float a[] = {1.1, 2.2, 3.3, 4.4, 5.5, 6.6, 7.7, 8.8, 9.9};
    float b[] = {1.1, 2.2, 3.3, 4.4, 5.5, 6.6, 7.7, 8.8};
    Matrix *m1 = createMatrix_default(m1, 3, 3);
    printMatrix(m1);
    Matrix *m2 = createMatrix_initial(m2, 3, 3, a);
    printMatrix(m2);
    Matrix *m3 = createMatrix_default(m3, 2, 4);
    valueMatrix_array(m3, b);
    printMatrix(m3);

    deleteMatrix(&m1);
    deleteMatrix(&m2);
    deleteMatrix(&m3);
}

void test_case1()
{
    printf("In this case, you can see how to copy a matrix\n");
    float a[] = {1.1, 2.2, 3.3, 4.4, 5.5, 6.6, 7.7, 8.8, 9.9};
    Matrix *m1 = createMatrix_default(m1, 3, 3);
    printf("m1:\n");
    printMatrix(m1);
    Matrix *m2 = createMatrix_initial(m2, 3, 3, a);
    printf("m2:\n");
    printMatrix(m2);
    copyMatrix(m2, m1);
    printf("m1:\n");
    printMatrix(m1);
    deleteMatrix(&m1);
    deleteMatrix(&m2);
}

void test_case2()
{
    printf("In this case, you can see how to add mul and subtract two matrices\n");
    float a[] = {1.1, 2.2, 3.3, 4.4, 5.5, 6.6, 7.7, 8.8, 9.9};
    float b[] = {1.1, 2.2, 3.3, 4.4, 5.5, 6.6, 7.7, 8.8};
    float c[] = {9.9, 8.8, 7.7, 6.6, 5.5, 4.4, 3.3, 2.2, 1.1};
    Matrix *m1 = createMatrix_initial(m1, 3, 3, c);
    printf("m1:\n");
    printMatrix(m1);
    Matrix *m2 = createMatrix_initial(m2, 3, 3, a);
    printf("m2:\n");
    printMatrix(m2);
    Matrix *sum = addMatrix(m1, m2);
    printf("m1+m2:\n");
    printMatrix(sum);
    Matrix *sub = subtractMatrix(m1, m2);
    printf("m1-m2:\n");
    printMatrix(sub);
    Matrix *product = mulMatrix(m1, m2);
    printf("m1*m2:\n");
    printMatrix(product);
    deleteMatrix(&m1);
    deleteMatrix(&m2);
    deleteMatrix(&sum);
    deleteMatrix(&sub);
    deleteMatrix(&product);
}

void test_case3()
{
    printf("In this case, you can see how to add mul and subtract a scalar to matrices\n");
    float a[] = {1.1, 2.2, 3.3, 4.4, 5.5, 6.6, 7.7, 8.8, 9.9};
    Matrix *m2 = createMatrix_initial(m2, 3, 3, a);
    printf("m2:\n");
    printMatrix(m2);

    Matrix *add = addScalar(m2, 2);
    printf("add:\n");
    printMatrix(add);

    Matrix *sub = subtractScalar(m2, 2);
    printf("sub:\n");
    printMatrix(sub);

    Matrix *mul = mulByScalar(m2, 2);
    printf("mul:\n");
    printMatrix(mul);
}

void test_case4()
{
    printf("In this case, you can see how to find max and min value of matrix\n");
    float a[] = {1.1, 2.2, 3.3, 4.4, 5.5, 6.6, 7.7, 8.8, 9.9};
    Matrix *m2 = createMatrix_initial(m2, 3, 3, a);
    printf("m2:\n");
    printMatrix(m2);
    float b = findMaxValue(m2);
    float c = findMinValue(m2);
    printf("max:");
    printf("%f\n", b);
    printf("min:");
    printf("%f\n", c);
}

void test_case5()
{
    printf("In this case, you can see how to exchange rows and cols of matrix and the rowminus and colminus\n");
    float a[] = {1.1, 2.2, 3.3, 4.4, 5.5, 6.6, 7.7, 8.8, 9.9};
    Matrix *m2 = createMatrix_initial(m2, 3, 3, a);
    printf("m2:\n");
    printMatrix(m2);

    printf("exchange row1 and row3:\n");
    exchangeRows(m2, 1, 3);
    printMatrix(m2);

    printf("exchange col1 and col3:\n");
    exchangeCols(m2, 1, 3);
    printMatrix(m2);

    printf("row1 minus 3 times of row3:\n");
    rowMinus(m2, 1, 3, 3);
    printMatrix(m2);

    printf("col1 minus 3 times of col3:\n");
    rowMinus(m2, 1, 3, 3);
    printMatrix(m2);
}

void test_case6()
{
    printf("In this case, you can see how to transpose a matrix\n");
    float a[] = {1.1, 2.2, 3.3, 4.4, 5.5, 6.6, 7.7, 8.8, 9.9};
    Matrix *m2 = createMatrix_initial(m2, 3, 3, a);
    printf("m2:\n");
    printMatrix(m2);

    printf("transpose m2:\n");
    transposeMatrix(&m2);
    printMatrix(m2);
}

void test_case7()
{
    printf("In this case, you can see how to delete a matrix\n");
    float a[] = {1.1, 2.2, 3.3, 4.4, 5.5, 6.6, 7.7, 8.8, 9.9};
    Matrix *m2 = createMatrix_initial(m2, 3, 3, a);
    printf("m2:\n");
    printMatrix(m2);
    printf("The address of m2:OX%p\n", m2);
    deleteMatrix(&m2);
    printf("The address of m2 after delete:OX%p\n", m2);
}