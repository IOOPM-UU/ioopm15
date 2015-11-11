# Parallellprogrammering

Denna föreläsning introducerar parallelprogrammering och "concurrency", specifikt "task-based parallelism".

* [Bilder](f22.pdf)

## Utdelat material

* [Demo.java](Demo.java) -- visar hur man kan skapa trådar och hur trådar kör samtidigt
* [DataRace.java](DataRace.java) -- visar hur flera trådar som läser och skriver samtidigt till en gemensam variabel råkar ut för "kapplöningsproblem" (dvs. data race)
* [FJ.java](FJ.java) -- visar en implementation parallell beräkning av summor av tal i en array med Javas ForkJoin-ramverk
