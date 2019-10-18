# Visualizing Search Algorithms
This is an old project visualizing several search algorithms, such as:
A-Star, Breadth-First-Search (BFS), Bellman-Ford, Depth-First-Search (DFS), Dijkstra, Greedy Best-First-Search

and also Kruskal and Prim for maze building with minimum spanning trees.
You can draw obstacles, set start and end point and the program will visualize the search for you.
Please read the section 'Usage' down below as the lock step is not that intuitive.
This project was mainly done to learn a bit of C++.
You could basically use this as a pixel art drawing tool.
Draw some nice images and run the search algorithm through it.

![Demo: DFS](examples/example_dfs.gif)
![Demo: A-Star](examples/example_a-star.gif)
![Demo: Dijkstra](examples/example_dijkstra.gif)
![Demo: Mazes](examples/example_mazes.gif)


## Getting Started

### Prerequisites
You need the [SFML](https://www.sfml-dev.org/) graphics library and 
[cmake](https://cmake.org/) to build it.

On an arch based OS you can get the SFML library with:

`sudo pacman -Sy sfml`.

On ubuntu: libsfml-dev

`sudo apt-get install libsfml-dev`

### Installing

1. clone or download the repo

`git clone git@github.com:Laeri/search_alg.git`

2. enter the folder and build it with cmake and make

`cmake .`

`make`

3. run the binary

`bin/search_alg`

## Usage
1. Use <kbd>left mouse</kbd> to draw obstacles (blue)
2. Choose algorithm by pressing <kbd>Left Arrow</kbd> or <kbd>Right Arrow</kbd> on keyboard. You can cycle through several algorithms.
3. Hold <kbd>ctrl</kbd>, first and second click with <kbd>left mouse</kbd> sets the start and end point.
4. The search algorithm will immediately connect both points if possible.
5. If you want to show the steps manually, see down below (Lock Step Mode).
6. Reset everything with <kbd>r</kbd>, or reset and keep obstacles with <kbd>t</kbd>.
7. Press <kbd>m</kbd> or <kbd>n</kbd> to draw a maze (deletes obstacles).
#### Lock Step Mode
<kbd>l</kbd> - lock serach algorithm, you can set start and end point and it will not try to connect them immediately
<kbd>p</kbd> - set to manual step, you can visualize every step of the algorithm
<kbd>u</kbd> - unlock, manual step is set, it does just one step. Press repeatedly to show progress.

1. Choose Algorithm (by pressing <kbd>Left</kbd>, <kbd>Right</kbd>)
2. Draw obstacles
3. Lock by pressing <kbd>l</kbd>
4. Set manual stepping mode by pressing <kbd>p</kbd>
5. Step through the algorithm by repeatedly pressing <kbd>u</kbd>, each key press does one step.
6. Press </kbd>p</kbd> to get out of manual mode
7. Unlock with </kbd>u</kbd>

### Keybindings
<kbd>s</kbd> - starts or stops the tree expansion

<kdb>r</kbd> - reset everything

<kdb>t</kbd> - reset only start and end point, keep obstacles

<kbd>left mouse</kbd> - click to create obstacles

<kbd>ctrl</kbd> + <kbd>left mouse</kbd> - create start and end point

<kbd>Right Arrow</kbd> or <kbd>Left</kbd> - cycle through search algorithms

<kbd>Escape</kbd> or <kbd>q</kbd> - quit

#### Mazes

<kbd>m</kbd> - create a maze (deletes other objects)

<kbd>k</kbd> - build a minimum spanning tree with Kruskal


## License
This project is licensed under the MIT License - see the [LICENSE.md](LICENSE.md) file
for details.
