# Föreläsning 8

* [Bilder](f8.pdf) (pdf, publiceras 2015-09-20)


# Vad du kan göra själv

**OBS! "Vad du kan göra själv-delarna av en föreläsning är på
inget sätt obligatoriska. Många studenter ber om övningar att 
göra själva på kammaren. Detta är vårt försök att möta detta.**

Under föreläsningen tittade vi på [stack.c](stack.c) och
[stack.h](stack.h) och hur man kunde testa dem. Vi såg att två
viktiga test hade utelämnats, nämligen

* stack underflow
* stack overflow

Det första sker när man försöker ta något från en tom stack. Det
sista sker när man försöker lägga till något på en stack som är
full. Notera att stackens maxstorlek var "hårdkodad" till 1024
element.

Vi tittade på [CUnit](http://cunit.sourceforge.net/doc/) och såg
på eller körde några tester som fanns givna för stacken. **Vad du
kan göra själv är att** utöka testprogrammet
[stack_test.c](stack_test.c) med två tester som fångar underflow
och overflow. Istället för att använda [stack.c](stack.c) som (med
viss sannolikhet) kraschar för dessa två fel, använd istället
[stack2_0.c](stack2_0.c) och [stack2_0.h](stack2_0.h) där `pop`,
`top` och `push` utökats med defensiv kod som undviker kraschar. 


# Att kompilera separat

Vi använder separatkompilering (se bl.a. [föreläsning 4](../L4/))
för separera ett litet program [driver.c](driver.c) från
stack-modulerna och testprogrammet. För att kompilera
[driver.c](driver.c) mot [stack.c](stack.c) (som kraschar), kör:

```
$ gcc -o bad driver.c stack.c
```

För att kompilera [driver.c](driver.c) mot
[stack2_0.c](stack2_0.c) (som inte kraschar), kör:

```
$ gcc -o good driver.c stack2_0.c
```

Notera att du måste editera [driver.c](driver.c) och se till att
rätt **headerfil** inkluderas innan du kompilerar, samt ändra
några av anropen eftersom några av funktionerna i
[stack2_0.c](stack2_0.c) har ett extra argument. (Gör det gärna
själv, men för att spara litet tid har jag förberett en
[driver2_0.c](driver2_0.c) redan, som används av
[Makefilen](Makefile) som du gärna får använda om du vill.)

Beroende på inställningarna på din dator kan du behöva lägga till
`-std=c11` för att inte kompilatorn skall klara på `for`-looparna.

# Så här kör du bad/good efter att du har kompilerat som som ovan

Programmen pushar så många argument som du har på stacken, och
tar sedan bort dem med pop. Om ett argument är negativt så görs
en pop. Alltså:

```
$ ./bad 1 2 3 4 5 6 7
7
6
5
4
3
2
1
```

Eller:

```
$ ./bad 1 2 3 4 5 6 7 -1
6
5
4
3
2
1
```

Eller:

```
$ ./bad 1 2 3 4 5 6 7 -1 -1 -1
4
3
2
1
```

Eller:

```
$ ./bad 1 -1 2 -1 3 -1 4 5 6 7
7
6
5
4
```

Eller:

```
$ ./bad 1 -1 2 -1 3 -1 4 5 6 7 -1 -1 -1 -1
(ingen output)
```


# Att kompilera med CUnit

För att kompilera testprogrammet måste du explicit ange att
biblioteket som innehåller alla funktioner i CUnit skall
inkluderas i programmet. Det gör du genom att ange flaggan
`-lcunit` vid kompileringen, som stå för ladda (`-l`) cunit.
Observera att det skall vara i ett enda ord. 

```
$ gcc -o stack_test stack_test.c stack.c -lcunit
```

