
# Smart OxyBeat Monitor

An IoT-based Pulse Oximeter for Real-Time Health Monitoring  
**Created by:** Antony Jerin K, Sri Shanmuga Vignesh M, Petchi Prabakaran E  
**Mentor:** Er. S. Muguntha Mala

---

## 🔍 Project Overview

Smart OxyBeat Monitor is a low-cost, IoT-enabled pulse oximeter that measures heart rate and oxygen saturation (SpO₂) using the MAX30100 sensor. The system is powered by an ESP32 microcontroller, displays live data on an OLED screen, and transmits readings to a mobile device using the Blynk app. Designed especially for home care, elderly patients, and physically challenged individuals, this project enables continuous remote monitoring of vital signs.

---

## 🧠 How It Works

1. **Sensor Reading:**  
   The MAX30100 emits red and infrared light to measure heart rate and SpO₂ from the user’s fingertip.

2. **Data Processing:**  
   The ESP32 receives the sensor’s raw data, processes it to extract clean values, and prepares it for display and transmission.

3. **Display Output:**  
   A 0.96-inch OLED screen connected to the ESP32 shows real-time heart rate and SpO₂ readings.

4. **IoT Integration (Blynk):**  
   The ESP32 sends the processed data to the Blynk mobile app via Wi-Fi. Users can monitor their vitals remotely on their smartphones.

5. **Health Alerts:**  
   Alerts can be programmed in the Blynk app to notify users or caretakers if the values fall below safe levels.

---

## 🛠️ Components Used

- ESP32-WROOM-32 Development Board  
- MAX30100 Pulse Oximeter and Heart Rate Sensor  
- 0.96" I2C OLED Display  
- Wi-Fi connectivity (via ESP32)  
- Blynk IoT Mobile App  
- Power source (Battery or USB)

---

## 📚 Libraries Used

The following libraries are required for this project:

- **Adafruit GFX** – For handling graphics on the OLED screen  
- **Adafruit SSD1306** – OLED display driver  
- **MAX30100_PulseOximeter** – For interfacing with the MAX30100 sensor  
- **WiFi** – For ESP32 Wi-Fi capability  
- **BlynkSimpleEsp32** – For connecting ESP32 to the Blynk IoT platform  

> Install all the libraries via **Arduino IDE → Sketch → Include Library → Manage Libraries**

### 📄 Library File Snippet

```cpp
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
```

---

## 🔌 Pin Connections

| Component       | ESP32 Pin         | Notes                       |
|----------------|-------------------|-----------------------------|
| MAX30100       | SDA → GPIO 21     | I2C Data Line               |
|                | SCL → GPIO 22     | I2C Clock Line              |
| OLED Display   | SDA → GPIO 21     | Shared with MAX30100 (I2C) |
|                | SCL → GPIO 22     | Shared with MAX30100 (I2C) |
| Power          | 3.3V / GND        | Common power for OLED & sensor |

> Note: Both OLED and MAX30100 use I2C, so they share the same SDA and SCL lines.

---

## 💡 Applications

- **Home Health Monitoring**  
- **Domiciliary Care for the Elderly**  
- **Post-Surgery Recovery**  
- **Remote Vital Sign Tracking**  
- **Alert Notifications for Low Oxygen Levels**

---
