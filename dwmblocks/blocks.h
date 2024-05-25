//Modify this file to change what commands output to your statusbar, and recompile using the make command.
static const Block blocks[] = {
	/*Icon*/	/*Command*/		/*Update Interval*/	/*Update Signal*/
	{" vol: ", "~/.config/dwm/configs/dwmblocks/sb-volume",	            0,		10},
	{" | load: ", "sh ~/.config/dwm/configs/dwmblocks/cpu_load.sh",	    60,		0},
	{" | mem: ", "~/.config/dwm/configs/dwmblocks/sb-memory",	3,		0},
	{" | ", "date +'%b %d %H:%M;'",					            60,		0},
    /* Left second bar */
	{" ", "~/.config/dwm/configs/dwmblocks/sb-battery",	30,		0},
	{"", "echo ';'",	                                                        0,		0},
    /* Right second bar */
	{"", "uname -r ",	0,		0},
	{" | updates: ", "checkupdates | wc -l",	1800,		0},
	{" | ", "df | awk -f ~/.config/dwm/configs/dwmblocks/display_disks.awk",	60,		0},
};

//sets delimiter between status commands. NULL character ('\0') means no delimiter.
static char delim[] = "";
static unsigned int delimLen = 5;
