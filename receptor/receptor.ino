#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>
#include <Servo.h>

#define CE_PIN    9
#define CSN_PIN   10
#define AIA       5
#define AIB       6
#define SERVO_PIN 3

struct ControleState {
  boolean btSTART = 0;
  boolean btSELECT = 0;
  boolean btUP = 0;
  boolean btDOWN = 0;
  boolean btLEFT = 0;
  boolean btRIGHT = 0;
  boolean btR1 = 0;
  boolean btR2 = 0;
  boolean btR3 = 0;
  boolean btL1 = 0;
  boolean btL2 = 0;
  boolean btL3 = 0;
  boolean btTRIANGLE = 0;
  boolean btCIRCLE = 0;
  boolean btSQUARE = 0;
  boolean btCROSS = 0;
  byte btRX = 0;
  byte btRY = 0;
  byte btLX = 0;
  byte btLY = 0;
};

ControleState state;

Servo servo;

RF24 radio(CE_PIN, CSN_PIN);
const byte address[6] = "00001";

long valor;

void setup() {
  pinMode(AIA, OUTPUT);
  pinMode(AIB, OUTPUT);

  servo.attach(SERVO_PIN);

  Serial.begin(115200);
  Serial.println("Iniciando receptor...");
  
  delay(1000);  //added delay to give wireless ps2 module some time to startup, before configuring it

  inicializarRadio();
}

void inicializarRadio(){
  radio.begin();
  radio.setChannel(5); // 0..127
  radio.setDataRate(RF24_250KBPS); // RF24_1MBPS, RF24_2MBPS, RF24_250KBPS
  radio.setPALevel(RF24_PA_MIN);
  //radio.setPALevel(RF24_PA_HIGH);
  radio.openReadingPipe(1, 0x1234567890L);
  radio.startListening();
  Serial.print("Radio inicializado");
}

void loop() {
  if (radio.available()){
    radio.read(&state, sizeof(state));
    controlarMotor();
    controlarServo();
    printState();
  }
  delay(5);
}

void controlarMotor(){
  if (state.btLY <= 125)  {
    analogWrite(AIA, LOW);
    analogWrite(AIB, map(state.btLY, 125, 0, 20, 255));
  } else if (state.btLY >= 130){
    analogWrite(AIA, map(state.btLY, 130, 255, 20, 255));
    analogWrite(AIB, LOW);
  } else {
    analogWrite(AIA, LOW);
    analogWrite(AIB, LOW);
  }
}

void controlarServo(){
    int direcao = map(state.btRX, 0, 255, 0, 180);
    //direcao = map(state.btRX, 0, 255, 10, 170);
    servo.write(direcao);
}

void printState(){
    Serial.print("START.......: ");
    Serial.println(state.btSTART);
    Serial.print("SELECT.......: ");
    Serial.println(state.btSELECT);

    Serial.print("SetaParaCima.......: ");
    Serial.println(state.btUP);
    Serial.print("SetaParaBaixo......: ");
    Serial.println(state.btDOWN);
    Serial.print("SetaParaEsquerda...: ");
    Serial.println(state.btLEFT);
    Serial.print("SetaParaDireita....: ");
    Serial.println(state.btRIGHT);

  /*
    Serial.print("L1: ");
    Serial.println(state.btL1);
    Serial.print("L2: ");
    Serial.println(state.btL2);
    Serial.print("L3: ");
    Serial.println(state.btL3);

    Serial.print("R1: ");
    Serial.println(state.btR1);
    Serial.print("R2: ");
    Serial.println(state.btR2);
    Serial.print("R3: ");
    Serial.println(state.btR3);

    Serial.print("TRIANGLE: ");
    Serial.println(state.btTRIANGLE);
    Serial.print("SQUARE: ");
    Serial.println(state.btSQUARE);
    Serial.print("CIRCLE: ");
    Serial.println(state.btCIRCLE);
    Serial.print("CROSS: ");
    Serial.println(state.btCROSS);
  */
    displayAnalog();

    Serial.println("================================");
}

void displayAnalog(){
  Serial.print("LEFT(");
  Serial.print(state.btLX);
  Serial.print(",");
  Serial.print(state.btLY);
  Serial.print(")");

  Serial.print(" RIGHT(");
  Serial.print(state.btRX);
  Serial.print(",");
  Serial.print(state.btRY);
  Serial.println(")");
}

