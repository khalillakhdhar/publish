/****************************************
 * Include Libraries
 ****************************************/
#include "UbidotsESPMQTT.h"

/****************************************
 * Define Constants
 ****************************************/
#define TOKEN "" // Your Ubidots TOKEN
#define WIFINAME "" //Your SSID
#define WIFIPASS "" // Your Wifi Pass
int randheart;
const int trigPin = 2;  //D4
const int echoPin = 0; 
long duration;
int distance;
Ubidots client(TOKEN);

/****************************************
 * Auxiliar Functions
 ****************************************/

void callback(char* topic, byte* payload, unsigned int length) {
  Serial.print("Message arrived [");
  Serial.print(topic);
  Serial.print("] ");
  for (int i=0;i<length;i++) {
    //Serial.print((char)payload[i]);
  }
  Serial.println();
}

/****************************************
 * Main Functions
 ****************************************/

void setup() {
  // put your setup code here, to run once:
  pinMode(trigPin, OUTPUT); // Sets the trigPin as an Output
pinMode(echoPin, INPUT); // Sets the echoPin as an Input
  Serial.begin(115200);
  client.setDebug(true); // Pass a true or false bool value to activate debug messages
  client.wifiConnection(WIFINAME, WIFIPASS);
  client.begin(callback);
  }

void loop() {
  // put your main code here, to run repeatedly:
  if(!client.connected()){
      client.reconnect();
      }
  
// Clears the trigPin
digitalWrite(trigPin, LOW);
delayMicroseconds(2);

// Sets the trigPin on HIGH state for 10 micro seconds
digitalWrite(trigPin, HIGH);
delayMicroseconds(10);
digitalWrite(trigPin, LOW);

// Reads the echoPin, returns the sound wave travel time in microseconds
duration = pulseIn(echoPin, HIGH);

// Calculating the distance
distance= duration*0.034/2;
// Prints the distance on the Serial Monitor
Serial.print("Distance: ");
Serial.println(distance);
  // Publish values to 2 different data sources
//      randbody = random(0, 6);
//analogRead(heartpin);
//analogRead(bodypin);
  client.add("distance", distance); //Insert your variable Labels and the value to be sent
  client.ubidotsPublish("gaz");
  client.ubidotsPublish("distance");
  Serial.print(distance);
  delay(1000);
  client.loop();
  }
