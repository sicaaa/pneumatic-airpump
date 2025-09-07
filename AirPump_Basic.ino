// Adafruit Motor Shield for Pneumatic Pumps


#include <Wire.h>
#include <Adafruit_MotorShield.h>

// Create the motor shield object
Adafruit_MotorShield AFMS = Adafruit_MotorShield();

// Assign pumps and valve to motor ports
Adafruit_DCMotor *pumpInflate = AFMS.getMotor(1); // M1
Adafruit_DCMotor *pumpDeflate = AFMS.getMotor(2); // M2
Adafruit_DCMotor *valve       = AFMS.getMotor(3); // M3 

void setup() {
  Serial.begin(9600);
  AFMS.begin();  // Start the shield
  stopAll(); // Ensure everything is off at start
}

void loop() {
  inflateObject(2000);   // Inflate for 2s
  delay(1000);           // Rest

  deflateObject(2000);   // Deflate for 2s
  delay(2000);           // Rest
}



// ---------- FUNCTIONS ----------

void inflateObject(int duration) {
  // Open valve
  valve->setSpeed(255);
  valve->run(FORWARD);

  // Run inflate pump
  pumpInflate->setSpeed(255);
  pumpInflate->run(FORWARD);
  delay(duration);
  stopAll();
}

void deflateObject(int duration) {
  // Open valve
  valve->setSpeed(0);
  valve->run(FORWARD);

  // Run deflate pump
  pumpDeflate->setSpeed(255);
  pumpDeflate->run(FORWARD);
  delay(duration);
  stopAll();
}

void stopAll() {
  // Stop both pumps and close valve
  pumpInflate->setSpeed(0);
  pumpInflate->run(RELEASE);
  pumpDeflate->setSpeed(0);
  pumpDeflate->run(RELEASE);
  valve->setSpeed(0);
  valve->run(RELEASE);
}
