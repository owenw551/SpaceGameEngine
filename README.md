# SpaceGameEngine

## About
Hi! Welcome to my Game Engine Project. SpaceGameEngine is a 2D game engine that uses SDL 2.0 and implements the Component pattern. It is being worked on in my free time.

I began the project by following the incredibly helpful tutorial series called "How To Make A Game" by Carl Birch on YouTube, available at https://www.youtube.com/user/creaper/ (See below for a link to his project). His series has been on hiatus for a while now, but it served as a great introduction to how games work under the hood.

This engine is an extension and reworking of that project. Since the tutorial series stopped, I have added:  

 * Improved vector mathematics 
 * a reworking of all components 
 * a scene manager
 * more advanced map functionality
 * mouse functionality
 * and more!
 
A couple of quick notes:

* I hope to keep what I am currently working on in a file called CurrentWork.
* The project uses x86 SDL binaries, but I've noticed the project may default to building x64 on your machine and not build correctly. If this happens (you'll recieve errors about not beig able to find to the SDL.h header file) switch to x86 and it should work.
* Building and running the project at any point will most likely load up a test of the latest feature I have added, which is why the resultant program may seem a bit ... incongruous?

Feel free to use this code however you wish.

Thanks for reading!

## Resources I have found helpful

https://github.com/carlbirch/BirchEngine
Link to the code for the aforementioned tutorial series

http://gameprogrammingpatterns.com/
The most helpful resource I have found for learning about how game engines are structured

http://lazyfoo.net/
Amazing resource for learning about SDL for game programming

https://www.learncpp.com/
The resource I find most helpful for C++ in general
