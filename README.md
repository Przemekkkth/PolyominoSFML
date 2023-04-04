# Polyomino SFML/C++
Simple Tetris-like game for 1,2,3,4,5-blocks.

## Screenshots
![image](https://user-images.githubusercontent.com/28188300/219856313-fecfb9b5-7c94-45a2-907c-a5c1434c6dc9.gif)

### Installing
A step by step series  that tell you how to get a execute project.

1) Using Qt

Get it from GitHub
```
git clone git@github.com:Przemekkkth/LookAtCursorQt-Cpp.git
```
Compile
```
qmake && make
```

2) Using CMake

```
cmake -S . -B build -DCMAKE_BUILD_TYPE=Release
```
```
cd build/
```
```
make -j4
```
```
cp -r ../res/ .
```
You can copy res directory using other method ie by GUI. Next, you can play it.

### Control

|     Key       | Action        |
| ------------- | ------------- |
| left arrow             | move left  |
| right arrow             | move right  |
| up arrow, z             | rotate  |
| down arrow         | move down  |
| SPACE, ENTER             | activate  |
| ESC           | pause, resume  |

## Addons
* [SFML](https://www.sfml-dev.org/) - page of SFML project
* [Github inspiration](https://github.com/SFML/SFML-Game-Development-Book) - many concepts of this book is used in project
* [Github inspiration 1](https://github.com/OneLoneCoder/Javidx9/blob/master/SimplyCode/OneLoneCoder_Tetris.cpp) - game logics
* [Music Theme](https://opengameart.org/content/title-theme-8-bit-style) - opengameart.org
* [Filled Row Soound](https://opengameart.org/content/title-theme-8-bit-style) - opengameart.org
* [Font](https://www.dafont.com/craftron-gaming.d6128) - page of author on dafont.com
* [yt](https://youtu.be/QdhNQLQd8Cs) - gameplay
