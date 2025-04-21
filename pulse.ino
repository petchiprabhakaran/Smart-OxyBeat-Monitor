#define BLYNK_TEMPLATE_ID "TMPL3drmAR_Yg"
#define BLYNK_TEMPLATE_NAME "pulse oximeter"
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include "MAX30100_PulseOximeter.h"

// Blynk Setup
#define BLYNK_PRINT Serial
#include <WiFi.h>
#include <BlynkSimpleEsp32.h>

#define REPORTING_PERIOD_MS 100

// Blynk credentials
char auth[] = "yFuQjw_hwpUOjxSY_uj0wUkEF6g74CUa";
char ssid[] = "Prabu";
char pass[] = "12345678";

PulseOximeter max_sensor;
uint32_t lastReportTime = 0;
Adafruit_SSD1306 OLED = Adafruit_SSD1306(128, 32, &Wire);
bool sendDataFlag = false;  // Flag for V0 switch
unsigned long lastAlertTime = 0; // For cooldown

// V0 handler
BLYNK_WRITE(V0) {
  sendDataFlag = param.asInt(); // 1 = ON, 0 = OFF
}

void onBeatDetected() {
  Serial.println("Beat!");
}

void setup() {
  Serial.begin(115200);
  
  // OLED Init
  OLED.begin(SSD1306_SWITCHCAPVCC, 0x3C);
  OLED.display();
  OLED.clearDisplay();
  OLED.setTextSize(2);
  OLED.setTextColor(SSD1306_WHITE);
  OLED.setCursor(0, 0);
  OLED.display();
  delay(1000);

  // Blynk Init
  Blynk.begin(auth, ssid, pass);

  // Sensor Init
  Serial.print("Initializing pulse oximeter..");
  if (!max_sensor.begin()) {
    Serial.println("FAILED");
    while (1);
  } else {
    Serial.println("SUCCESS");
  }

  max_sensor.setOnBeatDetectedCallback(onBeatDetected);
}

void loop() {
  Blynk.run();
  max_sensor.update();

  if (millis() - lastReportTime > REPORTING_PERIOD_MS) {
    float heartRate = max_sensor.getHeartRate();
    uint8_t spO2 = max_sensor.getSpO2();

    // Display on OLED
    OLED.clearDisplay();
    OLED.setCursor(0, 0);
    OLED.print("H:");
    OLED.print(heartRate);
    OLED.println("bpm");
    OLED.print("SpO2:");
    OLED.print(spO2);
    OLED.println("%");
    OLED.display();

    // Send to Blynk
    if (sendDataFlag) {
      Blynk.virtualWrite(V1, heartRate);
      Blynk.virtualWrite(V2, spO2);

      // 🟡 EVENT ALERT — Only if BPM is below 50
      if (heartRate < 50 && heartRate > 20) {
        // Cooldown: only trigger every 10 seconds
        if (millis() - lastAlertTime > 10000) {
          Blynk.logEvent("low_heart_rate");
          lastAlertTime = millis();
        }
      }
    }

    lastReportTime = millis();
  }
}