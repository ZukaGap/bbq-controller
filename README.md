🌡️ ESP32-S3 Temperature & Fan Monitor with LAN Web Dashboard
A DIY IoT project using an ESP32-S3, MAX6675 K-type thermocouple, 4x20 I2C LCD, and 3-wire fan, providing:

✅ Real-time temperature monitoring
✅ Automatic fan control based on temperature
✅ LAN-accessible web interface (no internet required)
✅ Live website updates without page reload (AJAX)
✅ LCD displays Wi-Fi status, IP address, fan state, and temperature

⚡ Features
Connects to home Wi-Fi network

Displays live temperature and fan status via browser (phone or PC)

Auto-starts fan when temperature drops below 200°C

Stops fan when temperature reaches 350°C

LCD shows:

Wi-Fi connection status

Device IP address for browser access

Fan status (ON/OFF)

Current temperature in °C

🛠️ Hardware Required
ESP32-S3 development board

MAX6675 K-type thermocouple module

4x20 I2C LCD Display

3-wire fan (Red = VCC, Black = GND, Yellow = Tach, optional)

NPN Transistor (e.g., 2N2222) or MOSFET for fan control

Diode (1N4007) for back EMF protection

Optional: External 5V or 12V fan power supply

🔌 Wiring Summary
Component ESP32 Pin / Connection
MAX6675 SO GPIO 19
MAX6675 CS GPIO 5
MAX6675 SCK GPIO 18
LCD SDA GPIO 8 (customizable)
LCD SCL GPIO 9 (customizable)
FAN Control GPIO 15 → Transistor Base
Fan Red +5V or 12V supply
Fan Black Transistor Collector → GND
Fan Yellow Optional (for RPM reading)

🌐 Web Interface
Access from any browser on the same LAN:
http://<ESP32_IP>

Live temperature and fan status update every 2 seconds

No need to refresh the page

Future Enhancements: Manual fan control via web

📦 Project Structure
bash
Copy
Edit
TempWebMonitor/
├── TempWebMonitor.ino → Main project file
├── constants.h → Pin definitions and settings
├── secrets.h → Wi-Fi credentials
├── temperatureModule.cpp/h → Temperature reading logic
├── fanController.cpp/h → Fan control logic
├── displayModule.cpp/h → LCD display management
├── webServerModule.cpp/h → LAN website & AJAX handling
🧩 Libraries Used
ESP32 Arduino Core

MAX6675 Library

LiquidCrystal I2C or ESP32-compatible equivalent

Built-in WiFi and WebServer libraries for ESP32

🚀 Getting Started
Install ESP32 board support via Arduino IDE

Install required libraries via Library Manager

Edit secrets.h with your Wi-Fi credentials

Wire components according to the wiring summary

Upload sketch to your ESP32-S3 (hold BOOT button if needed)

Open Serial Monitor to view device IP address

Access the web interface from your phone or PC browser

🛡️ Disclaimer
Fan control requires proper use of transistors or MOSFETs for safe operation

Always double-check wiring for your fan voltage and current specifications

Web interface works within your local LAN only — no external internet required

💡 Future Improvements
RPM monitoring using the fan's yellow tachometer wire

Manual fan override control via web interface

ESP32 Access Point mode for standalone operation

WebSocket real-time updates for smoother live data

🎯 Contributions
Pull requests welcome! Feel free to suggest features, report issues, or extend the project.
