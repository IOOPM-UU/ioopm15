# Föreläsning 7

* [Bilder](f7.pdf) (pdf, publiceras 2015-09-13)

Denna föreläsning hänger samman med [föreläsning 5](../L5/) och
handlar också om dynamiskt minne och pekarhantering. Vi demonstrerar
`realloc` och `calloc` som komplement/alternativ till `malloc`.


# Vad du kan göra själv

**OBS! "Vad du kan göra själv-delarna av en föreläsning är på
inget sätt obligatoriska. Många studenter ber om övningar att 
göra själva på kammaren. Detta är vårt försök att möta detta.**

Den dynamiska arrayen som presenteras på föreläsningen använder
både pekarsemantik och värdesemantik. Se till att förstå vilket
som används var och varför. Du kan med fördel experimentera genom
att ändra i koden och se vad som händer.


## Modularisera programmet

Programmet [dyn_driver.c](dyn_driver.c) använder arrayen. Det
förutsätter att det finns en fil `dyn_array.h` med
funktionsprototyperna, typedef:ar och struktdefinition från
`dyn_array.c`. Skapa denna fil (se föreläsning 4 för
instruktioner, ev. läs på om header-filer) så att du kan kompilera
programmet.


## Fixa ett minnesfel

När du kör programmet `dyn_driver` kommer du kanske (beroende på
din dator etc.) att märka att användandet av `realloc` inte är
superbra -- det fyller arrayen med skräpdata. Uppdatera programmet
så att `append` och `prepend` nollställer det nya minnet minnet
(alltså tilldelar `0` till det som allokeras). Se till så att du
inte skriver över något av det existerande datat!


## Förstärk inkapslingen

Flytta definitionen av strukten från headerfilen till c-filen. För
att `dyn_driver.c` fortfarande skall gå att kompilera måste du
ändra så att modulen `dyn_array.h` endast använder pekare till
arrayer. Anledningen till detta är för att C måste veta hur stor
en `dyn_array_t` är för att kunna lagra den i en stack-variabeln,
men när strukten flyttats från headerfilen till C-filen är det
bara funktionerna i C-filen som vet hur stor en `dyn_array_t` är.
Eftersom storleken på en pekare alltid är känd (den är samma
oavsett vad som pekar ut!) så fungerar det om du ändrar
signaturerna på alla funktioner i header-filen från `dyn_array_t`
till `dyn_array_t *`. Du måste ändra alla funktioner i C-filen
likadant! 


## Void-pekare

Filen [dyn_array_generic.c](dyn_array_generic.c) innehåller en
version av programmet som kan peka ut godtyckligt data. Om du
känner dig manad kan du fundera över hur *funktionspekare* kan
användas för att:

1. Se till att arrayen äger sina element (dvs. skapa en egen kopia av dem som pekas ut)
2. Frigöra kopiorna utan minnesläckage



