#include <SPI.h>
#include <SD.h>
#include <DHT.h>
#include <TimeLib.h>
#include <Arduino.h>
#include <WiFiClient.h>
#include <ESP8266WiFi.h>
#include <ESPAsyncTCP.h>
#include <ESPAsyncWebServer.h>
#include <Adafruit_Sensor.h>
#include <ESP8266HTTPClient.h>
#include <SoftwareSerial.h>

// SD Card
File myFile;
// Time

unsigned long TimeFrame;
unsigned long DHT_Time;
unsigned long SIM_Time;
// SIM900
SoftwareSerial SIM900(4, 5);
char incomingChar;
String Phone;
// DHT11
#define DHTPIN 2
#define DHTTYPE DHT11
DHT dht(DHTPIN, DHTTYPE);
float Humidity = 0;
float Temperature = 0;
// Async Web Server
AsyncWebServer server(80);
// Server & Host
// const char *host = "http://station0011.cloudsite.ir/";
// WiFi
#ifndef STASSID
#define STASSID "N@%Namei"
#define STAPSK "!qazxsw@#edcvfr$"
#endif
// REPLACE WITH YOUR NETWORK CREDENTIALS
const char *ssid = STASSID;
const char *password = STAPSK;
// WiFi LED
const int led = LED_BUILTIN;
// HTML Web Page
const char index_html[] PROGMEM = R"rawliteral(
    <!DOCTYPE html>
    <html lang="en">
    <head>
        <meta charset="UTF-8">
        <meta name="viewport" content="width=device-width, initial-scale=1.0">
        <title>Station 11</title>
        <link rel="stylesheet" href="https://stackpath.bootstrapcdn.com/bootstrap/4.4.1/css/bootstrap.min.css" 
            integrity="sha384-Vkoo8x4CGsO3+Hhxv8T/Q5PaXtkKtu6ug5TOeNV6gBiFeWPGFN9MuhOf23Q9Ifjh" crossorigin="anonymous">
        <link rel='stylesheet' href='https://use.fontawesome.com/releases/v5.7.2/css/all.css'
            integrity='sha384-fnmOCqbTlWIlj8LyTjo7mOUStjsKC4pOpQbqyi7RrhN7udi9RwhKkMHpvLbHG9Sr' crossorigin='anonymous'>
        <style>
            #information{
                /* display: none; */
            }
            .simple-grid {
                margin: 0 auto
            }
            .simple-btn {
                background: #232323;
                color : #fff
            }
            .simple-btn:hover {
                color : #fff !important
            }
            .form-control:focus {
                color: #495057;
                background-color: #fff;
                border-color: #cecece;
                outline: 0;
                box-shadow: 0 0 0 0.2rem #d4d4d4
            }
            @media (min-width: 650px) {
                .simple-grid {
                    width : 600px;
                }
            }
            @media (max-width: 650px) {
                .simple-grid {
                    width: 90%;
                }
                #d-table {
                    /* padding-left: 0px; */

                }
            }
            .d-block{
                font-size: 1.2rem;
            }
            i{
                font-size: 1.8rem;
            }
        </style>
    </head>
    <body class="simple-grid">
        <div class="container-scroller">
            <div class="container-fluid page-body-wrapper">
                <div class="main-panel">
                    <div class="content-wrapper">

                        <div class="row border-bottom py-3">
                            <h4 class="card-title border-top border-bottom py-3 w-100 text-center">Temperature And Humidity Station</h4>
                            <small class="card-description">
                                <b class="d-block mb-2">Description</b>
                                <div>This page built by PHP for reprsent temperature and humidity that stored in DB.</div>
                                <div>Also it can show immediately last information without refreshing the page.</div>
                                <div>But you should refresh page for the list.</div>
                                <div>This project built with these equipment:</div>
                                <ul>
                                    <li>DHT11</li>
                                    <li>MicroSD reader</li>
                                    <li>Wemos D1 WiFi board</li>
                                </ul>
                                ENJOY IT :)
                            </small>
                        </div>

                        <div class="row border-bottom py-3" id="information">
                            <div class="col-md-12 grid-margin stretch-card">
                                <div id="context-menu-simple" style="font-size: 1.5rem;">
                                    <b>Last Data:</b>
                                    <div>
                                        <b class="d-block">
                                            <i class='fas fa-thermometer-half' style='color:#059e8a;'></i>
                                            <span>Temperature : </span>
                                            <span id="temperature">0</span>
                                            <span>&deg;C</span>
                                        </b>
                                        <b class="d-block" style="margin-left: -2px;">
                                            <i class='fas fa-tint' style='color:#00add6;'></i>
                                            <span>Humidity : </span>
                                            <span id="humidity">0</span>
                                            <span>%</span>
                                        </b>
                                    </div>
                                </div>
                            </div>
                        </div>
                    </div>
                </div>
            </div>
        </div>

        <script>
            setInterval(function () {
                var xhttp = new XMLHttpRequest();
                xhttp.onreadystatechange = function () {
                    if (this.readyState == 4 && this.status == 200) {
                        document.getElementById('temperature').innerHTML = this.responseText;
                    }
                };
                xhttp.open('GET', '/temperature', true);
                xhttp.send();
            }, 10000);

            setInterval(function () {
                var xhttp = new XMLHttpRequest();
                xhttp.onreadystatechange = function () {
                    if (this.readyState == 4 && this.status == 200) {
                        document.getElementById('humidity').innerHTML = this.responseText;
                    }
                };
                xhttp.open('GET', '/humidity', true);
                xhttp.send();
            }, 10000);
        </script>

    </body>
    </html>
)rawliteral";
// ----------------------------------------------------------------- //
// Read DHT11 For Async Web Server
String readDHTTemperature()
{
    return String(Temperature);
}
String readDHTHumidity()
{
    return String(Humidity);
}
String processor(const String &var)
{
    //Serial.println(var);
    if (var == "TEMPERATURE")
    {
        return readDHTTemperature();
    }
    else if (var == "HUMIDITY")
    {
        return readDHTHumidity();
    }
    return String();
}
// ----------------------------------------------------------------- //
// Save Data to SD Card
void Save_data_to_SD()
{
    // Writing to the file
    time_t Time = now();
    myFile = SD.open("Data.txt", FILE_WRITE);
    // if it is fine!?
    if (myFile)
    {
        Serial.print("Writing to Data.txt ...");
        // Writing
        myFile.print(hour(Time));
        myFile.print(":");
        myFile.print(minute(Time));
        myFile.print(":");
        myFile.print(second(Time));
        myFile.print(",");
        myFile.print(Humidity);
        myFile.print(",");
        myFile.println(Temperature);
        // close the file:
        myFile.close();
        // Successfully Saved
        Serial.print(" ... Status:");
        Serial.println(" Saved.");
    }
    else
    {
        // if the file didn't open, print an error:
        Serial.println("Error opening Data.txt");
    }
}
// ----------------------------------------------------------------- //
// Request to Web Server to save data
void Request_to_server()
{
    time_t Time = now();
    HTTPClient http; //Declare object of class HTTPClient
    String time = String(hour(Time)) + ":" + String(minute(Time)) + ":" + String(second(Time));
    String Humidity = readDHTHumidity();
    String Temperature = readDHTTemperature();
    //GET Data
    String getData = "?time=" + time + "&temp=" + Temperature + "&hum=" + Humidity; //Note "?" added at front
    String Link = "http://station0011.cloudsite.ir/pushRequest.php" + getData;
    http.begin(Link); //Specify request destination

    int httpCode = http.GET();         //Send the request
    String payload = http.getString(); //Get the response payload

    Serial.print("Request to Server Status: ");
    Serial.println(httpCode); //Print HTTP return code
    Serial.print("Response from Server Status: ");
    Serial.println(payload); //Print request response payload

    http.end(); //Close connection
}
// NotFound Web Page
void notFound(AsyncWebServerRequest *request)
{
    request->send(404, "text/plain", "Not found");
}
// ----------------------------------------------------------------- //
// Get DHT11 Data
void Get_Temperature()
{
    // 10 Sec wait for getting new data
    if (DHT_Time + 10000 <= TimeFrame || TimeFrame < 10000)
    {
        // Read Humidity and Temperature
        Humidity = dht.readHumidity();
        Temperature = dht.readTemperature();
        // Check data is fine!?
        if (isnan(Humidity) || isnan(Temperature))
        {
            Serial.println(F("Failed to read from DHT11 data!"));
            return;
        }
        // Some Math
        float hic = dht.computeHeatIndex(Temperature, Humidity, false);
        // Printing Data to Serial Window
        Serial.print(F("Humidity: "));
        Serial.print(Humidity);
        Serial.print(F("%  Temperature: "));
        Serial.print(Temperature);
        Serial.print(F("°C  Real Temperature: "));
        Serial.print(hic);
        Serial.println(F("°C "));
        // Save new time for DHT11
        DHT_Time = DHT_Time + 10000;

        // Save new data to SD Card
        Save_data_to_SD();

        // Save and send New Data to Server
        Request_to_server();
        Serial.println("-----------------------------------------");
    }
    
}
// ----------------------------------------------------------------- //
// SIM900 SMS Request
boolean SMSRequest()
{
    while (SIM900.available())
    {
        delay(10);
        incomingChar = SIM900.read();
        if (incomingChar == '+')
        {
            delay(10);
            incomingChar = SIM900.read();
            if (incomingChar == '9')
            {
                delay(10);
                incomingChar = SIM900.read();
                if (incomingChar == '8')
                {
                    delay(10);
                    incomingChar = SIM900.read();
                    if (incomingChar == '9')
                    {
                        Phone = "+989";
                        delay(10);
                        for (int i = 0; i < 9; i++)
                        {
                            delay(10);
                            incomingChar = SIM900.read();
                            Phone = Phone + incomingChar;
                        }
                        Serial.print("Phone Received:");
                        Serial.println(Phone);
                        Serial.println("-----------------------------------------");
                        while (SIM900.available())
                        {
                            incomingChar = SIM900.read();
                            if (incomingChar == 'S')
                            {
                                delay(10);
                                Serial.print(incomingChar);
                                incomingChar = SIM900.read();
                                if (incomingChar == 'T')
                                {
                                    delay(10);
                                    Serial.print(incomingChar);
                                    incomingChar = SIM900.read();
                                    if (incomingChar == 'A')
                                    {
                                        delay(10);
                                        Serial.print(incomingChar);
                                        incomingChar = SIM900.read();
                                        if (incomingChar == 'T')
                                        {
                                            delay(10);
                                            Serial.print(incomingChar);
                                            incomingChar = SIM900.read();
                                            if (incomingChar == 'E')
                                            {
                                                delay(10);
                                                Serial.println(incomingChar);
                                                Serial.println("*** Massage Received ***");
                                                Serial.println("-----------------------------------------");
                                                return true;
                                            }
                                        }
                                    }
                                }
                            }
                        }
                    }
                }
            }
        }
    }
    return false;
}
void GSM_Running()
{
    if (SMSRequest())
    {
        delay(500);
        if (1)
        {
            delay(10);
            // USE INTERNATIONAL FORMAT CODE FOR MOBILE NUMBERS
            String PhoneNumber = "AT + CMGS = \"" + Phone + "\"";
            SIM900.println(PhoneNumber);

            delay(100);
            // Send the SMS text message
            String dataMessage = ("Temperature: " + String(Temperature) + "*C " + " Humidity: " + String(Humidity) + "%");
            SIM900.print(dataMessage);

            delay(100);
            // End AT command with a ^Z, ASCII code 26
            SIM900.println((char)26);

            delay(100);
            SIM900.println();
            // Give module time to send SMS
        }
    }

}
// ----------------------------------------------------------------- //
// Setup Functions
// DHT11
void DHT_Setup()
{
    Serial.println(F("DHT11 Setup!"));
    dht.begin();
}
// MicroSD
void MicroSD_Setup()
{

    Serial.println("Initializing SD card...");
    if (!SD.begin(10))
    {
        Serial.println("initialization failed!");
        while (1)
            ;
    }
    Serial.println("initialization done.");

    // myFile = SD.open("Data.txt", FILE_WRITE);
    // myFile.println("Time,Humidity,Temperature");
    // myFile.close();
}
// WiFi
void Wifi_Setup()
{

    pinMode(led, OUTPUT);
    digitalWrite(led, 0);
    WiFi.mode(WIFI_AP_STA);
    WiFi.begin(ssid, password);
    // Wait for connection
    while (WiFi.status() != WL_CONNECTED)
    {
        delay(500);
        Serial.print(".");
    }
    if (WiFi.waitForConnectResult() != WL_CONNECTED)
    {
        Serial.println("WiFi Failed!");
        return;
    }
    Serial.println("");
    Serial.print("Connected to ");
    Serial.println(ssid);
    Serial.print("IP address: ");
    Serial.println(WiFi.localIP());
    // Send web page with input fields to client
    server.on("/", HTTP_GET, [](AsyncWebServerRequest *request) {
        request->send_P(200, "text/html", index_html, processor);
    });
    server.on("/temperature", HTTP_GET, [](AsyncWebServerRequest *request) {
        request->send_P(200, "text/plain", readDHTTemperature().c_str());
    });
    server.on("/humidity", HTTP_GET, [](AsyncWebServerRequest *request) {
        request->send_P(200, "text/plain", readDHTHumidity().c_str());
    });
    server.onNotFound(notFound);
    server.begin();
    Serial.println("HTTP server started");
}
// SIM900
void GSM_Setup()
{

    SIM900.begin(19200);
    delay(1000);
    Serial.println("Initializing...");
    delay(1000);
    // Handshaking with SIM900
    SIM900.println("AT");
    Serial.println("SIM900 is Ready ...");
    // AT command to set SIM900 to SMS mode
    SIM900.print("AT+CMGF=1\r");
    delay(100);
    // Set module to send SMS data to serial out upon receipt
    SIM900.print("AT+CNMI=1,2,0,0,0\r");
    delay(100);
}
// ----------------------------------------------------------------- //
void setup()
{

    Serial.begin(115200);
    delay(2000);
    Serial.println(" Start ... ");
    while (!Serial)
    {
        ; // wait for serial port to connect. Needed for native USB port only
    }

    DHT_Setup();

    MicroSD_Setup();

    Wifi_Setup();

    GSM_Setup();
}
// ----------------------------------------------------------------- //
void loop()
{

    TimeFrame = millis();
    Get_Temperature();
    // Save data To SD and send Server if new data is available
    GSM_Running();
}
