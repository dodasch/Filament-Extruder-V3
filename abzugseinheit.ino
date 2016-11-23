/*

  Abzugseinheit
  von 0 (oben) bis 155 (unten)
  MotorPin muss an einem .... Pin angeschlossen werden.


*/

int PotPin = 5;    // Input Pin für den Potentiometer
int PotiWert = 0;       // Poti Wert zum

int Motor = 9;           // PWM Pin an dem der Motor angeschlossen ist
int Geschwindigkeit = 0;    // wie schnell der Motor ist
int Beschleunigen = 5;    // wie stark sich die Geschwindigkeit verändern soll
float KP = 1.6;
int Sollwert = 30;
int eSum = 0;     // Summe der Regelabweichung
float KI = 0;
const long interval = 100;
unsigned long currentMillis;
unsigned long previousMillis;


void setup()
{
  pinMode(Motor, OUTPUT);
  Serial.begin(9600);
}



void loop ()

{
  unsigned long currentMillis = millis();
  if (currentMillis - previousMillis >= interval) {
    previousMillis = currentMillis;

    PotiWert = analogRead(PotPin);    // liest Wert vom Poti aus


    eSum += PotiWert - Sollwert;
    eSum = constrain(eSum, -1000, 1000);
    Geschwindigkeit = PotiWert * KP + KI * eSum;
    Serial.print("eSum  ");
    Serial.println(eSum);
    Serial.print("Poti Wert  ");
    Serial.println (PotiWert);
    Serial.print("Geschwindigkeit  ");
    Serial.println (Geschwindigkeit);
    Serial.println("");

    Geschwindigkeit = constrain(Geschwindigkeit, 0, 255);
    analogWrite(Motor, Geschwindigkeit);
  }
}




/*
  void loop()
  {
  PotiWert = analogRead(PotPin);    // liest Wert vom Poti aus
  Serial.println (PotiWert);
  Serial.println (Geschwindigkeit);

  analogWrite(Motor, Geschwindigkeit);

  Geschwindigkeit = PotiWert - Beschleunigen;

  if (Geschwindigkeit >= 140)
  {
    Beschleunigen = +Beschleunigen;
  }

  if (Geschwindigkeit >=30)
  {
    Beschleunigen = -Beschleunigen;
  }
  delay(100);
  }
*/

