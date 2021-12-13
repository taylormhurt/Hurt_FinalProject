#include <Adafruit_NeoPixel.h>

//Create variables for the buttons
int buttonPins[6] = {33, 34, 35, 30, 31, 32};
bool buttonState[6] = {LOW, LOW, LOW, LOW, LOW, LOW};
bool lastButtonState[6] {LOW, LOW, LOW, LOW, LOW, LOW};
bool buttonOn[6] = {false, false, false, false, false, false};
//Assign the keys to each button
int keyArray[6] = {KEY_F1, KEY_F2, KEY_F3, KEY_F4, KEY_F7, KEY_F8};

//Create a variable for the neopixels
Adafruit_NeoPixel neopixel = Adafruit_NeoPixel(6, 36, NEO_RGB);

//Variables for counters used
int j = 0;
int k = 1;

void setup() {
  //Set the pin mode for the buttons
  for(int i = 0; i < 6; i++) {
    pinMode(buttonPins[i], OUTPUT);
  }
  neopixel.begin();
  delay(100);
  //Set the "starting" color for each NeoPixel to white
  neopixel.setPixelColor(0, 85, 85, 85);
  neopixel.setPixelColor(1, 85, 85, 85);
  neopixel.setPixelColor(2, 85, 85, 85);
  neopixel.setPixelColor(3, 85, 85, 85);
  neopixel.setPixelColor(4, 85, 85, 85);
  neopixel.setPixelColor(5, 85, 85, 85);
  neopixel.show();
}

void checkButtons() {
  
//Create for loop, checking whether a button is pressed or not
  for(int i = 0; i < 6; i++) {
    lastButtonState[i] = buttonState[i];
    buttonState[i] = digitalRead(buttonPins[i]);

//Since the first 4 buttons are similar in behavior, they all work within the same if statement
    if(i == 1 or i == 2 or i == 3 or i == 4) {
      if(lastButtonState[i] == LOW and buttonState[i] == HIGH) {
        //i indicates the current button being activated, while the j indicates the "opposite button" 
      j = 5 - i;
      buttonOn[i] = !buttonOn[i];
      Keyboard.press(keyArray[i]);
      //Turn the button being pressed blue, and turn the "opposite" button pink
      neopixel.setPixelColor(i, 0, 0, 255);
      neopixel.setPixelColor(j, 127, 0, 127);
      neopixel.show();
      }
//Release the key if it is no longer being pressed
    else if(lastButtonState[i] == HIGH and buttonState[i] == LOW) {
      Keyboard.release(keyArray[i]);
      delay(5);
    }
  }
  //For the last 2 buttons
  else {
    if(lastButtonState[i] == LOW and buttonState[i] == HIGH) {
      //When k == 2, the button is being activated and turns blue. Otherwise, it turns back to pink
      k++;
      buttonOn[i] = !buttonOn[i];
      Keyboard.press(keyArray[i]);
      if(k == 2) {
      neopixel.setPixelColor(i, 0, 0, 255);
      neopixel.show();
      }
      if(k > 2) {
        neopixel.setPixelColor(i, 127, 0, 127);
        neopixel.show();
        k = 1;
      }

  }

  else if(lastButtonState[i] == HIGH and buttonState[i] == LOW) {
      Keyboard.release(keyArray[i]);
      delay(5);
  }
    
  }
 
}
}

void loop() {
  checkButtons();
} 
