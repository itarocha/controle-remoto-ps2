#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>

// Definição dos pinos do motor (L298N)
#define IN1 2     // Motor Esquerdo - Sentido
#define IN2 3     // Motor Esquerdo - Sentido
#define IN3 4     // Motor Direito - Sentido
#define IN4 5     // Motor Direito - Sentido
#define ENA 9     // Motor Esquerdo - Velocidade (PWM)
#define ENB 10    // Motor Direito - Velocidade (PWM)

// Definição dos pinos do NRF24L01
#define CE_PIN  7
#define CSN_PIN 8

// Estrutura do pacote de dados (deve ser igual ao transmissor)
struct Comando {
  byte direcao;     // Frente, Trás, Esquerda, Direita
  byte velocidade;  // 0-255
  byte freio;       // 0 ou 1
};

RF24 radio(CE_PIN, CSN_PIN); // Cria o objeto radio
const uint64_t pipe = 0xE8E8F0F0E1LL; // Endereço de comunicação
Comando dados; // Variável para armazenar os dados recebidos

void setup() {
  // Configura os pinos dos motores
  pinMode(IN1, OUTPUT);
  pinMode(IN2, OUTPUT);
  pinMode(IN3, OUTPUT);
  pinMode(IN4, OUTPUT);
  pinMode(ENA, OUTPUT);
  pinMode(ENB, OUTPUT);
  
  // Inicia a comunicação serial (para debug)
  Serial.begin(9600);
  
  // Inicia o módulo de rádio
  radio.begin();
  radio.openReadingPipe(1, pipe);
  radio.startListening();
}

void loop() {
  if (radio.available()) {
    radio.read(&dados, sizeof(dados));
    executarComando();
  } else {
    // Se perder conexão, para o carrinho
    parar();
  }
}

void executarComando() {
  // Aplica a velocidade nos motores
  analogWrite(ENA, dados.velocidade);
  analogWrite(ENB, dados.velocidade);

  // Executa ações conforme a direção
  switch(dados.direcao) {
    case 0: // Frente
      frente();
      break;
    case 1: // Trás
      tras();
      break;
    case 2: // Esquerda
      esquerda();
      break;
    case 3: // Direita
      direita();
      break;
    default: // Parar
      parar();
  }

  // Aplica freio se necessário
  if (dados.freio == 1) {
    freio();
  }
}

// Funções de controle dos motores
void frente() {
  digitalWrite(IN1, HIGH);
  digitalWrite(IN2, LOW);
  digitalWrite(IN3, HIGH);
  digitalWrite(IN4, LOW);
}

void tras() {
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, HIGH);
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, HIGH);
}

void esquerda() {
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, HIGH);
  digitalWrite(IN3, HIGH);
  digitalWrite(IN4, LOW);
}

void direita() {
  digitalWrite(IN1, HIGH);
  digitalWrite(IN2, LOW);
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, HIGH);
}

void parar() {
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, LOW);
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, LOW);
}

void freio() {
  digitalWrite(IN1, HIGH);
  digitalWrite(IN2, HIGH);
  digitalWrite(IN3, HIGH);
  digitalWrite(IN4, HIGH);
  delay(100); // Tempo de frenagem
  parar();
}
