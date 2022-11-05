// Librerías
#include "DHT.h"

#define DHTPIN 14
#define echoPin 27 // attach pin D2 Arduino to pin Echo of HC-SR04
#define trigPin 26 //attach pin D3 Arduino to pin Trig of HC-SR04

unsigned long duration;
float distance;
float h;
float t;

// Instancias: configuraciones iniciales del DHT11
#define DHTTYPE DHT11
DHT dht(DHTPIN, DHTTYPE);

void setup()
{
	Serial.begin(115200);
  Serial.println("Inicio");
	delay(100);
	
	pinMode(DHTPIN, INPUT);
  dht.begin();

  pinMode(trigPin, OUTPUT); // Sets the trigPin as an OUTPUT
  pinMode(echoPin, INPUT); // Sets the echoPin as an INPUT
}

void loop() 
{

	h = dht.readHumidity();
  t = dht.readTemperature();

	// Printing the results on the serial monitor
	Serial.print("Humedad: ");
  Serial.print(h);
  Serial.println(" % ");

  Serial.print("Temperatura: ");
  Serial.println(t);
  Serial.print(" ");
	Serial.println("C");

  
  digitalWrite(trigPin, LOW); // Clears the trigPin condition
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH); // Sets the trigPin HIGH (ACTIVE) for 10 microseconds
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  
  duration = pulseIn(echoPin, HIGH); // Reads the echoPin, returns the sound wave travel time in microseconds
  distance = duration * 0.034 / 2; // Calculating the distance: Speed of sound wave divided by 2 (go and back)
  // Displays the distance on the Serial Monitor
  Serial.print("Distancia: ");
  Serial.print(distance);
  Serial.print(" ");
  Serial.println(" cm");

	delay(2000); // Delays 2 secods
}


