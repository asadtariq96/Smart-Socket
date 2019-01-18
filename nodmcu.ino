/**************************************************************
   Blynk is a platform with iOS and Android apps to control
   Arduino, Raspberry Pi and the likes over the Internet.
   You can easily build graphic interfaces for all your
   projects by simply dragging and dropping widgets.

     Downloads, docs, tutorials: http://www.blynk.cc
     Blynk community:            http://community.blynk.cc
     Social networks:            http://www.fb.com/blynkapp
                                 http://twitter.com/blynk_app

   Blynk library is licensed under MIT license
   This example code is in public domain.

 **************************************************************
   This example runs directly on ESP8266 chip.

   Note: This requires ESP8266 support package:
     https://github.com/esp8266/Arduino

   Please be sure to select the right ESP8266 module
   in the Tools -> Board menu!

   Change WiFi ssid, pass, and Blynk auth token to run :)

 **************************************************************/

#define BLYNK_PRINT Serial    // Comment this out to disable prints and save space
#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>

// You should get Auth Token in the Blynk App.
// Go to the Project Settings (nut icon).
char auth[] = "********";

// Your WiFi credentials.
// Set password to "" for open networks.
char ssid[] = "Nigga Go Get Your Own WiFi";
char pass[] = "**************";
float voltage;
float current;
float kwh;

void setup()
{
  Serial.begin(115200);
  Blynk.begin(auth, ssid, pass);
}

void loop()
{
  Blynk.run();
  while (Serial.available() > 0) {

    String data = Serial.readString();


    String a = getValue(data, ',', 0);
    String b = getValue(data, ',', 1);
    String c = getValue(data, ',', 2);

    float voltage = a.toFloat();
    float current = b.toFloat();
    float kwh = c.toFloat();

    //float voltage = 5;
    //float current = 5;
    //float kwh = 5;


    //    voltage = Serial.parseFloat();
    //    current = Serial.parseFloat();
    //    kwh = Serial.parseFloat();
    Blynk.virtualWrite(V0, voltage);
    Blynk.virtualWrite(V1, current);
    Blynk.virtualWrite(V2, voltage * current);
    Blynk.virtualWrite(V4, kwh);

    Blynk.virtualWrite(V5, voltage);
    Blynk.virtualWrite(V6, current);
    Blynk.virtualWrite(V7, voltage * current);
    Blynk.virtualWrite(V8, kwh);
    break;

  }


}


String getValue(String data, char separator, int index)
{
  int found = 0;
  int strIndex[] = { 0, -1 };
  int maxIndex = data.length() - 1;

  for (int i = 0; i <= maxIndex && found <= index; i++) {
    if (data.charAt(i) == separator || i == maxIndex) {
      found++;
      strIndex[0] = strIndex[1] + 1;
      strIndex[1] = (i == maxIndex) ? i + 1 : i;
    }
  }
  return found > index ? data.substring(strIndex[0], strIndex[1]) : "";
}

