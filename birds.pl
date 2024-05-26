% Entry point
identify_bird :-
    hypothesis(Bird),
    write('The bird you are thinking of is: '),
    write(Bird),
    nl,
    undo.

% Hypothesis that should be tested
hypothesis(eagle) :- eagle, !.
hypothesis(owl) :- owl, !.
hypothesis(hummingbird) :- hummingbird, !.
hypothesis(penguin) :- penguin, !.
hypothesis(unknown). % No diagnosis

% Bird Identification Rules
eagle :-
    verify(bird_of_prey),
    verify(large_size),
    verify(brown_feathers),
    write('Some characteristics of an eagle:'),
    nl,
    write('1: Bird of prey'),
    nl,
    write('2: Large size'),
    nl,
    write('3: Brown feathers'),
    nl.

owl :-
    verify(nocturnal),
    verify(small_size),
    verify(tufted_ears),
    write('Some characteristics of an owl:'),
    nl,
    write('1: Nocturnal'),
    nl,
    write('2: Small size'),
    nl,
    write('3: Tufted ears'),
    nl.

hummingbird :-
    verify(tiny_size),
    verify(bright_colors),
    verify(rapid_wing_flapping),
    write('Some characteristics of a hummingbird:'),
    nl,
    write('1: Tiny size'),
    nl,
    write('2: Bright colors'),
    nl,
    write('3: Rapid wing flapping'),
    nl.

penguin :-
    verify(aquatic),
    verify(black_and_white),
    verify(cannot_fly),
    write('Some characteristics of a penguin:'),
    nl,
    write('1: Aquatic'),
    nl,
    write('2: Black and white'),
    nl,
    write('3: Cannot fly'),
    nl.

% How to ask Questions
ask(Question) :-
    write('Does the bird have the following characteristic: '),
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
