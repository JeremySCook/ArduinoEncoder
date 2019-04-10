//Encder routine usin Arduino interrupts
//Misses steps occaisionally, but gets direction correct
//By Jeremy S. Cook


const int EncoderAPin = 2;
const int EncoderBPin = 3;

volatile bool EncoderAState = 0;
volatile bool EncoderBState = 0;
volatile bool debounceEncoder = 0;
volatile unsigned long changeTime = 0;
int encoderPosition = 0;


void setup() {
  pinMode(EncoderAPin, INPUT_PULLUP);
  pinMode(EncoderBPin, INPUT_PULLUP);
  attachInterrupt(digitalPinToInterrupt(EncoderAPin), changeA, CHANGE); //setup interrupt A
  attachInterrupt(digitalPinToInterrupt(EncoderBPin), changeB, CHANGE); //setup interrupt B
  
  // initialize digital pin LED_BUILTIN as an output.
  pinMode(LED_BUILTIN, OUTPUT);
  Serial.begin(9600);
}

void loop() {
  if(debounceEncoder) noInterrupts();
  if(millis - changeTime > 5) debounceEncoder = 0; //time 
  if(debounceEncoder == 0) interrupts();
  Serial.print("Encoder Position "); Serial.println(encoderPosition);
  delay(50);
}

void changeA(){
  changeTime = millis(); //time for debounce
  debounceEncoder = 1; //set flag for debounce
  EncoderAState = digitalRead(EncoderAPin);
  EncoderBState = digitalRead(EncoderBPin);
  //four states for encoder signals on A:
  if(EncoderAState == HIGH && EncoderBState == HIGH) encoderPosition +=1;
  else if(EncoderAState == LOW && EncoderBState == LOW) encoderPosition +=1;
  else if(EncoderAState == HIGH && EncoderBState == LOW) encoderPosition -=1;
  else if(EncoderAState == LOW && EncoderBState == HIGH) encoderPosition -=1;
  //Serial.println("increment A");
}

void changeB(){
  changeTime = millis(); //time for debounce
  debounceEncoder = 1; //set flag for debounce
  EncoderAState = digitalRead(EncoderAPin);
  EncoderBState = digitalRead(EncoderBPin);
  //four states for encoder signals on B:
  if(EncoderAState == HIGH && EncoderBState == HIGH) encoderPosition -=1;
  else if(EncoderAState == LOW && EncoderBState == LOW) encoderPosition -=1;
  else if(EncoderAState == HIGH && EncoderBState == LOW) encoderPosition +=1;
  else if(EncoderAState == LOW && EncoderBState == HIGH) encoderPosition +=1;
  //Serial.println("increment B"); 
}
