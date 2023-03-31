#pragma once
#include <vector>
#include "view/geometry.h"

/**
 * A single line of text for rendering in the gui
 */
class LetterLine
{
public:
    /**
 * the alignment of the line
 */
    enum class Align {Left,Right,Center};
    /**
   *creates a text line
   * @param startPos the Position of the line
   * @param spaceBetweenLetters the pixel space between the letters
   * @param sizeOfLetter the boundingbox of a letter
   * @param spaceSize the size of a blank
   * @param align the alignment of the text
    * @return the created text line
   */
    static LetterLine create(Vector2f startPos, float spaceBetweenLetters,Vector2f sizeOfLetter,float spaceSize,Align align);
        /**
   *creates a text line
   * @param startPos the Position of the line
   * @param spaceBetweenLetters the pixel space between the letters
   * @param maxSizedLetterInLine takes the size of the geometry as a reference size for every letter
   * @param spaceSize the size of a blank
   * @param align the alignment of the text
    * @return the created text line
   */
    static LetterLine create(Vector2f startPos, float spaceBetweenLetters,const Geometry& maxSizedLetterInLine, Align align);
    /**
    * Creates an empty letter line
    */
    LetterLine();
    /**
   * updates the Position of the letters
   * @param letters which should be updated
   */
    void update(const std::vector<Geometry>& letters);
    /**
   * Returns the Geometry of the lines as a vector of letter geometries
   * @return the geoemtry of the line
   */
    const std::vector<Geometry>& getGeometry() const;
private:
    /**
    * The alignment of the line
    */
    Align align;
    /**
    * The position of the line
    */
    Vector2f startPos; 
    /**
    * the space between every letter
    */
    float spaceBetweenLetters;
    /**
    * the size in px of every space
    */
    float spaceSize;
    /**
    * the size of the bounding box from every letter
    */
    Vector2f sizeOfLetter;
    /**
    * all letters in a vector
    */
    std::vector<Geometry> letters;  // All letter should have the same width and len
    /**
    * returns the bounding box of a letter
    * @return the boduningbox saved in 2d vector
    */
    static Vector2f getBoundingBoxOfLetter(const Geometry& letters);
    /**
    * checks if a letter is a space
    */
    inline bool isSpace(const Geometry& g) const {return g.size() == 0;}
};
