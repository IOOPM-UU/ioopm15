Här är koden som skrevs på föreläsningen den 22 september, plus
koden för iteratorn som behövs i funktionen `showStack` i
`calc.c`. `Makefile` har utökats med kommentarer, och `stack.c`
innehåller en kort presentation av iteratorer i kommentarerna.

Programmet `calc` är en mycket enkel stackkalkylator. Skriver man
ett heltal pushas det på stacken. '+' adderar de två översta talen
på stacken och ersätter dem med summan. '*' multiplicerar de två
översta talen på stacken och ersätter dem med produkten.

Förslag på utökningar:

* En seriös implementation skulle förstås innehålla fler
  operationer än bara addition och multiplikation. Lägg till stöd
  för subtraktion, division och modulo. Tillåt inte division eller
  modulo med noll (ge ett felmeddelande).

* Lägg till följande operationer:
  - dup: Duplicera det översta elementet på stacken
  - pop: Ta bort det översta elementet på stacken
  - swap: Byt plats på de två översta elementen på stacken
  - clr: Töm hela stacken

* Skapa en datatyp (en struct) som antingen representerar ett
  heltal eller ett boolskt värde (`true` eller `false`), till exempel
  genom att ha två fält `val` och `type` där `type == 0` betyder
  att `val` ska tolkas som ett heltal och `type == 1` betyder att
  `val` ska tolkas som ett boolskt värde. Använd din nya struct
  som element i stacken, så att man kan pusha `true`, `false` eller
  ett heltal.

  Om de tre översta elementen är `a b c`, lägg till följande
  operationer:
  - = : Ersätt `a b` med `true` om `a = b`, annars med `false`
  - < : Ersätt `a b` med `true` om `a < b`, annars med `false`.
    Ge ett felmeddelande om inte både `a` och `b` är heltal
  - if: Ersätt `a b c` med `b` om `a` är `true`, och med `c` om
    `a` är `false`. Ge ett felmeddelande om `a` inte är ett boolskt
    värde.

* Läs på om stack-orienterad programmering. Som vanligt kan man
  börja på
  [Wikipedia](http://en.wikipedia.org/wiki/Stack-oriented_programming_language),
  men kolla också till exempel in språket [Factor](http://factorcode.org/)
