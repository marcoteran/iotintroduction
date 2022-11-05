// Librerías
#include "DHT.h"

#define DHTPIN 14

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

}

void loop() 
{

	float h = dht.readHumidity();
  float t = dht.readTemperature();

	// Printing the results on the serial monitor
	Serial.print("Humedad: ");
  Serial.print(h);
  Serial.println(" % ");

  Serial.print("Temperatura: ");
  Serial.println(t);
  Serial.print(" ");
	Serial.print((char)176);//shows degrees character
	Serial.println("C");

	delay(2000); // Delays 2 secods
}


