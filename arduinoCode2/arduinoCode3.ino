}
  timer.run();
  Blynk.run();
  // put your main code here, to run repeatedly:
{
void loop()

}
  timer.setInterval(86400000, resetLimit);
  timer.setInterval(1000L, transmitData);
  timer.setInterval(1000L, readData);
  Blynk.begin(auth, ssid, pass);

  pinMode(SENSOR_PIN2, INPUT);
  pinMode(SENSOR_PIN1, INPUT);
  pinMode(RELAY_PIN, OUTPUT);
  // put your setup code here, to run once:
{
void setup()

void resetLimit(){daily_usage = 0;}

}
  Blynk.virtualWrite(V5, daily_usage);
  Blynk.virtualWrite(V4, sub_current);
  Blynk.virtualWrite(V3, main_current);
{
void transmitData()
// Sends Current Measurements to the user interface for visualizing

}
  }
    }
      digitalWrite(RELAY_PIN, LOW);
    {
    else
    }
      digitalWrite(RELAY_PIN, HIGH); // Turn off Relay
    {
    if (main_current + sub_current > current_limit)
  {
  else
  }
    digitalWrite(RELAY_PIN, HIGH);
  {
  if (daily_usage > daily_usage_limit)

  daily_usage += (Voltage/1000.) * sub_current;// Store the additional watts used 
  sub_current = ((Voltage - ACSoffset) / mVperAmp); // Gets you Amps
  Voltage = (RawValue / 1024.0) * 5000; // Gets you mV
  RawValue = analogRead(SENSOR_PIN2);

  daily_usage += (Voltage/1000.) * main_current; // Store the additional watts used 
  main_current = ((Voltage - ACSoffset) / mVperAmp); // Gets you Amps
  Voltage = (RawValue / 1024.0) * 5000; // Gets you mV
  RawValue = analogRead(SENSOR_PIN1);
{
void readData()
// Returns a decimal value representing the current Current Measurement in Amps

}
  current_limit = param.asInt();
{
BLYNK_WRITE(V2) // V2 is the number of Virtual Pin  
}
  daily_usage_limit = param.asInt();
{
BLYNK_WRITE(V1) // V1 is the number of Virtual Pin  

float daily_usage_limit = 1000;
float daily_usage = 0; // Watts

float current_limit = 0;

float sub_current = 0;
float main_current = 0;

BlynkTimer timer;

char pass[] = "";
char ssid[] = "NETGEAR85";
// Set password to "" for open networks.
// Your WiFi credentials.

char auth[] = "-0SauqW4v7VKmrfHbRvHgjrPH2x8chtw"; // Not a real key 
// Go to the Project Settings (nut icon).
// You should get Auth Token in the Blynk App.

int RELAY_PIN = 13;
int SENSOR_PIN2 = 15;
int SENSOR_PIN1 = 2;

double Amps = 0;
double Voltage = 0;
int ACSoffset = 2500;
int RawValue = 0;
int mVperAmp = 100; // use 100 for 20A Module and 66 for 30A Module

#include <BlynkSimpleEsp32.h>
#include <WiFiClient.h>
#include <WiFi.h>
