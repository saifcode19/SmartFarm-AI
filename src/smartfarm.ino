/*
 * Smart Farm AI
 * ESP32 Smart Farming Controller
 *
 * Core functions:
 * - Soil moisture monitoring
 * - Automatic irrigation control
 * - DHT11 environmental monitoring
 * - TDS monitoring
 * - Relay control
 * - Blynk IoT monitoring and manual control
 *
 * IMPORTANT:
 * Replace the placeholder credentials below with your own local values.
 * Do not commit real Wi-Fi passwords or Blynk authentication tokens
 * to a public repository.
 */

#define BLYNK_TEMPLATE_ID "YOUR_BLYNK_TEMPLATE_ID"
#define BLYNK_TEMPLATE_NAME "YOUR_BLYNK_TEMPLATE_NAME"
#define BLYNK_AUTH_TOKEN "YOUR_BLYNK_AUTH_TOKEN"

#include <WiFi.h>
#include <BlynkSimpleEsp32.h>
#include <DHT.h>

char ssid[] = "YOUR_WIFI_SSID";
char pass[] = "YOUR_WIFI_PASSWORD";

/* =========================
   Sensor Configuration
   ========================= */

#define DHTPIN YOUR_DHT_PIN
#define DHTTYPE DHT11

DHT dht(DHTPIN, DHTTYPE);

#define SOIL_PIN YOUR_SOIL_SENSOR_PIN
#define TDS_PIN YOUR_TDS_SENSOR_PIN

/* =========================
   Relay Configuration
   ========================= */

#define WATER_RELAY_PIN YOUR_WATER_RELAY_PIN
#define FERTILIZER_RELAY_PIN YOUR_FERTILIZER_RELAY_PIN

/* =========================
   Indicator Configuration
   ========================= */

#define LED_LOW YOUR_LOW_MOISTURE_LED_PIN
#define LED_HIGH YOUR_HIGH_MOISTURE_LED_PIN

/* =========================
   Soil Calibration
   ========================= */

const int WET_ADC = 1500;
const int DRY_ADC = 3500;

/* =========================
   Irrigation Thresholds
   ========================= */

const int PUMP_ON_THRESHOLD = 40;
const int PUMP_OFF_THRESHOLD = 80;

/* =========================
   Blynk Virtual Pins
   ========================= */

#define VPIN_SOIL V0
#define VPIN_RELAY V1
#define VPIN_MANUAL V2

/* =========================
   System Variables
   ========================= */

bool manualPumpControl = false;
bool pumpState = false;

BlynkTimer timer;

/* =========================
   Soil Moisture Function
   ========================= */

int readSoilMoisture()
{
    int adcValue = analogRead(SOIL_PIN);

    int moisture = map(
        adcValue,
        DRY_ADC,
        WET_ADC,
        0,
        100
    );

    moisture = constrain(moisture, 0, 100);

    return moisture;
}

/* =========================
   Pump Control
   ========================= */

void setPump(bool state)
{
    pumpState = state;

    /*
     * Adjust HIGH/LOW if your relay module
     * uses inverted logic.
     */
    digitalWrite(WATER_RELAY_PIN, state ? HIGH : LOW);

    Blynk.virtualWrite(VPIN_RELAY, state ? 1 : 0);
}

/* =========================
   Blynk Manual Control
   ========================= */

BLYNK_WRITE(VPIN_MANUAL)
{
    manualPumpControl = param.asInt();

    if (manualPumpControl)
    {
        setPump(true);
    }
    else
    {
        setPump(false);
    }
}

/* =========================
   Sensor Monitoring
   ========================= */

void readSensors()
{
    int soilMoisture = readSoilMoisture();

    float temperature = dht.readTemperature();
    float humidity = dht.readHumidity();

    int tdsRaw = analogRead(TDS_PIN);

    Serial.println("-----------------------------");

    Serial.print("Soil Moisture: ");
    Serial.print(soilMoisture);
    Serial.println("%");

    Serial.print("Temperature: ");
    Serial.print(temperature);
    Serial.println(" C");

    Serial.print("Humidity: ");
    Serial.print(humidity);
    Serial.println("%");

    Serial.print("TDS Raw: ");
    Serial.println(tdsRaw);

    /* =========================
       Automatic Irrigation
       ========================= */

    if (!manualPumpControl)
    {
        if (soilMoisture < PUMP_ON_THRESHOLD)
        {
            setPump(true);
        }
        else if (soilMoisture >= PUMP_OFF_THRESHOLD)
        {
            setPump(false);
        }
    }

    /* =========================
       LED Indication
       ========================= */

    if (soilMoisture < 40)
    {
        digitalWrite(LED_LOW, HIGH);
        digitalWrite(LED_HIGH, LOW);
    }
    else if (soilMoisture > 45)
    {
        digitalWrite(LED_LOW, LOW);
        digitalWrite(LED_HIGH, HIGH);
    }

    /* =========================
       Blynk Monitoring
       ========================= */

    Blynk.virtualWrite(VPIN_SOIL, soilMoisture);
}

/* =========================
   Setup
   ========================= */

void setup()
{
    Serial.begin(115200);

    pinMode(WATER_RELAY_PIN, OUTPUT);
    pinMode(FERTILIZER_RELAY_PIN, OUTPUT);

    pinMode(LED_LOW, OUTPUT);
    pinMode(LED_HIGH, OUTPUT);

    digitalWrite(WATER_RELAY_PIN, LOW);
    digitalWrite(FERTILIZER_RELAY_PIN, LOW);

    digitalWrite(LED_LOW, LOW);
    digitalWrite(LED_HIGH, LOW);

    dht.begin();

    Blynk.begin(
        BLYNK_AUTH_TOKEN,
        ssid,
        pass
    );

    timer.setInterval(5000L, readSensors);
}

/* =========================
   Main Loop
   ========================= */

void loop()
{
    Blynk.run();
    timer.run();
}
