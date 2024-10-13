#define HUMIDADE_PIN A2 

void setup() {
  Serial.begin(9600); 
}

void loop() {
  int humidadeValue = analogRead(HUMIDADE_PIN);  
  Serial.print("Umidade do solo: ");
  Serial.println(humidadeValue); 

  delay(2000); 
}
