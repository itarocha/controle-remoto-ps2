#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>
#include <PS2X_lib.h>

#define PS2_DAT       5 //15 //13  //14 MARROM     
#define PS2_CMD       3 //14 //11  //15 LARANJA
#define PS2_SEL       4 //12 //10  //16 AMARELO
#define PS2_CLK       2 //13 //12  //17 AZUL

#define CE_PIN        9
#define CSN_PIN       10

/******************************************************************
 * select modes of PS2 controller:
 *   - pressures = analog reading of push-butttons 
 *   - rumble    = motor rumbling
 * uncomment 1 of the lines for each mode selection
 ******************************************************************/
//#define pressures   true
#define pressures   false
//#define rumble      true
#define rumble      false

#define BT_START      1000
#define BT_SELECT     1001
#define BT_L1         1002
#define BT_L2         1003
#define BT_L3         1004
#define BT_R1         1005
#define BT_R2         1006
#define BT_R3         1007
#define BT_UP         1008
#define BT_DOWN       1009
#define BT_LEFT       1010
#define BT_RIGHT      1011
#define BT_TRIANGLE   1012
#define BT_SQUARE     1013
#define BT_CIRCLE     1014
#define BT_CROSS      1015

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

PS2X ps2x;

RF24 radio(CE_PIN, CSN_PIN);

//long valor = 1;

int error = 0;
byte type = 0;
byte vibrate = 0;

void setup() {
  Serial.begin(115200);
  Serial.println("Iniciando transmissor...");
  pinMode(LED_BUILTIN, OUTPUT);

  delay(1000);

  inicializarRadio();
  inicializarControlePS2();
}

void inicializarRadio(){
  radio.begin();
  radio.setChannel(5);
  radio.setDataRate(RF24_250KBPS); // RF24_1MBPS, RF24_2MBPS, RF24_250KBPS
  //radio.setPALevel(RF24_PA_MIN);
  radio.setPALevel(RF24_PA_HIGH);
  radio.setAutoAck(false);
  //radio.setPALevel(RF24_PA_HIGH);
  radio.stopListening();
  radio.openWritingPipe(0x1234567890L);
  Serial.print("Radio inicializado");
}

void inicializarControlePS2(){
  error = ps2x.config_gamepad(PS2_CLK, PS2_CMD, PS2_SEL, PS2_DAT, pressures, rumble);
  
  if(error == 0){
    Serial.print("Found Controller, configured successful ");
    Serial.print("pressures = ");
	if (pressures)
	  Serial.println("true ");
	else
	  Serial.println("false");
	Serial.print("rumble = ");
	if (rumble)
	  Serial.println("true)");
	else
	  Serial.println("false");
    Serial.println("Try out all the buttons, X will vibrate the controller, faster as you press harder;");
    Serial.println("holding L1 or R1 will print out the analog stick values.");
    Serial.println("Note: Go to www.billporter.info for updates and to report bugs.");
  }  
  else if(error == 1)
    Serial.println("No controller found, check wiring, see readme.txt to enable debug. visit www.billporter.info for troubleshooting tips");
   
  else if(error == 2)
    Serial.println("Controller found but not accepting commands. see readme.txt to enable debug. Visit www.billporter.info for troubleshooting tips");

  else if(error == 3)
    Serial.println("Controller refusing to enter Pressures mode, may not support it. ");
  
  type = ps2x.readType(); 
  switch(type) {
    case 0:
      Serial.print("Encontrado controle desconhecido ");
      break;
    case 1:
      Serial.print("DualShock Controller found ");
      break;
    case 2:
      Serial.print("GuitarHero Controller found ");
      break;
	case 3:
      Serial.print("Wireless Sony DualShock Controller found ");
      break;
   }
}

void loop(){
  gerenciarEstadoPS2();
  /*
  Serial.print("enviando ");
  Serial.print(valor);
  Serial.println(" ...");
  bool retorno = radio.write(&valor, sizeof(valor));
  delay(50);
  valor++;
  if (valor == 50000){
    valor = 1;
  }
  */
  delay(50);
}

void gerenciarEstadoPS2(){
  ps2x.read_gamepad(false, vibrate); //read controller and set large motor to spin at 'vibrate' speed
  
  /*
  if(ps2x.Button(PSB_START))         //will be TRUE as long as button is pressed
    Serial.println("START");
  if(ps2x.Button(PSB_SELECT))
    Serial.println("SELECT");      
  */

  //vibrate = ps2x.Analog(PSAB_CROSS);  //this will set the large motor vibrate speed based on how hard you press the blue (X) button
  vibrate = LOW;

  boolean mudou = false;
  if (ps2x.NewButtonState()) {        //will be TRUE if any button changes state (on to off, or off to on)
    if (ps2x.Button(PSB_START)) updateState(BT_START, HIGH); else updateState(BT_START, LOW);
    if (ps2x.Button(PSB_SELECT)) updateState(BT_SELECT, HIGH); else updateState(BT_SELECT, LOW);

    if (ps2x.Button(PSB_L1)) updateState(BT_L1, HIGH); else updateState(BT_L1, LOW);
    if (ps2x.Button(PSB_L2)) updateState(BT_L2, HIGH); else updateState(BT_L2, LOW);
    if (ps2x.Button(PSB_L3)) updateState(BT_L3, HIGH); else updateState(BT_L3, LOW);

    if (ps2x.Button(PSB_R1)) updateState(BT_R1, HIGH); else updateState(BT_R1, LOW);
    if (ps2x.Button(PSB_R2)) updateState(BT_R2, HIGH); else updateState(BT_R2, LOW);
    if (ps2x.Button(PSB_R3)) updateState(BT_R3, HIGH); else updateState(BT_R3, LOW);

    if (ps2x.Button(PSB_PAD_UP)) updateState(BT_UP, HIGH); else updateState(BT_UP, LOW);
    if (ps2x.Button(PSB_PAD_DOWN)) updateState(BT_DOWN, HIGH); else updateState(BT_DOWN, LOW);
    if (ps2x.Button(PSB_PAD_LEFT)) updateState(BT_LEFT, HIGH); else updateState(BT_LEFT, LOW);
    if (ps2x.Button(PSB_PAD_RIGHT)) updateState(BT_RIGHT, HIGH); else updateState(BT_RIGHT, LOW);

    if (ps2x.Button(PSB_TRIANGLE)) updateState(BT_TRIANGLE, HIGH); else updateState(BT_TRIANGLE, LOW);
    if (ps2x.Button(PSB_CIRCLE)) updateState(BT_CIRCLE, HIGH); else updateState(BT_CIRCLE, LOW);
    if (ps2x.Button(PSB_SQUARE)) updateState(BT_SQUARE, HIGH); else updateState(BT_SQUARE, LOW);
    if (ps2x.Button(PSB_CROSS)) updateState(BT_CROSS, HIGH); else updateState(BT_CROSS, LOW);

    mudou = true;

    printState();
  }

  byte rx = ps2x.Analog(PSS_RX);
  if (rx != state.btRX) {
    mudou = true;
    state.btRX = rx;
    displayAnalog();
  }
  
  byte ry = ps2x.Analog(PSS_RY);
  if (ry != state.btRY) {
    mudou = true;
    state.btRY = ry;
    displayAnalog();
  }

  byte lx = ps2x.Analog(PSS_LX);
  if (lx != state.btLX) {
    mudou = true;
    state.btLX = lx;
    displayAnalog();
  }

  byte ly = ps2x.Analog(PSS_LY);
  if (ly != state.btLY) {
    mudou = true;
    state.btLY = ly;
    displayAnalog();
  }

  // mudou sempre enviando...
  mudou = true;

  if (mudou) {
    Serial.println("Enviando...");
    radio.write(&state, sizeof(state));
    mudou = false;
  }
  
}

void updateState(unsigned int bt, boolean newValue){
  // char* tecla = "";
  switch (bt){
    case BT_START:
      state.btSTART = newValue;
      break;
    case BT_SELECT:
      state.btSELECT = newValue;
      break;

    case BT_L1:
      state.btL1 = newValue;
      break;
    case BT_L2:
      state.btL2 = newValue;
      break;
    case BT_L3:
      state.btL3 = newValue;
      break;
    case BT_R1:
      state.btR1 = newValue;
      break;
    case BT_R2:
      state.btR2 = newValue;
      break;
    case BT_R3:
      state.btR3 = newValue;
      break;

    case BT_UP:
      state.btUP = newValue;
      break;
    case BT_DOWN:
      state.btDOWN = newValue;
      break;
    case BT_LEFT:
      state.btLEFT = newValue;
      break;
    case BT_RIGHT:
      state.btRIGHT = newValue;
      break;

    case BT_TRIANGLE:
      state.btTRIANGLE = newValue;
      break;
    case BT_SQUARE:
      state.btSQUARE = newValue;
      break;
    case BT_CIRCLE:
      state.btCIRCLE = newValue;
      break;
    case BT_CROSS:
      state.btCROSS = newValue;
      break;
  }
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

    Serial.println("================================");
}

void displayAnalog(){
  Serial.print("(");
  Serial.print(state.btLX);
  Serial.print(",");
  Serial.print(state.btLY);
  Serial.print(")");

  Serial.print(" (");
  Serial.print(state.btRX);
  Serial.print(",");
  Serial.print(state.btRY);
  Serial.println(")");
}

