SuperMind

Program,  gra w grę SuperMind.

W grze łamie się ukryty kod złożony z sekwencji czterech cyfr wybranych
ze zbioru <1,6>. Gra dwóch graczy. Jeden układa kod z czterech cyfr
(nazywać go bedziemy się go koderem) a drugi stara się go odgadnąć 
(nazywać będziemy go dekoderem). Dekoder podaje sekwencję czterech cyfr 
i dostaje od kodera w odpowiedzi informację ile cyfr jest poprawnych i 
na swoich miejscach (oznaczone beda jako : 'black') a ile poprawnych, ale
na złych miejscach (oznaczone beda jako : 'white').

Osoba uruchamiająca program jest koderem i zapisuje sobie na
kartce kod złożony z czterech cyfr. Program cyklicznie drukuje swoją
propozycję kodu (cztery cyfry z zakresu od 1 do 6) i czeka na wprowadzenie
przez kodera liczbę białych i liczbę czarnych cyfr.

Przykład
W poniższym przykładzie program znalazł poprawny kod po zadaniu pięciu pytać:
$ ./mastermind

[1] [1] [1] [1]?

white: 0

black: 1

[1] [2] [2] [2]?

white: 1

black: 0

[3] [1] [3] [3]?

white: 1

black: 1

[3] [4] [1] [4]?

white: 2

black: 2

[3] [4] [4] [1]?

white: 0

black: 4

I win

