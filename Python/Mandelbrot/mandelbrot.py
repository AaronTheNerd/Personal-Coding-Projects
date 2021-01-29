# Written by Aaron Barge

import cmath
from PIL import Image


color_map_wiki = [(66, 30, 15),
                  (25, 7, 26),
                  (9, 1, 47),
                  (4, 4, 73),
                  (0, 7, 100),
                  (12, 44, 138),
                  (24, 82, 177),
                  (57, 125, 209),
                  (134, 181, 229),
                  (211, 236, 248),
                  (241, 233, 191),
                  (248, 201, 95),
                  (255, 170, 0),
                  (204, 128, 0),
                  (153, 87, 0),
                  (106, 52, 3)]


color_map_coolors_trending = [(0x37, 0x6, 0x17),
                              (0x6a, 0x4, 0xf),
                              (0x9d, 0x2, 0x8),
                              (0xd0, 0, 0),
                              (0xdc, 0x2f, 0x2),
                              (0xe8, 0x5d, 0x4),
                              (0xf4, 0x8c, 0x6),
                              (0xfa, 0xa3, 0x7),
                              (0xff, 0xba, 0x8),
                              (0xfa, 0xa3, 0x7),
                              (0xf4, 0x8c, 0x6),
                              (0xe8, 0x5d, 0x4),
                              (0xdc, 0x2f, 0x2),
                              (0xd0, 0, 0),
                              (0x9d, 0x2, 0x8),
                              (0x6a, 0x4, 0xf),
                              (0x37, 0x6, 0x17)]


def printProgressBar (iteration, total, prefix = '', suffix = '', decimals = 1, length = 100, fill = '█', printEnd = "\r"):
    """
    Call in a loop to create terminal progress bar
    @params:
        iteration   - Required  : current iteration (Int)
        total       - Required  : total iterations (Int)
        prefix      - Optional  : prefix string (Str)
        suffix      - Optional  : suffix string (Str)
        decimals    - Optional  : positive number of decimals in percent complete (Int)
        length      - Optional  : character length of bar (Int)
        fill        - Optional  : bar fill character (Str)
        printEnd    - Optional  : end character (e.g. "\r", "\r\n") (Str)
    """
    percent = ("{0:." + str(decimals) + "f}").format(100 * (iteration / float(total)))
    filledLength = int(length * iteration // total)
    bar = fill * filledLength + '-' * (length - filledLength)
    print(f'\r{prefix} |{bar}| {percent}% {suffix}', end = printEnd)
    # Print New Line on Complete
    if iteration == total: 
        print()


def color_funct(color_map, c):
    return color_map[c % len(color_map)]


# ============================= ADDITIONAL INFO ============================= #
# A few presets: 
#   1080p:
#       width = 1920
#       aspect_ratio = 16 / 9
#   4K:
#       width = 4096
#       aspect_ratio = 1.9 / 1
#   UHD:
#       width = 3840
#       aspect_ratio = 16 / 9
# Important Note: The Mandelbrot set is symmetric about the x-axis, therefore
# to save processing time I have made the x-axis of the image always run
# through the center of the image. This means that setting the initial x value
# will bound the image's view to +/- initial x. The y-axis will then conform
# to the required aspect ratio.
# =========================================================================== #
def draw_full(max_iter=500, width=1920, aspect_ratio= 16/9, initial_point={'x':-2.5, 'y':-1.25}, color_map=color_map_wiki):
    height = int(round(width / aspect_ratio))
    size = width, height
    image = Image.new('RGB', size)
    pixels = image.load()
    it = 2 * abs(initial_point['y']) / height
    for i in range(width):
        r = i * it + initial_point['x']
        for j in range(height // 2):
            c = complex(r, j * it + initial_point['y'])
            z = complex(0, 0)
            color = (0, 0, 0)
            for k in range(max_iter):
                if abs(z) > 2:
                    if k > 0:
                        color = color_funct(color_map, k)
                    break
                z = z ** 2 + c
            pixels[i, j] = color
            pixels[i, height - j - 1] = color
        printProgressBar(i, width-1, prefix='Progress:', suffix='Complete', length=50)
    image.save('mandelbrot_q' + str(max_iter) + '_w' + str(width) + '_c2.tif')


# ============================= ADDITIONAL INFO ============================= #
# Presets:
#   these all have the aspect ratio 16 / 9 so they may have to be changed
#   Mandelbrot duplicate:
#       bounds={'x0':-1.8, 'y0':-0.0225, 'xf':-1.72, 'yf':0.0225}
#   Seahorse Valley:
#       bounds={'x0':-0.75, 'y0':0.096, 'xf':-0.742, 'yf':0.1005}
#   Elephant Vally:
#       bounds={'x0':0.29, 'y0':0.01225, 'xf':0.31, 'yf':0.001}
# =========================================================================== #
def draw_partial(folder='./', max_iter=500, width=1920, bounds={'x0':-1.80, 'y0':-0.0225, 'xf':-1.72, 'yf':0.0225}, color_map=color_map_wiki):
    x_range = abs(bounds['xf'] - bounds['x0'])
    y_range = abs(bounds['yf'] - bounds['y0'])
    height = int(round(width * y_range / x_range))
    size = width, height
    image = Image.new('RGB', size)
    pixels = image.load()
    it = y_range / height
    for i in range(width):
        r = i * it + bounds['x0']
        for j in range(height):
            c = complex(r, j * it + bounds['y0'])
            z = complex(0, 0)
            color = (0, 0, 0)
            for k in range(max_iter):
                if abs(z) > 2:
                    if k > 0:
                        color = color_funct(color_map, k)
                    break
                z = z ** 2 + c
            pixels[i, j] = color
        printProgressBar(i, width-1, prefix='Progress:', suffix='Complete', length=50)
    image.save(folder + 'mandelbrot_partial_q' + str(max_iter) + '_w' + str(width) + '_c2.tif')


if __name__ == '__main__':
    #draw_full()
    draw_partial(folder='./elephant/', max_iter=1000, width=1920, bounds={'x0':0.29, 'y0':0.01225, 'xf':0.31, 'yf':0.001})
