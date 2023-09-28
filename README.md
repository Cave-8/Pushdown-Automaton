# Pushdown Automaton
A configurable simulator for Deterministic Pushdown Automaton.

# Syntax
To configure the automaton you have to write a configuration txt file following this syntax:

beginT
startingState readChar readStackChar writeStackChar endingState
...
endT
beginAcc
acceptingState1
endAcc
string1
string2
string3
...
$

Some examples can be seen in test files.

# Provided tests
test.txt contains PDA recognizing L = {a^nb^n}
test1.txt contains PDA recognizing L = {w2w'2 | where w (0,1)* and w' is w reversed}

# Notes
Code was written and compiled using WSL.
You can compile it yourself (I used gcc main.c -o PDA) and use following command to test it (be sure that PDA and tests files are in the same folder, otherwise use respective paths):
`./PDA < ./nameOfYourTest.txt > ./output.txt`
