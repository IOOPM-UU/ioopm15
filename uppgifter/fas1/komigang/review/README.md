Kodgranskning
=============

Välj en uppgift ur nedanstående lista av fem små program att
implementera. Implementera programmet och gå sedan vidare till
själva uppgiften, som är beskriven efteråt.

## Fem små program

### Gissa talet (enkel)

Skriv ett gissa talet-spel för två spelare. När programmet startar
frågar det efter ett tal. Detta matas in av spelare 1 medan
spelare 2 tittar bort. När spelare 1 har matat in talet får
spelare 2 gissa vilket tal spelare 1 matade in. Spelet svarar med
"För litet!", "För stort!" eller "Mitt i prick!". När rätt tal
matats in anges också hur många gissningar som krävdes för att
hitta rätt innan spelet avslutas. Vid 10 felaktiga gissningar
avslutas spelet och "Du förlorar!" skrivs ut.

En frivillig utökning av detta spel är att Spelare 1 ersätts av
datorn som slumpar fram ett tal mellan givna intervall som kan
vara konstanter i koden eller ges som kommandoradsargument.


### Frekvenstabell för vokaler i en text (enkel)

Vokalerna i det engelska språket är "aoueiy". Skriv ett program
som läser in en fil tecken för tecken och räknar förekomsterna av
varje vokal. När filen är processerad skall en frekvenstabell
skriva ut, t.ex.:

```
a    15
o    9
u    3
e    25
i    8
y    2
```

Ovanstående siffor stämmer för ovanstående paragraf och tabellen
och kan användas som ett test.

En frivillig utökning av uppgiften är att sortera tabellen i
fallande frekvensordning.


### Begränsad storlek på omdirigering av utdata (medelsvår)

Som [tidigare tagits upp](../io) kan man I UNIX omdirigera in- och
utdata med hjälp av operatorerna `<` och `>`.

Ett problem vid tidigare års kurser har varit när studenter
dirigerat utdata från ett program med en oändlig loop till en fil
på sitt konto och sedan blivit utloggade på grund av att de
överskridit sin kvota. En enkel lösning på detta är att skriva
programmet `cap` som läser från standard in tecken för tecken
och skriver allt den läser till standard out, upp till en viss
gräns, som kan vara en konstant i programmet t.ex. en megabyte
(`1024 * 1024` tecken), eller hellre ett kommandoradsargument.


### Sortering av värden i en array (medelsvår)

Skriv ett program som läser in positiva heltalsvärden från en
radorienterad fil, d.v.s. på varje rad i filen finns ett positivt
heltal följt av ett `\n`-tecken. Filens första rad anger hur många
rader som följer. Samtliga tal skall läsas in i en array med lika
många poster som antalet tal. När samtliga tal lästs in skall
arrayen sorteras i stigande ordning.


### N-fakultet (enkel)

Skriv ett program som läser in positiva heltalsvärden från
användaren i terminalen och räknar ut fakulteten. För ett heltal
större än noll är fakulteten lika med produkten av alla heltal
från 1 upp till och med talet självt, d.v.s. fem-fakultet är
`1 * 2 * 3 * 4 * 5 = 120`.


## Uppgiftens andra del

Uppgiftens andra del handlar om kodgranskning. Ni skall nu byta
kod med ett annat par. Ni ger dem en utskrift av er kod och får i
utbyte en utskrift av deras kod .

Om man sitter i en labbsal är det enkelt att fråga runt efter
andra, men annars finns det en diskussion om detta i Piazza just
med syftet att koppla ihop par.

Er uppgift är nu att läsa denna tillbytta kod och utföra en
**kodgranskning**. Kodgranskning är en viktig del av
programutveckling som hittar och rättar fel i programkod.
Kodgranskning är också en aktivitet som bidrar till att göra
granskarna till bättre programmerare, något som framhålls från
många håll både inom akademi och industri. En kompletterande del
av "magin" är att vetskapen att den kod man skriver kommer att
granskas -- detta leder till att koden man skriver blir bättre
från början.

Normalt är att granska ca 150 rader kod per timme och att inte
granska mer än 2 timmar per dag. Mer än 150 rader kod/timme är
ofta för snabbt för att hitta fel, och för lång tid leder ofta
till slarv p.g.a. "kodblindhet".

När ni är klara med er kodgranskning (ca 1 timme) skall ni byta
kommentarer med varandra och gå igenom dem tillsammans.

Nedan finns en checklista med frågor som ni skall särskilt beakta
under denna kodgranskning? (En sådan lista kallas för ett
kodgranskningsprotokoll. Det finns många varianter och vissa för
specifika programspråk. Detta är ett förenklat protokoll för denna
tidiga del av kursen. Det är lika viktigt att förstå frågorna som
att förstå koden man skall besvara dem för.)

* Har hela programmet implementerats?
* Är koden välstrukturerad och konsekvent formatterad?
* Finns det död kod? (T.ex. funktioner som aldrig anropas eller
  kod som aldrig kan nås.)
* Finns det upprepningar som skulle kunna bryta ut och läggas i
  separata funktioner?
* Har alla variabler namngivits på ett vettigt, tydligt och
  konsekvent sätt?
* Finns det överflödiga (redundanta eller oanvända) variabler?
* Är alla loopar, villkorssatser och andra logiska konstruktioner
  kompletta och korrekta?
* Prövas det mest sannolika fallet först i alla villkorssatser?
* Är det tydligt att alla loopar alltid terminerar?
* Deklareras och initieras temporära variabler i anslutning till
  den kod där de används?


### Reflektion

I samband med att ni jämför kommentarer, diskutera också
aktiviteten kodgranskning. Fundera över: ditt eget och andras ego,
hur ger man kritik, varför detta används i verkligheten i
industrin, vad läsbarhet är med avseende på kod, samt om ni tror
att sättet ni kodar på påverkas av det faktum att någon annan
skall kunna läsa koden?
