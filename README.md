AeroGuard: IoT Smart Air Quality Sentinel 🌍💨

AeroGuard is a real-time IoT air quality monitor powered by the ESP32. It actively tracks AQI, temperature, and humidity using MQ135 and DHT11 sensors. Featuring a live OLED display, it automatically triggers an audible buzzer alarm if hazardous gas levels (like smoke or CO2) exceed safety thresholds, ensuring proactive environmental safety.

🚀 Features

Real-time Air Quality Monitoring: Utilizes an MQ-series gas sensor for broad-spectrum pollutant detection.

Climate Tracking: Measures temperature and humidity using a DHT11 sensor.

Instant Visual Feedback: Live data visualization on a 0.96" I2C OLED display.

Automated Safety Alarm: Instantly triggers a piezo buzzer when AQI exceeds the threshold (set to 800).

Fault Tolerant: Built-in code logic prevents system crashes if environmental sensors temporarily disconnect.

🛠️ Hardware Requirements

ESP-32S NodeMCU (Microcontroller)

MQ135 Gas Sensor (or similar MQ-series analog sensor)

DHT11 (Temperature & Humidity Sensor)

0.96" SSD1306 OLED Display (I2C interface)

Piezo Buzzer

Breadboard and Jumper Wires

🔌 Circuit & Wiring Guide

Make sure to check component voltages! (MQ135 requires 5V, DHT11 and OLED require 3.3V).

Component                      Pin                          ESP32 Pin Connection   


MQ135 Gas Sensor               VCC / GND                       5V / GND
                               
                               A0 (Analog Out)                 SVP (GPIO 36)

DHT11 Sensor                   VCC / GND                       3V3 / GND

                                DATA                           P4 (GPIO 4)

OLED Display                   VCC / GND                       3V3 / GND

                                SCL (Clock)                    P22 (GPIO 22)
              
                                SDA (Data)                     P21 (GPIO 21)

Buzzer                         Positive (+)                    P12 (GPIO 12)

                                Negative (-)                    GND
                                

💻 Software & Installation

This project was programmed using the Arduino IDE.

Required Libraries:
Go to Sketch -> Include Library -> Manage Libraries... and install:

Adafruit GFX Library

Adafruit SSD1306

DHT sensor library (by Adafruit)

Running the Code:

Clone this repository or download AeroGuard.ino.

Open the file in Arduino IDE.

Select your ESP32 board and COM port.

Hit Upload.

📊 MATLAB Simulation

This repository also includes a MATLAB simulation script (AeroGuard_Simulation.m). It models the logic of the ESP32 in a simulated environment, demonstrating how the system reacts to a sudden "gas leak" data spike over a 60-second test period.
