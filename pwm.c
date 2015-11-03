#include <unistd.h>
#include <stdio.h>

FILE *slots;
FILE *period;
FILE *duty;
FILE *run;

int main(void) {
slots = fopen("/sys/devices/bone_capemgr.9/slots", "w");

fprintf(slots, "am33xx_pwm");

fprintf(slots, "bonw_pwm_P9_14");

fclose(slots);



period = fopen("/sys/devices/ocp.3/pwm_test_P9_14.22/period", "w");
duty = fopen("/sys/devices/ocp.3/pwm_test_P9_14.22/duty", "w");
run = fopen("/sys/devices/ocp.3/pwm_test_P9_14.22/run", "w");


fprintf(period, "400000");
int intensity = 0;
fprintf(duty, "0");

fprintf(run, "1");

char buffer[7];


while (1) {
	if (intensity > 300000) {
		intensity += 1;
	} else {
		intensity = 0;
	}
	sprintf(buffer, "%d", intensity);
	fprintf(duty, "%s", buffer);
	//usleep(1 * 1000);
}


fclose(period);
fclose(duty);
fclose(run);

return 0;
}


