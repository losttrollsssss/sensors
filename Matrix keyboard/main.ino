const int buttonPin = 0;
int buttonState = 0;
String str;

void setup() {
  Serial.begin(9600);
  pinMode(buttonPin, INPUT);

  attachInterrupt(0, swap, RISING);
}

void swap(){
  buttonState = analogRead(buttonPin);

  if (buttonState >= 1000){str = "Кнопка 6";}
  if (buttonState >= 513 && buttonState < 1000){str = "Кнопка 5";}
  if (buttonState >= 300 && buttonState < 500){str = "Кнопка 4";}
  if (buttonState >= 250 && buttonState < 300){str = "Кнопка 3";}
  if (buttonState >= 200 && buttonState < 250){str = "Кнопка 2";}
  if (buttonState >= 150 && buttonState < 200){str = "Кнопка 1";}
  Serial.println(str);
}

void loop() {
 buttonState = analogRead(buttonPin);
 Serial.println(buttonState);
 delay(50);
}
