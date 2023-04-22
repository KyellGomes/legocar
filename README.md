Future Engineers - Roadrunners
====

Dieses GitHub-Repository dient als Vorlage für Teams in Future Engineers.

## Content

* Der Ordner `Programmcode` enthält den kompletten Programmcode, der für das Roboterauto verwendet wird.
* Im Ordner `Roboterauto` sollen sechs Fotos abgelegt werden, die das Roboterauto aus allen Richtungen zeigen.
* Im Ordner `Technische Zeichnungen` werden Zeichnungen von Komponenten des Roboterautos oder dem gesamten Roboterauto abgelegt.
* Der Ordner `Video` beinhaltet die Datei "video.md", die mit einem Link zu einem Youtube-Video befüllt werden muss. Das Video zeigt das Roboterauto beim Absolvieren des Spielfeldes.

## Einleitung
Bauanleitung:
Wir haben unser Auto aus Legoteilen und Kunststoffplatten gebaut.
Die Bodenplatte besteht aus durchsichtigem Kunststoff. Eine Zeichnung in Originalgröße mit Bohrungen haben wir dazu gelegt. 
Die Hinterachse haben wir aus Legoteilen gebaut. Eine Fotobauanleitung liegt in Hinterachse.zip.
Die Hinterachse hat ein Differenzialgetriebe damit das Auto besser um Kurven fahren kann. Zum Antrieb haben wir zwei Lego Power functions Motoren benutzt die über ein Kopplungsgetriebe mit der Hinterachse verbunden sind.
Die lenkbare Vorderachse ist ebenfalls mit Legoteilen gebaut. Siehe Vorderachse.zip.
Oberhalb von Hinterachse und Vorderachse haben wir eine zweite Kunststoffplatte eingebaut. Auf dieser Platte haben wir unseren Arduino, diverse Elektronik Bauteile und unseren Lego Kameraturm drauf montiert.
Bauanleitung Kameraturm: siehe Kameraturm.zip.
Das Akkufach befindet sich oberhalb der Hinterachse damit immer genügend Gewicht auf der Hinterachse liegt.

Stromversorgung:
Wir haben uns überlegt wie viel Strom und Spannung unser Auto braucht.
Spannung:
Die beiden Motoren brauchen 9V und der Arduino und der Lenkservo jeweils 5V. Der Motortreiber verbraucht nochmal 1,4V für seine Transistoren.
Strom:
Die beiden Motoren verbrauchen zusammen maximal 2.600 mA.
Der Lenkservo braucht bis zu 900 mA.
Die Kamera braucht  ca. 300 mA.
Der Arduino bracht ca. 100 mA.
Das sind zusammen bis zu 3.900 mA.
Wir brauchen also eine Batterie die mindestens 4.000 mA und mindestens 10,4V liefern kann. Dabei soll die Batterie möglichst klein und leicht sein.
Wir haben uns angeguckt was für Batterien oder Akkus in Modellbauautos normalerweise verwendet werden. Wir haben uns dann für 11,1V Lipo - Akkus entschieden.

Motoriesierung: 
Wir haben 2 Powerfunctions L Lego Motoren genommen weil 1 Motor nicht genug Kraft zum Anfahren hat.
Die Motoren sind über ein Getriebe und elektrisch miteinander und mit dem Motortreiber verbunden. Dafür haben wir die Legoanschlüsse abgeschnitten und Normale Stecker angelötet. Wir haben die Motoren miteinander verbunden weil im Regelwerk steht dass man nur einen
logischen aber zwei physikalische Motoren haben darf.
Wir haben ein Diffenzialgetriebe eingebaut damit sich in der Kurve das innere Rad langsamer dreht als das äußere.





_In diesem Teil muss das Team das Roboterauto und den Entwicklungsprozess beschreiben._
