/*
mrbbp
4 potards connectés à un mc pour envoie des valeurs à Processing

v03:  changement de mc (exen mini M0 -> arduino leonardo)
v04:  envoie d'une premikere lecture des potard (init)
v05: inverse les valeurs des potards (0-> 1024 et 1024 -> 0);
v06: ajoute deux inté en D10 et D11
*/

const int pot1 = A0;
const int pot2 = A1;       
const int pot3 = A2;
const int pot4 = A3;
const int pInt1 = 10;
const int pInt2 = 11;

int responseDelay = 2;
int seuil = 2;// seuil de mouvement
int table[] = {pot1, pot2, pot3, pot4};    
int old1, old2, old3, old4, oldInt1, oldInt2, int1, int2;
bool first = true;

void setup() {
  Serial.begin(19200);
  while (!Serial) {
    ; // wait for serial port to connect. Needed for native USB port only
  }
  delay(100);
  Serial.println("début init programme");
  pinMode(13, OUTPUT); // la led
  pinMode(pInt1, INPUT_PULLUP);
  pinMode(pInt2, INPUT_PULLUP);
  // clignote 4 fois
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
    if (inByte == 10) {
      // si "\n", renvoie les valeurs (lancement du prog processing)
      // envoie les valeurs initiales
      Serial.print("p1:");
      Serial.println(Reading1);
      Serial.print("p2:");
      Serial.println(Reading2);
      Serial.print("p3:");
      Serial.println(Reading3);
      Serial.print("p4:");
      Serial.println(Reading4);
      Serial.print("int1:");
      Serial.println(digitalRead(pInt1));
      oldInt1 = digitalRead(pInt1);
      Serial.print("int2:");
      Serial.println(digitalRead(pInt2));
      oldInt2 = digitalRead(pInt2);
    }
  } else {
    /* si la valeur est proche de l'ancienne (seuil), il n'envoie rien
      Les potards analogiques ont parfois la bougeotte sur des valeurs envoyées
      il vaut mieux imposer un seuil de sensibilité un peu plus élévé que la valeur seule
    */
    if (Reading1 < old1 - seuil || Reading1 > old1 + seuil) {
      // format "x:(valeur:0-1024)" p.ex: "x:1022"
      Serial.print("p1:");
      Serial.println(Reading1);
      // met à jour la valeur mémorisée
      old1 = Reading1;
      blink();
    }
    if (Reading2 < old2 - seuil || Reading2 > old2 + seuil) {
      Serial.print("p2:");
      Serial.println(Reading2);
      // met à jour la valeur mémorisée
      old2 = Reading2;
      blink();;
    }
    if (Reading3 < old3 - seuil || Reading3 > old3 + seuil) {
      Serial.print("p3:");
      Serial.println(Reading3);
      // met à jour la valeur mémorisée
      old3 = Reading3;
      blink();
    }
    if (Reading4 < (old4 - seuil) || Reading4 > (old4 + seuil)) {
      Serial.print("p4:");
      Serial.println(Reading4);
      // met à jour la valeur mémorisée
      old4 = Reading4;
      blink();
    }
    if(digitalRead(pInt1) != oldInt1){
      int1 = digitalRead(pInt1);
      Serial.print("int1:");
      Serial.println(int1);
      oldInt1 = int1;
      blink();
    }
    if(digitalRead(pInt2) != oldInt2){
      int2 = digitalRead(pInt2);
      Serial.print("int2:");
      Serial.println(int2);
      oldInt2 = int2;
      blink();
    }
    delay(responseDelay);
  } 
}
// clignotement 1 fois durée total = 100ms
void blink() {
  digitalWrite(13, HIGH);
  delay(50);
  digitalWrite(13, LOW);
  delay(50);
}

int readPot(int index) {
  // lecture des valeurs analogiques:
  int reading = analogRead(table[index]);
  int retour = 1024 - reading;
  return retour;
}
