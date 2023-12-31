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
- To move from state 0 to 1 while reading a from input, Z from stack and write ZA on stack you should write: 0 a Z ZA 1
- To move from state 1 to 1 while reading a from input, A from stack and delete top character from stack you should write: 1 a A | 1
<!-- -->
Some examples can be seen in test files.<br>
Additional informations:<br>
- 0 is **always** the starting state.<br>
- States is identified **only** by number.

# Provided tests
- input0.txt contains PDA recognizing L = {a^nb^n | n>=1},
- input1.txt contains PDA recognizing L = {w2w'2 | where w is generated from (0,1)* and w' is w reversed},
- input2.txt contains well parenthesized language.

# Notes
Code was written and compiled using WSL.<br>
You can compile it yourself (I.E: `gcc main.c -o PDA`) and use following command to test it (use your paths):<br>
`./PDA < ./inputs/yourTest.txt > ./outputs/outputOfYourTest.txt`.<br>
To run it in verbose mode run: `./PDA -v < ./inputs/yourTest.txt > ./outputs/outputOfYourTest.txt`.<br>
You can compile and test automatically by running `bash test.sh` when in the project folder.<br>
Due to the fact that this automaton is deterministic, it **doesn't support epsilon transition** (pay attention during PDA creation).
