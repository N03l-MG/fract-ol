# fract-ol (42 Project)
#### Mandelbrot and Julia visualizer in C

In this project I used the [MLX](https://github.com/codam-coding-college/MLX42) graphical library as well as my [libft](https://github.com/N03l-MG/libft) to program an interactive visualizer capable of rendering and exploring fractals. The mandatory features are implementations of the Mandelbrot and its Julia set, along with the ability to zoom in and out. I took it a step further and implemented UI sliders to dynamically change the real and imaginary components of the Julia's complex point, as well as zooming at the cursor's position and panning with the arrow keys. I also added an extra fractal called the Burning Ship. I scored 125% and was granted "Outstanding Project" on two of the evaluations.

![[images/MandelbrotRed.png]]

![[images/JuliaWindow.png]]

![[images/BurningShip.png]]

![[images/ZoomedMandel.png]]

![[images/ZoomedJulia.png]]

**Controls:**

`Mouse Scroll` - Zooming in and out of the fractals.
`Left Click` - Dragging the sliders for the Julia sets.
`Up Key` - Pan view up.
`Down Key` - Pan view down.
`Left Key` - Pan view left.
`Right Key` - Pan view right.
`Escape Key` - Quit the program.

**Fractals / Commands:**

* The Mandelbrot set: ./fractol mandelbrot
* All Julia sets: ./fractol julia (real value) (imaginary value)
* The Burning Ship: ./fractol burningship

(*All fractals have 200 iterations and are in the range -2 to 2 on both axes.*)

**Known Bugs / Limitations:**

- The sliders have a slight offset from where the user is clicking and where the bars are filled in.
- On first render, all fractals are offset in the vertical axis by a few units. Zoom/pan can quickly adjust the view. (This issue is much harder to fix that in may seem!)
- Interacting with the program at deeper zoom levels, especially near back areas severely reduces performance due to many calculations needed to draw the pixels.
- The zoom eventually reaches the iteration and floating point breaking point, which leads to pixilation and inaccuracy.

**Planned Features:**

- Replacing sliders for a 2D graph where point C can be moved by dragging and the respective Julia is rendered.
- Allowing for switching between fractals from the window directly, as well as adding the ability to click on a point in the Mandelbrot to reveal its respective Julia.
- Improving the zoom amount by dynamically changing the total iterations based on how deep the user has zoomed. The more you zoom, the more iterations it runs.
- Switching to a fragment shader approach to delegate the rendering to the GPU, thus massively increasing the performance.
- Switching from float to double values to allow for extreme precision on super deep zooms.
