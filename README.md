# Scop
This was a school project which explores how to render things in OpenGL, including manual parsing of .obj files, manual implementation of transformation matrices, camera movement, texture application, GLSL shader writing, etcetera.

Written in C, tested and compatible with macOS 10.14.6 and Ubuntu 21.04<br/>

## Quick Start (download & run)
- go to the latest release
- download and unzip the source code
- download and unzip the executable ("scop") into the root folder of the unzipped source code
- navigate to it in your command shell
- if necessary, set permissions on the executables, eg:
>chmod 777 scop
- run the program, supplying it with a .obj file as an argument(and optionally a texture .bmp file):
>./scop resources/models/teapot.obj<br/>
>./scop resources/models/42.obj resources/textures/unicorn.bmp

## Quick Start (compile & run)
- install Make, GCC, and SDL; you will also need your system to be able to run OpenGL 4.1 or beyond
- clone the repository
- navigate to it in your command shell
- compile the program with:
>make 
- run the program, supplying it with a .obj file as an argument(and optionally a texture .bmp file):
>./scop resources/models/teapot.obj<br/>
>./scop resources/models/42.obj resources/textures/unicorn.bmp

### Compilation options
>make<br/>
>make re<br/>
>make clean<br/>
>make fclean<br/>

## Extended Explanation
This project had me creating an OpenGL C-program from scratch. The only libraries I was allowed to use, are those necessary for window/context creation and for setting up OpenGL function bindings. Everything else was up to me.

In the end what we have is a program that can parse .obj files, and display the .obj's vertex data as an on-screen model. It can also take a texture file in .bmp format, and plaster it onto the model. By using the keys displayed below, one can move the model around, grow and shrink it, and move the camera around the model. Parts of the model that are further away, will be smaller than those that are closer.

>----- Controls -----<br/>
>Esc: close program<br/>
>C: re-center object<br/>
>V: re-center camera<br/>
>B: balance object vertices<br/>
>N: toggle track object/world center<br/>
>M: toggle texture on/off<br/>
>ZX: scale object<br/>
>WASDQE: translate(move) object<br/>
>TGFHRY: rotate object<br/>
>IKJLUO: translate(move) camera<br/>

And that's how we end up with this fabulous model that we can manipulate and can walk/fly around!<br/>
![](https://imgur.com/58LNOZa.gif)

For more information you can read through the assignment PDF, included in the root of the repository.
