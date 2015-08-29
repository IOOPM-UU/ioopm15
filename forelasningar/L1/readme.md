# Föreläsning 1

* [Bilder](f1.pdf) (pdf, publiceras 2015-08-31)


## Utdelad kod

### Hello, world

```c
#include<stdio.h>

int main(int argc, char *argv[])
{
  puts("Hello, world!");
  return 0; 
}
```

Kompilera och kör så här: (`$` är prompten)

```
$ gcc -o hello hello.c
$ ./hello
Hello, world!
$ _
```

### Greeter

```c
#include <stdio.h>

int main(int argc, char *argv[])
{
  if (argc < 2)
    {
      puts("Usage: ./greeter <name>");
    }
  else
    {
      printf("Hello, %s!\n", argv[1]);
    }
  return 0; 
}
```

Kompilera och kör så här: (`$` är prompten)

```
$ gcc -o greeter greeter.c
$ ./greeter Tobias
Hello, Tobias!
$ _
```

### Program som skriver ut en fil på skärmen 

```c
#include <stdio.h>

int main(int argc, char *argv[])
{
  if (argc < 2)
    {
      puts("Usage: ./mycat <name>");
    }
  else
    {
      FILE *f = fopen(argv[1], "r");
      int c = 0; 
      while ((c = fgetc(f)) != EOF)
	{
	  putchar(c);
	}
    }
  return 0; 
}
```

Kompilera och kör så här: (`$` är prompten)

```
$ gcc -o mycat mycat.c 
$ ./mycat hello.c
#include<stdio.h>

int main(int argc, char *argv[])
{
  puts("Hello, world!");
  return 0; 
}
$_
```

### Sök efter förekomster av strängar i en fil 

```c
#include <stdio.h>
#include <string.h>

int main(int argc, char *argv[])
{
  if (argc < 2)
    {
      puts("Usage: ./mygrep <pattern> <name>");
    }
  else
    {
      FILE *f = fopen(argv[2], "r");
      int str_len;
      size_t buf_siz;
      char *string; 
      char *pattern = argv[1];
      
      while ((str_len = getline(&string, &buf_siz, f)) > 0)
	{
	  if (strnstr(string, pattern, str_len))
	    printf("%s", string);
	}

      fclose(f);
    }
  return 0; 
}
```

Kompilera och kör så här: (`$` är prompten)

```
$ gcc -o mygrep grep.c
$ ./grep Hello hello.c
```

Nu skrivs alla rader ut i `hello.c` som innehåller texten "Hello". 


### Fibonacci

```c
#include <stdio.h>

int main(int argc, char *argv[])
{
  int acc1, acc2, temp;

  acc1 = 0;
  acc2 = 1;
 
  const int n = 15; // <---- ÄNDRA DENNA RAD för att ändra vad programmet skall räkna ut

  for (int i = 0; i < n; ++i)
    {
      temp = acc2; 
      acc2 += acc1;
      acc1 = temp;
    }

  printf("fib(%d) = %d\n", n, acc1);

  return 0; 
}
```


Kompilera och kör så här: (`$` är prompten)

```
$ gcc -std=c11 -o fib fib.c 
$ ./fib 
fib(15) = 610
$ _
```


# Vad du kan göra själv

* Sätta igång med din egen [planering](http://wrigstad.com/ioopm/agile.php)!
* Gör [kom igång-uppgiften](https://github.com/IOOPM-UU/ioopm15/tree/master/uppgifter/fas1/komigang#kom-igång-med-c)
* Bekanta dig med [Piazza](http://piazza.com/uu.se/fall2015/1dl221), [Trello](http://trello.com/ioopm), [GitHub](), [kurswebben](http://wrigstad.com/ioopm)
* Du kan läsa om kursmålen på [AUPortal](http://auportal.herokuapp.com)
* Ev. köpa [kursboken](http://www.bokfynd.nu/0321884922.html)


