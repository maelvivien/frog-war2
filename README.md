# frogwar
little C++ game

Here's a brief overview of the Sprite class:

The Sprite class has two constructors. The first one takes a renderer, name, image path, position (x, y), dimensions (width, height), frame dimensions (frameWidth, frameHeight), number of frames (numFrames), and number of columns (numColumns). It loads an image from the provided path and creates a texture from it. The second constructor takes a renderer, position, and dimensions, and sets the name to an empty string.

The display method renders the sprite on the screen. It calculates the source rectangle based on the current frame and renders it to the destination rectangle.

The animate method updates the current frame based on the time elapsed since the last frame was rendered. It then renders the current frame, flipping it horizontally if the flip parameter is true.

The move method updates the sprite's position based on the provided deltas (dx, dy). It also applies gravity and friction to the sprite's speed, and allows the sprite to jump if it's not already jumping.

The test_collide method checks if the sprite would collide with another entity if it moved by the provided deltas.

The setCollisionVector static method sets the collision vector, which is a list of all entities that the sprite could potentially collide with.

The getName, getX, getY, getWidth, and getHeight methods are simple getters that return the sprite's name, position, and dimensions, respectively.

The Sprite class also has a destructor, but it's currently empty.
