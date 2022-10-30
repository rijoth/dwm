/* custom dwm fork by Rijo - https://github.com/rijoth/dwm */

/* See LICENSE file for copyright and license details. */

#include <X11/XF86keysym.h>

/* appearance */
static const unsigned int borderpx  = 2;        /* border pixel of windows */
static const unsigned int snap      = 32;       /* snap pixel */
static const unsigned int systraypinning = 0;   /* 0: sloppy systray follows selected monitor, >0: pin systray to monitor X */
static const unsigned int systrayonleft = 0;   	/* 0: systray in the right corner, >0: systray on left of status text */
static const unsigned int systrayspacing = 2;   /* systray spacing */
static const int systraypinningfailfirst = 1;   /* 1: if pinning fails, display systray on the first monitor, False: display systray on the last monitor*/
static const int showsystray        = 1;     /* 0 means no systray */
static const int showbar            = 1;     /* 0 means no bar */
static const int topbar             = 1;     /* 0 means bottom bar */
/* fonts */
static const char *fonts[]          = {"Jetbrains Mono:size=9","fontawesome:size=8","monospace:size=10"};
static const char dmenufont[]       = "Jetbrains Mono:size=9";
/* colors */
static const char col_gray1[]       = "#282828";
static const char col_gray2[]       = "#32302f";  /* prev #444444 */
static const char col_gray3[]       = "#ebdbb2";  /* non highlighted text color */
static const char col_gray4[]       = "#282828"; /* bar font color */
static const char col_cyan[]        = "#689d6a"; /* frame and title bar color */
static const char *colors[][3]      = {
	/*               fg         bg         border   */
	[SchemeNorm] = { col_gray3, col_gray1, col_gray2 },
	[SchemeSel]  = { col_gray4, col_cyan,  col_cyan  },
};

/* tagging */
static const char *tags[] = { "1", "2", "3", "4", "5", "6", "7", "8", "9" };

static const Rule rules[] = {
	/* xprop(1):
	 *	WM_CLASS(STRING) = instance, class
	 *	WM_NAME(STRING) = title
	 */
	/* class      instance    title       tags mask     isfloating   monitor */
	{ "Gimp",     NULL,       NULL,       0,            1,           -1 },
	/* { "Firefox",  NULL,       NULL,       1 << 8,       0,           -1 },*/
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
static const char *dmenucmd[] = { "dmenu_run", "-p", "run:", "-fn", dmenufont, "-nb", col_gray1, "-nf", col_gray3, "-sb", col_cyan, "-sf", col_gray4, NULL };
static const char *termcmd[]  = { "st", NULL };

/* custom commands */
static const char *firefox[] = { "firefox", NULL }; /* browser */
/*  static const char *files[]  = { "thunar", NULL }; file manager */
static const char *vifm[] = {"st", "-e", "vifm", NULL}; /* file manager */
static const char *exitcmd[]  = {"/home/rijo/.suckless/scripts/exit_script", NULL }; /* exit/quit prompt */
static const char *screenshot[]  = { "flameshot", "gui", NULL }; /* screenshot tool */
static const char *brightness_notif[] = {"/home/rijo/.suckless/scripts/brightness_notif", NULL }; /* notifications */
static const char *slock[] = { "slock", NULL }; /* lockscreen */

/* volume/brightness keys bindings */
static const char *upvol[]   = { "/usr/bin/pactl", "set-sink-volume", "0", "+1%",     NULL };
static const char *downvol[] = { "/usr/bin/pactl", "set-sink-volume", "0", "-1%",     NULL };
static const char *mutevol[] = { "/usr/bin/pactl", "set-sink-mute",   "0", "toggle",  NULL };
static const char *brightdown[] = { "light", "-U", "1", NULL };
static const char *brightup[]   = { "light", "-A", "1", NULL };

static const Key keys[] = {
	/* modifier                     key        function        argument */
	{ MODKEY,                       XK_p,      spawn,          {.v = dmenucmd } },
	{ MODKEY|ShiftMask,             XK_Return, spawn,          {.v = termcmd } },
	{ MODKEY,                       XK_b,      togglebar,      {0} },
	{ MODKEY,                       XK_j,      focusstack,     {.i = +1 } },
	{ MODKEY,                       XK_k,      focusstack,     {.i = -1 } },
	{ MODKEY,                       XK_i,      incnmaster,     {.i = +1 } },
	{ MODKEY,                       XK_d,      incnmaster,     {.i = -1 } },
	{ MODKEY,                       XK_h,      setmfact,       {.f = -0.05} },
	{ MODKEY,                       XK_l,      setmfact,       {.f = +0.05} },
	{ MODKEY,                       XK_Return, zoom,           {0} },
	{ MODKEY,                       XK_Tab,    view,           {0} },
	{ MODKEY|ShiftMask,             XK_c,      killclient,     {0} },
	{ MODKEY,                       XK_t,      setlayout,      {.v = &layouts[0]} },
	{ MODKEY,                       XK_f,      setlayout,      {.v = &layouts[1]} },
	{ MODKEY,                       XK_m,      setlayout,      {.v = &layouts[2]} },
	{ MODKEY,                       XK_space,  setlayout,      {0} },
	{ MODKEY|ShiftMask,             XK_space,  togglefloating, {0} },
	{ MODKEY,                       XK_0,      view,           {.ui = ~0 } },
	{ MODKEY|ShiftMask,             XK_0,      tag,            {.ui = ~0 } },
	{ MODKEY,                       XK_comma,  focusmon,       {.i = -1 } },
	{ MODKEY,                       XK_period, focusmon,       {.i = +1 } },
	{ MODKEY|ShiftMask,             XK_comma,  tagmon,         {.i = -1 } },
	{ MODKEY|ShiftMask,             XK_period, tagmon,         {.i = +1 } },
	TAGKEYS(                        XK_1,                      0)
	TAGKEYS(                        XK_2,                      1)
	TAGKEYS(                        XK_3,                      2)
	TAGKEYS(                        XK_4,                      3)
	TAGKEYS(                        XK_5,                      4)
	TAGKEYS(                        XK_6,                      5)
	TAGKEYS(                        XK_7,                      6)
	TAGKEYS(                        XK_8,                      7)
	TAGKEYS(                        XK_9,                      8)
	/*{ MODKEY|ShiftMask,             XK_q,      quit,           {0} },*/
	/* custom key bindings */

	/* volume/brightness keys */
	{ 0,              XF86XK_AudioLowerVolume, spawn,        {.v = downvol } },
	{ 0,                     XF86XK_AudioMute, spawn,        {.v = mutevol } },
	{ 0,              XF86XK_AudioRaiseVolume, spawn,        {.v = upvol   } },
        { 0,             XF86XK_MonBrightnessDown, spawn,        { .v = brightdown } },
        { 0,             XF86XK_MonBrightnessDown, spawn,        {.v = brightness_notif } }, 
        { 0,               XF86XK_MonBrightnessUp, spawn,        { .v = brightup } },
        { 0,               XF86XK_MonBrightnessUp, spawn,        {.v = brightness_notif } }, 

	/* Apps Launched with SUPER + ALT + KEY */
	/* { MODKEY|Mod1Mask,              XK_f,      spawn,          {.v = files } },*/
        { MODKEY|Mod1Mask,              XK_l,      spawn,          {.v = slock } },

	/* Apps Launched with SUPER + Shift + KEY */
	{ MODKEY|ShiftMask,             XK_s,      spawn,          {.v = screenshot } },
	{ MODKEY|ShiftMask,             XK_v,      spawn,          {.v = vifm } },
        { MODKEY|ShiftMask,             XK_b,      spawn,          {.v = firefox}},
	{ MODKEY|ShiftMask,             XK_q,        spawn,           {.v = exitcmd } },
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

