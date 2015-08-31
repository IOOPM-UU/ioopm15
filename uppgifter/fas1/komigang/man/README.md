Att läsa manual-sidor
=====================

"man-sidor" är smeknamn på "manual-sidor" som är dokumentation och
hjälpsidor för de verktyg och bibliotek vi använder i kursen.  Om du vill läsa
dokumentationen till programmet `passwd` för att söka efter hjälp skriver du:

```
    foo> man passwd
```

Då öppnas en textfil som beskriver `passwd`. Filen visas i verktyget
`less` eller `more`. Du kan navigera upp och ner genom tangenterna `k` respektive
`j` eller med piltangenterna. Tryck `q` för att avsluta och återgå
till terminalen.

Man-sidor är skrivna efter en mall. Detta gör det lättare att leta
efter exempel, beskrivningar av argument till programmet etc.
Några sådana avsnitt är: Namn (Name), sammanfattning (Synopsis),
beskrivning (Description) och argument (Options).

Om du läser man-sidan för `passwd` igen ser du att det står
PASSWD(1) högst upp till vänster. Det finns flera man-sidor för
kommandot `passwd` som beskriver andra delar av programmet, prova
att skriva `man 5 passwd`, vad beskriver den sidan som inte `man 1
passwd` gör? Du ser om en man-sida har flera sidor genom att söka
efter avsnittet "SEE ALSO". Öppna man-sidan för `printf`, tryck
`/` skriv "SEE ALSO" eller bara "SEE" och trycker `<return>`.
Vilken mer man-sida finns för sökordet "printf"? En man-sida
beskriver terminal-commandot `printf`; det andra
C-bibliotekfunktionen "printf". Titta på exemplen i man-sidan för
C-bibliotekfunktionen "printf" (Sök efter "EXAMPLE" enligt ovan).

Du kan också läsa manual-sidor i Emacs (och då följa länkar genom
att trycka `Enter` när markören står på ett nyckelord). Kommandot
är `M-x man`, följt av det kommando man vill läsa mer om, till
exempel `M-x man` `<return>` `printf` `<return>`.
