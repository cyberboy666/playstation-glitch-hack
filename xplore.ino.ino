/*  PSX Controller Decoder Library (Psx.pde)
	Written by: Kevin Ahrendt June 22nd, 2008
	
	Controller protocol implemented using Andrew J McCubbin's analysis.
	http://www.gamesx.com/controldata/psxcont/psxcont.htm
	
	Shift command is based on tutorial examples for ShiftIn and ShiftOut
	functions both written by Carlyn Maw and Tom Igoe
	http://www.arduino.cc/en/Tutorial/ShiftIn
	http://www.arduino.cc/en/Tutorial/ShiftOut

    This program is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

#include <Psx.h>                                          // Includes the Psx Library 
                                                          // Any pins can be used since it is done in software
#define dataPin 8
#define cmndPin 9
#define attPin 11
#define clockPin 10

#define LEDPin 13

Psx Psx;                                                  // Initializes the library

unsigned int data = 0;                                    // data stores the controller response
long current = 0;
void setup()
{
  Psx.setupPins(dataPin, cmndPin, attPin, clockPin, 10);  // Defines what each pin is used
                                                          // (Data Pin #, Cmnd Pin #, Att Pin #, Clk Pin #, Delay)
                                                          // Delay measures how long the clock remains at each state,
                                                          // measured in microseconds.
                                                          // too small delay may not work (under 5)
  pinMode(LEDPin, OUTPUT);                                // Establishes LEDPin as an output so the LED can be seen
  pinMode(2, OUTPUT);
  pinMode(3, OUTPUT);
  pinMode(4, OUTPUT);
  pinMode(5, OUTPUT);
  pinMode(6, OUTPUT);
  pinMode(7, OUTPUT);
  pinMode(A1, OUTPUT);
  pinMode(A2, OUTPUT);
  Serial.begin(9600);

}

void doStuff(long diff, int pin) {
  if (diff > 0) {
    Serial.print("Turned pin ");
    Serial.print(pin);
    Serial.println(" on");
    digitalWrite(pin, HIGH);
  }
  else if (diff < 0) {
    Serial.print("Turned pin ");
    Serial.print(pin);
    Serial.println(" off");
    digitalWrite(pin, LOW);
  }
  else {
    Serial.println("We somehow got 0?");
  }
}

void loop() { 
  long bin[16] = {32768, 16384, 8192, 4096, 2048, 1024, 512, 256, 128, 64, 32, 16, 8, 4, 2, 1};
  long buttons[8] = {0, 0, 0, 0, 0, 0, 0, 0};

  data = Psx.read();
  int pos = 0;

  if (data != current) {
    long diff = data - current;
    switch (abs(diff)) {
      case psxLeft:
        doStuff(diff, 0);
        break;
      case psxDown:
        doStuff(diff, 0);
        break;
      case psxRight:
        doStuff(diff, 0);
        break;
      case psxUp:
        doStuff(diff, 0);
        break;
      case psxStrt:
        doStuff(diff, 0);
        break;
      case psxRTrig:
        doStuff(diff, 0);
        break;
      case psxLTrig:
        doStuff(diff, 0);
        break;
      case psxSlct:
        doStuff(diff, 0);
        break;
      case psxSqu:
        doStuff(diff, 2);
        break;
      case psxX:
        doStuff(diff, 3);
        break;
      case psxO:
        doStuff(diff, 4);
        break;
      case psxTri:
        doStuff(diff, 5);
        break;
      case psxR1:
        doStuff(diff, 6);
        break;
      case psxL1:
        doStuff(diff, 7);
        break;
      case psxR2:
        doStuff(diff, A1);
        break;
      case psxL2:
        doStuff(diff, A2);
        break;
    }
    current = data; 
  }  
} 
//  for (int i=0; i < (sizeof(bin)/sizeof(long)); i++) {
//    if (bin[i] <= data) {
//      buttons[pos] = bin[i];
//      data -= bin[i];
//      Serial.println(buttons[pos]);
//      pos +=1;
//    }
//  }

  




  



