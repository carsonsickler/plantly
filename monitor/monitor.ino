int RGB_BUILTIN = 8;

void setup(){
  pinMode(RGB_BUILTIN, OUTPUT);
  digitalWrite(RGB_BUILTIN, HIGH);
  delay(1000);
  digitalWrite(RGB_BUILTIN, LOW);
  delay(1000);
}

void loop(){

}