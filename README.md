# Weather Station With Arduino
Weather Station with Arduino using Wemos D1 R1

# Contents
- [Equipment](#equipment)
- [Using Boards Manager](#installing-with-boards-manager)
- [How To Use It?](#how-to-use-it)
  - [Schematic](#Schematic)
  - [Server Side](#Server-side)
- [Code Explanation](#Code)
  - [Functions List](#Functions-List)
- [Resource](#Resource)
- [Issues and support](#Issues-and-support)
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

Also It Can Help: [https://www.instructables.com/id/Programming-the-WeMos-Using-Arduino-SoftwareIDE/](https://www.instructables.com/id/Programming-the-WeMos-Using-Arduino-SoftwareIDE/)

# How To Use It?
First you need basic knowledge about C, C++ language. After that you need at least 15 tiny wire (like using for Breadboard). Then you need a Sim card, A local WiFi (for Access Point) and an important thing is you need an adaptor to provide exactly [5V and 2A](https://www.google.com/search?q=5v+and+2a+adaptor&oq=5v+and+2a+adaptor&aqs=chrome..69i57.10565j0j1&sourceid=chrome&ie=UTF-8). This is really important for SIM900 module, if you can't provide the adaptor, you wont be able to set this module.

Basically, this project built for this equipment, but if you know some thing about this you can change it easily. Because i usually code very beautiful. (Laughing :) No i'm just kidding, i'm terrible)


### Schematic
You can just use the [Photo](https://github.com/Msameim181/Weather-Station-Arduino/blob/master/Schematic/Schematic%20Final%20(Sim900)/Schematic%20Final%20(Sim900).jpg) of Schematic.

##### MicroSD
- MicroSD(GND)  -> Wemos/UNO(GND)
- MicroSD(VCC)  -> Wemos/UNO(5V)
- MicroSD(MISO) -> Wemos/UNO(D12)
- MicroSD(MOSI) -> Wemos/UNO(D11)
- MicroSD(SCK)  -> Wemos/UNO(D13)
- MicroSD(CS)   -> Wemos/UNO(D10)

##### DHT11
- DHT11(GND)    -> Wemos/UNO(GND)
- DHT11(VCC)    -> Wemos/UNO(5V)
- DHT11(DATA)   -> Wemos(GPIO2/D9)/UNO(D2)

##### SIM900
- SIM900(GND)(Yellow Line)  -> Wemos/UNO(GND)
- SIM900(GND)(UART)         -> Wemos/UNO(GND)
- SIM900(RXD)(UART)         -> Wemos(D15)/UNO(D5)
- SIM900(TXD)(UART)         -> Wemos(D14)/UNO(D4)

### Server Side
 - You should run or rent a host servet for this part.
 - First, create a DataBase and add the table with importiing option (I give you a file 'data.sql' to import the table). 
 - Then, use the name of DB and your Login info to update the DataBase Connection of a php file named by 'Functions.php'. 
 - In the end, set the php file in the 'public_html' directory of your server. 
 - And test it.
 
### Soft Ware and code
Use Arduino IDE, open the code file. First Compile it, then Upload it to your board.


# Code Explanation
A full list of Functions are available in [here](https://github.com/Msameim181/Weather-Station-Arduino/blob/master/Functions.md).

# Resource
You can try your self by testing other project.

##### DHT11-12, MicroSD
- [Complete Guide for DHT11/DHT22 Humidity and Temperature Sensor With Arduino](https://randomnerdtutorials.com/complete-guide-for-dht11dht22-humidity-and-temperature-sensor-with-arduino/)
- [SD Card Module Arduino: How to Read/Write Data](https://electropeak.com/learn/sd-card-module-read-write-arduino-tutorial/)
- [9 Arduino Compatible Temperature Sensors for Your Electronics Projects](https://randomnerdtutorials.com/9-arduino-compatible-temperature-sensors-for-your-electronics-projects/)

##### SIM900
- [Send Receive SMS & Call with SIM900 GSM Shield & Arduino](https://lastminuteengineers.com/sim900-gsm-shield-arduino-tutorial/)
- [Guide to SIM900 GSM GPRS Shield with Arduino](https://randomnerdtutorials.com/sim900-gsm-gprs-shield-arduino/)
- [Request Sensor Data via SMS using Arduino and SIM900 GSM Shield](https://randomnerdtutorials.com/request-sensor-data-sms-arduino-sim900-gsm-shield/#more-61678)
- [SIM900 SMS and Call Commands](http://www.raviyp.com/sim900-sms-call-commands/)

##### ESP8266, ESP32, Wemos
- [ESP32 DHT11/DHT22 Web Server – Temperature and Humidity using Arduino IDE](https://randomnerdtutorials.com/esp32-dht11-dht22-temperature-humidity-web-server-arduino-ide/)
- [Smart Door Lock w/ WiFi Login Page by Arduino & ESP8266](https://electropeak.com/learn/smart-door-lock-w-wifi-login-page-by-arduino-esp8266/)
- [Getting Started NodeMCU ESP8266 on Arduino IDE](https://electropeak.com/learn/nodemcu-esp8266-on-arduino-ide/)
- [ESP8266WiFi library](https://arduino-esp8266.readthedocs.io/en/latest/esp8266wifi/readme.html)
- [Establishing a Wi-Fi connection](https://tttapa.github.io/ESP8266/Chap07%20-%20Wi-Fi%20Connections.html)
- [HOW TO USE ESP8266 WIFI MODES: STATION AND ACCESS POINT](http://onlineshouter.com/use-esp8266-wifi-modes-station-access-point/)
- [A Beginner's Guide to the ESP8266](https://tttapa.github.io/ESP8266/Chap01%20-%20ESP8266.html)
- And of course, the examples in the IDE are the best.
 
# Issues and support
If you have and problem, Just Ask me or Google.
 
# License and credits
MIT License
Copyright (c) 2020 Mohammad Mahdi Samei
