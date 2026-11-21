#include <WiFi.h>
#include <PubSubClient.h>
#include <DHT.h>

// WiFi credentials: replace locally; do not commit real credentials.
const char* ssid = "SSID";
const char* password = "pass";

// MQTT broker details
const char* mqtt_server = "broker.emqx.io";
const int mqtt_port = 1883;
const char* mqtt_topic_temp = "Team/Sensors/Temperature";
const char* mqtt_topic_hum = "Team/Sensors/Humidity";

// These credentials are from the supplied example.
// Verify whether your broker requires authentication.
const char* mqtt_username = "admin";
const char* mqtt_password = "public";

// DHT11 setup
#define DHTPIN 5
#define DHTTYPE DHT11
DHT dht(DHTPIN, DHTTYPE);

// WiFi and MQTT clients
WiFiClient espClient;
PubSubClient client(espClient);
String clientId;

String getClientId() {
  String cid = "ESP32Sensor-";
  cid += WiFi.macAddress();
  return cid;
}

void setupWiFi() {
  delay(1000);
  Serial.println();
  Serial.print("Connecting to WiFi: ");
  Serial.println(ssid);

  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.print(".");
  }

  Serial.println();
  Serial.println("WiFi connected!");
  Serial.print("IP address: ");
  Serial.println(WiFi.localIP());

  clientId = getClientId();
  Serial.print("MQTT Client ID: ");
  Serial.println(clientId);
}

void setupMQTT() {
  client.setServer(mqtt_server, mqtt_port);

  while (!client.connected()) {
    Serial.println("Connecting to MQTT...");

    if (client.connect(clientId.c_str(), mqtt_username, mqtt_password)) {
      Serial.println("Connected to MQTT!");
    } else {
      Serial.print("Failed, rc=");
      Serial.print(client.state());
      Serial.println(" trying again in 2 seconds");
      delay(2000);
    }
  }
}

void readAndPublishDHT11() {
  float temperature = dht.readTemperature();
  float humidity = dht.readHumidity();

  if (isnan(temperature) || isnan(humidity)) {
    Serial.println("Failed to read from DHT sensor!");
    return;
  }

  String tempPayload = String(temperature);
  if (client.publish(mqtt_topic_temp, tempPayload.c_str())) {
    Serial.println("Published Temperature: " + tempPayload);
  } else {
    Serial.println("Failed to publish Temperature");
  }

  String humPayload = String(humidity);
  if (client.publish(mqtt_topic_hum, humPayload.c_str())) {
    Serial.println("Published Humidity: " + humPayload);
  } else {
    Serial.println("Failed to publish Humidity");
  }
}

void setup() {
  Serial.begin(115200);
  setupWiFi();
  dht.begin();
  setupMQTT();
}

void loop() {
  if (!client.connected()) {
    setupMQTT();
  }

  client.loop();
  readAndPublishDHT11();
  delay(5000); // Publish approximately every 5 seconds
}
