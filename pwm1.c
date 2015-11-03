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


fclose(period);
fclose(duty);
fclose(run);

return 0;
}


