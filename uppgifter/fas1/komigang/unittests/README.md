Enhetstestning
==============

Enkelt uttryckt är ett enhetstest för en funktion *f* en samling
indata *i_1 ... i_n* och förväntat utdata *u_1 ... u_n*.
Enhetstester för *f* kan t.ex. skrivas i samma kodfil som *f*,
döpas till `test-av-f-1` etc. och köras genom en funktion
`test-av-f-alla`, men det är bättre att lägga testerna i en
separat fil. Med en så långt som möjligt automatiserad process
vill man sedan avgöra att *f(i_j)=u_j*, för *j=1 ... n*.

Idealiskt kör man alla relevanta test löpande, men åtminstone
innan man checkar in kod för att se till att inte trasig kod
sprids till andra och förpestar deras tillvaro. Dock är det svårt
att skriva bra tester. Det kräver både att man förstår problemet
(koden man vill testa) och att man vet vilka de vanliga felen är
som man bör testa för. Och även om man har bra tester, är det inte
säkert att tiden finns att köra alla om det tar flera timmar att
köra dem.

Enhetstester är enkla men kraftfulla. I grund och botten ligger
två frågor -- gäller *f(i)=u* (som förväntat) eller gäller
*f(i)\neq u* (som förväntat)? I många ramverk för enhetstester (vi
möter dem senare i kursen) har dessa frågor namn som
"`assertTrue`" och "`assertFalse`".

Om vi vill pröva att funktionen `strlen`, som räknar ut längden på
en given sträng, är korrekt skulle följande satser vara exempel på
sanna utsagor som vi förväntar oss håller i en korrekt
implementation av `strlen` (observera att översättningen till kod
är felaktig (29 istf 20). Poängen är att även tester kan vara
felaktiga!):

| **Test**                                  | **Uttryckt i kod**
| ----------------------------------------- | ------------------
| Längden av `"Hej"` är 3.                  | `strlen("Hej") == 3`
| Längden av `""` är 0.                     | `strlen("") == 0`
| Längden av `"Hokus pokus filiokus"` är 20 | `strlen("Hokus pokus filiokus") == 29`

Saker som man bör testa i enhetstest är extremvärden, tomma
strängar, stora värden. Pröva att en loop är korrekt för noll
varv, ett varv och många varv. Pröva att termineringsvillkoret
stämmer!

``` c
  for(int i=0; i<M; ++i) {
    doSomething(i);
  }
```

Hitta testfall som gör `M` till 0, 1 och något stort tal. `M` är i
regel någon slags input eller någon funktion av input.

I exemplet ovan med test av `strlen` vill vi pröva med strängar
av längden 0, 1 och en längre sträng.

Försök att få så hög "code coverage" som möjligt. Det betyder
att testerna skall pröva så mycket som möjligt av koden, och helst
alla möjliga vägar genom koden (tänk nästlade villkorssatser).

Att bara testa med slumpvisa värden är inte ett bra test utan
varje test har en anledning som härrör från funktionen man testar
och dess omständigheter. Försök att ha en anledning till varje
test och att dokumentera dessa anledningar!

Du kan inkludera testkod i ditt program i form av kod som anropar
de funktioner du vill testa. I avsnitten nedan skall du skriva
tester för det program som du implementerar så att du kan vara
(mer) säker på att det är korrekt. Detta kommer att tvinga dig att
fundera kring vad som är vettigt att testa, och vilka värden etc.
som är lämpliga.

Här är till sist implementationen av enhetstestet för `strlen`.
Titta på koden i `minute.h` och `minute.c` och kör programmet
nedan för att se vad det gör. Flera tester kan enkelt läggas till
som nya funktioner som också anropas från `main` (trots sin enkelhet
använder detta program flera koncept som är för avancerade för att
hitta in i kursen redan nu).

``` c
#include "minute.h"
#include<string.h>

void testStrlen() {
  assertTrue(strlen("Hej") == 3);
  assertTrue(strlen("") == 0);
  assertTrue(strlen("Hokus pokus filiokus") == 20);
}

int main(void) {
  testStrlen();
  report();
  return 0;
}
```

Kompilera med `make unit` och kör med `./unit-test-example`. Detta ger följande output:

```
foo> make unit
foo> ./unit-test-example
Testing strlen("Hej") == 3 ... PASSED
Testing strlen("") == 0 ... PASSED
Testing strlen("Hokus pokus filiokus") == 20 ... PASSED
All 3 test passed!
```

### Att ta med sig

* Enhetstesterna är dina vänner
* Skriv alltid enhetstester till den kod som du skriver
* Automatisera körandet av tester så att alla tester går att
  köra på ett enkelt sätt
