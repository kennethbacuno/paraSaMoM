#include <Servo.h>
#include <LiquidCrystal_I2C.h>

LiquidCrystal_I2C lcd(0x27, 16, 2);

Servo myServo1;
Servo myServo2;
const int entrance_btn = 1;
const int exit_btn = 2;
const int laser_btn = 3;
const int relay_btn = 4;
const int relay = 5;
const int ir_entrance = 6;
const int laser_security = 7;
const int buzzer_security = 8;
const int servo_entrance = 9;
const int ir_exit = 10;
const int trigPin = 11;
const int echoPin = 12;
const int servo_exit = 13;

String message = "Vacant: ";
int counter = 100; // Initialize counter at 100

const int receiver_security = A0;

int buttonState1 = 0;
int buttonState2 = 0;
int buttonState3 = HIGH;
int lastButtonState3 = HIGH;
int lastButtonState4 = HIGH;
int buttonState4 = 0;

bool lastObjectDetected = false;
bool lastExitObjectDetected = false;

unsigned long previousMillis = 0;
const long interval = 2000;

bool laserState = LOW;
bool relayState = LOW;

// Variables for buzzer control
unsigned long buzzerStartTime = 0;
bool buzzerActive = false;

void setup() {
  lcd.init();
  lcd.backlight();

  myServo1.attach(servo_entrance);
  myServo2.attach(servo_exit);
  pinMode(relay, OUTPUT);
  pinMode(ir_entrance, INPUT);
  pinMode(ir_exit, INPUT);
  pinMode(laser_security, OUTPUT);
  pinMode(receiver_security, INPUT);
  pinMode(buzzer_security, OUTPUT);
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
  pinMode(entrance_btn, INPUT);
  pinMode(exit_btn, INPUT);
  pinMode(laser_btn, INPUT);
  pinMode(relay_btn, INPUT);
  Serial.begin(9600);

  myServo1.write(0);
  myServo2.write(0);
  digitalWrite(laser_security, HIGH);
}

void loop() {
  int irSensorEntranceState = digitalRead(ir_entrance);
  int irSensorExitState = digitalRead(ir_exit);
  int laserSensorValue = digitalRead(receiver_security);
  unsigned long currentMillis = millis();

  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  long duration = pulseIn(echoPin, HIGH);
  int distance = duration * 0.034 / 2;

  // Check for incoming serial commands
  if (Serial.available() > 0) {
    String command = Serial.readStringUntil('\n');  // Read the incoming command
    command.trim();  // Remove any leading/trailing whitespace

    Serial.print("Command received: ");
    Serial.println(command);

    if (command == "ENTRANCE_SERVO_ON") {
      myServo1.write(90);  // Move the servo to 90 degrees (on position)
      Serial.println("Entrance servo turned on");
      
      lastObjectDetected = false; // Reset the detection flag when turning on the servo

    } 
    else if (command == "ENTRANCE_SERVO_OFF") {
      myServo1.write(0);  // Move the servo to 0 degrees (off position)
      Serial.println("Entrance servo turned off");
      lastObjectDetected = false;  // Reset object detection flag
    }

    else if (command == "EXIT_SERVO_ON") {
      myServo2.write(90);  // Move the servo to 90 degrees (on position)
      Serial.println("Exit servo turned on");
      lastExitObjectDetected = false; // Reset exit detection flag when turning on the servo

    }

    else if (command == "EXIT_SERVO_OFF") {
      myServo2.write(0);  // Move the servo to 0 degrees (off position)
      Serial.println("Exit servo turned off");
      lastExitObjectDetected = false;  // Reset exit object detection flag
    }

    else if (command == "LASER_ON") {
      digitalWrite(laser_security, HIGH); // Turn the laser on
      Serial.println("Laser turned on");
      laserState = HIGH;
    }
    else if (command == "LASER_OFF") {
      digitalWrite(laser_security, LOW); // Turn the laser off
      Serial.println("Laser turned off");
      laserState = LOW;
    }
    else if (command == "LIGHTS_ON") {
      digitalWrite(relay, HIGH); // Turn the laser on
      Serial.println("Lights turned on");
      relayState = HIGH;
    }
    else if (command == "LIGHTS_OFF") {
      digitalWrite(relay, LOW); // Turn the laser off
      Serial.println("Lights turned off");
      relayState = LOW;
    }
  }

  // Continuous IR sensor detection loop for entrance
  if (myServo1.read() == 90) { // Check if the entrance servo is on
    if (irSensorEntranceState == LOW && counter > 0) { // Object detected
      if (!lastObjectDetected) {
        Serial.println("May pumasok na tao!");
        counter--;
        count();
        lastObjectDetected = true; // Set the flag to indicate an object has been detected
      }
    } else if (irSensorEntranceState == HIGH) { // No object detected
      lastObjectDetected = false; // Reset object detection flag
    }
  }

  if (myServo2.read() == 90) { // Check if the exit servo is on
  if (irSensorExitState == LOW && counter >= 0 && counter < 100) { // Object detected and counter is within limit
    if (!lastExitObjectDetected) {
      Serial.println("May lumabas na tao!");
      counter++;  // Increment counter only if it's less than 100
      count();    // Update display or perform any other action related to counting
      lastExitObjectDetected = true;  // Set the flag to indicate an object has been detected
    }
  } else if (irSensorExitState == HIGH) { // No object detected
    lastExitObjectDetected = false;  // Reset object detection flag
  }
}

    // Check for laser detection or distance
  
}

void count() {
  if (counter <= 0) {
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("Please wait..");
    lcd.setCursor(2, 1);
    lcd.print("Puno pa!!");
    counter = 0;
  } else {
    lcd.clear();
    lcd.setCursor(0, 0);
    String a = message + counter;
    lcd.print(a);
    lcd.setCursor(2, 1);
    lcd.print("");
  }
}
