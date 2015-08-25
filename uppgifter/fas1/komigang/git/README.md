För en video-introduktion, see även screencast VC 1.

Versionshantering & Git
=======================

Versionshantering är en grundläggande aspekt av all
programutveckling. Enkelt uttryckt handlar versionshantering om
stöd för hantering av kataloger med filer som förändras över tid.
Förändringar loggas i ett så kallat repository, en plats där
skillnaderna mellan alla versioner av alla filer sparas så att man
kan gå fram och tillbaka i förändringshistoriken. Repo:t kan vara
en katalog på din egen hårddisk, ligga på en separat dator eller
en kombination. Loggningen sker löpande, manuellt av
programmeraren, med förklarande loggmeddelanden. Vid behov kan man
återskapa gamla versioner av filer (t.ex. för att återuppliva en
bit kod som man trodde att man kunde ta bort, eller gå tillbaka
till en fungerande version av en funktion). Eftersom
versionhanteringssystemet kommer ihåg allt kan man hålla rent och
snyggt i sitt program -- vid behov kan det återskapas. Loggfilen
är viktig för att kunna spåra förändringar och för att navigera
bakåt i historiken. Här är t.ex. en bit av loggarna för kursrepot
när det skapades 2015:

```
d933200 * Stubs för uppgifterna i fas 1
36224c6 * Lade till .gitignore för emacs temp-filer
42b2308 * Lathundar från gamla repot
d63b99c * Initial commit
```

Viktigt är att versionhanteringssystem tillåter
programmerare att ha varsin lokal kopia av alla filer i ett
program och få automatiskt stöd för att slå ihop förändringar som
gjorts parallellt i olika kopior av samma fil, etc. Ett sätt att
samarbeta distribuerat utan behov av att det finns en speciell
"masterkopia".

I denna enkla instruktion till Git kommer vi att skapa två
repositorys med inställningar för Emacs och länka samman dessa
repositorys så att man enkelt kan kopiera information mellan dem
och på så sätt hålla dem synkroniserade.

1. I ett terminalfönster (t.ex. eshell i Emacs), placera dig i
  din hemkatalog genom att köra kommandot `cd`
2. Gå in i katalogen `.emacs.d` med kommandot `cd .emacs.d`
3. Initiera denna katalog som ett tomt repo med `git init`
4. Markera att `init.el` som du tidigare skapat skall
   versionshanteras med `git add init.el`. Filer som inte explicit
   markeras för versionshantering kommer att ignoreras av
   systemet. **Notera att du måste markera `init.el` för
   versionshantering varje gång du vill checka in en förändring
   till denna fil!**
5. Checka in den nuvarande `init.el` i repot med `git
    commit -m "Initial commit"`. Nu är filen incheckad och sparad.
6. Editera nu `init.el` lägg till en ny textrad "; Kortlivad". Nu
   skall vi undertrycka denna ändring genom att återskapa filen
   från repot med `git checkout init.el`. Verifiera att texten ";
   Kortlivad" har försvunnit. OBS! Om filen är öppen i Emacs måste
   du göra `M-x revert-buffer` för att läsa in filen på nytt från
   disk eftersom Emacs håller filens innehåll i minnet.
7. Titta på loggen för `init.el` med `git log init.el` eller `git
   log` som visar hela loggen (ekvivalent eftersom det bara finns
   en fil för närvarande).
8. Gissningsvis är ni två som gör detta (*B*onnie och *C*lyde),
  men alla ändringar och filer finns nu bara hos en person (*C*).
  I detta steg skall vi försöka råda bot på detta med hjälp av
  Git.

  Öppna ett nytt terminalfönster och byt aktuell användare för
  detta fönster till *B* genom att logga in på någon dator vid IT
  med hjälp av SSH, t.ex. `ssh abcd1234@celsius.it.uu.se` där
  `abcd1234` ersätts med *B*s användarnamn. Hädanefter refererar
  vi till det fönster där *B* är inloggad som "*B*" och det
  fönster där *C* är inloggad som "*C*". Ställ båda dessa fönster
  i katalogen `.emacs.d` (t.ex. med `cd; cd .emacs.d`).

  I *C*, kör kommandot `pwd` som skriver ut den absoluta sökvägen
  till den aktuella katalogen. **OBS!** För att denna övning skall
  fungera krävs att *B* har läsrättigheter till katalogen som
  innehåller *C*:s git-repo, och tvärtom. Om problem med
  filrättigheter uppstår, pröva: `chmod 711 ~; chmod -R a+r
  ~/.emacs.d`. Om git-repot (i detta fall `.emacs.d`) **inte**
  ligger direkt under din hemkatalog (`~`), utan t.ex. i
  underkatalogerna `~/foo/bar/.emacs.d` måste du också göra `chmod
  a+x ~/foo` och `chmod a+x ~/foo/bar` i anslutning till
  föregående kommandon.

  I *B*, kör kommandot `git clone dir` där `dir` är sökvägen
  ni nyss fick ut. Detta klonar (kopierar) all information om repot från *C*
  till *B*. Så skapas alltså en katalog `.emacs.d` även hos
  *B*. Gå in i denna katalog med `cd .emacs.d` och lista
  filerna med `ls -l` för att kontrollera att de är där.

  Kör `emacs -nw` för att starta upp en icke-grafisk instans
  av Emacs i *B*. Om rullningslistor, meny och verktygsrad inte
  syns har inställningarna lästs in som avsett. Öppna
  `init.el` på nytt och lägg till följande:

  ``` lisp
  ;; Turn off annoying splash screen
  (setq inhibit-splash-screen t)
  ;; Turn on line number and column number modes
  (column-number-mode t)
  ;; Turn on parenthesis mode
  (show-paren-mode t)
  ```

  Kör nu `git add init.el` för att markera att du kommer vilja
  checka in ändringarna i filen, och utför sedan incheckningen med
  `git commit -m "Some additional essential settings"`. Nu är den
  nya revisionen incheckad hos *B* men inte hos *C*. För att göra denna
  ändring synlig hos *C*, har vi två möjligheter.

  * [Alt 1.)] *B* "knuffar" över ändringar med `git push`.
    Detta alternativ är du kanske bekant med om du använt t.ex.
    Subversion eller CVS förut, men detta kräver att man initierar
    sitt git-repo på ett speciellt sätt som inte är lika enkelt.
    **Därför väljer vi istället alternativ 2.**

  * [Alt 2.)] *C* "drar" över ändringar med `git pull dir` där
    `dir` är sökvägen till *B*'s repo.

9. Varför behövs ett `dir`-argument om *C* ska dra med `pull` men
  inte om *B* ska knuffa med `push`? Gör `cat .git/config` i *B*
  -- där finns informationen om var repot är klonat från och det
  är denna information som läses när man gör `push` (eller
  `pull`). Motsvarande information saknas dock i *C*. För att
  enkelt kunna dra information från varandras repon utan att
  manuellt ange sökväg varje gång måste man lägga till en
  motsvarande fil hos *C*. Gör det med hjälp av Emacs och skriv av
  *B*s fil från grunden, men ändra sökvägen som står efter `url`
  så att den går till *B*s repo istället.

10. Experimentera med att göra simultana förändringar i `init.el`,
    checka in och dra. Under vilka omständigheter kan Git räkna ut
    hur flera versioner av en fil enkelt kan slås samman, och
    under vilka omständigheter kommer den anse att filerna är "i
    konflikt"?

    Lös eventuella konflikter manuellt i Emacs, eller prova att köra
    `git mergetool ----tool emerge` för att öppna Emacs i ett
    speciellt git-konflikt-läge. Läs också på nätet vid behov.

11. Emacs innehåller ett fantastiskt stöd för Git i form av magit.
    Vidare läsning om magit finns på nätet, inklusive många bra
    video-tutorals.

### Att ta med sig
* Git är din vän
* Versionshantering är ett kraftfullt verktyg för att samarbeta med text
* Möjligheten att återskapa filer och ångra stora ändringar över många filer är en livräddare många gånger

Nu är det dags att klona kursens repo. URL:en hämtas fram i [nästa uppgift](../terminal).