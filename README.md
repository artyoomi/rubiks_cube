## Rubik's Cube solver

This project is an alternative exam in the discipline of DM&TI at the University of LETI 2nd year. This program shows the assembled Rubik's cube,
then shows the animation of random turns, then “forgets” the turns made, finds the (preferably optimal) sequence of turns to assemble the cube and shows the assembly animation.

Two algorithms have been implemented to assemble the Rubik's cube: the human algorithm and the Thistlethwaite algorithm. OpenGL is used for visualization.

![image](https://github.com/user-attachments/assets/3f909191-2017-4089-bc69-6f10d6054cf5)

When using Thistlethwaite's algorithm for the first time (before the databases were generated and stored on the computer), the databases will be generated, it will take some time. After generation, the build will work instantly.

Available commands:
- "U" - make up turn (+ shift to U');
- "L" - make left turn (+ shift to L');
- "F" - make front turn (+ shift to F');
- "R" - make right turn (+ shift to R');
- "B" - make back turn (+ shift to B');
- "D" - make down turn (+ shift to D');
- "s" - scramble cube;
- "=" - solve cube using human-like algorithm;
- "\-" - solve cube using Thistlethwaite algorithm

**Compatibility:** at the moment, the program has been run and tested only on Linux systems, so problems may occur on other operating systems.
