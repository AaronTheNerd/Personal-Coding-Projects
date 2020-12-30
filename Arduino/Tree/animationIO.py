from animation import Animation, Color, Frame

def exportAnimation(animation, out_name='out'):
    file = open(out_name, 'wb')
    file.write((animation.repeat & 0xFF).to_bytes(length=1, byteorder='big', signed=False))
    file.write((len(animation.frames) & 0xFFFFFFFF).to_bytes(length=4, byteorder='big', signed=False))
    for i in range(len(animation.frames)):
        file.write((animation.frames[i].hold).to_bytes(length=2, byteorder='big', signed=False))
        file.write(len(animation.frames[i].leds).to_bytes(length=1, byteorder='big', signed=False))
        for key, val in animation.frames[i].leds.items():
            file.write(key.to_bytes(length=1, byteorder='big', signed=False))
            file.write(val.red.to_bytes(length=1, byteorder='big', signed=False))
            file.write(val.green.to_bytes(length=1, byteorder='big', signed=False))
            file.write(val.blue.to_bytes(length=1, byteorder='big', signed=False))
    file.close()


def importAnimation(filename="out"):
    file = open(filename, 'rb')
    repeat = int.from_bytes(file.read(1), byteorder='big', signed=False)
    animation = Animation([], repeat)
    frames_count = int.from_bytes(file.read(4), byteorder='big', signed=False)
    animation.frames = [Frame(100, {}) for i in range(frames_count)]
    for i in range(frames_count):
        frame_hold = int.from_bytes(file.read(2), byteorder='big', signed=False)
        animation.frames[i].hold = frame_hold
        frame_led_count = int.from_bytes(file.read(1), byteorder='big', signed=False)
        for j in range(frame_led_count):
            frame_led_index = int.from_bytes(file.read(1), byteorder='big', signed=False)
            frame_led_red = int.from_bytes(file.read(1), byteorder='big', signed=False)
            frame_led_green = int.from_bytes(file.read(1), byteorder='big', signed=False)
            frame_led_blue = int.from_bytes(file.read(1), byteorder='big', signed=False)
            animation.frames[i].leds[frame_led_index] = Color(frame_led_red, frame_led_green, frame_led_blue)
    return animation


if __name__ == "__main__":
    animation = Animation([], 0)
    '''
    # animation.chasingLights(repeat=2)
    animation.colorChanging(repeat=1)
    animation.singularColorSwapping(repeat=20, hold=1000)
    animation.singularColorSwapping(color1=Color(0, 0, 255), color2=Color(255, 255, 0), repeat=20, hold=1000)
    animation.multipleColorSwapping(repeat=3)
    animation.multipleColorSwapping(color1=Color(0, 0, 255), color2=Color(255, 255, 0), repeat=3)
    animation.multipleColorSwapping(multiple=7, repeat=3)
    animation.boop(repeat=2)
    animation.snake(repeat=2)
    animation.gradualColorChange(repeat=2)
    animation.gradualColorChange(color1=Color(0, 0, 255), color2=Color(255, 255, 0), repeat=2)
    animation.gradient(repeat=1)
    animation.spinningRainbow(repeat=3, hold=100)
    
    animation.spiral(repeat=3)
    '''
    animation.snow()
    exportAnimation(animation)
    '''
    animation_new = importAnimation()
    print("Animation: ")
    print(animation)
    print("Animation Imported: ")
    print(animation_new)
    if animation == animation_new:
        print("Conversion Worked")
    else:
        print("Conversion Failed")
    '''
