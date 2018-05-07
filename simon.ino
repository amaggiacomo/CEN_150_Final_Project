//Below is the initilization of any variables associated with pins. This is done so the pins in question are easier to identify and debug

const int greenButtonPin = 2;
const int greenLED =  11;
const int blueButtonPin = 3;
const int blueLED =  12;
const int redButtonPin = 4;
const int redLED =  13;
const int debugLED = 6;
const int buzzer = 9;

//Below is where the remaining variables are declared and initilized
int sequence[20];
int mostRecent = -1;
int counter = 1;
bool takeTurn = true;
int greenButtonState = 0;
int blueButtonState = 0;
int redButtonState = 0;

//Sets all of the proper pins in the correct pinmode
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

//The method "loop". This method is constantly looping. The for loop inside only runs when it is time for the AI to take its "turn"
//Which involves it lighting up a sequence of random LEDs.
void loop() {

  for (int i = 0; i < counter && takeTurn; i++) {

    if (i == 0) {
      //Calling randomSeed is needed, or else the "random" sequence will always be the same
      randomSeed(analogRead(0));
      //Sets the next int in the sequence equal to a random number that is either a 0, 1 or 2.
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

  
  //While loop only runs when it is not the computer's turn.
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

    //The below commented out code was used for debugging purposes.
    
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

  //Waits for user input, as mostRecent will be -1 forever unless the user pushes a button. When that occurs, not only does it break out of
  //the loop, but now mostRecent is logged as the button address that the user just pushed.
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

//All of the below methods are for turning LED's on and off. When an LED is turned on, its corresponding buzzer noise is also activated

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

