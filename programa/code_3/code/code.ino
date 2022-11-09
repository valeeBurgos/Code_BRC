
#define PINBUZZER  10
#define PINBOTON  2

int base = 50;
float Kprop = 0.3;
float Kderiv = 3.5;
float Kinte = 0.2;
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
    int m = manejo_estado();
    int line_position = GetPos();
    int Correction_power = PIDLambo(line_position, Kprop, Kderiv, Kinte);
    //Serial.print(line_position);
    if (m==0) {
      beep();
      //Motores(0,0);
      //WaitBoton();
      }
    
    //Motores(base + Correction_power, base + -Correction_power);
    
    //Serial.print("\t");
    //Serial.println(Correction_power);
}
