Enkelt lagerhanteringssystem
============================

Denna uppgift går ut på att skriva ett enkelt
lagerhanteringssystem med ett interaktivt användargränssnitt i
terminalen. Det kommer att ta många timmar att skriva färdigt.
Senare under kursen kommer du att få möjlighet att *utöka* detta
program med nya funktioner.

**TIPS!** Ta fram anteckningspapper och penna. Den här
  specifikationen är lång och det kommer att löna sig att ta
  anteckningar om vad du skall göra. Det ingår alltså i problemet
  som du skall lösa att *förstå problemet*. Notera att
  lektion 1 handlar om att komma igång med uppgiften.
  Denna lektion förutsätter att du har gått igenom uppgiftstexten
  ordentligt.

**TIPS!** Efter att du har läst igenom denna uppgift kan du också
  titta på sidan om [simple](http://wrigstad.com/ioopm/simple.php)
  som tar denna uppgift som ett löpande exempel på hur man griper
  an ett programmeringsproblem. En work breakdown i olika tasks
  (inkomplett, som inspiration!) finns i [vår Trello](https://trello.com/ioopm).

Systemet skall hålla reda på en "databas" med varor. När
programmet startar går det in i den såkallade "main-loopen" där
användaren får ett antal alternativ:

* Lägga till en vara
* Ta bort en vara
* Redigera en vara
* Ångra senaste ändringen
* Lista hela varukatalogen
* Avsluta

Main-loopen skriver ut alternativen och frågar vad användaren vill
göra. De olika valen tar användaren ned i olika funktioner (se
nedan) med eget beteende. Efter att sådana funktioner har
avslutats återvänder de till huvudloopen igen. Detta förfarande
fortsätter tills användaren väljer att avsluta programmet.
Exempel:

    Välkommen till lagerhantering 1.0
    =================================

    [L]ägga till en vara
    [T]a bort en vara
    [R]edigera en vara
    Ån[g]ra senaste ändringen
    Lista [h]ela varukatalogen
    [A]vsluta

    Vad vill du göra idag? _

De bokstäver som användaren skall trycka för att välja ett
alternativ står inom klamrar. Stor eller liten bokstav spelar
ingen roll.

Du får gärna ändra på alla kommandon och skriva programmet på
engelska om du vill. Det viktiga är inte att det fungerar *exakt*
med dessa tecken etc., bara att det är uppenbart för användaren
hur systemet fungerar.

En kort film som visar interaktionen med ett liknande
(opolerat) lagerhanteringssystem finns [här](http://wrigstad.com/ioopm/images/lager.gif).


## Generellt för uppgiften

### Hantering av felaktig inmatning

Vid felaktig inmatning skall programmet inte krascha, utan
istället skall användaren få ett felmeddelande och den aktuella
frågan skall ställas igen. Exempel:

    Mata in nytt pris: asdf
    Felaktig inmatning: 'asdf'
    Mata in nytt pris: tusen
    Felaktig inmatning: 'tusen'
    Mata in nytt pris: 1000

**TIPS!** Hantering av felaktig inmatning är ett bra exempel på
  något som man kan *ducka* (se
  [simple](http://wrigstad.com/ioopm/simple.php)) vid en första
  implementation.


### Vara

En vara har ett **namn**, en **beskrivning**, ett **pris** och en
**lagerhylla** som avser platsen där den är lagrad.

* Namn och beskrivning skall vara en sträng (`char *`)
* Pris skall vara i ören och är därför ett heltal (`int`)
* Lagerhylla skall vara en bokstav åtföljd av en eller flera
  siffror t.ex. *A25* men inte *A 25* eller *25A*

Utöver denna information skall vi också hålla reda på **antalet**
varor av denna typ som är lagrad på den aktuella hyllplatsen.


## Lägga till en vara

Programmet skall fråga användaren efter all den information som en
vara innehåller (se ovan). Om något värde matas in felaktigt
(t.ex. priset var "tusen" och inte "1000") skall ett felmeddelande
skrivas ut och användaren får mata in värdet igen tills det blir
rätt. När samtliga värden matats in skall användaren få en
listning av varan och måste sedan svara på frågan om varan skall
läggas in i databasen eller inte. Svarsalternativen är *Ja*, *Nej*
och *Redigera*. *Ja* lägger till varan, *Nej* avbryter
tilläggningen, och *Redigera* ger möjlighet att redigera
informationen, lämpligen på samma sätt som **Redigera en vara** nedan.

Varje post i databasen avser en unik lagringsplats. Det går därför
bra att t.ex. lagra hushållspapper både på lagerhylla A25 och B12.
Däremot är det **inte** tillåtet att lagra två *olika* varor på
*samma* lagerhylla, dvs. om det redan finns hushållspapper på A25
får vi inte också lägga kritor på A25. Ett försök att lägga till
en vara där en annan redan finns sparad skall ge upphov till ett
felmeddelande. Det skall heller inte gå att skapa en sådan
situation genom att redigera en vara.


## Visa en vara

Först listas samtliga varors namn med indexnummer:

    1 Hushållspapper
    2 Kritor
    3 Målarfärg

Användaren erbjuds sedan att mata in numret på den vara som hen
vill se, alternativt trycka `a` för avbryta och återgå till
huvudmenyn. Om det finns fler än 20 varor ges också alternativet
att se fler varor. Då visas nästa 20 varor inderade från 1.

Den valda varan listas på skärmen så här:

    Namn: Hushållspapper
    Beskrivning: Tvålagerspapper med perforering. Varje pappersremsa
    har en liten bild av två blåmusslor som försiktigt vänslas.
    Pris: 20 kr
    Lagerhylla: A25
    Antal: 12

## Redigera en vara

Vara väljs på samma sätt som *Visa en vara*.

När användaren väljer en vara skall varas visas på skärmen.
Användaren får sedan frågan vilken *rad* som skall redigeras:

    [N]amn
    [B]eskrivning
    [P]ris
    [L]agerhylla
    An[t]al

    Välj rad eller [a]vbryt: _

Om användaren matar in t.ex. `p` skall först det gamla priset
skrivas ut och direkt efteråt visas en input för det nya priset:

    Nuvarande pris: 20 kr
    --------------------------------------------------------
    Nytt pris: _


## Ta bort en vara

Vara väljs på samma sätt som *Visa en vara*.

När användaren väljer en vara skall varan visas på skärmen.
Användaren får sedan frågan om hen är säker på att varan skall tas
bort:

    1 Hushållspapper
    2 Kritor
    3 Målarfärg

    Ta bort 1-3 eller [a]vbryt: 1

    Namn: Hushållspapper
    Beskrivning: Tvålagerspapper med perforering. Varje pappersremsa
    har en liten bild av två blåmusslor som försiktigt vänslas.
    Pris: 20 kr
    Lagerhylla: A25
    Antal: 12

    Ta bort varan? Ja/Nej: _

## Lista hela varukatalogen

Varukatalogen listas ~~i bokstavsordning~~, max 20 varor åt gången:

    1 Hushållspapper
    2 Kritor
    3 Målarfärg

Varje "sida" i listningen rymmer 20 varor. Om det finns fler än 20
varor ges alternativet att se fler varor. Varje vara ges ett
index, som alltid är mellan 1 och 20 och som börjar om på 1 varje
sida.

Ingen detaljinformation om varje vara visas.

## Ångra senaste ändringen

Alla ändringar skall gå att ångra. Det räcker med ångra ett steg
och man kan inte "ångra ett ångrande" eller ångra det första som
händer i programmet. I både dessa fall skall meddelandet "Det
finns inget att ångra" skrivas ut.

Ett sätt att implementera detta är att för varje händelse med
sidoeffekter (add, remove, edit) spara data som kan återställa
databasen. Så här såg denna datastruktur ut i min implementation
av uppgiften.

```c
struct action_t
{
  enum { NOTHING, ADD, REMOVE, EDIT } type;
  union
  {
    struct { goods_s saved; };      // REMOVE
    struct { goods_s *edited; goods_s original; }; // EDIT
  };
};
```

Här använder jag både `enum`- och `union`-begreppen i C, vilket
kanske är lite tidigt i kursen för de flesta. En enklare variant
är denna:

```c
struct action_t
{
  int type; // NOTHING = 0, ADD = 1, REMOVE = 2, EDIT = 3
  goods_s *merch;
  goods_s copy;
};
```

Här används `type == 1` för tillägg, `type == 2` för borttag etc.

Varje gång användaren gör något i main-loopen sparar vi
information så att vi kan ångra. Det räcker med en enda variabel
`undo` av typen `struct action_t`.

Vid tillägg används `merch` för att peka ut vilket värde som lagts
till och `copy` används ej.

Vid borttagning sparas det gamla värdet i `copy` och `merch`
används ej.

Vid edit sparas det gamla värdet i `copy` och `merch` används för
att peka ut det modifierade värdet i databasen.

Om användaren väljer att ångra kan vi se i `undo` vilken typ av
händelse som skall ångras (från `undo.type`). Om vi behöver
återskapa information kan vi titta i `undo.copy`. För att veta vad
som lagts till eller ändrats kan vi använda pekaren i
`undo.merch`.


# Implementation

Här följer några tips för implementationen.

* Ett bra sätt att implementera ett program är att göra det i
  olika diskreta steg, "inkrement", där varje steg för någon eller
  några delar av implementationen framåt.
* En strukt `goods` är en central datatyp vars definition går att
  extrahera ur ovanstående.
* I denna sprint duger det utmärkt att använda en array av `goods`
  med en given max-storlek, t.ex. 100, för att spara programmets
  data. I en senare sprint kan man tänka sig att man använder en
  dynamiskt växande struktur istället.
* Det är lämpligt att ha en funktion per alternativ i huvudloopen
  och som ställer alla relevanta underfrågor. Vi kallar dessa för
  gränssnittsfunktioner och de kan vara till exempel:
  - `add_goods` -- lägga till vara
  - `remove_goods` -- ta bort vara
  - `edit_goods` -- redigera vara
  - `list_goods` -- lista hela varukatalogen
  - `display_goods` -- visa en specifik vara
  - `undo_action` -- ångra
  - `exit_program` -- avsluta programmet
* Blanda inte *gränssnittslogik* med *varulogik*, dvs. `add_goods`
  huvuduppgift är att visa alternativ för användaren, och ställa
  frågor i rätt ordning, etc. -- men all logik för att visa varor,
  kolla vad som är lagrat på en specifik lagerhylla, etc. sker i
  specika funktioner, som förmodligen kommer att användas av flera
  gränssnittsfunktioner. (I ett senare skede i programmets
  utveckling skulle vi förmodligen separera gränssnittslogik och
  varulogik i två olika moduler.)
* Återkommande uppgifter bör brytas ut och läggas i separata
  funktioner. Ett typiskt sådant standard-mönster som programmet
  upprepar är att ställa en fråga tills ett lämpligt svar har
  tagits emot. För enkelhets skull kan vi implementera flera
  frågor för olika typer av förväntat indata. (I ett senare skede
  i utvecklingen kanske vi skulle slå samman dem till en enda och
  mer flexibel funktion.) Till exempel:
  - `ask_question_string` -- förväntar sig svar i form av hela
    strängar (t.ex. namn på vara eller beskrivning av vara)
  - `ask_question_int` -- förväntar sig ett svar i form av ett
    heltal (t.ex. priset på en vara)
  - `ask_question_char` -- förväntar sig ett svar i form av ett
    enskilt tecken (t.ex. ett alternativ som användaren
    presenteras för)
* Ytterligare ett exempel på ett lämpligt beteende som bör ges en
  egen funktion är att skriva ut en vara på terminalen,
  `print_goods`, något som sker flera gånger i olika skeden av
  programmet.
* Både `add_goods` och `edit_goods` kommer att behöva en funktion
  som kontrollerar *vad* som lagrat på en specifik lagerhylla, för
  att uppfylla kravet att enbart en vara finns per
  lagerhyllsplats. Till exempel funktionen
  `get_goods_for_storage_location`.


## Ett par lämpliga första steg

Se [simple](http://wrigstad.com/ioopm/simple.php) för en mer
detaljerad diskussion.

1. Börja med att skriva `ask_question_char` och använd den för att
   implementera programmets huvudloop. På detta vis har du alltid
   ett program som går att köra och det underlättar både
   utveckling och testning.
2. Definiera `goods`-strukten. Skriv en funktion som lägger till
   några exempelvaror i databasen genom att direkt skriva till den
   array (eller motsvarande) som håller datat. Detta vill vi göra
   för att nästa två steg skall kännas meningsfulla och gå att
   testa.
3. Implementera `display_goods` vilket kommer att leda till att du
   måste implementera flera hjälpfunktioner, t.ex. `print_goods`.
4. Implementera `list_goods`.
5. Fortsätt med `edit_goods`. För denna funktion behövs
   `get_goods_for_storage_location` så att du kan kontrollera att
   lagringsplatserna för varje vara är unika.
6. Nu borde du kunna implementera `add_goods` tämligen enkelt och
   mestadels förlita dig på de hjälpfunktioner du redan har.


## Att läsa in indata från användaren

Att läsa in indata från användaren är knepigt. Ett problem är hur
inbufferten fungerar. Användaren matar in text i bufferten, och
först vid *enter* blir den synlig för programmet. Det betyder att
även om du bara vill att användaren skall läsa in ett tecken
kommer användaren att behöva mata in en hel sträng, och när du har
tagit det första tecknet som du vill ha, **måste du tömma**
inbufferten så att allt skräpdata försvinner! Ponera följande
ofullständiga funktion:

```c
// Notera den tomma definitionen av Clear_stdin!
#define Clear_stdin

char ask_question_char(char *q, char *alt)
{
  char input = 0;

  printf("%s [%s]\n", q, alt);
  do {
    if (input)
      {
        printf("Bad input '%c', try again [%s]\n", input, alt);
        Clear_stdin;
      }

    input = getchar();
  } while (strchr(alt, input) == NULL);

  Clear_stdin;
  return input;
}
```

Här är `q` den fråga som ställs användren och `alt` är en sträng
av tillåtna tecken i svaret. Funktionen `getchar` läser ett tecken
från inbufferten (gör `man getchar` i terminalen för mer
information). Funktionen `strchr` söker genom `alt`-strängen efter
tecknet i `input` och returnerar `NULL` om det inte fanns. Det
använder vi som test för att komma ur loopen. Funktionen loopar
tills användaren har svarat något av tecknen i `alt`. Ponera att
vi använde funktionen så här:

```c
bool to_be_sure_to_be_sure()
{
  bool sure = ask_question_char("Are you sure?", "YyNn");

  if (!sure) return false;

  return ask_question_char("Are you REALLY sure?", "YyNn");
}
```

Förvånansvärt nog skulle det här bli resultatet i ett program om
vi försökte svara ja:

```
Are you sure? [YyNn]
y                           <-- här skriver jag 'y' och trycker enter
Are you REALLY sure? [YyNn]
Bad input '                 <-- det här händer "av sig självt"!
', try again [YyNn]
_
```

Anledningen till detta är att för att få in "y" i programmet måste
vi skriva "y" *enter* vilket resulterar i strängen `"y\n"`. Första
frågan får `'y'` och nästa fråga fortsätter att läsa från
bufferten och får därför `'\n'`.

Lösningen är att **tömma bufferten** efter varje inläsning. Det
gör man genom att läsa in alla tecken tills man kommer till ett
`'\n'`. Definiera `Clear_input` som en loop som gör detta så har
du fått en fungerande `ask_question_char`. Så här kan du göra:

```c
while (getchar() != '\n') ;
```

Detta anropar `getchar()` som läser från inbufferten, tills dess
att `'\n'`-tecknet lästs in. `Clear_stdin` är ett makro (tas upp
senare på kursen, föreläsning 9). För att få funktionen att
fungera kan du göra så här:

```c
#define Clear_stdin while (getchar() != '\n') ;
```

# Tio möjliga utökningar

För dig som vill sitta och pilla med uppgiften och vill göra mer.
(Eller vill göra en utökning för att redovisa fler mål.)

1. Stöd för att ångra flera steg.
2. Hitta dyraste respektive billigaste varan.
3. Skriv ut försäkringsvärdet, dvs. totalsumman av pris x antal
   för alla varor.
4. Omorganisera lagret genom att slå samman alla varor av samma
   typ och lägga dem på samma hyllplats.
5. Möjlighet att välja sorteringsordning vid utskrift av varor
   (bokstavsordning angivet ovan, men man kan tänka sig hyllplats,
   pris stigande, pris fallande, etc.).
6. Söka efter en viss vara och få ut alla hyllplatser där den finns.
7. Stöd för att lägga varor i olika kvantiteter i en "korg" vars
   kostnad skall visas vid varje interaktion med användaren; det
   skall vara möjligt att lägga varor i korgen, ta bort dem ur
   korgen (då hamnar de på hyllan igen), och tömma korgen.
8. Stöd för storlekar. Varje hyllplats rymmer bara ett visst antal
   kubikcentimeter och varubegreppet utökas med en storlek i
   kubikcentimeter. Se till att varorna får plats genom att tvinga
   användaren att bryta upp stora varukvantiteter över flera
   hyllplatser.
9. Stöd för kompaktering, dvs. omorganisera lagret så att en vara
   är lagrad på angränsande hyllplatser.
10. Skriv enhetstester för dina funktioner (detta kommer som ett
    krav i näst-nästa utökning).


# Förslag på mål att redovisa

Du använder uppgiften till att redovisa mål -- när du redovisar
ett mål skall det finnas en tydlig koppling till uppgiften eller
någon föreslagen utökning till uppgiften. Det ingår i uppgiften
(eller egentligen i hela kursupplägget) att förstå mappningen från
uppgift (eller del av uppgift) till lämpliga mål. Vi ger förslag
-- färre och färre ju längre in i kursen vi kommer. Notera att det
inte räcker med att bara följa förslagen för att bli godkänd.

1. [Inluppsmål 1](http://auportal.herokuapp.com/achievements/100)
2. [G15](http://auportal.herokuapp.com/achievements/15) -- ett måste vid inläsning med hjälp av en buffert. Vad kan hända annars?
3. [H20](http://auportal.herokuapp.com/achievements/20) -- vad är det för skillnad på att skicka in/returnera ett heltal respektive en sträng till/från en funktion? Kan relateras till ovanstående mål.
4. [M36](http://auportal.herokuapp.com/achievements/36) -- vid interaktion eller iteration över databasen, t.ex.
5. [W57](http://auportal.herokuapp.com/achievements/57) -- speciellt om du delar upp programmet i flera filer
6. [A1](http://auportal.herokuapp.com/achievements/1) -- genomgående inslag i denna uppgift
7. Börja på [C7](http://auportal.herokuapp.com/achievements/7) -- du vill inte behöva efterskapa saker sedan (**Du kan alltså inte redovisa detta redan nu.**)
