#include <WiFi.h>
#include <PubSubClient.h>
#include <Arduino.h>

const char* ssid = "Claro_D771";
const char* password = "V2pZSGUFVU";
const char* mqtt_server = "mqtt3.thingspeak.com";

#define LED 2




const int min_temperatura = 10;   
const int max_temperatura = 40;   

const int min_turbidez = 0;  
const int max_turbidez = 100;   

const int min_vibracion = 0;  
const int max_vibracion = 1000;   

const int min_velocidad = 0;       
const int max_velocidad = 100;    

const int min_presion = 10;      
const int max_presion = 150;       

const int min_nivel_agua = 0;       
const int max_nivel_agua = 100;    

 int generarVelocidad() {
  return random(min_velocidad, max_velocidad + 1);
}

 int generarPresion() {
  return random(min_presion, max_presion + 1);
}

 int generarNivelAgua() {
  return random(min_nivel_agua, max_nivel_agua + 1);
}


 int generarTemperatura() {
  return random(min_temperatura, max_temperatura + 1);
}

 int generarTurbidez() {
  return random(min_turbidez, max_turbidez + 1);
}

 int generarVibracion() {
  return random(min_vibracion, max_vibracion + 1);
}


WiFiClient espClient;
PubSubClient client(espClient);

void setup() {
  Serial.begin(115200);
  delay(1000);

  WiFi.mode(WIFI_STA);  
  WiFi.begin(ssid, password);
  Serial.println("\nConectando");

  while (WiFi.status() != WL_CONNECTED) {
    Serial.print(".");
    delay(100);
  }

  Serial.println("\nConectado a la red wifi");
  Serial.print("Local ESP32 IP: ");
  Serial.println(WiFi.localIP());
  client.setServer(mqtt_server, 1883);
}

void reconnect() {
  while (!client.connected()) {
    Serial.print("Intentando conexión MQTT...");

    if (client.connect("FgIAGToXIxABKhIEMxksDBI","FgIAGToXIxABKhIEMxksDBI","7oI2iWT5XyToBlpia540wws7")) {
      Serial.println("Conectado al broker MQTT");
    } else {
      Serial.print("Error en conexión: ");
      Serial.print(client.state());
      delay(5000);
    }
  }
}


 char payload[100];
void loop() {
  if (!client.connected()) {
    reconnect();
  }
  client.loop();  
   
  int velocidad = generarVelocidad();
  int presion = generarPresion();
  int nivelAgua = generarNivelAgua();
  int turbidez = generarTurbidez();
  int temperatura = generarTemperatura();
  int vibracion = generarVibracion();
   

  snprintf(payload, sizeof(payload), "field1=%d&field2=%d&field3=%d&field4=%d&field5=%d&field6=%d", velocidad, presion, nivelAgua,temperatura,turbidez,vibracion);
  
  client.publish("channels/2773816/publish", payload);  
  delay(2000);
}
