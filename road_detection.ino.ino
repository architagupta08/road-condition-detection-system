#include <Wire.h>
#include <MPU6050.h>

MPU6050 mpu;

float ax, ay, az;
float prev_ax = 0, prev_ay = 0, prev_az = 0;

void setup() {
  Serial.begin(115200);
  Wire.begin();

  mpu.initialize();

  if (!mpu.testConnection()) {
    Serial.println("MPU6050 connection failed");
    while (1);
  }

  Serial.println("MPU6050 connected");
}

void loop() {
  int16_t raw_ax, raw_ay, raw_az;
  mpu.getAcceleration(&raw_ax, &raw_ay, &raw_az);

  // Convert to g (approx)
  ax = raw_ax / 16384.0;
  ay = raw_ay / 16384.0;
  az = raw_az / 16384.0;

  // Calculate vibration (change in acceleration)
  float vibration = abs(ax - prev_ax) + abs(ay - prev_ay) + abs(az - prev_az);

  // Store previous values
  prev_ax = ax;
  prev_ay = ay;
  prev_az = az;

  // Classification
  if (vibration < 0.2) {
    Serial.println("Smooth Road");
  } 
  else if (vibration < 0.6) {
    Serial.println("Rough Road");
  } 
  else {
    Serial.println("Pothole Detected!");
  }

  delay(200);
}