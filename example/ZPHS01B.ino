#include <ZPHS01B.h>
#include <SoftwareSerial.h>

//Create an instance of Software Serial before declaring the Module Class

// Arduino UNO, Nano, Pro Mini, etc
//SoftwareSerial ZPHS01B_Serial(4, 5); // RX, TX

// ESP8266
SoftwareSerial ZPHS01B_Serial(D1, D2); // RX, TX

// Initiate the MH-Z19B Module
ZPHS01B ZPHS01B( ZPHS01B_Serial );  // initiate the module, also sets Auto calibration off and sets the range of 2000

// --------------

void setup() {
  Serial.begin(115200);
  delay(1000);
  Serial.println();

  Serial.println("-- Initializing ZPHS01B Module...");

  if( ZPHS01B_Serial )
    ZPHS01B_Serial.begin(9600);  // Software Serial
  else {
    Serial.println("Error setting up Software Serial for ZPHS01B Module");
    Serial.println("Cannot move forward. Please, push `Reset`");
    delay(1000);
    while(true);
  }

  delay(100);

  Serial.println("-- Reading ZPHS01B --");
  delay(200);
  Serial.print( "Detection Range: " ); Serial.println( 2000 );
}

//--------------------

void loop() {
  uint16_t co2PPM;

  ZPHS01B.read();

  co2PPM = ZPHS01B.getPM1();

  Serial.println("Test");


  if( co2PPM > 0 ) {
    Serial.print("co2(ppm): "); Serial.print( co2PPM );
  } else {
    Serial.println( "Error Reading MH-Z19B Module" );
  }

  delay(5000);

}
