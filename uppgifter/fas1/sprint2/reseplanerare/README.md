**Notera att denna fil kommer att uppdateras med tips på mål etc.**
**Jag ruschar ut den nu så att ingen blockerar på den. /Tobias**


# Reseplanerare 1.0

Reseplaneraren syftar till dels att visa ett bra exempel på C-kod
för ett större program som ledning för framtiden, men också till
att ge er möjligheten att se litet grand av logiken bakom system
som ni säkerligen har använt.

Uppgiften går ut på att vidareutveckla ett halvfärdigt system till
en fungerande reseplanerare. I den kod ni får ut finns stöd för:

* [graph.h](graph.h) -- ett generellt grafbibliotek
* [list.h](list.h) -- ett generellt listbibliotek 
* [network.h](network.h) -- ett lager ovapå grafbiblioteket som vet något om resor

När man just nu kör systemet går det in i en loop som frågar
varifrån man vill åka och vart. Du kan se en lista över platser
som finns i systemet i [data.txt](data.txt). Notera att ÅÄÖ har
ersatts av AAO. 

Här är ett exempel på en interaktion med programmet (input
markerad för tydlighets skull):

```
================================
 Welcome to the travel planner!
================================

What is your starting station?
Stora Torget <-- input
Where would you like to go?
Vaksala torg <-- input

adding duration to travel@0x7faabbd018c0: 4

adding duration to travel@0x7faabbd018e0: 9

adding duration to travel@0x7faabbd01950: 4
@ -1: #41 Stora Torget --(4)--> Kungsgardets center
@ -1: #22 Kungsgardets center --(9)--> Centralstationen
@ -1: #10 Centralstationen --(4)--> Vaksala torg
What is your starting station?
```

Programmet fortsätter att köra tills du trycker enter
som svar på frågan "Where would you like to go".

Logiken i programmet just nu använder antalet hållplatser på resan
för att avgöra vilken resa som är bäst. Det betyder att en resa
som passerar 11 hållplatser alltid är bättre än en som passerar 12,
även om den första innhåller 4 bussbyten och den sista inget.

Uppgiften går ut på att ändra på denna dumhet och istället använda
restiden som ett mått. Det blir dock problematiskt med bussbyten
eftersom man måste räkna ut när nästa buss går från varje
hållplats.


## Steg 1: Generera tidtabeller

Grafen just nu är en massa noder (som motsvarar stationer) och
bågar (sträcker mellan stationerna). Bågarna (edge på engelska)
har vikter som avser hur lång tid det tar att åka sträckan. Vi har
en fil [start.txt](start.txt) som innehåller alla bussars
avgångstid från sina ändhållplatser. Givet denna information kan
vi fylla i tidtabeller för alla hållplatser för alla bussar enligt
denna enkla algoritm:

- For every bus line L in the data
   - For every trip T that L does, with starting time ST and
     starting and ending positions SP and EP
      * Walk the graph from SP to EP, adding an entry for L with
        ST plus the accumulated time it took to get there

Skapa en tidtabellsstruktur som avser en viss buss, samt vilka
tiden den är vid en viss hållplats, samt i vilken riktning bussen
åker (kan t.ex. göras med hjälp av namnet på stationen man kommer
från eller skall till). Fyll i den med hjälp av ovanstående.

Du kan antingen spara tidtabeller i varje nod i grafen, eller
varför inte som ett binärt sökträd utanför grafen där nycklarna är
stationsnamn och datat är en lista över alla hålltider.


## Steg 2: Ändra så att planeraren använder hållplatstider istället för antal hållplatser. 

Reseplaneraren använder Dijkstras algoritm för grafsökning. Den
tittar på kortaste sträckan vidare, men tar inte bytestid med i
beräkningen. Låt T vara den tid som vi anlöper hållplats H1. Vi
vill vidare till H2 och det finns två bussar -- B1 och B2. B1 är
den vi sitter på -- då är "kostnaden" för att åka från H1 till H2
med B1 just den vikt V som står på bågen mellan noderna (så långt
är allt oförändrat). För B2 måste vi dock slå upp i tidtabellen
när närmaste avgång är. Om den är vid tiden T', så kan vi räkna ut
"kostnaden" att åka H1 till H2 med B2 som T' - T + V.

Ett enkelt sätt att åstadkomma denna förändring är genom att
använda en [funktionspekare](http://c.learncodethehardway.org/book/ex18.html).


## Steg 3: Fixa minnesläckage

Det finns minnesläckage i programmet. De skall åtgärdas! 


## Steg 4: Dokumentation

Det finns dokumentation i programmet. Alla nya funktioner och alla
förändringar måste speglas i dokumentationen.


## Steg 5: Ta bort skräputskrifter, etc.

* Programmet skriver ut en massa dumheter. Ta bort dem. 
* Programmet kraschar om man frågar efter noder som inte finns. Fixa det (på lämpligt sätt). 

Det skall gå att köra programmet så här: 

```
$ ./travel --from Polacksbacken --to "Uppsala C" --start 15:30 
```

för att få fram snabbaste resvägen från Polacksbacken till 
Uppsala C som avgår 15:30. Programmet skall titta på den 
närmaste avgången efter 15:30 och använda det som *senaste
tillåtna ankomsttid*. Programmet skall titta på alla bussar
som avgår mellan starttid och senaste ankomsttid från 
Polacksbacken (i detta exempel) för att hitta den som har
kortaste resväg i minuter. 


# Tester

Du uppmanas å det starkaste att lägga till tester för allt du
skriver! Det är inte (ännu) ett krav, men det kommer att hjälpa dig!
Använd också programmets tester för regressionstester! 
