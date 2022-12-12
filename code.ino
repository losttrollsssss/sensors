#define DATA_PIN 2
#define DATA_LEVEL LOW
#define SPACE_LEVEL HIGH
#define SPACE false
#define DATA true
#define TU 100
#define DASH_DURATION 3
#define DOT_DURATION 1

long start_data, start_space;
long duration[20];
bool color[20];
int previous=SPACE;
int index=0;
String CODES[]={".-","--.."};
char LETTERS[]={'A','Z'};
int NLETTERS=2;

void fill_arrays(){
  int current=digitalRead(DATA_PIN);
  if (current==DATA_LEVEL and previous == SPACE_LEVEL)
  {
    start_data=millis();
    duration[index]=int ((millis()-start_space+0.5*TU) /TU);
    color[index]=SPACE;
    index++;
  }
  if (current==SPACE_LEVEL and previous == DATA_LEVEL)
  {
    start_space=millis();
    duration[index]=int ((millis()-start_data+0.5*TU) /TU);
    color[index]=DATA;
    index++;
  }
}
void setup() {
  pinMode (DATA_PIN, INPUT);
  Serial.begin(9600);
}


void loop() {
  fill_arrays();
  decode_letters();
}

void decode_letters(){
  for (int i=0; i<index;i++){
      if (duration[i]==DASH_DURATION and color[i]==SPACE){
        String code="";
        for (int j=0; j<i;j++){
          if (duration[j]==DASH_DURATION and color[j]==DATA){
            code+='-';
          } 
          if (duration[j]==DOT_DURATION and color[j]==DATA){
            code+='.';
          }
          duration[j]=0;
        }
        duration[i]=0;
        for (int iletter=0; iletter < NLETTERS; iletter++){
          if (code== CODES[iletter]){
            Serial.println(LETTERS[iletter]);
          }
        }
      }
    }
    index=0;
}
