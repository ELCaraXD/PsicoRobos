// === BLOCO DE BIBLIOTECAS ===
#include <ESP32_NOW.h>       // API oficial ESP-NOW do ESP-IDF
#include <WiFi.h>             // Necessária para WiFi.mode()
// === VARIÁVEIS DE TESTE ===
int   val_INT;         // 4 bytes na RAM (stack ou .bss)
float val_FLOAT;       // 4 bytes, IEEE 754 single precision
bool  val_BOOL = true; // 1 byte (mas ocupa 4 por alinhamento)
// === MAC DO RECEPTOR ===
uint8_t broadcastAddress[] = { 0xA4,0xCB,0x8F,0xD4,0x83,0x28 };
// === STRUCT DE DADOS (payload) ===
typedef struct str_Mens {
  char  a[32]; // 32 bytes — string fixa
  int   b;     // 4 bytes
  float c;     // 4 bytes
  bool  d;     // 1 byte + 3 padding = 4 bytes alinhados
} str_Mens;                 // Total: ~44 bytes (com padding)
str_Mens euData;            // instância global na RAM (.bss)
// === PEER INFO (peer = dispositivo remoto) ===
esp_now_peer_info_t peerInfo; // struct do ESP-IDF para cadastrar peers
// === CALLBACK DE ENVIO ===
void OnDataSent(const wifi_tx_info_t *tx_info, esp_now_send_status_t status) {
  Serial.print("\r\nLast Packet Send Status:\t");
  Serial.println(status == ESP_NOW_SEND_SUCCESS ? "Delivery Success" : "Delivery Fail");
}
void setup() {
  Serial.begin(115200); // UART0, 115200 baud
  WiFi.mode(WIFI_MODE_STA); // modo Station — obrigatório para ESP-NOW
  delay(200);             // aguarda estabilização do rádio
  if (esp_now_init() != ESP_OK) {   // inicializa driver ESP-NOW
    Serial.println("Erro ao inicializar o ESP_NOW");
    return; // ⚠ return no setup não reinicia — loop() ainda executa
  }
  esp_now_register_send_cb(OnDataSent); // registra callback de status
  memcpy(peerInfo.peer_addr, broadcastAddress, 6); // copia 6 bytes do MAC
  peerInfo.channel = 0; // ⚠ canal 0 = "usar canal atual" — pode divergir do receptor
  peerInfo.encrypt  = false; // sem CCMP — dados trafegam em claro
  if (esp_now_add_peer(&peerInfo) != ESP_OK) {
    Serial.println("Failed to add Peer");
    return;
  }
}
void loop() {
  val_INT   = random(1,20); // gera int entre 1 e 19
  val_FLOAT = 1.3 * val_INT;
  val_BOOL  = !val_BOOL; 
  strcpy(euData.a, "Bem vindo Diego!!"); // 18 chars + '\0' — cabe nos 32 bytes
  euData.b = val_INT;
  euData.c = val_FLOAT;
  euData.d = val_BOOL;

  esp_err_t result = esp_now_send(broadcastAddress, (uint8_t *) &euData, sizeof(euData));
  
  if (result == ESP_OK) {
    Serial.println("Envio Confirmado");
  } else {
    Serial.println("Error Envio");
  }
  delay(2000); // bloqueia task Arduino por 2s
}