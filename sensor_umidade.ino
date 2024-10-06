#define HUMIDADE_PIN A2  // Pino analógico onde o sensor de umidade simples está conectado

void setup() {
  Serial.begin(9600);  // Inicializa a comunicação serial
}

void loop() {
  // Sensor de umidade simples
  int humidadeValue = analogRead(HUMIDADE_PIN);  // Lê o valor analógico do sensor de umidade
  Serial.print("Umidade do solo: ");
  Serial.println(humidadeValue);  // Exibe o valor no monitor serial

  delay(2000);  // Aguarda 2 segundos antes da próxima leitura
}
