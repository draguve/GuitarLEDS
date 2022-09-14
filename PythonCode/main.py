# Example showing use of HSV colors
import time
from neopixel import Neopixel

numpix = 52
pin = 27
strip = Neopixel(numpix, 0,pin, "GRB")

hue = 0
while(True):
    color = strip.colorHSV(hue, 255, 150)
    strip[0] = color
    strip.rotate_right(1)
    strip.show()
    hue += 360
    time.sleep_us(20000)
