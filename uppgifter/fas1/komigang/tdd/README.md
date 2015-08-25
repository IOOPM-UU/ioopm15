Testdriven utveckling och parprogrammering
==========================================

1. Testdriven utveckling (TDD) är ett sätt att programmera som
  utgår från skapandet av tester. En grov förenkling är denna: När
  man skall lägga till en funktion i ett program börjar man med
  att skapa ett eller flera tester för funktionen och fångar
  därigenom funktionens specifikation. Målet blir sedan att
  implementera funktionen så att testerna passerar utan fel,
  varefter man kan fortsätta till nästa funktion.

  Vi uppmuntrar testdriven utveckling på denna kurs av flera
  anledningar. Bland annat för att fånga en specifikation i ett
  test är att bra sätt att driva fram alla specialfall (läs gärna
  Minskys klassiker "Why Programming is a Good Medium for
  Expressing Poorly Understood and Sloppily­Formulated Ideas").
  Att använda testdriven utveckling är ett **krav** under
  projektet i Fas 2.

  Från och med nu, använd TDD för resten av denna fas.

2. Parprogrammering är ett enkelt sätt att bygga in granskning
  av kod och därmed förhöjd kodkvalitet i ett projekt som en del
  av utvecklingsprocessen. På denna kurs kommer vi att tillämpa
  parprogrammering hela tiden och specifikt en modell där en
  person är *driver* och den andre *co-pilot*. Dessa två
  roller växlar fram och tillbaka mellan medlemmarna i ett par
  flera gånger varje timme.

  Driver är den som sitter vid tangentbordet. Co-pilot sitter
  brevid och läser allt som Driver gör, och ser till att fånga
  alla småfel som Driver naturligt gör i sin iver att komma vidare
  i implementationen. Det kan vara namngivning, att bryta ut
  upprepningar till en separat funktion, snygga till en bit
  oläslig kod, etc. Driver får inte skriva kod som Co-pilot inte
  förstår. Det är inte meningen att Co-pilot skall sitta overksam
  och tyst, utan all kod skrivs med fördel under dialog.

  Från och med nu, använd parprogrammering under resten av kursen.
  Diskutera rollerna så att de är klara för er.

3. I kombination med TDD tillämpar vi nu en modell där vi växlar
  roller (Driver blir Co-pilot och vice versa) i samband med att
  vi byter mellan att skriva test och faktisk implementation. Det
  är inte meningen att en person skall skriva alla tester och en
  annan person all implementation, men samma person som skrev
  testet bör inte skriva koden som skall passera testet
  (varför?!).

  När ni bryter ned en uppgift i små beståndsdelar, försök hitta
  delar som är små nog att ta max 10 minuter att göra så att det
  blir många byten mellan att skriva test och implementation varje
  timme. Detta är givetvis svårt, speciellt i början -- och det
  kan vara en mycket god idé att ställa en klocka på 10 minuter
  och byta roller när den ringer så att det blir en bra balans
  mellan att vara Driver och Co-pilot för alla inblandade.

### Att ta med sig

* Parprogrammering tenderar att skapa kod av högre kvalitet
   fortare än "ensamkodning"
* Använd parprogrammering med klara roller (t.ex. skriva
  testkod/skriva programkod) och byt ofta.
