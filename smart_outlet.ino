/*
Code for Smart Outlet
Author: Ashish Derhgawen
Date: December 8, 2016
*/

int ledPin = 13;
int relayPin = 2;
void setup() {
  // start serial port at 9600 bps:
  Serial.begin(9600);
  while (!Serial) {
    ; // wait for serial port to connect. Needed for native USB port only
  }

  pinMode(2, INPUT);   // digital sensor is on digital pin 2
  pinMode(ledPin, OUTPUT);
  pinMode(relayPin, OUTPUT);
}

double get_current(unsigned int number_of_samples) {
  int offset = analogRead(A1);
  int inst_voltage;
  int filtered_voltage;
  int sum_squared_voltage = 0;
  int squared_voltage;

  for (unsigned int n = 0; n < number_of_samples; n++)
  {
    inst_voltage = analogRead(A0);
    filtered_voltage = inst_voltage - offset;

    // RMS calculations
    squared_voltage = filtered_voltage * filtered_voltage;
    sum_squared_voltage += squared_voltage;
  }

  double rms_voltage = sqrt(sum_squared_voltage / number_of_samples) / 1024;

  // 30A/V (CT sensor specification)

  double rms_current = 30 * rms_voltage;
  return rms_current;
}

void loop() {
  // if we get a valid byte, read analog ins:
  if (Serial.available() > 0) {
    // get incoming byte:
    char cmd = (char)Serial.read();

    if (cmd == 'l') {
      if (digitalRead(ledPin) == HIGH)
      {
        digitalWrite(ledPin, LOW);
        Serial.write("LED switched off\n");
      }
      else
      {
        digitalWrite(ledPin, HIGH);
        Serial.write("LED switched on\n");
      }
    }
    else if (cmd == 'c')
    {
      Serial.println(get_current(2000));
    }
    else if (cmd == 'r')
    {
      if (digitalRead(relayPin) == HIGH)
      {
        digitalWrite(relayPin, LOW);
        Serial.write("Relay switched off\n");
      }
      else
      {
        digitalWrite(relayPin, HIGH);
        Serial.write("Relay switched on\n");
      }
    }

  }
}
