// -------------- polynomials.h -------------------
// Sung Ho Park
// 1/8/2020
// 1/8/2020
// -------------------------------------------------
// Purpose - This is the polynomial.h file and creates the
// methods for the cpp file to implement.
// --------------------------------------------------
// Nothing changed.
// --------------------------------------------------

#ifndef POLYNOMIAL_H
#define POLYNOMIAL_H
#include <iostream>
#include <string>
using namespace std;

class Polynomial
{
    // Overloaded <<: prints Cn * x^n + Cn-1 * X^n-1 + ... C1 * X + C0
    friend ostream& operator<<(ostream &output, const Polynomial& p);
    // Constructor: the default is a 0-degree polynomial with 0.0 coefficient

public:
    //Member Functions
    
    Polynomial();
    Polynomial(const Polynomial& p);
    ~Polynomial();
    
    // returns the degree of a polynomial
    int degree() const;
    // returns the coefficient of the x^power term.
    double coefficient(const int power) const;
    
    // replaces the coefficient of the x^power term
    bool changeCoefficient(const double newCoefficient, const int power);
    
    // Arithmetic operators
    Polynomial operator+(const Polynomial& p) const;
    Polynomial operator-(const Polynomial& p) const;
    
    // Boolean comparison operators
    bool operator==(const Polynomial& p) const;
    bool operator!=(const Polynomial& p) const;
    
    // Assignment operators
    Polynomial& operator=(const Polynomial& p);
    Polynomial& operator+=(const Polynomial& p);
    Polynomial& operator-=(const Polynomial& p);

private:
    // a term on the sparce polynomial
    struct Term
    {
        // the coefficient of each term
        double coeff;
        
        // the degree of each term
        int power;
        
        // a pointer to the previous higher term
        Term *prev;
        
         // a pointer to the next lower term
        Term *next;
    };
    
    // # terms in the sparce polynomial
    int size;
    
    // a pointer to the doubly-linked circular list of sparce polynomial
    Term *head;
    
    bool insert(Term* pos, const double newCoefficient, const int power);
    bool remove(Term* pos);
    
};
#endif
