![Banner](asset/banner.png)
# Intro

Simple implementation of the Ray Caster principle in SFML. 
Ray casting is a basic computer graphics rendering algorithm that uses the geometric algorithm of ray tracing. 
Here it is:

![ex](asset/ex.jpg)

There is a 2D map that you can see in the top left corner, rays are cast from the player. If one ray touches a wall, a column is drawn.


# Usage and install

The makefile is at the root (need the SFML library) :
```
make 
./raycaster
```

#### Simple and Fast Multimedia Library (SFML )
`sudo apt-get install libsfml-dev`
OR
`sudo dnf install SFML-devel.x86_64`

