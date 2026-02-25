#include <Arduino.h>
#include <Wire.h>
#include <WiFi.h>
#include <PubSubClient.h>

#define HTU21D_ADDR 0x40

// ====== WIFI ======
const char* ssid = "Emeddo01";
const char* password = "31415926";

// ====== MQTT ======
const char* mqtt_server = "192.168.0.6"; // IP do seu PC

WiFiClient espClient;
PubSubClient client(espClient);

// ==========================
// Conectar WiFi
// ==========================
void setup_wifi() {
  Serial.println("Conectando ao WiFi...");
  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  Serial.println("\nWiFi conectado!");
  Serial.print("IP do ESP32: ");
  Serial.println(WiFi.localIP());
}

// ==========================
// Reconectar MQTT
// ==========================
void reconnect() {
  while (!client.connected()) {
    Serial.print("Conectando ao MQTT... ");

    if (client.connect("ESP32_HTU21D")) {
      Serial.println("Conectado!");
    } else {
      Serial.print("Erro, rc=");
      Serial.print(client.state());
      Serial.println(" tentando novamente em 2s");
      delay(2000);
    }
  }
}

// ==========================
// Ler Temperatura
// ==========================
float readTemperature() {
  Wire.beginTransmission(HTU21D_ADDR);
  Wire.write(0xF3);
  Wire.endTransmission();
  delay(50);

  Wire.requestFrom(HTU21D_ADDR, 2);
  if (Wire.available() < 2) return NAN;

  uint16_t raw = (Wire.read() << 8) | Wire.read();
  raw &= 0xFFFC;

  return -46.85 + (175.72 * raw / 65536.0);
}

// ==========================
// Ler Umidade
// ==========================
float readHumidity() {
  Wire.beginTransmission(HTU21D_ADDR);
  Wire.write(0xF5);
  Wire.endTransmission();
  delay(50);

  Wire.requestFrom(HTU21D_ADDR, 2);
  if (Wire.available() < 2) return NAN;

  uint16_t raw = (Wire.read() << 8) | Wire.read();
  raw &= 0xFFFC;

  return -6.0 + (125.0 * raw / 65536.0);
}

// ==========================
// SETUP
// ==========================
void setup() {
  Serial.begin(115200);
  Wire.begin(21, 22); // SDA 21, SCL 22

  setup_wifi();

  client.setServer(mqtt_server, 1883);
}

// ==========================
// LOOP
// ==========================
void loop() {

  if (!client.connected()) {
    reconnect();
  }

  client.loop();

  float temp = readTemperature();
  float hum = readHumidity();

  if (!isnan(temp) && !isnan(hum)) {

    Serial.println("----- SENSOR -----");
    Serial.print("Temperatura: ");
    Serial.print(temp);
    Serial.println(" °C");

    Serial.print("Umidade: ");
    Serial.print(hum);
    Serial.println(" %");
    Serial.println("------------------");

    char msg[100];
    sprintf(msg, "{\"temperatura\":%.2f,\"umidade\":%.2f}", temp, hum);

    client.publish("servidor/sensor1", msg);

  } else {
    Serial.println("Erro ao ler sensor!");
  }

  delay(5000);
}