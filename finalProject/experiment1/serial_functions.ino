/* --------------------------------------------------------------
 * Sketch file name   : serial_functions.ino
 * --------------------------------------------------------------
 * Group number       : 1
 * Group members      : Alex Gallet, Ben Whelan
 * Last updated on    : 25th September 2025
 * --------------------------------------------------------------
 * Sketch description : 
 * Example Arduino sketch for the Arduino UNO to demonstrate
 * the use of functions and multiple sketch files (.ino files)
 * -------------------------------------------------------------- */

/* --------------------------------------------------------------
 * void serialEvent(void)
 * -------------------------------------------------------------- */


//Function that reads input from the serial monitor 
void serialEvent(void)
{
  
  while (Serial.available())
  {   
    char inChar = (char)Serial.read();
    inputString += inChar;

    if (inChar=='\n')
    {
      stringComplete = true;
    }   
  }

}

/* --------------------------------------------------------------
 * void serial_header(void)
 * -------------------------------------------------------------- */
//Prints the header for the file 
void serial_header(void)
{

  Serial.println("\nExperiment 1 -- Group 1");

}

//Function that prints reading from the BME 280 Sensor 
void printValues(void){

   
   Serial.print("Temperature = ");
   Serial.print(bme.readTemperature());
   Serial.println(" °C");

   Serial.print("Pressure = ");
   Serial.print(bme.readPressure() / 100.0F);
   Serial.println("hPa");

   Serial.print("Approx. Altitude = ");
   Serial.print(bme.readAltitude(SEALEVELPRESSURE_HPA));
   Serial.println(" m");

   Serial.print("Humidity = ");
   Serial.print(bme.readHumidity());
   Serial.println(" %");

   Serial.println();


}

/* --------------------------------------------------------------
 * End of file
 * -------------------------------------------------------------- */
