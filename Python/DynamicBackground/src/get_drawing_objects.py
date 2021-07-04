from configs import TRIANGLE_COLORING_CONFIGS, LINE_DRAWING_CONFIGS, POINT_DRAWING_CONFIGS
from triangle_coloring import *
from line_drawing import *
from point_drawing import *

def get_triangle_coloring_object():
    if TRIANGLE_COLORING_CONFIGS["TYPE"] == 'PlainColor':
        return PlainColor(
                color=TRIANGLE_COLORING_CONFIGS["COLOR"])
    elif TRIANGLE_COLORING_CONFIGS["TYPE"] == 'HSVLinearGradientContinuous':
        return HSVLinearGradientContinuous(
                start_x=TRIANGLE_COLORING_CONFIGS["START_X"],
                start_y=TRIANGLE_COLORING_CONFIGS["START_Y"],
                end_x=TRIANGLE_COLORING_CONFIGS["END_X"],
                end_y=TRIANGLE_COLORING_CONFIGS["END_Y"],
                start_color=TRIANGLE_COLORING_CONFIGS["START_COLOR"],
                end_color=TRIANGLE_COLORING_CONFIGS["END_COLOR"])
    elif TRIANGLE_COLORING_CONFIGS["TYPE"] == 'HSVLinearGradientDiscrete':
        return HSVLinearGradientDiscrete(
                start_x=TRIANGLE_COLORING_CONFIGS["START_X"],
                start_y=TRIANGLE_COLORING_CONFIGS["START_Y"],
                end_x=TRIANGLE_COLORING_CONFIGS["END_X"],
                end_y=TRIANGLE_COLORING_CONFIGS["END_Y"],
                start_color=TRIANGLE_COLORING_CONFIGS["START_COLOR"],
                end_color=TRIANGLE_COLORING_CONFIGS["END_COLOR"],
                num_of_colors=TRIANGLE_COLORING_CONFIGS["NUM_OF_COLORS"])
    elif TRIANGLE_COLORING_CONFIGS["TYPE"] == 'HSVExponentialGradientContinuous':
        return HSVExponentialGradientContinuous(
                start_x=TRIANGLE_COLORING_CONFIGS["START_X"],
                start_y=TRIANGLE_COLORING_CONFIGS["START_Y"],
                end_x=TRIANGLE_COLORING_CONFIGS["END_X"],
                end_y=TRIANGLE_COLORING_CONFIGS["END_Y"],
                start_color=TRIANGLE_COLORING_CONFIGS["START_COLOR"],
                end_color=TRIANGLE_COLORING_CONFIGS["END_COLOR"],
                alpha=TRIANGLE_COLORING_CONFIGS["ALPHA"])
    elif TRIANGLE_COLORING_CONFIGS["TYPE"] == 'FlatShader':
        return FlatShader(
                cam_pos=TRIANGLE_COLORING_CONFIGS["CAM_POS"],
                gain=TRIANGLE_COLORING_CONFIGS["GAIN"]
        )
    else:
        raise RuntimeError(f"Incorrect 'TRIANGLE_COLORING_CONFIGS' attribute 'TYPE': {TRIANGLE_COLORING_CONFIGS['TYPE']}")

def get_line_drawing_object():
    if not LINE_DRAWING_CONFIGS["DRAW_LINES"]:
        return None
    if LINE_DRAWING_CONFIGS["TYPE"] == 'SolidLine':
        return SolidLine(
                color=LINE_DRAWING_CONFIGS["COLOR"],
                width=LINE_DRAWING_CONFIGS["WIDTH"])
    elif LINE_DRAWING_CONFIGS["TYPE"] == 'FadingLine':
        return FadingLine(
                start_color=LINE_DRAWING_CONFIGS["START_COLOR"],
                end_color=LINE_DRAWING_CONFIGS["END_COLOR"],
                width=LINE_DRAWING_CONFIGS["WIDTH"],
                alpha=LINE_DRAWING_CONFIGS["ALPHA"])
    raise RuntimeError(f"Incorrect 'LINE_DRAWING_CONFIGS' attribute 'TYPE': {LINE_DRAWING_CONFIGS['TYPE']}")

def get_point_drawing_object():
    if not POINT_DRAWING_CONFIGS["DRAW_POINTS"]:
        return None
    if POINT_DRAWING_CONFIGS["TYPE"] == 'PlainPoint':
        return PlainPoint(
                color=POINT_DRAWING_CONFIGS["COLOR"],
                width=POINT_DRAWING_CONFIGS["WIDTH"]
        )
    raise RuntimeError(f"Incorrect 'POINT_DRAWING_CONFIGS' attribute 'TYPE': {POINT_DRAWING_CONFIGS['TYPE']}")
