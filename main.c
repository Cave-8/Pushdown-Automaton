#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

#define ALLOCCONST 10000
#define REALLOCCONST 2
#define READLENGTH 32

/**
 * Transition
 */
typedef struct {
    int begin;
    char read;
    char onStack;
    char write[READLENGTH];
    int end;
    struct transition *nextT;
} transition;

/**
 * State and transitionList
 */
typedef struct {
    int id;
    transition *transitionList;
} state;

/**
 * Global constant for number of states currently defined
 */
int numOfStates = 0;

/**
 * Global constant for number of accepting states currently defined
 */
int numOfAcceptingStates = 0;

/**
 * Current state, always start from 0
 */
int currentState = 0;

/**
 * Current position on stack
 */
int top = 0;
char onTopStack = 'Z';

/**
 * Add transition with specified parameters to transitionList
 */
void addTransition(int begin, int end, char read, char onStack, char write[READLENGTH], state states[]) {
    transition *newT = (transition *) malloc(sizeof(transition));
    newT->begin = begin;
    newT->end = end;
    newT->read = read;
    newT->onStack = onStack;
    for (int i = 0; i < strlen(write); i++)
        newT->write[i] = write[i];
    newT->write[strlen(write)] = '\0';
    newT->nextT = NULL;

    transition *handle = NULL;
    int currState = 0;
    for (int i = 0; i < numOfStates; i++) {
        if (states[i].id == begin) {
            handle = states[i].transitionList;
            currState = i;
            break;
        }
    }

    if (states[currState].transitionList == NULL) {
        states[currState].transitionList = newT;
    } else {
        bool tailNotFound = true;
        while (tailNotFound) {
            if (handle->nextT == NULL) {
                handle->nextT = (struct transition *) newT;
                tailNotFound = false;
            } else
                handle = (transition *) handle->nextT;
        }
    }
}

/**
 * Find transition corresponding to specified parameters
 * @return found transition
 */
transition *findTransition(state state, char read) {
    transition *handle = state.transitionList;
    while (handle != NULL) {
        if (handle->read == read && onTopStack == handle->onStack)
            return handle;
        else
            handle = (transition *) handle->nextT;
    }
    return NULL;
}

/**
 * Function that creates a new state and insert it in states' array
 * @param id is id of the state
 * @param state is states' array
 * @return 1 if transitions list is over, 0 otherwise
 */
int createState(state states[]) {
    /**
     * Two states are created in case both two begin and end state are new
     */
    state *newS1 = (state *) malloc(sizeof(state));
    newS1->id = 0;
    newS1->transitionList = NULL;
    state *newS2 = (state *) malloc(sizeof(state));
    newS2->id = 0;
    newS2->transitionList = NULL;

    char buffer[READLENGTH];
    char stateBuffer[READLENGTH];
    int readingState = 0;
    bool alreadyPresent = false;

    int beginState = 0;
    char read = '0';
    char onStack = '0';
    char write[READLENGTH];
    int endState = 0;

    /**
     * 0 -> Begin state
     * 1 -> Read
     * 2 -> Write on stack
     * 3 -> End state
     */
    int phase = 0;

    /**
     * Reallocate state array
     */
    if (numOfStates > ALLOCCONST - 1)
        states = realloc(states, REALLOCCONST * sizeof(&states));

    if(fgets(buffer, READLENGTH, stdin) == NULL)
        exit(-1);

    if ((buffer[0] == 'e' && buffer[1] == 'n' && buffer[2] == 'd'))
        return 1;

    int innerWrite = 0;

    for (int i = 0; buffer[i] != '\n'; i++) {
        if (buffer[i] != ' ') {
            switch (phase) {
                case 0:
                    stateBuffer[readingState] = buffer[i];
                    readingState++;
                    break;
                case 1:
                    read = buffer[i];
                    break;
                case 2:
                    onStack = buffer[i];
                    break;
                case 3:
                    write[innerWrite] = buffer[i];
                    innerWrite++;
                    break;
                case 4:
                    write[innerWrite] = '\0';
                    stateBuffer[readingState] = buffer[i];
                    readingState++;
                    break;
                default:
                    printf("Unknown state");
            }
        } else {
            if (phase == 0) {
                stateBuffer[readingState] = '\0';
                readingState = 0;
                beginState = atoi(stateBuffer);

                stateBuffer[0] = '\0';

                for (int j = 0; j < numOfStates; j++) {
                    if (states[j].id == beginState) {
                        alreadyPresent = true;
                    }
                }
                if (!alreadyPresent) {
                    newS1->id = beginState;
                    states[numOfStates] = *newS1;
                    numOfStates++;
                } else {
                    free(newS1);
                    newS1 = NULL;
                }
                alreadyPresent = false;

            }
            phase++;
        }
    }
    stateBuffer[readingState] = '\0';
    readingState = 0;
    endState = atoi(stateBuffer);

    stateBuffer[0] = '\0';

    for (int j = 0; j < numOfStates; j++) {
        if (states[j].id == endState) {
            alreadyPresent = true;
        }
    }

    if (!alreadyPresent) {
        newS2->id = endState;
        states[numOfStates] = *newS2;
        numOfStates++;
    } else {
        free(newS2);
        newS2 = NULL;
    }

    alreadyPresent = false;
    //Add transition
    addTransition(beginState, endState, read, onStack, write, states);
    return 0;
}

/**
 * Function that insert a new accepting state in accepting states' array
 * @param id is id of the state
 * @param state is accepting states' array
 */
int insertAcceptingState(int accStates[]) {

    char buffer[READLENGTH];
    if(fgets(buffer, READLENGTH, stdin) == NULL)
        exit(-1);

    if (numOfAcceptingStates > ALLOCCONST - 1)
        accStates = realloc(accStates, REALLOCCONST * sizeof(&accStates));

    if ((buffer[0] == 'e' && buffer[1] == 'n' && buffer[2] == 'd'))
        return 1;
    else {
        accStates[numOfAcceptingStates] = atoi(buffer);
        numOfAcceptingStates++;
        return 0;
    }
}

/**
 * For details about syntax please check README
 */
void parsingMenu(state states[], int acceptingStates[]) {
    char buffer[READLENGTH];
    if(fgets(buffer, READLENGTH, stdin) == NULL)
        exit(-1);
    while (createState(states) != 1);

    buffer[0] = '\0';
    if(fgets(buffer, READLENGTH, stdin) == NULL)
        exit(-1);
    while (insertAcceptingState(acceptingStates) != 1);
}

/**
 * Find required transition
 */

/**
 * TM operating function
 */
void routine(state states[], int acceptingStates[], char stack[]) {
    char buffer;
    bool end = false;
    bool notAccepted = false;
    transition *newT = NULL;

    while (!end) {
        buffer = getc(stdin);

        switch (buffer) {
            case '$':
                end = true;
                break;
            case '\r':
                break;
            case '\n':
                for (int i = 0; i < numOfAcceptingStates && !notAccepted; i++) {
                    if (acceptingStates[i] == currentState) {
                        printf("String accepted\n");
                        break;
                    }
                    else if (i == numOfAcceptingStates - 1)
                        printf ("String not accepted\n");
                }



                /**
                * Reset
                */
                currentState = 0;
                memset(stack, '_', sizeof(char) * ALLOCCONST);
                stack[0] = 'Z';
                onTopStack = 'Z';
                top = 0;
                notAccepted = false;
                break;
            default:
                for (int i = 0; i < numOfStates && !notAccepted; i++) {
                    if (states[i].id == currentState) {
                        newT = findTransition(states[i], buffer);
                        if (newT != NULL) {
                            currentState = newT->end;
                            for (int j = 0; j < strlen(newT->write); j++) {
                                if (newT->write[j] == '|') {
                                    stack[top] = '_';
                                    top--;
                                    onTopStack = stack[top];
                                    break;
                                } else {
                                    stack[top] = newT->write[j];
                                    onTopStack = stack[top];
                                    if (j != strlen(newT->write) - 1)
                                        top++;
                                }
                            }
                        }
                        else {
                            printf ("String not accepted\n");
                            notAccepted = true;
                            break;
                        }
                        break;
                    }
                }
        }
    }
}

/**
 * Print current states and transitions read
 */
void printStateAndTransitions(state states[], int acceptingStates[]) {
    for (int i = 0; i < numOfStates; i++) {
        printf("State: %d\n", states[i].id);
        transition *handle = states[i].transitionList;
        int j = 0;

        while (handle != NULL) {
            printf("Transition found %c %c %s -> %d\n", handle->read, handle->onStack, handle->write, handle->end);
            handle = (transition *) handle->nextT;
            j++;
        }
    }

    printf("Accepting states:\n");
    for (int i = 0; i < numOfAcceptingStates; i++) {
        printf("%d\n", acceptingStates[i]);
    }
}

int main() {

    /**
     * TM stack
     * Hypothesis of single stack TM
     */
    char *stack = (char *) malloc(sizeof(char) * ALLOCCONST);
    memset(stack, '_', sizeof(char) * ALLOCCONST);
    stack[0] = 'Z';

    /**
     * States array (every cell points to a list of possible transitions)
     */
    state *states = (state *) malloc(sizeof(state) * ALLOCCONST);

    /**
     * Accepting states array (contains only ID)
     */
    int *acceptingStates = (int *) malloc(sizeof(int) * ALLOCCONST);

    /**
     * Setup of PDA
     */
    parsingMenu(states, acceptingStates);
    //printStateAndTransitions(states, acceptingStates);

    /**
     * Begin operating
     */
    routine(states, acceptingStates, stack);
    return 0;
}
