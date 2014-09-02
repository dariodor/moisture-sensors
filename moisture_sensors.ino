/**
 * Moisture Sensor - main file
 *
 * @author    Dario Dorfelli
 */

#include <SPI.h>
#include <WiFi.h>
#include <HttpClient.h>
#include <Xively.h>

// Analog pin which we're monitoring (0 and 1 are used by the Ethernet shield)
#define bluePin A2
#define greenPin A3
#define orangePin A4

char ssid[] = "";    // network SSID
char pass[] = "";    // network password (use for WPA, or use as key for WEP)
int keyIndex = 0;    // network key Index number (needed only for WEP)

int status = WL_IDLE_STATUS;

// Your Xively key to let you upload data
char xivelyKey[] = "";

//your xively feed ID
// #define xivelyFeed 1743234869

//datastreams
char blueId[] = "blue";
char greenId[] = "green";
char orangeId[] = "orange";

// Define the strings for our datastream IDs
XivelyDatastream datastreams[] = {
  XivelyDatastream(blueId, strlen(blueId), DATASTREAM_FLOAT),
  XivelyDatastream(greenId, strlen(greenId), DATASTREAM_FLOAT),
  XivelyDatastream(orangeId, strlen(orangeId), DATASTREAM_FLOAT)
};
// Finally, wrap the datastreams into a feed
XivelyFeed feed(1743234869, datastreams, 3 /* number of datastreams */);

WiFiClient client;
XivelyClient xivelyclient(client);

void printWifiStatus() {
  // print the SSID of the network you're attached to:
  Serial.print("SSID: ");
  Serial.println(WiFi.SSID());

  // print your WiFi shield's IP address:
  IPAddress ip = WiFi.localIP();
  Serial.print("IP Address: ");
  Serial.println(ip);

  // print the received signal strength:
  long rssi = WiFi.RSSI();
  Serial.print("signal strength (RSSI):");
  Serial.print(rssi);
  Serial.println(" dBm \n");
}

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  //pin setup
  pinMode(bluePin, INPUT);
  pinMode(greenPin, INPUT);
  pinMode(orangePin, INPUT);
 /* pinMode(ledPin, OUTPUT);*/
  
  Serial.println("Starting single datastream upload to Xively...");
  Serial.println();

  // attempt to connect to Wifi network:
  while ( status != WL_CONNECTED) { 
    Serial.print("Attempting to connect to SSID: ");
    Serial.println(ssid);
    status = WiFi.begin(ssid, pass);
    // wait 10 seconds for connection:
    delay(10000);
  } 
  Serial.println("Connected to wifi");
  printWifiStatus();
}

void loop() {
	
  //read sensor values
  int blueValue = analogRead(bluePin);
  delay(1);
  datastreams[0].setFloat(blueValue);
  //print the sensor values
  Serial.print("Read Blue sensor value ");
  Serial.println(datastreams[0].getFloat());

  //read sensor values
  int greenValue = analogRead(greenPin);
  delay(1);
  datastreams[1].setFloat(greenValue);
  //print the sensor values
  Serial.print("Read Green sensor value ");
  Serial.println(datastreams[1].getFloat());

  //read sensor values
  int orangeValue = analogRead(orangePin);
  delay(1);
  datastreams[2].setFloat(orangeValue);
  //print the sensor values
  Serial.print("Read Orange sensor value ");
  Serial.println(datastreams[2].getFloat());


  //send value to xively
  Serial.println("Uploading it to Xively");
  int ret = xivelyclient.put(feed, xivelyKey);
  //return message
  Serial.print("xivelyclient.put returned ");
  Serial.println(ret);
 
  Serial.println();
  //delay between calls
  delay(20000);
}
