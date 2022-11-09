
#define PINBUZZER  10
#define PINBOTON  2

int base = 40;
float Kprop = 0.25;
float Kderiv = 3.5;
float Kinte = 0.2;
int pos;

int cont = 0;
int ini = 0;
int tiempo2= 0;

int iniciado = 0;
void setup() {
  Serial.begin(115200);
  Motores(0, 0);
  WaitBoton();
  Peripherals_init();

  beep();
  calibracion();
  calibrate_lat();

  tone(PINBUZZER, 1500, 50);
  delay(70);
  tone(PINBUZZER, 1500, 50);
  delay(70);
  WaitBoton();
  delay(1000);

  int tiempo1 = millis();
}

void loop() {
  //delay(100);
  int m = manejo_estado();
  //Serial.print(   "m =");
  //Serial.print(m );
  //Serial.print("    ini =");
  //Serial.println(ini);
  //cuento
  
  //lee indicador de inicio y marca como tal
  if (ini == 0 && m==0) {
    ini = 1;
    Serial.println("Marcador de inicio");
    tiempo2 = millis() ;
    tone(PINBUZZER, 2000, 100);
  }

  int tiem;
  if (tiempo2 >0) {
    tiem= millis() ;
  }


  //lee indicador de final, debe permanecer acá hasta
  //presionar el botón.
  if (ini == 1 && m==0 and tiem >tiempo2 + 4000) {
    Serial.println("paralizado");
    Motores(0,0);
    tone(PINBUZZER, 2000, 100);
    WaitBoton();
    ini=0;
    m=0;
    delay(100);
  }
  
  int line_position = GetPos();
  int Correction_power = PIDLambo(line_position, Kprop, Kderiv, Kinte);
  Motores(base + Correction_power, base + -Correction_power);
}
