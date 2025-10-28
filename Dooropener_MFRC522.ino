#include <SPI.h> // SPI-Library added
#include <MFRC522.h> // RFID-Library added

#define SS_PIN 10 // SDA at Pin 10
#define RST_PIN 9 // RST at Pin 9
#define PIN_Doormotor 8 // Dooropener at PIN 8

MFRC522 mfrc522(SS_PIN, RST_PIN); // RFID-Receiver named

void setup(){
  Serial.begin(9600); // Starting Serial Connection (Monitor)
  SPI.begin(); // Build up SPI-Connection
  mfrc522.PCD_Init(); // Initialisation of the RFID-Receiver
  pinMode(PIN_Doormotor,OUTPUT);
  //digitalWrite(PIN_Doormotor, HIGH);
  //delay(5000);
  digitalWrite(PIN_Doormotor, LOW);
  Serial.println("Begin of the Script");
}

void loop(){
  String Token_ID;
  String Token_Byte;
  if ( ! mfrc522.PICC_IsNewCardPresent()) // When no card is near the receiver...
  {
    return; // ...the program jumps back before the if-loop and the query begins again
  }

  if ( ! mfrc522.PICC_ReadCardSerial()) // When no RFID-Sender is choosen...
  {
    return; // ...the program jumps back before the if-loop and the query begins again
  }
  Serial.print("The ID of the RFID-TAG is:");
  for (byte i = 0; i < mfrc522.uid.size; i++)
  {
    Token_Byte=(mfrc522.uid.uidByte[i]);
    Serial.print(mfrc522.uid.uidByte[i]); // Now the UID is readen by the receiver. The ID has four single blocks and they would be send one after another to the serial monitor.
	
    //Serial.print(mfrc522.uid.uidByte[i], HEX); // Now the UID is readen by the receiver. The ID has four single blocks and they would be send one after another to the serial monitor. The Ending Hex means, that the four blocks would be displayed as an HEX-Number (also with Letters)
    Serial.print(" ");
  Token_ID=Token_ID+Token_Byte;
  }
  Serial.println();
  delay(1000);

  //Serial.print("The ID is:");
  //Serial.println(Token_ID);


  if(Token_ID == "123"){                                 //Implant
    Serial.println("Token is registered. Door would be opend");
    digitalWrite(PIN_Doormotor, HIGH);
    delay(1000);
    digitalWrite(PIN_Doormotor, LOW);
    Serial.println("Tür is closing");
  }
   if(Token_ID == "456"){                                 //Token
    Serial.println("Token is registered. Door would be opend");
    digitalWrite(PIN_Doormotor, HIGH);
    delay(1000);
    digitalWrite(PIN_Doormotor, LOW);
    Serial.println("Tür is closing");
  }
  if(Token_ID == "789"){                                 //Smartwatch
    Serial.println("Token is registered. Door would be opend");
    digitalWrite(PIN_Doormotor, HIGH);
    delay(1000);
    digitalWrite(PIN_Doormotor, LOW);
    Serial.println("Tür is closing");
  }

mfrc522.PICC_HaltA();
mfrc522.PCD_StopCrypto1();
}
