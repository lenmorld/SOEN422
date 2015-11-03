//Blink led with four level of brightness

#include <stdio.h>
#include <stdlib.h>

FILE *exportFile;
FILE *frequency;
FILE *duty_cycle;
FILE *run;

exportFile = fopen("/sys/class/gpio/export", "w");

fprintf(exportFile, "23");

fclose(exportFile);

frequency = fopen("/sys/device
