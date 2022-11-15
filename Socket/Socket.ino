#include <SocketIoClient.h>
#include <WiFi.h>
#include <WiFiMulti.h>

WiFiMulti WiFiMulti;
SocketIoClient webSocket;

//CONST VARIABLES
const char* ssid = "PuetaWifi";
const char* password = "pueta@localhost:8080";
const char* HOST = "137.184.70.22";
//evento webSocket
void event(const char * payload, size_t length){
  Serial.printf("Activando alarma de emergencia: %s\n", payload);
}

void setup() {
  Serial.begin(115200);

  Serial.setDebugOutput(true);
  //Connectar a Wifi
  WiFiMulti.addAP(ssid, password);
  Serial.println("Intentando conectar a wifi");
  while (WiFiMulti.run()!= WL_CONNECTED) {
    Serial.println(".");
    delay(2900);
  }

  Serial.println("\nConectado a la red");
  Serial.print("IP address: ");
  Serial.println(WiFi.localIP());

  //Recibir evento desde el Seridor
  webSocket.on("alert",event);
  webSocket.begin(HOST,3000,"/");

}

void loop() {
  /* if((WiFi.status() == WL_CONNECTED)){
    Serial.println("Ya existe conexion, intenta hacer ping.");
    delay(10000);
  }
  else{
    Serial.println("Conexion perdida");
  } */
  webSocket.loop();
  
  int count = 0;
  count++;
    if (count == 18000){
        count = 0;

        // Send data to Server
        webSocket.emit("alert","Oee desde esp32");

    }
}

