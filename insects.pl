% Entry point
go:-
    hypothesis(Insect),
    write('The insect you are thinking of is: '),
    write(Insect),
    nl,
    undo.

% Hypothesis that should be tested
hypothesis(bee) :- bee, !.
hypothesis(butterfly) :- butterfly, !.
hypothesis(ant) :- ant, !.
hypothesis(mosquito) :- mosquito, !.
hypothesis(unknown). % No diagnosis

% Insect Identification Rules
bee :-
    verify(flying_insect),
    verify(yellow_and_black_stripes),
    verify(collects_nectar),
    write('Some characteristics of a bee:'),
    nl,
    write('1: Flying insect'),
    nl,
    write('2: Yellow and black stripes'),
    nl,
    write('3: Collects nectar'),
    nl.

butterfly :-
    verify(flying_insect),
    verify(brightly_colored_wings),
    verify(nectar_feeder),
    write('Some characteristics of a butterfly:'),
    nl,
    write('1: Flying insect'),
    nl,
    write('2: Brightly colored wings'),
    nl,
    write('3: Nectar feeder'),
    nl.

ant :-
    verify(social_insect),
    verify(has_antennae),
    verify(terrestrial),
    write('Some characteristics of an ant:'),
    nl,
    write('1: Social insect'),
    nl,
    write('2: Has antennae'),
    nl,
    write('3: Terrestrial'),
    nl.

mosquito :-
    verify(flying_insect),
    verify(small_size),
    verify(bites_humans),
    write('Some characteristics of a mosquito:'),
    nl,
    write('1: Flying insect'),
    nl,
    write('2: Small size'),
    nl,
    write('3: Bites humans'),
    nl.

% How to ask Questions
ask(Question) :-
    write('Does the insect have the following characteristic: '),
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
