# 42-fdf
Discovering the wonderful world of computer graphics rendering a wireframe map.

![Wireframe0](/assets/images/window0.png)
![Wireframe1](/assets/images/window1.png)

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
	make fdf && ./fdf <your_maps>
It will compile my [libft](https://github.com/noctuelles/42-libft) and the [MiniLibX](https://github.com/42Paris/minilibx-linux).

The project is ***only*** compiling on Linux for now. I've not tested on MacOS
nor making a suitable Makefile.

This project is compiled with the **-Ofast** flag to improve math speed. In this
regard, all optimisation provided by the **-O3** flag is enable.

Learn more about optimisation [here](https://gcc.gnu.org/onlinedocs/gcc/Optimize-Options.html).
## Future improvements and features
- [x] Color gradients based on the altitudes.
- [x] Orthogonal top projection with colors.
- [x] Auto-centering and auto-scaling of the map.
- [x] Z Scaling of the map.
- [x] Rotation on all axis.
- [x] Reducing lag and redundant calculations.
- [ ] Better MiniLibX handling.
- [ ] Better rotation and zoom : zooming in the middle of the rendering scene.
instead of the origin. The same applies for the rotation.
- [ ] Hiding H.U.D.
