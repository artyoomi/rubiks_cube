## Rubik's Cube solver

This project is an alternative exam in the discipline of DM&TI at the SPBSETU 2nd year. This program shows the assembled Rubik's cube at start,
then you can scramble the cube by yourself or use the random generator to scramble it automatically. The porgram doesn't save the turns made in any ways.
After the scrambling, you can choose one of two algorithms to solve the cube. This program has a complete 3D model of the cube and shows an animated movement at scrabmling/solving.

### Build
To build program you need to write the following in terminal\
*(instructions for Linux, the build may vary on Windows / MAC OS)*
```
cmake -B build/
cd build
cmake --build .
./Rubiks_cube
```

### Working with program
Two algorithms have been implemented to assemble the Rubik's cube: the human algorithm and the Thistlethwaite algorithm. OpenGL is used for visualization.

![image](https://github.com/user-attachments/assets/3f909191-2017-4089-bc69-6f10d6054cf5)

When using Thistlethwaite's algorithm for the first time (before the databases were generated and stored on the computer), the databases must be generated so it will take some time. After generation the solving algorithm will work almost instantly.

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
