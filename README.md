> this program only for **GNU/linux**


# how it's works
this program get the battery *chagrge now* from`/sys/class/power_supply/BAT0/subsystem/BAT0/charge_now` and *charge_full"* from `/sys/class/power_supply/BAT0/subsystem/BAT0/charge_full` , the values are string `text-based` .

so after get them the program uses `src/strToNum.c` module to convert it to a `unsigned long int` .

then the program get the power percentage value by **((charge_now /charge_full) * 100 )** .

When the battery reaches a certain level, the program will notify the user using `notify-send` and play a sound using `aplay` from `/assets/sound.wav`. For more details, check the source code at `/src/main.c`.

# compile the program
1. make sure *make* installed on your machine you also need *aplay* utility.
2. in the root directory run `make folders` to creaet `'/obj/'` and `'/bin/'` folders .
> **obj/** folder contain the object code
> **bin/** will contain the executable program
3. then run in the root also run `make` to **compile** the program and put the executable in `'/bin/'` folder .
4. to run the program run `make play`.

# usage
1. run the *binary* like any CLI tool from the trminal :
```bash
./prog
```
> Make sure `/assets/sound.wav` is in the current working directory.
### flages
the is no flgaes right now , but comming soon.
