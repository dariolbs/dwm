/* DWM - The dynamic window manager
 *        __                 
 *   ____/ /      ______ ___ 
 *  / __  / | /| / / __ `__ \
 * / /_/ /| |/ |/ / / / / / /
 * \__,_/ |__/|__/_/ /_/ /_/ 
 *
 */

/* appearance */
static unsigned int borderpx  = 1;        /* border pixel of windows */
static unsigned int snap      = 32;       /* snap pixel */
static int showbar            = 1;        /* 0 means no bar */
static int topbar             = 0;        /* 0 means bottom bar */
static const char *fonts[]          = { "JetBrainsMono:size=13" };
static const char dmenufont[]       = "JetBrainsMono:size=13";
static const char dmenu_boder[]     = "2";
static const char dmenu_lines[]     = "15";

/* Fallback colors for the ones that should be defined on Xresources */
static char normbgcolor[]           = "#222222";
static char normbordercolor[]       = "#444444";
static char normfgcolor[]           = "#bbbbbb";
static char selfgcolor[]            = "#eeeeee";
static char selbordercolor[]        = "#005577";
static char selbgcolor[]            = "#005577";

static int statussep = ';';     /* Statusline separator */

static char *colors[][3] = {
       /*               fg           bg           border   */
       [SchemeNorm] = { normfgcolor, normbgcolor, normbordercolor },
       [SchemeSel]  = { selfgcolor,  selbgcolor,  selbordercolor  },
};

/* Systray */
static const int systraypinningfailfirst = 1;           /* 1: if pinning fails, display systray on the first monitor, False: display systray on the last monitor*/
static const int showsystray        = 1;                /* 0 means no systray */
static const unsigned int systraypinning = 0;           /* 0: sloppy systray follows selected monitor, >0: pin systray to monitor X */
static const unsigned int systrayonleft = 0;            /* 0: systray in the right corner, >0: systray on left of status text */
static const unsigned int systrayspacing = 2;           /* systray spacing */

/* Behaviour */
static const int pointerfocus = 0;   /* 1 means the mouse pointer will be placed on the center of the window when changing focus */

/* tagging */
static const char *tags[] = { "1", "2", "3", "4", "5", "6", "7", "8", "9", "10" };

static const Rule rules[] = {
	/* xprop(1):
	 *	WM_CLASS(STRING) = instance, class
	 *	WM_NAME(STRING) = title
	 */
	/* class      instance    title       tags mask     isfloating   monitor */
	{ "Firefox",  NULL,       NULL,       1 << 8,       0,           -1 },
};

/* layout(s) */
static float mfact     = 0.55; /* factor of master area size [0.05..0.95] */
static int nmaster     = 1;    /* number of clients in master area */
static int resizehints = 1;    /* 1 means respect size hints in tiled resizals */
static const int lockfullscreen = 1; /* 1 will force focus on the fullscreen window */

static const Layout layouts[] = {
	/* symbol     arrange function */
	{ "[]=",      tile },    /* first entry is default */
	{ "><>",      NULL },    /* no layout function means floating behavior */
	{ "[M]",      monocle },
	{ "TTT",      bstack },
};

static const Attachm attmeth[] = {
	/* symbol      attach function */
    { "AD",       attachdefault },
    { "AB",       attachbottom },
};

static int attachdir          = 0;        /* Default attachment function */

/* key definitions */
#define MODKEY Mod4Mask
#define TAGKEYS(KEY,TAG) \
	{ MODKEY,                       KEY,      view,           {.ui = 1 << TAG} }, \
	{ MODKEY|ControlMask,           KEY,      toggleview,     {.ui = 1 << TAG} }, \
	{ MODKEY|ShiftMask,             KEY,      tag,            {.ui = 1 << TAG} }, \
	{ MODKEY|ControlMask|ShiftMask, KEY,      toggletag,      {.ui = 1 << TAG} },
/*
#define STACKKEYS(MOD,ACTION) \
	{ MOD, XK_j,     ACTION##stack, {INC(+1)}}, \
	{ MOD, XK_k,     ACTION##stack, {INC(-1)}}, \
	{ MOD, XK_grave, ACTION##stack, {.i = PREVSEL } }, \
	{ MOD, XK_q,     ACTION##stack, {.i = 0 } }, \
	{ MOD, XK_a,     ACTION##stack, {.i = 1 } }, \
	{ MOD, XK_z,     ACTION##stack, {.i = 2 } }, \
	{ MOD, XK_x,     ACTION##stack, {.i = -1 } },
*/

/* helper for spawning shell commands in the pre dwm-5.0 fashion */
#define SHCMD(cmd) { .v = (const char*[]){ "/bin/sh", "-c", cmd, NULL } }

/* commands */
static char dmenumon[2] = "0"; /* component of dmenucmd, manipulated in spawn() */
static const char *dmenucmd[] = { "dmenu_run", "-c", "-bw", dmenu_boder, "-l", dmenu_lines, "-b", "-m", dmenumon, "-fn", dmenufont, NULL };
static const char *termcmd[]  = { "st", NULL };

/*
 * Xresources preferences to load at startup
 */
ResourcePref resources[] = {
		{ "normbgcolor",        STRING,  &normbgcolor },
		{ "normbordercolor",    STRING,  &normbordercolor },
		{ "normfgcolor",        STRING,  &normfgcolor },
		{ "selbgcolor",         STRING,  &selbgcolor },
		{ "selbordercolor",     STRING,  &selbordercolor },
		{ "selfgcolor",         STRING,  &selfgcolor },
		{ "borderpx",          	INTEGER, &borderpx },
		{ "snap",          		INTEGER, &snap },
		{ "showbar",          	INTEGER, &showbar },
		{ "topbar",          	INTEGER, &topbar },
		{ "nmaster",          	INTEGER, &nmaster },
		{ "resizehints",       	INTEGER, &resizehints },
		{ "mfact",      	 	FLOAT,   &mfact },
};

static const Key keys[] = {
	/* modifier                     key        function        argument */
	{ MODKEY,                       XK_p,      spawn,          {.v = dmenucmd } },
	{ MODKEY,                       XK_Return, spawn,          {.v = termcmd } },
	{ MODKEY,                       XK_b,      togglebar,      {0} },
	{ MODKEY,                       XK_r,      togglerbar,     {0} },
	// { MODKEY,                       XK_v,      printdebug,     {0} },
	{ MODKEY,                       XK_s,      cycledirection, {0} },
	{ MODKEY,                       XK_a,      focusmaster,    {0} },
	{ MODKEY,                       XK_i,      incnmaster,     {.i = +1 } },
	{ MODKEY,                       XK_d,      incnmaster,     {.i = -1 } },
	{ MODKEY,                       XK_comma,  setmfact,           {.f = -0.05} },
	{ MODKEY,                       XK_period, setmfact,           {.f = +0.05} },
    /* Window managament using based vim bindings */
	{ MODKEY,                       XK_j,      focusdir,          {.i = DOWN} },
	{ MODKEY,                       XK_k,      focusdir,          {.i = UP} },
	{ MODKEY,                       XK_h,      focusdir,          {.i = LEFT} },
	{ MODKEY,                       XK_l,      focusdir,          {.i = RIGHT} },
	{ MODKEY|ShiftMask,             XK_j,      pushdir,           {.i = DOWN} },
	{ MODKEY|ShiftMask,             XK_k,      pushdir,           {.i = UP} },
	{ MODKEY|ShiftMask,             XK_h,      pushdir,           {.i = LEFT} },
	{ MODKEY|ShiftMask,             XK_l,      pushdir,           {.i = RIGHT} },
    /* Window managament using arrows*/
	{ MODKEY,                       XK_Down,   focusdir,          {.i = DOWN} },
	{ MODKEY,                       XK_Up,     focusdir,          {.i = UP} },
	{ MODKEY,                       XK_Right,  focusdir,          {.i = RIGHT} },
	{ MODKEY,                       XK_Left,   focusdir,          {.i = LEFT} },
	{ MODKEY|ShiftMask,             XK_Down,   pushdir,           {.i = DOWN} },
	{ MODKEY|ShiftMask,             XK_Up,     pushdir,           {.i = UP} },
	{ MODKEY|ShiftMask,             XK_Right,  pushdir,           {.i = RIGHT} },
	{ MODKEY|ShiftMask,             XK_Left,   pushdir,           {.i = LEFT} },

	{ MODKEY,                       XK_q,      killclient,     {0} },
	{ MODKEY,                       XK_t,      setlayout,      {.v = &layouts[0]} },
	{ MODKEY|ShiftMask,             XK_space,  setlayout,      {.v = &layouts[1]} },
	{ MODKEY,                       XK_m,      setlayout,      {.v = &layouts[2]} },
	{ MODKEY|ShiftMask,             XK_t,      setlayout,      {.v = &layouts[3]} },
	{ MODKEY,                       XK_space,  togglefloating, {0} },
	{ MODKEY,                       XK_f,      togglefullscr,  {0} },
	{ MODKEY|ShiftMask,             XK_f,      togglefakefullscr,  {0} },
	TAGKEYS(                        XK_1,                      0)
	TAGKEYS(                        XK_2,                      1)
	TAGKEYS(                        XK_3,                      2)
	TAGKEYS(                        XK_4,                      3)
	TAGKEYS(                        XK_5,                      4)
	TAGKEYS(                        XK_6,                      5)
	TAGKEYS(                        XK_7,                      6)
	TAGKEYS(                        XK_8,                      7)
	TAGKEYS(                        XK_9,                      8)
	TAGKEYS(                        XK_0,                      9)
	{ MODKEY|ShiftMask,             XK_e,      quit,           {0} },
    /* Unused
	{ MODKEY,                       XK_Return, zoom,           {0} },
	{ MODKEY,                       XK_Tab,    view,           {0} },
	{ MODKEY,                       XK_0,      view,           {.ui = ~0 } },
	{ MODKEY|ShiftMask,             XK_0,      tag,            {.ui = ~0 } },
	{ MODKEY,                       XK_f,      setlayout,      {.v = &layouts[1]} },
     */
};

/* button definitions */
/* click can be ClkTagBar, ClkLtSymbol, ClkStatusText, ClkWinTitle, ClkClientWin, or ClkRootWin */
static const Button buttons[] = {
	/* click                event mask      button          function        argument */
	{ ClkTagBar,            MODKEY,         Button1,        tag,            {0} },
	{ ClkTagBar,            MODKEY,         Button3,        toggletag,      {0} },
	{ ClkWinTitle,          0,              Button2,        zoom,           {0} },
	{ ClkStatusText,        0,              Button2,        spawn,          {.v = termcmd } },
	{ ClkClientWin,         MODKEY,         Button1,        movemouse,      {0} },
	{ ClkClientWin,         MODKEY,         Button2,        togglefloating, {0} },
	{ ClkClientWin,         MODKEY,         Button3,        resizemouse,    {0} },
	{ ClkTagBar,            0,              Button1,        view,           {0} },
	{ ClkTagBar,            0,              Button3,        toggleview,     {0} },
	{ ClkTagBar,            MODKEY,         Button1,        tag,            {0} },
	{ ClkTagBar,            MODKEY,         Button3,        toggletag,      {0} },
};
