# **Hausübung 3 - Ausarbeitung**

## **Aufgabe 1: Schach** (`src/chess`)

### **Aufgabe (a): Standard-Chess**

#### **Lösungsidee**
Die Aufgabe besteht darin, eine vollständige und erweiterbare Spiellogik für ein Schachspiel zu entwerfen, die neben der
Zugausführung auch das korrekte Erkennen von Spielendzuständen wie Schachmatt und Patt ermöglicht. Ausgangspunkt der
Lösung ist eine klare Vererbungshierarchie: Eine abstrakte Basisklasse beschreibt ein allgemeines Schachbrett mit den
notwendigen Funktionen zur Abfrage des Spielzustands, während eine konkrete abgeleitete Klasse die eigentliche
Spielregellogik implementiert. Ebenso existiert eine gemeinsame abstrakte Basisklasse für Schachfiguren, von der alle konkreten
Figuren wie König, Dame, Turm, Läufer, Springer und Bauer erben. Dadurch wird sichergestellt, dass jede Figur ein einheitliches
Interface besitzt, ihr konkretes Zugverhalten jedoch individuell umgesetzt werden kann.

Die Lösungsidee sieht vor, dass jede Figur selbst entscheidet, ob ein Zug ihrer grundlegenden Bewegungsregel entspricht,
während das Schachbrett zusätzlich prüft, ob dieser Zug im Gesamtkontext des Spiels zulässig ist. Dazu gehört insbesondere
die Kontrolle, ob ein Zug den eigenen König in Schach setzen oder im Schach belassen würde. Zur Erkennung von Schach, Schachmatt und Patt wird der aktuelle Spielzustand analysiert, indem alle gegnerischen Figuren betrachtet und ihre Wirkungsbereiche ermittelt werden. Anschließend wird geprüft, ob für den betroffenen Spieler noch mindestens ein legaler Zug existiert. Ist dies nicht der Fall, wird abhängig davon, ob der König im Schach steht oder nicht, Schachmatt oder Patt festgestellt.

Durch diese Aufteilung der Verantwortung zwischen Figurenklassen und Brettklasse entsteht eine übersichtliche und
wartbare Architektur. Die Vererbung ermöglicht es, neue Figuren oder Regelvarianten später einfach zu ergänzen,
ohne bestehende Logik grundlegend ändern zu müssen. Gleichzeitig bleibt die Lösung gut verständlich, da jede Klasse klar
definierte Aufgaben übernimmt und die komplexeren Spielregeln zentral an einer Stelle ausgewertet werden.
#### **Testfälle**
Auswählen einer Figur:
![auswählen.png](src/chess/resources/tests/ausw%C3%A4hlen.png)

Keine legalen Moves:
![keinelegalenmoves.png](src/chess/resources/tests/keinelegalenmoves.png)

Man kann auch keine fremden Figuren auswählen.

### **Der Bauer** <br>
Der Bauer kann bei seinem ersten Zug 2 Felder nach vorne gehen:
![auswählen.png](src/chess/resources/tests/ausw%C3%A4hlen.png)
![bauermove2.png](src/chess/resources/tests/bauermove2.png)

Er kann sich nicht 2 Felder bewegen wenn nicht auf Startposition:
![bauermove1.png](src/chess/resources/tests/bauermove1.png)

Er kann diagonal schlagen:
![bauerhauer.png](src/chess/resources/tests/bauerhauer.png)
![bauerhauer2.png](src/chess/resources/tests/bauerhauer2.png)

Er kann Schachmatt setzen (wenn er ganz cool ist):
![coolerbauer.png](src/chess/resources/tests/coolerbauer.png)

Er kann auch promoted werden:
![gigachadbauer.png](src/chess/resources/tests/gigachadbauer.png)

### **THE ROOK**<br>
Der Turm kann nicht über Pieces springen:
![turmkannnichtspringen.png](src/chess/resources/tests/turmkannnichtspringen.png)

Sonst kann sich der Turm natürlich in jede Richtung bewegen und schlagen.
![turmisfrei.png](src/chess/resources/tests/turmisfrei.png)
![turmhauer.png](src/chess/resources/tests/turmhauer.png)

### **Der Springer**<br>
Der Springer kann über andere Figuren springen.
![springer.png](src/chess/resources/tests/springer.png)
![hippityhoppity.png](src/chess/resources/tests/hippityhoppity.png)

Er kann auch in seiner L-Shape gegnerische Figuren schlagen:
![hauermimsprung.png](src/chess/resources/tests/hauermimsprung.png)
![boomoida.png](src/chess/resources/tests/boomoida.png)

Es werden auch die Fälle richtig erkannt wo der König zwar unter Schach ist, aber eine andere Figur
die angreifende Figur schlagen könnte:
![derfall.png](src/chess/resources/tests/derfall.png)
### **Der Läufer**<br>

Der Läufer kann auch nicht über andere Figuren springen:
![lauferlaufthaltnur.png](src/chess/resources/tests/lauferlaufthaltnur.png)

Er kann gegnerische Figuren in seiner diagonalen Laufbahn schlagen:
![laufforestlauf.png](src/chess/resources/tests/laufforestlauf.png)
![ripbauer.png](src/chess/resources/tests/ripbauer.png)
![laaaaalalala.png](src/chess/resources/tests/laaaaalalala.png)

Der Läufer kann auch ganz gekonnt Schachmatt setzen:
![gigachadlaufer.png](src/chess/resources/tests/gigachadlaufer.png)

Die Figuren können den König vor Schach auch per Block verteidigen:
![monsterblock.png](src/chess/resources/tests/monsterblock.png)

### **Queen**

Die Königin kann sich in alle Richtungen + Diagonal bewegen und kann nicht über andere Figuren springen:
![queen.png](src/chess/resources/tests/queen.png)

Kann auch Schachmatt setzen:
![queem.png](src/chess/resources/tests/queem.png)

### **King**

Der König kann sich ein Feld in alle Richtungen bewegen, wobei er sich nicht in Schach bringen darf:
![king.png](src/chess/resources/tests/king.png)

Der König kann auch gegnerische Figuren angreifen:
![chomp.png](src/chess/resources/tests/chomp.png)

Es kann auch ein Stalemate vorkommen:
![stalemate.png](src/chess/resources/tests/stalemate.png)

Der König kann auch castlen:
![castling.png](src/chess/resources/tests/castling.png)
![castling2.png](src/chess/resources/tests/castling2.png)
![castling3.png](src/chess/resources/tests/castling3.png)
![castling4.png](src/chess/resources/tests/castling4.png)

Der König kann nicht mehr castlen wenn der Turm oder der König schon einmal bewegt wurden.
![bewegunginderhüfte.png](src/chess/resources/tests/bewegunginderh%C3%BCfte.png)

Der König kann nicht über Schach castlen:
![schachcastling.png](src/chess/resources/tests/schachcastling.png)

### **Aufgabe (b): Random-Chess**

#### **Lösungsidee**

#### **Testfälle**

### **Aufgabe (c): Chess 2.0**

#### **Lösungsidee**

#### **Testfälle**

