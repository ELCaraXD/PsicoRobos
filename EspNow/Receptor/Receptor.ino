#include <ESP32_NOW.h>  // API ESP-NOW — obrigatória
#include <WiFi.h>       // driver Wi-Fi — obrigatória mesmo sem rede
// Struct idêntica ao transmissor — contrato de dados
typedef struct str_Mens {
  char  a[32]; // offset 0 — 32 bytes
  int   b;     // offset 32 — 4 bytes
  float c;     // offset 36 — 4 bytes
  bool  d;     // offset 40 — 1 byte + 3 padding
} str_Mens;          // sizeof = 44 bytes — igual ao TX
str_Mens euData;     // instância global na RAM (.bss)
void OnDataRecv(const esp_now_recv_info_t* mac, const uint8_t *incomingData, int len) {

  // memcpy correto: &euData=destino, incomingData=fonte, sizeof=tamanho
  memcpy(&euData, incomingData, sizeof(euData));

  Serial.print("Dados Recebidos: ");
  Serial.println(len); // len = bytes recebidos = sizeof(euData) = 44
  Serial.print("valor caracter: ");   Serial.println(euData.a);
  Serial.print("valor inteiro: ");    Serial.println(euData.b);
  Serial.print("valor float: ");      Serial.println(euData.c);
  Serial.print("valor booleano: ");   Serial.println(euData.d);
  Serial.println(); // linha em branco para separar pacotes
}
void setup() {
  Serial.begin(115200);
  WiFi.mode(WIFI_MODE_STA);
  delay(200);
  if (esp_now_init() != ESP_OK) {
    Serial.println("Erro ao iniciar o ESP_NOW");
    return; // ⚠ loop() ainda vai rodar — use while(true) aqui
  }
  esp_now_register_recv_cb(OnDataRecv); // registra callback de recepção
}
void loop() {
  // vazio — tudo acontece no callback assíncrono
}