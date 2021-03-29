const char ADDR[] = {22,24,26,28,30,32,34,36,38,40,42,44,46,48,50,52};
const char DATA[] = {45,43,41,39,37,35,33,31};

/* This is a test program to verify what is on the AT28C256 EEPROM
 *  Running makeromTEST.py generates a binary with alternating 
 *  0x00 and 0xFF values. This loops through every address on the 
 *  EEPROM (0x000 to 0x 7FFF) and checks that the value is 
 *  00 for evens and FF for odds.
 *  
 *  Connect 22 to 52 to A0 to A14 (dont need A15) on EEPROM
 *  Connect 31 to 45 to IO0 to IO7 on EEPROM
 */

void setup() {
  for(int i = 0; i < 16; i++){
    pinMode(ADDR[i], OUTPUT);
    digitalWrite(ADDR[i], LOW);
  }
  for(int i = 0; i < 8; i++){
    pinMode(DATA[i], INPUT);
  }

  Serial.begin(57600);

}

void loop() {
  // Loop from 0x0000 to 0x7fff, set input
  // read output

  Serial.println("START LOOP");
  
  for(unsigned int i = 0; i < 32768; i++){
    int n = i;
//    Serial.print("ADDR: ");
//    Serial.print(i, HEX);
    for(int b = 0; b < 15; b++){
      int bit = n & 1;
      n >>= 1;
      digitalWrite(ADDR[b], (bit) ? HIGH : LOW);
    }

    unsigned int data = 0;
    for(int b = 0; b < 8; b++){
      int bit = digitalRead(DATA[b]) ? 1 : 0;
      data = (data << 1) + bit;
      
    }

//    Serial.print("   DATA: ");
//    Serial.print(data, HEX);

//    Serial.print("   STATUS: ");
    if( (i % 2 == 0 && data == 0xEA) || (i % 2 != 0 && data == 0xEA)){
//      Serial.println("OK");
    } else {
      Serial.print("BAD: ");
      Serial.print(i, HEX);
      Serial.print("  DATA: ");
      Serial.println(data, HEX);
    }
    
    if(i % 1000 == 0){
      Serial.println(i);
    }
    
//    delay(1000);
  }

  Serial.println("FINSIHED LOOP");

}
