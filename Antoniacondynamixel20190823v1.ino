//Source code para Antonia, ojos, colores y dos dynamixel

#include <Adafruit_NeoPixel.h>
#include <Dynamixel_Servo.h>

//Estados de la rutina alegre para ojos
#define ENA 0
#define ET1A 1
#define ET12A 2
#define ET13A 3
unsigned int nxstateA = ENA ; //Variable MEF ojos alegre
//Estados de la rutina normal para ojos
#define ENN 4
#define E1N 5
#define E12N 6
#define E13N 7
unsigned int nxstateN = ENN ; //Variable MEF ojos normal
//Estados de la rutina confusa para ojos
#define EIC 8
#define E1C 9
#define E12C 10
#define E13C 11
unsigned int nxstateC = EIC ; //Variable MEF ojos confusa
//Estados MEF los dynamixel
#define Semuevearribaabajo 12
#define Semueveabajolento 13
#define Semueveabajomedio 14
unsigned int EstadoDyna; //Variable MEF Dynamixel
//Variables dynamixel
servo_error_t error;
int timeout = 50; //milliseconds
unsigned long tinid;
unsigned long treld;

char val;  //Variable de la MEF que determina el estado de animo
int Hall1 = A0;
int Hall2 = A1;
int Hall3 = A2;
int Hall4 = A3;
int Hall5 = A4;
int Hall6 = A5;
int HALL1 = 0; //Variable que se pone en 1 cuando algun sensor hall se pone en LOW
int HALL2 = 0;
int HALL3 = 0;
int HALL4 = 0;
int HALL5 = 0;
int HALL6 = 0;
int SW1   = 6;
int SW2   = 7;
int SW3   = 8;
int SW4   = 9;
int Sw1 = 0; //Variable que se pone en 1 cuando algun suiche se pone en LOW
int Sw2 = 0;
int Sw3 = 0;
int Sw4 = 0;

// Which pin on the Arduino is connected to the NeoPixels
unsigned int pin = 3; // para pin de ojo izquierdo
unsigned int pin1 = 4; // para pin de las orejas
unsigned int pin2 =  5; // para pin de ojo derecho
unsigned int pin3 = 10; // para pin de la falda
unsigned int pin4 = 11; // para pin de el brazo derecho
unsigned int pin5 = 12; // para pin de el brazo izquierdo

// How many NeoPixels are attached to the Arduino?
#define NUMPIXELS     64 // para la matriz ojo izquierdo
#define NUMPIXELSD    64 // para la matriz ojo derecho
#define NUMPIXELSS    16 // para las orejas
#define NUMPIXELSF    120 // para la falda
#define NUMPIXELSB    32 // para los brazos

//Variables tiempo rutinas ojos
unsigned long tiniA;
unsigned long tiniN;
unsigned long tiniC;
unsigned long tstate;

#define RETARDOMATRIZ 50  //Variable tiempo de transicion en parpadeo
int i; // variable para ojo izquierdo
int ia; // variable para la oreja izquierda
int ib; // variable para ojo derecho

Adafruit_NeoPixel pixels = Adafruit_NeoPixel(NUMPIXELS, pin, NEO_GRB + NEO_KHZ800); // ojo izquierdo
Adafruit_NeoPixel pixels2 = Adafruit_NeoPixel(NUMPIXELSD, pin2, NEO_GRB + NEO_KHZ800); // ojo derecho
Adafruit_NeoPixel pixels1 = Adafruit_NeoPixel(NUMPIXELSS, pin1, NEO_GRB + NEO_KHZ800); // orejas
Adafruit_NeoPixel pixels3 = Adafruit_NeoPixel(NUMPIXELSF, pin3, NEO_GRB + NEO_KHZ800); // falda
Adafruit_NeoPixel pixels4 = Adafruit_NeoPixel(NUMPIXELSB, pin4, NEO_GRB + NEO_KHZ800); // brazo derecho
Adafruit_NeoPixel pixels5 = Adafruit_NeoPixel(NUMPIXELSB, pin5, NEO_GRB + NEO_KHZ800); // brazo izquierdo

void setup()
{
  pinMode (Hall1, INPUT);
  pinMode (Hall2, INPUT);
  pinMode (Hall3, INPUT);
  pinMode (Hall4, INPUT);
  pinMode (Hall5, INPUT);
  pinMode (Hall6, INPUT);
  pinMode (SW1, INPUT);
  pinMode (SW2, INPUT);
  pinMode (SW3, INPUT);
  pinMode (SW4, INPUT);
  pinMode (pin, INPUT);
  pinMode (pin1, INPUT);
  pinMode (pin2, INPUT);
  pinMode (pin3, INPUT);
  pinMode (pin4, INPUT);
  pinMode (pin5, INPUT);
  // This initializes the NeoPixel library.
  pixels.begin();
  pixels1.begin();
  pixels2.begin();
  pixels3.begin();
  pixels4.begin();
  pixels5.begin();

  Serial.begin(9600);

  i = 0;
  ia = 0;
  ib = 0;

  nxstateN = ENN;
  nxstateA = ENA;
  nxstateC = EIC;

  servo_init(&Serial1, 50, SERVO_DEFAULT_BAUD);
  error = servo_set(0x01, SERVO_REGISTER_GOAL_ANGLE, 6.283, timeout);
  error = servo_set(0x02, SERVO_REGISTER_GOAL_ANGLE, 6.283, timeout);
  delay(2000);
  EstadoDyna = 12;

  pixels.setBrightness(1);   //Ojo Izq
  pixels1.setBrightness(20);  //Orejas
  pixels2.setBrightness(1);  //Ojo Der
  pixels3.setBrightness(20);  //Falda
  pixels4.setBrightness(40);  //Brazo Der
  pixels5.setBrightness(40);  //Brazo Izq

  tiniA = millis();
  tiniN = millis();
  tiniC = millis();
  tinid = millis();
}
// 16 luces dos orejas_120 luces falda_32 luces brazo derecho_ 32 luces brazo izquierdo
void lucesconfundidaorejasfaldabrazos() {
  for (ia = 0; ia < NUMPIXELSF; ia = ia + 1 ) {
    pixels1.setPixelColor(ia, pixels1.Color(33, 121, 251));
    pixels3.setPixelColor(ia, pixels3.Color(33, 121, 251));
    pixels4.setPixelColor(ia, pixels4.Color(33, 121, 251));
    pixels5.setPixelColor(ia, pixels5.Color(33, 121, 251));
  }
  pixels1.show();
  pixels3.show();
  pixels4.show();
  pixels5.show();
  //  for (ia = NUMPIXELSS; ia < NUMPIXELSB; ia = ia + 1 ) {
  //    pixels3.setPixelColor(ia, pixels3.Color(33, 121, 251));
  //    pixels4.setPixelColor(ia, pixels4.Color(33, 121, 251));
  //    pixels5.setPixelColor(ia, pixels5.Color(33, 121, 251));
  //    pixels3.show();
  //    pixels4.show();
  //    pixels5.show();
  //  }
  //  for (ia = NUMPIXELSB; ia < NUMPIXELSF; ia = ia + 1 ) {
  //    pixels4.setPixelColor(ia, pixels4.Color(33, 121, 251));
  //    pixels5.setPixelColor(ia, pixels5.Color(33, 121, 251));
  //    pixels4.show();
  //    pixels5.show();
  //  }
}
void lucesbravaorejasfaldabrazos() { //para todo el cuerpo
  for (ia = 0; ia < NUMPIXELSF; ia = ia + 1 ) {
    pixels1.setPixelColor(ia, pixels1.Color(255, 0, 0));
    pixels3.setPixelColor(ia, pixels3.Color(255, 0, 0));
    pixels4.setPixelColor(ia, pixels4.Color(255, 0, 0));
    pixels5.setPixelColor(ia, pixels5.Color(255, 0, 0));
    pixels1.show();
    pixels3.show();
    pixels4.show();
    pixels5.show();
  }
  //  for (ia = 0; ia < NUMPIXELSF; ia = ia + 1 ) {
  //    pixels3.setPixelColor(ia, pixels3.Color(255, 0, 0));
  //    pixels3.show();
  //  }
  //  for (ia = 0; ia < NUMPIXELSB; ia = ia + 1 ) {
  //    pixels4.setPixelColor(ia, pixels4.Color(255, 0, 0));
  //    pixels5.setPixelColor(ia, pixels5.Color(255, 0, 0));
  //    pixels4.show();
  //    pixels5.show();
  //  }
}
void lucesalegreorejasfaldabrazos() { //para todo el cuerpo
  for (ia = 0; ia < NUMPIXELSF; ia = ia + 1 ) {
    pixels1.setPixelColor(ia, pixels1.Color(255, 212, 0));
    pixels3.setPixelColor(ia, pixels3.Color(255, 212, 0));
    pixels4.setPixelColor(ia, pixels4.Color(255, 212, 0));
    pixels5.setPixelColor(ia, pixels5.Color(255, 212, 0));
  }
  pixels1.show();
  pixels3.show();
  pixels4.show();
  pixels5.show();
  //  if (ia == NUMPIXELSS) {
  //    for (ia = NUMPIXELSS; ia < NUMPIXELSB; ia = ia + 1 ) {
  //      pixels3.setPixelColor(ia, pixels3.Color(255, 212, 0));
  //      pixels4.setPixelColor(ia, pixels4.Color(255, 212, 0));
  //      pixels5.setPixelColor(ia, pixels5.Color(255, 212, 0));
  //    }
  //  }
  //  if (ia == NUMPIXELSB) {
  //    for (ia = NUMPIXELSB; ia < NUMPIXELSF; ia = ia + 1 ) {
  //      pixels4.setPixelColor(ia, pixels4.Color(255, 212, 0));
  //      pixels5.setPixelColor(ia, pixels5.Color(255, 212, 0));
  //    }
  //  }
}
void lucesnormalorejasfaldabrazos() { //para todo el cuerpo
  for (ia = 0; ia < NUMPIXELSF; ia = ia + 1 ) {
    pixels1.setPixelColor(ia, pixels1.Color(255, 0, 255));
    pixels3.setPixelColor(ia, pixels3.Color(255, 0, 255));
    pixels4.setPixelColor(ia, pixels4.Color(255, 0, 255));
    pixels5.setPixelColor(ia, pixels5.Color(255, 0, 255));
  }
  //  for (ia = 0; ia < NUMPIXELSS; ia = ia + 1 ) {
  //    pixels1.setPixelColor(ia, pixels1.Color(255, 0, 255));
  //    pixels1.show();
  //  }
  //  for (ia = 0; ia < NUMPIXELSF; ia = ia + 1 ) {
  //    pixels3.setPixelColor(ia, pixels3.Color(255, 0, 255));
  //    pixels3.show();
  //  }
  //  for (ia = 0; ia < NUMPIXELSB; ia = ia + 1 ) {
  //    pixels4.setPixelColor(ia, pixels4.Color(255, 0, 255));
  //    pixels5.setPixelColor(ia, pixels5.Color(255, 0, 255));
  //    pixels4.show();
  //    pixels5.show();
  //  }
  pixels1.show();
  pixels3.show();
  pixels4.show();
  pixels5.show();
}
void unoa() {  //Ojo derecho primera linea abajo y arriba
  pixels2.setPixelColor(3, pixels2.Color(255, 255, 255));
  pixels2.setPixelColor(4, pixels2.Color(255, 255, 255));
  pixels2.setPixelColor(59, pixels2.Color(255, 255, 255));
  pixels2.setPixelColor(60, pixels2.Color(255, 255, 255));
  pixels2.show(); // This sends the updated pixel color to the hardware.
}
void unob() {  //Ojo izquierdo primera linea abajo y arriba
  pixels.setPixelColor(3, pixels.Color(255, 255, 255));
  pixels.setPixelColor(4, pixels.Color(255, 255, 255));
  pixels.setPixelColor(59, pixels.Color(255, 255, 255));
  pixels.setPixelColor(60, pixels.Color(255, 255, 255));
  pixels.show();
}
void dosa () { //Ojo derecho segunda linea abajo y arriba
  pixels2.setPixelColor(10, pixels2.Color(255, 255, 255));
  pixels2.setPixelColor(11, pixels2.Color(255, 255, 255));
  pixels2.setPixelColor(12, pixels2.Color(255, 255, 255));
  pixels2.setPixelColor(13, pixels2.Color(255, 255, 255));
  pixels2.setPixelColor(50, pixels2.Color(255, 255, 255));
  pixels2.setPixelColor(51, pixels2.Color(255, 255, 255));
  pixels2.setPixelColor(52, pixels2.Color(255, 255, 255));
  pixels2.setPixelColor(53, pixels2.Color(255, 255, 255));
  pixels2.show(); // This sends the updated pixel color to the hardware.
}
void dosb () { //Ojo izquierdo segunda linea abajo y arriba
  pixels.setPixelColor(10, pixels.Color(255, 255, 255));
  pixels.setPixelColor(11, pixels.Color(255, 255, 255));
  pixels.setPixelColor(12, pixels.Color(255, 255, 255));
  pixels.setPixelColor(13, pixels.Color(255, 255, 255));
  pixels.setPixelColor(50, pixels.Color(255, 255, 255));
  pixels.setPixelColor(51, pixels.Color(255, 255, 255));
  pixels.setPixelColor(52, pixels.Color(255, 255, 255));
  pixels.setPixelColor(53, pixels.Color(255, 255, 255));
  pixels.show();
}
void tresa() { //Ojo derecho tercera linea abajo y arriba
  pixels2.setPixelColor(17, pixels2.Color(255, 255, 255));
  pixels2.setPixelColor(18, pixels2.Color(255, 255, 255));
  pixels2.setPixelColor(19, pixels2.Color(255, 255, 255));
  pixels2.setPixelColor(20, pixels2.Color(255, 255, 255));
  pixels2.setPixelColor(21, pixels2.Color(255, 255, 255));
  pixels2.setPixelColor(22, pixels2.Color(255, 255, 255));
  pixels2.setPixelColor(41, pixels2.Color(255, 255, 255));
  pixels2.setPixelColor(42, pixels2.Color(255, 255, 255));
  pixels2.setPixelColor(43, pixels2.Color(255, 255, 255));
  pixels2.setPixelColor(44, pixels2.Color(255, 255, 255));
  pixels2.setPixelColor(45, pixels2.Color(255, 255, 255));
  pixels2.setPixelColor(46, pixels2.Color(255, 255, 255));
  pixels2.show(); // This sends the updated pixel color to the hardware.
}
void tresb() { //Ojo izquierdo tercera linea abajo y arriba
  pixels.setPixelColor(17, pixels.Color(255, 255, 255));
  pixels.setPixelColor(18, pixels.Color(255, 255, 255));
  pixels.setPixelColor(19, pixels.Color(255, 255, 255));
  pixels.setPixelColor(20, pixels.Color(255, 255, 255));
  pixels.setPixelColor(21, pixels.Color(255, 255, 255));
  pixels.setPixelColor(22, pixels.Color(255, 255, 255));
  pixels.setPixelColor(41, pixels.Color(255, 255, 255));
  pixels.setPixelColor(42, pixels.Color(255, 255, 255));
  pixels.setPixelColor(43, pixels.Color(255, 255, 255));
  pixels.setPixelColor(44, pixels.Color(255, 255, 255));
  pixels.setPixelColor(45, pixels.Color(255, 255, 255));
  pixels.setPixelColor(46, pixels.Color(255, 255, 255));
  pixels.show();
}
void cuatroa () {  //Ojo derecho cuarta linea abajo y arriba
  pixels2.setPixelColor(25, pixels2.Color(255, 255, 255));
  pixels2.setPixelColor(26, pixels2.Color(255, 255, 255));
  pixels2.setPixelColor(27, pixels2.Color(255, 255, 255));
  pixels2.setPixelColor(28, pixels2.Color(255, 255, 255));
  pixels2.setPixelColor(29, pixels2.Color(255, 255, 255));
  pixels2.setPixelColor(30, pixels2.Color(255, 255, 255));
  pixels2.setPixelColor(33, pixels2.Color(255, 255, 255));
  pixels2.setPixelColor(34, pixels2.Color(255, 255, 255));
  pixels2.setPixelColor(35, pixels2.Color(255, 255, 255));
  pixels2.setPixelColor(36, pixels2.Color(255, 255, 255));
  pixels2.setPixelColor(37, pixels2.Color(255, 255, 255));
  pixels2.setPixelColor(38, pixels2.Color(255, 255, 255));
  pixels2.show();
}
void cuatrob () {//Ojo izquierdo cuarta linea abajo y arriba
  pixels.setPixelColor(25, pixels.Color(255, 255, 255));
  pixels.setPixelColor(26, pixels.Color(255, 255, 255));
  pixels.setPixelColor(27, pixels.Color(255, 255, 255));
  pixels.setPixelColor(28, pixels.Color(255, 255, 255));
  pixels.setPixelColor(29, pixels.Color(255, 255, 255));
  pixels.setPixelColor(30, pixels.Color(255, 255, 255));
  pixels.setPixelColor(33, pixels.Color(255, 255, 255));
  pixels.setPixelColor(34, pixels.Color(255, 255, 255));
  pixels.setPixelColor(35, pixels.Color(255, 255, 255));
  pixels.setPixelColor(36, pixels.Color(255, 255, 255));
  pixels.setPixelColor(37, pixels.Color(255, 255, 255));
  pixels.setPixelColor(38, pixels.Color(255, 255, 255));
  pixels.show();
}
void ojoneutroderechaizq() { //OJOS NORMALES Y SE ABREN DEL CENTRO A LOS EXTREMOS
  for (ib = 3; ib <= 27; ib = ib + 8) {
    if (ib == 3) {
      unoa();
      unob();
    }
    if (ib == 11) {
      dosa();
      dosb();
    }
    if (ib == 19) {
      tresa();
      tresb();
    }
    if (ib == 27) {
      cuatroa();
      cuatrob();
    }
  }
}
void ojoneutroderecha() { //OJO DERECHO NORMAL Y SE ABRE DEL CENTRO A LOS EXTREMOS
  for (ib = 3; ib <= 27; ib = ib + 8) {
    if (ib == 3) {
      unoa();
    }
    if (ib == 11) {
      dosa();
    }
    if (ib == 19) {
      tresa();
    }
    if (ib == 27) {
      cuatroa();
    }
  }
}
void ojoneutroizq() { //OJO IZQUIEERDO NORMAL Y SE ABRE DEL CENTRO A LOS EXTREMOS
  for (ib = 3; ib <= 27; ib = ib + 8) {
    if (ib == 3) {
      unob();
    }
    if (ib == 11) {
      dosb();
    }
    if (ib == 19) {
      tresb();
    }
    if (ib == 27) {
      cuatrob();
    }
  }
}
void trans1derechaizq() //MEDIO CERRADO
{
  pixels2.clear();
  pixels.clear();
  for (ib = 19 ; ib <= 27; ib = ib + 8) {
    if (ib == 19) {
      pixels2.setPixelColor(17, pixels2.Color(255, 255, 255));
      pixels2.setPixelColor(18, pixels2.Color(255, 255, 255));
      pixels2.setPixelColor(19, pixels2.Color(255, 255, 255));
      pixels2.setPixelColor(20, pixels2.Color(255, 255, 255));
      pixels2.setPixelColor(21, pixels2.Color(255, 255, 255));
      pixels2.setPixelColor(22, pixels2.Color(255, 255, 255));
      pixels2.setPixelColor(41, pixels2.Color(255, 255, 255));
      pixels2.setPixelColor(42, pixels2.Color(255, 255, 255));
      pixels2.setPixelColor(43, pixels2.Color(255, 255, 255));
      pixels2.setPixelColor(44, pixels2.Color(255, 255, 255));
      pixels2.setPixelColor(45, pixels2.Color(255, 255, 255));
      pixels2.setPixelColor(46, pixels2.Color(255, 255, 255));
      pixels.setPixelColor(17, pixels.Color(255, 255, 255));
      pixels.setPixelColor(18, pixels.Color(255, 255, 255));
      pixels.setPixelColor(19, pixels.Color(255, 255, 255));
      pixels.setPixelColor(20, pixels.Color(255, 255, 255));
      pixels.setPixelColor(21, pixels.Color(255, 255, 255));
      pixels.setPixelColor(22, pixels.Color(255, 255, 255));
      pixels.setPixelColor(41, pixels.Color(255, 255, 255));
      pixels.setPixelColor(42, pixels.Color(255, 255, 255));
      pixels.setPixelColor(43, pixels.Color(255, 255, 255));
      pixels.setPixelColor(44, pixels.Color(255, 255, 255));
      pixels.setPixelColor(45, pixels.Color(255, 255, 255));
      pixels.setPixelColor(46, pixels.Color(255, 255, 255));
      pixels2.show(); // This sends the updated pixel color to the hardware.
      pixels.show();
    }
    if (ib == 27) {
      pixels2.setPixelColor(25, pixels2.Color(255, 255, 255));
      pixels2.setPixelColor(26, pixels2.Color(255, 255, 255));
      pixels2.setPixelColor(27, pixels2.Color(255, 255, 255));
      pixels2.setPixelColor(28, pixels2.Color(255, 255, 255));
      pixels2.setPixelColor(29, pixels2.Color(255, 255, 255));
      pixels2.setPixelColor(30, pixels2.Color(255, 255, 255));
      pixels2.setPixelColor(33, pixels2.Color(255, 255, 255));
      pixels2.setPixelColor(34, pixels2.Color(255, 255, 255));
      pixels2.setPixelColor(35, pixels2.Color(255, 255, 255));
      pixels2.setPixelColor(36, pixels2.Color(255, 255, 255));
      pixels2.setPixelColor(37, pixels2.Color(255, 255, 255));
      pixels2.setPixelColor(38, pixels2.Color(255, 255, 255));
      pixels.setPixelColor(25, pixels.Color(255, 255, 255));
      pixels.setPixelColor(26, pixels.Color(255, 255, 255));
      pixels.setPixelColor(27, pixels.Color(255, 255, 255));
      pixels.setPixelColor(28, pixels.Color(255, 255, 255));
      pixels.setPixelColor(29, pixels.Color(255, 255, 255));
      pixels.setPixelColor(30, pixels.Color(255, 255, 255));
      pixels.setPixelColor(33, pixels.Color(255, 255, 255));
      pixels.setPixelColor(34, pixels.Color(255, 255, 255));
      pixels.setPixelColor(35, pixels.Color(255, 255, 255));
      pixels.setPixelColor(36, pixels.Color(255, 255, 255));
      pixels.setPixelColor(37, pixels.Color(255, 255, 255));
      pixels.setPixelColor(38, pixels.Color(255, 255, 255));
      pixels2.show();
      pixels.show();
    }
  }
}
void trans1 () {
  pixels2.clear();
  for (ib = 11 ; ib <= 27; ib = ib + 8) {
    if (ib == 11) {
      pixels2.setPixelColor(11, pixels2.Color(255, 255, 255));
      pixels2.setPixelColor(12, pixels2.Color(255, 255, 255));
      pixels2.setPixelColor(51, pixels2.Color(255, 255, 255));
      pixels2.setPixelColor(52, pixels2.Color(255, 255, 255));
      pixels2.show(); // This sends the updated pixel color to the hardware.
    }
    if (ib == 19) {
      pixels2.setPixelColor(18, pixels2.Color(255, 255, 255));
      pixels2.setPixelColor(19, pixels2.Color(255, 255, 255));
      pixels2.setPixelColor(20, pixels2.Color(255, 255, 255));
      pixels2.setPixelColor(21, pixels2.Color(255, 255, 255));
      pixels2.setPixelColor(42, pixels2.Color(255, 255, 255));
      pixels2.setPixelColor(43, pixels2.Color(255, 255, 255));
      pixels2.setPixelColor(44, pixels2.Color(255, 255, 255));
      pixels2.setPixelColor(45, pixels2.Color(255, 255, 255));
      pixels2.show(); // This sends the updated pixel color to the hardware.
    }
    if (ib == 27) {
      pixels2.setPixelColor(25, pixels2.Color(255, 255, 255));
      pixels2.setPixelColor(26, pixels2.Color(255, 255, 255));
      pixels2.setPixelColor(27, pixels2.Color(255, 255, 255));
      pixels2.setPixelColor(28, pixels2.Color(255, 255, 255));
      pixels2.setPixelColor(29, pixels2.Color(255, 255, 255));
      pixels2.setPixelColor(30, pixels2.Color(255, 255, 255));
      pixels2.setPixelColor(33, pixels2.Color(255, 255, 255));
      pixels2.setPixelColor(34, pixels2.Color(255, 255, 255));
      pixels2.setPixelColor(35, pixels2.Color(255, 255, 255));
      pixels2.setPixelColor(36, pixels2.Color(255, 255, 255));
      pixels2.setPixelColor(37, pixels2.Color(255, 255, 255));
      pixels2.setPixelColor(38, pixels2.Color(255, 255, 255));
      pixels2.show();
    }
  }
}
void trans2derechaizq() { //CERRADO
  pixels2.clear();
  pixels.clear();
  pixels2.setPixelColor(25, pixels2.Color(255, 255, 255));
  pixels2.setPixelColor(26, pixels2.Color(255, 255, 255));
  pixels2.setPixelColor(27, pixels2.Color(255, 255, 255));
  pixels2.setPixelColor(28, pixels2.Color(255, 255, 255));
  pixels2.setPixelColor(29, pixels2.Color(255, 255, 255));
  pixels2.setPixelColor(30, pixels2.Color(255, 255, 255));
  pixels2.setPixelColor(33, pixels2.Color(255, 255, 255));
  pixels2.setPixelColor(34, pixels2.Color(255, 255, 255));
  pixels2.setPixelColor(35, pixels2.Color(255, 255, 255));
  pixels2.setPixelColor(36, pixels2.Color(255, 255, 255));
  pixels2.setPixelColor(37, pixels2.Color(255, 255, 255));
  pixels2.setPixelColor(38, pixels2.Color(255, 255, 255));
  pixels.setPixelColor(25, pixels.Color(255, 255, 255));
  pixels.setPixelColor(26, pixels.Color(255, 255, 255));
  pixels.setPixelColor(27, pixels.Color(255, 255, 255));
  pixels.setPixelColor(28, pixels.Color(255, 255, 255));
  pixels.setPixelColor(29, pixels.Color(255, 255, 255));
  pixels.setPixelColor(30, pixels.Color(255, 255, 255));
  pixels.setPixelColor(33, pixels.Color(255, 255, 255));
  pixels.setPixelColor(34, pixels.Color(255, 255, 255));
  pixels.setPixelColor(35, pixels.Color(255, 255, 255));
  pixels.setPixelColor(36, pixels.Color(255, 255, 255));
  pixels.setPixelColor(37, pixels.Color(255, 255, 255));
  pixels.setPixelColor(38, pixels.Color(255, 255, 255));
  pixels2.show();
  pixels.show();
}
void trans2 () {
  pixels2.clear();
  for (ib = 19 ; ib <= 27; ib = ib + 8) {
    if (ib == 19) {
      pixels2.setPixelColor(18, pixels2.Color(255, 255, 255));
      pixels2.setPixelColor(19, pixels2.Color(255, 255, 255));
      pixels2.setPixelColor(20, pixels2.Color(255, 255, 255));
      pixels2.setPixelColor(21, pixels2.Color(255, 255, 255));
      pixels2.setPixelColor(42, pixels2.Color(255, 255, 255));
      pixels2.setPixelColor(43, pixels2.Color(255, 255, 255));
      pixels2.setPixelColor(44, pixels2.Color(255, 255, 255));
      pixels2.setPixelColor(45, pixels2.Color(255, 255, 255));
      pixels2.show(); // This sends the updated pixel color to the hardware.
    }
    if (ib == 27) {
      pixels2.setPixelColor(25, pixels2.Color(255, 255, 255));
      pixels2.setPixelColor(26, pixels2.Color(255, 255, 255));
      pixels2.setPixelColor(27, pixels2.Color(255, 255, 255));
      pixels2.setPixelColor(28, pixels2.Color(255, 255, 255));
      pixels2.setPixelColor(29, pixels2.Color(255, 255, 255));
      pixels2.setPixelColor(30, pixels2.Color(255, 255, 255));
      pixels2.setPixelColor(33, pixels2.Color(255, 255, 255));
      pixels2.setPixelColor(34, pixels2.Color(255, 255, 255));
      pixels2.setPixelColor(35, pixels2.Color(255, 255, 255));
      pixels2.setPixelColor(36, pixels2.Color(255, 255, 255));
      pixels2.setPixelColor(37, pixels2.Color(255, 255, 255));
      pixels2.setPixelColor(38, pixels2.Color(255, 255, 255));
      pixels2.show();
    }
  }
}
void trans3derechaizq() {//OJOS transicion alegria
  pixels2.clear();
  pixels.clear();
  for (ib = 35 ; ib <= 43; ib = ib + 8) {
    if (ib == 35) {
      pixels2.setPixelColor(33, pixels2.Color(255, 255, 255));
      pixels2.setPixelColor(34, pixels2.Color(255, 255, 255));
      pixels2.setPixelColor(35, pixels2.Color(255, 255, 255));
      pixels2.setPixelColor(36, pixels2.Color(255, 255, 255));
      pixels2.setPixelColor(37, pixels2.Color(255, 255, 255));
      pixels2.setPixelColor(38, pixels2.Color(255, 255, 255));
      pixels2.setPixelColor(59, pixels2.Color(255, 255, 255));
      pixels2.setPixelColor(60, pixels2.Color(255, 255, 255));
      pixels.setPixelColor(33, pixels.Color(255, 255, 255));
      pixels.setPixelColor(34, pixels.Color(255, 255, 255));
      pixels.setPixelColor(35, pixels.Color(255, 255, 255));
      pixels.setPixelColor(36, pixels.Color(255, 255, 255));
      pixels.setPixelColor(37, pixels.Color(255, 255, 255));
      pixels.setPixelColor(38, pixels.Color(255, 255, 255));
      pixels.setPixelColor(59, pixels.Color(255, 255, 255));
      pixels.setPixelColor(60, pixels.Color(255, 255, 255));
      pixels2.show();
      pixels.show();
    }
    if (ib == 43) {
      pixels2.setPixelColor(41, pixels2.Color(255, 255, 255));
      pixels2.setPixelColor(42, pixels2.Color(255, 255, 255));
      pixels2.setPixelColor(43, pixels2.Color(255, 255, 255));
      pixels2.setPixelColor(44, pixels2.Color(255, 255, 255));
      pixels2.setPixelColor(45, pixels2.Color(255, 255, 255));
      pixels2.setPixelColor(46, pixels2.Color(255, 255, 255));
      pixels2.setPixelColor(50, pixels2.Color(255, 255, 255));
      pixels2.setPixelColor(51, pixels2.Color(255, 255, 255));
      pixels2.setPixelColor(52, pixels2.Color(255, 255, 255));
      pixels2.setPixelColor(53, pixels2.Color(255, 255, 255));
      pixels.setPixelColor(41, pixels.Color(255, 255, 255));
      pixels.setPixelColor(42, pixels.Color(255, 255, 255));
      pixels.setPixelColor(43, pixels.Color(255, 255, 255));
      pixels.setPixelColor(44, pixels.Color(255, 255, 255));
      pixels.setPixelColor(45, pixels.Color(255, 255, 255));
      pixels.setPixelColor(46, pixels.Color(255, 255, 255));
      pixels.setPixelColor(50, pixels.Color(255, 255, 255));
      pixels.setPixelColor(51, pixels.Color(255, 255, 255));
      pixels.setPixelColor(52, pixels.Color(255, 255, 255));
      pixels.setPixelColor(53, pixels.Color(255, 255, 255));
      pixels2.show();
      pixels.show();
    }
  }
}
void trans4derechaizq() {
  pixels2.clear();
  pixels.clear();
  for (ib = 3 ; ib <= 11; ib = ib + 8) {
    if (ib == 3) {
      pixels2.setPixelColor(3, pixels2.Color(255, 255, 255));
      pixels2.setPixelColor(4, pixels2.Color(255, 255, 255));
      pixels2.setPixelColor(25, pixels2.Color(255, 255, 255));
      pixels2.setPixelColor(30, pixels2.Color(255, 255, 255));
      pixels.setPixelColor(3, pixels.Color(255, 255, 255));
      pixels.setPixelColor(4, pixels.Color(255, 255, 255));
      pixels.setPixelColor(25, pixels.Color(255, 255, 255));
      pixels.setPixelColor(30, pixels.Color(255, 255, 255));
      pixels2.show();
      pixels.show();
    }
    if (ib == 11) {
      pixels2.setPixelColor(10, pixels2.Color(255, 255, 255));
      pixels2.setPixelColor(11, pixels2.Color(255, 255, 255));
      pixels2.setPixelColor(12, pixels2.Color(255, 255, 255));
      pixels2.setPixelColor(13, pixels2.Color(255, 255, 255));
      pixels2.setPixelColor(17, pixels2.Color(255, 255, 255));
      pixels2.setPixelColor(18, pixels2.Color(255, 255, 255));
      pixels2.setPixelColor(21, pixels2.Color(255, 255, 255));
      pixels2.setPixelColor(22, pixels2.Color(255, 255, 255));
      pixels.setPixelColor(10, pixels.Color(255, 255, 255));
      pixels.setPixelColor(11, pixels.Color(255, 255, 255));
      pixels.setPixelColor(12, pixels.Color(255, 255, 255));
      pixels.setPixelColor(13, pixels.Color(255, 255, 255));
      pixels.setPixelColor(17, pixels.Color(255, 255, 255));
      pixels.setPixelColor(18, pixels.Color(255, 255, 255));
      pixels.setPixelColor(21, pixels.Color(255, 255, 255));
      pixels.setPixelColor(22, pixels.Color(255, 255, 255));
      pixels2.show();
      pixels.show();
    }
  }
}
void bravoojo2 () {  //Ojo izquierdo
  for (ib = 1; ib <= NUMPIXELS; ib++) {
    if (ib >= 17 && ib < 19)    {
      pixels.setPixelColor(ib, pixels.Color(255, 255, 255));
      pixels.show(); // This sends the updated pixel color to the hardware.
    }
    else if (ib >= 26 && ib < 28)    {
      pixels.setPixelColor(ib, pixels.Color(255, 255, 255));
      pixels.show(); // This sends the updated pixel color to the hardware.
    }
    else if (ib >= 35 && ib < 37)    {
      pixels.setPixelColor(ib, pixels.Color(255, 255, 255));
      pixels.show(); // This sends the updated pixel color to the hardware.
    }
    else if (ib >= 44 && ib < 46)    {
      pixels.setPixelColor(ib, pixels.Color(255, 255, 255));
      pixels.show(); // This sends the updated pixel color to the hardware.
    }
    else if (ib >= 53 && ib < 55)    {
      pixels.setPixelColor(ib, pixels.Color(255, 255, 255));
      pixels.show(); // This sends the updated pixel color to the hardware.
    }
    else    {
      pixels.setPixelColor(ib, pixels.Color(0, 0, 0));
      pixels.show(); // This sends the updated pixel color to the hardware.
    }
  }
}
void bravoojo() {//Ojo derecho
  for (i = 1; i <= 64; i++) {
    if (i >= 21 && i < 23)    {
      pixels2.setPixelColor(i, pixels2.Color(255, 255, 255));
      pixels2.show(); // This sends the updated pixel color to the hardware.
    }
    else if (i >= 28 && i < 30)    {
      pixels2.setPixelColor(i, pixels2.Color(255, 255, 255));
      pixels2.show(); // This sends the updated pixel color to the hardware.
    }
    else if (i >= 35 && i < 37)    {
      pixels2.setPixelColor(i, pixels2.Color(255, 255, 255));
      pixels2.show(); // This sends the updated pixel color to the hardware.
    }
    else if (i >= 42 && i < 44)    {
      pixels2.setPixelColor(i, pixels2.Color(255, 255, 255));
      pixels2.show(); // This sends the updated pixel color to the hardware.
    }
    else if (i >= 49 && i < 51)    {
      pixels2.setPixelColor(i, pixels2.Color(255, 255, 255));
      pixels2.show(); // This sends the updated pixel color to the hardware.
    }
    else    {
      pixels2.setPixelColor(i, pixels2.Color(0, 0, 0));
      pixels2.show(); // This sends the updated pixel color to the hardware.
    }
  }
}
void rutinanormalderechaizq() { //para ojo derecho e izquierdo
  tstate = millis() - tiniN;
  switch (nxstateN) {
    case ENN:
      ojoneutroderechaizq();
      if (tstate >= RETARDOMATRIZ * 40) { //Ojos abiertos
        nxstateN = E1N;
        tiniN = millis();
      }
      break;
    case E1N:
      trans1derechaizq();
      if (tstate >= RETARDOMATRIZ / 2 ) {
        nxstateN = E12N;
        tiniN = millis();
      }
      break;
    case E12N:
      trans2derechaizq();
      if (tstate >= RETARDOMATRIZ * 2  ) { //Ojos cerrados
        nxstateN = E13N;
        tiniN = millis();
      }
      break;
    case E13N:
      trans1derechaizq();
      if (tstate >= RETARDOMATRIZ / 2 ) {
        nxstateN = ENN;
        tiniN = millis();
      }
      break;
  }
}
void rutinaconfusa() { //para ojo izquierdo
  tstate = millis() - tiniC;
  switch (nxstateC) {
    case EIC:
      ojoneutroderecha();
      if (tstate >= RETARDOMATRIZ * 20) { //Ojo abierto
        nxstateC = E1C;
        tiniC = millis();
      }
      break;
    case E1C:
      trans1();
      if (tstate >= RETARDOMATRIZ / 2) {
        nxstateC = E12C;
        tiniC = millis();
      }
      break;
    case E12C:
      trans2();
      if (tstate >= RETARDOMATRIZ * 500) { //Ojo pequeño
        nxstateC = E13C;
        tiniC = millis();
      }
      break;
    case E13C:
      trans1();
      if (tstate >= RETARDOMATRIZ / 2) {
        nxstateC = EIC;
        tiniC = millis();
      }
      break;
  }
}
void rutinalegria() { //para ojos
  tstate = millis() - tiniA;
  switch (nxstateA) {
    case ENA:
      ojoneutroderechaizq();
      if (tstate >= RETARDOMATRIZ * 15 ) { //Ojo entero
        nxstateA = ET1A;
        tiniA = millis();
      }
      break;
    case ET1A:
      trans3derechaizq();
      if (tstate >= RETARDOMATRIZ / 2 ) { // Ojo medio abajo
        nxstateA = ET12A;
        tiniA = millis();
      }
      break;
    case ET12A:
      trans4derechaizq();
      if (tstate >= RETARDOMATRIZ * 100) {  //Ojo arco arriba
        nxstateA = ET13A;
        tiniA = millis();
      }
      break;
    case ET13A:
      trans3derechaizq();
      if (tstate >= RETARDOMATRIZ / 2) { //Ojo medio abajo
        nxstateA = ENA;
        tiniA = millis();
      }
      break;
  }
}
void alegre() {
  rutinalegria();
  lucesalegreorejasfaldabrazos();
}
void normal () {
  rutinanormalderechaizq();
  lucesnormalorejasfaldabrazos();
}
void confusa() {
  rutinaconfusa();
  ojoneutroizq();
  lucesconfundidaorejasfaldabrazos();
}
void brava () {
  bravoojo();
  bravoojo2();
  lucesbravaorejasfaldabrazos();
}
void sensores() {
  if (digitalRead(SW1) == LOW)  {
    Sw1 = 1;
    //    Serial.println("SW 1");
  }
  else {
    Sw1 = 0;
  }
  if (digitalRead(SW2) == LOW)  {
    //    Serial.println("SW 2");
    Sw2 = 1;
  }
  else {
    Sw2 = 0;
  }
  if (digitalRead(SW3) == LOW)  {
    //    Serial.println("SW 3");
    Sw3 = 1;
  }
  else {
    Sw3 = 0;
  }
  if (digitalRead(SW4) == LOW)  {
    //    Serial.println("SW 4");
    Sw4 = 1;
  }
  else {
    Sw4 = 0;
  }
  if (digitalRead(Hall1) == LOW)  {
    //    Serial.println("hall 1");
    HALL1 = 1;
  }
  else {
    HALL1 = 0;
  }
  if (digitalRead(Hall2) == LOW)  {
    //    Serial.println("hall 2");
    HALL2 = 1;
  }
  else {
    HALL2 = 0;
  }
  if (digitalRead(Hall3) == LOW)  {
    //    Serial.println("hall 3");
    HALL3 = 1;
  }
  else {
    HALL3 = 0;
  }
  if (digitalRead(Hall4) == LOW)  {
    //    Serial.println("hall 4");
    HALL4 = 1;
  }
  else {
    HALL4 = 0;
  }
  if (digitalRead(Hall5) == LOW)  {
    //    Serial.println("hall 5");
    HALL5 = 1;
  }
  else {
    HALL5 = 0;
  }
  if (digitalRead(Hall6) == LOW) {
    //    Serial.println("hall 6");
    HALL6 = 1;
  }
  else {
    HALL6 = 0;
  }
  if ( HALL1 == 0 && HALL2 == 0 && Sw2 == 0 && HALL3 == 0 && Sw3 == 0 && HALL4 == 0 && Sw4 == 0 && HALL5 == 0 && HALL6 == 0 ) {
    //    Serial.println("sin nov");
  }
}
void loop () {
  sensores();
  char val2 = Serial.read(); //Lee el puerto serial y lo asigna a la variable val2
  if (val2 != -1)  //Si val2 es diferente de -1
  {
    if (val2 == 'a') {
      val = 'a';  //asigna a la variable val el valor a de alegria
    }
    if (val2 == 'n') {
      val = 'n';  //asigna a la variable val el valor n de normal
    }
    if (val2 == 'c') {
      val = 'c';  //asigna a la variable val el valor c de confundida
    }
    if (val2 == 'b') {
      val = 'b';  //asigna a la variable val el valor b de brava
    }
    tiniA = millis();
    tiniC = millis();
    tiniN = millis();
    pixels.clear(); //Apaga Ojo Izq
    pixels1.clear(); //Apaga Orejas
    pixels2.clear(); //Apaga Ojo Der
    pixels3.clear(); //Apaga Falda
    pixels4.clear(); //Apaga Brazo derecho
    pixels5.clear(); //Apaga Brazo izquierdo
  }
  switch (val)  {  //MEF para cada estado de animo
    case 'a':
      alegre();
      EstadoDyna = Semuevearribaabajo;
      break;
    case 'n':
      normal();
      EstadoDyna = Semueveabajolento;
      break;
    case 'c':
      confusa();
      EstadoDyna = Semueveabajomedio;
      break;
  }
  treld = millis() - tinid;
  switch (EstadoDyna) {
    case Semuevearribaabajo:
      error = servo_set(0x01, SERVO_REGISTER_MOVING_SPEED, 13, timeout);
      if (treld < 500) {
        error = servo_set(0x01, SERVO_REGISTER_GOAL_ANGLE, 0, timeout);
      }
      if (treld >= 500 && treld <= 1000) {
        error = servo_set(0x01, SERVO_REGISTER_GOAL_ANGLE, 0.34, timeout);
      }
      if (treld > 1000 ) {
        tinid = millis();
      }
      break;
    case Semueveabajolento:
      error = servo_set(0x01, SERVO_REGISTER_MOVING_SPEED, 6, timeout);
      if (treld < 500) {
        error = servo_set(0x02, SERVO_REGISTER_GOAL_ANGLE, 0, timeout);
      }
      if (treld >= 500 && treld <= 1000) {
        error = servo_set(0x02, SERVO_REGISTER_GOAL_ANGLE, 0.1745, timeout);
      }
      if (treld > 1000) {
        tinid = millis();
      }
      break;
    case Semueveabajomedio:
      if (treld < 500) {
        error = servo_set(0x01, SERVO_REGISTER_MOVING_SPEED, 6, timeout);
        error = servo_set(0x01, SERVO_REGISTER_GOAL_ANGLE, 0, timeout);
      }
      if (treld >= 500 && treld <= 1000) {
        error = servo_set(0x01, SERVO_REGISTER_MOVING_SPEED, 0, timeout);
      }
      if (treld >= 1000 && treld <= 1500) {
      error = servo_set(0x01, SERVO_REGISTER_MOVING_SPEED, 6, timeout);
        error = servo_set(0x01, SERVO_REGISTER_GOAL_ANGLE, 0.1745, timeout);

      }
      if (treld > 1500) {
      tinid = millis();
      }
      break;
  }
}
