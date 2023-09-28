# Pushdown Automaton
A configurable simulator for Deterministic Pushdown Automaton.

# Syntax
To configure the automaton you have to write a configuration txt file following this syntax:

beginT<br>
startingState readChar readStackChar writeStackChar endingState<br>
startingState1 readChar1 readStackChar1 writeStackChar1 endingState1<br>
endT<br>
beginAcc<br>
acceptingState1<br>
endAcc<br>
string1<br>
string2<br>
string3<br>
$<br>

I.E: 
- To move from state 0 to 1 while reading a from input, Z from stack and write ZA on stack you should write: 0 a A ZA 1
- To move from state 1 to 1 while reading a from input, A from stack and delete top character from stack you should write: 1 a A | 1
<!-- -->
Some examples can be seen in test files.<br>
0 is starting state.<br>
States is identified **only** by number.

# Provided tests
- test0.txt contains PDA recognizing L = {a^nb^n | n>=1}
- test1.txt contains PDA recognizing L = {w2w'2 | where w (0,1)* and w' is w reversed}

# Notes
Code was written and compiled using WSL.<br>
You can compile it yourself (I used `gcc main.c -o PDA`) and use following command to test it (be sure that PDA and tests files are in the same folder, otherwise use respective paths):<br>
`./PDA < ./nameOfYourTest.txt > ./output.txt`<br>
Being deterministic **doesn't support epsilon transition**.
