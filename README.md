# Environmental Sensor & Voice-Controlled LED Project

A hardware/software project combining an Arduino Uno microcontroller with a Python-based control interface, supporting both typed and voice commands.

## Overview

The system lets a user control an RGB LED and read live environmental data (via a BME280 sensor) from a computer, either by typing commands or speaking them aloud. The Arduino handles hardware I/O and an OLED display, while Python scripts on the host machine manage the serial connection, user interface, and (optionally) speech recognition.

---

## Project Structure

```
├── experiment1.ino          # Main Arduino sketch — setup(), loop(), function calls
├── led_functions.ino        # LED on/off control functions
├── serial_functions.ino     # Serial input handling, debugging output, BME280 readings
├── experiment1.py           # Python interface — typed command control
└── experiment1withvoice.py  # Python interface — voice command control (adds speech recognition)
```

Total Arduino code: **~450 lines** across three `.ino` files.

---

## Arduino Code

### Architecture
- **`experiment1.ino`** acts as the main entry point. It defines hardware pins (RGB LED, screen) and library includes at the top, then calls out to the other two files.
- **`led_functions.ino`** contains all functions for turning LEDs on and off.
- **`serial_functions.ino`** handles reading user input over serial, printing debug/error messages, and outputting BME280 sensor readings.

### Libraries Used
| Library | Purpose |
|---|---|
| `U8glib` | Initializes and drives the OLED display |
| `Adafruit_BME280` | Initializes the BME280 sensor and reads environmental data |

### `setup()`
Runs once on power-up or reset. It:
1. Sets the RGB LED pins as outputs
2. Initializes serial communication at **9600 baud**
3. Calls `led_header()` — a startup blink sequence confirming the board is powered
4. Initializes the BME280 sensor library for data acquisition

### `loop()`
Runs continuously. Each cycle it calls `serialEvent()`, which listens for incoming user input (typed or relayed from voice) and updates hardware state in response.

---

## Python Code

### Overview
| Script | Description |
|---|---|
| `experiment1.py` | Serial interface between user and Arduino over USB. Displays a command menu and sends typed commands as newline-terminated strings. |
| `experiment1withvoice.py` | Identical to `experiment1.py`, but replaces typed input with speech recognition. |

**Available commands:** `Red`, `Green`, `Blue`, `LEDoff`, `LEDtest`, `Sample`, `Run(xx,yy)`, `Save`, `Help`, `Quit`

Both scripts support two-way communication — sending control commands to the Arduino and receiving/storing live sensor data for later analysis.

### Libraries Used
| Library | Purpose |
|---|---|
| `pyserial` | Serial read/write at 9600 baud |
| `time` | Adds delays via `time.sleep()` |
| `SpeechRecognition` | Converts spoken commands to text |

### `main()` (in `experiment1withvoice.py`)
1. Opens the serial connection at the correct baud rate
2. Initializes an empty array to store incoming samples
3. Sleeps for 5 seconds to allow the connection to stabilize
4. Enters a loop that listens via microphone until the user says **"quit"**
5. Recognized speech is matched against the command list via if/else checks; a match is written to the serial monitor, triggering the corresponding Arduino action (e.g., turning on the red LED)
6. Includes exception handling for two failure cases: speech not recognized, and no response from Google's speech API

---

## Getting Started

1. Flash `experiment1.ino` (with `led_functions.ino` and `serial_functions.ino` in the same sketch folder) to the Arduino Uno via the Arduino IDE.
2. Install Python dependencies:
   ```bash
   pip install pyserial SpeechRecognition
   ```
3. Run the typed-command interface:
   ```bash
   python experiment1.py
   ```
   Or the voice-command interface:
   ```bash
   python experiment1withvoice.py
   ```
4. Follow the on-screen (or spoken) menu to control the LED and sample sensor data.

## Hardware of the project
<br>
<img width="697" height="626" alt="image" src="https://github.com/user-attachments/assets/5cc97533-74df-45f1-bc33-68e893a5f488" />

