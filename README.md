# To build and run

`./makeProgram.sh`

`./build/simpleGame`

To run the game and be given the answer, run:

`./runCodeWithDebug.sh`


# How to play:
Assuming you know the rules of the game (see `Given Requirements` section below):
- 'a' on the keyboard is BUTTON A
- 's' on the keyboard is BUTTON B
- 'd' on the keyboard is BUTTON C

you must press the enter key after entering the character. 

The program will display something that looks like:
```
   LED 1       LED 2       LED 3
   GREEN       GREEN       ORANGE 
```

# Notes for reviewer:
- fun fact: If you change the value "NUM_OF_LEDS" to any positive integer, the game will automatically resize to that many LEDs. This has been tested with 5
- ctrl+f the entire project and look for ASSUMPTION and QUESTION. These are things that I would normally bring up in a meeting that I would be looking for responses to. 
- ctrl+f the entire project for TODO items. These are what will be needed to be done for the move to the target hardware.
- There is a requirment to handle button down events only. Since I am using a keyboard, I haven't done anything to deal with this case. The Buttons class hasn't dealt with the buttons backend code.



## Below was design notes for myself.











# PARSED REQUIREMENTS:
 - Have 3 outputs. LED 1, 2 ,3 each with 3 colors.
 - Have 3 inputs. 3 Buttons.
 - LED 3 will always be the most recent press
 - red == wrong, not in sequence.
 - yellow == wrong, exists in sequence.
 - green == correct in this sequence location.
 - off == not long enough to show sequence yet.
 - Only button down on the GPIO will be accepted.

 - Randomly generate a combination that is 3 button presses long. Repeat button presses are allowed.
 - After the combination is correctly guessed, generate a new sequence.
 - If the combination is incorrectly guessed, reset the board with the same sequence.


# ASSUMPTIONS: 
These assumptions would be confirmed before development if I could talk to the product owner)
 - assuming undetermined hardware and running on linux, I will assume the input and outputs are file handles to read/write to.
 - Since I do not have buttons and this is a console, I will use a keyboard to simulate the input for now. There is a concern that the input on the target hardware would be 3 seperate file handles as this would require more work for a responsive single threaded applicaiton. I would request that the undetermined hardware combine the 3 buttons to be a single file handle in the device tree.
 -I am going to assume any bug in the code for this will hard fail. Because of that, the program will immediately stop at an error. Discussion of error handling should happen before moving to the real hardware.


# Given Requirements
Below are the exact notes about the problem:

Given a system with the following:

 * LED 1 - which can be {red, green, orange, off}
 * LED 2 - which can be {red, green, orange, off}
 * LED 3 - which can be {red, green, orange, off}
 * Button A
 * Button B
 * Button C

Design & Implement software that fulfills these requirements:

  The system implements a game in which the user has to guess a sequence of three button presses.
  The sequence can contain any combination, e.g. BAC, CCB, AAA.
  The LEDs should always represent the result of the last 3 button presses.
   * LED 3 will always represent the most recent button event
   * LED 2 the one before that
   * LED 1 the one before that

  Red indicates that the button pressed was wrong for this position, and does not appear in a different position.
  Orange indicates that the button pressed was wrong for this position, but it does appear in a different position.
  Green indicates that the button pressed was correct for this position.

  Only "button down" events are generated, so there is no need to deal with held buttons.
  The button sequence is randomly generated on system start-up. 
  After a 3-green result, another random sequence is generated.

  To be written in C++ and executed on Linux.

  The application should be designed to run on the Linux console but with the plan to migrate to some as yet undetermined target hardware.

Provide your test plan and test results as part of your submission.