# Föreläsning 3

* [Bilder](f3.pdf) (pdf, uppdaterade 2015-09-04)
* [Screencast av delar som inte hanns med](http://youtu.be/dqlX-dH_suk)

Se även:
* [Tidigare screencasts](https://github.com/IOOPM-UU/ioopm15/tree/master/extramaterial/screencasts/fas1#screencasts-till-föreläsning-3) -
  Screencasts om strängar och `printf`/`scanf`.
* [Kom-igång-uppgiften](https://github.com/IOOPM-UU/ioopm15/tree/master/uppgifter/fas1/komigang/)
  som har övningar som rör [strängar](https://github.com/IOOPM-UU/ioopm15/tree/master/uppgifter/fas1/komigang/strings#strängar-och-tecken) och [I/O](https://github.com/IOOPM-UU/ioopm15/tree/master/uppgifter/fas1/komigang/io#io)

# Utdelad kod

Se filer i denna katalog. Generellt gäller att `foo.c` var filen
vi började med, medan `foo_fixed.c` är det färdiga resultatet.
`password_getline.c` innehåller en version av `password.c` som
använder `getline` istället för `scanf`. Notera att det kräver
att man manuellt tar bort den medföljande radbrytningen.

# Vad du själv kan göra

* Implementera delar av `string.h`. Bra övningar är:
  - `strcat`
  - `strchr`
  - `strncmp`
  - `strncpy`
  - `strncmp`
  - `strspn`
  - `strnstr`

  Kör `man strcat` (etc) för att få en beskrivning av dem.

* Skriv en funktion `rovar` som tar en sträng som input och
  översätter den till rövarspråket. I rövarspråket översätts alla
  vokaler (a, e, i, o, u, å, ä och ö) till sig själva och alla
  konsonanter `c` till `c`o`c`. "Uppsala" översätts alltså tillnn
  "Upoppopsosalola". Fundera på hur lång strängen som rymmer
  rövarspråkssträngen behöver vara i jämförelse med
  ursprungssträngen! (En lämplig skarvning kan vara att ignorera
  svenska vokaler).

* Implementera (enkla versioner av) några av de vanligaste
  terminalkommandona som hanterar text. Se
  [kom-igång-uppgiften](https://github.com/IOOPM-UU/ioopm15/tree/master/uppgifter/fas1/komigang/io#io-till-filer))
  för exempel på hur man skriver/läser till/från fil, eller skarva
  och läs bara från `stdin`.
  - `echo`
  - `cat`
  - `head`
  - `tail`
  - `grep` (för vanlig strängsökning, reguljära uttryck är svårare!)
  - `wc`

  Kör `man echo` (etc) för att få en beskrivning av dem.

* Modifiera rövarspråksprogrammet så att det läser text från
  `stdin`, översätter texten till rövarspråket och skriver den
  till `stdout`.