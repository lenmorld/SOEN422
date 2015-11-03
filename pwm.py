import Adafruit_BBIO.GPIO as GPIO
import Adafruit_BBIO.PWM as PWM
import time


PWM.cleanup()


x = 1

PWM.start("P8_13", x, 1000, 1)
while True:
	time.sleep(0.5)
	x+=25
	if x > 99:
		x = 1
	PWM.set_duty_cycle("P8_13", x)


PWM.stop("P8_13")
PWM.cleanup()
