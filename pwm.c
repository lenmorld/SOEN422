#include <unistd.h>
#include <stdio.h>

FILE *slots;
FILE *period;
FILE *duty;
FILE *run;

int main(void) {
slots = fopen("/sys/devices/bone_capemgr.9/slots", "w");

fprintf(slots, "am33xx_pwm");
fflush(slots);
fprintf(slots, "bonw_pwm_P9_14");
fflush(slots);

fclose(slots);



period = fopen("/sys/devices/ocp.3/pwm_test_P9_14.22/period", "w");
run = fopen("/sys/devices/ocp.3/pwm_test_P9_14.22/run", "w");

duty = fopen("/sys/devices/ocp.3/pwm_test_P9_14.22/duty", "w");


fprintf(period, "400000");
fflush(period);
fclose(period);


int intensity = 0;

fprintf(duty, "0");
fflush(duty);
fclose(duty);

fprintf(run, "1");
fflush(run);
fclose(run);


while (1) {

	duty = fopen("/sys/devices/ocp.3/pwm_test_P9_14.22/duty", "w");
	
	if (intensity < 320000) {
		intensity += 80000;
	} else {
		intensity = 0;
	}
	fprintf(duty, "%d", intensity);
	fflush(duty);
	fclose(duty);
	usleep(500000);
}



return 0;
}


