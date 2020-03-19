// -------------- driver.cpp -------------------
// Sung Ho Park
// 1/8/2020
// 1/18/2020
// -------------------------------------------------
// Purpose - This is tests the polynomial class to make
// sure that each method works.
// --------------------------------------------------
// No special methods/algorithms used.
// --------------------------------------------------
#include <iostream>
#include <assert.h>
using namespace std;

#include "polynomial.h"

void Test1()
{
    //Change coefficient, + operator,
    //and operator =
    cout << "Test 1: Testing +, =, and changeCoefficient" << endl;
    cout << endl;
    
    Polynomial p1;
    p1.changeCoefficient(1, 1);
    p1.changeCoefficient(4, 4);
    p1.changeCoefficient(2.2, 2);
    p1.changeCoefficient(-3.8, 3);
    cout << "p1 = " << p1 << endl;
       
    p1.changeCoefficient(0, 2);
    cout << "p1 = " << p1 << endl;
    Polynomial p2 = p1;
    cout << "p2 = " << p2 << endl;
    p2.changeCoefficient(9.5, 2);
       
    cout << "p2 = " << p2 << endl;
       
    Polynomial p3 = p1 + p2;
    cout << "p3 = " << p3 << endl;
    
    Polynomial p4;
    p4.changeCoefficient(2, 2);
    p4.changeCoefficient(1, 1);
    p4.changeCoefficient(3, 4);
    p4.changeCoefficient(4, 5);
    p4.changeCoefficient(7, 3);
    
    cout << "p4 = " << p4 << endl;
    
    Polynomial p5 = p4 + p3;
    cout << "p5 = " << p5 << endl;
    
    p5 = p1;
    cout << "p5 = " << p5 << endl;
    cout << endl;
    cout << "---------------------------------" << endl;
}

void Test2()
{
    // += and -= operator testing when size is less than or
    //equal to p.size
    cout << "Test 2: += and -= when size is less "
    << "than or equal to p.size" << endl;
    
    cout << endl;
    
    Polynomial p1;
    p1.changeCoefficient(4.2, 2);
    p1.changeCoefficient(-4.4, 3);
    p1.changeCoefficient(4.4, 4);
    p1.changeCoefficient(4.4, 1);
    cout << "p1 = " << p1 << endl;
    
    Polynomial p2;
    p2.changeCoefficient(5.6, 2);
    p2.changeCoefficient(5.6, 3);
    p2.changeCoefficient(-5.6, 4);
    p2.changeCoefficient(5.6, 1);
    cout << "p2 = " << p2 << endl;
    
    p1 += p2;
    cout << "p1 = " << p1 << endl;
    
    Polynomial p3;
    p3.changeCoefficient(12, 4);
    p3.changeCoefficient(-15, 2);
    p3.changeCoefficient(14, 1);
    cout << "p3 = " << p3 << endl;
    
    p3 -= p2;
    cout << "p3 = " << p3 << endl;
    cout << endl;
    cout << "---------------------------------" << endl;
}

void Test3()
{
    // += and -= operator testing when size is larger
    //than p.size
    cout << "Test 3: += and -= operator testing when "
    << "size is larger than p.size" << endl;
    cout << endl;
    
    Polynomial p1;
    p1.changeCoefficient(9, 2);
    p1.changeCoefficient(4.5, 3);
    p1.changeCoefficient(-3.3, 4);
    p1.changeCoefficient(7, 1);
    cout << "p1 = " << p1 << endl;
    
    Polynomial p2;
    p2.changeCoefficient(6.5, 2);
    p2.changeCoefficient(-3.4, 3);
    cout << "p2 = " << p2 << endl;
    
    p1 += p2;
    
    cout << "p1 = " << p1 << endl;
    
    Polynomial p3;
    p3.changeCoefficient(7, 2);
    p3.changeCoefficient(12, 3);
    cout << "p3 = " << p3 << endl;
    
    p1 -= p3;
    cout << "p1 = " << p1 << endl;
    cout << endl;
    cout << "---------------------------------" << endl;
}

void Test4()
{
    //Tests the == operator
    cout << "Test 4: The == operator" << endl;
    cout << endl;
    Polynomial p1;
    p1.changeCoefficient(9, 2);
    p1.changeCoefficient(4.5, 3);
    p1.changeCoefficient(-3.3, 4);
    p1.changeCoefficient(7, 1);
    cout << "p1 = " << p1 << endl;
    
    Polynomial p2;
    p2.changeCoefficient(9, 2);
    p2.changeCoefficient(4.5, 3);
    p2.changeCoefficient(-3.3, 4);
    p2.changeCoefficient(7, 1);
    cout << "p2 = " << p2 << endl;
    
    if(p1 == p2)
    {
        cout << "-----p1 and p2 are the same" << endl;
    }
    else
    {
        cout << "-----p1 and p2 are not the same" << endl;
    }
    
    Polynomial p3;
    p3.changeCoefficient(-9, 2);
    p3.changeCoefficient(1.4, 3);
    p3.changeCoefficient(3, 4);
    p3.changeCoefficient(-6, 1);
    cout << "p3 = " << p3 << endl;
    
    Polynomial p4;
    p4.changeCoefficient(-9, 2);
    p4.changeCoefficient(1.4, 3);
    p4.changeCoefficient(3, 4);
    p4.changeCoefficient(-6, 1);
    p4.changeCoefficient(-5, 15);
    cout << "p4 = " << p4 << endl;
    
    if(p3 == p4)
    {
        cout << "-----p3 and p4 are the same" << endl;
    }
    else
    {
        cout << "-----p3 and p4 are not the same" << endl;
    }
    
    Polynomial p5;
    p5.changeCoefficient(-9, 2);
    p5.changeCoefficient(1.4, 3);
    p5.changeCoefficient(3, 4);
    p5.changeCoefficient(-6, 1);
    cout << "p5 = " << p5 << endl;
    
    Polynomial p6;
    p6.changeCoefficient(-9, 2);
    p6.changeCoefficient(1, 3);
    p6.changeCoefficient(3, 4);
    p6.changeCoefficient(-6, 1);
    cout << "p6 = " << p6 << endl;
    
    if(p5 == p6)
    {
        cout << "-----p5 and p6 are the same" << endl;
    }
    else
    {
        cout << "-----p5 and p6 are not the same" << endl;
    }
    
    Polynomial p7;
    p7.changeCoefficient(-9, 5);
    p7.changeCoefficient(1, 3);
    p7.changeCoefficient(3, 2);
    p7.changeCoefficient(-6, 1);
    cout << "p7 = " << p7 << endl;
    
    Polynomial p8;
    p8.changeCoefficient(-9, 5);
    p8.changeCoefficient(1, 3);
    p8.changeCoefficient(3, 4);
    p8.changeCoefficient(-6, 1);
    cout << "p8 = " << p8 << endl;
    
    if(p7 == p8)
    {
        cout << "-----p7 and p8 are the same" << endl;
    }
    else
    {
        cout << "-----p7 and p8 are not the same" << endl;
    }
    cout << endl;
    cout << "---------------------------------" << endl;
}

void Test5()
{
    //Testing the != operator
    cout << "Test 5: Testing the !=  " << endl;
    cout << endl;
    
    Polynomial p1;
    p1.changeCoefficient(9, 2);
    p1.changeCoefficient(4.5, 3);
    p1.changeCoefficient(-3.3, 4);
    p1.changeCoefficient(7, 1);
    cout << "p1 = " << p1 << endl;
    
    Polynomial p2;
    p2.changeCoefficient(9, 2);
    p2.changeCoefficient(4.5, 3);
    p2.changeCoefficient(-3.3, 4);
    p2.changeCoefficient(7, 1);
    cout << "p2 = " << p2 << endl;
    
    if(p1 != p2)
    {
        cout << "-----p1 and p2 are not the same" << endl;
    }
    else
    {
        cout << "-----p1 and p2 are the same" << endl;
    }
    
    Polynomial p3;
    p3.changeCoefficient(-9, 2);
    p3.changeCoefficient(1.4, 3);
    p3.changeCoefficient(3, 4);
    p3.changeCoefficient(-6, 1);
    cout << "p3 = " << p3 << endl;
    
    Polynomial p4;
    p4.changeCoefficient(-9, 2);
    p4.changeCoefficient(1.4, 3);
    p4.changeCoefficient(3, 4);
    p4.changeCoefficient(-6, 1);
    p4.changeCoefficient(-5, 15);
    cout << "p4 = " << p4 << endl;
       
    if(p3 != p4)
    {
        cout << "-----p3 and p4 are not the same" << endl;
    }
    else
    {
        cout << "-----p3 and p4 are the same" << endl;
    }
    
    Polynomial p5;
    p5.changeCoefficient(-9, 2);
    p5.changeCoefficient(1.4, 3);
    p5.changeCoefficient(3, 4);
    p5.changeCoefficient(-6, 1);
    cout << "p5 = " << p5 << endl;
    
    Polynomial p6;
    p6.changeCoefficient(-9, 2);
    p6.changeCoefficient(1, 3);
    p6.changeCoefficient(3, 4);
    p6.changeCoefficient(-6, 1);
    cout << "p6 = " << p6 << endl;
       
    if(p5 != p6)
    {
        cout << "-----p5 and p6 not the same" << endl;
    }
    else
    {
        cout << "-----p5 and p6 are the same" << endl;
    }
    
    Polynomial p7;
    p7.changeCoefficient(-9, 5);
    p7.changeCoefficient(1, 3);
    p7.changeCoefficient(3, 2);
    p7.changeCoefficient(-6, 1);
    cout << "p7 = " << p7 << endl;
    
    Polynomial p8;
    p8.changeCoefficient(-9, 5);
    p8.changeCoefficient(1, 3);
    p8.changeCoefficient(3, 4);
    p8.changeCoefficient(-6, 0);
    cout << "p8 = " << p8 << endl;
    
    if(p7 != p8)
    {
        cout << "-----p7 and p8 are not the same" << endl;
    }
    else
    {
        cout << "-----p7 and p8 are the same" << endl;
    }
    cout << endl;
    cout << "---------------------------------" << endl;}

int main()
{
    Test1();
    Test2();
    Test3();
    Test4();
    Test5();
    return 0;
}

