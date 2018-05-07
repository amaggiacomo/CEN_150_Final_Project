const int greenButtonPin = 2;
const int greenLED =  11;
const int blueButtonPin = 3;
const int blueLED =  12;
const int redButtonPin = 4;
const int redLED =  13;
const int debugLED = 6;

int sequence[20];
int mostRecent = -1;
int counter = 1;
bool takeTurn = true;

const int buzzer = 9;

int greenButtonState = 0;
int blueButtonState = 0;
int redButtonState = 0;

void setup() {
  pinMode(greenLED, OUTPUT);
  pinMode(greenButtonPin, INPUT);
  pinMode(blueLED, OUTPUT);
  pinMode(blueButtonPin, INPUT);
  pinMode(redLED, OUTPUT);
  pinMode(redButtonPin, INPUT);

  pinMode(debugLED, OUTPUT);

  pinMode(buzzer, OUTPUT);
}

void loop() {

  for (int i = 0; i < counter && takeTurn; i++) {

    if (i == 0) {
      randomSeed(analogRead(0));
      sequence[counter-1] = random(0, 3);
    }

    if (sequence[i] == 0) {
      //0 = green
      greenON();
      delay(500);
      greenOFF();
      delay(500);
    }
    if (sequence[i] == 1) {
      //1 = blue
      blueON();
      delay(500);
      blueOFF();
      delay(500);
    }
    if (sequence[i] == 2) {
      //2 = red
      redON();
      delay(500);
      redOFF();
      delay(500);
    }

    if (i == (counter - 1)) {
      takeTurn = false;
    }

  }

  while (takeTurn == false) {


    for (int i = 0; i < counter; i++) {
      mostRecent = -1;
      pushable();
      if (mostRecent == sequence[i]) {
        delay(500);
        //Do nothing
      }
      else{
        gameover();
      }
    }
    counter = counter + 1;

/*
    for(int j = 0;j<counter;j++){
      digitalWrite(debugLED, HIGH);
      delay(500);
      digitalWrite(debugLED, LOW);
      delay(500);
    }
  */  
    takeTurn = true;

  }
  
}

void pushable() {

  while (mostRecent == -1) {

    greenButtonState = digitalRead(greenButtonPin);
    blueButtonState = digitalRead(blueButtonPin);
    redButtonState = digitalRead(redButtonPin);

    if (greenButtonState == LOW) {
      greenON();
      delay(100);
      greenOFF();
      mostRecent = 0;
    }
    else {
      greenOFF();
    }
    if (blueButtonState == LOW) {
      blueON();
      delay(100);
      blueOFF();
      mostRecent = 1;
    }
    else {
      blueOFF();
    }
    if (redButtonState == LOW) {
      redON();
      delay(100);
      redOFF();
      mostRecent = 2;
    }
    else {
      redOFF();
    }

  }
}

void gameover(){

  blueON();
  greenON();
  redON();
  exit(0);
  
}

void greenON() {
  digitalWrite(greenLED, HIGH);
  tone(buzzer, 50);
}

void greenOFF() {
  digitalWrite(greenLED, LOW);
  noTone(buzzer);
}

void blueON() {
  digitalWrite(blueLED, HIGH);
  tone(buzzer, 250);
}

void blueOFF() {
  digitalWrite(blueLED, LOW);
  noTone(buzzer);
}

void redON() {
  digitalWrite(redLED, HIGH);
  tone(buzzer, 666);
}

void redOFF() {
  digitalWrite(redLED, LOW);
  noTone(buzzer);
}

