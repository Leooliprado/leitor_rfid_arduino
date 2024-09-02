#include <SPI.h>
#include <MFRC522.h>

// Defina os pinos do RFID e LED
#define SS_PIN 10
#define RST_PIN 9
#define LED_PIN_VERDE 7

#define LED_PIN_VERMELHO 6

MFRC522 mfrc522(SS_PIN, RST_PIN); // Instancia o objeto do leitor RFID

// ID do cartão correto (substitua pelo seu)
byte correctCard[4] = {0xBD, 0xDF, 0x37, 0x21};

void setup() {
  Serial.begin(9600);  // Inicializa a comunicação serial
  SPI.begin();         // Inicializa o barramento SPI
  mfrc522.PCD_Init();  // Inicializa o leitor RFID
  pinMode(LED_PIN_VERDE, OUTPUT);  // Configura o pino do LED como saída
  pinMode(LED_PIN_VERMELHO, OUTPUT);
}

void loop() {
  // Verifica se há um novo cartão presente
  if (!mfrc522.PICC_IsNewCardPresent() || !mfrc522.PICC_ReadCardSerial()) {
    return;
  }

  // Verifica se o cartão lido é o correto
  if (checkCard(mfrc522.uid.uidByte)) {
    Serial.println("Cartão autenticado. Ligando o LED.");
    digitalWrite(LED_PIN_VERDE, HIGH); // Liga o LED
    delay(2000); // Mantém o LED ligado por 5 segundos
    digitalWrite(LED_PIN_VERDE, LOW); // Desliga o LED  
  } else {
    Serial.println("Cartão não autenticado.");
    digitalWrite(LED_PIN_VERMELHO, HIGH);
    delay(2000);
    digitalWrite(LED_PIN_VERMELHO, LOW);
  }

  mfrc522.PICC_HaltA(); // Para a leitura do cartão
}

// Função para verificar se o cartão lido é o correto
bool checkCard(byte *cardID) {
  for (byte i = 0; i < 4; i++) {
    if (cardID[i] != correctCard[i]) {
      return false;
    }
  }
  return true;
}

