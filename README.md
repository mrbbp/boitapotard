# boitapotard
Arduino + hardware + Processing = graphisme généré (à la ikeda)

4 potards + 2 intés soudés sur arduino Leonardo headerless

```
arduino | --- | capteur.       | arduino
------------------------------------
     A0 | --- | potard 1
     A1 | --- | potard 2
     A2 | --- | potard 3
     A3 | --- | potard 4
     …
     10 | --- | interrupteur 1 | GND
     11 | --- | interrupteur 2 | GND
     …
     13 | --- | led
```

Lorsque l'arduino est initilaisée, elle attend que le programme lui envoie un retour chariot pour commencer à envoyer les valeurs d'init.
Lorsqu'on manipule les inté ou potards, les valeurs brutes sont envoyées sur le port série au programme Processing.


MàJ 211205 - use midiUSB Library on Arduino + midiBus on Processing
Modifying just button pin for matchnig with my soldering choice, the `midictrl.ino` sketch.
Work fine on Processing 3.5.3.
Have some Processing Library error.
