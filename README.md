# 1. Overview
This program simulates how magic cubes work using OpenGL framework. The available operations are as follows.
![overview](/overview.png)

<ul>
<li>Rotating whole magic cube</li>
key R
<li>Formatting the magic cube</li>
key F
<li>Rotating each plate</li>
Front and back from left to right: key q w e

Left and right from back to front: key a s d

Clockwise and counterclockwise from bottom to top: key z x c
<li>Changing position of light</li>
X increase and decrease: key u and i

Y increase and decrease: key j and k

Z increase and decrease: key n and m
<li></li>
</ul>


# 2. Implementation
The implementation includes four parts: data representation, global rotation, local rotation and displaying a single cube.

A class is used to store one small cube, which keeps track of the angle of each rotation, the color of each face and the identity of the cubes.

Global rotation allows users to change the angle of observation. This is implemented by receiving information from user input (mouse action) and mapping the windows coordinate to the world coordinate.

Local rotation represents the actual process of playing with the magic cube. The users can rotate nine cubes on the same plate by the nteger multiple of 90 degrees.

The whole magic cube consists of 27 small cubes, and displaying a single cube requires its related information including color, coordiate and rotation angle.

Details of implementation can be found in the report.