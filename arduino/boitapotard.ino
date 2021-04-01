/*
mrbbp
4 potards connectés à un mc pour envoie des valeur à Processing

v03:  changement de mc (exen mini M0 -> arduino leonardo)
v04:  envoie d'une premikere lecture des potard (init)
v05: inverse les valeurs des potards (0-> 1024 et 1024 -> 0);
*/

const int pot1 = A0;           // analog sensor
const int pot2 = A1;           // analog sensor 
const int pot3 = A2;
const int pot4 = A3;
const int int1 = A10;
const int int1 = A11;

int responseDelay = 2;          // response delay of the mouse, in ms
int seuil = 2;                  // seuil de mouvement
int table[] = {pot1, pot2, pot3, pot4};    // pin numbers for {x, y}
int mouseReading[2];            // final mouse readings for {x, y}
int old1, old2, old3, old4;
bool first = true;

void setup() {
  Serial.begin(19200);
  while (!Serial) {
    ; // wait for serial port to connect. Needed for native USB port only
  }
  delay(100);
  Serial.println("début init programme");
  pinMode(13, OUTPUT); // la led
  // si on veut simuler une souris (utile pour les events MousePress et MouseRelease, interceptés dans Processing)
  //Mouse.begin();
  for (int i=0; i<4;i++) {
    digitalWrite(13, HIGH);
    delay(50);
    digitalWrite(13, LOW);
    delay(50);
  }
  delay(500);
  Serial.println("fin init");
}

void loop() {
  // read and scale the two axes:
  int Reading1 = readPot(0);
  int Reading2 = readPot(1);
  int Reading3 = readPot(2);
  int Reading4 = readPot(3);

  if (Serial.available() > 0) {
    // get incoming byte:
    int inByte = Serial.read();
    //Serial.println(inByte);
    if (inByte == 10) {
      // si "\n", renvoie les valeurs (lancement du prog processing)
      Serial.print("a:");
      Serial.println(Reading1);
      Serial.print("b:");
      Serial.println(Reading2);
      Serial.print("c:");
      Serial.println(Reading3);
      Serial.print("d:");
      Serial.println(Reading4);
    }
  } else {
    /* si la valeur est proche de l'ancienne (seuil), il n'envoie rien
      Les potards analogiques ont parfois la bougeotte sur des valeurs envoyées
      il vaut mieux imposer un seuil de sensibilité un peu plus élévé que la valeur seule
    */
    if (Reading1 < old1 - seuil || Reading1 > old1 + seuil) {
      // format "x:(valeur:0-1024)" p.ex: "x:1022"
      Serial.print("a:");
      Serial.println(Reading1);
      // met à jour la valeur mémorisée
      old1 = Reading1;
      digitalWrite(13, HIGH);
      delay(50);
      digitalWrite(13, LOW);
      delay(50);
    }
    if (Reading2 < old2 - seuil || Reading2 > old2 + seuil) {
      Serial.print("b:");
      Serial.println(Reading2);
      // met à jour la valeur mémorisée
      old2 = Reading2;
      digitalWrite(13, HIGH);
      delay(50);
      digitalWrite(13, LOW);
      delay(50);
    }
    if (Reading3 < old3 - seuil || Reading3 > old3 + seuil) {
      Serial.print("c:");
      Serial.println(Reading3);
      // met à jour la valeur mémorisée
      old3 = Reading3;
      digitalWrite(13, HIGH);
      delay(50);
      digitalWrite(13, LOW);
      delay(50);
    }
    if (Reading4 < (old4 - seuil) || Reading4 > (old4 + seuil)) {
      Serial.print("d:");
      Serial.println(Reading4);
      // met à jour la valeur mémorisée
      old4 = Reading4;
      digitalWrite(13, HIGH);
      delay(50);
      digitalWrite(13, LOW);
      delay(50);
    }
    delay(responseDelay);
  }

  /*// read button and click mouse:
    //if the switch attached to pin d0 is pressed
    if(digitalRead(0) == HIGH && oldB != HIGH){
    //press and hold the right mouse button
    Serial.println("P");
    //Mouse.press();
    }
    //if the switch attached to pin d0 is not pressed
    if(digitalRead(0) == LOW && oldB != LOW){
    //release the right mouse button
    Serial.println("R");
    //Mouse.release();
    }
    // met à jour les valeurs mémorisées
    oldB = digitalRead(0);
  */
  //Serial.println("loop");
}


int readPot(int index) {
  // read the analog input:
  int reading = analogRead(table[index]);
  int retour = 1024 - reading;
  return retour;
}
