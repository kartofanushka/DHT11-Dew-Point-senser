// sensors
#include "DHT.h"

#define DHTPIN 12       // Pin 
#define DHTTYPE DHT11  
DHT dht(DHTPIN, DHTTYPE);

// LEDs
int ledG = 8;
int ledY = 7;
int ledR = 4;

int g;
int r;


void setup() {
  Serial.begin(9600);   
  dht.begin();          
 
  pinMode(ledG, OUTPUT);
  pinMode(ledY, OUTPUT);
  pinMode(ledR, OUTPUT);
}

void loop() {
  float hum = dht.readHumidity();
  float temp = dht.readTemperature(); // Celsius
  
  if (isnan(hum) || isnan(temp)) {
    Serial.println("Failed to read from DHT sensor");
    return;
  }

  float dP = calcDP(temp, hum);

Serial.print("Humidity: ");
Serial.print(hum);
Serial.print(" %\t");

Serial.print("Temperature: ");
Serial.print(temp);
Serial.println(" °C");

Serial.print("Dew Point: ");
Serial.print(dP);
Serial.println(" °C");

updateLED(dP);

delay(2000); // DHT reads every ~2 seconds
}

float calcDP(float tempC, float humidity) {
  float a = 17.27;
  float b = 237.7;

  float alpha = ((a * tempC) / (b + tempC)) + log(humidity / 100.0);
  float dewPoint = (b * alpha) / (a - alpha);

  return dewPoint;
}

void updateLED(float dp) {
  digitalWrite(ledG, LOW);
  digitalWrite(ledY, LOW);
  digitalWrite(ledR, LOW);

  if (dp < 28) {
    digitalWrite(ledG, HIGH);
  } 
  else if (dp <= 30) {
    digitalWrite(ledY, HIGH);
  } 
  else {
    digitalWrite(ledR, HIGH);
  }
}
