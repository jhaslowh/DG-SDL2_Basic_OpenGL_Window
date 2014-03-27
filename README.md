SLD 2 Basic OpenGL 2.0+ Window
==============================

About
-----

The project in this repo shows how to setup a SDL 2 window that uses OpenGL 2.0+ with shaders. A basic sprite and 3D cube should be rendered to the screen when the program is run. A basic game loop is implemented as an example, but can be removed if not desired. 

All libraries and headers that are required are included for ease of use so that they do not need to be found individually. 

Technical Information
---------------------

### Implemented  

* Image Loading (using SOIL)
* Orthographic Projection 
* Perspective Projection
* 2D Sprite
* 3D Cube
* Matrix Transforms (Using GLM) 
* Basic Game Loop

### Libraries

**SDL 2**  
[http://www.libsdl.org/](http://www.libsdl.org/)  
Used for 
- GUI's   
- Threads  
- Timing  

**GLEW**   
[http://glew.sourceforge.net/](http://glew.sourceforge.net/)  
Used to access newer OpenGL functions
 
**GLM**  
[http://glm.g-truc.net/0.9.5/index.html](http://glm.g-truc.net/0.9.5/index.html)  
Used for matrix math

**SOIL**  
[http://www.lonesock.net/soil.html](http://www.lonesock.net/soil.html)  
Used to load texture files 

OpenGL Headers for linux
------------------------

You will need to get the OpenGL headers if you are compiling the code on linux. You can either look for there here..  

[http://www.opengl.org/registry/](http://www.opengl.org/registry/)  
[http://www.khronos.org/registry/](http://www.khronos.org/registry/)  

or run these commands. The freeglut library might not be nessesary.   

    sudo apt-get update  
    sudo apt-get install libglu1-mesa-dev freeglut3-dev mesa-common-dev  

