Att spåra minnesläckage
=======================

Programmet `valgrind` är ett program som kan hjälpa till att hitta
minnesfel i ett program. För att komma åt det i datorsalarna måste
man logga in på en av Linux-maskinerna. Kommandot `linuxlogin`
öppnar en terminal på en maskin som har lediga resurser. Du kan
också logga in manuellt med kommandot `rsh` följt av en av
adresserna nedan.

* `tussilago.it.uu.se`
* `vitsippa.it.uu.se`
* `gullviva.it.uu.se`

Du kommer ha tillgång till din hemkatalog och alla kataloger du
kan nå vanligtvis. Du behöver alltså inte skicka några filer
mellan maskinerna.

Läs på om Valgrind på Internet eller med hjälp av man-sidor i
terminalen (på Linux-maskin). Hitta informationen med hjälp av
Google. Försök att besvara följande frågor:

* Vilken typ av fel kan `valgrind` hitta?
* Vilken typ av fel kan `valgrind` inte hitta?
* Kan `valgrind` rapportera s.k. ``false positives'' alltså
  rapportera något som ett läckage som faktiskt inte är ett
  läckage?
* Hur kör man `valgrind`?

Kör nu `valgrind` på ert program från
[uppgiften om `malloc`](../malloc) och se om du hittar några fel.
Tyd utskrifterna från programmet och laga alla eventuella fel.
Fortsätt tills inga läckage rapporteras.

### Att ta med sig
* `valgrind` (eller motsvarande program) är din vän!
* Ca 40% av alla fel som görs i C-program har att göra med
  hantering av minnet
* Använd `valgrind` regelbundet utöver kompilatorn och
  enhetstester för att hitta fel under utveckling!
