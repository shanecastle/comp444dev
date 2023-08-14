//#include <atomic.h> // For the ATOMIC_BLOCK macro

#define OA 2 // Green O-A on Motor A
#define OB 3 // Orange O-B on Motor B

volatile int posi = 0; // specify posi as volatile

void setup() {
  Serial.begin(9600);
  pinMode(OA,INPUT);
  pinMode(OB,INPUT);
  attachInterrupt(digitalPinToInterrupt(OA),readEncoder,RISING);
}

void loop() {
  // Read the position in an atomic block to avoid a potential
  // misread if the interrupt coincides with this code running
  // see: https://www.arduino.cc/reference/en/language/variables/variable-scope-qualifiers/volatile/
  int pos = 0; 
 // ATOMIC_BLOCK(ATOMIC_RESTORESTATE) {
    pos = posi;
 // }
  
  Serial.println(pos);
}

void readEncoder(){
  int b = digitalRead(OB);
  if(b > 0){
    posi++;
  }
  else{
    posi--;
  }
}