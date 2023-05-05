Programmcode
====
**Softwareentwicklung**
====

 Unsere Roboter Software läuft auf einem Arduino Nanao-Every.
 Wir haben angefangen für die Sensoren, dem Lenkservo und dem Motortreiber Testprogramme zu schreiben,
 um herrauszufinden, wie diese funktionieren.
 An unserem Auto haben wir eine Ampel aus 3 LEDs (Rot, Gelb, Grün).
 Wir benutzen die LEDs beim Setup zum anzeigen, dass der Roboter fertig ist. Während der Fahrt benutzen wir sie,
 um wichtige Stellen im Ablauf zu signalisieren, z.B. Kurve links erkannt/Kurve rechts erkannt.
 Wir haben 2 getrennte Programme für das Eröffnungsrennen und das Rennen mit Hindernisen.
 
 **Eröffnungsrennen:**
 
 Beim eröffnungsrennen orientiert sich der Roboter mit dem rechten und linken Ultraschallsensor.
 Das Programm teilt sich in einem Anteil, der im Setup nur einmal läuft, und die Loop, die bis zum Ende der 3 Runden immer wieder wiederholt wird.
 
**Pseudocode Anfangssequenz:**
 
 
 Ampel Rot 
 
 Messe Abstand links, Rechts, Vorne
 
 Wenn Abstand vorne > 130 dann Startplatz Hinten, sonst Startplatz Vorne 
 
 Wenn Wandabstand Links < 10 dann Fahrtrichtung Links 
 
 wenn Wandabstand Rechts < 10 dann Fahrtrichtung Rechts
 
 Ampel Gelb
 
 Warte auf Startbutton
 
 Ampel Grün
 
 Wenn Fahrtrichtung unbekannt dann halte Abstandzwischen beiden Wänden bis ein Seitensensor > 60 misst dann Kurve erkannt
 
 Wenn Fahrtrichtung beannt dann langsam vorfahren bis Sensor in Fahrtrichtung > 60 misst dann erste Kurve erkannt
 
 Fahre erste Kurve 
 
 Zähle Kurve
 
 Nach Kurve fahre Geradeaus bis Sensorin Fahrtrichtung wieder Innenwand erkennt 
 
 
 
**Pseudocode Hauptschleife:**


 Messe Abstand zur Innenwand 
 
 Berechne Differenz zwischen gemessenem Abstand und 20 cm Wandabstand 
 
 Lenke propotional zur Innenwand hin oder von der Innenwand weg
 
 Wenn Sensor in Fahrtrichtung > 80 cm misst und genügend Zeit seit letzter Kurve
 
 Dann fahre und zähle Kurve
 
 Wenn Kuvenzähler = 12
 
 Dann Fahre kurz vorwärtz in Geraden Abschnitt
 
 Dann Stop 

 
 
 
**Hindernisrennen:**
 
 Wir verwenden zum erkennen der Hindernisse eine Huskylens AI Kamera von DFRobot.
 Die Huskylens kann darauf trainiert werden farbige Blöcke zu erkennen. Sie ordnet jeder gelernten Farbe eine ID zu.
 Bei der Abfrage liefert die Huskylensin in der Reinfolge der IDs.
 für einen gefundenen Block liefert sie die Position der Blockmitte im Bild in XY Koordinaten, die Breite und Höhe des Blocks und die ID der Farbe.
 Rote blöcke werden immer als erstes geliefert, da sie ID 1 haben, auch wenn ein grüner Block näher am Roboter steht.
 Um den Block zu finden, dem wir als nächstes ausweichen müssen, gehen wir wie folgt vor:
 
 
 **Pseudocode:**
 
 berechne die Position der Unterkannte des Blocks im Bild
 
 wenn Unterkannte des gefundenen Blockes nahe genug am Roboter und Unterkannte näher am Roboter als der letzte gemerkte Block
 
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
 
 Hierzu benutzen wir einen Grove Farbsensor. Der Farbsensor liefert 4 Werte: Rot, Grün, Blau und die Helligkeit.
 Beim start merkt sich der Roboter die Helligkeit des Untergrundes als Referenz.
 
 
 **Erkennen einer Linie Pseudocode:**
 
 Wenn Bodenhelligkeit weniger als 80% der gemerkten Helligkeit
 
 dann prüfe RGB Werte
 
 wenn Rot > Grün und Rot > Blau
 
 dann Orangene Linie gefunden
 
 wenn blau > Rot und Blau > Grün 
 
 dann Blaue Linie gefunden
 
 
 Aus der Farbe der ersten erkannten Linie bestimmt der Roboter die Fahrtrichtung und die Drehrichtung, wenn er an eine Kurve kommt.
