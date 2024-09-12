# Projeto: Sistema de Irrigação Inteligente com Arduino e IA

## 1. Introdução
O projeto visa desenvolver um sistema automatizado de irrigação para plantas, que utiliza sensores de umidade do solo conectados a um Arduino para medir os níveis de umidade. Através de um modelo de Inteligência Artificial (IA), o sistema será capaz de acionar a irrigação apenas quando necessário, economizando água e garantindo a saúde da planta.

## 2. Objetivo
Criar um sistema de irrigação inteligente que monitora em tempo real a umidade do solo e aciona automaticamente a irrigação quando os níveis de umidade caem abaixo de um determinado valor, utilizando IA para otimizar os momentos de irrigação.

## 3. Especificações Funcionais (RF)

- **RF01**: O sistema deve medir de hora em hora a umidade do solo através de um sensor conectado ao Arduino/Esp-01s.
- **RF02**: O Arduino/Esp-01s deve enviar os dados coletados para a unidade de controle, onde serão processados por um modelo de IA.
- **RF03**: A IA deve prever a necessidade de irrigação com base em condições climáticas (se disponível), histórico de irrigação e umidade do solo.
- **RF04**: O sistema deve ser capaz de operar no modo manual, permitindo que o usuário ative ou desative a irrigação conforme necessário.
- **RF05**: O usuário deve poder monitorar o status do sistema em uma interface (app ou web), visualizando os níveis de umidade e o estado da irrigação (ativada/desativada).
- **RF06**: Alertas devem ser enviados ao usuário quando o sistema identificar uma falha (como falta de água ou problema no sensor).

## 4. Especificações Não Funcionais (RNF)

- **RNF01**: O sistema deve ser eficiente no consumo de energia, podendo operar com baterias ou energia solar.
- **RNF02**: A comunicação entre o Arduino e o servidor onde o modelo de IA está hospedado deve ser segura e rápida (utilizando Wi-Fi ou rede LoRa).
- **RNF03**: A interface do sistema deve ser amigável e acessível via dispositivos móveis.
- **RNF04**: O sistema deve ser modular, permitindo a adição de mais sensores ou componentes de irrigação conforme necessário.
- **RNF05**: O tempo de resposta entre a leitura da umidade do solo e a ativação da irrigação deve ser de no máximo 10 segundos.
- **RNF06**: O sistema deve continuar funcionando off-line (modo manual), acionando a irrigação baseada em umidade crítica se perder conexão com a IA.

## 5. Arquitetura do Sistema

### 5.1. Componentes de Hardware

- **Arduino Uno/Nano**:  
  Responsável por coletar os dados do sensor de umidade e acionar a bomba de água.

- **Protoboard**:
  Usada para montar circuitos eletrônicos temporariamente sem a necessidade de substituição.

- **Resistor 220R (1/4W)**:
   Usado para limitar a corrente no circuitos.

- **Sensor de Umidade do Solo**:  
  Mede a umidade do solo em tempo real, enviando dados ao Arduino.

- **Módulo de Relé**:  
  Controla a bomba de água ou sistema de irrigação baseado no sinal do Arduino.

- **Válvula Solenoide 12V**:  
  Acionada pelo relé, a bomba envia água para o sistema de irrigação.
  
- **Mangueira de Jardim**
  Conectada a valvula solenoide e torneira, para levar a água ate a planta
    
- **Engate Rápido**
  Usado para conectar a Mangueia na valvula solenoide e na torneira

- **Módulo Esp8266 Esp01s Wi-Fi**:  
  Envia os dados do Arduino para a nuvem ou servidor local, onde a IA processa as informações.

- **Fonte de Energia 12V**:  
  Fornece uma tensão constante de 12 volts para alimentar oa dispositivos e equipamentos.

### 5.2. Componentes de Software

- **Arduino IDE**:  
  Desenvolvimento e carregamento do firmware para o Arduino.

- **Modelo de IA**:  
  Utiliza Machine Learning para analisar os dados de umidade e prever a necessidade de irrigação.

- **Servidor**:  
  Processa os dados enviados pelo Arduino, hospeda o modelo de IA e envia comandos de volta.

- **Aplicativo ou Interface Web**:  
  Interface gráfica para o usuário monitorar o sistema e, opcionalmente, interagir com o modo manual.
  

### 5.3. Fluxo de Dados

- **Coleta de Dados**:  
  O sensor de umidade do solo envia dados continuamente ao Arduino/Esp01s.

- **Processamento Local**:  
  O Arduino/Esp01s realizar a checagens da umidade e gera log.

 - **Acionamento da Bomba de Água**:  
  Caso a leitura esteja abaixo da cadastrada, o Arduino aciona a bomba através do módulo de relé. 

- **Envio de Dados à Nuvem/Servidor**:  
  Via Modulo Esp/01 Wi-Fi, os dados são enviados ao servidor onde o modelo de IA está hospedado.

- **Análise por IA**:  
  A IA analisa os dados do sensor e decide se a irrigação deve ser ativada.

- **Monitoramento e Interação**:  
  O usuário pode visualizar os dados e controlar o sistema pela interface gráfica.

## Este projeto foi desenvolvido pela equipe formada por:

- **Lucas Venero**
- **Michael Varaldo**
- **Guilherme Melato**
- **Gustavo Chaves**
- **Felipe Orlamunder**

Cada membro contribuiu ativamente para a criação e desenvolvimento do sistema de irrigação inteligente, combinando conhecimentos de eletrônica, programação, inteligência artificial e design de sistemas
