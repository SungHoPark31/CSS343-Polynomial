// -------------- polynomials.cpp -------------------
// Sung Ho Park
// 1/8/2020
// 1/18/2020
// -------------------------------------------------
// Purpose - This is the polynomial class. This will take care of
// adding terms, removing terms, creating the polynomial,
// deleting the polynomial and simple arithmetic for the
// polynomials.
// --------------------------------------------------
// Had to use <cmath> to get absolute value for negative numbers
// when implementing the friend function.
// --------------------------------------------------

#include "polynomial.h"
#include <iostream>
#include <cmath>    //This is used to get the absolute value of a
                    //negative number in the friend funciton.

using namespace std;

/*-------------------------Polynomaial-------------------------------
  Description
  Polynomial: When construct a Polynomial object without parameter, you
  should initialize the size as zero, and should construct a dummy header.
  Note that your polynomial is doubly-linked circular list.

  Preconditions: No input validation
  Postconditions: Creates a new object of the class, Polynomial, and
  creates a doubly-linked circular list with an dummy header.
 --------------------------------------------------------------------*/
Polynomial::Polynomial()
{
    //Initialize the size as zero.
    size = 0;
    
    //Construct a dummy header.
    head = new Term();
    head->coeff = 0;
    head->power = 0;
    head->prev = head;
    head->next = head;
}
//End of Default Constructor

/*------------------------~Polynomaial---------------------------
 Description
 Polynomial: Destroys every Term in the Polynomial along with
 the polynomial.

 Preconditions: No Parameters
 Postconditions: Destroys the Polynomial
----------------------------------------------------------------*/
Polynomial::~Polynomial()
{
    //Keep a temporary term to keep track
    Term* deleteCurr = head->next;
    Term* current = deleteCurr;

    //While the current is not the head...
    while (current != head)
    {
        //Go to the next
        current = current->next;
        
        //delete the current
        remove(deleteCurr);
        
        //Decrement size.
        size--;
        
        //Delete the pointers to the next.
        //Make the position that you're deleting to
        //the next.
        deleteCurr = current;
    }
    //Delete the head.
    delete head;
}
//End of ~Polynomial

/*------------------------Copy Constructor-------------------------------
  Description
  Polynomial: Takes care of a deep copy of the original link
  representation.

  Preconditions: The parameter that is being passed in is an object that
  exists.
  Postconditions: Copys all the information of the parameter object to
  this object.
 ----------------------------------------------------------------------*/
Polynomial::Polynomial(const Polynomial& p)
{
    //Initialize the size as zero.
    size = 0;
    
    //Construct a dummy header.
    head = new Term();
    head->coeff = 0;
    head->power = 0;
    head->prev = head;
    head->next = head;
    
    //Use the operator=
    *this = p;
}
//End of Copy Constructor

/*-------------------------degree-------------------------------
 Description
 degree: Returns the power of a Term.

 Preconditions: No parameters needed.
 
 Postconditions: It will return an integer that is a power of a term.
-------------------------------------------------------------------*/
int Polynomial::degree() const
{
    return head->next->power;
}
//End of degree

/*-------------------------coefficient-------------------------------
 Description
 coefficient: Returns the coefficient of a Term from the x power.

 Preconditions: No parameters needed.
 
 Postconditions: It will return a coefficient of a term
----------------------------------------------------------------------*/
double Polynomial::coefficient(const int power) const
{
    //Create a current because the original head is a dummy head. So,
    //start at head->next.
    Term *current = head->next;
    while(current != head)
    {
        if(current->power == power)
        {
            return current->coeff;
        }
        current = current->next;
    }
    //return -1 if not found.
    return -1;
}
//End of coefficient


/*-------------------------changeCoefficient-------------------------------
 Description
 changeCoefficient: Looks inside the circular doubly linked list and checks to
 see if there is a power that is the same as the power being passed in. If
 there is a power the same as the one being passed in, then this will change
 the coefficient in that power. If there is no power equivalent to the one
 passed in, create a new one and place it appropriately.

 Preconditions: The parameters being passed in are any real numbers. For the
 coefficient, negative numbers are acceptable.
 
 Postconditions: Looks for the power that is being passed in and on that power,
 the coefficient changes.
------------------------------------------------------------------------*/
bool Polynomial::changeCoefficient(const double newCoefficient, const int power)
{
    //Create a current to keep track of the dummyhead.
    Term *current = head->next;

    //Iterate through the list.
    for(int i = 0; i < size; i++)
    {
        //We start at head->next because head is a dummy head.
        //Term *nextNode = current->next;
    
        //If the nextNode's power is the same as the power, then
        if(current->power == power)
        {
            //If the coefficient is 0, then remove it.
            if(newCoefficient == 0)
            {
                remove(current);
                size--;
                return true;
            }
            else
            {
                //Other wise, change the coefficient
                current->coeff = newCoefficient;
                return true;
            }
        }
        //If the power being passed in is greater than the nextNode power,
        else if(current->power < power)
        {
            
            //Add it to the node previous to nextNode.
            insert(current, newCoefficient, power);
            size++;
            return true;
        }
        else
        {
            //If the power is less than the next power, keep going through
            //the list.
            current = current->next;
        }
    }
    
    //When it gets to the end of the list. Add it before the dummy head.
    insert(current, newCoefficient, power);
    size++;
    return true;
}
//End of changeCoefficient

/*-----------------------insert------------------------------
 Description
 insert: This will insert a node just before the existing position.

 Preconditions: The parameters being passed in are any real numbers. For the
 coefficient, negative numbers are acceptable. Term pos must be an existing
 object and not null.
 
 Postconditions: Inserts a new node with newCoefficient and power before the
 position
---------------------------------------------------------------*/
bool Polynomial::insert(Term* pos, const double newCoefficient, const int power)
{
    //Create a new node that'll be inserted
    Term *newNode = new Term;
    
    //Put the coefficient and power inside of this new node.
    newNode->coeff = newCoefficient;
    newNode->power = power;
    
    //Create a previous because you want to insert a term just before the
    //existing term.
    Term *previous = pos->prev;
    Term *nextNodeAfterPrevious = previous->next;
    
    //Connect it to the previous node and the next one to make it circular.
    previous->next = newNode;
    nextNodeAfterPrevious->prev = newNode;
    newNode->prev = previous;
    newNode->next = nextNodeAfterPrevious;
    
    return true;
}
//End of insert

/*----------------------remove------------------------------
 Description
 remove: Removes a node from the list.

 Preconditions: Term pos is existing and not NULL.
 
 Postconditions: Removes the desired node from the list.
------------------------------------------------------------*/
bool Polynomial::remove(Term* pos)
{
    //If head is null, then there is nothing to get rid of.
    //return false.
    if(head->next == head)
    {
        return false;
    }
    else
    {
        //Keep track of the previous and the next.
        Term *previous = pos->prev;
        Term *nextNode = pos->next;
        
        //Delete the position's node
        delete pos;
        
        //reconnect the list without the deleted position.
        previous->next = nextNode;
        nextNode->prev = previous;
    }
    //If something goes wrong, then it'll return false.
    return false;
}
//End of remove

/*--------------------operator+------------------------------
 Description
 operator+: Add all existing coefficients corresponding to
 their powers.

 Preconditions: Polynomial p is existing and not NULL.
 
 Postconditions: Adds every coefficient that corresponds to their power.
------------------------------------------------------------*/
Polynomial Polynomial::operator+(const Polynomial& p) const
{
    //Make a new Polynomial because that is what you will be returning.
    Polynomial tempo;
    
    //If the size is greater than p.size...
    if(size > p.size)
    {
        //Have a bool, we'll get to it later.
        bool inserted;
        
        //Have this variable for debugging putposes.
        int otherSize = p.size;
            
        //As you go through this list...
        //Create temporary variables to keep track.
        Term* current = head->next;
        for(int i = 0; i < size; i++)
        {
            //Insert is false.
            inserted = false;
            
            //As you go through the other list,
            //Have a temp head for the inner.
            Term* otherCurrent = p.head->next;
            for(int j = 0; j < otherSize; j++)
            {
                
                //If the powers are the same...
                if(current->power == otherCurrent->power)
                {
                    //Add the coefficient and insert it to temp
                    double sum = current->coeff + otherCurrent->coeff;
                    tempo.changeCoefficient(sum, current->power);
                    
                    //Insert is true
                    inserted = true;
                }
                
                //Go through p.list
                otherCurrent = otherCurrent->next;
            }
            //If you haven't inserted (or haven't found the same power...)
            if(inserted == false)
            {
                //Just add that value to Coefficient
                tempo.changeCoefficient(current->coeff, current->power);
            }
            //Go on through this list.
            current = current->next;
        }
    }
    //Otherwise, do the same operation for if the p.size is greater.
    else
    {
        bool inserted;
        int otherSize = p.size;
        
        Term* otherCurrent = p.head->next;
        for(int i = 0; i < otherSize; i++)
        {
            inserted = false;
            
            Term* current = head->next;

            for(int j = 0; j < size; j++)
            {
                if(current->power == otherCurrent->power)
                {
                    double sum = current->coeff + otherCurrent->coeff;
                    tempo.changeCoefficient(sum, current->power);
                    //cout << sum << endl;
                    inserted = true;
                }
                current = current->next;
            }
            if(inserted == false)
            {
                tempo.changeCoefficient(otherCurrent->coeff, otherCurrent->power);
            }
            otherCurrent = otherCurrent->next;
        }
    }
    //Return tempo.
    return tempo;
    
}
//End of operator+

/*-----------------minus operator-------------------------------
 Description
 operator-: Subtracts all existing coefficients corresponding to
 their powers.

 Preconditions: Polynomial p is existing and not NULL.
 
 Postconditions: Subtracts every coefficient that corresponds to
 their power.
------------------------------------------------------------*/
Polynomial Polynomial::operator-(const Polynomial& p) const
{
    //Make a new Polynomial because that is what you will be returning.
    Polynomial tempo;
    
    //If the size is greater than p.size...
    if(size > p.size)
    {
        //Have a bool, we'll get to it later.
        bool inserted;
        
        //Have this variable for debugging putposes.
        int otherSize = p.size;
            
        //As you go through this list...
        Term* current = head->next;
        for(int i = 0; i < size; i++)
        {
            //Insert is false.
            inserted = false;
            Term* otherCurrent = p.head->next;
            
            //As you go through the other list,
            for(int j = 0; j < otherSize; j++)
            {
                //If the powers are the same...
                if(current->power == otherCurrent->power)
                {
                    //Subtract the coefficient and insert it to temp
                    double sub = current->coeff - otherCurrent->coeff;
                    tempo.changeCoefficient(sub, current->power);
                    
                    //Insert is true
                    inserted = true;
                }
                //Go through p.list
                otherCurrent = otherCurrent->next;
            }
            //If you haven't inserted (or haven't found the same power...)
            if(inserted == false)
            {
                //Just add that value to Coefficient
                tempo.changeCoefficient(current->coeff, current->power);
                //cout << current->coeff << endl;
            }
            //Go on through this list.
            current = current->next;
        }
    }
    //Otherwise, do the same operation for if the p.size is greater.
    else
    {
        bool inserted;
        int otherSize = p.size;
        
        Term* otherCurrent = p.head->next;
        for(int i = 0; i < otherSize; i++)
        {
            inserted = false;
            Term* current = head->next;
            for(int j = 0; j < size; j++)
            {
                if(current->power == otherCurrent->power)
                {
                    double sub = current->coeff - otherCurrent->coeff;
                    tempo.changeCoefficient(sub, current->power);
                    inserted = true;
                }
                current = current->next;
            }
            if(inserted == false)
            {
                tempo.changeCoefficient(otherCurrent->coeff, otherCurrent->power);
            }
            otherCurrent = otherCurrent->next;
        }
    }
    
    //Return tempo.
    return tempo;
}
//End of operator-

/*------------------------operator==------------------------------
 Description
 operator==: Checks if there are two lists that are equal to one another.

 Preconditions: The parameter being passed in is an existing object.
 
 Postconditions: Return true if both of the lists are equal, false otherwise.
------------------------------------------------------------*/
bool Polynomial::operator==(const Polynomial& p) const
{
    //If the sizes are not the same, then they are not the same.
    if(size != p.size)
    {
        return false;
    }
    else
    {
        //This will tell if the lists are the same
        bool same;
        bool samePower;
        
        //Keep track of the current head
        Term *current = head->next;
        
        //Go through the current list
        for(int i = 0; i < size; i++)
        {
            //Keep track of the list that is being passed in.
            Term *otherCurrent = p.head->next;
            samePower = false;
            
            //Go through the second list
            for(int j = 0; j < p.size; j++)
            {
                //Start with a false value
                same = false;
                
                //Look for the power and if the same power is found,
                if(current->power == otherCurrent->power)
                {
                    samePower = true;
                    //Check if the coefficients are the same.
                    if(current->coeff == otherCurrent->coeff)
                    {
                        //If they are the same, set same to true. That
                        //way, we'll look at the entire list before
                        //determining if it is true.
                        same = true;
                    }
                    else
                    {
                        //If that same power has a different coefficient,
                        //return false.
                        return false;
                    }
                }
               
                //If the same power cannot be found, then go through
                //p list.
                otherCurrent = otherCurrent->next;
            }
            //If you went through the entire Polynomial that is passed in
            //and there is no corresponding powers, then return false.
            if(samePower == false)
            {
                return false;
            }
            //Look next into this list. 
            current = current->next;
        }
        //If you get through the end of the list and it is
        //the same, then return true.
        return true;
    }
}
//End of operator==

/*------------------------!=operator------------------------------
 Description
 operator==: Checks if there are two lists that are not equal to one another.

 Preconditions: The parameter being passed in is an existing object.
 
 Postconditions: Return true if both of the lists are equal, false otherwise.
------------------------------------------------------------*/
bool Polynomial::operator!=(const Polynomial& p) const
{
        //If the sizes are not the same, then they are not the same.
    if(size != p.size)
    {
        return true;
    }
    else
    {
        //This will tell if the lists are not the same
        bool same;
        bool samePower;
        
        //Keep track of the current head
        Term *current = head->next;
        
        //Go through the current list
        for(int i = 0; i < size; i++)
        {
            //Keep track of the list that is being passed in.
            Term *otherCurrent = p.head->next;
            samePower = true;
            
            //Go through the second list
            for(int j = 0; j < p.size; j++)
            {
                //Start with a true value
                same = true;
                
                //Look for the power and if the same power is found,
                if(current->power == otherCurrent->power)
                {
                    samePower = false;
                    //Check if the coefficients are the same.
                    if(current->coeff == otherCurrent->coeff)
                    {
                        //If they are the same, set same to true. That
                        //way, we'll look at the entire list before
                        //determining if it is true.
                        same = false;
                    }
                    else
                    {
                        return true;
                    }
                }
               
                //If the same power cannot be found, then go through
                //p list.
                otherCurrent = otherCurrent->next;
            }
            //If you went through the entire Polynomial that is passed in
            //and there is no corresponding powers, then return false.
            if(samePower == true)
            {
                return true;
            }
            //Look next into this list.
            current = current->next;
        }
        //If you get through the end of the list and it is
        //the same, then return true.
        return false;
    }
}
//End of operator!=

/*---------------------operator=------------------------------
 Description
 operator=: Does a deep copy of the p copy and copies each Term
 to this class.

 Preconditions: The parameter being passed in is an existing object.
 
 Postconditions: Copies the every Term in p over to this object.
------------------------------------------------------------*/
Polynomial& Polynomial::operator=(const Polynomial& p)
{
    //If both of them are the same, do nothing.
    if(p.head == head)
    {
        return *this;
    }
    else
    {
        //Delete this before copying over.
        Term* deleteNode = head->next;
        Term* current = deleteNode;
       
        //If the next is not the head...
        if(current != head)
        {
            //Then delete everything.
            while (current != head)
            {
                //Delete and go next.
                current = current->next;
                
                //Once it is deleted, decrement size.
                remove(deleteNode);
                size--;
                deleteNode = current;
            }
        }
    
        //Keep track of the p.head->next. Not the dummy head.
        Term* otherCurrent = p.head->next;
        //Each time you go through the p list, then change the
        //Coefficient.
        for(int i = 0; i < p.size; i++)
        {
            
            //Don't need to worry about the size because the
            //changeCoefficient takes care of that.
            changeCoefficient(otherCurrent->coeff, otherCurrent->power);

            //Go through the p list.
            otherCurrent = otherCurrent->next;
        }
    }
    return *this;
}
//End of = operator

/*---------------------operator+=------------------------------
 Description
 operator+=: Add all existing coefficients corresponding to
 their powers.

 Preconditions: Polynomial p is existing and not NULL.
 
 Postconditions: Updates each term in this Polynomial by adding every
 coefficient that corresponds to their power.
------------------------------------------------------------*/
Polynomial& Polynomial::operator+=(const Polynomial& p)
{
    //If the size is greater than p.size...
    if(size > p.size)
    {
        //Have a bool, we'll get to it later.
        bool inserted;
        
        //Have this variable for debugging putposes.
        int otherSize = p.size;
            
        //As you go through this list...
        //Create temporary variables to keep track.
        Term* current = head->next;
        for(int i = 0; i < size; i++)
        {
            //Insert is false.
            inserted = false;
            
            //As you go through the other list,
            //Have a temp head for the inner.
            Term* otherCurrent = p.head->next;
            for(int j = 0; j < otherSize; j++)
            {
                //cout << current->power << " " << otherCurrent->power << endl;
                //If the powers are the same...
                if(current->power == otherCurrent->power)
                {
                    //Add the coefficient and insert it to temp
                    double sum = current->coeff + otherCurrent->coeff;
                    changeCoefficient(sum, current->power);
                    
                    //Insert is true
                    inserted = true;
                }
                //If inserted is still false, add it to the tempo
                if(inserted == false)
                {
                    changeCoefficient(otherCurrent->coeff, otherCurrent->power);
                }
                //Go through p.list
                otherCurrent = otherCurrent->next;
            }
            //If you haven't inserted (or haven't found the same power...)
            if(inserted == false)
            {
                //Just add that value to Coefficient
                changeCoefficient(current->coeff, current->power);
            }
            //Go on through this list.
            current = current->next;
        }
    }
    //Otherwise, do the same operation for if the p.size is greater.
    else
    {
        bool inserted;
        int otherSize = p.size;
        
        Term* otherCurrent = p.head->next;
        for(int i = 0; i < otherSize; i++)
        {
            inserted = false;
            
            Term* current = head->next;
            for(int j = 0; j < size; j++)
            {
                if(current->power == otherCurrent->power)
                {
                    double sum = current->coeff + otherCurrent->coeff;
                    changeCoefficient(sum, current->power);
                    //cout << sum << endl;
                    inserted = true;
                }
                current = current->next;
            }
            if(inserted == false)
            {
                changeCoefficient(otherCurrent->coeff, otherCurrent->power);
            }
            otherCurrent = otherCurrent->next;
        }
    }
    return *this;
}
//End of += operator

/*---------------------operator-=------------------------------
 Description
 operator-=: Subtracting all existing coefficients corresponding to
 their powers.

 Preconditions: Polynomial p is existing and not NULL.
 
 Postconditions: Updates each term in this Polynomial by subtracting every
 oefficient that corresponds to their power.
------------------------------------------------------------*/
Polynomial& Polynomial::operator-=(const Polynomial& p)
{
    //If the size is greater than p.size...
    if(size > p.size)
    {
        //Create temporary variables to keep track.
        Term* current = head->next;
        
        //Have a bool, we'll get to it later.
        bool inserted;
        
        //Have this variable for debugging putposes.
        int otherSize = p.size;
            
        //As you go through this list...
        for(int i = 0; i < size; i++)
        {
            //Insert is false.
            inserted = false;
            
            //Keep track of the other list that is being compared.
            Term* otherCurrent = p.head->next;
            //As you go through the other list,
            for(int j = 0; j < otherSize; j++)
            {
                //If the powers are the same...
                if(current->power == otherCurrent->power)
                {
                    //Subtract the coefficient and insert it to this
                    double sub = current->coeff - otherCurrent->coeff;
                    changeCoefficient(sub, current->power);
                    
                    //Insert is true
                    inserted = true;
                }
                //Go through p.list
                otherCurrent = otherCurrent->next;
            }
            //If you haven't inserted (or haven't found the same power...)
            if(inserted == false)
            {
                //Just add that value to this list.
                changeCoefficient(current->coeff, current->power);
            }
            //Go on through this list.
            current = current->next;
        }
    }
    //Otherwise, do the same operation for if the p.size is greater.
    else
    {
        //Create temporary variables to keep track.
        bool inserted;
        int otherSize = p.size;
        
        //Create temporary variables to keep track.
        Term* otherCurrent = p.head->next;
        for(int i = 0; i < otherSize; i++)
        {
            //Have a temp for the inner next.
            Term* current = head->next;
            
            inserted = false;
            for(int j = 0; j < size; j++)
            {
                if(otherCurrent->power == current->power)
                {
                    double sub = current->coeff - otherCurrent->coeff;
                    changeCoefficient(sub, current->power);
                    inserted = true;
                }
                current = current->next;
            }
            if(inserted == false)
            {
                    changeCoefficient(otherCurrent->coeff, otherCurrent->power);
            }
            otherCurrent = otherCurrent->next;
        }
    }
    return *this;
}
//End of -= operator

/*---------------------operator<<------------------------------
 Description
 operator<<: Like a toString method, this method will print out the output
 as the user formats it.

 Preconditions: The parameter being passed in is an existing object and not
 NULL.
 
 Postconditions: Returns a formatted output.
------------------------------------------------------------*/
ostream& operator<<(ostream &output, const Polynomial& p)
{
    //Make a temporary current because head->next is the start of
    //the list.
    Polynomial::Term *current = p.head->next;

    //This is the first coefficient. This will show the negative if
    //they is one.
    //cout << p.size << endl;
    if((current->coeff > 1 && current->power > 1) ||
       (current->coeff < 0 && current->power > 1))
    {
        output << current->coeff << "x^" << current->power;
    }
    else if(current->coeff == 1)
    {
        output << "";
    }
    else if(current->power == 1)
    {
        output << "x";
    }
    Polynomial::Term *nextNode = current->next;

    //Go through the list.
    for(int i = 1; i < p.size; i++)
    {
        //If you have a positive coefficient after the first term.
        if(nextNode->coeff > 1)
        {
            output << " + " << nextNode->coeff;
        }
        else if(nextNode->coeff == 1)
        {
            //Do nothing and look at the power.
        }
        else if(nextNode->coeff < 0)
        {
            //Otherwise, for a negative coefficient, find the
            //absolute value and put the - sign in the beginning.
            output << " - " << abs(nextNode->coeff);
        }

        //If the power is greater than 1, then print out the exponent.
        if(nextNode->power > 1)
        {
            //If coefficient is 0, then power doesn't matter.
            if(nextNode->coeff == 1)
            {
                output << " + x^" << nextNode->power;
            }
            else
            {
               output << "x^" << nextNode->power;
            }
        }
        //If the power is 1...
        else if(nextNode->power == 1)
        {
            //If the coefficient is 1,
            if(nextNode->coeff == 1)
            {
                //just print out x
                output << " + x ";
            }
            else
            {
                //Otherwise, just add an x at the end because, it is already
                //"multiplied" by the coefficient. And we made it so that the
                //negative coefficients don't effect the power.
                output << "x";
            }
        }
        //If the power is zero...
        else if(nextNode->power == 0)
        {
            //Print out nothing because this will indicate if
            //it is a constant.
            output << "";
        }
        else
        {
            //If a negative power is encountered, then it would flip
            //(reciprocal).
            output << " 1/(" << nextNode->coeff << "x^"
                                << nextNode->power << ")";
        }
        //Go on to the next term on the list.
        nextNode = nextNode->next;
    }

    //The reason why a zero coefficient case is not here is because the remove
    //method deletes the node that has a zero coefficient.

    //Return the output.
    return output;
}
//End of friend ostream function.
