/* --------------------------------------------------------------

 * Sketch file name   : experiment1.ino
 * --------------------------------------------------------------
 * Group number       : 1
 * Group members      : Alex Gallet, Ben Whelan
 * Last updated on    : 25th September 2025
 * --------------------------------------------------------------
 * Sketch description : 
 * Acts as the main() function where all functions are called to and results 
 * are returned to
 * -------------------------------------------------------------- */

/* --------------------------------------------------------------
 * Preamble
 * -------------------------------------------------------------- */

int delayTime = 1000*6;

//Header file needed for OLED
#include "U8glib.h"

//Header files needed for BME280 
#include <Wire.h>
//#include <SPI.h>
#include <Adafruit_Sensor.h>
#include <Adafruit_BME280.h>

#define SEALEVELPRESSURE_HPA (1013.25)
Adafruit_BME280 bme; // I2C

#define OLED_MOSI   9
#define OLED_CLK    10
#define OLED_DC     11
#define OLED_CS     12
#define OLED_RESET  8

#define RED 3
#define BLUE 4
#define GREEN 5

// U8GLIB_SSD1306_128X64 u8g(OLED_CLK, OLED_MOSI, OLED_CS, OLED_DC);
U8GLIB_SH1106_128X64 u8g(OLED_CLK, OLED_MOSI, OLED_CS, OLED_DC);

String inputString = "";
boolean stringComplete = false;


/* --------------------------------------------------------------
 * void clear_screen(void)
 * --------------------------------------------------------------
 * Clear the screen
 * -------------------------------------------------------------- */

void clear_screen(void)
{

  u8g.firstPage();        
  do
  {    
  }
  while (u8g.nextPage());
 
}




/* --------------------------------------------------------------
 * display_text(int x, int y, String value)
 * --------------------------------------------------------------
 * Display a string at a particular location
 * -------------------------------------------------------------- */

void display_text(int x, int y, String my_string)
{

  int array_length = my_string.length() + 1;
  char char_array[array_length];
  my_string.toCharArray(char_array, array_length);
 
  u8g.firstPage();      
  do
  {  
    u8g.setFont(u8g_font_courB12);  
    u8g.drawStr(x, y, char_array);  
  }
  while (u8g.nextPage());

  delay(1000);
 
}


/* --------------------------------------------------------------
 * void setup(void)
 * -------------------------------------------------------------- */

void setup(void)
{

  pinMode(RED, OUTPUT);
  pinMode(BLUE,OUTPUT);
  pinMode(GREEN, OUTPUT);

  digitalWrite(RED, HIGH);
  digitalWrite(BLUE, HIGH);
  digitalWrite(GREEN, HIGH);
  
  pinMode(LED_BUILTIN, OUTPUT);
  digitalWrite(LED_BUILTIN, LOW);

  
 // Splash Screen Set Up Code 
  pinMode(OLED_RESET, OUTPUT);
 
  digitalWrite(OLED_RESET, LOW);
  delay(100);
  digitalWrite(OLED_RESET, HIGH);

  clear_screen();

  u8g.firstPage();        
  do
  {  
    u8g.setFont(u8g_font_courB10);  
    u8g.drawStr(10, 10, "Arduino UNO");  
  }
  while (u8g.nextPage());

  delay(1000);


  Serial.begin(9600);

  serial_header();

  Serial.flush();

  
 

  

}

/* --------------------------------------------------------------
 * void loop(void) 
 * -------------------------------------------------------------- */
 
void loop(void)
{
 


  
  /* ---------------------------------------------------
   * Check for byte received
   * --------------------------------------------------- */

  //Calls function to read input from the serial monitor entered by the user 
  serialEvent();

  /* --------------------------------------------------- */

  if (stringComplete && (inputString=="red\n"))
  {
    //Calls function to turn  Red led on
    turn_Red_On();

    

    inputString    = "";
    stringComplete = false; 

  /* --------------------------------------------------- */

  } else if ( stringComplete && ( inputString=="green\n" ) )
  {

    //Calls function to turn Green on
    turn_Green_On();

    inputString    = "";
    stringComplete = false;

  /* --------------------------------------------------- */

  } else if ( stringComplete && ( inputString=="blue\n" ) )
  {
    //Calls function to turn Blue led on
    turn_Blue_On();

    inputString    = "";
    stringComplete = false;

  /* --------------------------------------------------- */

  } else if ( stringComplete && ( inputString=="ledoff\n" ) )
  {

    //Calls function to turn led off
    ledOff();
    

    inputString    = "";
    stringComplete = false;

  /* --------------------------------------------------- */
      
  } else if(stringComplete && (inputString == "sample\n")){


   Serial.println("\nSample Read from BME280");

   unsigned status;
    
    // default settings
    status = bme.begin(0x76);  
    // You can also pass in a Wire library object like &Wire2
    //status = bme.begin(0x76, &Wire2)
    if (!status) {
        Serial.println("Could not find a valid BME280 sensor, check wiring, address, sensor ID!");
        Serial.print("SensorID was: 0x"); Serial.println(bme.sensorID(),16);
        Serial.print("        ID of 0xFF probably means a bad address, a BMP 180 or BMP 085\n");
        Serial.print("   ID of 0x56-0x58 represents a BMP 280,\n");
        Serial.print("        ID of 0x60 represents a BME 280.\n");
        Serial.print("        ID of 0x61 represents a BME 680.\n");
        while (1) delay(1);
        
    }
    
    //Calls function to print sample values  from BME280 only once 
    printValues();

    inputString    = "";
    stringComplete = false;


  } else if(stringComplete && (inputString.startsWith("run"))) {
  
  //Run(xx,yy)
  String xxstring = inputString.substring(4,6);
  String yystring = inputString.substring(7,9);

  
  //Extracting out each value from xx
  String x1 = xxstring.substring(0,1);
  String x2 = xxstring.substring(1);


  //Converting each x value from a String to an Integer
  int xOne = x1.toInt();
  int xTwo = x2.toInt();
  //Converting yy from a String to an Integer
  int yy = yystring.toInt();

  int ones;
  int tens;
  
  //loops until xx samples are read from and printed to the screen
  for(int i = 0; i < 100; i++){

    ones = (i % 10);
    tens = ((i - ones) / 10);
    
    //Check if xx samples have been read, if they have it terminates the loop
    if(tens == xOne && ones == xTwo) break;

    
    unsigned status;
    
    // default settings
    status = bme.begin(0x76);  
   
    if (!status) {
        Serial.println("Could not find a valid BME280 sensor, check wiring, address, sensor ID!");
        Serial.print("SensorID was: 0x"); Serial.println(bme.sensorID(),16);
        Serial.print("        ID of 0xFF probably means a bad address, a BMP 180 or BMP 085\n");
        Serial.print("   ID of 0x56-0x58 represents a BMP 280,\n");
        Serial.print("        ID of 0x60 represents a BME 280.\n");
        Serial.print("        ID of 0x61 represents a BME 680.\n");
        while (1) delay(1);
        
    }
    
    Serial.print("Sample Reading: ");  
    Serial.print(tens);
    Serial.println(ones);

    //print sample reading from BME280
    printValues();
    // delay each read with yy seconds
    delay(yy*1000);

    
   }

      
  inputString    = "";
  stringComplete = false;

 

  
 
  
  
  } else if (stringComplete && (inputString == "ledtest\n")) {

    //calls function to perform LED routine 
    ledTest();
  
  
  } else if (stringComplete && (inputString == "oled\n")){

  // Display text on Splash Screen
  display_text(5, 40, "GROUP 1 ");
  delay(delayTime);
  display_text(5, 40, "2025 Project");
  delay(delayTime);
  display_text(5, 100, "AB");
  delay(delayTime);

  clear_screen();
  delay(delayTime);

//animation slide in
for (int i = 0; i < 128; i += 8) {
  u8g.firstPage();
  do {
    u8g.setFont(u8g_font_courB10);
    u8g.drawStr(128 - i, 30, "Alex & Ben ");
  } while (u8g.nextPage());
 delay(80);
}


delay(delayTime);
clear_screen();

  inputString    = "";
  stringComplete = false;

  } else if (stringComplete)
  {
    
    Serial.println("Error: Incorrect string received.");
    

    inputString    = "";
    stringComplete = false;

  }

  



  /* --------------------------------------------------- */

}

/* --------------------------------------------------------------
 * End of file
 * -------------------------------------------------------------- */
