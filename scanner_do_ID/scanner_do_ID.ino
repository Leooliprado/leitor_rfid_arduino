#include <SPI.h>
#include <MFRC522.h>

// Defina os pinos do RFID
#define SS_PIN 10
#define RST_PIN 9

MFRC522 mfrc522(SS_PIN, RST_PIN); // Instancia o objeto do leitor RFID

void setup() {
  Serial.begin(9600);  // Inicializa a comunicação serial
  SPI.begin();         // Inicializa o barramento SPI
  mfrc522.PCD_Init();  // Inicializa o leitor RFID
  Serial.println("Aproxime o cartão do leitor...");
}

void loop() {
  // Verifica se há um novo cartão presente
  if (!mfrc522.PICC_IsNewCardPresent() || !mfrc522.PICC_ReadCardSerial()) {
    return;
  }

  // Exibe o UID do cartão no Monitor Serial
  Serial.print("UID do cartão: ");
  for (byte i = 0; i < mfrc522.uid.size; i++) {
    Serial.print(mfrc522.uid.uidByte[i] < 0x10 ? " 0" : " ");
    Serial.print(mfrc522.uid.uidByte[i], HEX);
  }
  Serial.println();

  mfrc522.PICC_HaltA(); // Para a leitura do cartão
}

