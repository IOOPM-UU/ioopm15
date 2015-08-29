Inlupp 2.a: Utökat lagerhanteringssystem
========================================

Nu skall vi förbättra lagerhanteringssystemet. Vi skall lägga till
några features, men främst jobba på de interna datastrukturerna
och kodkvaliteten. Framförallt skall vi använda dynamiskt
allokerat minne (F5 och F7). I korthet:

1. Vi kommer att använda oss både av ett binärt sökträd och en länkad
lista för att hantera datat.
2. Lagerhanteraren utökas med ett "shoppingläge" där användaren kan
packa en pall (varukorg) med en eller flera varor, och
få utskrivet:

  * Den totala summan av varorna i korgen
  * När varorna finns inne
  * Vilka lagerplatser som måste besökas för att hämta varorna

3. Programmet skall delas upp i lämpliga moduler
4. Koden skall dokumenteras och repetition och namngivning beaktas särskilt

## Packa en pall

Användaren kan accessa shoppingläget från huvudmenyn

    Välkommen till lagerhantering 2.0
    =================================

    [L]ägga till en vara
    [T]a bort en vara
    [R]edigera en vara
    Ån[g]ra senaste ändringen
    Lista [h]ela varukatalogen
    [P]acka en pall  <------------
    [A]vsluta

    Vad vill du göra idag? _

Användaren skall nu få en listning av varukatalogen och får väja
en vara att packa på pallen, följt av en kvantitet. T.ex.

    Din pall är tom

    Varor i databasen:

    1 Hushållspapper
    2 Kritor
    3 Målarfärg

    Välj vara att packa på pallen: <2>

    Namn: Kritor
    Antal: 25

    Välj antal (0--25): <14>

    Vill du packa en till vara? (j/n) _

Efter varje vald vara får användaren frågan om hen vill packa en
till vara. Så länge svaret är ja återvänder programmet till
listningen ovan, men beskrivningen av varukorgen uppdateras:

    Din pall innehåller:
      - Kritor (14)

    Varor i databasen:

    1 Hushållspapper
    2 Kritor
    3 Målarfärg

    Välj vara att packa på pallen: _

Det går att lägga samma vara i korgen flera gånger som då adderas
till den existerande mängden. Alltså, om ytterligare 5 kritor köps
blir det 19 kritor i varukogen ovan. Köp av 0 enheter av en vara
skall inte registreras.

När man väljer att inte packa fler varor skall pallen listas på
skärmen:

    Din pall:

    1. Kritor (19)
    2. Hushållspapper (1)
    3. Minecraftsvärd (600)

    Totalt pris för pallen: 601.190 kr

    Lagerplatser för att packa pallen:
    A25 (1 Hushållspapper)
    B1 (19 Kritor)
    C9 (311 Minecraftsvärd)
    C11 (289 Minecraftsvärd)

Notera att de 600 svärden inte fanns lagrade på samma plats utan
kommer från två olika lagerplatser. Hur du väljer att implementera
hur en pall packas med varor från olika lagerplatser är fritt så
länge du minimerar antalet platser att hämta från. Ett enkelt sätt
att göra detta är att hitta alla platser där varan är lagrade och
plocka från dem i fallande antalsordning.

Exempel: om det finns svärd på fyra platser, A (100 svärd), B (200
svärd), C (350 svärd) och D (250 svärd) och du skall plocka 600,
plocka i ordning från C, D, B, A. I detta fall behöver du bara
plocka från C och D för att nå 600. Om du hade plockat i ordningen
A, B, D, C hade du behövt plocka från samtliga platser för att nå
600. I en verklig situation hade man kanske beaktat andra
aspekter, som avstånd mellan lagerplatser, etc.


# Förändring av databasformatet

Nu beskriver vi en intern förändring som inte kommer att vara
synlig för användaren, men är nog så viktig: användning av
dynamiska, länkade strukturer för att hantera programmets minne.

I föregående sprinten använde vi en statisk array av `goods` för
att hålla programmets data. Det duger förstås inte i ett riktigt
program eftersom det

1. kräver att vi har ett hårt maxtak på *n* antal varor i
   systemet, och
2. medför att systemet använder minne för *n* antal varor, oavsett
   hur många som faktiskt finns.

I denna uppgift skall vi ändra i lagerprogrammet så att dessa två
problem försvinner. Vi kommer att göra det genom att först skriva
två helt nya delar av programmet för att hantera en dynamisk lista
av lagerplatser samt ett binärt sökträd av varor (båda dessa togs
upp på PKD). Sedan skall vi ändra i det gamla programmet så att
det använder dem. Vi ställer följande krav på den nya
datastrukturen som skall hålla i programmets databas:

1. Det skall inte finnas något hårt maxtak på antalet varor i
   systemet (förutom vad som ryms i det lediga minnet).
2. Sökning efter varor skall ske i O(log n) tid (**OBS!** du
   behöver *inte* balansera trädet).
3. Systemet skall inte använda minne för varor som inte finns (och
   frigöra minne för varor som tas bort), likaså för lagerplatser.

Ett utkast till gränssnittet (alltså listan av funktioner som en
klient kan använda) för träd och lista finns [här](list.h) och
[här](tree.h).

**TIPS!** Fundera över vad som är en lämplig moduluppdelning för
programmet så att relaterade funktioner grupperas och
icke-relaterade funktioner inte blandas med varandra.

**TIPS!** Fundera över inkapsling. Vad behöver vara synligt för
programmet? Behöver programmet t.ex. veta något om listorna som
finns sparade i varje nod i trädet?

Sammanfattningsvis:

* Nycklarna i sökträdet är varunamn
* Varor med samma namn anses vara identiska
* Varje vara har informationen från föregående uppgift, och
  dessutom en pekare till en lista med lagerplatser där varan
  finns lagrad
* Listan med lagerplatser innehåller information om vilken
  kvantitet av varan som finns på platsen

För att ett binärt sökträd skall vara korrekt med avseende på
sortering av dess index är det viktigt att det inte går att
modifiera dess nycklar från en annan plats i programmet. Vi
använder varornas namn i detta program -- varje namn representeras
alltså som en array av tecken. Om man ändrar innehållet i en array
`A` från t.ex. `"Anrikare av uran"` till `"Öljetter"` och `A`
används som en nyckel i det binära trädet T har man förmodligen
just förstört `T` så tillvida att man inte kan nå öljetterna i
trädet längre (varför?). Ännu värre: vad händer om någon gör
`free(A)` fast `A` fortfarande används av trädet?

För att skydda sig mot denna typ av beteende krävs att nycklarna i
trädet inte är åtkomliga utanför trädet. Det går t.ex. att lösa
genom att skapa en kopia av alla nycklar inuti trädet. Glöm inte
bort att frigöra allt minne som allokeras!


## Förändringar i funktionen för att lägga till en vara

I föregående uppgift kunde en vara vara lagrad flera gånger i
databasen på olika platser. I och med skiftet till ett binärt
sökträd kommer en vara nu enbart finnas lagrad en gång. När man
lägger till en vara fler än en gång manipuleras nu den länkade
listan med lagerplatser.

Exempel: För att lägga till minecraftsvärden på de fyra
lagerplatserna som angavs ovan kan du först lägga till varan på
precis samma sätt som i föregående uppgift. Användaren märker
ingen skillnad men internt sparas svärden i trädet T med en lista
L av lagerplatser vars längd kommer att vara ett (1). Nästa gång
varan läggs till måste systemet se att varan redan finns. Denna
kontroll sker lämpligen efter att namnet matas in genom en sökning
i T. Om varan redan finns behöver vi inte fråga efter beskrivning
eller pris. Istället frågar vi bara om lagerplats och kvantitet
och uppdaterar L med den informationen.

Så här kan man tänka sig att interaktionen med användaren ser ut
(text inom <vinkelparenteser> avser text som användaren matat in).

    Vad vill du göra idag? <L>

    Lägg till vara
    ==============

    Namn: <Minecraftsvärd>

    Minecraftsvärd finns redan i databasen.
    Använder samma pris och beskrivning.

    Lagerplats: <C12>
    Antal: <350>


Om samma lagerplats används flera gånger aggregeras varorna på
denna plats.


## Förändringar i funktionen för att ta bort en vara

När man tar bort en vara tar man endast bort en enskild lagerplats
för varan. När samtliga lagerplatser för en vara har tagits bort
skall också varan tas bort ur trädet.

Exempel:

    Vad vill du göra idag? <T>

    Ta bort vara
    ============

    1. Kritor
    2. Hushållspapper
    3. Minecraftsvärd

    Välj vara att ta bort: <3>

    Minecraftsvärd finns lagrat på följande platser:

    1. A88 (100 stycken)
    2. B2 (150 stycken)
    3. C11 (350 stycken)

    Vilken plats skall tas bort (0 för ingen)? <3>


## Ångra

Det är frivilligt (se utökning 9) att implementera stöd för att
ångra funktionerna ovan. Valet ångra skall dock bara finnas
synligt om det finns något att ångra/går att ångra något.


## Tips: omdirigering av stdin för att testa programmet

I UNIX-miljö kan indata till ett program komma från en textfil.
När programmet körs läses svaren till programmets frågor från en
fil istället för att matas in för hand. Detta kommer att vara
nyttigt för att testa ditt program i denna uppgift eftersom det
kommer att krävas många inmatningar för att fylla programmet med
intressant data.

Du kan t.ex. pröva att styra en minimal interaktion med programmet
så här:

1. Skapa en fil `test.txt` med innehållet `q` och en radbrytning.
   (`q` för att avsluta programmet -- byt till annat tecken om du
   gjort ändringar.)
2. Kör programmet så här: `./myprog < test.txt` där `myprog` är
   det kompilerade programmet.

Nu kan du pröva att ändra i `test.txt`. T.ex. så här:

```
L
Kritor
Vita kritor
20
C4
h
q
```

Detta skall lägga till en vara (kritor), lista hela varukatalogen,
och sedan avsluta. (Notera att ditt program kanske tar emot indata
i en annan ordning!)


## Namngivning och refaktorering

När du skrev den förra lagerhanteraren var ditt fokus kanske på
att få programmet att fungera. Det är lika viktigt att programmet
fungerar som att det är **läsbart** och **förändringsbart**.

Gå igenom ditt program och titta på alla namn. Vad heter
funktioner? De bör ha namn som förklarar vad de gör t.ex.
`save_product_to_db` eller `ask_yes_no_question`. Detsamma gäller
för variabler! Variabelnamnet `amount` är mindre informativt än
`number_of_fish` såvida det inte är fullständigt uppenbart från
det kontext där `amount` används att det är antalet *fiskar* som
avses.

En bra tumregel är att ju längre variablernas räckvidd är -- desto
längre namn skall de ha. Globala variabler bör alltså ha långa
namn, och en loopvariabel för ett index in i en array kan heta
`i`.

Sök också igenom ditt program efter repetitioner. Om du ser att
samma följd av instruktioner förekommer flera gånger för att
åstadkomma samma sak men kanske med olika input är det läge att
skapa en funktion för det. Till exempel, om denna kod förekommer
på flera ställen:

```c
int merch_id = ask_selection("Välj vara", db);
bool remove = ask_yes_no_question("Ta bort vara?");
if (remove)
  {
     db_remove(db, merch_id);
  }
```

Kan man tänka sig att skapa funktionen `remove_merch_from_db`:

```c
void remove_merch_from_db(db_t *db)
{
  // koden ovan
}
```

och anropa den. Då blir det enklare att ändra på interaktionen med
databasen eftersom man bara behöver ändra på ett ställe.

Ofta kan det vara så att man använder olika parameterar på olika
platser i koden, t.ex. olika frågesträngar till `ask_selection`.
Då kan de bli extra parametrar till funktionen:

```c
void remove_merch_from_db(db_t *db, char *query, char *conf_query)
{
  int merch_id = ask_selection(query, db);
  bool remove = ask_yes_no_question(conf_query);
  if (remove)
    {
       db_remove(db, merch_id);
    }
}
```


## Koddokumentation

Använd verktyget doxygen för att dokumentera din kod. Du kan börja
med att titta på exempel i headerfilen för den länkade listan.
Målet med koddokumentation är att förklara för en användare av
*koden* (inte programmet) hur den skall användas.

Tänk dig att vi plötsligt skulle byta ut din implementation av
lagerhanteraren mot en annan grupps implementation, som du aldrig
har sett. Förmodligen är många funktioner väldigt lika, men det
finns säkert också stora skillnader. Funktioner som du aldrig har
sett blir betydligt enklare att använda om de har en beskrivande
text och funktioner som du också har, men som skiljer sig litet,
är ännu viktigare att ha dokumentation för eftersom din
förförståelse för hur de fungerar kommer att vara fel.

Dokumentation är med fördel kort för enkla saker och längre för
komplexa saker. För komplexa funktioner kan man t.ex. ha ett
exempel på hur man kan använda den för att göra något.

Tänk på att dokumentation kostar! När programmet ändras måste
dokumentationen också ändras för att fortfarande vara korrekt.
Felaktig dokumentation är en klassisk felkälla.


# Tio möjliga utökningar

För dig som vill sitta och pilla med uppgiften och vill göra mer.
(Eller vill göra en utökning för att redovisa fler mål.)

1. Stöd fär skiftlägesokänslighet vid inmatning av vara. Det vill
   säga, "kritor", "Kritor", "KRITOR" är samma vara.
2. Stöd för att ta bort en vara i ett steg oavsett antal
   lagringsplatser.
3. Möjlighet att låta en vara ligga kvar i systemet utan
   lagringsplatser.
4. Vid inmatning av existerande vara, lista existerande lagerplats
   och kvantitet.
5. Se till att man inte lagrar flera varor av olika typ på samma
   plats.
6. Stöd för att spara pallar. När man väljer att packa en pall får
   man möjlighet att fortsätta packa en sparad pall. Man skall
   kunna ta bort sparade pallar.
7. Balansera binärträdet av varor.
8. Stöd för att byta namn på en vara. Om man byter namn på en vara
   V1 till ett redan existerande namn på en vara V2 skall man få
   frågan om man vill slå ihop posterna. Då flyttas alla
   lagerplatser från V1 till V2 och V1 tas bort ur databasen.
9. Utöka stödet för att ångra till att omfatta alla förändringar
   och utökningar som du har gjort, samt implementera "ångra
   ångra" (aka redo).
10. Skriv enhetstester för dina funktioner (detta kommer som ett
    krav i nästa utökning).


# Förslag på 3-mål att redovisa

1. [Inluppsmål 2](http://auportal.herokuapp.com/achievements/101)
2. [F13](http://auportal.herokuapp.com/achievements/13) -- finns flera lämpliga delar av programmet där man t.ex.
   letar efter data eller räknar ut totalsumman
3. [J26](http://auportal.herokuapp.com/achievements/26) -- vad behöver sparas på heapen, och varför?
4. [D9](http://auportal.herokuapp.com/achievements/9) -- ett direkt krav ovan
7. Fortsätt med [C7](http://auportal.herokuapp.com/achievements/7) -- du vill inte behöva efterskapa saker sedan (**Du kan alltså inte redovisa detta redan nu.**)

# Förslag på 4/5-mål att redovisa

1. [K31](http://auportal.herokuapp.com/achievements/31) -- motivera din modularisering
2. [M39](http://auportal.herokuapp.com/achievements/39) -- vid insättning/uttag ur länkade strukturer
