# Dynamic Background
> Generates Triangular patterns which act as a seamless gif.



## Installation

*Python 3.8 required*

Required Python dependencies:
- [PIL](https://pillow.readthedocs.io/en/stable/index.html)
- [numpy](https://numpy.org/doc/stable/)
- [opensimplex](https://pypi.org/project/opensimplex/)

Will need some way to turn images into gifs. Whether by [website](https://ezgif.com/maker) or [command line](https://imagemagick.org/index.php). Personally I use the ImageMagick command:
```
convert -delay 13 -loop 0 <ABS_PATH>/<GIF_NUM>/*.bmp <GIF_NAME>.gif
```

## Usage example

I would recommend modifying gif_maker.py directly.

In the function `main` running the line `run()` will create a series of bitmaps at `<ABS_PATH>/<GIF_NUM>/` and an info.json which can be used to recreate the gif. This gif we be defined by the constants at the top of the file.

In the function `main` running the line `run_with_json()` when the constant `JSON_ABS_PATH` is correctly pointing to a valid json generated by a prior `run()` command. The series of bitmaps created by said `run()` command will be recreated at `<ABS_PATH>/<GIF_NUM>/` by seeding the triangulation functions with the same seed as previous.

Currently I have `info.json` in the root of this directory which shows an example of a valid json generated by a `run()` command. This `run()` command generated `gif5.gif` which is also included so you can ensure that your installation is working as expected.

## Future Work

Something that I would like to do with this is to make the points move more, currently it appears like the points slowly oscillate back and forth. One way to do this is to potentially add a 'drift' to the points. Constantly pulling them one direction such that they always appear back where they started. Another thing I would like to do is add an HCL gradient. Finally, I would like the ability to change how the OpenSimplex oscillates. I could do this by changing the circle that the OpenSimplex function takes to instead be a different, smooth, continuous shape. Perhaps randomly generated or a set shape. A potential shape could be a sort of infinity symbol.