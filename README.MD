# Physic Engine: Construction d’un moteur physique de jeux vidéo

This is the repository of the school project "Construction d’un moteur physique de jeux vidéo". We are the group G with four members:

- Théo Bouguet
- Nahla Boujnah
- Wenhao Luo
- Valentin Plantard-Wahl

Now (the 25th of September), we have accomplished the phase 1 with the implementation of the particles, vectors, an integrator, and two demos. The code is written in C++.

## How to compile our code
The code should be launched on a Windows platform. Then the program can be build via Visual Studio or CMake.

### Necessary libraries
To compile our code, the first step is to install the following libraries:

- opengl32.lib
- glfw3.lib

Which should already be installed in the system. 

### Build with Visual Studio
We have already conclude a ```physics-engine.vcxproj``` file in the repository, which should enable the Visual Studio to automatically configure the build settings. Then by clicking the green button the first demo should be compiled then be launched.![](C:\Users\nemol\source\repos\Alex2740\physics-engine\doc-figures\visual-ui.png)

### Build with ```CMake```

To build with `CMake`, first install the `CMake`. Once it is installed, go to the root repository, then type the following code in a shell:

```shell
rm -r ./build
mkdir build
cd ./build
cmake ..
cmake --build .
```

This should build the files in the `./build/Debug` repository. For now the two demos are named as:

- shooter.exe
- three_bodies.exe

## Brief explanation of our demo

### shooter.exe

This program demonstrate our code can simulate the different particles which are thrown away. Their trajectory should all be parabola, with different maximum height.

### three_bodies.exe

This program showing the interaction of three particles in the space. Their movements are bounded by a form of gravitation (much bigger than the real life value), and they are bounced from the boarder of screen.
