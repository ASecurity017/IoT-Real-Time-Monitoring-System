# ---------------------------------------------------------
import speech_recognition as sr
import time
import serial

com_port = 'COM4'
# ---------------------------------------------------------
def main():

    ser = serial.Serial(com_port, 9600)

    listOfSamples = []  # needs to be outside loop so data isn't lost

    time.sleep(5)

    # Reads first two lines \n and Experiment 1 -- Group 1
    for i in range(0, 2):
        reading = ser.readline().decode('utf-8')[:-2]

        print(f' {reading}')

    #Initialise user input as an empty string
    user_input = ""

    while user_input != "quit":

        r = sr.Recognizer()

        with sr.Microphone() as source:
                print('Say your command ...')
                audio = r.listen(source)
        try:
            user_input = r.recognize_google(audio)
            print(
                'Google Speech Recognition thinks you said \'' +
                 user_input + '\'')

            if user_input == 'red' or user_input == 'Red':
                # Write command "Red" to serial monitor to turn on RED LED
                ser.write("red\n".encode())
                # Read the output produced from the "Red" command
                for i in range(0, 3):
                    reading = ser.readline().decode('utf-8')[:-1]
                    print(f'  {reading} ')
                    time.sleep(5)



            # if inputString == Green
            if user_input == 'green' or user_input == 'Green':
                #Write command to serial monitor to turn on  LED
                ser.write("green\n".encode())
                #Read the output produced from the "Green" command
                for i in range(0, 3):
                    reading = ser.readline().decode('utf-8')[:-1]
                    print(f'  {reading} ')
                    time.sleep(5)

            #if inputString == Blue
            if user_input == 'blue'or user_input == 'Blue':
                #Write command to serial monitor to turn on  LED
                ser.write("blue\n".encode())
                #Read the output produced from the "Blue" command
                for i in range(0, 3):
                    reading = ser.readline().decode('utf-8')[:-1]
                    print(f'  {reading} ')
                    time.sleep(5)

            if user_input == 'ledoff' or user_input == 'Ledoff' or user_input == 'LED off':
                #Write command to turn led off
                ser.write("ledoff\n".encode())
                # Read the output produced from the "ledoff" command
                for i in range(0, 3):
                    reading = ser.readline().decode('utf-8')[:-1]
                    print(f'  {reading} ')
                    time.sleep(5)

            if user_input == 'ledtest' or user_input == 'Ledtest' or user_input == 'LED test':
                #Write command to start RGB routine
                ser.write("ledtest\n".encode())

            #If inputString == sample
            if user_input == 'sample':
                #Write Sample to serial monitor
                ser.write("sample\n".encode())
                #Read 8 lines from Serial monitor
                for i in range(0, 6):
                    reading = ser.readline().decode('utf-8')[:-2]
                    listOfSamples.append(reading + "\n")
                    print(f'  {reading} ')
                    time.sleep(5)


            if user_input.startswith('run'):

                r = sr.Recognizer()

                with sr.Microphone() as source:
                    # Extract xx and yy from Run(xx,yy)
                    print('Say your xx value ...')
                    audio = r.listen(source)
                try:
                    user_xx_input = r.recognize_google(audio)

                    print('Google Speech Recognition thinks you said \'' +user_xx_input + '\'')

                except sr.UnknownValueError:
                    print('Google Speech Recognition could not understand audio')
                except sr.RequestError as e:
                    print(
                        'Could not request results from '
                        'Google Speech Recognition service; {0}'.format(e))


                with sr.Microphone() as source:
                    print('Say your yy value ...')
                    audio = r.listen(source)
                try:
                    user_yy_input = r.recognize_google(audio)

                    print('Google Speech Recognition thinks you said \'' + user_yy_input + '\'')

                except sr.UnknownValueError:
                    print('Google Speech Recognition could not understand audio')
                except sr.RequestError as e:
                    print(
                        'Could not request results from '
                        'Google Speech Recognition service; {0}'.format(e))

                xxstring = user_xx_input
                yystring = user_yy_input

                print(xxstring)
                print(yystring)

                yy_value = int(yystring)

                # Write Run(xx,yy) command to serial monitor
                ser.write(f'run({xxstring},{yystring})\n'.encode())

                # Read 30 lines outputted from Run(xx,yy) from the Serial monitor
                for i in range(0, 30):
                    reading = ser.readline().decode('utf-8')[:-2]
                    listOfSamples.append(reading + "\n")
                    print(f' {reading}')

                time.sleep(yy_value)

            if(user_input == 'help' or  user_input == 'Help'):


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


            if(user_input == "save" or user_input == "Save"):

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





        except sr.UnknownValueError:
            print('Google Speech Recognition could not understand audio')
        except sr.RequestError as e:
            print(
            'Could not request results from '
            'Google Speech Recognition service; {0}'.format(e))
# ---------------------------------------------------------
if __name__ == '__main__':
    print('\n----------------------------------------------------------')
    print('--Start script run ' + str(time.strftime('%c')))
    print('----------------------------------------------------------\n')
    main()
    print('\n----------------------------------------------------------')
    print('--End script run ' + str(time.strftime('%c')))
    print('----------------------------------------------------------\n')
    # ---------------------------------------------------------