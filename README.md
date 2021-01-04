# Soft object deformation

## About

A 2D image should be deformed using a 4x4 grid of control points which are used to construct
a cubic Bezier Spline surface for a smooth deformation field in x- and y-direction.
This was a task as part of the Simulators in Games and Medicine course, Heidelberg University. 

## Build

```sh
g++ -Wall Image.cpp CG_2019_Youssef_10.cpp -o sodfrm -s
```

2021
