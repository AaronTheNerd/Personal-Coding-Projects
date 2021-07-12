from configs import TRIANGLE_COLORING_CONFIGS, LINE_DRAWING_CONFIGS, POINT_DRAWING_CONFIGS
from triangle_coloring import *
from line_drawing import *
from point_drawing import *

def get_triangle_coloring_object():
    if TRIANGLE_COLORING_CONFIGS["TYPE"] == 'PlainColor':
        return PlainColor(**TRIANGLE_COLORING_CONFIGS["KWARGS"])
    elif TRIANGLE_COLORING_CONFIGS["TYPE"] == 'HSVLinearGradientContinuous':
        return HSVLinearGradientContinuous(**TRIANGLE_COLORING_CONFIGS["KWARGS"])
    elif TRIANGLE_COLORING_CONFIGS["TYPE"] == 'HSVLinearGradientDiscrete':
        return HSVLinearGradientDiscrete(**TRIANGLE_COLORING_CONFIGS["KWARGS"])
    elif TRIANGLE_COLORING_CONFIGS["TYPE"] == 'HSVExponentialGradientContinuous':
        return HSVExponentialGradientContinuous(**TRIANGLE_COLORING_CONFIGS["KWARGS"])
    elif TRIANGLE_COLORING_CONFIGS["TYPE"] == 'AmbientShader':
        return AmbientShader(**TRIANGLE_COLORING_CONFIGS["KWARGS"])
    elif TRIANGLE_COLORING_CONFIGS["TYPE"] == 'MultiLightShader':
        return MultiLightShader(**TRIANGLE_COLORING_CONFIGS["KWARGS"])
    else:
        raise RuntimeError(f"Incorrect 'TRIANGLE_COLORING_CONFIGS' attribute 'TYPE': {TRIANGLE_COLORING_CONFIGS['TYPE']}")

def get_line_drawing_object():
    if not LINE_DRAWING_CONFIGS["DRAW_LINES"]:
        return None
    if LINE_DRAWING_CONFIGS["TYPE"] == 'SolidLine':
        return SolidLine(**LINE_DRAWING_CONFIGS["KWARGS"])
    elif LINE_DRAWING_CONFIGS["TYPE"] == 'FadingLine':
        return FadingLine(**LINE_DRAWING_CONFIGS["KWARGS"])
    raise RuntimeError(f"Incorrect 'LINE_DRAWING_CONFIGS' attribute 'TYPE': {LINE_DRAWING_CONFIGS['TYPE']}")

def get_point_drawing_object():
    if not POINT_DRAWING_CONFIGS["DRAW_POINTS"]:
        return None
    if POINT_DRAWING_CONFIGS["TYPE"] == 'PlainPoint':
        return PlainPoint(**POINT_DRAWING_CONFIGS["KWARGS"])
    raise RuntimeError(f"Incorrect 'POINT_DRAWING_CONFIGS' attribute 'TYPE': {POINT_DRAWING_CONFIGS['TYPE']}")
