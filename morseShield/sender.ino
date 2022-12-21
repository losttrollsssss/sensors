#define DATA_PIN 9
#define DATA_LEVEL LOW

float TU = 1000;
String ENCODE[] = {".-","-...","-.-.","-..",".","..-.","--.","....","..",".---","-.-",".-..","--","-.","---",".--.","--.-",".-.","...","-","..-","...-",".--","-..-","-.--","--.."};
char LETTERS[] = {'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J', 'K', 'L', 'M', 'N', 'O', 'P', 'Q', 'R', 'S', 'T', 'U', 'V', 'W', 'X', 'Y', 'Z'};
int n_letters = 26;
void setup() {
  Serial.begin(9600);
  pinMode(DATA_PIN, OUTPUT);
  digitalWrite(DATA_PIN, !DATA_LEVEL);
}

void loop() {
  if(Serial.available() >=1){
    char letter = Serial.read();
   Serial.println(letter);
    for (int iletter = 0; iletter < n_letters; iletter++) {
      if (letter == LETTERS[iletter]){
        encode(ENCODE[iletter]);
        Serial.println(ENCODE[iletter]);
      }
    }
  }
}

void encode(String dashdot){
  int len = dashdot.length();
  for (int isymbol = 0; isymbol < len; isymbol++){
    if(dashdot[isymbol] == '.'){
      digitalWrite(DATA_PIN, DATA_LEVEL);
      delay(TU);
      
    } else if(dashdot[isymbol] == '-'){
      digitalWrite(DATA_PIN, DATA_LEVEL);
      delay(3*TU);
      
    }
    digitalWrite(DATA_PIN,!DATA_LEVEL);
    delay(TU);
  }
  delay(2*TU);
}
