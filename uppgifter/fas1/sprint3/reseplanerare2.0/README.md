# Inlupp 3.b: Reseplanerare 2.0

I denna uppgift skall vi utöka reseplaneraren med några olika
funktioner, men framförallt skall vi titta på kodens generalitet
(därtill uppmuntrade av en deluppgift som kommer att dra nytta av
generaliteten). Vi skall också se hur man kan använda
standardbiblioteket för att anropa andra program från sitt
C-program.

Sammafattningsvis skall vi i denna uppgift:

1. Se till att koden för grafer och listor är generell
2. Utökad funktion: resa miljövänligt
3. Generera en resplan
4. Lägg till tester för **all** ny funktionalitet som lagts till utöver det som var givet (se instruktioner i [Lagerhanterare 3.0](../lagerhanterare3.0/README.md) för vägledning om vad som inte skall testas)
5. Kodkonventioner


## Generella bibliotek för listor och grafer

Biblioteken list.c och graph.c (och *.h) är avsedda att vara
generella, dvs. det skall vara kod som inte har någonting med
reseplanering att göra. Det är inte tillåtet för denna kod att
inkludera någon headerfil (eller motsvarande) från delar av
programmet som är specifika för reseplaneraren (t.ex. network.h).

Samarbeta med ett annat kodpar (fråga gärna på piazza) och skapa
tillsammans två generella bibliotek, ett för listor och ett för
grafer som skall gå att använda i båda programmen. Det går utmärkt
att varje par gör sina egna bibliotek så länge båda bibioteken går
att använda i båda programmen.

Ett bra sätt att bryta ut programlogik ur ett bibliotek och på så
sätt göra det mer generellt är med hjälp av funktionspekare.
Notera att programmet redan använder funktionspekare på många
ställen. Det är t.ex. lämpligt att vissa sökfunktioner tar emot en
funktionspekare som anropas på allt data och räknar ut vikter. 


## Resa miljövänligt

Grafen i reseplaneraren mäter avstånd mellan platser. Varje båge i
grafen har information om vilken busslinje som avses. Nu är det så
att kommunen experimenterar med olika typer av bussar som drar
olika mycket "bensin". Det finns tre typer av bussar:

- Typ A: drar en enhet bensin per tidsenhet
- Typ B: drar en enhet bensin per tidsenhet för sträckor < 3, annars 1 enhet bensin per 2 tidsenheter
- Typ C: drar en enhet bensin per tidsenhet för sträckor > 3, annars 1 enhet bensin per 2 tidsenheter

Vi vill ge resenärer en möjlighet att resa miljövänligt och därför
utöka programmet med ett motsvarande informationsstöd. När man
söker en resa från A till B skall man inte längre bara få den
kortaste resvägen utan

1. Information om dess bränsleåtgång
2. Veta vilken den bränslesnålaste resvägen är, och veta dess tidsåtgång

Med hjälp av de generella graf- och listbiblioteket är det inte
särskilt svårt att göra två sökningar: en som beaktar tid, en som
beaktar bränsleåtgång.


## Generera en resplan

Flaggan `--generate-plan` skall generera en PDF-fil med en resplan
för en given sökning. Denna resplan skall innehålla:

För varje bussfärd som resan består av:

- En tabell med 
  * Starthållplats och tid för avfärd
  * Ändhållplats och ankomsttid
- En linjekarta för de busslinjer som ingår, med markering vilka delsträckor som avses på redan

Observera att både det snabbaste och det mest miljövänliga
alternativen skall anges!

Denna PDF skall genereras med hjälp av LaTeX och dot (se nedan).
Använd två textfiler med latexdokument för all kod innan
innehållet tabellen, och all efter, och generera ett nytt
LaTeX-dokument med hjälp av dessa två samt tabellens data
och linjekartan. Linjekartan skall vara en PDF som inkluderas
med (ungefär):

```
\includegraphics[width=10cm]{travelmap.pdf}
```

Gången för att generera en resplan är alltså:

1. Räkna fram resultatet (som tidigare)
2. Skapa koden för linjekartan (se nedan)
3. Generera en PDF för linjekartan
4. Skapa koden för tabellen
5. Skapa ett LaTeX-dokument med tabellens kod i
6. Generera en PDF-fil

Funktionen `system` i `stdlib.h` kan användas för att anropa ett
program från ett C-program:

```
system("pdflatex linjekarta.tex")
```

### Dot

Programmet
[dot](https://en.wikipedia.org/wiki/DOT_(graph_description_language))
används av vårt dokumentationsverkty
[doxygen](http://www.stack.nl/~dimitri/doxygen/) för att generera
anropsgrafer. Dot använder ett extremt enkelt språk för att rita diagram, t.ex.

```
// The graph name and the semicolons are optional
 graph graphname {
     a -- b -- c;
     b -- d;
 }
```

genererar detta (via Wikipedia)

![undirected graph](https://upload.wikimedia.org/wikipedia/commons/thumb/3/39/DotLanguageUndirected.svg/440px-DotLanguageUndirected.svg.png)

För att skapa en linjekarta kan du alltså generera en mycket enkel
oriktad graf från informationen för de linjer som är med i resan.
Använd sedan attribut (se exempel på wikipediasidan) för att
färglägga just de sträckor som är med i resan.


## Testning

All ny funktionalitet utöver det som var givet till Lagerhanterare
2.0 skall testas. För att undvika upprepningar (och bara behöva
fixa fel i ett enda dokument), se instruktioner i
[Lagerhanterare 3.0](../lagerhanterare3.0/README.md) för
vägledning om vad som inte skall testas och hur du skall tänka
kring enhetstestning.


## Kodkonventioner

För all kod, använd samma namngivningskonventioner och
formattering. Du kan använda programet `astyle` med flaggorna `-s4
-A7` för att formattera om kodfiler:

```
astyle -A7 -s4 foo.c 
```

Ta också bort all `CamelCase` och ersätt med `snake_case` och ta
också bort alla `_t` utanför typedefs, alltså `struct foo_t` skall
bli `struct foo`. Fundera på om det inte finns ett smidigt sätt
att göra detta som inte är lika felbenäget som att göra det
manuellt.


