# Föreläsning 2

* [Bilder](f2.pdf) (pdf, publiceras 2015-08-30)
* [Screencast av delar som inte hanns med 1/2](http://youtu.be/4w4miaUyhuA)
* [Screencast av delar som inte hanns med 2/2](http://youtu.be/S6TFKftlDp4)

Notera att det görs ett dumt misstag i film 2: jag (Tobias) stavar fel 
till "fib-iter" när jag kör med time, vilket dels leder till en direkt 
lögn (körtiden blir för kort eftersom programmet inte finns) och att 
jag misslyckas med att visa `--verbose`. **Jag premierar att få ut dessa
filmer nu över att rätta till felet.**

Kompilera programmen och gör rätt på din egen dator! 

# Utdelad kod

Se filer i denna katalog. Instruktioner för hur man kompilerar
(generellt) finns i bilderna. Se även
[föregående föreläsning](../L1/README.md).


# Vad du själv kan göra

* Skriv ett program som skriver ut arean av alla kvadrater med
  sidan [1,20].

* Skriv ett program som skriver ut n! för alla n [1,10] som
  en tabell.

* Skriv ett program som räknar ut det N:te fibonacci-talet.
  Experimentera med olika datatyper för talen: `int`, `long`,
  `long long`. De rymmer olika stora tal. Vid vilket N slutar
  programmet att fungera korrekt?
  
* Experimentera med två lösningar av fibonacci-programmet ovan: en
  imperativ (som använder en `for` loop, t.ex., se [F1](../F1))
  och en rekursiv (jmf. Haskell-implementationen på [F1](../F1)).
  Pröva att köra dem för "stora värden på N". Är det någon
  skillnad i körtid? Experimentera med att ange flaggorna `-O0`
  (bokstaven O följt av siffran O) och `-O3` till kompilatorn, för
  olika nivåer av optimering. Påverkar det prestanda?
