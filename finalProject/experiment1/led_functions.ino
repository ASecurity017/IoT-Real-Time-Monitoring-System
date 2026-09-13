/* --------------------------------------------------------------
 * Sketch file name   : led_functions.ino
 * --------------------------------------------------------------
 * Group number       : 1
 * Group members      : Alex Gallet, Ben Whelan
 * Last updated on    : 18th September 2025
 * --------------------------------------------------------------
 * Sketch description : Contains all functions for LED manipulation 
 * 
 * -------------------------------------------------------------- */

/* --------------------------------------------------------------
 * void led_header(void)
 * -------------------------------------------------------------- */

#define RED 3
#define BLUE 4
#define GREEN 5







/* --------------------------------------------------------------
 * led_function_1(void)
 * -------------------------------------------------------------- */

void turn_Red_On(void)
{
  digitalWrite(GREEN, HIGH);
  digitalWrite(BLUE, HIGH);
  Serial.println("\nRed LED Turned on\n");
  digitalWrite(RED, LOW);
  delay(500);

}

/* --------------------------------------------------------------
 * led_function_2(void)
 * -------------------------------------------------------------- */

void turn_Green_On(void)
{
  digitalWrite(RED, HIGH);
  digitalWrite(BLUE, HIGH);
  Serial.println("\nGreen LED turned ON\n");
  digitalWrite(GREEN, LOW);

}

/* --------------------------------------------------------------
 * led_function_3(void)
 * -------------------------------------------------------------- */

//Turn on BLUE Led
void turn_Blue_On(void)
{
  
  digitalWrite(RED, HIGH);
  digitalWrite(GREEN, HIGH);
  Serial.println("\nBlue LED turned ON\n");
  digitalWrite(BLUE, LOW);
  

}

//Turns all RGB Leds off
void ledOff(void){

  digitalWrite(RED,HIGH);
  digitalWrite(BLUE,HIGH);
  digitalWrite(GREEN,HIGH);
  Serial.println("LED Turned off sucessfully\n");

}


//turn on and off each RGB led in a sequence
void ledTest(void){

  digitalWrite(RED, LOW);
  delay(10003);
  digitalWrite(RED, HIGH);
  digitalWrite(BLUE, LOW);
  delay(10003);
  digitalWrite(BLUE, HIGH);
  digitalWrite(GREEN, LOW);
  delay(1000*3);
  digitalWrite(GREEN, HIGH);
}


/* --------------------------------------------------------------
 * 
 * -------------------------------------------------------------- */
 

/* --------------------------------------------------------------
 * End of file
 * -------------------------------------------------------------- */
