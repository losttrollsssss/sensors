// Машинка тесла за пять минут

/* Распиновки */

// Пины для 1 датчика

#define PIN_ECHO 9
#define PIN_TRIG 8

// Пины для 2 датчика

#define PIN_SHARP A0

// Пины для мотора

#define SPEED_1 5
#define DIR_1 4
#define SPEED_2 6
#define DIR_2 7

/* переменные */
long distanceForward = 0;
long distanceRight = 0;
long lastDistanceRight = 0;
int speed = 100;

void setup() {
  Serial.begin(9600);

  /* Подготовка пинов motorShield */
  pinMode(SPEED_1, OUTPUT);
  pinMode(DIR_1, OUTPUT);
  pinMode(SPEED_2, OUTPUT);
  pinMode(DIR_2, OUTPUT);

  /* Подготовка пинов датчиков */
  pinMode(PIN_SHARP, INPUT);
  pinMode(PIN_TRIG, OUTPUT);
  pinMode(PIN_ECHO, INPUT);

  /* Направление колес вперед */
  digitalWrite(DIR_1, HIGH);
  digitalWrite(DIR_2, HIGH);
  /* Скорость колес */
  analogWrite(SPEED_1, 80);
  analogWrite(SPEED_2, 80); 
}

void loop() {
  update_state();
  do_move();
  Serial.println(distanceRight);
}

/* Функция измерения дистанции спереди */
long distance_forward(uint8_t trig=PIN_TRIG, uint8_t echo=PIN_ECHO) {
  digitalWrite(trig, LOW);
  delayMicroseconds(5);
  digitalWrite(trig, HIGH);

  delayMicroseconds(10);
  digitalWrite(trig, LOW);

  return ((pulseIn(echo, HIGH)) / 2) / 29.1;
}

/* Функция измерения дистанции сбоку */
long distance_right(float K = 12.298) {
  int16_t analog_value = analogRead(PIN_SHARP);
  float V = analog_value * 0.0048828125;

  return K * pow(V, -1.10);
}

void turnRight(int sp1=0, int sp2=80) {
  analogWrite(SPEED_1, sp1);
  analogWrite(SPEED_2, sp2);
}

void turnLeft(int sp1=80, int sp2=0) {
  analogWrite(SPEED_1, sp1);
  analogWrite(SPEED_2, sp2);
}

void goForward() {
  analogWrite(SPEED_1, speed);
  analogWrite(SPEED_2, speed);
}

/* Опрос датчиков */
void update_state() {
  distanceForward = distance_forward();
  
  lastDistanceRight = distanceRight;  // Сохраняем прошлое значение
  
  distanceRight = distance_right();  // берем новое
  if (distanceRight < 0) {  // Отбрасываем невалидное
    distanceRight = 15;
  }
}

void do_move()
{
    if (distanceRight > lastDistanceRight * 2) {  // Если резко увеличилось расстояние во время поворота направо, делаем доворот
    turnRight(0, 250);
      delay(300);
  }
  
  if (distanceForward < 25) {  // Если спереди близится тупик
    Serial.print(distanceForward);
    if (distanceRight > 15) {  // Если справа стена далеко, то поварачиваем направо
      Serial.println("go right");
      turnRight(0, 250);
      delay(300);
    } else {  // Иначе налево
      Serial.println("go left");
      turnLeft(250, 0);
      delay(300);  
    }
  }

/* Корректировка траектории при движении прямо */
  if (distanceRight > 10) { // Стена дальше нужного - берем правее
    Serial.println("turn right");
    turnRight(0, 150);
    delay(100);
    turnLeft(150, 0);
    delay(50);
    goForward();
    delay(100);
  }
  else if (distanceRight < 7) { // иначе левее
  Serial.println("turn left");
    turnLeft(150, 0);
    delay(100);
    turnRight(0, 150);
    delay(50);
    goForward();
    delay(100);
  } else {  // Иначе прямо
    Serial.println("go forward");
    goForward();
    delay(50);
  }
}
