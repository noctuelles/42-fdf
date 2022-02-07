# 42-fdf

[![42](https://img.shields.io/badge/42-common_core-green.svg)](https://shields.io/)
[![Vim](https://img.shields.io/badge/--019733?logo=vim)](https://www.vim.org/)
[![42](https://img.shields.io/badge/Made%20in%20-C-blue.svg)](https://shields.io/)
[![42](https://img.shields.io/badge/Made%20with%20-GNU%20Make-red.svg)](https://shields.io/)

[![made-with-Markdown](https://img.shields.io/badge/Made%20with-Markdown-1f425f.svg)](http://commonmark.org)
[![Ask Me Anything !](https://img.shields.io/badge/Ask%20me-anything-1abc9c.svg)](https://GitHub.com/Naereen/ama)

Discovering the wonderful world of computer graphics rendering a wireframe map.

![Wireframe1](/assets/images/w1.png)
![Wireframe0](/assets/images/w0.png)
![Wireframe2](/assets/images/w2.png)

## Subject
You can find the subject [here](https://cdn.intra.42.fr/pdf/pdf/38057/en.subject.pdf).
## Explanations and documentations.

An excellent [video](https://www.youtube.com/watch?v=go1qrWFw_bs) by CodingMath
explain to you the barebone of isometric 3D. I **highly** recommand you his
videos : you can also find a tutorial about [2D and 3D Coordinate Rotation](https://www.youtube.com/watch?v=AmaC23gQCTw) on his channel. Watching his first videos about vectors,
basic trigonometry, primitives is very usefull.

Check out the [Bresenham algorithm](https://en.wikipedia.org/wiki/Bresenham%27s_line_algorithm) wikipedia page. The explanation rocks. My bresenham is directly inspired by their implementation.

If you're eager to learn more maths with some very serious stuff, you can
check out this [site](http://www.sciences.ch/htmlfr/rechercher/recherchemecanique.php) (**french!**).
Old but gold.

If you're not french or find the website shitty (it his in some way), you can
download their [book](https://archive.org/details/OperaMagistris) for free (5,834 pages, be ready..).

Good luck !
## Compiling & running
	git clone --recurse-submodules https://github.com/noctuelles/42-fdf fdf
	cd fdf && make fdf && ./fdf assets/maps/france.fdf
It will compile my [libft](https://github.com/noctuelles/42-libft) and the [MiniLibX](https://github.com/42Paris/minilibx-linux).

The project is ***only*** compiling on Linux for now. I've not tested on MacOS
nor making a suitable Makefile.

This project is compiled with the **-O3** flag to improve speed. In this
regard, all optimisation provided by the **-O2** flag is enable.

Learn more about optimisation [here](https://gcc.gnu.org/onlinedocs/gcc/Optimize-Options.html).

	make norm

Will check the norm on the whole project.

	make clean

Clean the objects files.

	make fclean

Clean the executable and the objects files.

	make re

Re-make the executable from scratch.
## Future improvements and features
- [x] Color gradients based on the altitudes.
- [x] Orthogonal top projection with colors.
- [x] Auto-centering and auto-scaling of the map.
- [x] Z Scaling of the map.
- [x] Rotation on all axis.
- [x] Reducing lag and redundant calculations.
- [x] Better rotation and zoom : zooming in the middle of the rendering scene.
instead of the origin. The same applies for the rotation.
- [x] Each projection is fully isolated from the others.
The rotation angles, tile width, of each projection will not intefere with the
existing projection.
- [x] Modular code : you can add more projection on the go, by just adding
a transformation fonction. I'm using linked list and function pointer to make
this possible.
- [x] Added a compass in the bottom-left of the screen.
- [ ] Make auto zoom and center work with extremely large map.
- [ ] Better MiniLibX handling.
- [ ] Hiding H.U.D.
