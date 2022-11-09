//Los valores aara los 6 sensores frontales
int v_s_min[6] = {1023, 1023, 1023, 1023, 1023, 1023};

//Para izq y der respectivamente.
int v_s_min_lat[2] = {1023,1023};

//Max para los 6 laterales
int v_s_max[6] = {0, 0, 0, 0, 0, 0};

//Max para los dos, izq, der
int v_s_max_lat[2] = {0, 0};

volatile int s_p[6];
volatile int s_p_lat[2];

boolean online;

int l_pos;

void calibracion() {
  calibracion_8();
  calibracion_lat();
  beep();
  beep();
}

void calibracion_8() {
  int v_s[6];
  for (int j = 0; j < 100; j++) {
    delay(10);
    v_s[0] = analogRead(A6);
    v_s[1] = analogRead(A5);
    v_s[2] = analogRead(A4);
    v_s[3] = analogRead(A3);
    v_s[4] = analogRead(A2);
    v_s[5] = analogRead(A1);

    for (int i = 0; i < 6; i++) {
      Serial.print(v_s[i]);
      Serial.print("\t");
    }
    Serial.println();

    for (int i = 0; i < 6; i++) {
      if (v_s[i] < v_s_min[i]) {
        v_s_min[i] = v_s[i];
      }
    }
    for (int i = 0; i < 6; i++) {
      if (v_s[i] > v_s_max[i]) {
        v_s_max[i] = v_s[i];
      }
    }
  }
  Serial.println();
  Serial.print("Mínimos frontal");
  Serial.print("\t");
  for (int i = 0; i < 6; i++) {
    Serial.print(v_s_min[i]);
    Serial.print("\t");
  }
  
  Serial.println();
  Serial.print("Máximos frontal");
  Serial.print("\t");
  for (int i = 0; i < 6; i++) {
    Serial.print(v_s_max[i]);
    Serial.print("\t");
  }
  Serial.println();
  Serial.println();
  Serial.println();
}

void calibracion_lat(){

  //Calibracion en laterales.
  int v_s_lat[2];
  for (int j = 0; j < 50; j++) {
    delay(10);
    v_s_lat[0] = analogRead(A7);
    v_s_lat[1] = analogRead(A0);

    //for (int i = 0; i < 2; i++) {
    //  Serial.print(v_s_lat[i]);
    //  Serial.print("\t");
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
  //Serial.print("Mínimos lateral");
  //Serial.print("\t");
  //for (int i = 0; i < 2; i++) {
    //Serial.print(v_s_min_lat[i]);
    //Serial.print("\t");
  //}
  
  //Serial.println();
  //Serial.print("Máximos lateral");
  //Serial.print("\t");
  //for (int i = 0; i < 2; i++) {
    //Serial.print(v_s_max_lat[i]);
    //Serial.print("\t");
  //}
}

void readSensors() {
  volatile int s[6];

  s[0] = analogRead(A6);
  s[1] = analogRead(A5);
  s[2] = analogRead(A4);
  s[3] = analogRead(A3);
  s[4] = analogRead(A2);
  s[5] = analogRead(A1);

  for (int i = 0; i < 6; i++) {
    if (s[i] < v_s_min[i]) {
      s[i] = v_s_min[i];
    }

    if (s[i] > v_s_max[i]) {
      s[i] = v_s_max[i];
    }
    s_p[i] = map(s[i], v_s_min[i], v_s_max[i], 100, 0);
  }
  volatile int sum = s_p[0] + s_p[1] + s_p[2] + s_p[3] + s_p[4] + s_p[5];
  if (sum > 100) {
    online = 1;

  } else {
    online = 0;
    sum = 100;
  }

  if (online) {
    for (int i = 0; i < 6; i++) {
      Serial.print(s_p[i]);
      Serial.print("\t");
    }
    //Serial.println();
  }
}


void leer_lat(){
  volatile int l[2];
  l[0] = analogRead(A7);
  l[1] = analogRead(A0);
  
  for (int i = 0; i < 2; i++) {
    if (l[i] < v_s_min_lat[i]) {
      l[i] = v_s_min_lat[i];
    }

    if (l[i] > v_s_max_lat[i]) {
      l[i] = v_s_max_lat[i];
    }
    s_p_lat[i] = map(l[i], v_s_min_lat[i], v_s_max_lat[i], 100, 0);
  }
  
  if (online) {
    for (int i = 0; i < 2; i++) {
      Serial.print("Laterales:");
      Serial.print(s_p_lat[i]);
      Serial.print("\t");
    }
    //Serial.println();
  }
}


int GetPos() {
  readSensors();
  int prom = -2.5 * s_p[0] - 1.5 * s_p[1] - 0.5 * s_p[2] + 0.5 * s_p[3] + 1.5 * s_p[4] + 2.5 * s_p[5];
  int sum = s_p[0] + s_p[1] + s_p[2] + s_p[3] + s_p[4] + s_p[5];

  if (online) {
    pos = int(100.0 * prom / sum);
  } else {
    if (l_pos < 0) {
      pos = -255;
    }
    if (l_pos >= 0) {
      pos = 255;
    }
  }
  l_pos = pos;
  return pos;
}
