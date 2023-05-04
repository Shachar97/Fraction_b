#include <stdio.h>
#include <iostream>
#include <exception>
#include <stdexcept>
#include <fstream>
#include <sstream>
#include <stdexcept>
#include <math.h>
#include <limits>
#include <algorithm>

using namespace std;

#include "Fraction.hpp"

using namespace ariel;

/*CONSTRUCTORS*/

Fraction::Fraction():_numerator(1),_denominator(1){}//default

Fraction::Fraction(const int numerator, const int denominator):_numerator(numerator), _denominator(denominator){
    if(this->_denominator==0){
        throw std::invalid_argument("Arithmetic exception: zero in denominator\n");
    }
    this->_reduce();
}

Fraction::Fraction(float num){
    
    if(num==0){
        this->_numerator=0;
        this->_denominator=1;
        return;
    }

    /*round to the three digit after the decimal dot*/
    num*=1000;
    this->_numerator=(int)num;
    this->_denominator=1000;
    this->_reduce();

}

Fraction::Fraction(const Fraction& other):_numerator(other._numerator),_denominator(other._denominator){
    this->_reduce();
}

Fraction::Fraction(Fraction&& other) noexcept : _numerator(other._numerator),_denominator(other._denominator){}


/*DESTRUCTOR*/
Fraction::~Fraction(){}

/*~~~~~~~~~~~~~~~~~~~~~
    GETTERS & SETTERS:
  ~~~~~~~~~~~~~~~~~~~~*/
      
int Fraction::getNumerator() const{
    return this->_numerator;
}

int Fraction::getDenominator() const{
    return this->_denominator;
}

void Fraction::setNumerator( int numerator){
    this->_numerator=numerator;
}

void Fraction::setDenominator( int denominator){
    this->_denominator=denominator;
}

/*~~~~~~~~~~~~~~~~~~~
    OPERATORS:
  ~~~~~~~~~~~~~~~~~~*/

/*DESIGNATIONS*/

Fraction& Fraction::operator= (const Fraction& other){
    this->_numerator=other._numerator;
    this->_denominator=other._denominator;
    this->_reduce();
    return *this;
}


Fraction& Fraction::operator=(Fraction&& other) noexcept{
    if(this != &other){
        this->_numerator=other._numerator;
        this->_denominator=other._denominator;
    }
    return *this;
}

/*DESIGNATIONS & ARITHMETICS*/

Fraction& Fraction::operator+= (const Fraction& other){ 
    
    /*nothing to add*/
    if(other._numerator==0){
        this->_reduce();
        return *this;
    }

    /*CHECK FOR OVERFLOWS*/
    overFlowMultipChech(this->_denominator,other._numerator);
    overFlowMultipChech(this->_numerator,other._denominator);
    overFlowAddCheck(this->_denominator*other._numerator,this->_numerator*other._denominator);
    overFlowMultipChech(this->_denominator,other._denominator);

    /*find the gcd between the denominators*/
    int gcd = __gcd(this->_denominator,other._denominator);
    if(gcd<0){
        gcd *= -1;
    }

    /*multiply each of fraction with the the non-common divisor alternately*/
    int divisor1 = this->_denominator/gcd;
    int divisor2 = other._denominator/gcd;
    
    this->_denominator *= divisor2;
    this->_numerator *= divisor2;

    /*after the fractions have common denominator, do the adding*/
    this->_numerator += (other._numerator*divisor1);

    return *this;
}

Fraction& Fraction::operator-= (const Fraction& other){

    /*nothig to add*/
    if(other._numerator==0){
        this->_reduce();
        return *this;
    }

    /*CHECK FOR OVERFLOWS*/
    overFlowMultipChech(this->_denominator,other._numerator);
    overFlowMultipChech(this->_numerator,other._denominator);
    overFlowSubCheck(this->_numerator*other._denominator,this->_denominator*other._numerator);
    overFlowMultipChech(this->_denominator,other._denominator);


    /*find the gcd between the denominators*/
    int gcd = __gcd(this->_denominator,other._denominator);
    if(gcd<0){
        gcd*=-1;
    }

    /*multiply each of fraction with the the non-common divisor alternately*/
    int divisor1 = this->_denominator/gcd;
    int divisor2 = other._denominator/gcd;
    
    this->_denominator *= divisor2;
    this->_numerator *= divisor2;
    
    /*after the fractions have common denominator, do the subtraction*/
    this->_numerator -= (other._numerator*divisor1);
    
    return *this;    
}


Fraction& Fraction::operator/= (const Fraction& other){
    
    /*runtime error*/
    if(other._numerator==0){
        throw std::runtime_error("Arithmetic exception: zero in denominator\n");
    }
    
    /*CHECK FOR OVERFLOWS*/
    overFlowMultipChech(this->_numerator,other._denominator);
    overFlowMultipChech(this->_denominator,other._numerator);

    /*the arithmetic calculate*/
    this->_numerator *= other._denominator;
    this->_denominator *= other._numerator;

    this->_reduce();

    return *this;
}

Fraction&  Fraction::operator/= (int wholeNum){
    
    /*runtime error*/
    if(wholeNum==0){
        throw std::runtime_error("Arithmetic exception: zero in denominator\n");
    }  

    /*find the gcd between the denominator and the number*/
    int gcd = __gcd(this->_numerator,wholeNum);
    if(gcd<0){
        gcd *= -1;
    }
    /*reduce*/
    this->_numerator /= gcd;
    this->_denominator *= (wholeNum/gcd);
    

    return *this;
}

Fraction& Fraction::operator*= (const Fraction& other){

    /*fraction detail*/
    int numerL = this->_numerator;
    int denomL = this->_denominator;
    int numerR = other._numerator;
    int denomR = other._denominator;

    
    /*CHECK FOR OVERFLOWS*/
    overFlowMultipChech( numerL, numerR);
    overFlowMultipChech( denomR, denomL);

    /*reducing numerators & denominators*/
    int gcd = __gcd(numerR,denomL);
    if(gcd<0){
        gcd*=-1;
    }

    numerR/=gcd;
    denomL/=gcd;

    gcd = __gcd(numerL,denomR);
    if(gcd<0){
        gcd *= -1;
    }
    numerL /=gcd;
    denomR /=gcd;

    /*arithmetic calculation*/
    this->_numerator = numerL*numerR;
    this->_denominator = denomL*denomR;

    this->_reduce();
    return *this;
}


Fraction& Fraction::operator*= (const int& wholeNum){
    /*set Fraction to zero*/
    if(wholeNum==0){
        this->_numerator=0;
        this->_denominator=1;
        return *this;
    }

    /*reduce denominator and whole-num*/
    int gcd = __gcd(this->_denominator,wholeNum);
    if(gcd<0){
        gcd *= -1;
    }
    this->_denominator /=gcd;

    /*arithmetic calculate*/
    this->_numerator *= (wholeNum/gcd);

    this->_reduce();

    return *this;
}


/*INCREASE & DECREASE*/  

Fraction& Fraction::operator-- (){

    /*arithmetic calculate: fraction-1 */
    this->_numerator -= this->_denominator;

    this->_reduce();

    return *this;
}

Fraction Fraction::operator-- (int){

    /*save fraction before decreasing*/
    Fraction oldFraction(*this);

    /*arithmetic calculate: fraction-1 */
    this->_numerator -= this->_denominator;

    this->_reduce();

    /*return fraction before decreasing*/
    return oldFraction;
}


Fraction& Fraction::operator++ (){

    /*arithmetic calculate: fraction+1 */
    this->_numerator+=this->_denominator;

    this->_reduce();

    return *this;
}
Fraction Fraction::operator++ (int){
    
    /*save fraction before increasing*/
    Fraction oldFraction(*this);

    /*arithmetic calculate: fraction+1 */
    this->_numerator+=this->_denominator;

    this->_reduce();

    /*return fraction before increasing*/
    return oldFraction;
}

/*ARITHMETICS*/                 
Fraction ariel::operator+(const Fraction &fracL, const Fraction &fracR){
    
    /*use operator += (Fraction)*/

    Fraction myFraction = fracL;
    myFraction += fracR;

    myFraction._reduce();

    return myFraction;
}

Fraction ariel::operator+ (const Fraction& fraction ,const float& right_float){
    
    /*use constructor of float*/
    Fraction myFraction(right_float);
    

    /*use operator += (Fraction)*/
    myFraction += fraction;

    /*for StudentTest2 calculation: 
    1. casting fraction to decimal number
    2. use constructor of float (inside float we using the round calculation)
    */
    float myFloat = (float)(myFraction._numerator);
    myFloat /=(float)(myFraction._denominator);

    Fraction newFraction(myFloat);

    return newFraction;
}


Fraction ariel::operator+ (const float& left_float,const Fraction& fraction){
    return fraction+left_float;
}

Fraction ariel::operator- (const Fraction& fracL, const Fraction& fracR){
    
    Fraction myFraction(fracL);

    myFraction-=fracR;
    
    return myFraction;
}

Fraction ariel::operator- (const Fraction& fraction ,const float& right_float){
    
    /*use constructor of float*/
    Fraction rightFraction(right_float);


    Fraction leftFraction(fraction);
    leftFraction-=rightFraction;

    /*for StudentTest2 calculation: 
    1. casting fraction to decimal number
    2. use constructor of float (inside float we using the round calculation)
    */
    float myFloat = (float)(leftFraction._numerator);
    myFloat /=(float)(leftFraction._denominator);

    Fraction newFraction(myFloat);

    return newFraction;
}

Fraction ariel::operator- (const float& left_float,const Fraction& fraction){
    
    Fraction leftFraction(left_float);
    leftFraction -= fraction;

    /*for StudentTest2 calculation: 
    1. casting fraction to decimal number
    2. use constructor of float (inside float we using the round calculation)
    */
    float myFloat = (float)(leftFraction._numerator);
    myFloat /=(float)(leftFraction._denominator);
    Fraction newFraction(myFloat);

    return newFraction;
}

Fraction ariel::operator/ (const Fraction& fracL, const Fraction& fracR){
    
    Fraction myFraction(fracL);
    myFraction /= fracR;
    
    return myFraction;
}

Fraction ariel::operator/ (const Fraction& fraction ,const float& right_float){
    Fraction myFraction(right_float);

    return fraction/myFraction;
}

Fraction ariel::operator/ (const float& left_float,const Fraction& fraction){
    Fraction myFraction(left_float);

    return myFraction/fraction;

}

Fraction ariel::operator* (const Fraction& fracL, const Fraction& fracR){
    Fraction myFraction(fracL);
    myFraction*=fracR;

    return myFraction;
}

Fraction ariel::operator* (const Fraction& fraction ,const float& right_float){
    Fraction myFraction(right_float);

    return fraction*myFraction;
}

Fraction ariel::operator* (const float& left_float,const Fraction& fraction){
    return fraction*left_float;
}

/*BOOLEAN*/
bool ariel::operator==(const Fraction& fracL, const Fraction& fracR){

    /*for StudentTest2 calculation: 
    1. casting fractions to decimal number
    2. round to the three digit after the decimal dot.
    3. compare as floats
    */

    float leftFloat = (float)(fracL._numerator);
    leftFloat /=(float)(fracL._denominator);

    //rounding:
    leftFloat *=1000;
    leftFloat = (int) leftFloat;
    leftFloat/=1000.0f;

    float rightFloat = (float)(fracR._numerator);
    rightFloat /=(float)(fracR._denominator);

    //rounding:
    rightFloat *=1000;
    rightFloat = (int) rightFloat;
    rightFloat/=1000.0f;
    
    return leftFloat == rightFloat;
}

bool ariel::operator!=(const Fraction& fracL, const Fraction& fracR){
    bool isDiff = !(fracL==fracR);
    return isDiff;
}


bool ariel::operator<(const Fraction& fracL, const Fraction& fracR){

    Fraction tempL(fracL);
    Fraction tempR(fracR);
    
    bool isLess = true;

    /*equal*/
    if(tempL==tempR){
        return !isLess;
    }

    /*left is 0*/
    if(tempL._numerator==0){
        if(tempR._numerator>0){
            return !isLess;
        }
        return isLess;
    }

    /*right is 0*/
    if(tempR._numerator == 0){
        if(tempL._numerator<0){
            return isLess;
        }
        return !isLess;
    }

    /*find common denominator*/
    int gcd = __gcd(tempL._denominator,tempR._denominator);
    if(gcd<0){
        gcd *= -1;
    }
    int divideL = tempL._denominator/gcd;
    int divideR = tempR._denominator/gcd;

    tempL._numerator *= divideR;
    

    tempR._numerator *= divideL;
    
    /*compare numerators*/
    isLess = (tempL._numerator<tempR._numerator);

    return isLess;
}

bool ariel::operator<=(const Fraction& fracL, const Fraction& fracR){
    bool ans = ((fracL==fracR)|| (fracL<fracR));
    return ans;
}

bool ariel::operator>(const Fraction& fracL, const Fraction& fracR){
    bool ans = (!(fracL<fracR) && (fracL!=fracR));
    return ans;
}

bool ariel::operator>=(const Fraction& fracL, const Fraction& fracR){
    bool ans = ((fracL>fracR) || (fracL==fracR));
    return ans;
}

/*compare with float*/        
bool ariel::operator==(const float& left_float, const Fraction& fracR){

    /*casting to float and compare after rounding*/
    float namer = (float)fracR._numerator;
    float denom = (float)fracR._denominator;
    float floatRight = namer/denom;

    floatRight *= 1000;
    floatRight = (int)floatRight;
    floatRight /= 1000.0f;

    return left_float == floatRight;
    
}

bool ariel::operator!=(const float& left_float, const Fraction& fracR){
    return !(left_float==fracR);
}

bool ariel::operator<(const float& left_float, const Fraction& fracR){
    Fraction myFraction(left_float);
    return (myFraction<fracR);
}

bool ariel::operator<=(const float& left_float, const Fraction& fracR){
    Fraction myFraction(left_float);
    return (myFraction<=fracR);
}

bool ariel::operator>(const float& left_float, const Fraction& fracR){
    Fraction myFraction(left_float);
    return (myFraction>fracR);
}

bool ariel::operator>=(const float& left_float, const Fraction& fracR){
    Fraction myFraction(left_float);
    return (myFraction>=fracR);
}

bool ariel::operator==(const Fraction& fracL, const float& right_float){
    return (right_float==fracL);
}

bool ariel::operator!=(const Fraction& fracL, const float& right_float){
    return !(fracL==right_float);
}

bool ariel::operator<(const Fraction& fracL, const float& right_float){
    Fraction myFraction(right_float);
    return (fracL<myFraction);
}

bool ariel::operator<=(const Fraction& fracL, const float& right_float){
    Fraction myFraction(right_float);
    return (fracL<=myFraction);
}

bool ariel::operator>(const Fraction& fracL, const float& right_float){
    Fraction myFraction(right_float);
    return (fracL>myFraction);
}

bool ariel::operator>=(const Fraction& fracL, const float& right_float){
    Fraction myFraction(right_float);
    return (fracL>=myFraction);
}

/*IO*/ 
std::ostream& ariel::operator<< (std::ostream& output, const Fraction& fraction){
    if(fraction._numerator==0){
        return output << 0;
    }
    return output << fraction._numerator << "/" << fraction._denominator;
}

std::istream& ariel::operator>>(std::istream& input, Fraction& fraction) { /*helped by the cures compelx git 04-operator-overloading/1-arithmetic-operators/Complex.cpp*/
    int numer = 0, denom = 0;
    char separator;

    if (input.fail()) {
        return input;
    }

    // remember place for rewinding
    std::ios::pos_type startPosition = input.tellg();
    
    if ( (!(input >> numer)) || (!(input >> denom)) ){
        // rewind on error
        
        auto errorState = input.rdstate(); // remember error state
        input.clear(); // clear error so seekg will work
        input.seekg(startPosition); // rewind
        input.clear(errorState); // set back the error flag
        throw std::runtime_error("\n");
    } else {
        if (denom == 0) {
            throw std::runtime_error("Arithmetic exception: zero in denominator\n");
        } else {
            if(denom<0){
                numer*=-1;
                denom *=-1;
            }
            fraction.setNumerator(numer);
            fraction.setDenominator(denom);
        }
    }
    fraction._reduce();
    return input;
}



/*Functions*/
int ariel::intPart(float num){
    return (int)num;
}

int ariel::fracPart(float num){
    
    int whole = (int)num;
    float fraction = num - whole;

    float digit = fraction*(1000); 
    
    return (int)digit;
}

void Fraction::_reduce(){

    if(this->_numerator==0){
        this->_denominator=1;
        return;
    }

    if((this->_denominator<0)){
    
        this->_numerator *= -1;
        this->_denominator *= -1;
    }

    int numer= this->_numerator;
    int denom= this->_denominator;
    
    int gcd = std::__gcd(numer,denom);
    if (gcd < 0){
        gcd *= -1;
    }
    
    this->_numerator = (numer/gcd);
    this->_denominator = (denom/gcd);
}

void ariel::overFlowMultipChech(int number1, int number2){
    if((number2 > 0 && number1 > MAX / number2) || (number2 < 0 && number1 < MAX / number2) ){
        throw std::overflow_error("over flow number");
    }
}

void ariel::overFlowAddCheck(int number1, int number2){
    if (number1 >= 0 && number2 >= 0 && (number1 > MAX - number2)) {
        throw std::overflow_error(" over flow number");
    }
 
    if (number1 < 0 && number2 < 0 && (number1 < MIN - number2)) {
        throw std::overflow_error(" over flow number");
    }
}

void ariel::overFlowSubCheck(int number1, int number2){
    if ((number2 < 0 && number1 > MAX + number2) || (number2 > 0 && number1 < MIN + number2)){
        throw std::overflow_error(" over flow number");
    }
}
