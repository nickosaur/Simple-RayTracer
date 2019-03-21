# RayTracer
Raytracer project written from scratch for school.

A RayTracer that takes in an input file and renders an image based on the contents of the input file.
The input file consists of a sequence of lines, each of which has a command. For examples and clarifications, [click here](https://github.com/nickosaur/Simple-RayTracer/blob/master/Nickosaur%20-%20RayTracer/scene1.test). The lines have the following form. Note that in practice, you would not implement all these commands at once but implement the smallest subset to debug the first aspect of your raytracer (camera control), then implement more commands to go to the next step and so on. This page contains the complete file specification for reference.

`\#` for comments

`Blank line` The input file can have blank lines that should be ignored.

`command parameter1 parameter2 ...` The first part of the line is always the command. Based on what the command is, it has certain parameters which should be parsed appropriately.

### General options
`size width height` : the size of the image output. The default settings are 640 x 480.

`maxdepth depth` : The maximum depth (number of bounces) for a ray used to create reflections. The default setting is 5. 

`output filename` : The output file to which the image should be written. The default is raytracer.png.

`camera lookfromx lookfromy lookfromz lookatx lookaty lookatz upx upy upz fov` : specifies the camera in the standard way. The fov stands for the field of view in the y direction. The field of view in the x direction will be determined by the image size. The world aspect ratio (distinct from the width and height that determine image aspect ratio) is always 1; a sphere at the center of a screen will look like a circle, not an ellipse, independent of the image aspect ratio. 

`maxverts number` : Defines a maximum number of vertices for later triangle specifications. It must be set before vertices are defined.

`vertex x y z` : Defines a vertex at the given location. The vertex is stored in a vector, which is indexed from 0.

`tri v1 v2 v3` : Creates a triangle out of the vertices involved (which have previously been specified with the vertex command). The vertices are assumed to be specified in counter-clockwise order.

`sphere x y z` : radius Defines a sphere with a given position and radius.

`translate x y z` : A translation 3-vector.

`rotate x y z angle` Rotate by angle (in degrees) about the given axis.

`scale x y z` : Scale by the corresponding amount in each axis (a non-uniform scaling).

`pushTransform` : Push the current modeling transform on the stack as in OpenGL. You might want to do pushTransform immediately after setting the camera to preserve the identity transformation.

`popTransform` : Pop the current transform from the stack as in OpenGL. The sequence of popTransform and pushTransform can be used if desired before every primitive to reset the transformation (assuming the initial camera transformation is on the stack as discussed above).

`directional x y z r g b` : The direction to the light source, and the color, as in OpenGL.

`point x y z r g b` : The location of a point source and the color, as in OpenGL.

`attenuation const linear quadratic` : Sets the constant, linear and quadratic attenuations (default 1,0,0) as in OpenGL. By default there is no attenuation (the constant term is 1, linear and quadratic are 0; that's what we mean by 1,0,0).

`ambient r g b` The global ambient color to be added for each object (default is .2,.2,.2).

`diffuse r g b` : specifies the diffuse color of the surface.
`specular r g b` : specifies the specular color of the surface.
`shininess s` : specifies the shininess of the surface.
`emission r g b` : gives the emissive color of the surface.

### Example output images
scene7.test:

![alt text](https://github.com/nickosaur/Simple-RayTracer/blob/master/Nickosaur%20-%20RayTracer/Output/scene7.png)

scene4-diffuse.test:

![alt text](https://github.com/nickosaur/Simple-RayTracer/blob/master/Nickosaur%20-%20RayTracer/Output/scene4-diffuse.png)
