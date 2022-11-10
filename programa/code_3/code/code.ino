
#define PINBUZZER  10
#define PINBOTON  2

int base = 45;
float Kprop = 0.215;
float Kderiv = 5;
float Kinte = 0;
int pos;

int cont = 0;
int ini = 0;
int tiempo2= 0;
int vuelta = 1;
int a= 0;
int iniciado = 0;

void setup() {
  Serial.begin(115200);
  Motores(0, 0);
  WaitBoton();
  Peripherals_init();

  beep();
  calibracion();
  calibrate_lat();

  tone(PINBUZZER, 1500, 100);
  delay(100);
  tone(PINBUZZER, 1500, 100);
  delay(70);
  WaitBoton();
  delay(1000);

  int tiempo1 = millis();
}

void loop() {
  
  if (vuelta == 1) {
    base = 52;
    Kprop = 0.395;
    Kderiv = 22;
    Kinte = 0.1;
    int m = manejo_estado();
    

  if (ini == 0 && m==0) {
    ini = 1;
    tiempo2 = millis() ;
    tone(PINBUZZER, 2000, 100);
  }

  int tiem;
  if (tiempo2 >0) {
    tiem= millis() ;
  }


  //lee indicador de final, debe permanecer acá hasta
  //presionar el botón.
  if (ini == 1 && m==0 and tiem >tiempo2 + 6000) {
    if (ini == 1 and !is_cruce()) {
      ini =1;
    }
    else {
      Motores(0,0);
      tone(PINBUZZER, 2000, 100);
      state_reset();
      WaitBoton();
      ini=0;
      m=0;
      vuelta = 2;
      state_reset();
      delay(1000);
      }

    
  }
 
  int line_position = GetPos();
  int Correction_power = PIDLambo(line_position, Kprop, Kderiv, Kinte);
  Motores(base + Correction_power, base + -Correction_power);
  }

  if (vuelta == 2) {
    if (a ==0) {
      a=1;
      state_reset();
      }
    base = 47;
    Kprop = 0.1971;
    Kderiv = 5;
    Kinte = 0.1;

    
  int m = manejo_estado();
  
  if (ini == 0 && m==0) {
    ini = 1;
    tiempo2 = millis() ;
    tone(PINBUZZER, 2000, 100);
  }

  int tiem;
  if (tiempo2 >0) {
    tiem= millis() ;
  }


  //lee indicador de final, debe permanecer acá hasta
  //presionar el botón.
  if (ini == 1 && m==0 and tiem >tiempo2 + 1000) {
    if (ini == 1 and !is_cruce()) {
      ini =1;
    }
    else {
      Motores(0,0);
      tone(PINBUZZER, 2000, 100);
      state_reset();
      WaitBoton();
      ini=0;
      m=0;
      vuelta = 2;
      state_reset();
      delay(1000);
      }

    
  }
  int line_position = GetPos();
  int Correction_power = PIDLambo(line_position, Kprop, Kderiv, Kinte);
  Motores(base + Correction_power, base + -Correction_power);
  }
  
  
}
