
#define PINBUZZER  10
#define PINBOTON  2


//Para la primera velocidad.
int base;     
float Kprop;  
float Kderiv; 
float Kinte;  
int pos;


int ini = 0;
unsigned long tiempo2= 0;



void select_mode() {
  //inicio un contador en cero.
  int cont = 0;

  for (int i=0; i<3; i++) {
    tone(PINBUZZER, 2000, 100); 
    delay(500);
  }
  
  //tiempo desde que inicia esta función
  unsigned long  tiempo_select = millis();

  //indico que esta función esta activa sonando el buzzer 5 veces.
  while ((unsigned long) millis()< tiempo_select + 3000) {
    if (digitalRead(PINBOTON)) {
      cont = cont +1;
      digitalWrite(13, HIGH);
      delay(200);
      digitalWrite(13, LOW);
    } 
  }
  if (cont == 0) {
      //Primera velocidad
      base = 45;
      Kprop = 0.215;
      Kderiv = 5;
      Kinte = 0;
    }
    if (cont == 1) {
      //Segunda velocidad
      base = 50;
      Kprop = 0.45;
      Kderiv = 5;
      Kinte = 0.2;
    }

    if (cont == 2) {
      //Primera velocidad
      base = 52;
      Kprop = 0.395;
      Kderiv = 22;
      Kinte = 0.1;
    }

    tone(PINBUZZER, 2000, 100); 
    delay(1000);
}






void setup() {
  //Serial.begin(115200);
  Motores(0, 0);
  WaitBoton();
  Peripherals_init();
  
  select_mode();
  
  WaitBoton();
  
  beep();
  calibracion();
  calibrate_lat();

  tone(PINBUZZER, 1500, 100);
  delay(100);
  tone(PINBUZZER, 1500, 100);
  delay(70);
  WaitBoton();
  delay(1000);
}



void loop() {
  int m = manejo_estado();
  //Primer caso, ve por primera vez el marcador a ka derecha.
  
  if (ini == 0 && m==0) {
    ini = 1;
    tiempo2 = millis() ;
    tone(PINBUZZER, 2000, 100);
  }
  //Si ya ha visto el marcador a la derecha, entonces debe 
  //calcular el tiempo transcurrido desde entonces, para lo que
  //toma el tiempo actual.
  unsigned long  tiem;
  if (tiempo2 >0) {
    tiem= millis() ;
  }
  if (m==0) {
    tone(PINBUZZER, 2000, 100);
    }
  
  
  //lee indicador de final, debe permanecer acá hasta
  //presionar el botón.
  if (ini == 1 && m==0 ) {
    tone(PINBUZZER, 2000, 100);
  }
  
  if (ini == 1 && m==0 and tiem > tiempo2 + 5000) {
    if (is_cruce()) {
      ini = 1;
    }
    else {          //Debe detenerse AHORA.
      Motores(0,0);
      tone(PINBUZZER, 2000, 100);
      WaitBoton();
      ini=0;
      m=0;
      delay(1000);
    }     
  }

  //En cualquier otri caso, debe avanzar.
  int line_position = GetPos();
  int Correction_power = PIDLambo(line_position, Kprop, Kderiv, Kinte);
  Motores(base + Correction_power, base + -Correction_power);
  

}
