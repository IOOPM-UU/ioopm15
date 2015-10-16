# Lektionsmaterial om testning, 2015-10-08

**OBS** Under lektionen går vi igenom testning
av mängden, dvs. det högsta abstraktionslagret.
För den som vill finns även det underliggande
trädet här att gå vidare med. 

## Introduktion 

Uppgiften går ut på att ta fram testfall för det
program som vi skrev på föreläsning 12. Det är alltså
inte egentligen ett program, utan ett bibliotek för att
hantera mängder av heltal som är byggt ovanå en
trädstruktur. En lämplig övning på kammaren är att
också skriva testerna och se om programmet har fel
eller inte, men under lektionen skall vi fokusera på
att ta fram testfallen och prata om hur vi skall
testa. En lämplig nivå på ett svar kan vara:

"Först skapar vi en ny mängd med fem element i ordningen

```
3
2
1
5
7
```

vilket det interna trädet borde representera som

```
       3
      / \
     2   5
    /     \
   1       7
```

sedan kollar vi att djupet är 3 och storleken 5."  (Det
är för övrigt förmodligen inte ett bra test -- svårt
att säga eftersom vi inte har sett frågan, bara svaret
--- såvida vi inte också kollar att storleken är 0, 1,
etc. och djupet växer som vi förväntar oss. Helst då
med 3, 2, 5, 1, 7.)

**Minns** att det är speciellt intressant att testa
*gränsfall*, t.ex. när vi går från en tom mängd till en
icke-tom, från en icke-tom, till en tom, insättning av
dubletter, etc.


## Testuppgift

Vi vill testa korrektheten för både mängden och dess
underliggande implementation -- ett binärt träd. Vi
fokuserar på *enhetstestning*, vilket betyder att vi
vill testa varje funktion i isolation så långt det är
möjligt. Med detta menas alltså att vi skall undvika
att ``spara tid'' genom att testa borttagning och
insättning i samma test, eftersom det gör att vi måste
söka i en betydligt större mängd kod för att hitta
felen när testen fallerar.

Låt oss börja top-down, dvs. genom att testa själva
domänen. Då vill vi skriva tester som prövar att
mängden är korrekt implementerad. Vad vi vill pröva är
alltså de funktioner som finns i `set.h`:

```c
// Skapa en ny, tom mängd
set_t *set_new();
// Utöka mängden s med ett nytt element
// Om value redan finns i s händer ingenting
void set_add(set_t *s, int value);
// Returnerar true om value finns i s, annars false
bool set_contains(set_t *s, int value);
// Returnernar en ny mängd som är unionen av s1 och s2
set_t *set_union(set_t *s1, set_t *s2);
// Returnernar en ny mängd som är snittet av s1 och s2
set_t *set_intersection(set_t *s1, set_t *s2);
// Returnernar en ny mängd som är s1 minus s2
set_t *set_subtraction(set_t *s1, set_t *s2);
// Returnerar true om mängderna är lika stora och har samma element
bool set_equal(set_t *s1, set_t *s2);
// Returnerar antalet element i s
int set_size(set_t *s);
// Behöver ej testas -- är med i koden för din debugging
void set_print(set_t *s);
// Behöver ej testas -- se nedan
void set_free(set_t *s);
```

För enkelhets skull testar vi inte `set_free` eftersom
det är väldigt invecklat att kontrollera minnesanvändning.
Vi hänvisar istället till att köra `valgrind` på
testfall för `set_free` och kontrollera att inga
minnesläckage finns.

Nästa steg (utanför lektionstid, frivillig övning) är att testa
det träd som implementerar mängden, alltså `tree.h`:

```c
// Skapar en ny lövnod med värdet value
node_t *node_new(int value);
// Lägger in en ny nod i trädet på rätt plats (ignorerar dubletter)
void node_add(node_t **n, int value);
// Returnerar true om det finns en nod med värdet value i trädet rotat i *n, annars false
bool node_contains(node_t **n, int value);
// Besöker alla noder i trädet i ordning och utför f på dess värden med arg1 och arg2 som argument
void node_forall(node_t *n, action_f f, void *arg1, void *arg2);
// Nedanstående behöver ej testas untan kan antas vara korrekta
// Letar upp en nod i trädet (ignorera denna) 
node_t **node_find(node_t **n, int value);
// Returnerar antalet noder i trädet (0 om n == NULL)
int node_size(node_t *n);
// Returnerar djupet på trädet, dvs. längsta kjedjan från roten till ett löv (0 om n == NULL)
int node_depth(node_t *n);
```


# Domänkunskap: Elementär mängdlära:

En mängd är en oordnad samling unika element (dvs. utan dubletter).

{} är tomma mängden
{1} är en mängd med ett element
{1,2,1} är inte en valid mängd eftersom det finns dubletter

Unionen av två mängder A och B är en ny mängd som
innehåller alla element i A och alla element i B.

Exempel: A = {1,2,3}, B = {3, 4, 5}

```
A union B  = {1, 2, 3, 4, 5}
A union A  = A
A union {} = A
```

Snittet av två mängder A och B skrivs är en ny mängd
som innehåller de element som finns i både A och B.

Exempel: A = {1,2,3}, B = {3, 4, 5}

```
A snitt B  = {3}
B snitt A  = {3}
A snitt A  = A
A snitt {} = {}
```

Subtraktion mellan mängder skrivs med \. A \ B, alltså
A minut B, definieras som en ny mängd med alla element
i A som inte också är element i B. 

Exempel: A = {1,2,3}, B = {3, 4, 5}

```
A \ B  = {1, 2}
B \ A  = {4, 5}
A \ A  = {}
A \ {} = A
```


# För att komma åt filerna

## Steg 1: Ladda ned materialet vi skall jobba med

```
$ git clone https://XXX
```

## Steg 2: Bygg programmet

```
$ make all
```

Detta bygger programmet, testerna, och länkar.

## Steg 3: Kör testerna

```
$ make test
```

Detta kör programmet och visar samtidigt att
testerna ännu inte är implementerade.
