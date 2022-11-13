#include <SocketIoClient.h>
#include <WiFi.h>


SocketIoClient webSocket;

//CONST VARIABLES
const char* ssid = "Claro_eeeeeeeee";
const char* password = "44444444444";
const char* HOST = "http://137.184.70.22";

//evento webSocket
void event(const char * payload, size_t length){
  Serial.printf("Activando alarma de emergencia: %s\n", payload);
}

void setup() {
  Serial.begin(115200);

  //Connectar a Wifi
  WiFi.begin(ssid, password);
  Serial.println("Intentando conectar a wifi");
  while (WiFi.status() != WL_CONNECTED) {
    Serial.println(".");
    delay(500);
  }

  Serial.println("\nConeectado a la red");
  Serial.print("IP address: ");
  Serial.println(WiFi.localIP());

  //Recibir evento desde el Seridor
  webSocket.on("alert",event);
  webSocket.begin(HOST);
}

void loop() {
  if((WiFi.status() == WL_CONNECTED)){
    Serial.println("Ya existe conexion, intenta hacer ping.");
    delay(10000);
  }
  else{
    Serial.println("Conexion perdida");
  }
}

