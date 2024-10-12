#### Copyright Manolache Maria-Catalina 313CAb 2023-2034
***Simulator de Octave:***
Scopul programului este de a realiza un simulator al software-ului Octave ce
presupune lucrul cu matrice alocate dinamic. Functionalitati de baza ale
acestuia includ incarcarea in memorie a unei matrici, transpunere, inmultire,
ridicare la putere, redimensionare.


# Functii elementare: 
Programul contine la inceput 7 functii elementare folosite pe parcursul
rezolvarii cerintelor, care vor fi explicate in randurile ce urmeaza.

Functia allocate() primeste ca parametrii dimensiunile unei matrice de alocat
si auxiliarul in care aceasta va fi alocata, folosind calloc(). Am abordat
cazul in care alocarea esueaza, dandu-i auxiliarului NULL si incheiand executia
functiei. Asemanator, daca in cadrul alocarii fiecarui pointer spre un bloc de
n int (coloane), aceasta esueaza, voi elibera tot ce am alocat pana in acest
punct, voi da auxiliarului NULL si voi incheia executia functiei.

Functia free_mat() primeste ca parametrii o matrice oarecare si dimensiunea
liniilor sale. Aceasta va fi dezalocata folosind free().

Functia swap() inverseaza valorile a doua variabile.
Functia swap_mat() inverseaza doua matrice.

Functia sum() returneaza suma elementelor unei matrice modulo 10007.
Daca rezultatul fiecarei sume este negativ, adun 10007.

Functia mul() returneaza rezultatul inmultirii a doua matrici oarecare,
modulo 10007. Cele doua matrici si dimensiunile lor sunt primite ca parametrii.
Rezultatul este alocat folosind functia allocate(), deoarece se
cunosc dimensiunile produsului. 

Functia mat_in() creeaza matricea In pe baza unei dimensiuni primite ca
parametru.

Functiile ce urmeaza vor fi apelate in main, reprezentand rezolvarile pentru
toate comenzile.

# Functii de rezolvare
#### R:
Functia power() returneaza rezultatul ridicarii la putere in timp log. a
unei matrici (mat) primite ca parametru. Puterea (pow), vectorul dimensiunilor
liniilor, indexul matricei de ridicat la putere sunt, de asemenea, primite ca
parametrii. Functia va returna result, adica rezultatul ridicarii la putere.
Algoritmul functioneaza cat timp puterea ramane > 0. Daca ea este impara,
pastrez in aux inmultirea dintre result si mat, eliberez vechea valoare a lui
result pt a-l inlocui cu aux si scad pow. Acum pow este par, caz in care aux ia
valoarea ridicarii la patrat a lui mat, eliberez vechea mat, o inlocuiesc cu
noua valoare si injumatatesc pow. La finalul acestei functii, eliberez mat si
calculez modulo 10007 rezultatul.
#### L:
Functia load() incarca in memorie o matrice, citind m si n si verificand daca
mai exista spatiu in vectorul de matrice. In caz contrar, dimensiunea se 
dubleaza si vectorii sunt realocati dupa noua dimensiune. Daca realocarea
vreunuia esueaza, opresc executia. In final, adaug matricea alocata, citesc
matricea, adaug dimensiunile noii matrici in vectorii corespunzatori.
#### P:
Functia print() tipareste un element al vectorului de matrice, dat de indexul
pe care il citeste.
#### T:
Functia transposition() realizeaza transpusa unei matrice. Se aloca memorie
pentru auxiliarul trans, in care este calculata transpusa. Este eliberata
memoria pentru vechea matrice, fiind inlocuita de transpusa, iar dimensiunile
matricei sunt inversate cu swap().
#### O:
Functia sort() realizeaza ordonarea vectorului de matrice in functie de suma
fiecarei matrice. Am folosit bubble sort, calculand pentru fiecare matrice din
vectorul de matrici si pentru adiacenta sa suma elementelor matricelor. Am
comparat aceste sume, iar daca ele nu sunt crescatoare, folosesc swap
pentru a inversa matricile si elementele vectorililor de linii si de coloane.
#### M:
Functia multiply() realizeaza inmultirea a doua matrice, tinand cont de cazul
in care vectorii trebuie realocati. Rezultatul inmultirii va fi stocat in
auxiliarul rez, ce ia valoarea returnata de functia mul(). Acesta va fi pus in
locul vechii matrice, iar dimensiunile acesteia sunt actualizate in functie de
dimensiunile matricelor de inmultit.
#### C:
Functia resize() realizeaza redimensionarea unei matrice. Noua matrice
va avea dimensiunile nl si nc, iar fiecare element al ei va lua valoarea din
matricea de redimensionat de la pozitia determinata de valoarea vectorului de
linii si de coloane pentru i si j (practic se intersecteaza liniile si 
coloanele). Rezultatul va fi pus in locul vechii matrici, dimensiunile vor fi
actualizate si vectorii considerati vor fi eliberati.
#### F:
Functia F() realizeaza eliberarea unei matrice, cu redimensionarea vectorului 
de matrice (ultimul element este eliminat). Fiecare element al vectorilor de
matrici si de dimensiuni este deplasat cu o pozitie, iar ultima matrice este
facuta sa pointeze catre NULL si vectorii de dimensiuni sunt facuti 0. In final
scade indexmat, ce reprezinta numarul de matrici din vectorul de matrici.

In main() se afla declararile variabilelor si alocarea memoriei pentru vectorul
de matrici. In cadrul unui switch, apelez functiile de mai sus pentru fiecare
comanda valida, cazul default acoperind comenzile invalide. 

Pentru eliberarea resurselor (Q), folosesc un for ce elibereaza fiecare
matrice din vectorul de matrici, apoi eliberez vectorii dimensiunilor si
vectorul de matrici.