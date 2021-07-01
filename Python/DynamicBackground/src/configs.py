import json
import os

def _getConfigs():
    abs_path = os.path.abspath(os.path.dirname(__file__))
    with open(f'{abs_path}/../config.json') as configs:
        return json.load(configs)

CONFIGS = _getConfigs()
POINT_CONFIGS = CONFIGS["POINT_CONFIGS"]
BORDER_CONFIGS = POINT_CONFIGS["BORDER_CONFIGS"]
DRIFTING_CONFIGS = POINT_CONFIGS["DRIFTING_CONFIGS"]
TRIANGLE_COLORING_CONFIGS = CONFIGS["TRIANGLE_COLORING_CONFIGS"]
LINE_DRAWING_CONFIGS = CONFIGS["LINE_DRAWING_CONFIGS"]
POINT_DRAWING_CONFIGS = CONFIGS["POINT_DRAWING_CONFIGS"]
