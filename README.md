# boitapotard
Arduino + hardware + Processing = graphisme généré (à la ikeda)

4 potards + 2 intés soudés sur arduino Leonardo headerless

A0 | --- | potard 1
A1 | --- | potard 2
A2 | --- | potard 3
A3 | --- | potard 4
…
10 | --- | interrupteur 1
11 | --- | interrupteur 2
…
13 | --- | led

Lorsque l'arduino est initilaisée, elle attend que le programme lui envoie un retour chariot pour commencer à envoyer les valeurs d'init.
Lorsqu'on manipule les inté ou potards, les valeurs brutes sont envoyées sur le port série au programme Processing.
