# LoadBSH
A program to load .bsh files from the game Anno 1602 on runtime speed.
This is a very early code. A lot will change!

## What it can do
- Loads textures from .bsh files into a "Gfx"-structure array
- Loads .col palette file
- Converts 8 bit optimized palette pixels from .bsh file to 24 bit bitmap pixels
- Can print loaded palette to console for debugging
- Can visualize Gfx in a Cimg-window

## How to run
1. The project was made in VS 2022. It is the safest way to compile it there sucessfully.
2. In the main.cpp define the path to the general .col palette file and the .bsh file(s) you want to load
3. On successfully parsing of a .bsh the Gfx's will be loaded into an array which contain width, height and pixelarray that can be used in your program.
4. Enjoy some minor memory leaks, haven't even looked into them yet.

## ToDo
- A lot faster and efficient .bsh parsing
- Even mooore simple C methods to optimize efficiency
- More Gfx information
- Multiversion support (+ Multilanguage)
- Multiplatform support (+ CMake)
- Merge this project into an even bigger one (that can do more, from doing some simple animated Gfx, to even rendering)

## Dependencies
### CImg
https://github.com/GreycLab/CImg
CImg is used only for testing purposes. It is a great single header tool to quickly show image content to the user.
It can be removed from the code and is not necesary for basic loading of .bsh and .col files.

## FAQ
### 1. Why another tool for the over 27 year old game?
Because I love that game. And I love programming and reverse engineering stuff, as well as game design.

### 2. A similar tool xyz exists already, why not continuing on that one?
I know there might be already a few other amazing tools that can do the same stuff out there, maybe even better, but my goal is to have fun in making it my way, my style and mostly in pure C without a lot of dependencies.

### 3. Is there Linux, Mac support?
Currently I am focussing on the core functionality and not on compatiblity. Since it the tool has no or not much dependencies, it could be easy to migrate it to other systems.

### 4. Why you dont use CMake, Make etc?
Currently I am focussing on the core functionality and not on compatiblity.

### 5. Why do you prefer using old C code over newer C++ functions or other new languages like C#?
I like to be closer to machine code, thats why I prefer using C. I love to do things as efficient as possible, in terms of performance and ressource usage. I come from electronics engineer background, so I learned to keep code small and optimized from programming Micro-Controllers (Atmel, stm32, ...).
Languages as C++, Rust, C# are fine as well, but I do believe they make us programmers lazy because of using a lot of predefined functions and dependencies, that will make programs heavy and harder to maintain on multiple platforms.

### 6. I want to use the entire code or parts in my own software. Are there any requirements?
Feel free to use my code, expand it, make it better, learn from it, heck you can even use it in your comercial projects if you want, it's open source. Just follow the LICENSE. ;-)

### 7. Which game version are you using primarly for developement?
I am using the Anno 1602 Version from GoG in English, planning to add all other languages (from GoG) too in future and the History Edition.

### 8. Is it possible to manipulate or save .BSH data this tool?
This might be a possible added feature in newer versions. Feel free to use this code as a base to create code which can manipulate and save .BSH files.

### 9. Whats the goal with this project?
My goal is to have fun for myself and also make the available to others, so people can learn from it. 

If I find more free time for this project, there might come more in future. :-)
