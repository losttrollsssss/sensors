int column[8]={5,4,3,2,1,0,A1,A2};
int layer[2]={A2,A1};

void setup()
{

  //ряды
  for(int i = 0; i<8; i++)
  {
    pinMode(column[i], OUTPUT);
  }
  //слои
  for(int i = 0; i<4; i++)
  {
    pinMode(layer[i], OUTPUT);
  }
  //рандом
  randomSeed(analogRead(10));
  for (int i=0; i<6; i++) {
  	pinMode(i, OUTPUT);
  }
  pinMode(A1, OUTPUT);
  pinMode(A2, OUTPUT);
  
  digitalWrite(A1,HIGH); 
  digitalWrite(A2,HIGH);
}

void loop()
{	 EverythingOn();
 	 EverythingOff();
   LightOnRib();
   FlickBy();
   RandomFlick();
   ColumnsOff();
   UptoDown();
   delay (2000);
  }
  

void EverythingOn()
{
  for(int i = 0; i<8; i++)
  {
    digitalWrite(column[i], 0);
  }
  //turning on layers
  for(int i = 0; i<4; i++)
  {
    digitalWrite(layer[i], 1);
  }
}  

void EverythingOff()
 {
   for(int i = 0; i<8; i++)
   {
     digitalWrite(column[i], 1);
   }
   for(int i = 0; i<4; i++)
   {
     digitalWrite(layer[i], 0);
   }
 }

//зажигание по ребрам
void LightOnRib()
{
  digitalWrite(A1,LOW); // на слой 1 куба подана земля
  for (int i=2; i<6; i++) {
    digitalWrite(i,HIGH);
    delay(200);
    delay(200);
    delay(200);
    digitalWrite(i,LOW);}
  
  digitalWrite(A2,LOW); 
  for (int i=2; i<6; i++) {
    digitalWrite(i,HIGH);
    delay(200);
    delay(200);
    delay(200);
    digitalWrite(i,LOW);
  }
  digitalWrite(A2,HIGH);
}

//мерцание с ускорением
 void FlickBy()
{
  int i = 150;
  while(i != 0)
  {
    EverythingOn();
    delay(i);
    EverythingOff();
    delay(i);
    i-= 5;
  }
}

//мерцание в разнобой
void RandomFlick()
{
  EverythingOff();
  int x = 100;
  for(int i = 0; i!=60; i+=2)
  {
    int randomColumn = random(0,16);
    digitalWrite(column[randomColumn], 0);
    digitalWrite(layer[0], 1);
    delay(x+50);
    digitalWrite(layer[0], 0);
    digitalWrite(layer[1], 1);
    delay(x);
    digitalWrite(layer[1], 0);
    digitalWrite(layer[2], 1);
    delay(x);
    digitalWrite(layer[2], 0);
    digitalWrite(layer[3], 1);
    delay(x+50);
    digitalWrite(layer[3], 0);
    digitalWrite(column[randomColumn], 1);
  }
}

void ColumnsOff()
{
  for(int i = 0; i<8; i++)
  {
    digitalWrite(column[i], 1);
  }
}

//затухание сверху вниз 
void UptoDown()
{
  EverythingOff();
  int x = 90;
  for(int y = 4; y>0; y--)
  {
    for(int i = 0; i<6; i++)
    {
      
      digitalWrite(layer[y-1], 1);
      
      ColumnsOff();
      digitalWrite(column[0], 0);
      digitalWrite(column[5], 0);
      digitalWrite(column[10], 0);
      digitalWrite(column[15], 0);
      delay(x);
      
      ColumnsOff();
      digitalWrite(column[4], 0);
      digitalWrite(column[5], 0);
      digitalWrite(column[10], 0);
      digitalWrite(column[11], 0);
      delay(x);
      
      ColumnsOff();
      digitalWrite(column[6], 0);
      digitalWrite(column[7], 0);
      digitalWrite(column[8], 0);
      digitalWrite(column[9], 0);
      delay(x);
      
      ColumnsOff();
      digitalWrite(column[3], 0);
      digitalWrite(column[6], 0);
      digitalWrite(column[9], 0);
      digitalWrite(column[12], 0);
      delay(x);
      
      ColumnsOff();
      digitalWrite(column[2], 0);
      digitalWrite(column[6], 0);
      digitalWrite(column[9], 0);
      digitalWrite(column[13], 0);
      delay(x);
      
      ColumnsOff();
      digitalWrite(column[1], 0);
      digitalWrite(column[5], 0);
      digitalWrite(column[10], 0);
      digitalWrite(column[14], 0);
      delay(x);
    }
  }
  
  ColumnsOff();
  digitalWrite(column[0], 0);
  digitalWrite(column[5], 0);
  digitalWrite(column[10], 0);
  digitalWrite(column[15], 0);
  delay(x);
}

