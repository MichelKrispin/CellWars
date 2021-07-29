# Cell Wars

A student side project. (Rather old)
Some feeatures I was looking for:
- Useful inheritance architecture
- Usable GUI ([SFML](https://github.com/SFML/SFML))
- Python binding of existent C++ code ([Pybind11](https://github.com/pybind/pybind11))

## Game
The rules of the games are quite easy:
- Both Player start with an initial field and 100 cells on opposite sides of the field.
- They get some information about the world for every turn.
- After each turn they get 10% new cells (rounded up; so at least 1) on every field. (E.g. one field with 10 cells, 1 new cell there)
- A field which is possessed can split cells to another field.
- If both player try to capture a field the one who has more cells on that field owns it.
  (E.g. 10 split from blue, 15 from red, red possesses the field with 5 cells left)
- If one player captures all fields or the one who owns more fields after 1000 turns (by default) wins.

### Examples
There are a few example of how one can create a bot and decide on how to split the cells.
Most of them are in `src/Bot/Examples.h`.

### Interface
On the bottom left there is the current turn count. (If a font was fount)
On the bottom right are three buttons.
```
Red   - Stop (Space)
Green - Play (Key up)
Blue  - Step (Key right)
```

### Preview

<img src="https://github.com/MichelKrispin/CellWars/blob/master/misc/preview_1.png?raw=true" alt="After 15 turns" width="400" height="400">  | <img src="https://github.com/MichelKrispin/CellWars/blob/master/misc/preview_2.png?raw=true" alt="After 50 turns" width="400" height="400"> 
--- | --- 
<img src="https://github.com/MichelKrispin/CellWars/blob/master/misc/preview_3.png?raw=true" alt="After 15 turns" width="400" height="400">  | <img src="https://github.com/MichelKrispin/CellWars/blob/master/misc/preview_4.png?raw=true" alt="After 50 turns" width="400" height="400"> 

The top row shows one game while the bottom row shows another one (from left to right).


## Dependencies
The project uses CMake as its build system.
The build scripts (`./Build.sh -h` to see all options) are essentially only looking for the correct folder structure 
and will download [SFML](https://github.com/SFML/SFML) if the folder does not exist.

Note that you'll need a font inside of the bin folder. By default this should be `arial.ttf`.
If that can't be found the only thing missing is the turn number and 
the 'Someone wins!' text. So it is still playable.
You can specify this font inside of the `misc/configs.txt` file.

#### Building the python binding
Use `./Build.sh --python` to install the python binding (or `BuildPython.bat` on Windows).
It is probably a good idea to create a virtual environment.
So to build and then run a python script (unix) execute the following
```shell
python3 -m venv ven
source venv/bin/activate
./Build.sh -p
python3 Python/Game.py
```

The `Python/Game.py` file shows how the binding works.
Most game functions found in the C++ base are also found in python.
