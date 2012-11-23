# Game of Life in C

This project is meant as an educational piece of software. The development
process is described step by step in [slides.pdf](https://github.com/preek/edu_gol/raw/master/slides.pdf). 

Start by reading the slides and try to implement the next step on your own. If
you're stuck, there's help. This project is structed in branches - master only
features the start of the project, every next step n is described in a
subsequent branch prefixed with n.


## Room for improvement

* use strategy pattern to implement output
 * for example this exact code could be used in google nacl
 ([sample implementation](http://dispatched.ch/gol_nacl/gol.html))
* implement more intelligent calculation of next\_tick using caching
* refactor code into more files with separation of concern

## Linklist

* Description of GOL
 * http://en.wikipedia.org/wiki/Conway%27s_Game_of_Life
* Sample Implementation using NaCl
 * http://dispatched.ch/gol_nacl/gol.html
* Game of Life in Game of Life
 * http://www.jwz.org/blog/2012/05/turtles-all-the-way-down-or-gliders-or-glider-turtles/