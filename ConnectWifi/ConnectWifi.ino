#include <WiFi.h>
const char* ssid = "Claro_eeeeeeeee";
const char* password = "44444444444";


//Hola mundo

void setup() {
  Serial.begin(115200);
  WiFi.begin(ssid, password);
  Serial.println("Intentando conectar a wifi");
  while (WiFi.status() != WL_CONNECTED) {
    Serial.println(".");
    delay(500);
  }

  Serial.println("\nConeectado a la red");
  Serial.print("IP address: ");
  Serial.println(WiFi.localIP());
}

void loop() {
  // put your main code here, to run repeatedly:
  // Serial.println("este es el Loop");
  //delay(2000);
  if((WiFi.status() == WL_CONNECTED)){
    Serial.println("Ya existe conexion, intenta hacer ping.");
    delay(5000);
  }
  else{
    Serial.println("Conexion perdida");
  }
}