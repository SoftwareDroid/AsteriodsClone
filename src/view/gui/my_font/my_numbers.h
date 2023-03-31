#pragma once
#include "view/geometry.h"
#include <list>
#include <ctype.h>

/**
 * A number as letter
 */
class MyNumbers
{
public:
    /**
 * converts integer to its digits 
 * @param number the number which should be converted
 * @return a list of the digits
 */
    static std::list<int> numberToDigits(int number)
    {
      std::list<int> ret;  
      while(number > 0)
      {
          int digit = number % 10;
          ret.push_front(digit);
          number /= 10;
      }
      return ret;
    }
    /**
 * checks if a char is a digit
 * @param c the checked charakter
 * @return the result
 */
    static bool isDigit(char c) {
      return isdigit(c);   
    }
    /**
 * Creates the geometry for a digit
 * @param diggit the diggit
 * @return a geometry of the digit
 */
    static Geometry get(int diggit)
    {
       std::vector<Geometry::Line> lines;
        Geometry::Line B(0,0,23,0);
        Geometry::Line A(23,17,23,0);
        Geometry::Line C(0,0,0,18);
        Geometry::Line D(23,17,0,17);
        Geometry::Line E(23,17,23,34);
        Geometry::Line F(0,34,23,34);
        Geometry::Line G(0,34,0,17);
        switch(diggit)
        {
            case(0):
            {
              lines.push_back(A);
              lines.push_back(E);
              lines.push_back(B);
              lines.push_back(C);
              lines.push_back(G);
              lines.push_back(F);
              break;
            }
            case(1):
            {
               lines.push_back(A);
              lines.push_back(E);  
              break;  
            }
            case(2):
            {
               lines.push_back(B);
               lines.push_back(A);
               lines.push_back(D);
               lines.push_back(G);
               lines.push_back(F);
              break;  
            }
            case(3):
            {
              lines.push_back(A);
              lines.push_back(E);
              lines.push_back(D);
              lines.push_back(B);
              lines.push_back(F);
              break;  
            }
             case(4):
            {
              lines.push_back(C);
              lines.push_back(A);
              lines.push_back(D);
              lines.push_back(E);
              break;  
            }             
             case(5):
            {
              lines.push_back(B);
              lines.push_back(C);
              lines.push_back(D);
              lines.push_back(E);
              lines.push_back(F);
              break;  
            }
            case(6):
            {
              lines.push_back(C);
              lines.push_back(D);
              lines.push_back(D);
              lines.push_back(G);
              lines.push_back(E);
              lines.push_back(F);
              break;  
            }
            case(7):
            {
              lines.push_back(B);
              lines.push_back(A);
              lines.push_back(E);
              break;  
            }
            case(8):
            {
              lines.push_back(A);
              lines.push_back(B);
              lines.push_back(C);
              lines.push_back(D);
              lines.push_back(E);
              lines.push_back(F);
              lines.push_back(G);
              break;  
            }
            case(9):
            {
              lines.push_back(A);
              lines.push_back(B);
              lines.push_back(C);
              lines.push_back(D);
              lines.push_back(E);
              break;  
            }
            
        }
        return lines;
    }
};
