Kom igång med C
===============

Det här är en lite längre övningsuppgift (egentligen en samling
småuppgifter) för komma igång med kursen i allmänhet och C i
synnerhet. Tanken är att du här ska få en överblick av det
innehåll som ingår i fas 1 på kursen. Om du gör hela den här
övningen under den första veckan kommer du vara väl förberedd att
ta dig an första tredjedelen av kursen!

Lejonparten av denna uppgift består av instruktioner som skall
följas. Successivt får uppgiften karaktär av att du själv måste
tänka och utföra något. Inför varje moment finns det pekare till
material, t.ex. screencasts, som du bör titta på innan du går
vidare.

Du kan navigera mellan de olika delarna med hjälp av länkarna i
det här dokumentet. Om du redan känner dig bekväm med någon del är
det helt okej att hoppa över den, men tänk på att resten av kursen
mer eller mindre kommer att förutsätta att du förstår begreppen
som presenteras här.

## Förberedande steg

1. Hitta någon att jobba med för den här uppgiften. (Det är alltid
    kaos när en kurs startar. Många av delarna av denna uppgift
    går i värsta fall att göra på egen hand, men kvaliteten på
    inlärningen blir i regel bättre när man är två och diskuterar
    allt tillsammans). Senare i kursen måste din labbpartner vara
    någon i din grupp, men för den första veckan kan du alltså
    jobba med vem du vill.
2. Logga in på en lämplig Unixmaskin.
3. Starta ett terminalfönster.

## Innehåll

Klicka på nedanstående länkar för att komma till uppgifterna.

### Verktyg
1. [Emacs](emacs)
2. [Versionshantering och git](git)
3. [Terminalhantering](terminal)
4. [Mer Emacs](meremacs)
5. [man-sidor](man)
6. [LaTeX](latex)

### C-programmering

**Lämpliga förberedelser:** de flesta screencasts om C, inklusive
enkla datatyper, loopar, variabler, funktioner, grundläggande I/O,
arrayer. Om du inte vill se alla på en gång kan du t.ex. vänta med
arrayer till just före det avsnittet.

1. [Att kompilera ett C-program](compile)
2. [Debugging och gdb](gdb)
3. [Iteration vs. rekursion](rec)
4. [Arrayer](arrays)
5. [Strängar och tecken](strings)
6. [I/O](io)
7. [Malloc och pekare](malloc)
8. [Minnesläckage och valgrind](valgrind)

### Metodik
1. [Testdriven utveckling och parprogrammering](tdd)
2. [Enhetstestning](unittests)
3. [Kodgranskning](review)
4. [Redovisingar](demonstrations)

## Sammanfattning

Ett av målen med denna kurs är att du skall skapa ett fungerande
arbetsflöde som innehåller verktyg som stöder dig i din
programmering. Idealiskt skall du uppleva att verktygen är
"naturliga förlängningar av dig själv" och du skall kunna hoppa
sömlöst mellan olika verktyg och aktiviteter, t.ex. från editering
till terminalen för att använda `Make`, och in i `gdb` när
programmet kraschar (allt detta kan göras inifrån Emacs förstås).

Vad som passar i ett arbetsflöde är naturligtvis personligt. Av
flera anledningar (dessa går vi igenom på annan plats) kommer vi
dock på denna kurs att kräva bland annat:

* Emacs för all editering (under fas 2 är det okej att använda en
   av IDEerna Eclipse, Netbeans och IntelliJ)
* Make för bygghantering
* `valgrind` för minneskontroll
* Git för versionshantering
* `gdb` för debuggning
* Doxygen och/eller JavaDoc för generering av API-dokumentation
* LaTeX för alla rapporter

Det är med verktygskedjor som med programmering: man måste nöta
och nöta och nöta för att till slut bemästra dem. Det är sannolikt
att du kommer att uppleva att vissa saker i denna påtvingade
verktygskedja är dåligt, och andra saker bra, och några
fantastiska. Då har du en bra bas att stå på för att börja designa
din egen verktygskedja och ditt eget optimala arbetsflöde!


### Ytterligare råd
* Kompilera ofta, gärna mellan varje ändring
* Åtgärda alltid kompileringsfel uppifrån och ned!
* Använd Emacs för att kompilera och navigera till den plats i
  koden där kompileringsfel finns. Varje hopp mellan t.ex. Emacs
  och terminalen gör att du riskerar att tappa bort var du håller
  på med. **Skapa ett fungerande arbetsflöde för att hålla
  fokus!**


## Det var det!

Grattis, nu har du redan stött på de flesta verktyg etc. som
kommer att användas på kursen, och sett en hel del av den
imperativa programmeringen i C! Tanken med denna inledande duvning
är inte att du skall tänka "nu är jag av med det" utan tvärtom --
nu vet jag vilka verktyg jag skall bemöda mig om att använda i
mesta möjligaste mån under resten av kursen!

Efter den inledande veckan återstår tre sprintar i denna fas, som
alltså behandlar imperativ programmering exemplifierat med C.
Kursen fortsätter sen på detta sätt: varje sprint kommer du att
göra minst en uppgift som du använder för att redovisa mål. Du
redovisar (oftast) mål vid labbtillfällen.

Den sista fasen är projektarbetet och då är arbetet något friare.
Observera att du förväntas använda projektet till att bocka av
mål, och att målet med projektet inte är att göra en perfekt
implementation av en specifikation.

Avslutningsvis finns det bara ett sätt att lära sig programmering
och det är genom att skriva så mycket egen kod som möjligt och
läsa så mycket kod skriven av andra som möjligt! Gör't!
