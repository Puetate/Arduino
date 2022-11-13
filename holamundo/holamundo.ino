//Hola mundo

void setup() {
  Serial.begin(115200);
  Serial.print("Esto es el setup perro");
  Serial.println("Progrmando en aurduino perro");

}

void loop() {
  // put your main code here, to run repeatedly:
  Serial.println("este es el Loop");
  delay(2000); 
}
