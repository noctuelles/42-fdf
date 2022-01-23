# 42-fdf
Discovering the wonderful world of computer graphics rendering a wireframe map.
![Wireframe](/assets/images/window.png)
## Explanations and documentations.
*Under Construction*

An excellent [video](https://www.youtube.com/watch?v=go1qrWFw_bs) by CodingMath
explain to you the barebone of isometric 3D. I **highly** recommand you his
videos : you can also find a tutorial about [2D and 3D Coordinate Rotation](https://www.youtube.com/watch?v=AmaC23gQCTw) on his channel. Watching his first videos about vectors,
basic trigonometry, primitives is very usefull
## Compiling & running
	make fdf && ./fdf <your_maps>
It will compile my [libft](https://github.com/noctuelles/42-libft) and the [MiniLibX](https://github.com/42Paris/minilibx-linux).

The project is ***only*** compiling on Linux for now. I've not tested on MacOS
nor making a suitable Makefile.

This project is compiled with the **-Ofast** flag to improve math speed. In this
regard, all optimisation provided by the **-O3** flag is enable.

Learn more about optimisation [here](https://gcc.gnu.org/onlinedocs/gcc/Optimize-Options.html).
## Future improvements and features
- [ ] Color gradients based on the altitudes.
- [ ] Better rotation and zoom : zooming in the middle of the rendering scene
instead of the origin. The same applies for the rotation. 
- [ ] Further optimisation : reducing lag and redundant calculations.
- [ ] Hiding H.U.D
- [x] Auto-centering and auto-scaling of the map.
- [x] Z Scaling of the map.
- [x] Rotation on all axis.
