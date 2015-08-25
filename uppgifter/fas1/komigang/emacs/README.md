Lämplig förberedelse är att titta på screencasts Emacs 1 och 2.

Emacs
=====

Nu skall du få bekanta dig med Emacs, som är en texteditor för
bland annat programmering. Emacs är skrivet i C och Emacs Lisp
(Elisp) och består av en "liten" kärna runt vilken tusentals
paket av Elisp är virade för att tillhandahålla utökad
funktionalitet, som t.ex. färgläggning av nyckelord, stöd för att
navigera mellan kodfiler som refererar till varandra, kompilering,
felsökning och mycket annat. I texten nedan kommer vi att använda
Emacs syntax för kortkommandon. Så här tolkar du dem:

* `M-x` Håll ned meta-tangenten (I Sunray-maskinerna i
  datorsalarna på Polacksbacken har dessa en symbol som ser ut som
  en diamant, på andra tangentbord motsvarar meta ofta `Alt` eller
  `Cmd`) och tryck `x`
* `C-x,b` Håll ned kontrolltangeten (`ctrl`) och tryck `x`, släpp, tryck `b`
* `C-x,C-f` Håll ned kontrolltangeten och tryck `x`, släpp, håll
  ned kontrolltangeten igen och tryck `f`

Nu börjar vi!

1. Starta Emacs från terminalen: `emacs &`
2. Titta runt litet i menyerna -- vad finns det för alternativ?
3. Nu skall vi skapa en ny fil. Det gör man genom att öppna en
  fil och använda ett namn som inte finns. Öppna en fil med
  `C-x, C-f`. Döp filen till något godtyckligt som slutar
  med `.c`, till exempel `foo.c` och lägg den i din hemkatalog.
4. Notera att Emacs nu har gått in i "c-mode" och förväntar
  sig att du skall skriva C-kod. Pröva att skriva några
  C-nyckelord (t.ex. `int`, `void`, `return`, `for`,
  `while`, `case`) och se hur de färgläggs.
5. Skriv av följande program:

   ```c
   #include <stdio.h>
   int main(void) {
     puts("Hello, world\n");
     return 0;
   }
   ```

  Tryck `C-x,C-s` för att spara.
6.  För att kunna köra programmet måste vi kompilera det. Låt oss
  pröva att göra det inifrån Emacs. Vi måste nu utföra ett så
  kallat utökat kommando: `M-x compile`. Dessa symboler betyder
  tryck på meta-tangenten och skriv sedan `compile` och tryck på
  enter. Notera att vid `M-x` så flyttas fokus ned till den sk
  "minibuffern" längst ned på skärmen.

  Emacs föreslår nu att kompilera filen med kommandot `make -k`.
  Det fungerar inte ännu på grund av att det inte finns en s.k.
  Makefil, vi skall bygga en sådan senare. Ersätt kommandot med
  `gcc foo.c` (där `foo.c` alltså är vad du döpte filen
  till). Tryck sedan enter.

  När du gjort detta bör programmet ha kompilerats och Emacs
  öppnar en ny buffer som meddelar detta eller visar eventuella
  felmeddelanden.

  Notera att Emacs har stöd för automatisk komplettering av
  kommandon med `<tab>` (tabtangenten). Om du skriver `compi` och
  trycker `<tab>` `<tab>` så kommer Emacs att visa alla utökade
  kommandon som börjar med `compi`. Om det bara finns ett
  alternativ räcker det med att trycka `<tab>` en gång så skriver
  Emacs resten av kommandot själv. Du kan pröva detta med t.ex.
  `M-x` `auto-f` `<tab>` som bör expandera till `auto-fill-mode`
  (Med detta läge påslaget radbryter Emacs i textfiler. Detta är
  inte så vettigt i programkod så slå av det igen med `M-x
  auto-fill-mode` om du har slagit på det!). Tryck sedan `<return>`
  för att utföra kommandot.

7. Lås oss köra programmet. Det kan vi göra genom att göra `M-!`
  `./a.out` `<return>`. Nu bör texten "Hello, world" visas i
  minibuffern.

8. Ett annat sätt att köra programmet är att starta en terminal
  inuti Emacs. Kommandot `M-x eshell` gör detta och du hamnar i den
  aktuella katalogen. Nu kan du skriva `./a.out` för att köra
  programmet och se resultatet utskrivet precis som på en vanlig
  terminal.

9. Fortfarande i eshell, pröva att skriva `grep puts foo.c`.
   Kommandot `grep` listar alla rader i en fil som innehåller ett
   visst ord (i detta fall "puts") men när du kör det i eshell
   visas output i en särskild Emacs-buffer där varje rad är
   klickbar och tar dig till rätt rad i filen i fråga. Navigera på
   detta sätt till raden där "Hello, world" skrivs ut i `foo.c`
   och ändra till ett annat meddelande. Kompilera om enligt ovan.
   För att köra programmet igen, tryck `C-x b` för att byta till
   en annan buffer. Emacs föreslår den senaste aktiva buffern, men
   skriv `*eshell*` (minns att du kan använda `<tab>`) och tryck
   enter för att komma dit igen. Du kan använda uppåtpilen för att
   navigera tillbaka till kommandot `./a.out` och köra det igen
   och se det nya meddelandet.

10. Nu skall vi pröva några enkla kommandon:
  1. Pröva att trycka mellanslag framför `return` i din
    `.c`-fil och tryck `<tab>`. Vad händer?
  2. Skapa en ny buffer `C-x, b` `temp`
    `<return>`. Skriv följande (observera användandet av små och stora bokstäver):

    ```
    hej Hopp sköna min
    Vi skall dansa i det gröna
    ```

  3. Placera markören på `h` i `hej` och tryck `M-c`. Vad händer?
  4. Tryck sedan `M-l` och sedan `M-u`. Vad händer?
  5. Tryck sedan `M-t`. Vad händer?
  6. Om vill ångra någon ändring, pröva `M-x` `undo` `<return>`.
  7. Gå till början av denna rad med `C-a` (`C-e` går till slutet av raden).
  8. Gå till nästa rad genom att trycka `C-n` eller nedåtpil.
  9. Byt plats på raderna genom att trycka `C-x,C-t`.
  10. Om du vill veta mer om vad ett kommando gör, pröva
    `C-h,k` och tryck sedan kortkommandot så visas en
    förklaring, samt hur man kan köra kommandot med hjälp av
    `M-x`.
  11. Det omvända fungerar också, ta reda på kortkommandot för
    `undo` genom att trycka `C-h,f` `undo` `<return>`.

11. Emacs kan betydligt mer spännande textmanipulering. Titta
  t.ex. här (YouTube-länkar):
  * [Multiple Cursors Mode](https://www.youtube.com/watch?v=jNa3axo40qM)
  * [Yasnippets](https://www.youtube.com/watch?v=dlDvDNnsYr4)

12. Låt oss så till sist göra några inställningar i Emacs som är
  persistenta mellan körningar. Nu vill vi skapa filen
  `.emacs.d/init.el`. Det kan vi göra t.ex. så här:

  1. `C-x,C-f` `~/.emacs.d/init.el` `<return>`
  2. `M-x` `make-directory` `<return>` `<return>`

  I den tomma filen, skriv sedan:

  ```lisp
  (menu-bar-mode -1)
  (tool-bar-mode -1)
  (scroll-bar-mode -1)
  ```

  Detta kommer att **stänga av** scrollbar (aka rullningslistorna),
  verktygsfältet och menyraden i Emacs så att det ser ut som i
  kursens screencasts.

  Du behöver dock inte stänga av Emacs och starta om det för att
  ladda dessa inställningar. Istället kan du köra:

  * `M-x` `eval-buffer` `<return>`

  Voila!

### Att ta med sig:
* Emacs är din vän
* Man kan göra oerhört kraftfulla texttransformationer med Emacs
* Var rädd om dina handleder -- undvik att hoppa mellan tangentbord och
   mus, och försök att hålla dina fingrar på "home row" så mycket
   som möjligt
