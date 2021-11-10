# Introduction to Robotics (2021 - 2022)

Introduction to Robotics laboratory homeworks, taken in the 3rd year at the Faculty of Mathematics and Computer Science, University of Bucharest. Each homework includes requirements, implementation details, code and image files.

## Homeworks

<details>
<summary>Homework 1</summary>
<br>
The homework consists of the following:
  
• Components: RBG led (1 minimum), potentiometers (3 minimum), resistors and wires (per logic)

• Technical Task: Use a separate potentiometer in controlling each of the colors of the RGB led (Red, Green and Blue). The control must be done with digital electronics (you must read the value of the potentiometer with Arduino, and write a mapped value to each of the pins connected to the led.

• Publishing task: You must add the code to the Github repo and continue updating the readme with at least the following details (but feel free to be more creative):
1.  Task Requirements
2.  Picture of the setup
3.  Link to video showcasing functionality

• Coding task: Coding style is of utmost importance. You must have a perfectly clean code in order to receive the maximum grade. Keep in mind that magic numbers are not accepted, although you might see them in the lab (as a trade-off for speed). Remember to be consistent in your style, check the style guide and the provided style document and use correct spacing.


The solution for the homework is in the folder "Tema 1":

• The picture is here: https://github.com/marian222200/IntroductionToRobotics/blob/main/Tema%201/poza_tema_robotica_1.jpeg

• The video showcasing the functionality is here: https://github.com/marian222200/IntroductionToRobotics/blob/main/Tema%201/clip_tema_robotica_1.mp4

• The file with the code is here: https://github.com/marian222200/IntroductionToRobotics/blob/main/Tema%201/codTema.ino
</details>

<details>
<summary>Homework 2</summary>
<br>
The homework consists of the following:
  
• Components: 5 LEDs, 1 button, 1 buzzer, resistors and wires (per logic)
  
• General  description: Building the traffic lights for a crosswalk. You will use 2 LEDs to represent the traffic lights for people (red and green) and 3 LEDs to represent the traffic lights for cars (red, yellow and green).
  
• The system has the following states:
1.  State 1 (default, reinstated after state 4 ends): green light for cars, red light for people, no sounds. Duration: indefinite, changed bypressing the button.
2.  State 2 (initiated by counting down 10 seconds after a button press): the light should be yellow for cars, red for people and no sounds. Duration: 3 seconds.
3.  State 3 (iniated after state 2 ends): red for cars, green for people and a beeping sound from the buzzer at a constant interval. Duration:10 seconds.
4.  State 4 (initiated after state 3 ends): red for cars, blinking greenfor people and a beeping sound from the buzzer, at a constant interval, faster than the beeping in state "3.". This state should last 5 seconds.
Be careful: pressing the button in any state other than state 1 should NOT start any actions.

• Publishing task: You must add the code to the Github repo and continue updating the readme with at least the following details (but feel free to be more creative).
1.  Task Requirements
2.  Picture of the setup
3.  Link to video showcasing functionality
  
• Coding task: Coding style is of utmost importance. You must have aperfectly clean code in order to receive the maximum grade. An important coding challenge present in this task is using "millis()" instead of "delay()". However, remember that the bulk of the grade is if the project works. Do not tend to small details unless you have the entire functionality done.
  
  
The solution for the homework is in the folder "Tema 2":
  
• The picture is here: https://github.com/marian222200/IntroductionToRobotics/blob/main/Tema%202/poza_tema_robotica_2.png

• The video showcasing the functionality is here: https://github.com/marian222200/IntroductionToRobotics/blob/main/Tema%202/clip_tema_robotica_2.mp4

• The file with the code is here: https://github.com/marian222200/IntroductionToRobotics/blob/main/Tema%202/varianta_finala.ino
  
• The second method (different code): https://github.com/marian222200/IntroductionToRobotics/blob/main/Tema%202/varianta_steps.ino
  
• The file containing the tones: https://github.com/marian222200/IntroductionToRobotics/blob/main/Tema%202/pitches.h
</details>

<details>
<summary>Homework 3</summary>
<br>
The homework consists of the following:
  
• Components: a buzzer and a 7-segment display (or a led bar / or 8 leds in a row that simulate a led bar)
  
• Task: should detect EMF (check body and near outlets). It should print the value on the 7-segment display (or light the led bar) and should make a sound based on the intensity.

• The catch: it’s really easy, but one of the mistakes you can do is not to calibrate for the interval on the values you are going to get. Check the link on calibrations.

• Publishing task: You must add the code to the Github repo and continue updating the readme with at least the following details (but feel free to be more creative).
1.  Task Requirements
2.  Picture of the setup
3.  Link to video showcasing functionality

Just to be clear: the input is the EMF using a home-made antenna (can be a wire and a resistor) and the output is some sort of lighting (7-segment values, leds lighting up etc.) and a buzzer with intensity (change the 2nd parameter in the tone function based on the intensity).
The purpose of this project is, first of all, to have a bit of fun and also let you be creative (or lazy) with it. Bonus points for extra effort.


The solution for the homework is in the folder "Tema 3":
  
• The picture from above is here: https://github.com/marian222200/IntroductionToRobotics/blob/main/Tema%203/tema3_poza_deasupra.jpeg

• The picture from the side is here: https://github.com/marian222200/IntroductionToRobotics/blob/main/Tema%203/tema3_poza_deasupra.jpeg

• The video showcasing the functionality is here: https://github.com/marian222200/IntroductionToRobotics/blob/main/Tema%203/tema3_clip.mp4

• The first method code (average of a sample of readings) is here: https://github.com/marian222200/IntroductionToRobotics/blob/main/Tema%203/variant_average_of_a_sample.ino

• The second method code (maximum of multimple averages of a samples of readings over a certain period of time) is here: https://github.com/marian222200/IntroductionToRobotics/blob/main/Tema%203/variant_max_of_average_of_sample.ino
  
• The third method code (maximum of readings over a certain period of time): https://github.com/marian222200/IntroductionToRobotics/blob/main/Tema%203/variant_max_over_time.ino
</details>
