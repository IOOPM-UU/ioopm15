Typsättning med LaTeX
=====================

När du skriver rapporter och dokument är du kanske van att använda
Word eller OpenOffice. I den här kursen ska vi istället använda
LaTeX för all dokumentframställning. Att använda LaTeX
påminner till stor del om att programmera eftersom att du skriver
text som vanligt och använder LaTeX-kommandon för att byta
typsnitt, storlek, bakgrund, sidhuvud, titel etc. En stor poäng
med LaTeX är att de kommandon du skriver har karaktären
"metadata" och inte "så här skall texten formateras". Du anger
"detta är en rubrik på nivå 2", "detta är en lista", "detta
är en sökväg till en fil", etc. Hur rubriker, listor och sökvägar
slutligen skall formateras beskrivs på **ett enda ställe** och
är ofta enkelt att byta ut genom att bara ändra på en enda rad i
dokumentet.

Se följande exempel som skapar en punktlista:

```
\begin{itemize}
    \item Mother of Dragons
    \item Jon Snow
    \item Hodor
\end{itemize}
```

Vilket med standardinställningar för formatering ger en punktlista:

* Mother of Dragons
* Jon Snow
* Hodor

Byter man ut `itemize` mot `enumerate` får man en numrerad lista istället:

1. Mother of Dragons
2. Jon Snow
3. Hodor

Latex är ett typsättningssystem, där typsättningen syftar på att vi
i exemplet typsätter "Mother of Dragons", "Jon Snow" och
"Hodor" till en lista. Precis som andra språk som HTML så
beskriver man början och slut av typsättningen med start- och
stoppkommandon.

Nu tar vi det från början och skapar ett minimalt dokument i Latex.

```
\documentclass[a4paper]{article}

\begin{document}
    Hello World!
\end{document}
```

Den första raden (`\documentclass`) avser grundinställningar,
t.ex. vilken papperstorlek som skall användas. Samma källkodsfil
kan användas för att göra allt ifrån stora affischer och
presentationer till små visitkort. Parametern `article` ger
sidorna i dokumentet ett utseende som passar för "vanliga
dokument".

Det som står mellan `\begin{document}` och `\end{document}` är det
som kommer synas i det färdiga dokumentet.

Nu skall du kompilera ditt exempel:

```
foo> pdflatex doc.tex
```

Från en källkodfil spottar `pdflatex` ur sig en
`.aux`-fil och en `.pdf`-fil. Ett bra tips är att ha
`.pdf`-filen öppen samtidigt som du redigerar och kompilerar
`.tex`-filen för att kunna se framstegen.

Typsätt nu rubriker av olika storlek:

```
\begin{document}

\section{Introduction}

It has begun!

\subsection{A subheading}

It goes on and on...

\subsection{Another subheading}

...and on and on.

\section{Ending}

It's all over!

\end{document}
```

Kompilera och titta på resultatet. Du kan lägga till ytterligare
nivåer av rubriker med kommandona `subsubsection` och `paragraph`.
Vad händer om du skriver `\section*` istället for `\section`?

Du kan kontrollera hur din text ska se ut på många olika sätt:

```
  Some words are more **important** than others.

  Sometimes you might want a part of a sentence to **stand out**.

  You can also write pretty math: $x^2 + 4x + 2 \leq \sqrt{\pi} \cdot |x|$
```

Koden som står mellan `\documentclass` och `\begin{document}`
kallas för dokumentets *preamble*. Här kan du ställa in
metainformation om dokumentet, importera paket och definiera egna
kommandon. Prova att skriva följande kod i preamblen

```
  \title{Baby's first steps in LaTeX}
  \author{Alice \and Bob}
  \date{\today}
```

Lägg sedan in kommandot `\maketitle` direkt efter
`\begin{document}`. Hur blev det? Du kan prova att byta ut
`article` i `\documentclass{article}` till andra format som t.ex.
`report` och `book`.

Även om inlärningskurvan bitvis kan vara lite brant så är LaTeX
ovärderligt när man ska typsätta dokument. För att vattna din
tunga hoppar vi nu långt framåt och ger en försmak på
möjligheterna! Här är ett exempel som använder stödpaketet Tikz
för att rita en automat. Prova att kopiera och kompilera koden.

```
\documentclass{article}
\usepackage{tikz}
\usetikzlibrary{automata,positioning}
\begin{document}
\begin{tikzpicture}[shorten >=1pt,node distance=2cm,on grid,auto]
   \node[state,initial] (q_0)   {$q_0$};
   \node[state] (q_1) [above right=of q_0] {$q_1$};
   \node[state] (q_2) [below right=of q_0] {$q_2$};
   \node[state,accepting](q_3) [below right=of q_1] {$q_3$};
    \path[->]
    (q_0) edge  node {0} (q_1)
          edge  node [swap] {1} (q_2)
    (q_1) edge  node  {1} (q_3)
          edge [loop above] node {0} ()
    (q_2) edge  node [swap] {0} (q_3)
          edge [loop below] node {1} ();
\end{tikzpicture}
\end{document}
```

Fler otroligt tjusiga bilder kan du ögna igenom på
http://www.texample.net/tikz/examples/

### Att ta med sig

* LaTeX är ett bra verktyg när du vill fokusera mer på
  *innehållet* än *utseendet* av det du skriver
* Välskriven LaTeX-kod låter dig skilja på *vad* något är (en
  numrerad lista) och *hur* något ska se ut (arabiska eller
  romerska siffror).
* Med LaTeX är det (oftast) enkelt att generera
  innehållsförteckningar, referenser, figurhänvisningar och så
  vidare.