//Plano e igual a mapa mental
uint8_t Plano[3][3] = {
  {1, 0, 0},
  {0, 0, 0},
  {0, 0, 0}
};

//Posição no plano cartesiano começando do zero, 0 = primeira linha e coluna
uint8_t pos_Atual[2] = {0, 0};
uint8_t pos_Antiga[2];

//Direca e pra onde ele ta apontando 
//       1
//   4       2         
//       3
uint8_t Direcao = 1;

void Mover_Frente(uint8_t passos, uint8_t Direcao, uint8_t vel = 255){
  pos_Antiga[0] = pos_Atual[0];
  pos_Antiga[1] = pos_Atual[1];

  switch (Direcao){
    case 1: Serial.printf("Indo %d passos para cima \n", passos); pos_Atual[0]--; break;
    case 2: Serial.printf("Indo %d passos para direita \n", passos); pos_Atual[1]++; break;
    case 3: Serial.printf("Indo %d passos para baixo \n", passos); pos_Atual[0]++; break;
    case 4: Serial.printf("Indo %d passos para esquerda \n", passos); pos_Atual[1]--; break;
  }

  Plano[pos_Atual[0]][pos_Atual[1]] = Direcao;
  Plano[pos_Antiga[0]][pos_Antiga[1]] = 0;

}

void Mover_Tras(uint8_t passos, uint8_t Direcao, uint8_t vel = 255){
  pos_Antiga[0] = pos_Atual[0];
  pos_Antiga[1] = pos_Atual[1];

  switch (Direcao){
    case 1: Serial.printf("Indo %d passos para baixo \n", passos); pos_Atual[0]++; break;
    case 2: Serial.printf("Indo %d passos para esquerda \n", passos); pos_Atual[1]--; break;
    case 3: Serial.printf("Indo %d passos para cima \n", passos); pos_Atual[0]--; break;
    case 4: Serial.printf("Indo %d passos para direita \n", passos); pos_Atual[1]++; break;
  }

  Plano[pos_Atual[0]][pos_Atual[1]] = Direcao;
  Plano[pos_Antiga[0]][pos_Antiga[1]] = 0;

}

void MostrarPos(uint8_t linha, uint8_t coluna){
  for (uint8_t i = 0; i < linha; i++){
    for(uint8_t j = 0; j < coluna; j++){
      Serial.print(Plano[i][j]);
    }
    Serial.print("\n");
  }
}

void Girar(uint8_t passos, uint8_t Sentido, uint8_t vel = 255){ // sentido 1 == horario // sentido 0 == anti-horario // x nao muda
  for (uint8_t i = 0;i < passos;i++){
    if (Direcao < 5 && Direcao >= 1){
      
      if (Sentido == 1)
      { Serial.println("Girando Horario"); Direcao++; }
      else
      { Serial.println("Girando Ant-Horario"); Direcao--; }
    }
    
    if (Direcao > 4){ Direcao = 1; }
    if (Direcao < 1){ Direcao = 4; }
    

  }

}


void setup() {
  Serial.begin(115200);
}

void loop() {
  Serial.print("Posição Antes de mover: \n");
  MostrarPos(3,3);
  Girar(1,1);
  Mover_Frente(1,Direcao);
  
  Serial.print("Posição Depois de mover: \n");
  MostrarPos(3,3);


  delay(10000);
  
}
