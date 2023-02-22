const int button= 0;
int state = 0;

void setup() {
    Serial.begin(9600);
    pinMode (button, INPUT);
}

void loop() {
    state = analogRead(button);
    Serial.println(state);
    delay(150);
}
