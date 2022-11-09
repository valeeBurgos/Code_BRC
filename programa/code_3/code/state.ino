//state 0 = ambos marcadores en negro.
//state 1 = marcador der en negro e izq en blanco.
//State 2 = marcador izq en negro y der en blanco.
//state 3 =ambos marcadores en blanco. cruce.

int state = 0;
int o_state = -1;
int oo_state = 0;
int ooo_state = 0;

int r0=0;
int r1= 0;
int r2 = 0;
int r3=0;

int umbral = 50;
int s_der;
int s_izq;

int v_s_min_lat[2] = {1023, 1023};
int v_s_max_lat[2] = {0, 0};
volatile int s_p_lat[2];

//Se calibran los sensores laterales.
void calibracion_lat() {
  int v_s_lat[2];
  for (int j = 0; j < 100; j++) {
    delay(10);
    v_s_lat[0] = analogRead(A0);
    v_s_lat[1] = analogRead(A7);

    //for (int i = 0; i < 2; i++) {
      //Serial.print(v_s_lat[i]);
      //Serial.print("\t");
    //}
    //Serial.println();

    for (int i = 0; i < 2; i++) {
      if (v_s_lat[i] < v_s_min_lat[i]) {
        v_s_min_lat[i] = v_s_lat[i];
      }
    }
    for (int i = 0; i < 2; i++) {
      if (v_s_lat[i] > v_s_max_lat[i]) {
        v_s_max_lat[i] = v_s_lat[i];
      }
    }
  }

  beep();
  beep();
  Serial.println();
  Serial.print("Mínimos ");
  Serial.print("\t");
  for (int i = 0; i < 2; i++) {
    Serial.print(v_s_min_lat[i]);
    Serial.print("\t");
  }
  Serial.println();
  Serial.print("Máximos ");
  Serial.print("\t");
  for (int i = 0; i < 2; i++) {
    Serial.print(v_s_max_lat[i]);
    Serial.print("\t");
  }
  //Serial.println();
  //Serial.println();
  //Serial.println();
}


//Lectura de sensores laterales, entregan blanco o negro en 
void read_lat() {
  volatile int s_lat[2];
  //Leo ambos sensores laterales.
  s_lat[0] = analogRead(A7); //der?
  s_lat[1] = analogRead(A0); //izq?
  
  //Sensor sobre el negro
  if (s_p_lat[0] < umbral) {
    s_der = 0;
  }else {  //sobre blanco
    s_der = 1;
  }
  
  //Sensor izq sobre negro
  if (s_p_lat[1] < umbral) {
    s_izq = 0;
  }else {  //sobre blanco
    s_izq = 1;
  }
  //Serial.println(); 
  //for (int i=0; i<2;i++) {
    //Serial.println(s_lat[i]); 
    //}
  //Serial.println(); 
}
  

//Se evalua el estado actual del robot
void act_state () {
  int current_state;
  //comienzo leyendo los sensores}
  read_lat();
  
  //ambos en negro
  if (s_izq == 0 and s_der ==0) {
    current_state = 0;
    //Serial.println("ambos izq");
  }
  //der en negro
  if (s_izq == 1 and s_der ==0) {
    current_state = 1;
    //Serial.print("der en negro");
  }
  //izq en negro
  if (s_izq == 0 and s_der ==1) {
    current_state = 2;
    //Serial.println("izq en negro");
  }
  //ambos en blanco
  if (s_izq == 1 and s_der ==1) {
    current_state = 3;
    //Serial.println("ambos izq");
  }
  ooo_state = oo_state;
  oo_state = o_state;
  o_state =state;
  state = current_state;
}

int manejo_estado() {
  act_state ();
  if (state != o_state) {
    //Serial.print(" state: ");
    //Serial.print(state);
    //Serial.print(" o_state: ");
    //Serial.print(o_state);
    //Serial.print(" oo_state: ");
    //Serial.print(oo_state);
    //Serial.print(" ooo_state: ");
    //Serial.print(ooo_state);
    //Serial.println();
  
    //Serial.println("cambio de estado:");
    //evaluo si es marcador si cruce.
    
    if ( (state == 0 and (r1 ==3 || r2 == 3 || r3 == 3))) {
      Serial.println("cruce ");
      //return 1;
    }
    else if (state == 0 and r1 == 2 and r2==0) {
      Serial.println("marcador a la izquierda"); 
      return 0;
    }
    else if (state == 0 and r1== 1 and r2==0) {
      Serial.println("marcador a la der");
      //tone(PINBUZZER, 1500, 200);
      //return 1;
     } else {
      Serial.println("derecho");
      }
      r3=r2;
      r2=r1;
      r1=state;
  }
  return 1;
}

  
