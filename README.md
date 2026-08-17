<img width="970" height="761" alt="Screenshot 2026-08-17 192302" src="https://github.com/user-attachments/assets/66ba96b0-1646-4098-aae6-b665aa8215ab" />

A desk bot that is made using XIAO ESP32S3 and a NEO-6M GPS and a 1.3inch OLED. HIs name is alfred and he uses the GPS instead of an IMU and rtc time module to detect shake and time. When I shake it the speed goes up high and GPS detects it , this makes the desk companion show some fun animations, like when someone is feeling sick then dizzy then getting better and finally it shows a clock. The time, on this clock comes from the GPS UTC. itll use a 3d printed enclosure from my previous project

# Wiring Diagram 
<img width="1488" height="1061" alt="Screenshot 2026-08-16 114726" src="https://github.com/user-attachments/assets/35292611-4fc5-447d-96e3-583bdeb5bba7" />

# Faces 
<img width="3120" height="4160" alt="faces" src="https://github.com/user-attachments/assets/cbd511da-7612-4d63-ae0f-9c8bb02b2fee" />

# BOM 
| Name | Purpose | Quantity | Total Cost (USD) | Link | Distributor |
| :--- | :--- | :---: | :---: | :---: | :--- |
| Wires | To make connections | 2 | 0.38 | [Product Link](https://robu.in/product/24awg-single-core-teflon-wire-black/) | Robu.in |
| NEO-6M GPS Module | Global Positioning System Module. It measures speed using latitude and longitude data by connecting to various satellites | 1 | 2.70 | [Product Link](https://robu.in/product/neo-6m-gps-module-with-eprom-normal-quality/) | Robu.in |
| 1.3 Inch I2C OLED Display Module | To show speed, time, distance, and other various telemetry | 1 | 2.90 | [Product Link](https://robu.in/product/1-3-inch-i2c-oled-display-module-4-pin-white/) | Robu.in |
| Seeed Studio XIAO ESP32-S3 | MCU, It is the brain of my speedometer | 1 | 9.66 | [Product Link](https://robu.in/product/seeed-studio-xiao-esp32s3-2-4ghz-wifi-ble-5-0) | Robu.in |
