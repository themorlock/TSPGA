`Traveling-Salesman Genetic Algorithm`
=
### Prerequisites:
- `gcc`, `clang`, or another C compiler

 - `cmake>=3.17`
 
 - `SDL2`
 
 ### Build instructions:
```sh
$ git clone https://github.com/themorlock/TSPGA.git
$ cd TSPGA
$ mkdir build
$ cd build
$ cmake -DCMAKE_BUILD_TYPE=Release ..
$ make
```

 ### Usage:
```sh
$ ./TSPGA [board_width] [board_height] [num_cities] [elite_population_size] [graph_screen_proportion] 
```
- `board_width` - X-Range of cities (default 512)
- `board_height` - Y-Range of cities (default 256)
- `num_cities` - Number of cities (default 64)
- `elite_population_size` - Number of elite chromosomes (Total population will be double this size) (default 64)
- `graph_screen_proportion` - Proportion of vertical-screen that distance graph will cover (default 0.125)

