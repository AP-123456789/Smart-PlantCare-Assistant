**SMART PLANT CARE ASSISTANT**

A plant-monitoring system built with a Seeed Studio XIAO RP2040. It monitors soil moisture, temperature, and humidity, 
then displays readings and provides LED alerts.

**Features**
 -Reads soil moisture using a capacitive sensor.
 -Measures temperature and humidity with an AHT20 sensor.
 -Displays readings on a 0.96-inch SSD1306 OLED.
 -Uses red and green LEDs for status indication.
 -Switches OLED pages with a push button.
 -Prints sensor readings and status messages to the Serial Monitor.

 **Hardware**
 -Seeed Studio XIAO RP2040
 -Capacitive soil moisture sensor
 -AHT20 temperature and humidity sensor
 -0.96-inch SSD1306 I2C OLED display
 -Red LED and green LED
 -2 × 220 Ω resistors
 -Push button
 -100 nF capacitor
 -10 µF capacitor
 
**Firmware**
It is built with PlatformIO in Visual Studio Code using the Arduino framework.

**Required libraries:** 
  - Adafruit AHTX0
  - Adafruit SSD1306
  - Adafruit GFX Library

<img width="1365" height="717" alt="Schematic" src="https://github.com/user-attachments/assets/9dbd710c-24cf-44c5-8409-14e1c4645420" />


<img width="1365" height="722" alt="pcb layout" src="https://github.com/user-attachments/assets/fa02c718-d102-4af9-a86b-7da23c0a7cdf" />

**To build:**
 1. Open the firmware folder in Visual Studio Code.
 2. Make sure the PlatformIO IDE extension is installed.
 3. Open platformio.ini and check the board configuration.
 4. Save the files and run PlatformIO: Build.

**Alert Thresholds**
  -Soil moisture below 30%
  -Temperature above 35 °C
  -Relative humidity below 30%

**Project Status**
The KiCad hardware design and PlatformIO firmware have been prepared.
The firmware compiles successfully. 

**Repository Structure**

Smart-PlantCare-Assistant/
├── Hardware/
│   ├── KiCad/
│   ├── Gerber/
|
├── Firmware/
│   └── Smart_Plant_Care/
│       ├── src/
│       ├── include/
│       ├── lib/
│       ├── test/
│       ├── platformio.ini
│       └── .gitignore
└── README.md

<img width="527" height="291" alt="image" src="https://github.com/user-attachments/assets/cd98fd86-216b-4502-863b-d591596ad382" />
<img width="528" height="138" alt="image" src="https://github.com/user-attachments/assets/c2715ce9-e2b9-4f55-93a5-08488a4daa2f" />


