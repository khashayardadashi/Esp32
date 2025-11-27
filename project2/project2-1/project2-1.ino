const int button = 23;
const int ledpin = 5;

bool state = false;
bool pressed = false;
unsigned long start = 0;

void setup() {
  pinMode(ledpin, OUTPUT);
  pinMode(button, INPUT_PULLDOWN);
  digitalWrite(ledpin, LOW);
}

void loop() {
  int readButton = digitalRead(button);

  if (readButton == HIGH) {
    if (!pressed) {
      start = millis();
      pressed = true;
    }
    if (millis() - start >= 3000) {
      state = !state;
      digitalWrite(ledpin, state ? HIGH : LOW);
      pressed = false;
    }
  } else {
    pressed = false;
  }
}
