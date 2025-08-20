# ESP32 Wi-Fi Probe Request Scanner

This project implements a **Wi-Fi probe request scanner** on the ESP32.  
It listens for probe requests from nearby Wi-Fi devices and extracts their **MAC addresses**, which are then sent to a [remote server](https://github.com/Rev0lt0x33/ESP32_Scanner_UserApp).  

The device also includes a built-in **configuration web server** that allows you to set the destination server address and other parameters without reflashing.

---

## Features
-  Captures **probe requests** packets
-  Gets **MAC addresses** of detected devices from packets
-  Sends data to a **remote server** 
-  Built-in **web interface** for configuration (server URL, credentials, etc.)  
-  Stores settings in non-volatile memory (NVS/EEPROM)  

---

## Disclaimer
The system only collects information that is already present in the standard  
**IEEE 802.11 probe request frame**, such as:
- Device MAC address  
- Timestamp of detection  
