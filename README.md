# Projekt na zaliczenie eksternistyczne
## Programowanie (1100-1F23) Jakub Korsak

## Instalacja
Należy:
* otworzyć emulator terminala
* `git clone github.com/korsakjakub/ext.git`
* `cd ext/`

## Struktura projektu
* Pliki źródłowe (c++) znajdują się w `src/`,
* pliki zapisane przez program pojawiają się w `output/`,
* pliki *binaries* pojawiają się w `build/`

## Kompilowanie
W `/` znajduje się skrypt `compile.sh`, którym można wszystko skompilować.
`$ sh compile.sh`

## Użycie
`./build/ext <ścieżka do zdjęcia>`

Zalecany emulator terminala ze wsparciem ANSI escape sequences (raczej wszystkie terminale, które można znaleźć w *NIX). Ze względu na szalenie niską wydajność formatu `.ppm` i `.pgm` bezcelowym zdaje się używanie plików większych niż ok. 200x200
