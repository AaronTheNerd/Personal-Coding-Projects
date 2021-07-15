# Dynamic Background
> Generates seamless gifs of triangle meshes.



## Installation
---
*Python 3.8 required*

Required Python Dependencies:
- [PIL](https://pillow.readthedocs.io/en/stable/index.html)
- [numpy](https://numpy.org/doc/stable/)
- [opensimplex](https://pypi.org/project/opensimplex/)

Third Party Dependencies:
- [ImageMagick](https://imagemagick.org/script/download.php)

## Notes on Usage
---
The only file which needs to be modified in order to customize the gifs is `config.json`. However, if the file structure is changed there will be some issues in the source code (either `src/main.py` or `src/configs.py` depending on what is moved).

## `config.json` Attribute Notes
---
Example config.json:
```
{
    "RANDOM_SEED": true,
    "SEED": 1625466190,
    "WIDTH": 1366,
    "HEIGHT": 768,
    "NUM_OF_FRAMES": 250,
    "BACKGROUND_COLOR": [
        0,
        0,
        0
    ],
    "GIF_CONFIGS": {
        "NUM": 5,
        "MS_PER_FRAME": 11,
        "MARGIN": 150
    },
    "POINT_CONFIGS": {
        "AMPLITUDE": 0,
        "INTENSITY": 0,
        "SCALE": 0,
        "OFFSET_Y": 100,
        "NUM_OF_POINTS": 500,
        "SEPARATION_RADIUS": 40,
        "MAX_FAILS": 10000,
        "BORDER_CONFIGS": {
            "TOP": true,
            "BOTTOM": true,
            "LEFT": true,
            "RIGHT": true,
            "SEPARATION": 40
        },
        "DRIFTING_CONFIGS": {
            "PERCENTAGE": 1,
            "X_MIN": -1,
            "X_MAX": 1,
            "Y_MIN": 0,
            "Y_MAX": 0
        }
    },
    "TRIANGLE_COLORING_CONFIGS": {
        "TYPE": "ShadedGradient",
        "KWARGS": {
            "START_X": 150,
            "START_Y": 0,
            "END_X": 1516,
            "END_Y": 0,
            "START_COLOR": [235, 52, 52],
            "END_COLOR": [66, 224, 245],
            "ALPHA": 0.8,
            "AMBIENT_VECTOR": [1.0, 1.0, 0.5],
            "AMBIENT_GAIN": 55000,
            "AMBIENT_DEFINITION": 10
        }
    },
    "LINE_DRAWING_CONFIGS": {
        "DRAW_LINES": false,
        "TYPE": "SolidLine",
        "KWARGS": {
            "COLOR": [255, 255, 255],
            "WIDTH": 2
        }
    },
    "POINT_DRAWING_CONFIGS": {
        "DRAW_POINTS": false,
        "TYPE": "PlainPoint",
        "KWARGS": {
            "COLOR": [255, 255, 255],
            "WIDTH": 5
        }
    }
}
```

- `RANDOM_SEED` (boolean): Whether or not a random seed should be generated at runtime.
- `SEED` (int): The seed to be used to recreate a gif. This seed will be overwritten if `RANDOM_SEED` is set to true.
- `WIDTH` (int): The width of the final gif.
- `HEIGHT` (int): The height of the final gif.
- `NUM_OF_FRAMES` (int): The number of frames in the final gif.
- `BACKGROUND_COLOR` ([int]): The 0-255 RGB background color.
- `GIF_CONFIGS`: Configuration attributes for the final gif.
    * `NUM` (int): The folder where the final gif will be stored in.
    * `MS_PER_FRAME` (int): The number of milliseconds between frames.
    * `MARGIN` (int): The maximum distance past the edge of the screen that a point can move to.
- `POINT_CONFIGS`:
    * `AMPLITUDE` (float): How far points can travel compared to where initial position.
    * `INTENSITY` (float): How quickly points can change directions.
    * `SCALE` (float): How 'zoomed in' the noise should be (affects smoothness of motion).
    * `OFFSET_Y` (float): *There is almost no reason to modify this.* When the noise function is calculated it gives a scalar value based on the point's position. In order for the x-offset to not be equal to the y-offset the calculation for the y-offset must have a different position than the x-offset's calculation. This attribute moves the point's position for the y-offset calculation.
    * `NUM_OF_POINTS` (int): The maximum number of points in the gif.
    * `SEPARATION_RADIUS` (int): The minimum distance away initial points can be from each other.
    * `MAX_FAILS` (int): The maximum number of times the code will attempt to place a point before giving up.
    * `BORDER_CONFIGS`: Configuration attributes for drawing points on the border of the gif. Helpful for ensuring there are no gaps in the triangular mesh.
        - `TOP` (boolean): Whether or not the top border should be generated.
        - `BOTTOM` (boolean): Whether or not the bottom border should be generated.
        - `LEFT` (boolean): Whether or not the left border should be generated.
        - `RIGHT` (boolean): Whether or not the right border should be generated.
        - `SEPARATION` (int): How far apart border points should be.
    * `DRIFTING_CONFIGS`: Configuration attributes for points which continually drift in a specific direction.
        - `PERCENTAGE` (float): What percentage of points should be drifting (the rest will sway).
        - `X_MIN` (int): The minimum number of times a drifting point can drifting a full screen distance in the positive x-direction (will drift in the negative x-direction if negative).
        - `X_MAX` (int): The maximum number of times a drifting point can drifting a full screen distance in the positive x-direction (will drift in the negative x-direction if negative).
        - `Y_MIN` (int): The minimum number of times a drifting point can drifting a full screen distance in the positive y-direction (will drift in the negative y-direction if negative).
        - `Y_MAX` (int): The maximum number of times a drifting point can drifting a full screen distance in the positive y-direction (will drift in the negative y-direction if negative).
- `TRIANGLE_COLORING_CONFIGS`: The configuration attributes for coloring of the triangles (more detail in section [Triangle Coloring](#triangle-coloring)).
    * `TYPE` (string): Which triangle coloring object will be used to color the gif.
    * `KWARGS` (dict): The attributes needed to instantiate the triangle coloring object.
- `LINE_DRAWING_CONFIGS`: The configuration attributes for drawing the lines between points (more detail in section [Line Drawing](#line-drawing)).
    * `DRAW_LINES` (boolean): Whether or not the lines should be drawn.
    * `TYPE` (string): Which line drawing object will be used to color the gif.
    * `KWARGS` (dict): The attributes needed to instantiate the line drawing object.
- `POINT_DRAWING_CONFIGS`: The configuration attributes for drawing the points (more detail in section [Point Drawing](#point-drawing)).
    * `DRAW_POINTS`: Whether or not the points should be drawn.
    * `TYPE` (string): Which point drawing object will be used to color the gif.
    * `KWARGS` (dict): The attributes needed to instantiate the point drawing object.


## Triangle Coloring
---
`PlainColor`: Draws all triangles the same color.
```
    ...
    "TRIANGLE_COLORING_CONFIGS": {
        "TYPE": "PlainColor",
        "KWARGS": {
            "COLOR": [255, 255, 255]
        }
    },
    ...
```
- `COLOR` ([int]): 0-255 RGB color code for the color of the triangles.

`HSVLinearGradientContinuous`: Draws all triangles based off of a linear HSV color gradient. To define the direction of the gradient, two points are defined as the start and end of a line. Then the center of the triangle is used to find where the triangle is on the line and a linear interpolation is used to find the specific color. As the color gradient uses HSV colors, the gradient may create many intermediate colors.
```
    ...
    "TRIANGLE_COLORING_CONFIGS": {
        "TYPE": "HSVLinearGradientContinuous",
        "KWARGS": {
            "START_X": 0,
            "START_Y": 0,
            "END_X": 1366,
            "END_Y": 768,
            "START_COLOR": [255, 0, 0],
            "END_COLOR": [0, 0, 255]
        }
    },
    ...
```
- `START_X` (int): The x-value of the starting point for the gradient line.
- `START_Y` (int): The y-value of the starting point for the gradient line.
- `END_X` (int): The x-value of the ending point for the gradient line.
- `END_Y` (int): The y-value of the ending point for the gradient line.
- `START_COLOR` ([int]): A 0-255 RGB color code to be used as a starting color.
- `END_COLOR` ([int]): A 0-255 RGB color code to be used as a ending color.

## Line Drawing

## Point Drawing

## Future Work

Something that I would like to do with this is to make the points move more, currently it appears like the points slowly oscillate back and forth. One way to do this is to potentially add a 'drift' to the points. Constantly pulling them one direction such that they always appear back where they started. Another thing I would like to do is add an HCL gradient. Finally, I would like the ability to change how the OpenSimplex oscillates. I could do this by changing the circle that the OpenSimplex function takes to instead be a different, smooth, continuous shape. Perhaps randomly generated or a set shape. A potential shape could be a sort of infinity symbol.
