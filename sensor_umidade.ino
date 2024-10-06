#define HUMIDADE_PIN A2  // Pino analógico onde o sensor de umidade simples está conectado

void setup() {
  Serial.begin(9600);  // Inicializa a comunicação serial
}

void loop() {
  // LDR (sensor de luminosidade)
  int ldrValue = analogRead(A0);  // Lê o valor analógico do LDR
  Serial.print("Luminosidade (LDR): ");
  Serial.println(ldrValue);  // Exibe o valor no monitor serial

  // LM35 (sensor de temperatura)
  int tempValue = analogRead(A1);  // Lê o valor analógico do LM35
  float voltage = tempValue * (5.0 / 1023.0);  // Converte para tensão
  float temperature = voltage * 100;  // Converte para graus Celsius
  Serial.print("Temperatura (LM35): ");
  Serial.println(temperature);  // Exibe o valor no monitor serial

  // Sensor de umidade simples
  int humidadeValue = analogRead(HUMIDADE_PIN);  // Lê o valor analógico do sensor de umidade
  Serial.print("Umidade do solo: ");
  Serial.println(humidadeValue);  // Exibe o valor no monitor serial

  delay(2000);  // Aguarda 2 segundos antes da próxima leitura
}

