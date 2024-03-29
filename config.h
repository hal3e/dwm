/* Dwm config */
#include <X11/XF86keysym.h>

static const unsigned int borderpx    = 1;   /* Border pixel of windows */
static const unsigned int snap        = 8;  /* Snap pixel */
static const unsigned int gappx       = 3;   /* Pixel gap between clients */
static const int smartgaps            = 0;   /* 1 means no outer gap when there is only one window */
static const int showbar              = 1;   /* 0 means no bar */
static const int topbar               = 1;   /* 0 means bottom bar */
static const int horizpadbar          = -5;  /* Horizontal padding for statusbar */
static const int vertpadbar           = 8;   /* Vertical padding for statusbar */

static const char *fonts[]            = {"Hack:size=11:antialias=true:autohint=true",
                                         "Font Awesome 6 Free Solid:size=9:antialias=true:autohint=true",
                                         "Font Awesome 6 Brands:size=9:antialias=true:autohint=true"};

static const char nord0[]  = "#24273A";
static const char nord2[]  = "#75829c";
static const char nord5[]  = "#EAEEFA";
static const char nord10[] = "#8AADF4";
static const char nord7[]  = "#8BD5CA";
static const char nord11[] = "#ED8796";
static const char nord13[] = "#EED49F";
static const char nord14[] = "#A6DA95";
static const char nord15[] = "#F5BDE6";

static const unsigned int baralpha    = 0xff; /* 0xff is no transparency */
static const unsigned int borderalpha = OPAQUE;

static const char *colors[][3]        = {
	/*                    fg      bg      border */
	[SchemeNord10]    = { nord10, nord0,  nord2},
	[SchemeNord7]     = { nord7,  nord0,  nord0 },
	[SchemeNord12]    = { nord11, nord0,  nord0 },
	[SchemeNord13]    = { nord13, nord0,  nord0 },
	[SchemeNord15]    = { nord15, nord0,  nord0 },
	[SchemeNord14]    = { nord14, nord0,  nord0 },
	[SchemeNord2]     = { nord2,  nord0,  nord0 },
	[SchemeNorm]      = { nord5,  nord0,  nord0 },
	[SchemeUrgent]    = { nord11, nord0,  nord0 },
};

static const unsigned int alphas[][3] = {
	/*                fg      bg        border */
	[SchemeNord10]    = { OPAQUE, baralpha, borderalpha },
	[SchemeNord7]     = { OPAQUE, baralpha, borderalpha},
	[SchemeNord12]    = { OPAQUE, baralpha, borderalpha },
	[SchemeNord13]    = { OPAQUE, baralpha, borderalpha },
	[SchemeNord15]    = { OPAQUE, baralpha, borderalpha },
	[SchemeNord14]    = { OPAQUE, baralpha, borderalpha },
	[SchemeNord2]     = { OPAQUE, baralpha, borderalpha},
	[SchemeNorm]      = { OPAQUE, baralpha, borderalpha },
	[SchemeUrgent]    = { OPAQUE, baralpha, borderalpha },
};

/* static const char *tags[] =   { "", "", "", "", "", "", "", "", "" }; */
static const char *tags[] =   { "", "", "", "", ""};

static const Rule rules[] = {
	/* Class       Itstance    Title  Tags Mask  Isfloating  Monitor */
	{ NULL,        "float-m",  NULL,  0,         1,          -1 },
};

/* Layout(s) */
static const float mfact     = 0.65; /* Factor of master area size [0.05..0.95] */
static const int nmaster     = 1;    /* Number of clients in master area */
static const int resizehints = 0;    /* 1 means respect size hints in tiled resizals */

#include "layouts.c"
static const Layout layouts[] = {
	/* symbol  arrange function */
	{ "| ",  tile },  /* First entry is default */
 	{ "| ",  centeredmaster },
	{ "| ",  monocle },
	{ "| ",  grid },
	{ "| ",  NULL },  /* No layout function means floating behavior */
};

/* Key definitions */
#define MODKEY  Mod1Mask
#define MODKEY2 Mod5Mask
#define CMD(cmd) { .v = (const char*[]){ "/bin/sh", "-c", cmd, NULL } }
#define TAGKEYS(KEY,TAG) \
	{ MODKEY,                       KEY,      view,           {.ui = 1 << TAG} }, \
	{ MODKEY|ControlMask|ShiftMask, KEY,      toggleview,     {.ui = 1 << TAG} }, \
	{ MODKEY|ShiftMask,             KEY,      tag,            {.ui = 1 << TAG} }, \
	{ MODKEY|ControlMask,           KEY,      toggletag,      {.ui = 1 << TAG} },

static Key keys[] = {
	/* Modifier             Key        Function        Argument */
	{ MODKEY,               XK_v,          togglebar,      {0} },
	{ MODKEY|ShiftMask,     XK_n,          rotatestack,    {.i = +1 } },
	{ MODKEY|ShiftMask,     XK_e,          rotatestack,    {.i = -1 } },
	{ MODKEY,               XK_n,          focusstack,     {.i = +1 } },
	{ MODKEY,               XK_e,          focusstack,     {.i = -1 } },
	{ MODKEY|ControlMask,   XK_e,          incnmaster,     {.i = +1 } },
	{ MODKEY|ControlMask,   XK_n,          incnmaster,     {.i = -1 } },
	{ MODKEY|ControlMask,   XK_y,          setmfact,       {.f = -0.05} },
	{ MODKEY|ControlMask,   XK_o,          setmfact,       {.f = +0.05} },
	{ MODKEY,               XK_i,          zoom,           {0} }, /* Move window to master */
	{ MODKEY,               XK_apostrophe, focusmaster,    {0} },
	{ MODKEY,               XK_k,          killclient,     {0} },

  /* Layout manipulation */
	{ MODKEY,               XK_Tab,    cyclelayout,    {.i = -1 } },
	{ MODKEY|ShiftMask,     XK_Tab,    cyclelayout,    {.i = +1 } },
	{ MODKEY,               XK_space,  togglefloating, {0} },

  /* Switch to specific layouts */
	{ MODKEY,               XK_l,      setlayout,      {.v = &layouts[0]} },
	{ MODKEY,               XK_comma,  setlayout,      {.v = &layouts[1]} },
	{ MODKEY,               XK_period, setlayout,      {.v = &layouts[2]} },
	{ MODKEY,               XK_slash,  setlayout,      {.v = &layouts[3]} },
	{ MODKEY,               XK_minus,  setlayout,      {.v = &layouts[4]} },

	{ MODKEY|ControlMask,           XK_0,    tag,      {.ui = ~0 } },
	{ MODKEY|ControlMask|ShiftMask, XK_0,   view,      {.ui = ~0 } },

  /* Monitor manipulation */
	{ MODKEY,               XK_y,     focusmon,        {.i = -1 } },
	{ MODKEY,               XK_o,     focusmon,        {.i = +1 } },
	{ MODKEY|ShiftMask,     XK_y,     tagmon,          {.i = -1 } },
	{ MODKEY|ShiftMask,     XK_o,     tagmon,          {.i = +1 } },

  /* Launch progarms */
	{ MODKEY,               XK_1,      spawn,          CMD("~/bin/change-layout.sh workman") },
    { MODKEY,               XK_2,      spawn,          CMD("~/bin/change-layout.sh us") },
	{ MODKEY,               XK_r,      spawn,          CMD("~/bin/connect-bt-earp.sh") },
	{ MODKEY2,              XK_e,      spawn,          CMD("~/bin/connect-bt-keyb.sh") },
	{ MODKEY2,              XK_s,      spawn,          CMD("~/bin/sk-lunch.sh") },
	{ MODKEY2,              XK_b,      spawn,          CMD("st -T '~'") },
	{ MODKEY2,              XK_t,      spawn,          CMD("firefox") },
	{ MODKEY2,              XK_g,      spawn,          CMD("firefox --private-window") },
    { MODKEY2,              XK_m,      spawn,          CMD("~/bin/calcurse-dwm.sh") },
	{ MODKEY2,              XK_x,      spawn,          CMD("~/bin/pulse-term.sh") },
	{ MODKEY2,              XK_r,      spawn,          CMD("~/bin/float.sh ~ 80x16 fish") },
	{ MODKEY2,              XK_a,      spawn,          CMD("~/bin/float.sh 'install packages' 128x16 ~/bin/install.sh") },
	{ MODKEY2,              XK_z,      spawn,          CMD("~/bin/float.sh 'remove packages' 128x16 ~/bin/remove.sh") },
	{ MODKEY2,              XK_q,      spawn,          CMD("~/bin/pass-2-clip.sh") },
	{ MODKEY2,              XK_h,      spawn,          CMD("~/bin/float.sh stopwatch 28x5 ~/bin/stopwatch.sh") },
	{ MODKEY2,              XK_w,      spawn,          CMD("~/bin/float.sh ranger 150x35 ranger") },
    { 0,                    XK_Print,  spawn,          CMD("sleep 0.2; scrot -s") },
	{ MODKEY2|ControlMask,  XK_q,      spawn,          CMD("~/bin/poweroff.sh") },
	{ MODKEY2|ControlMask,  XK_z,      spawn,          CMD("~/bin/hibernate.sh") },

	{ MODKEY2,              XK_d,      spawn,          CMD("~/bin/wifi-connect.sh") },
	{ MODKEY2|ControlMask,  XK_a,      spawn,          CMD("~/bin/mount-script.sh") },
    { MODKEY2|ControlMask,  XK_h,      spawn,          CMD("~/bin/umount-script.sh") },
	{ MODKEY2|ControlMask,  XK_v,      spawn,          CMD("~/bin/vpn-select.sh") },

    { 0,     XF86XK_AudioLowerVolume,  spawn,          CMD("pactl set-sink-volume 0 -5%") },
    { 0,     XF86XK_AudioRaiseVolume,  spawn,          CMD("pactl set-sink-volume 0 +5%") },
    { 0,     XF86XK_MonBrightnessDown, spawn,          CMD("xbacklight -dec 10") },
    { 0,     XF86XK_MonBrightnessUp,   spawn,          CMD("xbacklight -inc 10") },

    { MODKEY2|ShiftMask,    XK_q,	   quit,           {0} },
    { MODKEY2|ShiftMask,    XK_w,      quit,           {1} },

  /* Tag keymaps */
	TAGKEYS(                XK_f,             0)
	TAGKEYS(                XK_u,             1)
	TAGKEYS(                XK_p,             2)
	TAGKEYS(                XK_semicolon,     3)
	TAGKEYS(                XK_bracketleft,   4)
};

/* Click can be ClkTagBar, ClkLtSymbol, ClkStatusText, ClkWinTitle, ClkClientWin, or ClkRootWin */
static Button buttons[] = {
	/* Click           Event mask   Button          Function        Argument */
	{ ClkLtSymbol,     0,           Button1,        setlayout,      {0} },
	{ ClkLtSymbol,     0,           Button3,        setlayout,      {.v = &layouts[2]} },
	{ ClkWinTitle,     0,           Button2,        zoom,           {0} },
	{ ClkStatusText,   0,           Button2,        spawn,          CMD("st") },
	{ ClkClientWin,    MODKEY,      Button1,        movemouse,      {0} },
	{ ClkClientWin,    MODKEY,      Button2,        togglefloating, {0} },
	{ ClkClientWin,    MODKEY,      Button3,        resizemouse,    {0} },
	{ ClkTagBar,       0,           Button1,        view,           {0} },
	{ ClkTagBar,       0,           Button3,        toggleview,     {0} },
	{ ClkTagBar,       MODKEY,      Button1,        tag,            {0} },
	{ ClkTagBar,       MODKEY,      Button3,        toggletag,      {0} },
};
