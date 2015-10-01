# Hur man får Emacs att sjunga

## Installation (obs, ej Windows)

Först skall vi verifiera att du har en tillräckligt ny Emacs. 
In i terminalen!

```
$ emacs --version
```

Om din Emacs är 24.0 och över är det bara att köra på. Om du har
laddat ned en grafisk Emacs i OS X måste du se till att det är den
Emacs du kör och inte systemets egen som är uråldrig. Låt säga att
du installerade din Emacs i OS X i programmappen, dvs. `/Applications`.
Då kan du köra så här istället:

```
$ /Applications/Emacs.app/Contents/MacOS/bin/emacs --version
```

Om du vill slippa skriva detta långa kommando hela tiden i resten
av installationen kan du skriva så här:

```
$ alias emacs='/Applications/Emacs.app/Contents/MacOS/bin/emacs'
```

Nu binder `emacs` till
`/Applications/Emacs.app/Contents/MacOS/bin/emacs` istället.

Kopiera filerna `ioopm.el` och `ioopm-install.el` till din dator.
Står du redan i terminalen är ett enkelt sätt att göra:

```
$ curl -O https://github.com/IOOPM-UU/ioopm15/tree/master/extramaterial/emacs/ioopm.el 
$ curl -O https://github.com/IOOPM-UU/ioopm15/tree/master/extramaterial/emacs/ioopm-install.el 
```

Kör sedan följande kommandon (i samma katalog som filerna ligger):

```
$ emacs --batch -l ./ioopm-install.el
```

Detta kommer att starta Emacs och sedan använda Emacs för att
ladda ned ett antal paket med nya funktioner. 

Kolla först om filen `~/.emacs` finns. Det kan du göra så här:

```
$ ls ~/.emacs
```

Om du får svaret "no such file or directory" är allt bra.
**Annars**, gå till rubriken "Existerande init-fil" nedan.
Nu kör vi vidare:

```
$ cat ioopm.el >> ~/.emacs.d/init.el
```

Detta kopierar in innehållet i filen `ioopm.el` i
`~/.emacs.d/init.el` som är den inställningsfil som Emacs läser
vid uppstart.

Nu kan du starta om Emacs och så är vi klara!


### Existerande init-fil

Har du en existerande iställningsfil kopierar vi istället
`ioopm.el` in i Emacs inställningskatalog och talar om för
den existerande inställningsfilen att också ladda den:

```
$ cd mkdir -p ~/.emacs.d/
$ cp ioopm.el ~/.emacs.d/
$ echo '(load "~/.emacs.d/ioopm.el")' >> ~/.emacs
```

Nu kan du starta om Emacs och så är vi klara!


## Genomgång av filens innehåll 

Stänger av menyraden, verktygsraden och rullningslistor (scroll
bars). De är ju ändå bara i vägen. Om du är beroende av menyer
etc. för att använda Emacs -- ta bort dessa rader ur `ioopm.el`. 

```
(menu-bar-mode   -1);
(tool-bar-mode   -1);
(scroll-bar-mode -1);
```

Starta paketen vi laddade ned, initiera multiple-cursors (se
nedan)!

```
(package-initialize)
(require 'multiple-cursors)
```

Lägg till stöd för att navigera kod. T.ex. gå från ett
funktionsanrop till definitionen av funktionen. Läs mer här:
[https://github.com/leoliu/ggtags](https://github.com/leoliu/ggtags).

```
(add-hook 'c-mode-common-hook
	  (lambda ()
	    (when (derived-mode-p 'c-mode 'c++-mode 'java-mode)
	      (ggtags-mode 1))))
```

**OBS!** För att få ovanstående att fungera måste du ha [GNU Global]()
installerat på din dator. Med [homebrew]() på OS X kan du bara
köra:

```
$ brew install global
```

Linux-distributioner är olika, så det är svårt att ge installations-
instruktioner. Men pröva gärna:

```
$ sudo apt-get install global
```

---

Nytt kortkommando: Shift + TAB. Expanderar ord. Pröva att skriva
"FooBar" i Emacs, ställ dig sedan på raden under och skriv "F" och
tryck Shift + TAB. Glädje. 

```
(global-set-key (kbd "<backtab>") 'dabbrev-expand)
```

Om du står i ett Git-repo och vill öppna vilken fil som helst,
pröva detta: `Control-x` följt av `Control-p` för att starta detta
kommando.

```
(global-set-key (kbd "C-x C-p") 'find-file-in-project)
```

[Multiple cursors](https://www.google.se/url?sa=t&rct=j&q=&esrc=s&source=web&cd=4&ved=0CD8QtwIwA2oVChMIz6yBmZCiyAIVA90sCh3D6wkx&url=http%3A%2F%2Fwww.youtube.com%2Fwatch%3Fv%3DjNa3axo40qM&usg=AFQjCNF37BDXGxAVAhNA49A4fLEWkQijww&sig2=V5PGaHfcihvQcyfb4_0CGg). Minimalt stöd. Konfigurera mera! 

```
(global-set-key (kbd "C-S-M") 'mc/edit-lines)
```

I en C-fil (eller Java-fil), tryck `Meta-I` för att få söka mellan
alla funktioner och hoppa direkt till dem, variabler etc. Grymt!

```
(global-set-key (kbd "M-i") 'idomenu)
```

En bättre `Meta-X`. 

```
(global-set-key (kbd "M-x") 'smex)
```

Ibland när man kodar vill man se var andra variabler/symboler med
samma namn finns, eller hoppa till nästa anrop till funktionen,
etc.
`Meta-å` färglägger ordet man står på (i hela filen), 
`Meta-ö` och `Meta-ä` hoppar till föregående respektive nästa förekomst av ordet man står på (i filen), 
`Meta-p` tillåter dig att ersätta alla förekomster av ordet med något annat. 

```
(global-set-key (kbd "M-å") 'highlight-symbol-at-point)
(global-set-key (kbd "M-ä") 'highlight-symbol-next)
(global-set-key (kbd "M-ö") 'highlight-symbol-prev)
(global-set-key (kbd "M-p") 'highlight-symbol-query-replace)
```

Lägg till `Control-Shift-U` som kortkommando för att ångra. 

```
;; Alternative undo command
(global-set-key (kbd "C-S-U") 'undo)
```

För dig på Mac (annars behöver du nog inte detta och kan ta bort
dem):

```
;; Remap some keys on the mac keyboard 
(define-key key-translation-map (kbd "M-8") (kbd "["))
(define-key key-translation-map (kbd "M-9") (kbd "]"))
(define-key key-translation-map (kbd "M-(") (kbd "{"))
(define-key key-translation-map (kbd "M-)") (kbd "}"))
(define-key key-translation-map (kbd "M-7") (kbd "|"))
(define-key key-translation-map (kbd "M-/") (kbd "\\"))
(define-key key-translation-map (kbd "M-2") (kbd "@"))
(define-key key-translation-map (kbd "M-4") (kbd "$"))
```

