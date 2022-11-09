
#define PINBUZZER  10
#define PINBOTON  2

int base = 80;
float Kprop = 1.2;
float Kderiv = 7.5;
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
  Serial.print(line_position);
  Serial.print("\t");
  Serial.println(Correction_power);


}






