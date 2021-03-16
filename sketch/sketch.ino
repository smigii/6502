const char ADDR[] = {22,24,26,28,30,32,34,36,38,40,42,44,46,48,50,52};
const char DATA[] = {39,41,43,45,47,49,51,53};

#define CLOCK 2
#define RW 3

void setup() {
  for(int i = 0; i < 16; i++){
    pinMode(ADDR[i], INPUT);
  }
  for(int i = 0; i < 8; i++){
    pinMode(DATA[i], INPUT);
  }

  pinMode(RW, INPUT);

  attachInterrupt(digitalPinToInterrupt(CLOCK), onClock, RISING);

  Serial.begin(57600);
  
}

void onClock() {
  char output[15];
  
  unsigned int addr = 0;
  for(int i = 0; i < 16; i++){
    int bit = digitalRead(ADDR[i]) ? 1 : 0;
    Serial.print(bit);
    addr = (addr << 1) + bit;
  }
  
  Serial.print("     ");

  unsigned int data = 0;
  for(int i = 0; i < 8; i++){
    int bit = digitalRead(DATA[i]) ? 1 : 0;
    Serial.print(bit);
    data = (data << 1) + bit;
  }

  sprintf(output, " | %04x - %02x : %c", addr, data, digitalRead(RW) ? 'r' : 'w');
  
  Serial.println(output);
  
}

void loop() {
  
}
