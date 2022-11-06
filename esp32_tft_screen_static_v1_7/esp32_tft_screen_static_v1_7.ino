// ESP WROOM 32
// 
/*
 * This is a small project to try to replicate the analogue static that used to appear on tvs before digital
 * Using an ST7735 screen with ESP WROOM32 which Arduino IDE says is a dev kit in the board manager
 * 
 * NOTE : the height and the width are the wrong way round ! By default the longer edge of the screen is the Y axis but I rotate it during setup
 * So be careful
 * 
 * If you want to have a different image then I used : https://www.mischianti.org/images-to-byte-array-online-converter-cpp-arduino/
 * Resize the image you'd like to use to match to your screen size before uploading and save as a bitmap ( think I choose 16-bit ) in the image editor of your choice
 * On the webpage, try different background colours until preview turns colour - transparent probably
 * Draw mode = horizontal 2 bytes per pixel
 * Replace the array info in this code with the one the website suggested
 * 
 */

#include <SPI.h>
#include <TFT_eSPI.h>
#include "backgrounds.h"
class screenStatic {
  public:
  //constructor
    screenStatic (byte staticStartPosition, byte screenHeight, byte screenWidth, byte staticStripHeight, byte staticPixelSize, byte pixelThreshold, uint16_t *background){
      this -> staticStartPosition = staticStartPosition;
      this -> screenHeight = screenHeight;
      this -> screenWidth = screenWidth;
      this -> staticStripHeight = staticStripHeight;
      this -> staticPixelSize = staticPixelSize;
      this -> pixelThreshold = pixelThreshold;
      this -> background = background;
      backgroundColour = TFT_BLACK;
    } //end constructor
   // getters
   byte getStaticStartPosition(byte staticStartPosition){return staticStartPosition;}
   byte getStaticStripHeight(byte staticStripHeight){return staticStripHeight;}
   byte getStaticPixelSize(byte staticPixelSize){return staticPixelSize;}
   byte getPixelThreshold(byte pixelThreshold){return pixelThreshold;}
   uint16_t getBackground(uint16_t *background){return *background;}
   uint16_t getBackground2(uint16_t *background){return *background2;}
   // end getters
   // setters
   void setStaticStartPosition(byte staticStartPosition){this -> staticStartPosition = staticStartPosition;}
   void setStaticStripHeight(byte staticStripHeight){this -> staticStripHeight = staticStripHeight;}
   void setStaticPixelSize(byte staticPixelSize){this -> staticPixelSize = staticPixelSize;}
   void setPixelThreshold(byte pixelThreshold){this -> pixelThreshold = pixelThreshold;}
   void setBackground(uint16_t *background){this -> background = background;}
   void setBackground2(uint16_t *background){this -> background2 = background;}
   //end setters
   void start(){
    myScreen.init();
    myScreen.setRotation(1); //this turns screen 90 degrees so width actually = height and vice versa
    myScreen.fillScreen(backgroundColour);
    delay(50);
    backgroundImageRefreshColour();
  }
   void backgroundImageRefresh(){
    /* This redraws a 1 bit per pixel bitmap array
     *  I'm not using it but leaving it in here
     *  uncomment the line and make sure your array is uint8_t or char type
     *  You might also have to comment out the colour version of this function
     */
//      myScreen.drawXBitmap(0 ,0, background, screenHeight, screenWidth, TFT_WHITE);    
  }
  void backgroundImageRefreshColour(){
    /* draw the colour 2-byte per pixel bitmap information from the array
     *  Pixel by pixel
     *  It's slow but not as bad as you'd think
     */
      uint32_t arrayCounter = 0;
//      unsigned long startTime = millis(); //used for timing checks
      for (byte j = 0; j < screenWidth; j ++){
        for (byte i = 0; i < screenHeight; i ++){
          myScreen.drawPixel(i, j, background[arrayCounter]);
          arrayCounter++;
        } //end screenHeight loop
      } //end screenWidth loop
/*      unsigned long endTime = millis() - startTime; //used for timing checks
      Serial.print("Full background refresh Loop time : ");
      Serial.println(endTime);*/ 
  } //end backgroundimagerefreshcolour
  
  void backgroundLoadGradual(byte increaseBy){
    /*
     * Load image by random
     * Higher reduceLoadBy means less image displayed
     * 
     */
//     unsigned long startTime = millis(); //used for timing checks
    for (uint16_t i = 0; i < (screenWidth * screenHeight) * increaseBy ; i++){
      /*
       * Create random x and y values then draw a pixel on the screen
       * 
       */
      byte randomY = random(0, screenWidth);
      byte randomX = random(0, screenHeight);
      uint16_t tempColour = (randomY * screenHeight) + randomX;// find correct colour in background
      myScreen.drawPixel(randomX, randomY, background[tempColour]);
    }
/*    unsigned long endTime = millis() - startTime; //used for timing checks
      Serial.print("Gradual background refresh Loop time : ");
      Serial.println(endTime);*/
  }//end backgroundload partial
  
  void displayStaticBar(){
  /* this draws a chunk of static across the screen of the height of the user's prefernce
   *  
   *  it also redraws a few lines (but full width of screen) of the background image after static bar passes
   *  as redrawing the whole image after each chunk of static is too slow
   *  
   *  No redrawing of background = full static screen
   *  
   *  It never redraws the very last line though !
   */
    backgroundArrayCounter = screenHeight * staticStartPosition;
    uint16_t tempColour[4];
    tempColour[0] = TFT_BLACK;
    tempColour[1] = TFT_WHITE;
    tempColour[2] = TFT_BLACK;
    tempColour[3] = TFT_LIGHTGREY;
    for (byte y = staticStartPosition; y < (staticStartPosition + staticStripHeight); y +=staticPixelSize){
      for (byte j = 0; j < screenHeight; j += staticPixelSize){
        byte pixel = random(0, 4);
        myScreen.fillRect(j, y, staticPixelSize, staticPixelSize, tempColour[pixel]);
        }
      }
      //below redraws the background after the static bar has been passed
      for (uint8_t i = 0; i < staticPixelSize; i++){
        for (byte j = 0; j < screenHeight; j++){
          myScreen.drawPixel(j, staticStartPosition - i, background[backgroundArrayCounter + j]);
        }
      }
      staticStartPosition += staticPixelSize;
      if (staticStartPosition == screenWidth) {
        setStaticStartPosition(0);
      }
  } //end displaystaticbar

  
  void fullScreenStatic(long interval, byte repeatValue){
    /* 
     *  This will show a full screen of static after the time interval specified
     *  A repeat value is for how many times the screen will refresh with static
     *  It looks better repeated a few times
     */
    unsigned long currentMillis = millis();
    if (currentMillis - previousMillis >= interval){
      previousMillis = currentMillis;
      for (byte repeat; repeat < repeatValue; repeat ++){
        fullScreenStatic();
      }
    }
  } //end full screen static with interval and repeat
  
  void fullScreenStatic(byte repeatValue){
    /*
     * This will cycle through a full screen of static as many times as the repeat value 
     */
      for (byte repeat = 0; repeat < repeatValue; repeat ++){
        fullScreenStatic();
      }
  } //end fullscreen static with repeat value
  
  void pixelateScreen(byte increaseBy){
    /**
     * Load a pixelated version of image
     * A higher reduceLoadBy means less of image drawn
     * 
     */
    for (uint16_t i = 0; i < (screenWidth * screenHeight) * increaseBy ; i++){
      /*
       * Create random x and y values then draw a larger square on the screen
       * Colour picked from background image to try to match what's already on screen
       */
      byte randomY = random(0, screenWidth);
      byte randomX = random(0, screenHeight);
      uint16_t tempColour = (randomY * screenHeight) + randomX;// find correct colour in background
      byte newPixelSize = staticPixelSize * 4; //makes pixels new and blocky
      myScreen.fillRect(randomX, randomY, newPixelSize, newPixelSize, background[tempColour]);
    }
  } //end pixelateScreen
  
  void fullScreenStatic(){
    /*
     * Show randomly generated static on the screen
     * If changing colour array then make sure to have half black/half different shades
     */
//     unsigned long startTime = millis(); //used for timing checks
    uint16_t tempColour[4];
    tempColour[0] = TFT_BLACK;
    tempColour[1] = TFT_WHITE;
    tempColour[2] = TFT_BLACK;
    tempColour[3] = TFT_LIGHTGREY;
    for (uint16_t i = 0; i < (screenWidth * screenHeight); i++){
      byte randomY = random(0, screenWidth);
      byte randomX = random(0, screenHeight);
      uint16_t colourNumber = random(0, 3);//should this be 3
      byte newPixelSize = staticPixelSize; //needed ?
      myScreen.fillRect(randomX, randomY, newPixelSize, newPixelSize, tempColour[colourNumber]);
    }
/*    unsigned long endTime = millis() - startTime; //used for timing checks
    Serial.print("Full screen static Loop time : ");
    Serial.println(endTime);*/
  } //end fullScreenStatic
  
  void staticAndBackground(byte amountOfBackground){
    /*
     * Show randomly generated static and random parts of the background on the screen
     * If changing colour array then make sure to have half black/half different shades
     * 
     * IMPORTANT - amount of background has to be 5 or higher to ensure a mix of static and background.
     * 10 is a nice mix, and a for loop increasing from 10-100 in increments of 10 creates a nice effect
     * 
     */
    if (amountOfBackground < 5){ 
      amountOfBackground = 5; 
                }
    uint16_t tempColour[4];
    tempColour[0] = TFT_BLACK;
    tempColour[1] = TFT_WHITE;
    tempColour[2] = TFT_BLACK;
    tempColour[3] = TFT_LIGHTGREY;
    for (uint16_t i = 0; i < (screenWidth * screenHeight); i++){
      byte randomY = random(0, screenWidth);
      byte randomX = random(0, screenHeight);
      uint16_t colourNumber = random(0, amountOfBackground);
      byte newPixelSize = staticPixelSize;
      if (colourNumber < 4) {
        myScreen.fillRect(randomX, randomY, newPixelSize, newPixelSize, tempColour[colourNumber]);
      }
      else {
         uint16_t tempColour2 = (randomY * screenHeight) + randomX;// find correct colour in background
         myScreen.drawPixel(randomX, randomY, background[tempColour2]);
      }
    }
  } //end static and background
  
 void staticAndBackground(byte amountOfBackground, byte repeatValue){
    /*
     * Show randomly generated static and random parts of the background on the screen
     * If changing colour array then make sure to have half black/half different shades
     */
     for (byte i = 0; i < repeatValue; i++){
      staticAndBackground(amountOfBackground);
    } //end repeat loop
  } //end static and background
  
  private :
  byte screenHeight;
  byte screenWidth;
  byte staticHeight;
  byte staticStripHeight;
  byte staticPixelSize;
  byte staticStartPosition;
  byte pixelThreshold; //higher number = less black in static
  uint32_t backgroundArrayCounter;
  uint16_t backgroundColour;
  uint16_t *background;
  uint16_t *background2;
  TFT_eSPI myScreen=TFT_eSPI();
  unsigned long previousMillis = 0;
  };
  
//construct the static objects
screenStatic staticOne(0, 160, 128, 5, 2, 5, background1);

void setup(){
  Serial.begin(115200);
  delay(1000);  
  staticOne.start(); //remember to start each object otherwise screen won't be orientated correctly
}
void loop() {
  staticOne.fullScreenStatic(10);
  for (byte i = 0; i < 150; i+= 10){
    staticOne.staticAndBackground(i);
  }
  staticOne.backgroundLoadGradual(2);
  staticOne.backgroundImageRefreshColour();
  delay(3000);
  for (byte i = 150; i > 0; i -= 10){
    staticOne.staticAndBackground(i);
  }
  staticOne.setBackground(background2);
}
