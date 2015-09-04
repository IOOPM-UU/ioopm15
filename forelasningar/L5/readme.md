# Föreläsning 5

* [Bilder](f5.pdf) (pdf, publiceras 2015-09-06)


# Vad du kan göra själv

Till denna föreläsning finns det ett antal kodexempel som du kan
arbeta med. Vissa av dem använder minnet korrrekt (de heter `good`),
vissa av dem läcker minne, eller använder minne dåligt på något 
annat sätt (de heter `bad`). Din uppgift är att
förstå varför de som inte läcker minne inte gör det, samt fixa
minnesläckagen hos de program som läcker minne.

För att få information om minnesläckage kan du använda `valgrind`:

```
$ valgrind --leak-check=full ./bad1
```

Observera  att programmen  är väldigt  lika, och  att de  visar på
olika typer av fel. En fellista  finns längre ned i detta dokument
-- för varje  program/minnesfel, försök att hitta  ett motsvarande
fel i fellistan!

Du kan inte redovisa mål på de här uppgifterna. Du kan däremot ta
tag i labbassar och be dem förklara eller ännu hellre visa hur man
löser uppgiften på någon av labbarna.

Kompilera och kör så här: (`$` är prompten)

```
$ gcc -o bad1 bad1.c
$ ./bad1
```

Eller ännu hellre, använd medföljande `makefile` (se föreläsning 6):

```
$ make
```

Detta kompilarar alla filerna. Du kommer att se något i stil med:

```
gcc -Wall -ggdb -o bad1 bad1.c
gcc -Wall -ggdb -o bad2 bad2.c
gcc -Wall -ggdb -o bad3 bad3.c
gcc -Wall -ggdb -o good1 good1.c
gcc -Wall -ggdb -o good2 good2.c
gcc -Wall -ggdb -o good3 good3.c
```

## Fellista

Flera av dessa kan vara sanna samtidigt!

* Programmet frigör inte minne som har allokerats via `malloc`, `calloc` eller `realloc`
* Programmet frigör inte minne som har allokerats som en sido-effekt av någon funktion som anropats i programmet (t.ex. `strdup`)
* Programmet försöker frigöra minne som inte har allokerats på heapen (t.ex. strängliteraler eller minne på stacken)
* Programmet försöker frigöra minne via en pekare som har ändrats via pekararitmetik (finns ej exempel på detta bland de utdelade programmen här)
* En länkad struktur `a --> b`  frigörs inte ordentligt, t.ex. man frigör bara `a`, och förlorar därmed möjligheten att frigöra `b`
* Programmet läcker minne genom att den sista pekaren till någon objekt `p` skrivs över utan att `free(p)` eller motsvarande görs


