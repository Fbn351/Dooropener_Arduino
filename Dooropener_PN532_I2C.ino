//*******************************************************************************************************
//**  Samplesketch for reading ID-Tags. With the right ID the PIN13 would be opened for 2 seconds (LED)**
//**  With a wrong ID at PIN 12 a Tone would be generated (PASSIVE Buzzer / Piezzo)                    **
//**  Instead of an LED you can use also a dooropener f.e. over a TIP120 switching amplifier           **
//*******************************************************************************************************
#include <Wire.h>                            // Library for the I2C Protocol
#include <Adafruit_PN532.h>                  // Library for the NFC/RFID Module !!! Load by Arduino IDE !!!
#define PN532_IRQ   (2)                      // Define the IRQ Connection
#define PN532_RESET (3)                      // Define the Reset Connection
const int AlarmPin  =  12;                   // Define the Conenctions to 
const int OutputPin =  13;                   // the (Switch)Exits
unsigned long cardid;                        // Variable for the readen TAG-ID
unsigned long TAGid1 = 123;           		 // Here you can put in the TAG-IDs that are allowed
unsigned long TAGid2 = 456;                  // Or let it free. The ID of an single TAG can be
unsigned long TAGid3 ;                       // read at the Serial Monitor (Config to 115200 Baud)
Adafruit_PN532 nfc(PN532_IRQ, PN532_RESET);  // // Create Instance with I2C Protocol
void setup() {                               // Begin of the Setp Function
pinMode(AlarmPin, OUTPUT);                   // Define PIN als OUTPUT
pinMode(OutputPin, OUTPUT);                  // Define PIN als OUTPUT
Serial.begin(115200);                        // Open serial Transmission with 115200 Baud
Serial.println("Hello!");                    // Sending Text "Hello!" to the Serial Monitor
nfc.begin();                                 // Begin Communication with the RFID-Reader
unsigned long versiondata = nfc.getFirmwareVersion();  // Reading Versionnumber of Firmware
if (! versiondata) {                                   // When we get no answer
Serial.print("No Board was found !");            // Sending Text "No Board..." to serial Monitor
while (1);                                           // stop while there is no board found
}
Serial.print("Found chip PN5"); Serial.println((versiondata >> 24) & 0xFF, HEX); // Sending Text and Versionnumber to the serial
Serial.print("Firmware ver. "); Serial.print((versiondata >> 16) & 0xFF, DEC);   // Monitor, when we get an answer from the board
Serial.print('.'); Serial.println((versiondata >> 8) & 0xFF, DEC);               // 
nfc.SAMConfig();                                             // configure Board to read RFID Tags
Serial.println("Wait for an ISO14443A Chip ...");        // Sending a text to the serial Monitor that we have to wait for an ISO14443A TAG
}
void loop() {                                                // Begin of the Loop Function
uint8_t success;                                           // Create Variable
uint8_t uid[] = { 0, 0, 0, 0, 0, 0, 0 };                   // Buffer to save the UID
uint8_t uidLength;                                         // Lenght of the UID (4 or 7 bytes depending on which ISO14443A Card/Chip Type)
// Waiting for an ISO14443A Chip. If there would be found one, the Variable would be
// flled with the UID. Depending on which length (4 bytes (Mifare Classic) or
// 7 bytes (Mifare Ultralight) the Cardtype would be recognized.
success = nfc.readPassiveTargetID(PN532_MIFARE_ISO14443A, uid, &uidLength);
if (success) {                                                    // Wenn erkannt wird, do work...
Serial.println("Found an ISO14443A card");
Serial.print("  UID Length: "); Serial.print(uidLength, DEC); Serial.println(" bytes");
Serial.print("  UID Value: ");
nfc.PrintHex(uid, uidLength);                          // put the information to the serial Monitor
if (uidLength == 4) {                                  // If the Card&Chip has 4 Bytes length...
// Mifare Classic Karte
cardid = uid[0];                                     //
cardid <<= 8;                                        // Put the 4 Blocks together
cardid |= uid[1];                                    //
cardid <<= 8;                                        // to one
cardid |= uid[2];                                    //
cardid <<= 8;                                        // single Block
cardid |= uid[3];                                    //
Serial.print("Scheint eine Mifare Classic zu sein #");  //
Serial.println(cardid);                                 // Put ut the Information
Serial.println("");                                     // 
Serial.println("");                                     // 
}
if  ((cardid) == (TAGid1)||(cardid) == (TAGid2)||(cardid) == (TAGid3))  // Query, whether the TAGs 1..2..3 with the
{digitalWrite(OutputPin,HIGH);                                                // respective one. Then switch the Port
delay(2000);
digitalWrite(OutputPin,LOW);}                                                 // ON or OFF
else
{tone(AlarmPin, 1000);                                                        // And create a noise
delay(4000);
noTone(AlarmPin);}
}                                                      // End of the IF Loop
}                                                        // End of the Loop Loop
