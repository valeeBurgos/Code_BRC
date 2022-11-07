
#define PINBUZZER  10
#define PINBOTON  2

int base = 50;
float Kprop = 0.35;
float Kderiv = 1.4;
float Kinte = 0.0;
int pos;


void setup() {
  Serial.begin(115200);
  Motores(0, 0);
  WaitBoton();
  Peripherals_init();

  beep();
  delay(1000);
  calibracion();
  calibracion_lat();

  tone(PINBUZZER, 1500, 50);
  delay(70);
  tone(PINBUZZER, 1500, 50);
  delay(70);

  WaitBoton();
  delay(1000);

}


void loop() {
  int line_position = GetPos();
  int Correction_power = PIDLambo(line_position, Kprop, Kderiv, Kinte);
  Motores(base + Correction_power, base + -Correction_power);
  


}
