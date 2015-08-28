Inlupp 3.a: Utökat lagerhanteringssystem
========================================

Den sista utökningen av lagerhanteringssystemet omfattar flera
olika steg:

1. Använda C:s standardbibliotek (filer, sortering via dynamiska
   arrayer)
2. Stöd för persistens på fil (alltså spara databasen till disk
   och läsa upp den igen)
3. Skriv enhetstester för programmet
4. Generalisering av list och träd-modulerna från
   [Inlupp 2.a](../../sprint2/lagerhanterare2.0)
5. Integration med kod från annat kodpar på kursen

En bra idé är att börja med 4 följt av 5 eftersom 5 kräver
interaktion med ett annat kodpar vilket ofta medför några dagars
slack.


## Användning av C:s standardbibliotek

Vi har använt C:s standardbibliotek förut (`malloc`, `free`,
strängmanipulering, etc.). Nu skall vi utöka detta med användning
av funktioner för filmanipulering. Du kan använda `man stdio` för
att se standardfunktioner för I/O. Vi kommer att behöva ganska få
av dessa: förmodligen räcker det med öppna, läsa, skriva och
stänga. Läs vidare under **Persistens på fil** nedan. Notera att det
finns olika funktioner för att läsa `int`:ar, strängar, etc.

Vidare skall vi använda oss av C:s inbyggda stöd för sortering för
att balansera binärträdet som håller i varudatabasen. Du kan
använda `man qsort` för att läsa om C:s implementation av
quicksort-algoritmen.

Balansering av binärträdet sker på följande sätt:

1. Dumpa trädet i preorder ned i en array. Du kan använda
   `tree_size()` för att ta reda på hur många element som skall
   finnas i arrayen. Du kan också med fördel använda en generell
   preorder-funktion som tar en funktionspekare för att dumpa
   trädet ned i arrayen.
2. Skapa ett nytt träd och fyll det med element från arrayen i
   rätt ordning.

Nedan finns ett litet Python-program som bygger upp trädet från en
sorterad array. Notationen [:] nedan betyder att om `a = [1,2,3,4,5]`
så är `a[middle] == 3`, `a[:middle] == [1,2]` och `a[middle+1:] == [4,5]`.

```python
def build_tree_from_array(a):
    middle = len(a) / 2
    tree_insert(a[middle])
    if middle > 0:
        build_tree_from_array(a[:middle])
    if middle > 1:
        build_tree_from_array(a[middle+1:])
```

Balansering av trädet skall göras tillgänglig från huvudloopen:

    [S]ortera databasen


## Generalisering av datastrukturerna

I förra versionen av lagerhanteringen bytte vi lagringsformat från
en statisk array till dynamiska träd och listor. Nu skall vi
generalisera träden och listorna på ett sådant sätt att det går
att använda dem i godtyckliga C-program.

Det betyder att du måste ändra på datastrukturerna på följande
sätt:

* Nycklar och poster i trädet/element i listan måste vara av typen
  `void *`
* All jämförelse eller operation på data av typen `void *` måste
  ske med hjälp av funktionspekare

För att arbeta med funktionspekare är `typedef` ovärdeligt för att
hålla koden läsbar. Följande C-kod deklarerar typen `cmp_t` som en
funktion som tar två pekare av okänd typ (`void *`) och returnerar
en `int`. Tanken är att funktionen skall fungera som
biblioteksfunktionen `strcmp` som jämför strängar. Låt `x = strcmp(a,b)`.
Om `x < 0` är `a` före `b` i aktuell sorteringsordning. Om `x > 0` är `b`
före `a`. Om `x == 0` är `a` och `b` exvivalenta.

```c
/// @returns like strcmp
typedef int(*cmp_t)(void *, void *);
```

Nu kan vi modifiera funktionen som skapar en lista till att ta en pekare till en
funktion för att jämföra elementen:

```c
list_t *mk_list(cmp_t *cmp)
{
  list_t *result = malloc(sizeof(list_t));
  if (result)
  {
    *result = { .cmp_f = cmp };
  }
  return result;
}
```

Och sedan använda denna funktion när vi behöver jämföra element,
t.ex. när vi vill göra insättning i sorteringsordning:

```c
void list_insert(list_t *l, void *elem)
{
  node_t **c = &(l->first);
  while (*c && l->cmp_f((*c)->elem, elem)
    {
      c = &((*c)->next);
    }
  *c = mk_node(elem, *c);
}
```

**TIPS!**

Om listan/trädet behöver kopiera element behövs en funktion för
det. Om listan/trädet behöver ta bort ett element ur minnet behövs
en funktion för det (eftersom elementet kan innehålla pekare till
andra strukturer som måste frigöras explicit). Och så vidare.

**Koden för listan eller trädet får inte innehålla någon som helst
kod som är specifik för lagerhanteraren!**

Om du t.ex. behöver skriva ut alla element i en lista kan du lösa
det på två sätt:

1. Implementera en extern iterator
2. Implementera en intern iterator

En extern iterator är ett protokoll som låter en användare vandra
igenom en datastruktur. Så här:

```c
iter_t *iter = list_iterator(mylist);
while (iter_has_next(iter))
  {
    T *elem = (T *) iter_next(iter);
    ... // print elem
  }
```

Här är magin att vi vet att listan innehåller element av typen `T`
så att vi kan typomvandla resultatet av `iter_next`. Iteratorer
tas upp på lektion 2.

En intern iterator tar en funktionspekare och applicerar den på
alla element i turordning:

```c
void list_iterate(list_t *l, iter_t *f)
{
  for (elem_t *c = l->first; c; c = c->next)
    {
        f(c->elem);
    }
}
```

Här är `iter_t` en typ för en funktion som tar en `void *` och
inte returnerar något utan bara har sido-effekted. T.ex. kunde
vi ha en funktion:

```c
void print_element(void *p)
{
  T *elem = p;
  ... // print elem
}
```

som kan användas så här:

```c
list_iterate(mylist, print_element);
```

**När ni är klara med denna del, flytta trädet och listan egna
kataloger som inte ligger tillsammans med kod från
lagerhanteringssystemet.**


## Integration med andras kod

Denna del av uppgiften går ut på att uppleva integration med kod
som man inte själv har skrivit. För denna uppgift skall ni para
ihop er med ett annat kodpar på kursen. Använd Piazza för att
hitta ett annat par.

Nu skall ni byta träd och lista med varandra. Ni klonar (eller
forkar) deras repository och kompilerar och länkar mot den koden
istället för er egen list/trädkod. Eftersom listans gränssnitt var
givet samma till alla torde detta vara lätt att byta ut. Jämför
det med utbyte av trädet vars gränssnitt inte var
"standardiserat".

Använd deras dokumentation och headerfiler men försök undvika att
läsa deras kod. Programmera mot *gränssnittet* som det är tänkt
att man skall göra -- man har inte alltid tillgång till koden. Med
mindre än att ni kan påvisa buggar i det andra kodparets kod får
ni **INTE** ändra deras kod -- ni måste anpassa ert program att
fungera med de nya träd- och listmodulerna. Använd issue trackern
på GitHub för att få det andra kodparet att laga sina fel.

Skriv en kort rapport om era erfarenheter som en issue på GitHub
för det andra kodparets repository.

* Hur stora var skillnaderna mellan implementationerna?
* Var dokumentationen välskriven och användbar?
* Även om gränssnitten var lika, fanns det ibland skillnader i
  beteenden?
* Hur upplevde ni kvaliteten på namn i den andra koden?
* Saknades någon funktion?
* Fanns det något som var extra bra i den andra koden som saknades
  i er?


## Enhetstester

**TODO**


## Persistens på fil

Nu skall vi lägga till stöd för att spara databasen på fil och
läsa upp den igen. Börja med att bekanta dig med hur funktionerna
`fopen`, `fread` och `fclose` fungerar, lämpligen genom att
implementera en egen version av UNIX-programmet `cat` (skriv `man
cat` om du inte känner till programmet).

Programmet skall ta som kommandoradsargument, namnet på den fil
som innehåller databasen. Om denna fil inte finns skall den skapas
och databasen skall vara tom. När programmet avslutas skall
databasen sparas ned på filen så att den kan läsas upp igen nästa
gång programmet startar. Det finns inga kommandon i programmet för
att spara eller ladda databasen -- det sker automatiskt.

För att spara datat i databasen har du två val:

1. Spara datat som radorienterad text där varje vara tar upp 4
   rader (namn, beskrivning, pris, AL -- antal lagerplatser) och
   en lagerplats tar upp två rader (lagerplats, kvantitet).
   Inläsning läser först 4 rader och skapar en post i databasen
   från den. Sedan läser man AL * 2 rader för att läsa in
   lagerplatserna och stoppar in dem för den aktuella varan i
   databasen. När man når `EOF` -- end of file -- är man klar.
2. Definiera ett binärt filformat på motsvarande sätt. Ett hyfsat
   bra filformat är detta:

```c
int siz;             // antal bytes i posten
int name_siz;        // antal tecken i nästföljande sträng
char[name_siz] name; // namnet
int desc_siz;        // antal tecken i nästföljande sträng
char[desc_siz] desc; // beskrivningen
int price;           // pris
int storage_siz;     // antal lagerplatser
lagerplats_t[storage_siz] storage; // lagerplatserna
```

Egentligen är `storage_siz` onödig, men det blir något enklare på
detta vis.

Man kan till och med tänka sig att själva filen startar med en
`int` som berättar hur många poster den innehåller, men det går
förstås också bra att leta efter `EOF` -- end of file.


# Åtta möjliga utökningar

1. Möjlighet att spara och ladda en annan databasfil under körning
   av programmet
2. Automatisk balansering av databasträdet istället för att
   användaren måste göra det manuellt
3. Utöka makefilen med ett test-direktiv som kör alla tester
4. Använd ett "coverage-verktyg" typ `gcov` för att ta reda på hur
   stor del av er kod testerna testar
5. Konfigurera GitHub för att köra enhetstester automatiskt när
   kod checkas in
6. Använd listmodul och trädmodul från två olika kodpar
7. Utöka lagerplatsinformation med datum -- om datumet är före
   dagens datum finns varan, annars avser datumet
8. Tillämpa defensiv programmering på hela programmet (se
   föreläsning 12)



# Förslag på 3-mål att redovisa

1. [Inluppsmål 3](http://auportal.herokuapp.com/achievements/102)
2. [E10](http://auportal.herokuapp.com/achievements/10) -- om du implementerar databasen t.ex. med ett binärt
   sökträd eller en länkad lista som är kan lagra godtyckligt data
3. [I22](http://auportal.herokuapp.com/achievements/22) -- indata både från användaren och andra delar av
   programmet att tänka på

# Förslag på 4/5-mål att redovisa

1. [A3](http://auportal.herokuapp.com/achievements/3) -- om du delar upp programmet i olika moduler som antytts
   ovan
2. [P47](http://auportal.herokuapp.com/achievements/47) -- hjälp en annan grupp förbättra sin kod med en pull request
3. [Q50](http://auportal.herokuapp.com/achievements/50) -- försök avgöra hur bra dina tester är
