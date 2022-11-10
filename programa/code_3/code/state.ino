//state 0 = ambos marcadores en negro.
//state 1 = marcador der en negro e izq en blanco.
//State 2 = marcador izq en negro y der en blanco.
//state 3 =ambos marcadores en blanco. cruce.

int state = 0;
int o_state = 0;
int oo_state = 0;
int ooo_state = 0;
int current_state;
int umbral = 50;
int s_der;
int s_izq;

int time_3;
int v_s_min_lat[2] = {1023, 1023};
int v_s_max_lat[2] = {0, 0};
volatile int s_p_lat[2];

void calibrate_lat(){
  int v_s_lat[2];

  for (int j = 0; j < 200; j++) {
    delay(10);
    v_s_lat[0] = analogRead(A7);
    v_s_lat[1] = analogRead(A0);

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

  //Serial.println();
  //Serial.print("Mínimos ");
  //Serial.print("\t");
  //for (int i = 0; i < 2; i++) {
    //Serial.print(v_s_min_lat[i]);
    //Serial.print("\t");
  //}
  //Serial.println();
  //Serial.print("Máximos ");
  //Serial.print("\t");
  //for (int i = 0; i < 2; i++) {
    //Serial.print(v_s_max_lat[i]);
    //Serial.print("\t");
  //}
  //Serial.println();
  //Serial.println();
  //Serial.println();
  

  beep();
  beep();
}


//Lectura de sensores laterales, entregan blanco o negro en 
void read_lat() {
  volatile int s_lat[2];
  //Leo ambos sensores laterales.
  s_lat[0] = analogRead(A7); //der?
  s_lat[1] = analogRead(A0); //izq?


  for (int i = 0; i < 2; i++) {
    if (s_lat[i] < v_s_min_lat[i]) {
      s_lat[i] = v_s_min_lat[i];
    }

    if (s_lat[i] > v_s_max_lat[i]) {
      s_lat[i] = v_s_max_lat[i];
    }
    s_p_lat[i] = map(s_lat[i], v_s_min_lat[i], v_s_max_lat[i], 100, 0);
  }
  
  
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
    //Serial.print(s_lat[i]); 
    //Serial.print("   "); 
    //}
  //Serial.println(); 


  int current_state;
  
  //ambos en negro
  if (s_izq == 0 and s_der ==0) {
    current_state = 0;
    //Serial.println("ambos en negro");
  }
  //der en negro
  if (s_izq == 1 and s_der ==0) {
    current_state = 1;
    //Serial.print("der n");
  }
  //izq en negro
  if (s_izq == 0 and s_der ==1) {
    current_state = 2;
     //Serial.println("izq  n");
  }
  //ambos en blanco
  if (s_izq == 1 and s_der ==1) {
    current_state = 3;
     //Serial.println("ambos blanco");
  }
  state = current_state;
}




//Función que retorna true si ha visto recientemente un cruce
bool is_cruce() {
  //lee sensores laterales
  read_lat() ;
  
  int time2= millis();
  //Si se ha leido un 3, reasigno la variable
  
  if (state == 3) {
    time_3 = time2;
    return true;
  } else {
    //si ha pasado medio segundo desde la ultima lectura
    if (time2 > time_3 + 70) {
      return true;
    }
    //si ha pasado mas tiempo, considero que puede ser un nuevo cruce.
    return false;
  }
}






//Función para manejar el estado actual. Retorna 0 si debe detenerse.
int manejo_estado() {
  //lee sensores laterales
  read_lat() ;
  
  if (state != o_state) {
    //evaluo si spudo haber sido un cruce y en caso de serlo retorno inmediatamente.
    if (is_cruce()) {
    }

    //marcador de detenerse, retorna 0.
    if (state == 0 and o_state== 1 and oo_state==0) {
      //Serial.println("marcador a la der"); 
      return 0;
     }
  //Serial.println("cambio de estado:");
    //Reasigno los estados
    ooo_state = oo_state;
    oo_state = o_state;
    o_state =state;
    state = current_state;
  }
  //En caso de no haber retornado 0, retorno 1.
  return 1;
}


//devuelve los 4 estados recordados a  su valor inicial igual a 0
void state_reset() {
  state = 0;
  o_state = 0;
  oo_state = 0;
  ooo_state = 0;
}

  
