Screencasts om C
================

Här finns länkar till samtliga skärmföreläsningar som rör
imperativ programmering i C. Varje screencast ligger under den
vecka som vi rekommenderar att man ser just den screencasten.

## V. 36

### Screencasts till föreläsning 1

* Introduktion till C. En screencast i 3 delar
  - [Hello World](https://www.youtube.com/watch?v=SNYwzVtj0mY&list=UUxcEJHLbYZC7TdmDAPnHE4Q&index=67)
  [10 minuter] - Vi skriver det klassiska "Hello World"-programmet
  i C

  - [Kompilering](https://www.youtube.com/watch?v=lSznMdjLrMA&list=UUxcEJHLbYZC7TdmDAPnHE4Q&index=66)
  [6 minuter] - Hur man kompilerar och länkar sitt C-program
    - Flaggan `-g` för att bädda in debugga sitt program.
    - Flaggan `-W` för varningar.
    - Flaggan `-o` för att döpa output.

  - [Inkludera standardbiblioteket `stdio.h`](https://www.youtube.com/watch?v=gmZsTqGT_uo&index=65&list=UUxcEJHLbYZC7TdmDAPnHE4Q)
    [6 minuter] - Vi visar hur man inkluderar bibliotek i C med
    preprocessor-direktivet include, exemplifierar hur man kan ta
    fram hjälp för vissa funktioner med man-programmet (i
    \*nix-system)

* [Litet exempelprogram: Kvadrater](https://www.youtube.com/watch?v=BXzJPX-KelM)
   [10 minuter] - Vi skriver ett program som skriver ut kvadrater
   av ett tal. Exemplifierar några standard-features i C-språket.
  - Funktionsdefinitioner och -anrop
  - Villkorssatser (conditionals)
  - Formaterad output med printf
  - Rekursiva funktioner
  - `for`-loopar (iteration)
  - C99-standard-flaggan. (Vi använder i regel C99 och inte C11
    eftersom stödet för C11 inte är lika utbrett.)

* [Funktioner](http://www.youtube.com/watch?v=rOPb50v8YDc)
  [24 minuter] - En lite längre genomgång av hur funktioner
  fungerar i C. (Ersätt mentalt "ML" med "Haskell")

### Screencasts till föreläsning 2

* [Variabler och tilldelningssatser](http://www.youtube.com/watch?v=NHZENqezN2Y)
  [Längd: 22 minuter] - Vi introducerar C:s semantik för variabler
  och tilldelningar genom ett antal exempel. Vi nämner begrepp som
  statisk typning, implicit konvertering mellan primitiva typer,
  värdesemantik vid parameteröverföring,
  inkrementeringsoperatorerna `++` och `--`.

* [Villkorssatser](https://www.youtube.com/watch?v=GnH3aFovFPA)
  [21 minuter] - Vi går igenom hur vilkorssatser fungerar i C.
  Notera (som även visas som en not till denna screencast) att
  stöd för en boolesk typ finns i C i och med C99 genom `stdbool.h`.
  Det är rekommenderat att använda `stdbool.h` överallt i C.

  (Här finns det 2 frågor som inte fungerar längre)

* [Loopar](http://www.youtube.com/watch?v=6dQ1pZt0lcM)
  [17 minuter] - Vi refaktorerar ett enkelt rekursivt program till
  att använda iteration istället. Visar de inbyggda looparna
  `for`, `while`, `do-while`. Diskuterar kort några skillnader
  mellan rekursion och iteration

* [Pekare](https://www.youtube.com/watch?v=01xJqhhFKK0)
  [26 minuter] - Vi introducerar kort C:s modell av minnet (en
  array av bytes), och koncepten adresser, pekare, `NULL`-pekare,
  avreferering, avreferering av `NULL` (segmentation fault).
  Pekare kommer att avhandlas mer genomgående senare i kursen!

  (Här finns det 3 frågor som inte fungerar längre)

* [Arrayer](http://www.youtube.com/watch?v=Xb3Ff9JtPMc)
  [12 minuter] - Presenterar arrayer, och hur visar hur
  arraynotationen är syntaktiskt socker för pekararitmetik.

### Screencasts till föreläsning 3

* [I/O i terminalen](https://www.youtube.com/watch?v=aYiatm0ni3A)
  [11 minuter] - Förklarar hur man på ett enkelt sätt kan läsa in
  och skriva ut värdet av olika typer i terminalen med ett
  C-program.

* [Strängar](http://www.youtube.com/watch?v=Q71HcbxaRPc)
  [22 minuter] - Förklarar hur strängar fungerar i C.
  - Strängar är arrayer.
  - Skillnaden på en "likadan" och "samma" sträng
  - Hur man kopierar strängar i C
  - Hur man jämför strängar i C


## V. 37

### Screencasts till föreläsning 4

* [Datatyper](http://www.youtube.com/watch?v=bitCJRyp45g)
  [6 minuter] - Kort repetition om några de grundläggande
  datatyperna i C - `int`, `char`, `long` etc.

* [Sammansatta datatyper](http://www.youtube.com/watch?v=RUXoQ5pzcMg)
  [19 minuter] - Hur man sätter ihop datatyper till nya med
  *struktar*.

* [Typer, typomvandling och typedef](http://www.youtube.com/watch?v=ZsicwbZUJYU)
  [16 minuter] - Mer ingående om C:s typsystem.
  - Vad betyder det att C är statiskt typat?
  - Vad betyder det att C är svagt typat?
  - Hur ger man nya namn till typer?

### Screencasts till föreläsning 5

* [Minneshantering](http://www.youtube.com/watch?v=goZT-RupQYA)
  [13 minuter] - Mer om C:s minnesmodell.
  - Var allokeras minnet för olika värden?
  - `malloc` och `free`

  (Här finns det 5 frågor som inte fungerar längre)

* [Minne och länkade strukturer](http://www.youtube.com/watch?v=gOeVI8qn4aU)
  [57 minuter] - Att implementera en länkad lista


## V. 38

### Screencasts till föreläsning 6

Inga just nu

### Screencasts till föreläsning 7

* [Kommandoradsargument](https://www.youtube.com/watch?v=MvI1w4M2Xbs&list=UUxcEJHLbYZC7TdmDAPnHE4Q)
  [6 minuter] - Hur man tar emot kommandoradsargument i ett
  C-program. Vi skriver programmet "echo" som skriver ut de
  argument som skickas in på terminalen.


## V. 39-40

* [Bitset: bitoperationer, uppräkningsbara typer, variabla argumentlistor, makron](http://www.youtube.com/watch?v=W8dEcUWdZqg)
  [78 minuter]