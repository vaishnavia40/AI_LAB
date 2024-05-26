go:-
    hypothesis(Animal),
    write('The animal you are thinking of is: '),
    write(Animal),
    nl,
    undo.

% Hypothesis that should be tested
hypothesis(lion) :- lion, !.
hypothesis(tiger) :- tiger, !.
hypothesis(elephant) :- elephant, !.
hypothesis(giraffe) :- giraffe, !.
hypothesis(kangaroo) :- kangaroo, !.
hypothesis(unknown). % No diagnosis

% Animal Identification Rules
lion :-
    verify(mammal),
    verify(carnivore),
    verify(has_mane),
    write('Some characteristics of a lion:'),
    nl,
    write('1: Mammal'),
    nl,
    write('2: Carnivore'),
    nl,
    write('3: Has a mane'),
    nl.

tiger :-
    verify(mammal),
    verify(carnivore),
    verify(has_stripes),
    write('Some characteristics of a tiger:'),
    nl,
    write('1: Mammal'),
    nl,
    write('2: Carnivore'),
    nl,
    write('3: Has stripes'),
    nl.

elephant :-
    verify(mammal),
    verify(herbivore),
    verify(has_trunk),
    verify(has_tusks),
    write('Some characteristics of an elephant:'),
    nl,
    write('1: Mammal'),
    nl,
    write('2: Herbivore'),
    nl,
    write('3: Has a trunk'),
    nl,
    write('4: Has tusks'),
    nl.

giraffe :-
    verify(mammal),
    verify(herbivore),
    verify(has_long_neck),
    verify(has_spots),
    write('Some characteristics of a giraffe:'),
    nl,
    write('1: Mammal'),
    nl,
    write('2: Herbivore'),
    nl,
    write('3: Has a long neck'),
    nl,
    write('4: Has spots'),
    nl.

kangaroo :-
    verify(mammal),
    verify(herbivore),
    verify(has_pouch),
    verify(can_jump),
    write('Some characteristics of a kangaroo:'),
    nl,
    write('1: Mammal'),
    nl,
    write('2: Herbivore'),
    nl,
    write('3: Has a pouch'),
    nl,
    write('4: Can jump'),
    nl.

% How to ask Questions
ask(Question) :-
    write('Does the animal have the following characteristic: '),
    write(Question),
    write('? '),
    read(Response),
    nl,
    ( (Response == yes ; Response == y)
    ->
    assert(yes(Question)) ;
    assert(no(Question)), fail).

:- dynamic yes/1, no/1.

% How to verify Something
verify(S) :-
    (yes(S)
    ->
    true ;
    (no(S)
    ->
    fail ;
    ask(S))).

% Undo all yes or no assertions
undo :- retract(yes(_)), fail.
undo :- retract(no(_)), fail.
undo.
