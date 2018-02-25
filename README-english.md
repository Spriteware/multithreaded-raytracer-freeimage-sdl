# Digital Imaging - Raytracing Algorithm
* Une version Française est disponible à **README-french.md** *

The aim of this project was to implement a 3D rendering system by ray throwing with the following specificities:  

- Make a beam throw with a Blinn-Phong material model;
- Manage spheres, planes and triangular faces as primitive;
- Save this image as an output file.

The project was coded in C++, with Visual Studio 2013 software. It uses **FreeImage** for image recording as well as **SDL 2.0** to display the rendering directly in the program window, and has been optimized using basic **multithreading**.

Thanks to multithreading, it is possible to generate several scenes in parallel and thus to propose **an animation** to the user. On average, it was possible to generate **140 scenes in ~20sec** (on an Intel i5, quad core).

However, real time has been discarded because the ray throwing algorithm is simply not efficient enough.

### Overview of the result obtained
![screenshot](screenshot. png)

Project architecture

- Scene**: main class that has the `render ()` method implementing the ray throwing algorithm and `save ()` that saves the image in a file.
- Camera**: calculates the size of the screen to be displayed and where to display it.
- Light**: calculates the different types of light (ambient, diffuse, specular).
- Objects**:
    * Object**: mother class containing the position of any object and the abstraction of the ray throwing method `intersect ()'.
    * Plane**: contains the intersection radius/plane
    * **Sphere**: contains the intersection radius/sphere and gravity simulation
    * Triangle**: contains the intersection radius/tiangle
    * Pyramid**: based on the intersection of 4 triangles to calculate the intersection radius/pyramid.
* **Tools**:
    * **Vec4**: support of geometric computation between vectors 
    * Vec4N**: standardized vectors
    * Mat4**: Matrix computational support, used for the rotation of vectors in 3D.
    

The scene can currently have only one camera. On the other hand, it can support several lights, but this functionality has not been fully implemented.