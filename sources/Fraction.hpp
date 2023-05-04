/**
 * Fraction.hpp file, represents a fraction of two integers. Overload the following operators for this class:
 * The + operator to add two fractions and return their sum as another fraction in reduced form.
 * The - operator to subtract two fractions and return their difference as another fraction in reduced form.
 * The * operator to multiply two fractions and return their product as another fraction in reduced form.
 * The / operator to divide two fractions and return their quotient as another fraction in reduced form.
 * The == operator to compare two fractions for equality and return true or false.
 * All comparison operations (>,<,>=,<=)
 * The ++ and -- operator that adds (or subtracts) 1 to the fraction. implement both pre and post fix.
 * The << operator to print a fraction to an output stream in the format “numerator/denominator”.
 * The >> operator to read a fraction from an input stream by taking two integers as input.
 * All operators should work on both sides on fractions and floats type variables. 
 * on a float var you need use up to 3 digits beyond the decimal point for accuracy.
 * 
 * 
 * @author Shachar Ketz 208968362
 * @since 05.23
*/


#ifndef FRACTION_HPP
#define FRACTION_HPP

#include <iostream>
#include <fstream>
#include <sstream>
#include <stdexcept>
#include <limits>
using namespace std;

/*CONST*/

const int MAX = std::numeric_limits<int>::max();
const int MIN = std::numeric_limits<int>::min();


namespace ariel{

    /**
     * @class Fraction- the arithmetic Fraction structure.
     * Fracture have two fields member:
     * numerator and denominator
     * and he can do arithmetic operations ( + - * / += -= *= /=) and booleans comparisons ( < <= == != > >= )
     * also we can get Fractions from the IO system by giving two integers
     * the output of Fraction member is two integers separated by '/' char
     * for example; numerator=1, denominator=2 the fraction output is- 1/2.
     * a fraction will always be in his most limit representation.
     * 
     * @throws
     * overflow_error- when the arithmetic solution is bigger the MAX_INTEGER or smaller then the MIN_INTEGER.
     * runtime_error- if the solution is illegal for Fraction, for example: denominator=0.
    */
    class Fraction {

    private:
        int _numerator;
        int _denominator;

        /*functions*/

        
        /**
         * reduce this fraction by the greatest common divisor
        */
        void _reduce();


    public:
        /*CONSTRUCTORS*/

        /**
         * default constructor build fraction with:
         * numerator=1 denominator=1
        */
        Fraction();

        /**
         * @param numerator
         * @param denominator
         * @throw overflow_error if denominator is 0.
        */
        Fraction(int numerator, int denominator);

        /**
         * @param num decimal number, 
         * the constructor will build fraction in his most limit representation.
        */
        Fraction(float num);

        /**
         * copy constructor
         * @param other Fraction member, 
         * the constructor will build the fraction in his most limit representation.
        */        
        Fraction(const Fraction& other);//copy

        /**
         * move constructor
         * @param other Fraction member, 
         * the constructor will build the fraction in his most limit representation.
        */  
        Fraction(Fraction&&) noexcept; 


        /*DESTRUCTOR*/
        ~Fraction();

    /*~~~~~~~~~~~~~~~~~~~~~
        GETTERS & SETTERS:
      ~~~~~~~~~~~~~~~~~~~~*/

        int getNumerator() const;
        int getDenominator() const;

        void setNumerator( int numerator);
        void setDenominator( int denominator);

    /*~~~~~~~~~~~~~~~~~~~
        OPERATORS:
      ~~~~~~~~~~~~~~~~~~*/

        /*DESIGNATIONS*/

        Fraction& operator= (const Fraction& other);
        Fraction& operator=(Fraction&&) noexcept;//move assignment

        /*DESIGNATIONS & ARITHMETICS*/

        Fraction& operator+= (const Fraction& other);
        Fraction& operator-= (const Fraction& other);
        Fraction& operator/= (const Fraction& other);
        Fraction& operator/= (int wholeNum);
        
        Fraction& operator*= (const Fraction& other);
        Fraction& operator*= (const int& other);
        
        /*INCREASE & DECREASE*/

        Fraction& operator-- ();
        Fraction operator-- (int);
        Fraction& operator++ ();
        Fraction operator++ (int);

        /*ARITHMETICS*/

        friend Fraction operator+ (const Fraction& fracL, const Fraction& fracR);

        friend Fraction operator+ (const Fraction& fraction ,const float& right_d);
        friend Fraction operator+ (const float& left_float,const Fraction& fraction);

        friend Fraction operator- (const Fraction& fracL, const Fraction& fracR);

        friend Fraction operator- (const Fraction& fraction ,const float& right_float);
        friend Fraction operator- (const float& left_float,const Fraction& fraction);

        friend Fraction operator/ (const Fraction& fracL, const Fraction& fracR);

        friend Fraction operator/ (const Fraction& fraction ,const float& right_d);
        friend Fraction operator/ (const float& left_float,const Fraction& fraction);


        friend Fraction operator* (const Fraction& fracL, const Fraction& fracR);

        friend Fraction operator* (const Fraction& fraction ,const float& right_d);
        friend Fraction operator* (const float& left_float,const Fraction& fraction);


        /*BOOLEAN comparisons*/
        friend bool operator==(const Fraction& fracL, const Fraction& fracR);
        friend bool operator!=(const Fraction& fracL, const Fraction& fracR);
        friend bool operator<(const Fraction& fracL, const Fraction& fracR);
        friend bool operator<=(const Fraction& fracL, const Fraction& fracR);
        friend bool operator>(const Fraction& fracL, const Fraction& fracR);
        friend bool operator>=(const Fraction& fracL, const Fraction& fracR);

        /*compare with float*/

        friend bool operator==(const float& left_float, const Fraction& fracR);
        friend bool operator!=(const float& left_float, const Fraction& fracR);
        friend bool operator<(const float& left_float, const Fraction& fracR);
        friend bool operator<=(const float& left_float, const Fraction& fracR);
        friend bool operator>(const float& left_float, const Fraction& fracR);
        friend bool operator>=(const float& left_float, const Fraction& fracR);

        friend bool operator==(const Fraction& fracL, const float& right_float);
        friend bool operator!=(const Fraction& fracL, const float& right_float);
        friend bool operator<(const Fraction& fracL, const float& right_float);
        friend bool operator<=(const Fraction& fracL, const float& right_float);
        friend bool operator>(const Fraction& fracL, const float& right_float);
        friend bool operator>=(const Fraction& fracL, const float& right_float);

        /*IO*/

        friend std::ostream& operator<< (std::ostream& output, const Fraction& fraction);
        friend std::istream& operator>> (std::istream& input , Fraction& fraction);
        
    };


    /*FUNCTION*/

    /**
     * check if there is arithmetic overflow in multiplication number1 with number2
     * @param number1
     * @param number2
     * @throw overflow_error
    */
    void overFlowMultipChech(int number1, int number2);

    /**
     * check if there is arithmetic overflow in adding operation number1 with number2
     * @param number1
     * @param number2
     * @throw overflow_error
    */
    void overFlowAddCheck(int number1, int number2);

    /**
     * check if there is arithmetic overflow in subtracting operation number1 with number2
     * @param number1
     * @param number2
     * @throw overflow_error
    */
    void overFlowSubCheck(int num1, int num2);

    /**
     * @param num a decimal number
     * @return int represent the whole part of the decimal number.
    */
    int intPart(float num);

    /**
     * @param num a decimal number
     * @return int represent the three digit after the point value.
    */
    int fracPart(float num);

}
#endif