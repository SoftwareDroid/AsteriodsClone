#include "asteriods_hub.h"
#include "view/objects/spaceship_geometry.h"
#include "share/math/helper.h"
#include "my_font/my_numbers.h"
#include "my_font/my_letters.h"
#include <iostream>


void AsteriodsHub::setRemainingLifes(int number)
{
    Geometry spaceshipGeometry = SpaceShipGeometry::create(false);
    spaceshipGeometry.setRotation(degToRad(-90));
    auto pos = Vector2f(screenSize.x * 0.135,screenSize.y * 0.06);
    LetterLine line = LetterLine::create( pos,0,spaceshipGeometry,LetterLine::Align::Left);
    std::vector<Geometry> letters;
    for(int i = 0; i < number;i++)
    {
        letters.push_back(spaceshipGeometry);
    }
    line.update(letters);
    this->lines[LineKey::RemainingLifes] = line;
    
}

void AsteriodsHub::destroyStartscreenGUI()
{
     this->lines.erase(LineKey::ONE_COIN_ONE_PLAY);
      this->lines.erase(LineKey::PUSH_START);
}


void AsteriodsHub::showGameOverMessage()
{
    Geometry fullSizeLetter = MyLetters::get('O');
    std::string text = "GAME OVER";
    LetterLine line = LetterLine::create(Vector2f(screenSize.x * 0.5,screenSize.y * (1 - 0.73)) ,9,fullSizeLetter,LetterLine::Align::Center);

    std::vector<Geometry> letters;
    for(char c : text)
    {
        Geometry g = MyLetters::get(c);
        letters.push_back(g);  
    }
    line.update(letters);
     this->lines[LineKey::GAME_OVER_MESSAGE] = line;
}

void AsteriodsHub::askForPlayerNameMessage()
{
        this->lines.erase(LineKey::GAME_OVER_MESSAGE);
        Geometry fullSizeLetter = MyNumbers::get(0);
        int spaceBetweenLines = 45;
        LetterLine line1 = LetterLine::create(Vector2f(50,screenSize.y * 0.25) ,10,fullSizeLetter,LetterLine::Align::Left);
        LetterLine line2 = LetterLine::create(Vector2f(50,screenSize.y * 0.25 + spaceBetweenLines) ,10,fullSizeLetter,LetterLine::Align::Left);
        LetterLine line3 = LetterLine::create(Vector2f(50,screenSize.y * 0.25 + spaceBetweenLines * 2) ,10,fullSizeLetter,LetterLine::Align::Left);
        LetterLine line4 = LetterLine::create(Vector2f(50,screenSize.y * 0.25 + spaceBetweenLines * 3) ,10,fullSizeLetter,LetterLine::Align::Left);
        
        {
            std::vector<Geometry> letters;
            for(char c : "YOUR SCORE IS ONE OF THE TEN BEST")
            {
                letters.push_back(MyLetters::get(c));  
            }
            line1.update(letters);
        }
        {
            std::vector<Geometry> letters;
            for(char c : "PLEASE ENTER YOUR INITIALS")
            {
                letters.push_back(MyLetters::get(c));  
            }
            line2.update(letters);
        }
        {
            std::vector<Geometry> letters;
            for(char c : "PUSH ROTATE TO SELECT LETTER")
            {
                letters.push_back(MyLetters::get(c));  
            }
            line3.update(letters);
        }
        {
            std::vector<Geometry> letters;
            for(char c : "PUSH HYPERSPACE WHEN LETTER IS CORRECT")
            {
                letters.push_back(MyLetters::get(c));  
            }
            line4.update(letters);
        }
        this->lines[LineKey::ASK_FOR_PLAYER_NAME1] = line1;
        this->lines[LineKey::ASK_FOR_PLAYER_NAME2] = line2;
        this->lines[LineKey::ASK_FOR_PLAYER_NAME3] = line3;
        this->lines[LineKey::ASK_FOR_PLAYER_NAME4] = line4;
}



void AsteriodsHub::setInsertOneCoinMessage()
{
     Geometry fullSizeLetter = MyNumbers::get(0);
     LetterLine line1 = LetterLine::create(Vector2f(screenSize.x * 0.5,screenSize.y * 0.62) ,10,fullSizeLetter,LetterLine::Align::Center);
     std::vector<Geometry> letters;
     for(char c : "I COIN I PLAY")
     {
         if (MyNumbers::isDigit(c))
         {
              letters.push_back(MyNumbers::get( *MyNumbers::numberToDigits(c).begin()));  
         }
         else 
         {
            letters.push_back(MyLetters::get(c));  
         }
    }
    line1.update(letters);
    this->lines[LineKey::ONE_COIN_ONE_PLAY] = line1;
}

void AsteriodsHub::setPushStartMessage()
{
    Geometry fullSizeLetter = MyNumbers::get(0);
     LetterLine line1 = LetterLine::create(Vector2f(screenSize.x * 0.5,screenSize.y * 0.21) ,10,fullSizeLetter,LetterLine::Align::Center);
     std::vector<Geometry> letters;
     for(char c : "PUSH START")
     {
         if (MyNumbers::isDigit(c))
         {
              letters.push_back(MyNumbers::get( *MyNumbers::numberToDigits(c).begin()));  
         }
         else 
         {
            letters.push_back(MyLetters::get(c));  
         }
    }
    line1.update(letters);
    std::cout<<"Create Push start message"<<std::endl;
    this->lines[LineKey::PUSH_START] = line1;
}


void AsteriodsHub::setBestHighScore(int number)
{
    Geometry fullSizeLetter = MyNumbers::get(0);
    fullSizeLetter.setScale(Vector2f(0.5,0.5));
    LetterLine line = LetterLine::create(Vector2f(screenSize.x * 0.5,screenSize.y * 0.01) ,4,fullSizeLetter,LetterLine::Align::Center);

    std::vector<Geometry> letters;
    if(number == 0)
    {
        letters.push_back(fullSizeLetter);
        letters.push_back(fullSizeLetter);
    }   
    else 
    {
        for(int digit : MyNumbers:: numberToDigits(number))
        {
           Geometry g = MyNumbers::get(digit);
           g.setScale(Vector2f(0.5,0.5));
           letters.push_back(g);  
        }
    }
     line.update(letters);
    this->lines[LineKey::BEST_HIGH_SCORE] = line;
}


void AsteriodsHub::setPoints(int points)
{

    Geometry fullSizeLetter = MyNumbers::get(8);
    LetterLine line = LetterLine::create(Vector2f(screenSize.x * 0.20,5),9,fullSizeLetter,LetterLine::Align::Right);
    std::vector<Geometry> letters;
    if(points == 0)
    {
        letters.push_back(MyNumbers::get(0));
        letters.push_back(MyNumbers::get(0));
    }
    else 
    {
        for(int digit : MyNumbers:: numberToDigits(points))
        {
          letters.push_back(MyNumbers::get(digit));  
        }
    }
     line.update(letters);
    this->lines[LineKey::Points] = line;
}




