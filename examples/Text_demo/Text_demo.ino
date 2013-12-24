#include <MatrixDisplay.h>
#include <DisplayToolbox.h>

// Easy to use function
#define setMaster(dispNum, CSPin) initDisplay(dispNum,CSPin,true)
#define setSlave(dispNum, CSPin) initDisplay(dispNum,CSPin,false)

// 3 = Number of displays
// WR = 11
// Data = 10
// True - we dont need a shadow buffer for this example. False would save 50% memory!

// Init Matrix
MatrixDisplay disp(3,11,10, true);
// Pass a copy of the display into the toolbox
DisplayToolbox toolbox(&disp);

int i = 0;

void setup() {
  //Serial.begin(9600); 
  
  // Prepare displays
  // The first number represents how the buffer/display is stored in memory. Could be useful for reorganising the displays or matching the physical layout
  // The number is a array index and is sequential from 0. You can't use 4-8. You must use the numbers 0-4
  disp.setMaster(0,4);
  disp.setSlave(1,5);
  disp.setSlave(2,6);
  //disp.setSlave(3,7);

  // Set PWM brightness of display, 0 to15.
  toolbox.setBrightness(5);
  
  // Set the font used for messages on the display.  Default is FONT_5x7W.  Available choices can be found in MatrixDisplay.h
  //toolbox.setFont(FONT_4x6);
  
  // Draw a string of text. (x start position, y start position, message and LEFT, RIGHT or CENTER alignment)
  toolbox.drawString(6,0,"Left",LEFT);
  toolbox.drawString(6,0,"- Right",RIGHT);
  // Sync the displays to push the messages to the board.
  disp.syncDisplays();
  delay(6000);
  
  disp.clear();
  toolbox.drawString(0,0,"Center Line",CENTER); // Center alignment doesn't carea bout the x start position.
  disp.syncDisplays();
  delay(6000);
 }


int x = 32+30;

void loop() {
  disp.clear();
  toolbox.drawString(6,0,"Left",LEFT);
  toolbox.drawString(6,0,"Right",RIGHT);
  // Sync the displays to push the messages to the board.
  disp.syncDisplays();
  delay(6000);
  
  disp.clear();
  toolbox.drawString(0,0,"Center Line",CENTER); // Center alignment doesn't carea bout the x start position.
  disp.syncDisplays();
  delay(6000);
  
/*
  disp.clear();
  toolbox.drawString(x,0,"Scrolling Text",RIGHT);
  disp.syncDisplays();
  delay(50);
  x--;
    
  //*/
}