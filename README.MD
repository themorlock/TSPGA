`Traveling-Salesman Genetic Algorithm`
=
### Prerequisites:
- `gcc`, `clang`, or another C compiler

 - `cmake>=3.17`
 
 - `SDL2`
 
 ### Build instructions:
```sh
$ git clone https://github.com/themorlock/TSPGA.git
$ mkdir build
$ cd build
$ cmake ..
$ make
```

 ### Usage:
```sh
$ ./TSPGA [board_width] [board_height] [num_cities] [elite_population_size] [graph_screen_proportion] 
```
- `board_width` - X-Range of cities
- `board_height` - Y-Range of cities
- `num_cities` - Number of cities
- `elite_population_size` - Number of elite chromosomes (Total population will be double this size)
- `graph_screen_proportion` - Proportion of vertical-screen that distance graph will cover

