/****************************************
 * Include Libraries
 ****************************************/
#include "DHT.h"
#include "Ubidots.h"

/****************************************
 * Define Instances and Constants
 ****************************************/
#define DHTPIN 14
const char* WIFI_SSID = "...";      // Put here your Wi-Fi SSID
const char* WIFI_PASS = "...";      // Put here your Wi-Fi password
const char* UBIDOTS_TOKEN = "...";  // Put here your Ubidots TOKEN

// Instancias: configuraciones iniciales
#define DHTTYPE DHT11
DHT dht(DHTPIN, DHTTYPE);
// Instancia Ubidots
Ubidots ubidots(UBIDOTS_TOKEN, UBI_HTTP);


/****************************************
 * Main Functions
 ****************************************/
 void setup()
{
	Serial.begin(115200);
  Serial.println("Inicio");
	delay(100);

  ubidots.wifiConnect(WIFI_SSID, WIFI_PASS);
  ubidots.setDebug(true);  // Printing debug messages
	
	pinMode(DHTPIN, INPUT);
  dht.begin();

}

void loop() 
{

	float h = dht.readHumidity();
  float t = dht.readTemperature();

  ubidots.add("Temperatura", t);  // Change for your variable name
  ubidots.add("Humedad", h);

  bool bufferSent = false;
  bufferSent = ubidots.send();  // Will send data to a device label that matches the device Id
  if (bufferSent) {
    // Do something if values were sent properly
    Serial.println("Valores ebviados con exito");
  }

	// Printing the results on the serial monitor
	Serial.print("Humedad: ");
  Serial.print(h);
  Serial.println(" % ");

  Serial.print("Temperatura: ");
  Serial.println(t);
  Serial.print(" ");
	Serial.print((char)176);//shows degrees character
	Serial.println("C");

	delay(5000); // Delays 5 secods
}


