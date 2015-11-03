#!/bin/sh
# Blink an LED on breadboard

PIN = "38"   # P8_12 is gpio1[6] = (32 * 1) + 6 = 38
GPIOPIN="/sys/class/gpio/gpio$PIN"
echo $GPIOPIN

echo 38 > /sys/class/gpio/export


if [ -d "$GPIOPIN" ]; then
	echo "Blinking LED connected to Pin $PIN ..."
else
	echo "Mapping GPIO pin to export file"
	echo $PIN > /sys/class/gpio/export
	echo "Blinking LED connected to Pin $PIN ..."
	sleep 1
fi

while true; do
	echo high > $GPIOPIN/direction
	sleep 2
	echo low > $GPIOPIN/direction
	sleep 2
done
