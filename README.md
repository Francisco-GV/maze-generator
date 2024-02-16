# maze-generator
Generate a random maze using multiple algorithms.<br>
Programmed in **C++** and **SFML** library.

<img src="https://github.com/Francisco-GV/maze-generator/assets/54688495/6b83af93-37d9-4db2-8b62-ee455da786f6" alt="maze" width=300px>

## Algorithms
+ **Backtracker Algorithm** (depth-first search)<br>
    + Method name: `IterativeBacktracker` 
    <br><img src="https://github.com/Francisco-GV/maze-generator/assets/54688495/0bbf8e93-a323-4097-9161-f9299e49b271" alt="maze animation" width="150px">
+ **Kruskal's Algorithm**
    + Method name: `KruskalAlgorithm`
    <br><img src="https://github.com/Francisco-GV/maze-generator/assets/54688495/aa8e75ab-0f4a-4de6-815c-8ec44e986e68" alt="maze animation" width="150px">
+ **Prim's Algorithm**
    + Method name: `PrimAlgorithm`
    <br><img src="https://github.com/Francisco-GV/maze-generator/assets/54688495/287924e6-059e-4fb5-a71d-38bf661f9d3c" alt="maze animation" width="150px">
#### Aditional
+ **Recursive implementation of Backtracker Algorithm**
    + Method name: `RecursiveBacktracker`

## (Optional) Command Line Arguments
+ `-s`: Set seed (default = 0) \*
+ `-m`: Set algorithm (see [#Algorithms](#algorithms)) (default = "IterativeBacktracker")
+ `-a`: Animate algorithm
+ `-p`: Set walls padding (thickness) (default = 0)
+ `-c`: Set columns (horizontal cells) (default = 50)
+ `-r`: Set rows (vertical cells) (default = 50)
+ `-w`: Set window width (default = 500) \*\*
+ `-h`: Set window height (default = 500) \*\*
+ `-f`: Set window framerate (default = 20) \*\*\*

<sub>[\*]: Default value (0) indicates to use the current [unix time](https://en.wikipedia.org/wiki/Unix_time), this guarantees a random seed every time</sub>
<br>
<sub>[\*\*]: The cells size only use integer values, so preferably use multiples of columns/rows (respectively) to fit in the window</sub>
<br>
<sub>[\*\*\*]: If animating, each frame the algorithm will perform one step, so higher values will run the animation faster</sub>

## Installation

### Requirements
To compile this project, you need to have installed:
+ [SFML](https://www.sfml-dev.org/index.php)
+ [CMake](https://cmake.org/)

### Getting Started
To run the program locally, follow these steps:

+ Clone the repository:  

```
git clone https://github.com/Francisco-GV/maze-generator.git
```

+ Build the project using CMake:  
```
cd maze-generator
mkdir build
cd build
cmake ..
cmake --build .
```

+ Run the executable:

```
./maze-generator
```
