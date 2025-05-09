/* See LICENSE file for copyright and license details. */

/* appearance */
static const unsigned int borderpx  = 1;        /* border pixel of windows */
static const unsigned int snap      = 32;       /* snap pixel */
static const int showbar            = 1;        /* 0 means no bar */
static const int topbar             = 1;        /* 0 means bottom bar */
static const char *fonts[]          = { "terminus:size=10" };
static const char dmenufont[]       = "terminus:size=10";
static const char col_gray1[]       = "#222222";
static const char col_gray2[]       = "#444444";
static const char col_gray3[]       = "#bbbbbb";
static const char col_gray4[]       = "#eeeeee";
static const char col_cyan[]        = "#005577";
static const char col_gray5[]       = "#8f8f8f";
static const char *colors[][3]      = {
	/*               fg         bg            border   */
	[SchemeNorm] = { col_gray3, col_gray1,    col_gray2 },
	[SchemeSel]  = { col_gray4, col_cyan,     col_gray5 },
};

/* tagging */
static const char *tags[] = { "1", "2", "3", "4", "5", "6", "7", "8", "9" };

static const Rule rules[] = {
	/* xprop(1):
	 *	WM_CLASS(STRING) = instance, class
	 *	WM_NAME(STRING) = title
	 */
	/* class             instance    title          tags mask     isfloating   monitor */
        { NULL,              NULL,       "screen_user", 1 << 0,       0,            0 },
        { NULL,              NULL,       "screen_ops",  1 << 1,       0,            0 },
        { NULL,              NULL,       "screen_apps", 1 << 2,       0,            0 },
        { "KeePassXC",       NULL,       NULL,          1 << 7,       0,            0 },
	{ "Pavucontrol",     NULL,       NULL,          1 << 8,       0,            0 },
	{ "pavucontrol",     NULL,       NULL,          1 << 8,       0,            0 },
	{ "Vieb",            NULL,       NULL,          1 << 0,       0,            1 },
	{ "firefox",         NULL,       NULL,          1 << 1,       0,            1 },
	{ "librewolf",       NULL,       NULL,          1 << 0,       0,            1 },
	{ "Tor Browser",     NULL,       NULL,          1 << 2,       0,            1 },
	{ "Zathura",         NULL,       NULL,          1 << 3,       0,            1 },
	{ "mpv",             NULL,       NULL,          1 << 8,       0,            1 },
	{ "Gimp",            NULL,       NULL,          0,            1,           -1 },
};

/* layout(s) */
static const float mfact     = 0.55; /* factor of master area size [0.05..0.95] */
static const int nmaster     = 1;    /* number of clients in master area */
static const int resizehints = 1;    /* 1 means respect size hints in tiled resizals */
static const int lockfullscreen = 1; /* 1 will force focus on the fullscreen window */

static const Layout layouts[] = {
	/* symbol     arrange function */
	{ "[]=",      tile },    /* first entry is default */
	{ "><>",      NULL },    /* no layout function means floating behavior */
	{ "[M]",      monocle },
};

/* key definitions */
#define MODKEY Mod4Mask
#define TAGKEYS(KEY,TAG) \
	{ MODKEY,                       KEY,      view,           {.ui = 1 << TAG} }, \
	{ MODKEY|ControlMask,           KEY,      toggleview,     {.ui = 1 << TAG} }, \
	{ MODKEY|ShiftMask,             KEY,      tag,            {.ui = 1 << TAG} }, \
	{ MODKEY|ControlMask|ShiftMask, KEY,      toggletag,      {.ui = 1 << TAG} },

/* helper for spawning shell commands in the pre dwm-5.0 fashion */
#define SHCMD(cmd) { .v = (const char*[]){ "/bin/sh", "-c", cmd, NULL } }

/* commands */
static char dmenumon[2] = "0"; /* component of dmenucmd, manipulated in spawn() */
static const char *dmenucmd[] = { "dmenu_run", "-m", dmenumon, "-fn", dmenufont, "-nb", col_gray1, "-nf", col_gray3, "-sb", col_cyan, "-sf", col_gray4, "-l", "15", NULL };
static const char *termcmd[]  = { "alacritty", NULL };
static const char *webcmd[] = { "vieb", NULL };
static const char *upvol[] = { "amixer", "set", "Master", "656+", NULL };
static const char *upvolbig[] = { "amixer", "set", "Master", "3280+", NULL };
static const char *downvol[] = { "amixer", "set", "Master", "656-", NULL };
static const char *downvolbig[] = { "amixer", "set", "Master", "3280-", NULL };
static const char *mutevol[] = { "amixer", "set", "Master", "toggle", NULL };
static const char *lock[] = { "slock", NULL };
static const char *screenshot[] = { "scrot", "-M", "1", "-F", "/home/dv/.cache/screenshots/%m-%d-%Y-%H-%M-%S.png", NULL };
static const char *screenshotselect[] = { "scrot", "-s", "-F", "/home/dv/.cache/screenshots/%m-%d-%Y-%H-%M-%S.png", NULL };
static const char *screenshotreborn[] = { "scrot", "-a", "160,0,1600,1200", "-F", "/home/dv/.cache/screenshots/%m %d-%Y-%H-%M-%S.png" };


static Key keys[] = {
	/*modifier                      key              function        argument */
	{ MODKEY,                       XK_comma,        spawn,          {.v = upvol } },
	{ MODKEY|ShiftMask,             XK_comma,        spawn,          {.v = downvol } },
	{ MODKEY|ControlMask,           XK_comma,        spawn,          {.v = mutevol } },
	{ MODKEY,                       XK_period,       spawn,          {.v = upvolbig } },
	{ MODKEY|ShiftMask,             XK_period,       spawn,          {.v = downvolbig } },
	{ MODKEY,                       XK_slash,        spawn,          {.v = lock } },
	{ MODKEY,                       XK_Return,       spawn,          {.v = termcmd } },
	{ MODKEY|ShiftMask,             XK_Return,       spawn,          {.v = webcmd } },
	{ MODKEY,                       XK_semicolon,    spawn,          {.v = dmenucmd } },
	{ MODKEY|ShiftMask,             XK_semicolon,    spawn,          {.v = screenshot } },
	{ MODKEY|ControlMask,           XK_semicolon,    spawn,          {.v = screenshotselect } },
	{ MODKEY,                       XK_b,            togglebar,      {0} },
	{ MODKEY,                       XK_bracketleft,  focusstack,     {.i = +1 } },
	{ MODKEY|ShiftMask,             XK_bracketleft,  focusstack,     {.i = -1 } },
	{ MODKEY,                       XK_i,            incnmaster,     {.i = +1 } },
	{ MODKEY,                       XK_d,            incnmaster,     {.i = -1 } },
	{ MODKEY,                       XK_r,            setmfact,       {.f = -0.05} },
	{ MODKEY,                       XK_l,            setmfact,       {.f = +0.05} },
	{ MODKEY|ShiftMask,             XK_Return,       zoom,           {0} },
	{ MODKEY,                       XK_Tab,          view,           {0} },
	{ MODKEY,                       XK_quoteright,   killclient,     {0} },
	{ MODKEY,                       XK_t,            setlayout,      {.v = &layouts[0]} },
	{ MODKEY,                       XK_f,            setlayout,      {.v = &layouts[1]} },
	{ MODKEY,                       XK_m,            setlayout,      {.v = &layouts[2]} },
	{ MODKEY|ShiftMask,             XK_f,            togglefullscr,  {0} },
	{ MODKEY,                       XK_space,        setlayout,      {0} },
	{ MODKEY|ShiftMask,             XK_space,        togglefloating, {0} },
	{ MODKEY,                       XK_0,            view,           {.ui = ~0 } },
	{ MODKEY|ShiftMask,             XK_0,            tag,            {.ui = ~0 } },
	{ MODKEY,                       XK_backslash,    focusmon,       {.i = -1 } },
	{ MODKEY|ShiftMask,             XK_backslash,    focusmon,       {.i = +1 } },
	{ MODKEY|ControlMask,           XK_backslash,    tagmon,         {.i = -1 } },
	{ MODKEY|ShiftMask|ControlMask, XK_backslash,    tagmon,         {.i = +1 } },
	{ MODKEY,                       XK_bracketright, viewnext,       {0} },
	{ MODKEY|ShiftMask,             XK_bracketright, viewprev,       {0} },
	{ MODKEY|ControlMask,           XK_bracketright, tagtonext,      {0} },
	{ MODKEY|ShiftMask|ControlMask, XK_bracketright, tagtoprev,      {0} },
	TAGKEYS(                        XK_1,                    0)
	TAGKEYS(                        XK_2,                    1)
	TAGKEYS(                        XK_3,                    2)
	TAGKEYS(                        XK_4,                    3)
	TAGKEYS(                        XK_5,                    4)
	TAGKEYS(                        XK_6,                    5)
	TAGKEYS(                        XK_7,                    6)
	TAGKEYS(                        XK_8,                    7)
	TAGKEYS(                        XK_9,                    8)
	{ MODKEY|ShiftMask,             XK_quoteright,   quit,           {0} },
};

/* button definitions */
/* click can be ClkTagBar, ClkLtSymbol, ClkStatusText, ClkWinTitle, ClkClientWin, or ClkRootWin */
static Button buttons[] = {
	/* click                event mask      button          function        argument */
	{ ClkLtSymbol,          0,              Button1,        setlayout,      {0} },
	{ ClkLtSymbol,          0,              Button3,        setlayout,      {.v = &layouts[2]} },
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

