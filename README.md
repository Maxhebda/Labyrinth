# Labyrinth
Project assumptions:
- Creating an algorithm (or algorithms) to generate the correct Labyrinth
- The maze has one entrance and one exit
- The object looking for the exit does not know the algorithm structure
- The object is blind (it's dark in the maze)
- writing and testing exit searching algorithms

<img src="./projectScreenImage/Labyrinth02.png" width=500 />

Creating algorithms:
 - [ ] Labyrinth generation
 - [ ] Solving: Blintfold (right hand)
 - [ ] Solving: Blinfold (left hand)
 - [ ] Solving: Brute Force
 - [ ] Solving: Wave propagation (wave of water)
 - [ ] Solving: Time table (time of passing the segment)
---
tools:
- QT Creator 4.12.3
- programming language: c++
- OS : Windows 10 Pro / 64bit
---
### Ways and idea of solution:
* Description of the ways -> [MicroMouse robots](https://forbot.pl/blog/roboty-micromouse-5-metod-przeszukiwania-labiryntu-id17354)
* The shortest path in the graph -> [BELLMAN-FORD algorithm](https://pl.wikipedia.org/wiki/Algorytm_Bellmana-Forda)