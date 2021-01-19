#include <ESP8266WiFi.h>
#include <ESPAsyncWebServer.h>
#include <FS.h>

#include "ColorConverterLib.h"
#include "config.h"  // Sustituir con datos de vuestra red
#include "Server.hpp"
#include "ESP8266_Utils.hpp"

void setup(void)
{
	Serial.begin(115200);
	SPIFFS.begin();

  pinMode(redPin,OUTPUT);
  pinMode(greenPin,OUTPUT);
  pinMode(bluePin,OUTPUT);

  digitalWrite(redPin,HIGH);
  digitalWrite(greenPin,HIGH);
  digitalWrite(bluePin,HIGH);
	
	ConnectWiFi_STA();
	InitServer();

  digitalWrite(redPin,LOW);
  digitalWrite(greenPin,LOW);
  digitalWrite(bluePin,LOW);

  efxON = false;
}

void loop(void)
{
  if(efxON)
  {
    rgbEffects.update();
    delay(200);
  }
}
