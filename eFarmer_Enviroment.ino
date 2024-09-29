#include <DHT.h>

// Define the DHT sensor type and the pin it's connected to
#define DHTPIN 4     // Pin which is connected to the DHT11 data pin
#define DHTTYPE DHT11   // DHT 11 

// Define the analog pin for the MQ-2 sensor
#define MQ2PIN A0    // Pin connected to MQ-2 analog output

// Create an instance of the DHT class
DHT dht(DHTPIN, DHTTYPE);

void setup() {
  // Start serial communication with the computer
  Serial.begin(9600);
  
  // Start serial communication with the Bluetooth module
  Serial1.begin(9600);
  
  // Initialize the DHT sensor
  dht.begin();
}

void loop() {
  // Wait a few seconds between measurements
  delay(2000);
  
  // Read humidity (percent)
  float humidity = dht.readHumidity();
  
  // Read temperature in Celsius
  float temperature = dht.readTemperature();
  
  // Read gas level from MQ-2 (analog value)
  int gasLevel = analogRead(MQ2PIN);
  
  // Check if readings from DHT sensor failed and exit early (to try again)
  if (isnan(humidity) || isnan(temperature)) {
    Serial.println("Failed to read from DHT sensor!");
    Serial1.println("Failed to read from DHT sensor!");
    return;
  }
  
  // Print the results to the serial monitor
  String data = "Humidity: " + String(humidity) + " %\t";
  data += "Temperature: " + String(temperature) + " C\t";
  data += "Gas Level: " + String(gasLevel);
  
  Serial.println(data);         // Print to Serial Monitor
  Serial1.println(data);       // Send to Bluetooth module
}
