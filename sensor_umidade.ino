#define HUMIDADE_PIN A2 

void setup() {
  Serial.begin(9600); 
}

void loop() {
  int ldrValue = analogRead(A0);
  Serial.print("Luminosidade (LDR): ");
  Serial.println(ldrValue);

  int tempValue = analogRead(A1); 
  float voltage = tempValue * (5.0 / 1023.0); 
  float temperature = voltage * 100; 
  Serial.print("Temperatura (LM35): ");
  Serial.println(temperature); 

  int humidadeValue = analogRead(HUMIDADE_PIN);  
  Serial.print("Umidade do solo: ");
  Serial.println(humidadeValue); 

  delay(2000); 
}

