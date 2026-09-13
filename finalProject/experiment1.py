import time
import serial

com_port = 'COM4'


def main():
    user_input = ""

    ser = serial.Serial(com_port, 9600)

    listOfSamples = []  # needs to be outside loop so data isnt lost

    time.sleep(5)

    #Reads first two lines \n and Experiment 1 -- Group 1
    for i in range(0, 2):
        reading = ser.readline().decode('utf-8')[:-2]

        print(f' {reading}')

    #while loop that continues to prompt the user to enter a command until the user types "quit"
    while user_input != "quit":
        print("Enter your command:")
        user_input = input()


        listOfSamples = [""]

        #if the user types  red or Red
        if user_input == 'red' or user_input == 'Red':
        # Write command "Red" to serial monitor to turn on RED LED
            ser.write("red\n".encode())
            #Read the output produced from the "Red" command
            for i in range(0, 3):
                reading = ser.readline().decode('utf-8')[:-2]
                print(f'{reading}')
                time.sleep(2)


        # if the user types green or Green
        if user_input == 'green' or user_input == 'Green':
            # Write command to serial monitor to turn on  LED
            ser.write("green\n".encode())
            # Read the output produced from the "Green" command
            for i in range(0, 3):
                reading = ser.readline().decode('utf-8')[:-2]
                print(f'{reading}')
                time.sleep(2)

        # if the user types blue or Blue
        if user_input == 'blue' or user_input == 'Blue':
            #Write command to serial monitor to turn on Blue  LED
            ser.write("blue\n".encode())
            # Read the output produced from the "Blue" command
            for i in range(0, 3):
                reading = ser.readline().decode('utf-8')[:-2]
                print(f'{reading}')
                time.sleep(2)
        # if the user types ledoff , or Ledoff, or LED off
        if user_input == 'ledoff' or user_input == 'Ledoff' or user_input == 'LED off':
            # Write command to turn led off
            ser.write("ledoff\n".encode())
            # Read the output produced from the "ledoff" command
            for i in range(0, 1):
                reading = ser.readline().decode('utf-8')[:-1]
                print(f'{reading}')
                time.sleep(2)


        if user_input == 'ledtest' or user_input == 'Ledtest' or user_input == 'LED test':
            # Write command to start RGB routine
            ser.write("ledtest\n".encode())
            time.sleep(12)


        #If user inputs sample or Sample
        if user_input == 'sample' or user_input == 'Sample':
            #Write Sample to serial monitor
            ser.write("sample\n".encode())
            # Read 8 lines from Serial monitor
            for i in range(0, 7):
                reading = ser.readline().decode('utf-8')[:-2]
                listOfSamples.append(reading + "\n")
                print(reading)
                time.sleep(2)
        # If the user inputs OLED, oled or Oled
        if user_input == 'OLED' or user_input == 'oled' or user_input == 'Oled':
            # Write oled command to serial monitor
            ser.write("oled\n".encode())
            time.sleep(2)

        #if the user inputs run or the string Run
        if user_input.startswith('run') or user_input.startswith('Run'):


            #Extract xx and yy from Run(xx,yy)
            xxstring = user_input[4:6]
            yystring = user_input[7:9]


            yy_value = int(yystring)

            # Write Run(xx,yy) command to serial monitor
            ser.write(f'run({xxstring},{yystring})\n'.encode())

            #Read 30 lines outputted from Run(xx,yy) from the Serial monitor
            for i in range(0, 30):
                reading = ser.readline().decode('utf-8')[:-2]
                listOfSamples.append(reading + "\n")
                print(f'{reading}')
                time.sleep(yy_value)

        #Prints out description describing each function clearly
        if (user_input == 'help' or user_input == 'Help'):
            print("\nAvailable Commands:")
            print("Red          - Turn The Red LED on.")
            print("Green        - Turn The Green LED on.")
            print("Blue         - Turn The Blue LED on.")
            print("LEDOff       - Turn All LED Off")
            print("LEDtest      - Run The LED Test Routine Once")
            print("Sample       - Read From BME-280 Sensor Once.")
            print("Run(xx,yy)   - Read From The BME-280 Sensor XX Times With YY S Delay.")
            print("Save         - Save The Sensor Results To A CSV File.")
            print("Help         - Show Available Commands & Information")
            print("Quit         - Quit the Program.")

        #Saves sample readings to csv file named by the user after the user inputs
        # Save or save
        if (user_input == "save" or user_input == "Save"):

            if len(listOfSamples) == 0:
                print("No samples to save")
            else:
                filename = input("Enter filename to save. (results.csv): ")
                try:
                    with open(filename, "w") as f:
                        for line in listOfSamples:
                            f.write(line)
                    print(f"\nData Sucessfully Saved to {filename}\n")
                except:
                    print("\nError Saving File. Please Try again. \n")



if __name__ == '__main__':
    main()
