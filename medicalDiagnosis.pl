go :-
    hypothesis(Disease),
    write('I believe that the patient has '),
    write(Disease),
    nl,
    write('TAKE CARE'),
    nl,
    undo.

/* Hypothesis that should be tested */
hypothesis(cold) :- cold, !.
hypothesis(flu) :- flu, !.
hypothesis(typhoid) :- typhoid, !.
hypothesis(measles) :- measles, !.
hypothesis(malaria) :- malaria, !.
hypothesis(unknown). /* NO diagnosis */

/* Hypothesis Identification Rules */
cold :-
    verify(headache),
    verify(runny_nose),
    verify(sneezing),
    verify(sore_throat),
    write('Advices and Suggestions: '),
    nl,
    write('1: Tylenol/tab'),
    nl,
    write('2: Panadol/tab'),
    nl,
    write('3: Nasal spray'),
    nl,
    write('Please wear warm clothes because '),
    nl.

flu :-  
    verify(fever),
    verify(headache),
    verify(chills),
    verify(body_ache),
    write('Advice and Suggestions: '),
    nl,
    write('1: Tamiflu/tab'),
    nl,
    write('2: Panadol/tab'),
    nl,
    write('3: Zanamivir/tab'),
    nl,
    write('Please take a warm bath and do salt gargling because '),
    nl.

typhoid :-
    verify(headache),
    verify(abdominal_pain),
    verify(poor_appetite),
    verify(fever),
    write('Advice and Suggestions: '),
    nl,
    write('1: Chloramphenicol/tab'),
    nl,
    write('2: Amoxicillin/tab'),
    nl,
    write('3: Ciprofloxacin/tab'),
    nl.

measles :-
    verify(fever),
    verify(runny_nose),
    verify(rash),
    verify(conjunctivitis),
    write('Advices and Suggestions: '),
    nl,
    write('1: Tylenol/tab'),
    nl,
    write('2: Aleve/tab'),
    nl,
    write('3: Advil/tab'),
    nl,
    write('4: Vitamin A'),
    nl,
    write('Please get rest and use more liquid because '),
    nl.

malaria :-
    verify(fever),
    verify(sweating),
    verify(headache),
    verify(nausea),
    verify(vomiting),
    verify(diarrhea),
    write('Advices and Suggestions: '),
    nl,
    write('1: Aralen/tab'),
    nl,
    write('2: Qualaquin/tab'),
    nl,
    write('3: Plaquenil/tab'),
    nl,
    write('4: Mefloquine'),
    nl,
    write('Please do not sleep in open air and cover your full skin because '),
    nl.

/* How to ask Questions */
ask(Question) :-
    write('Does the patient have the following symptom: '),
    write(Question),
    write('? '),
    read(Response),
    nl,
    ( (Response == yes ; Response == y)
    ->
    assert(yes(Question)) ;
    assert(no(Question)), fail).

:- dynamic yes/1, no/1.

/* How to verify Something */
verify(S) :-
    (yes(S)->true ;
    (no(S)->fail ;
    ask(S))).

/* Undo all yes or no assertions */
undo :- retract(yes(_)), fail.
undo :- retract(no(_)), fail.
undo.
