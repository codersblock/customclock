#include <LedControl.h>
#include <TimeLib.h>

//pin definitions

//LED matrix
#define DIN 11
#define CS  12
#define CLK 13

//buttons
#define STARTBUTTON 3
#define PLUSONEBUTTON 0
#define PLUSFIVEBUTTON 1
#define RESETBUTTON 2

//breadboard LEDs
#define REDONE 9
#define REDTWO 8
#define REDTHREE 7
#define GREEN 6

#define BUZZER 5

#define uint unsigned long
#define ONE_MIN 60

//global state variables
bool start_button_pressed = false;
bool plusone_button_pressed = false;
bool plusfive_button_pressed = false;
bool reset_button_pressed = false;
bool clock_running = false;
int clock_time = 0;

//led layout of each digit and character
const byte ZERO[] = {
  B01110,
  B10001,
  B10001,
  B10001,
  B10001,
  B10001,
  B01110
};

const byte ONE[] = {
  B00100,
  B01100,
  B10100,
  B00100,
  B00100,
  B00100,
  B11111
};

const byte TWO[] = {
  B01110,
  B10001,
  B00001,
  B00110,
  B01000,
  B10000,
  B11111
};

const byte THREE[] = {
  B01110,
  B10001,
  B00001,
  B01110,
  B00001,
  B10001,
  B01110
};

const byte FOUR[] = {
  B00010,
  B00110,
  B01010,
  B10010,
  B11111,
  B00010,
  B00010
};

const byte FIVE[] = {
  B11111,
  B10000,
  B10000,
  B11110,
  B00001,
  B10001,
  B01110
};

const byte SIX[] = {
  B01110,
  B10000,
  B10000,
  B11110,
  B10001,
  B10001,
  B01110
};

const byte SEVEN[] = {
  B11111,
  B00001,
  B00010,
  B00100,
  B00100,
  B00100,
  B00100
};

const byte EIGHT[] = {
  B01110,
  B10001,
  B10001,
  B01110,
  B10001,
  B10001,
  B01110
};

const byte NINE[] = {
  B01110,
  B10001,
  B10001,
  B01111,
  B00001,
  B10001,
  B01110
};

const byte G[] = {
  
};

const byte O[] = {
  
};

LedControl lc = LedControl(DIN, CLK, CS, 4);

uint pushByteRow(uint currentDisplayRow, byte ledValues) {
  return ((currentDisplayRow << 6) | ledValues);
}

void pushDigit(uint* currentDisplay, uint digitToPush) {
  for (uint row = 0; row < 7; row++) {
    switch(digitToPush) {
      case 1 : {
        currentDisplay[row] = pushByteRow(currentDisplay[row], ONE[row]);
        break;
      }
      case 2 : {
        currentDisplay[row] = pushByteRow(currentDisplay[row], TWO[row]);
        break;
      }
      case 3 : {
        currentDisplay[row] = pushByteRow(currentDisplay[row], THREE[row]);
        break;
      }
      case 4 : {
        currentDisplay[row] = pushByteRow(currentDisplay[row], FOUR[row]);
        break;
      }
      case 5 : {
        currentDisplay[row] = pushByteRow(currentDisplay[row], FIVE[row]);
        break;
      }
      case 6 : {
        currentDisplay[row] = pushByteRow(currentDisplay[row], SIX[row]);
        break;
      }
      case 7 : {
        currentDisplay[row] = pushByteRow(currentDisplay[row], SEVEN[row]);
        break;
      }
      case 8 : {
        currentDisplay[row] = pushByteRow(currentDisplay[row], EIGHT[row]);
        break;
      }
      case 9 : {
        currentDisplay[row] = pushByteRow(currentDisplay[row], NINE[row]);
        break;
      }
      default : {
        currentDisplay[row] = pushByteRow(currentDisplay[row], ZERO[row]);
        break;
      }
    }
  }
}

void pushColon(uint* currentDisplay) {
  for (uint row = 0; row < 7; row++) {
    currentDisplay[row] = currentDisplay[row] << 2;
    if (row == 1 || row == 5) {
      currentDisplay[row] |= 1;
    }
  }
}

void updateLedRows(uint* displayMatrix) {
  //leave top row blank
  for (uint row = 1; row < 8; row++) {
    uint rowData = displayMatrix[row-1];
    for (int displayAddress = 0; displayAddress < 4; displayAddress++) {
      lc.setRow(displayAddress, row, ((byte)(rowData & 0x000000FF)));
      rowData = rowData >> 8;
    }
  }
}

void displayTime(int elapsedTimeInSeconds) {
  //find the number of seconds to display
  uint seconds = elapsedTimeInSeconds % 60;
  
  //find the number of minutes
  uint elapsedMinutes = elapsedTimeInSeconds / 60;

  //find the number of minutes to display
  uint minutes = elapsedMinutes % 60;

  //find the number of hours to display
  uint hours = elapsedMinutes / 60;

  uint displayMatrix[7] = {0,0,0,0,0,0,0};
  
  if (hours > 0) {
    pushDigit(displayMatrix, hours);
    pushColon(displayMatrix);
    if (minutes < 10) {
      pushDigit(displayMatrix, 0);
    }
  }

  if (minutes > 9) {
    pushDigit(displayMatrix, (minutes / 10));
  }
  pushDigit(displayMatrix, (minutes % 10));

  pushColon(displayMatrix);

  pushDigit(displayMatrix, (seconds / 10));
  pushDigit(displayMatrix, (seconds % 10));
  
  updateLedRows(displayMatrix);
}

void setup()
{ 
  pinMode(STARTBUTTON, INPUT_PULLUP);
  pinMode(PLUSONEBUTTON, INPUT_PULLUP);
  pinMode(PLUSFIVEBUTTON, INPUT_PULLUP);
  pinMode(RESETBUTTON, INPUT_PULLUP);

  pinMode(BUZZER, OUTPUT);
  digitalWrite(BUZZER, LOW);
  
  for (int device = 0; device < lc.getDeviceCount(); device++) {
    lc.setIntensity(device, 5);
    lc.shutdown(device, false);
    lc.clearDisplay(device);
  }

  setTime(0);
}

void loop() {
  if (digitalRead(STARTBUTTON) == LOW) {
    if (start_button_pressed == false) {
      start_button_pressed = true;
      clock_running = !clock_running;
      setTime(0);
      displayTime(clock_time);
//      digitalWrite(BUZZER, HIGH);
//      delay(100);
//      digitalWrite(BUZZER, LOW);
    }    
  } else {
    start_button_pressed = false;
  }

  if (digitalRead(PLUSONEBUTTON) == LOW) {
    if (plusone_button_pressed == false) {
      plusone_button_pressed = true;
      clock_time += ONE_MIN;
    }    
  } else {
    plusone_button_pressed = false;
  }

  if (digitalRead(PLUSFIVEBUTTON) == LOW) {
    if (plusfive_button_pressed == false) {
      plusfive_button_pressed = true;
      clock_time += (ONE_MIN * 5);
    }
  } else {
    plusfive_button_pressed = false;
  }
  
  if (digitalRead(RESETBUTTON) == LOW) {
    if (reset_button_pressed == false) {
      reset_button_pressed = true;
      clock_time = 0;
    }
  } else {
    reset_button_pressed = false;
  }

  if (clock_running) {
    if (clock_time == 0) {
      displayTime((int)now());
    } else {
      int time_diff = clock_time - (int)now();
      time_diff = time_diff > 0 ? time_diff : 0;
      displayTime(time_diff);
    }
  } else {
    displayTime(clock_time);
  }
}
