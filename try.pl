% Facts about the family members
male(pralhad).
male(sakahari).
male(omprakash).
male(dnyaneshwar).
male(kishan).
male(megha).
male(vijay).
male(mahesh).
male(shubham).
male(yogesh).
male(sanjay).
male(sainath).
male(ganesh).
male(gajanan).
male(shree).
male(mahesh).
male(sagar).
male(sai).
male(parth).
male(shravan).
male(samarth).

female(vimal).
female(pushpa).
female(sakhu).
female(suman).
female(kanta).
female(sunanda).
female(suchita).
female(vaishnavi).
female(soni).
female(jayshree)
female(sangita).
female(jyoti).
female(sushma).
female(vedika).
female(ishwari).
female(pranavi).
female(sayali).
female(nayan).
female(shruti).
female(gayatri).

% Parent-child relationships
parent(pralhad, kanta).
parent(pralhad, sakhu).
parent(pralhad, suman).
parent(pralhad, gajanan).
parent(pralhad, sunanda).
parent(pralhad, sai).
parent(vimal, sai).
parent(vimal, kanta).
parent(vimal, sakhu).
parent(vimal, suman).
parent(vimal, gajanan).
parent(vimal, sunanda).
parent(sakahari, vijay).
parent(sakahari, sanjay).
parent(sakahari, sainath).
parent(pushpa, vijay).
parent(pushpa, sanjay).
parent(pushpa, sainath).
parent(vijay, vaishnavi).
parent(vijay, yogesh).
parent(sunanda, vaishnavi).
parent(sunanda, yogesh).
parent(suchita, vedika).
parent(sai, vedika).
parent(suchita, ishwari).
parent(sai, ishwari).
parent(suchita, pranavi).
parent(sai, pranavi).
parent(kishan,shubham).
parent(kishan,jyoti).
parent(suman,shubham).
parent(suman,jyoti).
parent(kishan,soni).
parent(suman,soni).
parent(kishan,jayshree).
parent(suman,jayshree).
parent(dnyaneshwar,mahesh).
parent(kanta,mahesh).
parent(dnyaneshwar,shree).
parent(kanta,shree).
parent(dnyaneshwar,sagar).
parent(kanta,sagar).
parent(sakhu,parth).
parent(ganesh,parth).
parent(sakhu,sayali).
parent(sakhu,nayan).
parent(ganesh,sayali).
parent(ganesh,nayan).
parent(sainath,gayatri).
parent(sangita,gayatri).
parent(sainath,samarth).
parent(sangita,samarth).
parent(sushma,shruti).
parent(sushma,shravan).
parent(sanjay,shruti).
parent(sanjay,shravan).

% Marriage relationships
married(pralhad, vimal).
married(sakahari,pushpa).
married(dnyaneshwar, kanta).
married(kishan, suman).
married(gajanan,megha).
married(sai,suchita).
married(vijay,sunanda).
married(sainath,sangita).
married(ganesh,sakhu).
married(sanjay,sushma).
married(sai,suchita).


% Rules to define relationships
maternal_grandmother(X,Y):- female(X),parent(X,Z),female(Z),parent(Z,Y).

maternal_grandfather(X,Y):- male(X),parent(X,Z),female(Z),parent(Z,Y).

paternal_grandmother(X,Y):- female(X),parent(X,Z),male(Z),parent(Z,Y).

paternal_grandfather(X,Y):- male(X),parent(X,Z),male(Z),parent(Z,Y).

mother(X,Y):- female(X),parent(X,Y).

father(X,Y):- male(X),parent(X,Y).

brother(X,Y):- male(X),parent(Z,X),parent(Z,Y),X\=Y.

sister(X,Y):- female(X),parent(Z,X),parent(Z,Y),X\=Y.

sibling(X,Y):-parent(Z,X),parent(Z,Y),X\=Y.

child(X,Y):- parent(Y,X).

husband(X,Y):- male(X),female(Y),married(X,Y).

wife(X,Y):- female(X),male(Y),married(Y,X).

grandson(X,Y):-male(X),parent(Y,Z),parent(Z,X).

granddaughter(X,Y):-female(X),parent(Y,Z),parent(Z,X).

daughter_in_law(X,Y):- female(X),married(Z,X),parent(Y,Z).

son_in_law(X,Y):-male(X),married(X,Z),parent(Y,Z).

maternal_aunt(X,Y):-
    female(X),female(Z),sister(X,Z),parent(Z,Y);
    female(X),married(Z,X),maternal_uncle(Z,Y).

paternal_aunt(X,Y):- 
    female(X),male(Z),sister(X,Z),parent(Z,Y);
    female(X),married(Z,X),paternal_uncle(Z,Y).

maternal_uncle(X,Y):-
    male(X),female(Z),brother(X,Z),parent(Z,Y);
    male(X),married(X,Z),maternal_aunt(Z,Y).

paternal_uncle(X,Y):-
    male(X),male(Z),brother(X,Z),parent(Z,Y);
    male(X),married(X,Z),paternal_aunt(Z,Y).

cousin(X,Y):- parent(A,X),parent(B,Y),sibling(A,B).

niece(X,Y):-female(X),parent(A,X),sibling(A,Y).
    
nephew(X,Y):-male(X),parent(A,X),sibling(A,Y).

/* <examples>
?- grandson(mahesh,vimal)
?- daughter_in_law(sunanda,sakahari)
?- granddaughter(vaishnavi,sakahari)
?- nephew(mahesh,sunanda)
?- niece(vaishnavi,suman)
?- sister(vaishnavi,yogesh)
?- maternal_grandmother(vimal,vaishnavi)
?- maternal_grandmother(vimal,mahesh)
?- brother(vijay,sanjay)
?- maternal_aunt(suman,vaishnavi)
?- paternal_aunt(sushma,vaishnavi)
?- son_in_law(ganesh,pralhad)
?- son_in_law(vijay,pralhad)
*/


