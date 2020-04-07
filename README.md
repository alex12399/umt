# umt
Cerintele nu se potriveau cu exemplul asa ca mi-am luat libertatea de a pune cerintele in prim-plan: in exemplu se regaseste de doua ori booked calendar1, insa niciodata booked calendar2, asa ca am presupus ca al doilea booked calendar1 trebuie sa fie booked calendar2; in output-ul dat ca exemplu, se considera ca 11:30 - 12:30 este o intalnire valida, insa calendarul primului om este ocupat in intervalul 12:00 - 12:30, asa ca am presupus ca intalnirea trebuia sa fie de fapt intre 11:30 - 12:00.

Pentru a functiona, datele trebuie introduse in fisier astfel:
Linia 1 : intervalele orare in care primul om este ocupat (chiar si cu ghilimele sau cuvinte inainte, ca in exemplu)
Linia 2 : intervalul orar in care primul om poate avea intalniri (chiar si cu ghilimele sau cuvinte inainte, ca in exemplu)
Linia 3 : intervalele orare in care al doilea om este ocupat (chiar si cu ghilimele sau cuvinte inainte, ca in exemplu)
Linia 4 : intervalul orar in care al doilea om poate avea intalniri (chiar si cu ghilimele sau cuvinte inainte, ca in exemplu)
Linia 5 : durata unei intalniri (chiar si cu ghilimele sau cuvinte inainte, ca in exemplu)

In fisierul de output vor fi intervalele orare intre care cei doi oameni pot avea intalniri.

Pentru inceput, am parsat fiecare linie folosind regex-uri, astfel incat fiecare linie sa ramana doar cu ore (pe primele 4 linii, pentru ultima, voi avea doar numarul de minute). Stiind ca toate datele sunt sub forma de perechi (inceput si sfarsit), am luat fiecare pereche, am spart fiecare pereche dupa ":" (firstHour reprezinta ora de inceput, firstMinute reprezinta minutele de inceput, secondHour reprezinta ora de sfarsit, secondMinute reprezinta minutele de sfarsit), si am convertit totul in minute, adaugand datele - sub forma de tuplu(minutul de inceput, minutul de sfarsit) intr-un vector dintr-un obiect de tip Calendar (bookedMinutes). Pentru intervalul orar intre care un om poate avea intalniri se repeta rutina, dar se salveaza in tuplul workingMinutes din Calendar.

In continuare, am apelat metoda calculateAvailableMinutes din fiecare Calendar pentru a gasi inervalele orare in care fiecare om este liber si am iterat peste aceste intervale orar cautand suprapuneri. Aceste suprapuneri reprezinta datele de output in minute. Pentru a le converti in ore, ora reprezinta catul impartirii la 60 iar minutele reprezinta restul impartirii la 60.
