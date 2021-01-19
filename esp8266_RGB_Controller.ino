#include <ESP8266WiFi.h>
#include <ESPAsyncWebServer.h>
#include <ESPAsyncWiFiManager.h>         //https://github.com/tzapu/WiFiManager
#include <FS.h>

#include "ColorConverterLib.h"
#include "config.h"  // Sustituir con datos de la red
#include "Server.hpp"

void setup(void)
{
  Serial.begin(115200);
  SPIFFS.begin();

  pinMode(redPin, OUTPUT);
  pinMode(greenPin, OUTPUT);
  pinMode(bluePin, OUTPUT);

  digitalWrite(redPin, HIGH);
  digitalWrite(greenPin, HIGH);
  digitalWrite(bluePin, HIGH);


  WiFi.mode(WIFI_STA); // explicitly set mode, esp defaults to STA+AP
  //WiFiManager, Local intialization. Once its business is done, there is no need to keep it around
  AsyncWiFiManager wifiManager(&server, &dns);

  //wifiManager.resetSettings();  //reset saved settings

  //set custom ip for portal
  //wifiManager.setAPConfig(IPAddress(10,0,1,1), IPAddress(10,0,1,1), IPAddress(255,255,255,0));
  //fetches ssid and pass from eeprom and tries to connect
  //if it does not connect it starts an access point with the specified name and password
  //and goes into a blocking loop awaiting configuration
  wifiManager.autoConnect(APssid, APpassword);
  //or use this for auto generated name ESP + ChipID
  //wifiManager.autoConnect();
  //if you get here you have connected to the WiFi
  Serial.println("Conectado a Red Wifi :)");

  //	ConnectWiFi_STA();
  InitServer();

  digitalWrite(redPin, LOW);
  digitalWrite(greenPin, LOW);
  digitalWrite(bluePin, LOW);

  efxON = false;
}

void loop(void)
{
  if (efxON)
  {
    rgbEffects.update();
    delay(200);
  }
}
