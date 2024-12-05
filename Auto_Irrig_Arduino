#include <OneWire.h>
#include <DallasTemperature.h>

// Definições de pinos
#define PINO_UMIDADE A0
#define PINO_LDR A1
#define PINO_RELE 10
#define PINO_DS18B20 2

// Configuração do sensor de temperatura DS18B20
OneWire oneWire(PINO_DS18B20);
DallasTemperature sensors(&oneWire);

// Função para prever irrigação com base nos valores brutos
bool preverIrrigacaoIA(float temperatura, int umidadeBruto, int luminosidadeBruto) {
    // Permite irrigação se a umidade estiver acima de 750 (solo seco)
    if (umidadeBruto > 750) {
        Serial.println("Decisão: Solo seco detectado. Irrigação necessária.");
        return true;
    }

    // Lógica adicional da árvore de decisão
    if (temperatura > 30.5) {
        if (luminosidadeBruto > 65) { // Ajuste para valores reais do sensor
            return true;
        } else {
            return false;
        }
    } else {
        if (luminosidadeBruto > 75) { // Ajuste para valores reais do sensor
            return true;
        } else {
            return false;
        }
    }
}

void setup() {
    Serial.begin(9600); // Inicializa a comunicação serial
    sensors.begin();    // Inicializa o sensor de temperatura

    // Configuração dos pinos
    pinMode(PINO_UMIDADE, INPUT);
    pinMode(PINO_LDR, INPUT);
    pinMode(PINO_RELE, OUTPUT);
    digitalWrite(PINO_RELE, HIGH); // Certifica-se de que o relé está desligado inicialmente
}

void loop() {
    // Leitura dos sensores sem conversão
    int umidadeBruto = analogRead(PINO_UMIDADE); // Leitura bruta do sensor de umidade
    int luminosidadeBruto = analogRead(PINO_LDR); // Leitura bruta do sensor de luminosidade
    sensors.requestTemperatures();                // Solicita a leitura da temperatura
    float temperatura = sensors.getTempCByIndex(0); // Obtém a temperatura em °C

    // Exibir leituras brutas no Monitor Serial
    Serial.print("Temperatura (°C): ");
    Serial.println(temperatura);
    Serial.print("Umidade (bruto): ");
    Serial.println(umidadeBruto);
    Serial.print("Luminosidade (bruto): ");
    Serial.println(luminosidadeBruto);

    // Decisão com base na árvore de decisão treinada
    if (preverIrrigacaoIA(temperatura, umidadeBruto, luminosidadeBruto)) {
        Serial.println("Decisão: Ativando irrigação...");
        digitalWrite(PINO_RELE, LOW); // Ativa o relé para iniciar a irrigação
        delay(5000);                   // Aguarda 5 segundos para a irrigação
        digitalWrite(PINO_RELE, HIGH);  // Desativa o relé após o tempo
        Serial.println("Decisão: Irrigação concluída.");

        // Releia os sensores para avaliar a nova condição
        umidadeBruto = analogRead(PINO_UMIDADE);
        Serial.print("Umidade após irrigação (bruto): ");
        Serial.println(umidadeBruto);

        // Verifique novamente se é necessário irrigar
        if (umidadeBruto > 750) {
            Serial.println("Solo ainda seco após irrigação. Continuando irrigação.");
            return; // O loop será reiniciado automaticamente
        } else {
            Serial.println("Solo agora úmido. Não é necessário continuar irrigação.");
        }
    } else {
        Serial.println("Decisão: Não é necessário irrigar.");
    }

    delay(15000); // Pausa de 5 segundos antes da próxima atualização
}
