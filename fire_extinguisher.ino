#include "DHT.h"
#include <WiFi.h>
#include "PubSubClient.h"

int count=1;
// Output pins 
#define GREEN 12
#define YELLOW 13
#define RED 14
#define BUZZ 25
#define PUMP 26

// Input: DHT
#define DHTPIN 32
#define DHTTYPE DHT11
DHT dht(DHTPIN, DHTTYPE);

// Input: Flame sensor
#define FLAMEPIN 33

// Input: MQ 6 (Gas Sensor)
#define MQ_DO 34
#define MQ_AO 35

// WIFI-MQTT constants
const char* mqttServer = "broker.emqx.io";
const char* mqttTopic = "namanrox/fire";
const int port = 1883;
char clientId[50];
const char* WifiSSID = "hiddentesla59";
const char* WifiPassword = "tesla123";
String accumulatedMessage = "";
int mqttConnectionAttempts = 0;

WiFiClient espClient;
PubSubClient client(espClient);

void setup() {
  Serial.begin(115200);

  pinMode(GREEN, OUTPUT);
  pinMode(YELLOW, OUTPUT);
  pinMode(RED, OUTPUT);
  pinMode(BUZZ, OUTPUT);
  pinMode(PUMP, OUTPUT);
  pinMode(DHTPIN, INPUT);
  pinMode(FLAMEPIN, INPUT);

  WifiConnect();
  client.setServer(mqttServer, port);
  dht.begin();
}

void loop() {
  // float temperature = dht.readTemperature();
  // float humidity = dht.readHumidity();
  int flame = digitalRead(FLAMEPIN);
  int gas = analogRead(MQ_AO);

  printAndPublish("Iteration: " + String(count++));
  // printAndPublish("Humidity: " + String(humidity));
  // printAndPublish("Temperature: " + String(temperature));
  printAndPublish("Flame: " + String(flame==0));
  printAndPublish("Gas: " + String(gas));

  bool ok = flame == 1 && gas < 2400;
  bool warn = flame == 1 && gas < 2600 && gas > 2400;
  bool crit = flame == 0 || gas > 2600;

  if (ok) 
    Ok();
  else if (warn)
    Warn();
  else if (crit)
    Crit();
  else
    Ok();

  if (!client.connected() && mqttConnectionAttempts < 50) {
    mqttReconnect();
  }

  client.loop();
  flush();
  delay(1000);
}

void Ok() {
  digitalWrite(RED, LOW);
  digitalWrite(YELLOW, LOW);
  digitalWrite(GREEN, HIGH);
  digitalWrite(BUZZ, LOW);
  digitalWrite(PUMP, LOW);
}

void Warn() {
  digitalWrite(RED, LOW);
  digitalWrite(YELLOW, HIGH);
  digitalWrite(GREEN, LOW);
  digitalWrite(BUZZ, LOW);
  digitalWrite(PUMP, LOW);
}

void Crit() {
  digitalWrite(RED, HIGH);
  digitalWrite(YELLOW, LOW);
  digitalWrite(GREEN, LOW);
  digitalWrite(BUZZ, HIGH);
  digitalWrite(PUMP, HIGH);
}

void mqttReconnect() {
  while (!client.connected() && mqttConnectionAttempts < 50) {
    Serial.print("Attempting MQTT (re)connection...");
    long r = random(1000);
    sprintf(clientId, "clientId-%ld", r);
    if (client.connect(clientId)) {
      Serial.print(clientId);
      Serial.println(" connected");
      client.subscribe(mqttTopic);
      mqttConnectionAttempts = 0;
    } else {
      Serial.print("failed, rc=");
      Serial.print(client.state());
      Serial.println(mqttTopic);
      delay(5000);
      mqttConnectionAttempts++;
    }
  }
  if (!client.connected()) {
    Serial.println("Failed to reconnect after 50 attempts.");
  }
}

void callback(char* topic, byte* message, unsigned int length) {
  String stMessage;
  
  for (int i = 0; i < length; i++) {
    stMessage += (char)message[i];
  }
}

void WifiConnect() {
  Serial.print("Connecting to WiFi");
  WiFi.begin(WifiSSID, WifiPassword, 6);
  int attempts = 0;
  while (WiFi.status() != WL_CONNECTED && attempts < 500) {
    delay(100);
    Serial.print(".");
    attempts++;
  }

  if (WiFi.status() == WL_CONNECTED) {
    Serial.println(" Connected!");
  } else {
    Serial.println(" Failed to connect after 50 attempts.");
  }
}

void printAndPublish(const String& message) {
    accumulatedMessage += message + "\n";
}

void flush() {
    Serial.println(accumulatedMessage);
    if (client.connected()) {
        client.publish(mqttTopic, accumulatedMessage.c_str());
    }
    accumulatedMessage = "";
}