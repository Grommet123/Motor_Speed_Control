/* Motor Speed Control
*
*  Controls the speed of a DC motor using a L298N Dual H Bridge Stepper Motor Driver Board
*  and a rotary encoder.
*
*  Based on Brainy Bits "Use a L9110S dual motor driver to control the speed of a small DC Motor."
*
*  v1.0 Initial Release
*/

//#define EXTRA_SPEED  // Uncomment to gain more motor speed

volatile boolean TurnDetected;  // need volatile for Interrupts
volatile boolean up;

byte motorSpeed[] = {0, 20, 25, 30, 40, 60, 80, 100, 120, 140};

const int PinCLK = 2; // Generating interrupts using CLK signal
const int PinDT = 3;  // Reading DT signal
const int PinSW = 4;  // Reading Push Button switch

// Motor Speed & Direction
#define MOTOR_A_PWM 10  // Motor PWM Speed
#define MOTOR_A_DIR1 9  // Motor Direction
#define MOTOR_A_DIR2 8  // Motor Direction

#define MAX_VALUE 100

// Interrupt routine runs if CLK goes from HIGH to LOW
void isr ()  {
  delay(4);  // delay for Debouncing
  if (digitalRead(PinCLK))
    up = digitalRead(PinDT);
  else
    up = !digitalRead(PinDT);
  TurnDetected = true;
}

void setup ()  {
  pinMode(PinCLK, INPUT);
  pinMode(PinDT, INPUT);
  pinMode(PinSW, INPUT);
  digitalWrite(PinSW, HIGH); // Pull-Up resistor for switch

  attachInterrupt (0, isr, FALLING); // interrupt 0 always connected to pin 2 on Arduino
  Serial.begin (9600);
  Serial.println("Start");
  pinMode(MOTOR_A_DIR1, OUTPUT);
  pinMode(MOTOR_A_DIR2, OUTPUT);
  pinMode(MOTOR_A_PWM, OUTPUT);
  digitalWrite(MOTOR_A_DIR1, LOW); // Set motor to off
  digitalWrite(MOTOR_A_DIR2, LOW);
  digitalWrite(MOTOR_A_PWM, motorSpeed[0]);
}

void loop ()  {
  static long RotaryPosition = 0;  // STATIC to count correctly

  if (!(digitalRead(PinSW))) {   // check if button is pressed
    if (RotaryPosition == 0) {  // check if button was already pressed
    } else {
      RotaryPosition = 0; // if YES, then reset position to ZERO
      digitalWrite(MOTOR_A_DIR1, LOW); // turn motor off
      digitalWrite(MOTOR_A_DIR2, LOW);
      analogWrite(MOTOR_A_PWM, motorSpeed[0]);
      Serial.print ("Reset = ");
      Serial.println (RotaryPosition);
    }
  }

  // Runs if rotation was detected
  if (TurnDetected)  {
    if (up) {
      if (RotaryPosition >= MAX_VALUE) { // Max value set to MAX_VALUE
        RotaryPosition = MAX_VALUE;
      } else {
        RotaryPosition += 2;
      }
    } else {
      if (RotaryPosition <= -MAX_VALUE) { // Max value set to -MAX_VALUE
        RotaryPosition = -MAX_VALUE;
      }
      else {
        RotaryPosition -= 2;
      }
    }
    TurnDetected = false;  // Do NOT repeat IF loop until new rotation detected
    Serial.print ("Speed = ");
    Serial.println (RotaryPosition);


    // if Rotation is Clockwise

    if (RotaryPosition > 0 && RotaryPosition < 11) {
      digitalWrite(MOTOR_A_DIR1, LOW); // turn motor off
      digitalWrite(MOTOR_A_DIR2, LOW);
      analogWrite(MOTOR_A_PWM, motorSpeed[0]);
    }
    if (RotaryPosition > 10 && RotaryPosition < 21) {
      digitalWrite(MOTOR_A_DIR1, HIGH); // direction = forward
      digitalWrite(MOTOR_A_DIR2, LOW);
      analogWrite(MOTOR_A_PWM, motorSpeed[1]);
    }
    if (RotaryPosition > 20 && RotaryPosition < 31) {
      digitalWrite(MOTOR_A_DIR1, HIGH); // direction = forward
      digitalWrite(MOTOR_A_DIR2, LOW);
      analogWrite(MOTOR_A_PWM, motorSpeed[2]);
    }
    if (RotaryPosition > 30 && RotaryPosition < 41) {
      digitalWrite(MOTOR_A_DIR1, HIGH); // direction = forward
      digitalWrite(MOTOR_A_DIR2, LOW);
      analogWrite(MOTOR_A_PWM, motorSpeed[3]);
    }
    if (RotaryPosition > 40 && RotaryPosition < 51) {
      digitalWrite(MOTOR_A_DIR1, HIGH); // direction = forward
      digitalWrite(MOTOR_A_DIR2, LOW);
      analogWrite(MOTOR_A_PWM,motorSpeed[4]);
    }
#ifdef EXTRA_SPEED
    if (RotaryPosition > 50 && RotaryPosition < 61) {
      digitalWrite(MOTOR_A_DIR1, HIGH); // direction = forward
      digitalWrite(MOTOR_A_DIR2, LOW);
      analogWrite(MOTOR_A_PWM, motorSpeed[5]);
    }
    if (RotaryPosition > 60 && RotaryPosition < 71) {
      digitalWrite(MOTOR_A_DIR1, HIGH); // direction = forward
      digitalWrite(MOTOR_A_DIR2, LOW);
      analogWrite(MOTOR_A_PWM, motorSpeed[6]);
    }
    if (RotaryPosition > 70 && RotaryPosition < 81) {
      digitalWrite(MOTOR_A_DIR1, HIGH); // direction = forward
      digitalWrite(MOTOR_A_DIR2, LOW);
      analogWrite(MOTOR_A_PWM, motorSpeed[7]);
    }
    if (RotaryPosition > 80 && RotaryPosition < 91) {
      digitalWrite(MOTOR_A_DIR1, HIGH); // direction = forward
      digitalWrite(MOTOR_A_DIR2, LOW);
      analogWrite(MOTOR_A_PWM, motorSpeed[8]);
    }
    if (RotaryPosition > 90) {
      digitalWrite(MOTOR_A_DIR1, HIGH); // direction = forward
      digitalWrite(MOTOR_A_DIR2, LOW);
      analogWrite(MOTOR_A_PWM, motorSpeed[9]);
    }
#endif

    // if Rotation is Counter-Clockwise

    if (RotaryPosition < 0 && RotaryPosition > -11) {
      digitalWrite(MOTOR_A_DIR1, LOW); // turn motor off
      digitalWrite(MOTOR_A_DIR2, HIGH);
      analogWrite(MOTOR_A_PWM, motorSpeed[0]);
    }
    if (RotaryPosition < -10 && RotaryPosition > -21) {
      digitalWrite(MOTOR_A_DIR1, LOW); // direction = reverse
      digitalWrite(MOTOR_A_DIR2, HIGH);
      analogWrite(MOTOR_A_PWM, motorSpeed[1]);
    }
    if (RotaryPosition < -20 && RotaryPosition > -31) {
      digitalWrite(MOTOR_A_DIR1, LOW); // direction = reverse
      digitalWrite(MOTOR_A_DIR2, HIGH);
      analogWrite(MOTOR_A_PWM, motorSpeed[2]);
    }
    if (RotaryPosition < -30 && RotaryPosition > -41) {
      digitalWrite(MOTOR_A_DIR1, LOW); // direction = reverse
      digitalWrite(MOTOR_A_DIR2, HIGH);
      analogWrite(MOTOR_A_PWM, motorSpeed[3]);
    }
    if (RotaryPosition < -40 && RotaryPosition > -51) {
      digitalWrite(MOTOR_A_DIR1, LOW); // direction = reverse
      digitalWrite(MOTOR_A_DIR2, HIGH);
      analogWrite(MOTOR_A_PWM,motorSpeed[4]); // PWM speed = 100
    }
#ifdef EXTRA_SPEED
    if (RotaryPosition < -50 && RotaryPosition > -61) {
      digitalWrite(MOTOR_A_DIR1, LOW); // direction = reverse
      digitalWrite(MOTOR_A_DIR2, HIGH);
      analogWrite(MOTOR_A_PWM, motorSpeed[5]);
    }
    if (RotaryPosition < -60 && RotaryPosition > -71) {
      digitalWrite(MOTOR_A_DIR1, LOW); // direction = reverse
      digitalWrite(MOTOR_A_DIR2, HIGH);
      analogWrite(MOTOR_A_PWM, motorSpeed[6]);
    }
    if (RotaryPosition < -70 && RotaryPosition > -81) {
      digitalWrite(MOTOR_A_DIR1, LOW); // direction = reverse
      digitalWrite(MOTOR_A_DIR2, HIGH);
      analogWrite(MOTOR_A_PWM, motorSpeed[7]);
    }
    if (RotaryPosition < -80 && RotaryPosition > -91) {
      digitalWrite(MOTOR_A_DIR1, LOW); // direction = reverse
      digitalWrite(MOTOR_A_DIR2, HIGH);
      analogWrite(MOTOR_A_PWM, motorSpeed[8]);
    }
    if (RotaryPosition < -90) {
      digitalWrite(MOTOR_A_DIR1, LOW); // direction = reverse
      digitalWrite(MOTOR_A_DIR2, HIGH);
      analogWrite(MOTOR_A_PWM, motorSpeed[9]);
    }
#endif
  }
}
