#pragma once
#include "view/geometry.h"
#include <list>
#include <assert.h>
#include <iostream>

/**
 * a class which for creating geometries of charakters for the gui
 */
class MyLetters {
public:
/**
 * creates the geometry of letter 
 * @param c the letter
 * @return the geometry of the letter
 */
    static Geometry get(char c)
    {
        std::vector<Geometry::Line> lines;
        switch(c)
        {
            case('A'):
            {
               lines.push_back(Geometry::Line(12,0,24,11));
               lines.push_back(Geometry::Line(12,0,0,11));
               lines.push_back(Geometry::Line(0,11,0,22));
               lines.push_back(Geometry::Line(23,22,23,11));
               lines.push_back(Geometry::Line(0,22,23,22));
                lines.push_back(Geometry::Line(23,33,23,12));
               lines.push_back(Geometry::Line(0,33,0,12));
               break;
            }
            case('B'):
            {
               lines.push_back(Geometry::Line(0,0,17,0));
               lines.push_back(Geometry::Line(17,0,23,6));
               lines.push_back(Geometry::Line(23,6,24,12));
               lines.push_back(Geometry::Line(24,12,17,17));
               lines.push_back(Geometry::Line(17,17,0,17));
               lines.push_back(Geometry::Line(0,0,0,33));
               lines.push_back(Geometry::Line(17,33,23,28));
               lines.push_back(Geometry::Line(23,28,23,21));
               lines.push_back(Geometry::Line(0,33,17,33));
               lines.push_back(Geometry::Line(23,21,17,17));
               break;
            }
            case('C'):
            {
               lines.push_back(Geometry::Line(0,0,23,0));
               lines.push_back(Geometry::Line(0,0,0,33));
               lines.push_back(Geometry::Line(0,33,23,33));
               break;
            }
            case('D'):
            {
               lines.push_back(Geometry::Line(0,0,13,0));
               lines.push_back(Geometry::Line(13,0,23,11));
               lines.push_back(Geometry::Line(22,11,23,22));
               lines.push_back(Geometry::Line(23,22,13,33));
               lines.push_back(Geometry::Line(13,33,0,33));
               lines.push_back(Geometry::Line(0,33,0,0));
               break;
            }
             case('E'):
            {
               lines.push_back(Geometry::Line(0,0,23,0));
               lines.push_back(Geometry::Line(0,0,0,33));
               lines.push_back(Geometry::Line(0,33,23,33));
               lines.push_back(Geometry::Line(0,16,17,16));
               break;
            }
            case('F'):
            {
               lines.push_back(Geometry::Line(0,0,23,0));
               lines.push_back(Geometry::Line(0,0,0,33));
               lines.push_back(Geometry::Line(0,17,17,17));
               break;
            }
            case('G'):
            {
               lines.push_back(Geometry::Line(0,0,23,0));
               lines.push_back(Geometry::Line(23,0,23,13));
               lines.push_back(Geometry::Line(0,0,0,33));
               lines.push_back(Geometry::Line(0,33,23,33));
               lines.push_back(Geometry::Line(23,33,13,22));
               break;
            }
            case('H'):
            {
               lines.push_back(Geometry::Line(0,0,0,33));
               lines.push_back(Geometry::Line(23,0,23,33));
               lines.push_back(Geometry::Line(0,16,23,16));
               break;
            }
            case('I'):
            {
               lines.push_back(Geometry::Line(17,0,17,33));
               break;
            }
             case('J'):
            {
               lines.push_back(Geometry::Line(0,22,12,33));
               lines.push_back(Geometry::Line(12,33,23,33));
               lines.push_back(Geometry::Line(23,33,23,0));
               break;
            }
            case('K'):
            {
               lines.push_back(Geometry::Line(0,0,0,33));
               lines.push_back(Geometry::Line(0,16,16,0));
               lines.push_back(Geometry::Line(0,16,16,33));
               break;
            }
            case('L'):
            {
               lines.push_back(Geometry::Line(0,0,0,33));
               lines.push_back(Geometry::Line(0,33,23,33));
               break;
            }
            case('M'):
            {
               lines.push_back(Geometry::Line(0,0,12,13));
               lines.push_back(Geometry::Line(12,13,23,0));
               lines.push_back(Geometry::Line(23,0,23,33));
               lines.push_back(Geometry::Line(0,0,0,33));
               break;
            }
             case('N'):
            {
               lines.push_back(Geometry::Line(0,0,23,33));
               lines.push_back(Geometry::Line(23,33,23,0));
               lines.push_back(Geometry::Line(0,0,23,33));
               lines.push_back(Geometry::Line(0,0,0,33));
               break;
            }
 
            case('O'):
            {
               lines.push_back(Geometry::Line(0,0,23,0));
               lines.push_back(Geometry::Line(23,0,23,33));
               lines.push_back(Geometry::Line(23,33,0,33));
               lines.push_back(Geometry::Line(0,33,0,0));
               break;
            }
            case('P'):
            {
               lines.push_back(Geometry::Line(0,0,23,0));
               lines.push_back(Geometry::Line(23,0,23,17));
               lines.push_back(Geometry::Line(23,17,0,17));
               lines.push_back(Geometry::Line(0,0,0,33));
               break;
            }
            case('Q'):
            {
               lines.push_back(Geometry::Line(0,0,23,0));
               lines.push_back(Geometry::Line(23,0,23,22));
               lines.push_back(Geometry::Line(23,22,13,33));
               lines.push_back(Geometry::Line(13,33,0,33));
               lines.push_back(Geometry::Line(0,33,0,0));
               lines.push_back(Geometry::Line(12,22,23,33));
               break;
            }
            case('R'):
            {
               lines.push_back(Geometry::Line(0,0,23,0));
               lines.push_back(Geometry::Line(23,0,23,18));
               lines.push_back(Geometry::Line(23,18,0,18));
               lines.push_back(Geometry::Line(0,18,0,0));
               lines.push_back(Geometry::Line(0,18,0,33));
               lines.push_back(Geometry::Line(8,18,23,33));

               break;
            }
            case('S'):
            {
               lines.push_back(Geometry::Line(0,0,23,0));
               lines.push_back(Geometry::Line(0,0,0,18));
               lines.push_back(Geometry::Line(0,18,23,18));
               lines.push_back(Geometry::Line(23,18,23,33));
               lines.push_back(Geometry::Line(23,33,0,33));
               break;
            }
            case('T'):
            {
               lines.push_back(Geometry::Line(0,0,23,0));
               lines.push_back(Geometry::Line(11,0,11,33));
               break;
            }
            case('U'):
            {
               lines.push_back(Geometry::Line(0,0,0,33));
               lines.push_back(Geometry::Line(0,33,23,33));
               lines.push_back(Geometry::Line(23,33,23,0));
               break;
            }
            case('V'):
            {
               lines.push_back(Geometry::Line(0,0,13,33));
               lines.push_back(Geometry::Line(13,33,23,0));
               break;
            }
            case('W'):
            {
               lines.push_back(Geometry::Line(0,0,0,33));
               lines.push_back(Geometry::Line(0,33,12,21));
               lines.push_back(Geometry::Line(12,21,23,33));
               lines.push_back(Geometry::Line(23,33,23,0));
               break;
            }
            case('X'):
            {
               lines.push_back(Geometry::Line(0,0,23,33));
               lines.push_back(Geometry::Line(0,33,23,0));
               break;
            }    
            case('Y'):
            {
               lines.push_back(Geometry::Line(0,0,11,11));
               lines.push_back(Geometry::Line(11,11,23,0));
               lines.push_back(Geometry::Line(11,11,11,33));
               break;
            }
            case('Z'):
            {
               lines.push_back(Geometry::Line(0,0,23,0));
               lines.push_back(Geometry::Line(23,0,0,33));
               lines.push_back(Geometry::Line(0,33,23,33));
               break;
            }
            case(' '):
            {
              break;  
            }
            case('\0'):
            {
                break;
            }
            case('\n'):
            {
                break;
            }
            default:
                std::cout<<"Render unkown char: "<<(int)c<<std::endl;
                assert(false);
        };
        
        return lines;

    }
    
};
