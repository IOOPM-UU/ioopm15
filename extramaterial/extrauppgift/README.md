# Frivillig extrauppgift, IOOPM: Ordräknare

*Programmet övar delar av innehållet i
[F2](https://github.com/IOOPM-UU/ioopm15/tree/master/forelasningar/L2),
[F3](https://github.com/IOOPM-UU/ioopm15/tree/master/forelasningar/L3),
[F4](https://github.com/IOOPM-UU/ioopm15/tree/master/forelasningar/L4),
[F5](https://github.com/IOOPM-UU/ioopm15/tree/master/forelasningar/L5), och
[F7](https://github.com/IOOPM-UU/ioopm15/tree/master/forelasningar/L7).*

Programmet skall ta emot en lista av filer som anges på
kommandoraden. Den första filen innehåller en sorterad lista av
ord med ett ord på varje rad. Läs in dem och lägg dem i en array.

Läs sedan in resterande filer. För varje ord, kolla om ordet är
med i indexet, och om så är fallet, uppdatera dess räknare med ett.

I slutet av programmet, skriv ut indexet i frekvensordning.

Interaktionen med programmet borde se ut ungefär så här:

```
$ ./ordraknare 4 index.txt fil1.txt fil2.txt ... filn.txt
Foo     23
Bar     11
Quux     3
Kakfot   0
```

där 4 avser att längden på `index.txt` är 4 rader (ord).


# Genomgång av funktioner i programmet

Funktionen `index_new` tar som indata namnet på en fil som skall
innehålla en ordlista, med ett ord per rad i bokstavsordning, samt
storleken på det index som skall skapas (alltså antalet rader i
filen). Utifrån innehållet i denna fil skall ett index skapas
(tänk som en tabell med två kolumner, en för orden och en för
deras frekvens) där varje ord har startfrekvensen 0. Indexet skall
ligga på heapen (alltså använda `malloc` eller `calloc` för att
skapa det) och funktionen skall returnera tillbaka en pekare till
indexet.

```
index_t *index_new(char *filename, int index_size);
```

Funktionen `index_print` tar emot en pekare till ett index och
skriver ut det i tabellform. Det andra argumentet styr
sorteringsordningen -- skall det vara sorteras med avseende på
frekvensordning eller bokstavsordning.

```
void index_print(index_t *index, bool freq_sort);
```

Funktionen `index_add_word` kontrolelrar om `word` finns i `index`
och i så fall ökas dess frekvens med ett. Ord som inte finns i
index ignoreras helt.

```
void index_add_word(index_t *index, char *word);
```

Funktionen `word_iterator_new` tar som indata ett filnamn och
returnerar en *iterator* för denna fil som kan användas för att
läsa innehållet i filen ord för ord med hjälp av de övriga
iteratorfuktionerna. Datatypen `word_iter_t` definieras så här:

```
typedef struct word_iter word_iter_t;
struct word_iter
{
  FILE *f;
  bool open;
};
```

Hjälpkod för `word_iterator_new` finns senare i denna text. 

```
word_iter_t word_iterator_new(char *filename);
```

Funktionen `word_iterator_next` returnerar nästa ord i den fil som
`iter` avser. Funktionen hoppar över specialtecken, etc. Vid varje
anrop följer vi följande algoritm:

1. Läs in nästa tecken tills dess att det inlästa tecknet är en bokstav
-  Spara bokstaven i en buffert. Fortsätt läsa in tecken så länge som
   det är bokstäver som läses in. Spara dem också i bufferten.
-  Avbryt vid nästa inläsning av en icke-bokstav. Kopiera upp ordet på
   heapen och returnera en pekare till det. 

Vid anrop till `word_iterator_next` där slutet av filen nås innan
något ord har lästs in i bufferten skall NULL returneras. 

```
char *word_iterator_next(word_iter_t *iter);
```

Funktionen `word_iterator_has_more` returnerar `true` om
`word_iterator_next` inte har nått slutet på filen, dvs.
filpositionen inte är end of file (EOF).

```
bool word_iterator_has_more(word_iter_t *iter);
```

Utöver ovanstående funktioner skall du skapa funktionen
`index_free` och för att rensa data allokerat på heapen. Notera
att `word_iterator_t` inte behöver en motsvarande funktion
eftersom dess minne ligger på heapen. Dock måste vi *stänga* filen
som vi itererat över när vi är klara. Det kan vi faktiskt sköta om
i `word_iterator_next` i samband med att vi når filslutet. Vi
sätter sedan `open`-flaggan i `word_iterator_t` till `false` så
att detta sedan kan användas av `word_iterator_has_more`.


# Hur man läser in en fil

Du behöver använda `fopen` för att öppna en fil. Man skickar med
filnamnet och det sätt på vilket filen skall öppnas. I detta fall
räcker det med att öppna filer för läsning:

```
#include <stdio.h>

FILE *f = fopen("foo.txt", "r");
```

Detta öppnar filen foo.txt för läsning och (r = read) och vi får
tillbaka en pekare till en fil som kan användas som argument till
funktioner som läser från filer. För att stänga filen (vilket vi
gör när vi är klara med den) anropar vi `fclose`:

```
fclose(f);
```

För att läsa ett tecken från en fil kan vi använda `fgetc`:

```
int c = fgetc(f);
```

Observera att resultatet är en `int` och inte en sträng. Det är
för att kunna returnera EOF (som är en konstant) vid filslut.
Alltså, om `c == EOF` ovan så vet vi att vi har kommit till slutet
på filen.



# En lämplig ordning att skriva programmet

Utgå från main-funktionen nedan.

1. Definiera strukten `struct index` och typen `index_t` -- du behöver förmodligen ytterligare en datastruktur som avser "en rad i tabellen"
2. Stoppa in funktionerna i programmet så att du kan kompilera det
   a.) Första inkrementet: programmet kompilerar
   b.) Andra inkrementet: se till att programmet också kör även om det inte skriver ut något vettigt 
3. Implementera `index_new`
   a.) Första inkrementet: returnera ett hårdkodat index
   b.) Andra inkrementet: indexet skapas från filen -- använd funktionerna från 6. för att läsa in orden! 
4. Implementera `index_print` -- nu kan kan du testa dem ihop och se att du får ut rätt resultat
   a.) Börja med att skriva ut i bokstavsordning
   b.) Gå sedan vidare till frekvensordning efter att du är klar med 5.
5. Implementera `index_free` -- nu kan du pröva att programmet inte läcker minne
6. Implementera `word_iterator_new`, `word_iterator_next` och `word_iterator_has_more` i den ordningen. 


```
int main(int argc, char *argv[])
{
  // Obs! Programmet funkar inte om man anger fel parametrar
  int index_size = atoi(argv[1]); 
  index_t *index = index_new(argv[2], index_size); 
  for (int i = 2; i < argc; ++i)
    {
      word_iterator_t iter = word_iterator_new(argv[i]);
	  while (word_iterator_has_more(&iter))
        {
	      index_add_word(index, word_iterator_next(&iter));
	    }
    }
  index_print(index, true);
  index_free(index);
  return 0;
}
```


# Frivilliga utökningar (till den frivilliga uppgiften)

1. Utöka programmet så att indexet kan ha ett godtyckligt antal
   ord. Detta kräver att du implementerar om `index_t` så att det
   har en länkad lista i sig istället för en array.
2. Ändra så att indexfilen inte behövs. Alla nya ord som inte finns
   i index tidigare skall läggas till när de träffas på för första
   gången. 
3. Tidskomplexiteten för detta program är dålig -- körtiden växer
   exponentiellt eftersom vi måste göra linjära sökningar in i 
   en länkad lista hela tiden. Skriv om programmet så att det 
   använder ett träd istället för en länkad lista! 
   

# Tips


C-kompilatorn kompilerar programmet uppifrån och ned. Om man på
rad X använder en funktion som definieras på rad Y och X kommer
före Y i programmet klagar kompilatorn. Lösningen på deta är att
högst upp i programmet förklara vilka funktioner det innehåller.
Det gör man genom att helt enkelt lista deras *prototyper*, så
här:

```
int foo(bar_t *arg);
...
```

I genomgång av funktionerna i programmet är funktionsprototyperna
för de flesta funktionerna som du kommer att behöva listade.



# Redovisning av mål

Det går bra att redovisa mål på denna uppgift. Ta inspiration från
mål-tipsen från lagerhanterare 1 och 2. Prata med Tobias/en
assistent om du behöver hjälp. Enskilda studenter kan få redovisa
denna uppgift som Z101. Prata med Tobias om detta, vi avgör det
från fall till fall beroende på omständigheterna. I övrigt är
denna uppgift, precis som all C-programmering, utmärkt träning
inför kodprovet.


   
