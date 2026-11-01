# SMART PLANT CARE ASSISTANT

A plant-monitoring system built with a Seeed Studio XIAO RP2040. It monitors soil moisture, temperature, and humidity, 
then displays readings and provides LED alerts.

**Features**<br>
 -Reads soil moisture using a capacitive sensor.<br>
 -Measures temperature and humidity with an AHT20 sensor.<br>
 -Displays readings on a 0.96-inch SSD1306 OLED.<br>
 -Uses red and green LEDs for status indication.<br>
 -Switches OLED pages with a push button.<br>
 -Prints sensor readings and status messages to the Serial Monitor.

 **Hardware**<br>
 -Seeed Studio XIAO RP2040<br>
 -Capacitive soil moisture sensor<br>
 -AHT20 temperature and humidity sensor<br>
 -0.96-inch SSD1306 I2C OLED display<br>
 -Red LED and green LED<br>
 -2 × 220 Ω resistors<br>
 -Push button<br>
 -100 nF capacitor<br>
 -10 µF capacitor<br>
 
**Firmware**<br>
It is built with PlatformIO in Visual Studio Code using the Arduino framework.

**Required libraries:** <br>
  - Adafruit AHTX0<br>
  - Adafruit SSD1306<br>
  - Adafruit GFX Library

<img width="1365" height="717" alt="Schematic" src="https://github.com/user-attachments/assets/9dbd710c-24cf-44c5-8409-14e1c4645420" /> <br>


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

## Bill of Materials (BOM)

| Reference | Quantity | Component | Description |
|:---|:---:|:---|:---|
| U1 | 1 | Seeed Studio XIAO RP2040 | Microcontroller development board |
| J1 | 1 | AHT20 Sensor Module | Temperature and relative humidity sensor module |
| J2 | 1 | 0.96-inch OLED Display Module | SSD1306 I2C OLED, 128x64 |
| J3 | 1 | Capacitive Soil Moisture Sensor | 3-pin capacitive soil moisture sensor module |
| D1 | 1 | Red LED | Alert indicator LED |
| D2 | 1 | Green LED | Normal-status indicator LED |
| R1, R2 | 2 | Resistor | LED current-limiting resistor (220 Ω) |
| SW1 | 1 | Tactile Push Button | OLED page-selection button |
| C1 | 1 | Ceramic Capacitor | Power-supply decoupling capacitor (100 nF) |
| C2 | 1 | Electrolytic Capacitor | Power-supply filtering capacitor (10 µF) |

<img width="527" height="291" alt="image" src="https://github.com/user-attachments/assets/cd98fd86-216b-4502-863b-d591596ad382" />
<img width="528" height="138" alt="image" src="https://github.com/user-attachments/assets/c2715ce9-e2b9-4f55-93a5-08488a4daa2f" />


