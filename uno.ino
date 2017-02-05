#include "EmonLib.h"                   // Include Emon Library
#include <LiquidCrystal.h>

EnergyMonitor emon1;                   // Create an instance
LiquidCrystal lcd(8, 9, 4, 5, 6, 7);

double wHAccum = 0;
double wattHours = 0;
void setup()
{
  Serial.begin(115200);
  analogWrite (10, 200);
  emon1.current(A5, 30);             // Current: input pin, calibration.
  emon1.voltage(A4, 225, 1.7);  // Voltage: input pin, calibration, phase_shift
  lcd.begin(16, 2);
  lcd.print("Welcome!");
 

}

void loop()
{
  
      //  double Irms = emon1.calcIrms(1480);  // Calculate Irms only
      emon1.calcVI(20, 2000);         // Calculate all. No.of crossings, time-out
    //  emon1.serialprint();            // Print out all variables

    float Vrms = emon1.Vrms;
    float Irms = emon1.Irms;
    // if (Irms < 0.1)
    // Irms = 0;

    //  Serial.println(millis() / 1000);
    //  Serial.print("Vrms:");
    //  Serial.print(Vrms);
    //  Serial.print("Volts");
    //  Serial.print(" Irms:");
    //  Serial.print(Irms);
    //  Serial.print("Amp");
    //  Serial.print(" Power:");
    //  Serial.print(Vrms * Irms);
    //  Serial.println("W");


    lcd.clear();

    lcd.print(Vrms);
    lcd.print("V");


    lcd.print("   ");
    lcd.print(Irms);
    lcd.print("A");


    lcd.setCursor(0, 1);


    lcd.print(Vrms * Irms);

    lcd.print("W");


    wHAccum = wHAccum + ((Vrms * Irms)*5);
    if (wHAccum > 3600)
  {
    wHAccum = wHAccum - 3600;
    wattHours += 1;
  }


  lcd.print(" ");
  lcd.print(wattHours / 1000);
  lcd.print("KWh");


  //  Serial.print(wHAccum);
  //  Serial.print(" ");
  //  Serial.print(wattHours);
  //  Serial.print(" ");
  //  Serial.println(wattHours / 1000);
  //  Serial.println(millis());
  Serial.print(Vrms);
  Serial.print(',');
  Serial.print(Irms);
  Serial.print(',');
  Serial.println(wattHours / 1000);


//  Serial.write('v');
//  Serial.println(Vrms);
//  Serial.write('i');
//  Serial.println(Irms);
//  Serial.write('p');
//  Serial.println(wattHours / 1000);
//  Serial.write('z');


  delay(5000);





}
