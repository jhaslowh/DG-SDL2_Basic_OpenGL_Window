SLD 2 Basic OpenGL 2.0+ Window
==============================

About
-----

The project in this repo shows how to setup a SDL 2 window that uses OpenGL 2.0+ with shaders. A basic 2D sprite and 3D cube should be rendered to the screen when the program is run. A basic game loop is implemented as an example, but can be removed if not desired.   

This is also the same project used during my GLSL presentation.  

All libraries and headers that are required are included for ease of use so that they do not need to be found individually. If you are running this on Linux, the libraries might need to be found or recompiled for compatibility reasons.  

What it should look like  
![Example](/example_pic.png)


Building / Running
--------

OpenGL 2.0 or greater is required to run.   

**Windows**  
To compile on windows, run the project with Visual Studio 2010 or greater and build it.  

**Linux**  
To compile (starting in the root project directory)  
    
    cd src
    make

To run (starting in the root project directory)  

    cd src/Build/
    ./SDL2Example

If you get errors while building or running on linux, check the error section below. 

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
* Basic Keyboard and Mouse wrappers

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

Linux Errors
------------------------

**Error:** OpenGL headers cannot be found  
If you are getting OpenGL errors, run the following commands  

    sudo apt-get update  
    sudo apt-get install libglu1-mesa-dev freeglut3-dev mesa-common-dev  


**Error:** ./2DLight: error while loading shared libraries: libSDL2-2.0.so.0: cannot open shared object file: No such file or directory

Open the file 

    /etc/ld.so.conf  

Add the following line the the bottom  

    include /usr/local/lib

Then run the following command  

    sudo /sbin/ldconfig

Installing Libraries on Linux
-----------------

SDL2, GLEW, and SOIL are required to compile. If you do not have any of these libraries, follow the instructions below to install them.  

**SDL 2**  
Download SDL2-2.0.3.tar.gz from here [http://www.libsdl.org/download-2.0.php](http://www.libsdl.org/download-2.0.php)  
Then run the following commands   

    tar -zxvf SDL2-2.0.3.tar.gz
    cd SDL-1.2.7
    ./configure
    make
    sudo make install


**GLEW**  
Download glew-1.10.0.tgz from here [http://glew.sourceforge.net/](http://glew.sourceforge.net/)  
Then run the following commands  

    tar -zxvf glew-1.10.0.tgz
    cd glew-1.10.0
    make
    sudo make install

If you get errors about -lXmu and -lXi not being found when trying to install this package, then do the following.  

    sudo apt-get install libxmu-dev
    sudo apt-get install libxi-dev


**SOIL**  
Download soil.zip from here [http://www.lonesock.net/soil.html](http://www.lonesock.net/soil.html)  
Then run the following commands  

    unzip soil.zip
    cd Simple\ OpenGL\ Image\ Library/projects/makefile/
    mkdir obj
    make 
    sudo make install

