#include "letter_line.h"
#include <assert.h>
#include <iostream>

 LetterLine LetterLine::create(Vector2f startPos, float spaceBetweenLetters, const Geometry& maxSizedLetterInLine, LetterLine::Align align)
{
    auto box = getBoundingBoxOfLetter(maxSizedLetterInLine);
    return create(startPos,spaceBetweenLetters,box,box.x,align);
}

LetterLine::LetterLine() : startPos(0,0),sizeOfLetter(0,0)
{
}


LetterLine LetterLine::create(Vector2f startPos, float spaceBetweenLetters,Vector2f sizeOfLetter, float spaceSize, LetterLine::Align align)
{
    LetterLine l;
    l.startPos = startPos;
    l.spaceBetweenLetters = spaceBetweenLetters;
    l.spaceSize = spaceSize;
    l.align = align;
    l.sizeOfLetter = sizeOfLetter;
    return l;
}

void LetterLine::update(const std::vector<Geometry>& letters)
{
    this->letters = letters;
    // Gesamt Länge
    float lenOfLineInPx = 0;
    for(std::size_t n = 0; n < letters.size();n++)
    {
        const Geometry& g = letters[n];
        lenOfLineInPx += isSpace(g) ?  spaceSize : sizeOfLetter.x;
        if(n != letters.size() - 1)
        {
            lenOfLineInPx += spaceBetweenLetters;
        }
    }
    // Gesamt Höhe
    float summedLineHigh = sizeOfLetter.y;
    if(align == Align::Center)
    {
        startPos.x -= lenOfLineInPx / 2.0;
        align = Align::Left;
    }
    // Align right
    if(align == Align::Right)
    {
        startPos.x -= lenOfLineInPx;
        align = Align::Left;
    }
    
    // Align left
    if(align == Align::Left)
    {
      Vector2f posOfNextLetter = startPos + sizeOfLetter / 2.0;
      // Positon the letters from left to right
       for(std::size_t n = 0; n < this->letters.size();n++)
       {
           Geometry& g = this->letters[n];
           if(isSpace(g))
           {
               posOfNextLetter.x += this->spaceSize;
           }
           else 
           {
               Vector2f currentLetterSize = getBoundingBoxOfLetter(g);
               Vector2f diffSize = sizeOfLetter - currentLetterSize;
              // assert(diffSize.x >= 0 && diffSize.y >= 0); 
               diffSize /= 2.0f;
               // Add diffSize if the size of the letters is different
               g.setPosition(posOfNextLetter + diffSize);
               posOfNextLetter.x += this->sizeOfLetter.x;
           }
            if(n != letters.size() - 1)
            {
                posOfNextLetter.x += spaceBetweenLetters;
            }
       }
    }
}

const std::vector<Geometry> & LetterLine::getGeometry() const
{
    return letters;
}


Vector2f LetterLine::getBoundingBoxOfLetter(const Geometry& letters)
{
        assert(letters.size() != 0);
        auto boundingBox = letters.getBoundingBox();
        Vector2f minPoint =  std::get<0>(boundingBox);
        Vector2f maxPoint =  std::get<1>(boundingBox);
        Vector2f box = maxPoint - minPoint;
        return  box;
}


