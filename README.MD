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

----

## conception notes

This part is written to remind ourselves how to implement the `force generator` part of the project (phase II).

### general structure of registry

*This part might be altered lator in the implementation process since the conception might not be good enough.*

So we need to add new parts to our already-existed parts of program, i.e. the particles and the integrator (if it's still valid after the coming changes).

For each particle in the world, there should be a registry of forces applied to them. This is because the integration calculus need to update the status of a particle only while knowing every force applied to it, instead of appling $n$ times of integration of $dt$. The reason is noted in the appendix.

So for every particle we should have a list binded to it. Of course, it's possible to combine each in list into a bigger list, if we note at the same time the particle $p$ and the force $F$ as a group: $(p, F)$. This is doable, but from the efficence aspect I doubt if it's worth the cost: to do the actual calculation we need to iterate the whole list and seperate it into groups, thus it might be better to start it with different lists.

That being the first thing to consider. So at the present stage of conception (6 oct 2022), I, Wenhao, personlly suggest to save a registry for each force. They can be saved into a bigger list in a strcture like `std::vector<>`. The code will be like:

```c++
class Particle {...}
class ParticleForceRegistry
{
private:
    Particle* p;
    std::vector<Force> registry;
public:
    void update();
}

class ParticleForceRegistries
{
private:
    std::vector<ParticleForceRegistry>;
public:
    void updateAll();
}
```
### Force

> May the force be with you. 

For the actual `force` object, there are mutiple choices. Firstly:

- either a `force` can be simply a value of vector `Vec3` like what we had done in the phase I.

- or it can be a object that indicade a relation instead of a certain value, with can be changed throughout the time ; for instance, the gravity is a constant in the form of $\vec a = \vec g$, or a variable if we take the equation
  $$
  \vec F = \mathbf G \frac{M m}{r^2} \vec u
  $$
  into considertaion.

And if we do use a class, we can also decide if a `Force` is binded with a object or not. A force can:
- either binded with a certain particle $p$, and is initilized with method `ASpectialForce(Partial p)`, and updated by using a `getForce(void)` method ;
- or not binded with a certain particle, but as something more general, initialized with method `ASpecialForce(void)`, and updated by a getForce(Particle p) method.

The former one can be more efficient if we introduce a `dirty` variable, while the second one should take less memory if we do the programming part properly.
## Appendix

### Problème de l'additivité de force avec l'opération de l'intégration

Posons qu'un objet $P$ avec une masse $m$ est mis sur un plan fixe et parallèle au sol, alors cet objet $P$ reste immobile car son poids est à équilibre avec la force exercé par le plan. Notons que les deux forces $\vec F_1, \vec F_2$, on a $\vec{F_1} = m \vec{g}, \vec{F_2} = -\vec{F_1}$. Apparemment cet objet ne déplace pas, avec une vitesse nulle et une accélération nulle. On note quand même cette vitesse $\vec v$ et cette accélération $\vec a$. On note également son positionnement $\vec p$.

Maintenant si on utilise les registres de force et on essaie de calculer séparément les effets des deux forces afin de montrer que ça ne marche pas si les calculs sont faits séquentiellement. 

- premièrement une première force $\vec F_1$ appliquée ; pour une durée de $\Delta t$ donnée, on fait le calcul de l'intégration : 
  $$
  \vec{a} = \frac{\vec{F_1}}{m} = \vec{g} \\
  \vec v = \vec 0 + \Delta \vec v = \int_0^{\Delta t} \vec a \ dt = \vec{g} \ \Delta t \\
  \vec p = \vec 0 + \Delta \vec p = \int_0^{\Delta t} \vec v \ dt = \int_0^{\Delta t}(\vec 0 + \int_0^{\Delta t} \vec a ) \ dt = \vec v \Delta t + \frac{\vec g}{2} \ (\Delta t)^2
  $$
  autrement dit après ce calcul on a un changement de vitesse de $\vec g \ \Delta t$ et un déplacement de $\frac{\vec g}{2} \ (\Delta t)^2$.

- ensuite on applique une deuxième force $\vec F_2 = - \vec F_1 $, avec le même raisonnement ; les deux premières étapes sont pareilles :
  $$
  \vec a = - \vec g \\
  \vec v = \vec g \ \Delta t + \int - \vec a \ dt = \vec 0
  $$.

  > au moins la vitesse est nulle à la fin de calcul...

  maintenant, notons que si on n'introduit pas une variable globale qui sauvegarde la vitesse origine de la particule $\vec v_0 = \vec 0$, on aura malheureusement $\vec{v_0} \not = \vec 0$,
  $$
  \vec p = \vec {p_0} + \int_0^{\Delta t} \vec v \ dt
  \\
  \vec p = \frac{\vec g}{2} \ (\Delta t)^2 + \int_0^{\Delta t} (\vec{v_0} + \vec v) \ dt
  \\
  \vec p = \frac{\vec g}{2} \ (\Delta t)^2 + \vec{v_0} \ \Delta t + \iint_0^{\Delta t} - \vec g \ dt
  \\
  \vec p = \vec{v_0} \ \Delta t
  $$
  Evidemment la partie $\vec{v_0} \ \Delta t$ ne supprime pas avec les autres parties. Ceci donne un résultat absurde, et donc le calcul ne marche pas.
