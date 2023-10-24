# Brain Blast : A 2D top-down arcade zombie shooter
no further information provided.
incompetence is my greatest superpower.

## compiling instruction
use cmake! if you are unsure, checkout github actions workflow [ci.yml](.github/workflows/ci.yml) for more info.
cmake template from [CMake SFML Project Template](https://github.com/SFML/cmake-sfml-project) by [SFML Contributors](https://github.com/SFML/cmake-sfml-project/graphs/contributors) under [Public Domain or MIT](https://github.com/SFML/cmake-sfml-project/blob/master/LICENSE.md)

this commands works on my machine(tm)

```bash
cd KMITL-ProgrammingFundamentals-GameDev
cmake -DCMAKE_BUILD_TYPE=Debug -DCMAKE_MAKE_PROGRAM=ninja -DCMAKE_C_COMPILER=gcc -DCMAKE_CXX_COMPILER=g++ -G Ninja -S KMITL-ProgrammingFundamentals-GameDev/ -B KMITL-ProgrammingFundamentals-GameDev/build
cmake --build build/ --target all -- -j 4
```

then, for distribution, run `cmake --install build --config Release` to copy libraries.

replace `Debug` from `-DCMAKE_BUILD_TYPE=Debug` with following options
- `Release` for release build
  - also append 
    - `-DBUILD_SHARED_LIBS=FALSE` to build static executable
    - `-DBUILD_SHARED_LIBS=TRUE` to build dynamic executable
- `RelWithDebInfo` for release build with debug info
- `MinSizeRel` for release build optimized for minimal size

## ci status
[![CI](https://github.com/phuwit/KMITL-ProgrammingFundamentals-GameDev/actions/workflows/ci.yml/badge.svg)](https://github.com/phuwit/KMITL-ProgrammingFundamentals-GameDev/actions/workflows/ci.yml)

download build [here!](https://github.com/phuwit/KMITL-ProgrammingFundamentals-GameDev/actions/workflows/ci.yml?query=is%3Asuccess) for bestest build.
to run executables from CI artifacts, download the artifact, extract it, and run the executable from bin/.

## Attributions
many projects/ assets are used in this one. please see [attribution.md](attribution.md) for more info.

## Todo

- [x] player sprite
- [x] import movement code
- [x] import gun code
- [x] background generation
- [x] make a map
- [x] import zombies code
- [x] vary zombies movement
- [x] import zombies horde spawning code
- [x] handle score
- [x] handle scene change
- [x] hud
- [x] level progression
- [x] handle menu screen
- [x] handle paused screen
- [x] handle gameover screen
- [x] handle levelup screen
- [x] handle leaderboard
- [x] implement pickups
- [x] animation
- [ ] rework spawn timing
- [ ] zombie dead animation?


## Master Plan as a Garnt chart

| Task                                     |            |            |            |            |            |            |    Week    |                |            |                |            |            |            |
|:-----------------------------------------|:----------:|:----------:|:----------:|:----------:|:----------:|:----------:|:----------:|:--------------:|:----------:|:--------------:|:----------:|:----------:|:----------:|
|                                          | 16-07-2023 | 23-07-2023 | 30-07-2023 | 06-08-2023 | 13-08-2023 | 20-08-2023 | 27-08-2023 | **03-09-2023** | 10-09-2023 | **17-09-2023** | 24-09-2023 | 01-10-2023 | 08-10-2023 |
|                                          |     3      |     4      |     5      |     6      |     7      |     8      |     9      |     **10**     |     11     |     **12**     |     13     |     14     |     15     |
| Writing Proposal                         |     /      |            |            |            |            |            |            |                |            |                |            |            |            |
| Learning SFML and C++                    |     /      |     /      |     /      |            |            |            |            |                |            |                |            |            |            |
| Implementing Player/ Control scheme      |            |            |     /      |     /      |            |            |            |                |            |                |            |            |            |
| Implementing Play Area/ Maps             |            |            |            |     /      |     /      |            |            |                |            |                |            |            |            |
| Implementing Guns                        |            |            |            |            |     /      |     /      |     /      |                |            |                |            |            |            |
| Implementing Zombies                     |            |            |            |            |            |            |     /      |       /        |     /      |       /        |            |            |            |
| Implementing Zombies spawning/ balancing |            |            |            |            |            |            |            |                |     /      |       /        |     /      |            |            |
| Implementing Zombies drops/ scoring      |            |            |            |            |            |            |            |                |            |       /        |     /      |     /      |            |
| Implementing Power-ups                   |            |            |            |            |            |            |            |                |            |                |            |     /      |     /      |


## atan(rad) converted to deg visualization
![angle_visualization.png](https://github.com/phuwit/KMITL-ProgrammingFundamentals-GameDev/assets/26784267/eb81752f-39c3-48e4-81ae-764c52441a85)
