
#include <Arduino.h>
#include <Wire.h>
#include <Adafruit_AHTX0.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

// ---------------- PIN CONFIGURATION ----------------

#define SOIL_PIN   A0
#define RED_LED    D1
#define GREEN_LED  D2
#define BUTTON_PIN D3

// ---------------- OLED CONFIGURATION ----------------

#define SCREEN_WIDTH  128
#define SCREEN_HEIGHT 64
#define OLED_RESET    -1
#define OLED_ADDRESS  0x3C

// ---------------- SOIL CALIBRATION ----------------

// Initial example values for a 12-bit ADC.
// Calibrate these using your actual moisture sensor.
#define SOIL_DRY_VALUE  3200
#define SOIL_WET_VALUE  1500

// ---------------- ALERT THRESHOLDS ----------------

#define DRY_SOIL_LIMIT       30
#define HIGH_TEMP_LIMIT      35.0
#define LOW_HUMIDITY_LIMIT   30.0

// ---------------- OBJECTS ----------------

Adafruit_AHTX0 aht;

Adafruit_SSD1306 display(
    SCREEN_WIDTH,
    SCREEN_HEIGHT,
    &Wire,
    OLED_RESET
);

// ---------------- SENSOR VARIABLES ----------------

int soilRawValue = 0;
int soilMoisture = 0;

float temperature = 0.0;
float humidity = 0.0;

bool ahtAvailable = false;
bool oledAvailable = false;

bool alertActive = false;

// ---------------- TIMING VARIABLES ----------------

unsigned long lastSensorRead = 0;
unsigned long lastDisplayUpdate = 0;
unsigned long lastDebounceTime = 0;

const unsigned long SENSOR_INTERVAL = 2000;
const unsigned long DISPLAY_INTERVAL = 500;
const unsigned long DEBOUNCE_DELAY = 50;

// ---------------- BUTTON VARIABLES ----------------

int currentButtonState = HIGH;
int lastButtonReading = HIGH;

int displayPage = 0;

// ---------------- FUNCTION DECLARATIONS ----------------

void readSensors();
void calculateSoilMoisture();
void updateAlerts();
void updateLEDs();
void checkButton();
void updateDisplay();
void printSerialData();

// =====================================================
// SETUP
// =====================================================

void setup() {

    Serial.begin(115200);

    // Configure pins
    pinMode(SOIL_PIN, INPUT);
    pinMode(RED_LED, OUTPUT);
    pinMode(GREEN_LED, OUTPUT);
    pinMode(BUTTON_PIN, INPUT_PULLUP);

    // Set ADC resolution
    analogReadResolution(12);

    // Initialize I2C
    Wire.begin();

    // Initialize LEDs
    digitalWrite(RED_LED, LOW);
    digitalWrite(GREEN_LED, LOW);

    // Initialize OLED
    oledAvailable = display.begin(
        SSD1306_SWITCHCAPVCC,
        OLED_ADDRESS
    );

    if (oledAvailable) {

        display.clearDisplay();
        display.setTextSize(1);
        display.setTextColor(SSD1306_WHITE);
        display.setCursor(0, 10);

        display.println("SMART PLANT CARE");
        display.println();
        display.println("Initializing...");
        display.display();

    } else {

        Serial.println("ERROR: OLED not detected!");
    }

    // Initialize AHT20
    ahtAvailable = aht.begin();

    if (ahtAvailable) {

        Serial.println("AHT20 initialized successfully!");

    } else {

        Serial.println("ERROR: AHT20 not detected!");
    }

    Serial.println();
    Serial.println("SMART PLANT CARE ASSISTANT");
    Serial.println("--------------------------");
    Serial.println("System started.");

    delay(1500);

    readSensors();
    updateAlerts();
    updateLEDs();
    updateDisplay();
    printSerialData();
}

// =====================================================
// MAIN LOOP
// =====================================================

void loop() {

    unsigned long currentTime = millis();

    // Read sensors periodically
    if (currentTime - lastSensorRead >= SENSOR_INTERVAL) {

        lastSensorRead = currentTime;

        readSensors();
        updateAlerts();
        updateLEDs();
        printSerialData();
    }

    // Check push button
    checkButton();

    // Refresh OLED periodically
    if (currentTime - lastDisplayUpdate >= DISPLAY_INTERVAL) {

        lastDisplayUpdate = currentTime;

        updateDisplay();
    }
}

// =====================================================
// READ SENSORS
// =====================================================

void readSensors() {

    // Read soil moisture sensor
    soilRawValue = analogRead(SOIL_PIN);

    calculateSoilMoisture();

    // Read AHT20 temperature and humidity
    if (ahtAvailable) {

        sensors_event_t humidityEvent;
        sensors_event_t temperatureEvent;

        aht.getEvent(
            &humidityEvent,
            &temperatureEvent
        );

        temperature = temperatureEvent.temperature;
        humidity = humidityEvent.relative_humidity;
    }
}

// =====================================================
// CALCULATE SOIL MOISTURE PERCENTAGE
// =====================================================

void calculateSoilMoisture() {

    // Dry reading maps to 0%.
    // Wet reading maps to 100%.

    soilMoisture = map(
        soilRawValue,
        SOIL_DRY_VALUE,
        SOIL_WET_VALUE,
        0,
        100
    );

    soilMoisture = constrain(
        soilMoisture,
        0,
        100
    );
}

// =====================================================
// CHECK ALERT CONDITIONS
// =====================================================

void updateAlerts() {

    bool soilIsDry =
        soilMoisture < DRY_SOIL_LIMIT;

    bool temperatureIsHigh =
        ahtAvailable &&
        temperature > HIGH_TEMP_LIMIT;

    bool humidityIsLow =
        ahtAvailable &&
        humidity < LOW_HUMIDITY_LIMIT;

    bool sensorError = !ahtAvailable;

    alertActive =
        soilIsDry ||
        temperatureIsHigh ||
        humidityIsLow ||
        sensorError;
}

// =====================================================
// CONTROL LED INDICATORS
// =====================================================

void updateLEDs() {

    if (alertActive) {

        digitalWrite(RED_LED, HIGH);
        digitalWrite(GREEN_LED, LOW);

    } else {

        digitalWrite(RED_LED, LOW);
        digitalWrite(GREEN_LED, HIGH);
    }
}

// =====================================================
// PUSH BUTTON CONTROL
// =====================================================

void checkButton() {

    int reading = digitalRead(BUTTON_PIN);

    if (reading != lastButtonReading) {

        lastDebounceTime = millis();
    }

    if ((millis() - lastDebounceTime) > DEBOUNCE_DELAY) {

        if (reading != currentButtonState) {

            currentButtonState = reading;

            // Button pressed
            if (currentButtonState == LOW) {

                displayPage = !displayPage;

                if (oledAvailable) {
                    updateDisplay();
                }
            }
        }
    }

    lastButtonReading = reading;
}

// =====================================================
// OLED DISPLAY
// =====================================================

void updateDisplay() {

    if (!oledAvailable) {
        return;
    }

    display.clearDisplay();

    display.setTextSize(1);
    display.setTextColor(SSD1306_WHITE);

    // Header
    display.setCursor(0, 0);
    display.println("SMART PLANT CARE");

    display.drawLine(0, 10, 127, 10, SSD1306_WHITE);

    // PAGE 1: SOIL MOISTURE
    if (displayPage == 0) {

        display.setCursor(0, 16);
        display.println("SOIL MOISTURE");

        display.setTextSize(2);
        display.setCursor(0, 29);
        display.print(soilMoisture);
        display.print("%");

        display.setTextSize(1);
        display.setCursor(0, 53);

        if (soilMoisture < DRY_SOIL_LIMIT) {

            display.println("Status: DRY!");

        } else {

            display.println("Status: OK");
        }
    }

    // PAGE 2: TEMPERATURE AND HUMIDITY
    else {

        display.setCursor(0, 16);

        if (ahtAvailable) {

            display.print("Temperature: ");
            display.print(temperature, 1);
            display.println(" C");

            display.println();

            display.print("Humidity: ");
            display.print(humidity, 1);
            display.println(" %");

            display.setCursor(0, 53);

            if (alertActive) {
                display.println("Check plant conditions");
            } else {
                display.println("Environment: OK");
            }

        } else {

            display.println("AHT20 unavailable");
            display.println("Check sensor wiring");
        }
    }

    display.display();
}

// =====================================================
// SERIAL MONITOR OUTPUT
// =====================================================

void printSerialData() {

    Serial.println();
    Serial.println("----- PLANT STATUS -----");

    Serial.print("Soil Raw Value: ");
    Serial.println(soilRawValue);

    Serial.print("Soil Moisture: ");
    Serial.print(soilMoisture);
    Serial.println("%");

    if (ahtAvailable) {

        Serial.print("Temperature: ");
        Serial.print(temperature);
        Serial.println(" C");

        Serial.print("Humidity: ");
        Serial.print(humidity);
        Serial.println(" %");

    } else {

        Serial.println("AHT20: Sensor unavailable");
    }

    Serial.print("Plant Status: ");

    if (alertActive) {

        Serial.println("ATTENTION REQUIRED");

    } else {

        Serial.println("NORMAL");
    }

    Serial.println("------------------------");
}
