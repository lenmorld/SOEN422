PIN = "38"        # P8_12 is gpio1[6] = (32 * 1) + 6 = 38
GPIOPIN="/sys/class/gpio/gpio$PIN"
echo $GPIOPIN
if [ -d "$GPIOPIN" ]; then
	echo "FUCKL!!!!!"
	echo "Blinking LED connected to Pin $PIN ..."
fi
