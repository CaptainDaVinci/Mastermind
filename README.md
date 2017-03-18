# Mastermind
A simple C++ implementation of the game _Mastermind_.

##Rules
Rules of the game are simple. Two players are required,
one sets the code and the other breaks it. Code is a
combination of 4 colours out of 6 possible colours. At
each point where the code breaker guesses the incorrect
code feedback is provided in the form of number of colours
correct in both position an colour, or correct only in colour
but not in position. For more details refer the following article on
[wikipedia](https://en.wikipedia.org/wiki/Mastermind_(board_game)). 

## How to play
Two players decide upon the number of games to be played
and also the guesses they are allowed to take. Both of them
should be even.

#### Colours used
The allowed colours are: 
- RED     : R
- GREEN   : G
- BLUE    : B
- YELLOW  : Y
- MAGENTA : M
- CYAN    : C
- BLANK   : -

#### Interface
After entering the number of games and the number of guesses
allowed, the first player is to set the secret code which the 
second player should not see.

The code to be set should have a combination of 4 colours out 
of the allowed colours. The combination may contain repeated
colours or even blanks.

```
New game
Set secret code: RBG- 
``` 
The secret code set is red blue green blank.
 Now, its upto the second player to crack the code within the fixed
number of guesses.

If the code entered is not the same as the secret code then the
code is checked for providing feedback. There are two types of 
feedback:
- 'P' denotes that one of the colours is correct in both colour and 
  position.

- 'O' denotes that one of the colours is present in the secret code
  but the position is incorrect.

This continues until the player guesses the correct code or runs out
of guesses.
