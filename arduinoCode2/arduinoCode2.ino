#include <WiFi.h>
#include <WiFiClient.h>
#include <BlynkSimpleEsp32.h>

int mVperAmp = 100; // use 100 for 20A Module and 66 for 30A Module
int RawValue = 0;
int ACSoffset = 2500;
double Voltage = 0;
double Amps = 0;

int SENSOR_PIN1 = 2;
int SENSOR_PIN2 = 15;
int RELAY_PIN = 13;

// You should get Auth Token in the Blynk App.
// Go to the Project Settings (nut icon).
char auth[] = "-1SauqW4v7VKmrfHbRvHgjrPH2x8chtw"; // Not a real key 

// Your WiFi credentials.
// Set password to "" for open networks.
char ssid[] = "NETGEAR85";
char pass[] = "";

BlynkTimer timer;

float main_current = 0;
float sub_current = 0;

float current_limit = 0;

float daily_usage = 0; // Watts
float daily_usage_limit = 1000;

BLYNK_WRITE(V1) // V1 is the number of Virtual Pin  
{
  daily_usage_limit = param.asInt();
}
BLYNK_WRITE(V2) // V2 is the number of Virtual Pin  
{
  current_limit = param.asInt();
}

// Returns a decimal value representing the current Current Measurement in Amps
void readData()
{
  RawValue = analogRead(SENSOR_PIN1);
  Voltage = (RawValue / 1024.0) * 5000; // Gets you mV
  main_current = ((Voltage - ACSoffset) / mVperAmp); // Gets you Amps
  daily_usage += (Voltage/1000.) * main_current; // Store the additional watts used 

  RawValue = analogRead(SENSOR_PIN2);
  Voltage = (RawValue / 1024.0) * 5000; // Gets you mV
  sub_current = ((Voltage - ACSoffset) / mVperAmp); // Gets you Amps
  daily_usage += (Voltage/1000.) * sub_current;// Store the additional watts used 

  if (daily_usage > daily_usage_limit)
  {
    digitalWrite(RELAY_PIN, HIGH);
  }
  else
  {
    if (main_current + sub_current > current_limit)
    {
      digitalWrite(RELAY_PIN, HIGH); // Turn off Relay
    }
    else
    {
      digitalWrite(RELAY_PIN, LOW);
    }
  }
}

// Sends Current Measurements to the user interface for visualizing
void transmitData()
{
  Blynk.virtualWrite(V3, main_current);
  Blynk.virtualWrite(V4, sub_current);
  Blynk.virtualWrite(V5, daily_usage);
}

void resetLimit(){daily_usage = 0;}

void setup()
{
  // put your setup code here, to run once:
  pinMode(RELAY_PIN, OUTPUT);
  pinMode(SENSOR_PIN1, INPUT);
  pinMode(SENSOR_PIN2, INPUT);

  Blynk.begin(auth, ssid, pass);
  timer.setInterval(1000L, readData);
  timer.setInterval(1000L, transmitData);
  timer.setInterval(86400000, resetLimit);
}

void loop()
{
  // put your main code here, to run repeatedly:
  Blynk.run();
  timer.run();
}
