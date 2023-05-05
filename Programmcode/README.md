Programmcode
====

**Softwareentwicklung**
====

Unsere Roboter Software läuft auf einem Arduino Nanao-Every.
 Wir haben angefangen für die Sensoren, dem Lenkservo und dem Motortreiber Testprogramme zu schreiben,
 um herrauszufinden, wie diese funktionieren.
 Wir haben 2 getrennte Programme für das Eröffnungsrennen und das Rennen mit Hindernisen.
 
**Eröffnungsrennen:**
 
 
 
 
 
**Hindernisrennen:**
 
 Wir verwenden zum erkennen der Hindernisse eine Huskylens AI Kamera von DFRobot.
 Die Huskylenskann darauf trainiert werden farbige Blöcke zu erkennen. Sie ordnet jeder gelernten Farbe eine ID zu.
 Bei der Abfrage liefert die Huskylensin in der Reinfolge der IDs.
 für einen gefundenen Blovck liefert sie die Position der Blockmitte im Bild in XY Koordinaten, die Breite und Höhe des Blocks und die ID der Farbe.
 Rote blöcke werden immer als erstes geliefert, da sie ID 1 haben, auch wenn ein grüner Block näher am Roboter steht.
 Um den Block zu finden, dem wir als nächstes ausweichen müssen, gehen wir wie folgt vor:
 
 
 **Pseudocode:**
 
 berechne die Position der Unterkannte des Blocks im Bild
 
 wenn Unterkannte des gefundenen Blockes nahe genug am Roboter und Unterkannte näher am Roboter als der letzte gemerkte Blocke
 
 dann merke dir diesen Block
 
 wenn kein Block in Sicht 
 
 dann lösche gemerkten Block
 
 wenn ein Block nahe genug am Roboter ist, starten wir ein Ausweichmanöver.
 
 
 **Ausweichmanöver Pseudocode:**
 
 Lenke in Ausweichrichtung, bis der Block nicht mehr zu sehen ist
 
 dann fahre kurz geradeaus
 
 dann lenke kurz in gegenrichtung 
 
 wenn kein Block in Sicht ist, versuchen wir in die Mitte der Banden zu steuern
 
 
 **Erkennen einer Kurve und der Fahrtrichtung:**
 
 Hierzu benutzen wir einen Grove Farbsensor. Der Farbsensor liefert 4 Werte: Rot, Grün, Blau, Helligkeit
 Beim start merkt sich der Roboter die Helligkeit des Untergrundes als Referenz.
 
 
 **Erkennen einer Linie Pseudocode:**
 
 Wenn Bodenhelligkeit weniger als 80% der gemerkten Helligkeit
 
 dann prüfe RGB Werte
 
 wenn Rot > Grün und Rot > Blau
 
 dann Orangene Linie gefunden
 
 wenn blau > Rot und Blau > Grün 
 
 dann Blaue Linie gefunden
 
 
 Aus der Farbe der ersten erkannten Linie bestimmt der Roboter die Fahrtrichtung und die Drehrichtung, wenn er an eine Kurve kommt.
