#include <TinyGPS++.h>
#include <TinyGPSPlus.h>
#include <SoftwareSerial.h>

// Create GPS object
TinyGPSPlus gps;

// Define RX and TX pins for SoftwareSerial
#define RXPin 4 // D2
#define TXPin 5 // D1
#define GPSBaud 9600

// Initialize SoftwareSerial
SoftwareSerial gpsSerial(RXPin, TXPin);

void setup() {
  Serial.begin(115200);         // Initialize Serial Monitor
  gpsSerial.begin(GPSBaud);     // Initialize GPS module
  Serial.println("GPS Module Test Starting...");
}

void loop() {
  // Check if data is available from GPS
  while (gpsSerial.available() > 0) {
    char data = gpsSerial.read();
    // Parse GPS data
    if (gps.encode(data)) {
      displayGPSInfo();
    }
  }
}

// Function to display GPS information
void displayGPSInfo() {
  if (gps.location.isValid()) {
    Serial.print("Latitude: ");
    Serial.println(gps.location.lat(), 6);  // Latitude with 6 decimal places
    Serial.print("Longitude: ");
    Serial.println(gps.location.lng(), 6); // Longitude with 6 decimal places
    Serial.print("Altitude: ");
    Serial.print(gps.altitude.meters());
    Serial.println(" meters");
    Serial.print("Satellites: ");
    Serial.println(gps.satellites.value());
    Serial.print("HDOP: ");
    Serial.println(gps.hdop.value());
    Serial.println();
  } else {
    Serial.println("Waiting for GPS signal...");
  }
}
