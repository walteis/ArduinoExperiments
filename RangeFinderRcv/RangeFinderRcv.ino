/*********************************************************************
Program to display output from Ultrasonic range finder, sent by 433MHz transmitter, on a .96" OLED display.

As designed uses .96" display and Make "Maker" board, heterodyne receiver, and UNO R3.

Pinouts are:
Display     Prototype board
-------     ---------------
 VCC        3.3v
 GND        GND
 SCL        A5 (SCL)
 SDA        A4 (SDA)

Receiver   Prototype board
--------   ---------------
 VCC            5v
 GND            GND
 Data           D11





 
*********************************************************************/
#include <RH_ASK.h>
#include <SPI.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include <Fonts/FreeSans12pt7b.h>
#include <Fonts/FreeSans9pt7b.h>
#include <Fonts/FreeSerif9pt7b.h>
#include <Fonts/FreeMonoOblique9pt7b.h>


// set constants for display
#define OLED_RESET 4

// preform reset
Adafruit_SSD1306 display(OLED_RESET);

String a;   // global to hold distance

RH_ASK driver;

/*
 * Setup screen defaults and constants
 *  
 */
void setup()   {                  
  Serial.begin(9600);

  if (!driver.init())
      Serial.println("init failed");
  

  display.begin(SSD1306_SWITCHCAPVCC, 0x3C);  // initialize with the I2C addr 0x3C (for the 128x32)
  
  // Clear the buffer.
  display.clearDisplay();
  
  // write header text
  display.setTextSize(1);
  display.setTextColor(WHITE);
  display.println("Range Finder v3.0");
  
  // write column headings
  display.setTextSize(1);
  display.setTextColor(BLACK, WHITE);
  display.setCursor(1,10);
  display.print("     Distance     ");
  //display.setTextSize(2);
  display.setFont(&FreeMonoOblique9pt7b);
  display.display();
}

/*
 *  Processing Loop
 */
void loop() {

  
  String message;
  // Clear last distance
  // I do this to reset the screen to background color.
  display.setTextColor(BLACK,WHITE);
  display.setCursor(7,31);
  display.print(a);

  
  // get rangefinder output

  uint8_t buf[12];
  uint8_t buflen = sizeof(buf);
  if (driver.recv(buf, &buflen)) // Non-blocking
    {
      int i;
      // Message with a good checksum received, dump it.
      a = (char*)buf;
      a = a.substring(0,a.length()-4);
      a.trim();
      a.concat(" in");
    } else
    { 
      display.print("No Link");
    }
         
  // refresh the display
  display.setTextColor(WHITE, BLACK);
  display.setCursor(7,31);
  display.print(a);
  Serial.println(message);

  display.display();
  delay(10);
  
}
