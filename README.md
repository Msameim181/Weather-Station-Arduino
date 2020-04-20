# Weather-Station-Arduino
Weather Station with Arduino using Wemos D1 R1

# Contents
- [Equipment](#equipment)
- [Using Boards Manager](#installing-with-boards-manager)
- [Documentation](#documentation)
- [Issues and support](#issues-and-support)
- [Contributing](#contributing)  
- [License and credits](#license-and-credits)   

# Equipment:
- DHT11 (temperature and humidity) Sensor (You can use DHT22 as well)
- [Micro SD module (we use Micro-SD/TF)](https://github.com/Msameim181/Weather-Station-Arduino/blob/master/Equipment/Micro-SD-TF.jpg) 
- [Wemos D1 R1 (Old board, Microprocessor: ESP8266EX, Compatible with Arduino)](https://github.com/Msameim181/Weather-Station-Arduino/blob/master/Equipment/WeMos-D1-R1-Board-2.jpg)
- [SIM900 GSM/GPRS (Quad-Band)](https://github.com/Msameim181/Weather-Station-Arduino/blob/master/Equipment/SIM900-GSM-GPRS-2.jpg)
- Breadboard
- 15 Wire
- A MicroUSB Cable

P.S. : You can use Wemos D1 R2 instead R1 but it is a little different in pins, if have any problems just ask [Google](https://www.Google.com/)

### Installing with Boards Manager

Starting with 1.6.4, Arduino allows installation of third-party platform packages using Boards Manager. We have packages available for Windows, Mac OS, and Linux (32 and 64 bit).

- Install the current upstream Arduino IDE at the 1.8.7 level or later. The current version is on the [Arduino website](https://www.arduino.cc/en/main/software).
- Start Arduino and open the Preferences window.
- Enter ```https://arduino.esp8266.com/stable/package_esp8266com_index.json``` into the *Additional Board Manager URLs* field. You can add multiple URLs, separating them with commas.
- Open Boards Manager from Tools > Board menu and install *esp8266* platform (and don't forget to select your ESP8266 board from Tools > Board menu after installation).

#### Latest release [![Latest release](https://img.shields.io/github/release/esp8266/Arduino.svg)](https://github.com/esp8266/Arduino/releases/latest/)
Boards manager link: `https://arduino.esp8266.com/stable/package_esp8266com_index.json`

Documentation: [https://arduino-esp8266.readthedocs.io/en/2.6.3/](https://arduino-esp8266.readthedocs.io/en/2.6.3/)
Resource: [https://github.com/esp8266/Arduino](https://github.com/esp8266/Arduino)

# How To Use It?
First you need basic knowledge about C, C++ language. After that you need at least 15 tiny wire (like using for Breadboard). Then you need a Sim card, A local WiFi (for Access Point) and an important thing is you need an adaptor to provide exactly 5V and 2A. This is really important for SIM900 module, if you can't provide the adaptor, you wont be able to set this module.

Basically, this project built for this equipment, but if you know some thing about this you can change it easily. Because i usually code very beautiful. (Laughing :) No i'm just kidding, i'm terrible)
