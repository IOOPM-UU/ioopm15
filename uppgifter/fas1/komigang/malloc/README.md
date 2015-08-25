Förberedande screencasts om C inkluderar sammansatta datatyper,
typer, typomvanling och typedef, samt grundläggande
minneshantering.

Malloc
======

### Stacken är finit / Stacken är bara så djup

Ta reda på hur "djup" stacken är. Det går enkelt att göra genom
att skriva ett program med en funktion som rekursivt anropar sig
själv och skriver ut antalet rekursiva anrop tills det kraschar.
(På grund av s.k. stack overflow -- programmet får inte plats på
stacken.)

``` c
#include<stdio.h>

void checkStackdepth(int depth) {
  printf("Djup: %d\n", depth);
  checkStackdepth(depth+1);
}

int main(void) {
  checkStackdepth(0);
  return 0;
}
```

Pröva att modifiera programmet ovan så att varje rekursivt anrop
till `checkStackdepth` använder mer stackyta. Läs t.ex. på
[Wikipedia](http://en.wikipedia.org/wiki/Stack_overflow) för
ledning om hur man kan göra det. Vad betyder detta i praktiken för
det redan uppmätta stackdjupet?


### Struktar och värdesemantik

En strukt i C är en sammansatt datatyp som används för att
definiera objekt med flera olika beståndsdelar. En strukt kallas
ibland på svenska för "post" och består av noll eller flera
datafält med sinsemellan unika etiketter. Se t.ex.
[Wikipedia](http://en.wikipedia.org/wiki/Struct_(C_programming_language)).

En strukt för att skapa objekt som beskriver punkter i planet
skulle kunna definieras så här:

``` c
  struct point {
    int x;
    int y;
  }
```

Detta deklarerar datatypen `struct point` som kan
användas på efterföljande rader. Variabler av denna typ har två
fält -- `x` och `y` som kan läsas och skrivas individuellt.
Man skulle kunna definiera en variabel `somewhere` så här:

``` c
  struct point somewhere;
  somewhere.x = 7;
  somewhere.y = 3;
```

C stöder en smidigare typ av initiering av sammansatta datatyper
med följande syntax:

``` c
  struct point somewhere = { 7 , 3 };
```

där de initiala värdena tilldelas fälten i deklarationsordning
uppifrån och ned. Detta är bräckligt eftersom en förändring av
deklarationsordningen i `point` kommer att ändra kodens
betydelse utan varken varningar eller fel. Ett bättre sätt är att
istället ange namnen på de fält man vill initiera:

``` c
  struct point somewhere = { .x = 7 , .y = 3 };
```

Kompilera och kör programmet `point-struct.c`. Programmets
avsikt är att flytta en punkt (7,3) relativt en punkt (4,5) så att
den första punkten får koordinaten (11,8) -- men något är fel! Vad?

Felet består i att den punkt `p` som ändras är funktionen
`translate`:s egen **kopia** av den punkt som skickades in,
eftersom struktar överförs med s.k. värdesemantik.

För att lösa problemet kan vi göra två saker: vi kan antingen
skicka tillbaka (en kopia av) den ändrade kopian eller använda oss
av *referenssemantik* som tillåter två platser i koden att dela på
samma värde. Kod för den första lösningen finns i
`point-struct-return.c` -- jämför programmen för att se den
minimala ändringen. Sedan går vi vidare till att prata om
referenssemantik.


### Pekare och referenssemantik

En pekare är enkelt uttryckt en adress till en plats i minnet där
det ligger ett annat värde (mer exakt *kan* det ligga ett annat
värde där. Mer om detta senare under kursen). En variabel av typen
`int` innehåller ett heltalsvärde; en variabel av typen `int *`
innehåller en adress till en plats i minnet där det finns ett
heltalsvärde. Analogt avser typen `int * *` en adress till en
plats i minnet där det finns en annan adress till en plats i
minnet där det finns ett heltal, etc. På svenska säger vi "en
pekare" till ett heltal och på engelska "pointer".

Programmet `point-struct-pointer.c` använder sig av pekare till
punkter för att dela punkter mellan huvudprogrammet och
`translate`-funktionen. Detta sker genom att typen på parametern
till funktionen ändrats till `struct point *`, alltså inte längre
en punkt utan en pekare till en punkt. Vad som nu skickas in som
argument till funktionen är adressen till en plats i minnet där en
punkt finns, som kan läsas och skrivas -- en plats (och en punkt)
som därmed delas mellan huvudprogrammet och funktionen. Notera att
syntaxen för att komma åt fält via pekare ändras från `.` till
`->` (rad 7 och 8) för att tydligt visa att man gör åtkomst till
en icke-lokal plats i minnet som kan var synlig för "vem som
helst".

Operatorn `&` kallas för "adresstagningsoperatorn" och den kan
användas för att ta fram adressen till ett värde. På rad 21 i
`point-struct-pointer.c` används den för att komma åt de platser i
minnet där `somewhere` och `other` finns eftersom `translate` nu
förväntar sig denna input istället för det faktiska värdet.

Kör programmet och kontrollera att uppdateringarna av `p` i
`translate` nu får förväntat genomslag.


#### Gå från värdesemantik till referenssemantik

Ändra funktionen `printPoint` så att den också tar emot en pekare
till en punkt istället för en kopia. Du måste modifiera
parameterdeklarationen, åtkomsten till `x` och `y` i utskriften,
samt anropsplatserna som nu måste skicka in adresser till punkter
istället för de faktiska punkterna. Verifiera med hjälp av
verktygen och förstås genom att köra programmet!


### Allokering på heapen

Hittills har alla värden vi hanterat legat på stacken. Stacken
medger effektiv hantering av små och kortlivade värden, men för
stora och dynamiskt växande strukturer vill vi i regel använda
heapminnet.

Allokering på heapen sker med hjälp av funktionen `malloc` (och
några till med liknande funktion). Som argument till `malloc`
anger man hur många bytes i minnet man vill allokera, och i retur
får man adressen till ett minnesblock av denna storlek (mer exakt
av minst denna storlek, men det finns i regel inget sätt att ta
reda på storleksskillnaden).

En van C-programmerare kan enkelt räkna ut hur många bytes som
behövs för att lagra t.ex. en `struct point` i minnet, en siffra
som varierar beroende på vilken platform (vilken hårdvara och
vilket operativsystem) man använder. För att slippa göra denna
huvudräkning varje gång man skall kompilera sitt program på en ny
plattform tillhandahåller C ett hjälpmacro `sizeof`.

För att "mallokera" nog med utrymme för att rymma en `struct
point` kan man skriva:

``` c
  ... = malloc(sizeof(struct point));
```

Returtypen för `malloc` är något komplicerad och vi återkommer
till detta senare i kursen. För stunden kan vi tänka att `malloc`
returnerar en pekare till den struktur vars yta vi bad om, i
exemplet ovan alltså en pekare till en `struct point`, alltså en
`struct point *`.


#### Från allokering på stacken till allokering på heapen

Ditt modifierade program från ovan har två variabler `somewhere`
och `other` som innehåller punkter som är allokerade på stacken.
Modifiera variablerna så att de blir *pekare* till punkter som
är allokerade på heapen. Notera att användade av `malloc` kräver
att man först inkluderar `stdlib.h`.

En viktig skillnad mellan allokering på stacken och allokering på
heapen är att initieringen av strukten måste göras explicit (vi
kan alltså inte använda oss av `= { 7, 3 }` etc. som vi såg
tidigare):

``` c
  p->x = 7;
  p->y = 3;
```

Du kan jämföra din lösning med `point-struct-malloc.c`.


### Utökning: typedef

Använd `typedef` för att lägga till en ny typdefinition i ditt
program (se t.ex. [här](http://en.wikipedia.org/wiki/Typedef) för
mer information.). På kursen använder vi med något undantag
konventionen att typer med stor begynnelsebokstav avser pekare.
Definiera alltså typen `Point` som en pekare till en `struct`
`point*`. Du kan jämföra din lösning med `point-struct-typedef.c`.
Tycker du att programmet blir mer eller mindre läsbart?


### Att ta med sig

* Notera att argumentet till `sizeof` är `struct point` *utan* `*`
  -- det är för att vi vill veta hur mycket plats den faktiska
  strukten tar, och inte hur mycket utrymme som krävs för att
  lagra själva adressen dit!
* Använd alltid `sizeof` istället för att försöka räkna ut
  storlekar -- det senare leder bara till fel och
  plattformsspecifik kod!
* Minnesläckage och pekarfel är de vanligaste felen
  C-programmerare gör, oavsett om de är nybörjare eller har lång
  erfarenhet!
