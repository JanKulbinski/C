MATCH 

Program tworzy funkcję match(char* wzorzec, char* łańcuch), która ustala zgodność wzorca z
łańcuchem. Znak ’ ?’ we wzorcu oznacza zgodność z dowolnym innym znakiem. Znak
* oznacza zgodność z dowolnym, również pustym, ciągiem znaków w łańcuchu.
Znak różny od ’ ?’ i * oznacza zgodność tylko z samym sobą.

Na przykład

• match(”a???”,s) zwraca true wtedy i tylko wtedy, gdy s ma długość 4 i
zaczyna się od litery ’a’

• match("a*b*b*c", s) zwraca true wtedy i tylko wtedy, gdy napis s zaczyna
się od litery ’a’ i kończy się literą ’c’ a między nimi znajdują się przynajmniej
dwie litery ’b’ (niekoniecznie obok siebie)

