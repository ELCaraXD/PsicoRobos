//Plano e igual a mapa mental
uint8_t Plano[3][3] = {
  {0, 0, 0},
  {0, 0, 0},
  {0, 0, 0}
};

//Posição no plano cartesiano começando do zero, 0 = primeira linha e coluna
uint8_t pos_Atual[2] = {0, 0};
uint8_t pos_Antiga[2];

//Direca e pra onde ele ta apontando 
//       0
//   3       1         
//       2
uint8_t Direcao = 0;

void frente(uint8_t passos, uint8_t Direcao, uint8_t vel = 255){
  switch (Direcao){
    case 0: Serial.printf("Indo %d passos para cima \n", passos);  break;
    case 1: Serial.printf("Indo %d passos para direita \n", passos); break;
    case 2: Serial.printf("Indo %d passos para baixo \n", passos); break;
    case 3: Serial.printf("Indo %d passos para esquerda \n", passos); break;
  }
}


void setup() {
  Serial.begin(115200);
}

void loop() {
  for (uint8_t i = 0; i <= 10; i++){
    
    Serial.print("Movimentos do robo:\nDirecao: ");
    Serial.println(Direcao);
    frente(i,Direcao);
    
    if (Direcao < 3)
    { Direcao++; }
    else
    { Direcao = 0; }

    delay(2000);

  }


}
