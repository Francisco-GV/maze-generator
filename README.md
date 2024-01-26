# maze-generator
Maze Generator in C++

![maze](https://github.com/Francisco-GV/maze-generator/assets/54688495/cdfee131-c587-40cc-911b-3ef3396f134a)

The program generates a random maze using a recursive backtracking algorithm, implemented in C++ using the SFML library.

## (Optional) Command Line Arguments
+ `-s`: Set random generator seed (default = 0)\*
+ `-a`: Animate the algorithm, showing visited cells and backtracked cells
+ `-c`: Set columns (horizontal cells) that the maze will have (default = 50)
+ `-r`: Set rows (vertical cells) that the maze will have (default = 50)
+ `-w`: Set window width (default = 500) \*\*
+ `-h`: Set window height (default = 500) \*\*
+ `-f`: Set window framerate (default = 20) \*\*\*

<sub>[\*]: Default value (0) indicates to use the current [unix time](https://en.wikipedia.org/wiki/Unix_time), this guarantees a random seed every time</sub>
<br>
<sub>[\*\*]: The cells size only use integer values, so preferably use multiples of columns/rows (respectively) to fit in the window</sub>
<br>
<sub>[\*\*\*]: If animating, each frame the algorithm will perform one step, so higher values will run the animation faster</sub>

![maze animation](https://github.com/Francisco-GV/maze-generator/assets/54688495/0ac1fdf7-eb19-40f6-9367-f698ce442f98)

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