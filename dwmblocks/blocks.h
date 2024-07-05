//Modify this file to change what commands output to your statusbar, and recompile using the make command.
static const Block blocks[] = {
	/*Icon*/	/*Command*/		/*Update Interval*/	/*Update Signal*/
	{"", "~/.config/dwm/statusbar/sb-volume",	            0,		10},
	{" ", "sh ~/.config/dwm/statusbar/cpu_load.sh",	    60,		0},
	{" ", "~/.config/dwm/statusbar/sb-memory",	3,		0},
	{" ", "date +'%b %d %H:%M;'",					            60,		0},
    /* Left second bar */
	{" ", "~/.config/dwm/statusbar/sb-battery",	30,		0},
	{"", "echo ';'",	                                                        0,		0},
    /* Right second bar */
	{"", "echo [$(uname -r)]",	0,		0},
	{" ", "echo [$(checkupdates | wc -l)U]",	1800,		0},
	{" ", "df | awk -f ~/.config/dwm/statusbar/display_disks.awk",	60,		0},
};

//sets delimiter between status commands. NULL character ('\0') means no delimiter.
static char delim[] = "";
static unsigned int delimLen = 5;
