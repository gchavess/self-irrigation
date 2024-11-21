#include <OneWire.h>
#include <DallasTemperature.h>
#include <SoftwareSerial.h>

// Definições de pinos
#define PINO_UMIDADE A0
#define PINO_LDR A1
#define PINO_RELE 10
#define PINO_DS18B20 2

// Definir pinos de comunicação com o ESP-01
#define ESP_RX 4
#define ESP_TX 5

OneWire oneWire(PINO_DS18B20);
DallasTemperature sensors(&oneWire);
SoftwareSerial espSerial(ESP_RX, ESP_TX);

const int limiteUmidade = 800;
const char* ssid = "CLARO_2GB740B9";            // Sua rede Wi-Fi
const char* password = "2VKCA94utz";            // Senha da rede Wi-Fi
const char* firebaseHost = "self-irrigation-59e17-default-rtdb.firebaseio.com";  // URL do Firebase

// Função para enviar comandos AT
void sendCommand(const char* cmd, const char* ack, int timeout) {
  Serial.println("sendCommand");
  
  // Enviar o comando AT
  espSerial.println(cmd);
  long int time = millis();
  
  // Esperar até o timeout
  while ((time + timeout) > millis()) {
    if (espSerial.available()) {
      String response = espSerial.readStringUntil('\n'); // Ler a resposta até o final da linha
      Serial.print("Resposta: ");
      Serial.println(response);  // Mostrar a resposta para depuração
      
      // Verificar se a resposta contém o 'ack'
      if (response.indexOf(ack) != -1) {
        Serial.println("Conexão Wi-Fi bem-sucedida!");
        return;
      }
    }
  }
  
  Serial.println("Falha na conexão Wi-Fi (2).");
}

void connectToWiFi() {
  Serial.println("connectToWiFi");

  sendCommand("AT", "OK", 1000);
  sendCommand("AT+CWMODE=1", "OK", 1000); // Modo Wi-Fi station
  String connectCmd = "AT+CWJAP=\"" + String(ssid) + "\",\"" + String(password) + "\"";
  
  // Aumente o tempo de espera para 30 segundos
  sendCommand(connectCmd.c_str(), "OK", 30000); // Conectar ao Wi-Fi
  
  // Testar a resposta de conexão
  if (espSerial.find("OK")) {
    Serial.println("Conexão Wi-Fi bem-sucedida!");
  } else {
    Serial.println("Falha na conexão Wi-Fi.");
  }
}


// Função para enviar dados ao Firebase
void enviarDadosFirebase(int umidade, int luz, float temperatura) {
  Serial.println("enviarDadosFirebase");

  // Formatar os dados em JSON
  String data = "{ \"umidadeSolo\": " + String(umidade) + ", \"luz\": " + String(luz) + ", \"temperatura\": " + String(temperatura) + " }";
  
  // Conectar ao Firebase via AT
  String startCmd = "AT+CIPSTART=\"TCP\",\"" + String(firebaseHost) + "\",80";
  sendCommand(startCmd.c_str(), "OK", 1000);
  
  // Montar o cabeçalho HTTP
  String httpRequest = "POST /irrigacao.json HTTP/1.1\r\n";
  httpRequest += "Host: " + String(firebaseHost) + "\r\n";
  httpRequest += "Content-Type: application/json\r\n";
  httpRequest += "Content-Length: " + String(data.length()) + "\r\n";
  httpRequest += "\r\n" + data; // Corpo da requisição com os dados em formato JSON

  // Enviar o tamanho dos dados
  String cipSendCmd = "AT+CIPSEND=" + String(httpRequest.length());
  sendCommand(cipSendCmd.c_str(), ">", 1000);
  
  // Enviar o corpo do pedido HTTP
  espSerial.print(httpRequest);  
  delay(1000);

  // Fechar a conexão
  sendCommand("AT+CIPCLOSE", "OK", 1000);
}

void testInternetConnection() {
  Serial.println("testInternetConnection");

  // Enviar comando AT para verificar a conexão com o servidor
  sendCommand("AT+PING=\"8.8.8.8\"", "OK", 5000);  // Usando o servidor DNS do Google (8.8.8.8)
  
  // Verificar resposta do comando de ping
  if (espSerial.find("OK")) {
    Serial.println("Conexão com a Internet bem-sucedida!");
  } else {
    Serial.println("Falha na conexão com a Internet.");
  }
}

void setup() {
  Serial.begin(9600);
  espSerial.begin(115200);

  // Conectar ao Wi-Fi
  connectToWiFi();

  // Testar a conexão com a Internet
  testInternetConnection();
  
  // Inicializar sensores
  sensors.begin();
  pinMode(PINO_UMIDADE, INPUT);
  pinMode(PINO_LDR, INPUT);
  pinMode(PINO_RELE, OUTPUT);
  delay(1000);
}

void loop() {
  // Leitura dos sensores
  int umidadeSolo = analogRead(PINO_UMIDADE);
  int luz = analogRead(PINO_LDR);
  sensors.requestTemperatures();
  float temperatura = sensors.getTempCByIndex(0);

  // Enviar dados para o Firebase
  enviarDadosFirebase(umidadeSolo, luz, temperatura);

  // Monitoramento no Serial
  Serial.print("Umidade: ");
  Serial.println(umidadeSolo);
  Serial.print("Luz: ");
  Serial.println(luz);
  Serial.print("Temperatura: ");
  Serial.println(temperatura);

  // Verifica o limite de umidade para ativar o relé
  if (umidadeSolo >= limiteUmidade) {
    digitalWrite(PINO_RELE, HIGH);
    Serial.println("Irrigação ativada.");
    delay(5000);
    digitalWrite(PINO_RELE, LOW);
    Serial.println("Irrigação desativada.");
  }

  delay(10000);  // Pausa para a próxima leitura
}
