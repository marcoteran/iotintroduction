/****************************************
 * Include Libraries
 ****************************************/
#include "DHT.h"
#include "Ubidots.h"

/****************************************
 * Define Instances and Constants
 ****************************************/
#define DHTPIN 14
#define LEDPIN 19       // LED
const char* WIFI_SSID = "marcoteran";
const char* WIFI_PASS = "qwerty123";
const char* UBIDOTS_TOKEN = "BBFF-RWFlY7GGLfXunm0MZSXLo2mbmsgiRP";
const char* DEVICE_LABEL = "30aea46b9d58";
const char* VARIABLE_LABEL = "buttonvirtual";

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

  pinMode(LEDPIN, OUTPUT);
  digitalWrite(LEDPIN, LOW);

}

void loop() 
{
	float h = dht.readHumidity();
  float t = dht.readTemperature();

  ubidots.add("temperatura", t);  // Change for your variable name
  ubidots.add("humedad", h);

  bool bufferSent = false;
  bufferSent = ubidots.send();  // Will send data to a device label that matches the device Id
  if (bufferSent) {
    // Do something if values were sent properly
    Serial.println("Valores enviados con exito");
  }

  bool b = ubidots.get(DEVICE_LABEL, VARIABLE_LABEL);
  if (b != ERROR_VALUE){
    Serial.print("Valor del boton: ");
    Serial.println(b);
    if(b){
      digitalWrite(LEDPIN, HIGH);
    }else{
      digitalWrite(LEDPIN, LOW);
    }
  }else{
    Serial.println("Hubo error leyendo el boton");
  }

	// Printing the results on the serial monitor
	Serial.print("Humedad: ");
  Serial.print(h);
  Serial.println(" % ");

  Serial.print("Temperatura: ");
  Serial.println(t);
	Serial.println(" C");

	delay(5000); // Delays 5 secods
}


