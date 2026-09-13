# IoT-Real-Time-Monitoring-System
 A real-time monitoring system using the  hardware that consists of The Arduino Uno, a Prototype breadboard, wiring, an RGB LED, an OLED Display and the BME280 sensor. All of these hardware components are controlled by code, using Arduino IDE and the C language as well as Py Charm and the Python language


<br>
Image of the of the hardware of the project
<br>
<img width="697" height="626" alt="image" src="https://github.com/user-attachments/assets/7e0a19c5-da2d-45c7-aa94-8206250ca23d" />
<br>

.1 Code Overview 
Arduino code is referring to the code in the Arduino IDE that we used for this project. The 
code was made into 3 separate Arduino files (.ino extension) and in total the project consists 
of 450 lines. The file layout that is most commonly used is to have your includes and 
definitions at the top, then any functions that you make yourself to be used in the file. In our 
project, we have experiment1.ino which acts as the main function in which all function calls 
are made from experiment1.ino to our two other Arduino code files – led_functions.ino 
(contains functions that turn on and off LEDs ) and serial_functions.ino (contains functions 
that read user input, display debugging messages used for error handling, and prints readings 
from the BME280). In experiment1.ino, the setup() function only runs once, after each 
powerup or rest of the Arduino board. Below that is the loop() function, this function 
continuously loops, allowing the program to change and respond. At the top of 
experiment1.ino and led_functions.ino, there is definitions for the hardware, specifically for 
defining what pins do what for example like RGB colours and Screen pins. Also, libraries 
used needed for screen and sensor initialization were included at the top of experiment1.ino. 

3.2 Libraries Used 
The following two libraries were used for the project: The U8glib library enabled us to 
initialise the OLED Display. The Adafruit_BME280 enabled us to initialise the BME280 
sensor for taking in readings from the surrounding environment. 

3.3 The setup( ) Function 
The setup() function defined the RGB LED pins as outputs, also initialized the serial 
communication to 9600 baud to enable communication with the computer, and called 
led_header() to perform a startup blink sequence using the LED, this is confirming that the 
board was powered. It also initialized the BME280 sensor library, preparing the sensor for 
data acquisition. 

3.4 The loop( ) Function 
The loop() function is an infinite loop that checks for updates to the hardware state and acts 
accordingly when these updates happen. The code within the loop firstly calls the 
serialEvent() function that we added which takes in user input that was either typed or voice


Chapter 4: Python Code 
4.1 Code Overview  
The first python script – experiment1.py - served as the external interface between user and 
microcontroller. This established a serial connection with the Arduino over USB and allowed 
the user to type commands directly from the computer. The program initially displayed a 
menu which prompted the user the defined commands (Red, Green, Blue, LEDoff, LEDtest, 
Sample, Run (xx,yy ), Save, Help, Quit). Each command was sent to the Arduino as a text 
string followed by a newline character which allowed the Arduino to recognise it 
immediately. This script ensured two-way communication which allows the computer to 
control the Arduinos hardware, but also to receive and store live data for later analysis. 
The second python script – experiment1withvoice.py – is the exact same as experiment1.py 
only this time it utilizes the speech recognition library allowing the user to speak their 
commands rather than type them. 
4.2 Libraries Used 
The following libraries that we used for this project include: The serial.py library allowed us 
to read and write to the serial on the 9600 baud rate. The time library gave us the ability to 
add delays to specific parts of our code using the time.sleep() function provided by the time 
library. Lastly, the speechrecognition.py library made it possible to use voice recognition to 
speak commands into the computer which could then manipulate the hardware on the 
Arduino Uno. 

4.3 The main() function  
Note: I will be referring to experiment1withvoice.py from now on. The main() function 
starts with connecting to the serial ports and setting the baud rate. After this we initialise an 
empty array to store the samples to be read and sleep the program for 5 seconds. Now the 
while loop starts and will continue to loop until the user speaks the command “quit”. The 
while loop contains a microphone source and will prompt the user to say their command. It 
will begin a try-block and start trying to recognise the command and store it in the variable 

user-input. This user input is put through an array of if-else statements if it matches any of the 
conditions the corresponding commands is written to the serial monitor for the Arduino uno 
to go and perform its actions on the hardware (i.e. Turning on the Red LED). An example of 
how a command is written out below in figure 4.1  
Figure 4.1: Code segment of experiment1withvoice.py 
Lastly, at the bottom of the main function there are catch statements, one for if google cannot 
recognise what you said, and one if google cannot request any results from their service. 
