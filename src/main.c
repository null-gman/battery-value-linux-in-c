#include <stdio.h>
#include <stdlib.h> //system()
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

    /* notify-send  -t 4 <title> <content> && aplay <soundFile> */

    int isAvtive = 1;/* so the notification done once in the time for every value below */
    while (1) {
            getPowerPerS(&myPower_t);
            /* to get percentage of value get the max of it and ( (value / max of if) * 100 ) */
            LLINT power_percentage = (LLINT) ( ((double)myPower_t.powerNow / (double) myPower_t.powerFull) * (double)100 );
            printf("power percentage : %lu%%\n",power_percentage);
            switch (power_percentage) {
                case 100:
                case 95:
                case 90:
                case 82:
                    if (isAvtive)
                        system("notify-send  -t 4 \"battary\" \"battery is Battery is high\" && aplay ./assets/sound.wav");
                    isAvtive = 0;
                    break;
                case 45:
                case 40:
                case 30:
                case 20:
                case 15:
                case 10:
                case 5:
                case 3:
                case 2:
                    if (isAvtive)
                        system("notify-send  -t 4 \"battary\" \"battery is low\" && aplay ./assets/sound.wav");
                    isAvtive = 0;
                    break;
                case 1:
                    if (isAvtive)
                       system("notify-send  -t 4 \"battary\" \"the program will close\" && aplay ./assets/sound.wav");
                    isAvtive = 0;
                    goto END;
                    break;
                default:
                    /* After reaching another level, the program will be ready for the next notification. */
                    isAvtive = 1;
                    break;
            }
            sleep(2);
    }
END:
    return 0;
}
