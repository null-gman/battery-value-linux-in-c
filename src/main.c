#include <stdio.h>
#include <unistd.h> //sleep()
#include "strToNum.h"

#define PATH_BATT_CHARGE_NOW "/sys/class/power_supply/BAT0/subsystem/BAT0/charge_now"
#define PATH_BATT_CHARGE_FULL "/sys/class/power_supply/BAT0/subsystem/BAT0/charge_full"

typedef struct {
   LLINT powerFull;
   LLINT powerNow;
} power_t;


LLINT getFileNum (const char * path)
{
    FILE *pf= fopen(path, "r");
    if (!pf)
        return -1;
    char buffer[12] = {0};
    fgets(buffer,12,pf);
    fclose(pf);
    return stringToNum(buffer);
}

int getPowerPerS(power_t * myPower_t){
    /* !TODO!
            "need error checking";
            if the getFileNum() return an -1
    */
    myPower_t->powerNow = getFileNum(PATH_BATT_CHARGE_NOW);
    myPower_t->powerFull = getFileNum(PATH_BATT_CHARGE_FULL);

    return 0;
}

int main(void)
{

    power_t myPower_t = {0,0};

    while (1) {
            getPowerPerS(&myPower_t);
            /* to get percentage of value get the max of it and ( (value / max of if) * 100 ) */
            LLINT power_percentage = (LLINT) ( ((double)myPower_t.powerNow / (double) myPower_t.powerFull) * (double)100 );
            printf("power percentage : %lu%%\n",power_percentage);
            if (power_percentage <= 0) {
                break;
            }

            sleep(2);

    }
    return 0;
}
