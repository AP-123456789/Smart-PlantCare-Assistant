# Smart Plant Care Assistant

The **Smart Plant Care Assistant** is a plant-monitoring system built around the Seeed Studio XIAO RP2040 microcontroller. It monitors soil moisture, ambient temperature, and humidity, presenting real-time telemetry on an SSD1306 OLED display with visual status alerts via red and green LEDs. A push-button switch allows seamless navigation between multiple display pages.

## Project Design & Development Overview

1. **Schematic & Component Selection:** Designed in KiCad using the Seeed Studio XIAO RP2040 core. Wired analog soil moisture sensing, shared I2C bus lines for the AHT20 sensor and SSD1306 OLED display, dual-LED indicators with current-limiting resistors, and a debounced push button.

2. **Rules Checking & Footprints:** Configured `PWR_FLAG` symbols and No Connect markers to pass KiCad Electrical Rules Check (ERC) with zero errors. Mapped custom physical footprints for all surface-mount and through-hole components.

3. **PCB Layout & Routing:** Built a dual-layer PCB with routed power, ground, and signal traces, decoupling capacitors (`C1`, `C2`), and clean `Edge.Cuts` boundary outlines. Cleared all 19 Design Rules Check (DRC) clearance and text height warnings.

4. **Manufacturing Preparation:** Generated and verified production Gerber layers, Excellon drill files, and 3D render outputs using KiCad Gerber Viewer.

5. **Firmware Development:** Written in C++ using Visual Studio Code and PlatformIO under the Arduino framework. Integrated Adafruit driver libraries (`AHTX0`, `SSD1306`, `GFX`), implemented low moisture (<30%) and high temp (>35°C) alert logic, and added multi-page OLED UI toggling.

## Key Features

* **Microcontroller Core:** Seeed Studio XIAO RP2040 running custom C++/Arduino firmware developed in Visual Studio Code with PlatformIO.

* **Environmental Sensing:** High-precision ambient temperature and humidity tracking via the I2C AHT20 sensor.

* **Soil Moisture Monitoring:** Capacitive soil moisture sensor for corrosion-free analog measurement.

* **Multi-Page Visual Display:** 128x64 SSD1306 OLED displaying soil status on Page 1 and climate telemetry on Page 2.

* **User Interface Control:** Physical push button connected to interrupt input (`D3`) for instantaneous display page toggling.

* **Status Alert Logic:** Dynamic red/green LED indicators evaluating threshold conditions (low moisture <30%, high temp >35°C, dry air <30%).

* **Custom PCB Design:** Two-layer custom PCB designed in KiCad, complete with power decoupling capacitors and optimized trace routing.

## Bill of Materials (BOM)

All electronic components, hardware, and prototyping boards are sourced from a single vendor (**Adafruit**) to eliminate extra shipping fees and streamline procurement under \$30.00.

| Item No. | Component Description | Designator | Qty | Unit Price (\$) | Ext. Price (\$) | Vendor | Sourcing Link | 
| ----- | ----- | ----- | ----- | ----- | ----- | ----- | ----- | 
| **1** | Seeed Studio XIAO RP2040 Microcontroller | U1 | 1 | \$5.40 | \$5.40 | Adafruit | [Adafruit Product 5395](https://www.adafruit.com/product/5395) | 
| **2** | AHT20 Temperature & Humidity Sensor | J1 | 1 | \$4.50 | \$4.50 | Adafruit | [Adafruit Product 4566](https://www.adafruit.com/product/4566) | 
| **3** | SSD1306 OLED Display (128x64, I2C) | J2 | 1 | \$3.50 | \$3.50 | Adafruit | [Adafruit Product 938](https://www.adafruit.com/product/938) | 
| **4** | Capacitive Soil Moisture Sensor | J3 | 1 | \$4.95 | \$4.95 | Adafruit | [Adafruit Product 4026](https://www.adafruit.com/product/4026) | 
| **5** | Red LED (5mm) | D1 | 1 | \$0.25 | \$0.25 | Adafruit | [Adafruit Product 298](https://www.adafruit.com/product/298) | 
| **6** | Green LED (5mm) | D2 | 1 | \$0.25 | \$0.25 | Adafruit | [Adafruit Product 300](https://www.adafruit.com/product/300) | 
| **7** | 220 Ω Through-Hole Resistors | R1, R2 | 2 | \$0.10 | \$0.20 | Adafruit | [Adafruit Product 2780](https://www.adafruit.com/product/2780) | 
| **8** | Tactile Push Button Switch | SW1 | 1 | \$0.50 | \$0.50 | Adafruit | [Adafruit Product 367](https://www.adafruit.com/product/367) | 
| **9** | 100 nF Non-Polarized Capacitor | C1 | 1 | \$0.20 | \$0.20 | Adafruit | [Adafruit Product 2778](https://www.adafruit.com/product/2778) | 
| **10** | 10 µF Polarized Capacitor | C2 | 1 | \$0.25 | \$0.25 | Adafruit | [Adafruit Product 2195](https://www.adafruit.com/product/2195) | 
| **11** | Perma-Proto Custom PCB Board | PCB | 1 | \$2.95 | \$2.95 | Adafruit | [Adafruit Product 1609](https://www.adafruit.com/product/1609) | 

### Cost Breakdown Summary

* **Adafruit Hardware & Components Subtotal:** \$22.70

* **Estimated Consolidated Shipping (USPS Ground):** \$4.75

* **Estimated Taxes:** \$1.80

* **TOTAL PROJECT COST:** **\$29.25**

## Hardware Pinout and Schematic Mapping

| Microcontroller Pin | Connected Hardware Component | Signals / Net Label | Function Description | 
| ----- | ----- | ----- | ----- | 
| **D0 / A0** | Capacitive Soil Moisture Sensor | `SOIL_ANALOG` | Analog moisture reading (ADC input) | 
| **D1** | Red LED (via 220 Ω resistor R1) | `LED_RED` | High-risk / Alert status indicator output | 
| **D2** | Green LED (via 220 Ω resistor R2) | `LED_GREEN` | Healthy status indicator output | 
| **D3** | Push Button Switch (SW1) | `BTN_PAGE` | Display page toggle (Internal pull-up) | 
| **D4** | AHT20 Sensor & SSD1306 OLED | `I2C_SDA` | Shared I2C Data Line | 
| **D5** | AHT20 Sensor & SSD1306 OLED | `I2C_SCL` | Shared I2C Clock Line | 
| **3.3V / GND** | Capacitors C1 (100nF) & C2 (10µF) | `3V3` / `GND` | Power rail decoupling and filtering | 

## Repository Structure

```
├── Hardware/
│   ├── Plant_Care.kicad_pro       # KiCad Project File
│   ├── Plant_Care.kicad_sch       # Schematic Layout
│   ├── Plant_Care.kicad_pcb       # Two-Layer PCB Layout
│   └── Gerbers/                   # Production-ready Gerber & Drill files
├── Firmware/
│   ├── platformio.ini             # PlatformIO Board & Library Dependencies
│   └── src/
│       └── main.cpp               # Microcontroller Firmware Source Code
├── Manufacturing/
│   └── Plant_Care_Gerbers.zip     # Consolidated fabrication archive
└── README.md                      # Project documentation
```

## Firmware Setup and Compilation

### Prerequisites

1. Install [Visual Studio Code](https://code.visualstudio.com/).

2. Install the **PlatformIO IDE** extension from the VS Code Marketplace.

### Build Instructions

1. Clone or download this repository.

2. Open the `Firmware` directory in VS Code via PlatformIO.

3. Verify library declarations in `platformio.ini`:

   ```ini
   [env:seeed_xiao_rp2040]
   platform = https://github.com/maxgerhardt/platform-raspberrypi.git
   board = seeed_xiao_rp2040
   framework = arduino
   lib_deps = 
       adafruit/Adafruit AHTX0 @ ^2.0.5
       adafruit/Adafruit SSD1306 @ ^2.5.7
       adafruit/Adafruit GFX Library @ ^1.11.5
   ```

4. Run the build command via terminal or PlatformIO toolbar:

   ```bash
   pio run
   ```

5. Connect the XIAO RP2040 via USB-C and flash the binary:

   ```bash
   pio run --target upload
   ```

## References

* [KiCad Official Documentation](https://www.kicad.org/documentation/)

* [Seeed Studio XIAO RP2040 Datasheet & Guide](https://wiki.seeedstudio.com/XIAO-RP2040/)

* [PlatformIO Raspberry Pi RP2040 Integration](https://docs.platformio.org/en/latest/platforms/raspberrypi.html)

* [Adafruit AHTX0 Driver Documentation](https://github.com/adafruit/Adafruit_AHTX0)

* [Adafruit SSD1306 Display Driver](https://github.com/adafruit/Adafruit_SSD1306)