#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include <DHT.h>

// --- Pin Definitions (ESP-32S NodeMCU) ---
#define DHTPIN 4           // DHT11 Data connected to P4 (GPIO 4)
#define DHTTYPE DHT11      // Defining the sensor type as DHT11
#define MQ135_PIN 36       // MQ135 Analog Out connected to SVP (GPIO 36)
#define BUZZER_PIN 12      // Buzzer positive connected to P12 (GPIO 12)

// --- Safety Thresholds ---
#define AQI_THRESHOLD 800  // The analog value at which the alarm triggers

// --- OLED Setup ---
#define SCREEN_WIDTH 128 
#define SCREEN_HEIGHT 64 
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, -1);

// Initialize the DHT sensor object
DHT dht(DHTPIN, DHTTYPE);

void setup() {
  Serial.begin(115200);

  // Initialize the I2C bus for the OLED
  Wire.begin(); 

  // Set the buzzer pin as an output
  pinMode(BUZZER_PIN, OUTPUT);
  digitalWrite(BUZZER_PIN, LOW); // Ensure it starts OFF

  // Start the DHT sensor
  dht.begin();

  // Start the OLED Display (Address 0x3C)
  if(!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) {
    Serial.println(F("SSD1306 allocation failed. Check OLED wiring!"));
    for(;;); // Stop here if the screen fails
  }
  
  // --- Startup Message & Author ---
  display.clearDisplay();
  display.setTextSize(1);
  display.setTextColor(SSD1306_WHITE);
  display.setCursor(10, 10);
  display.println(F("AeroGuard System"));
  display.setCursor(10, 30);
  display.println(F("By: S. Pranesh Kumaran")); 
  display.display();
  delay(3000); 
}

void loop() {
  // 1. Read Gas Sensor
  int rawGasValue = analogRead(MQ135_PIN); 
  
  // 2. Read Climate Data
  float temp = dht.readTemperature();
  float hum = dht.readHumidity();

  // Safety Check: Verify DHT readings
  bool dhtValid = true;
  if (isnan(temp) || isnan(hum)) {
    Serial.println(F("Failed to read from DHT sensor!"));
    dhtValid = false;
  } else {
    Serial.print(F("Temp: ")); Serial.print(temp); Serial.print(F("C | "));
    Serial.print(F("Humidity: ")); Serial.print(hum); Serial.print(F("% | "));
  }
  
  Serial.print(F("Gas Level: ")); Serial.println(rawGasValue);

  // 3. Prepare Display
  display.clearDisplay();
  display.setTextColor(SSD1306_WHITE);

  // 4. Threshold Logic & Alarm
  if (rawGasValue > AQI_THRESHOLD) {
    digitalWrite(BUZZER_PIN, HIGH); // DANGER: Buzzer ON
    display.setTextSize(2); 
    display.setCursor(0, 0);
    display.println(F("WARNING!"));
  } else {
    digitalWrite(BUZZER_PIN, LOW);  // SAFE: Buzzer OFF
    display.setTextSize(2);
    display.setCursor(0, 0);
    display.println(F("AQI SAFE"));
  }

  // 5. Display Live Sensor Values
  display.setTextSize(1);
  display.setCursor(0, 25);
  display.print(F("Gas Level: "));
  display.print(rawGasValue);

  display.setCursor(0, 40);
  if (!dhtValid) {
    display.print(F("DHT Error!"));
  } else {
    display.print(F("Temp     : "));
    display.print(temp);
    display.print(F(" C"));
    display.setCursor(0, 52);
    display.print(F("Humidity : "));
    display.print(hum);
    display.print(F(" %"));
  }

  // Push graphics to screen
  display.display();
  delay(2000); // 2-second refresh rate
}