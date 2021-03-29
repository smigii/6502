const char ADDR[] = {52,50,48,46,44,42,40,38,36,34,32,30,28,26,24,22};
const char DATA[] = {45,43,41,39,37,35,33,31};

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
  char output[32];
  
  unsigned int addr = 0;
  for(int i = 0; i < 16; i++){
    int bit = digitalRead(ADDR[i]) ? 1 : 0;
//    Serial.print(bit);
    addr = (addr << 1) + bit;
  }
  

  unsigned int data = 0;
  for(int i = 0; i < 8; i++){
    int bit = digitalRead(DATA[i]) ? 1 : 0;
//    Serial.print(bit);
    data = (data << 1) + bit;
  }

  sprintf(output, "@ %04x -> %02x : %c", addr, data, digitalRead(RW) ? 'r' : 'w');
  
  Serial.println(output);
  
}

void loop() {
  
}
