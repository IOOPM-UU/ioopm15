Terminalhantering
=================

När man är van vid en grafisk filhanterare (som Finder i Mac OSX
eller Explorer i Windows) kan det verka omständigt att lära sig
använda terminalen. Många känner sig tryggare när de kan se
allting som ikoner och klicka med musen, och så länge det enda man
gör är att öppna och kanske flytta enstaka filer så är lidandet
begränsat. Men när man ska göra mer avancerade saker så är
terminalen ett ovärdeligt verktyg!

Tänk dig till exempel att du har en mapp med 100 mappar som
*bland annat* innehåller mp3-filer och att du skulle vilja
flytta alla dessa till en egen mapp. I ett grafiskt
användargränssnitt skulle du behöva gå in i varje mapp separat,
markera alla mp3-filer och dra över dem till den nya mappen. Innan
du är klar med den första mappen så är någon som kan använda
terminalen redan klar genom att ha skrivit (Vi använder
konsekvent `foo>` för att representera terminalprompten. Det
är alltså ingenting du skall skriva själv.)

```
foo> mv */*.mp3 music/
```

Innan du är klar med den andra mappen har terminalfantomen redan
utmanat dig till att hitta hårddiskens alla textfiler som innehåller
ordet "choklad". Du hinner knappt uppfatta frågan innan hen har
skrivit

```
foo> find / -type f -name "*.txt" | xargs grep -l choklad
```

**OBS! Oroa dig inte om du inte förstår de här kommandona än!**

Terminalfantomen vill utmana dig igen, men du har fattat poängen och
lovar dig själv att du ska lära dig att använda terminalen.

### Att navigera och söka bland text och filer

Nu ska vi prova på att använda terminalen för att hitta en
specifik rad text bland en massa filer som ligger i en enda röra.
Texten vi letar efter är URLen för kursens repo (du får låtsas att
du inte bara kan kopiera den från adressfältet)!

1. Börja med att öppna en terminal (om du inte redan har en öppen)

2. Ta reda på vilken mapp du befinner dig i med kommandot `pwd`
  (som står för **print working directory**).

  ```
  foo> pwd
  /home/abcd1234
  ```

3. Med `cd` (*change directory*) byter du mapp till det
  som står efter kommandot. Om du inte skriver någonting efter
  `cd` hamnar du i din hem-mapp. Vi ska dock till följande mapp:

  ```
  foo> cd /it/kurs/imperoopmet/labyrinth
  ```

  Kom ihåg att du nästan alltid kan använda `<tab>` för att
  komplettera något du har skrivit eller se vilka alternativ som
  finns. Till exempel behöver du inte skriva ut ordet "labyrinth",
  det räcker med att skriva "lab" och trycka `<tab>`.

  Någonstans i den här labyrinten finns URLen vi letar efter. Med
  hjälp av terminalen ska vi hitta den!

4. Kommandot `ls` listar alla filer i mappen du befinner dig i.

  ```
  foo> ls
  east        north       rK8Mmp      south       VEN0z1.txt  west
  ```

  Man kan också lista alla filer i en eller flera andra mappar

  ```
  foo> ls north
  east        n6qlnh      south       Y24dr8
  N53t2F.txt  north       west
  foo> ls north south
  north:
  east        n6qlnh      south       Y24dr8
  N53t2F.txt  north       west

  south:
  east        north       sZh7pv.txt  west
  FPh8zv.txt  south       UM9BvA      X0UwPV.txt
  ```


5. I alla mappar finns två namn som är speciella. Namnet `.`
  betyder "mappen jag står i" och `..` "mappen ovanför den jag
  står i". Gå till mappen `north/west` och lista innehållet i den
  mappen.

  ```
  foo> cd north/west
  foo> ls
  9RlYdp.txt   laKnns.txt   P6roYu.txt   READMETHREE  south
  east         north        README       READMETOO    west
  ```

  Använd `cat` för att visa innehållet i `README`. Använd
  sedan `cd ../..` för att komma tillbaka för att komma tillbaka
  till mappen labyrinth.

6. Det finns finns det väldigt många filer under
  `labyrinth`. För att se precis hur många filer kan du prova
  kommandot `find .` som listar alla filer under sitt första
  argument (här "`.`", alltså mappen vi står i).

7. Som namnet antyder kan `find` användas för att hitta
  filer. Vi ska nu begränsa vilka filer `find` visar. Till att
  börja med vill vi ange att vi bara är intresserade av "vanliga
  filer" och inte till exempel mappar:

  ```
  foo> find . -type f
  ...
  ```

  Hade vi skrivit `find -type d` hade vi istället bara visat
  mappar (directories).

8. Nu ska vi dessutom ange att vi bara är intresserade av filer som
  slutar på "`.txt`":

  ```
  foo> find . -type f -name "*.txt"
  ...
  ```

  Stjärnan är ett så kallat *wildcard* som betyder "vad som
  helst".

9. Ett väldigt kraftfullt verktyg i terminalen är möjligheten att
  koppla ihop flera kommandon. Det gör man med symbolen `|`, som
  kallas "pipe". Kommandot `find` producerar en lista med
  filnamn. Prova att skicka den listan till kommandot `wc`
  (*word count*) för att se hur många rader listan består av:

  ```
  foo> find . -type f -name "*.txt" | wc -l
      519
  ```

  Flaggan `-l` anger att vi bara är intresserade av antalet rader
  (och inte antalet ord och tecken, som `wc` också visar annars).

10. Om vi istället vill ge varje rad i listan som `find`
  producerar som argument till `wc` använder vi kommandot
  `xargs`. `xargs` tar ett annat kommando som argument och
  väntar sedan på input att mata till kommandot. För att räkna antalet
  rader i varje enskild fil skriver man så här:

  ```
  foo> find . -type f -name "*.txt" | xargs wc -l
  ...
  ```

  För att skriva ut alla filer som `find` hittar använder vi
  `xargs` med `cat` som argument:

  ```
  foo> find . -type f -name "*.txt" | xargs cat
  ...
  ```

  Nu kan vi alltså läsa alla textfiler i labyrinten, men det är
  fortfarande väldigt mycket text att gå igenom för hand (lägg till
  `| wc -l` till ovanstående kommando för att se hur mycket!).

11. Kommandot `grep` används för att söka efter en textsnutt i
  en fil. Skriver man `grep foo file.txt` så visas alla rader i
  filen `file.txt` som innehåller teckenföljden `foo`. Eftersom
  vi är intresserade av att hitta en URL så ber vi `grep` leta efter
  "http" i alla filer som `find` hittar:

  ```
  foo> find . -type f -name "*.txt" | xargs grep http
  ...
  ```

12. Nu är det "bara" 1014 rader att gå igenom (istället för
  51960), men vi ska förfina sökningen ytterligare en sista gång.
  Eftersom vi använder Git för kursens repo kan vi söka efter det
  ordet i vår resultatslista genom att använda `grep` igen. Vi
  lägger också till flaggan `-h` på den första förekomsten av
  `grep`, som gör så att `grep` inte skriver ut vilka filer
  resultaten kommer ifrån:


  ```
  foo> find . -type f -name "*.txt" | xargs grep -h http | grep git
  https://github.com/IOOPM-UU/ioopm15
  ```


13. Success! Gå nu tillbaka till din hemkatalog (kommandot `cd`)
  och checka ut kursens repo. Eftersom
  [Gits egna protokoll](http://git-scm.com/book/en/Git-on-the-Server-The-Protocols)
  är något snabbare kommer vi använda det istället för `https`:

  ```
  foo> cd
  foo> git clone git://github.com/IOOPM-UU/ioopm15
  ```

  Nu borde du ha en mapp som heter `ioopm15` i din hemkatalog. Ta
  och utforska den med dina nya terminalkunskaper! Om du stöter på
  en PDF som du vill läsa kan du öppna den med kommandot `evince
  file.pdf &` (byt ut `evince` mot `acroread` om du sitter på en
  äldre maskin).

Som du säkert förstår går det att göra mycket, mycket mer i
terminalen (titta på man-filerna för de här få kommandona för att
få en uppfattning av hur stora möjligheterna är, se
[avsnitt om man-sidor](../man)). Var inte rädd att googla eller
fråga om du kommer på något du skulle vilja göra i terminalen. Ju
mer du håller på desto mer naturligt kommer det kännas!

### Don't fear the void!
Det kan också vara bra att veta terminalprogram som inte är gjorda för
att skriva ut saker oftast bara gör ljud (alltså text) ifrån sig när
något har blivit fel. Om du till exempel ska kopiera tusentals filer
och du får upp en ny prompt utan något meddelande så har det alltså
förmodligen lyckats.

Vill man lära sig mer om terminalen finns det gott om resurser på
Internet. Se (till exempel)
http://linuxcommand.org/learning_the_shell.php för en mer utförlig
genomgång.

### Att ta med sig:

* Terminalen är din vän
* Ett interaktivt terminalgränssnitt är oerhört kraftfullt för interaktion med ett filsystem eller ett helt operativsystem
* Försök att automatisera arbetsflöden genom att skriva sekvenser av kommandon i en fil, ett så-kallat "shell script"
