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
                                         "Font Awesome 5 Free Solid:size=9:antialias=true:autohint=true",
                                         "Font Awesome 5 Brands:size=9:antialias=true:autohint=true"};

static const char nord0[]  = "#2E3445";
static const char nord2[]  = "#75829c";
static const char nord5[]  = "#D8DEE9";
static const char nord10[] = "#4d8ccb";
static const char nord7[]  = "#609f9e";
static const char nord11[] = "#BF616A";
static const char nord12[] = "#D08770";
static const char nord13[] = "#EBCB8B";
static const char nord14[] = "#A3BE8C";
static const char nord15[] = "#B48EAD";

static const unsigned int baralpha    = 0xff; /* 0xff is no transparency */
static const unsigned int borderalpha = OPAQUE;

static const char *colors[][3]        = {
	/*                    fg      bg      border */
	[SchemeNord10]    = { nord10, nord0,  nord2},
	[SchemeNord7]     = { nord7,  nord0,  nord0 },
	[SchemeNord12]    = { nord12, nord0,  nord0 },
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
static const char *tags[] =   { "", "", "", "", "",""};

static const Rule rules[] = {
	/* Class       Itstance    Title  Tags Mask  Isfloating  Monitor */
	{ "Firefox",   NULL,       NULL,  1 << 2,    0,          -1 },
	{ "Chromium",  NULL,       NULL,  1 << 2,    0,          -1 },
	{ "Inkscape",  NULL,       NULL,  1 << 3,    0,          -1 },
	{ "Nautilus",  NULL,       NULL,  0,         1,          -1 },
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
static const char *lunchcmd[]    = { "/home/hal3e/bin/sk-lunch.sh", NULL };
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
	{ MODKEY2,              XK_s,      spawn,          { .v = lunchcmd } },
	{ MODKEY2,              XK_b,      spawn,          CMD("st -t 'fish /home/hal3e'") },
	{ MODKEY2,              XK_t,      spawn,          CMD("firefox") },
	{ MODKEY2,              XK_g,      spawn,          CMD("firefox --private-window") },
	{ MODKEY2,              XK_c,      spawn,          CMD("~/bin/latex-eq/latex-2-svg.sh") },
	{ MODKEY2,              XK_w,      spawn,          CMD("st -n float-m -g 150x35 -e ranger") },
  { MODKEY2,              XK_m,      spawn,          CMD("~/bin/calcurse-dwm.sh") },
	{ MODKEY2,              XK_x,      spawn,          CMD("~/bin/pulse-term.sh") },
	{ MODKEY2,              XK_r,      spawn,          CMD("st -t 'fish /home/hal3e' -n float-m -g 80x16 -e fish") },
	{ MODKEY2,              XK_a,      spawn,          CMD("st -n float-m -g 100x16 -e /home/hal3e/bin/install.sh") },
	{ MODKEY2,              XK_d,      spawn,          CMD("st -n float-m -g 64x16 -e /home/hal3e/bin/wifi-connect.sh") },
	{ MODKEY2,              XK_q,      spawn,          CMD("st -n float-m -g 32x12 -e /home/hal3e/bin/pass-2-clip.sh") },
	{ MODKEY2,              XK_h,      spawn,          CMD("st -n float-m -g 28x5 -e /home/hal3e/bin/stopwatch.sh") },
  { 0,                    XK_Print,  spawn,          CMD("sleep 0.2; scrot -s") },

	{ MODKEY2|ControlMask,  XK_q,      spawn,          CMD("~/bin/poweroff.sh") },
	{ MODKEY2|ControlMask,  XK_z,      spawn,          CMD("~/bin/hibernate.sh") },
	{ MODKEY2|ControlMask,  XK_a,      spawn,          CMD("st -n float-m -g 32x12 -e /home/hal3e/bin/mount-script.sh") },
  { MODKEY2|ControlMask,  XK_h,      spawn,          CMD("st -n float-m -g 32x12 -e /home/hal3e/bin/umount-script.sh") },
  { MODKEY2|ShiftMask,    XK_q,	     quit,           {0} },
  { MODKEY2|ShiftMask,    XK_w,      quit,           {1} },

  { 0,     XF86XK_AudioLowerVolume,  spawn,          CMD("pactl set-sink-volume 0 -5%") },
  { 0,     XF86XK_AudioRaiseVolume,  spawn,          CMD("pactl set-sink-volume 0 +5%") },

  { 0,     XF86XK_MonBrightnessDown, spawn,          CMD("xbacklight -dec 10") },
  { 0,     XF86XK_MonBrightnessUp,   spawn,          CMD("xbacklight -inc 10") },

  /* Tag keymaps */
	TAGKEYS(                XK_f,             0)
	TAGKEYS(                XK_u,             1)
	TAGKEYS(                XK_p,             2)
	TAGKEYS(                XK_semicolon,     3)
	TAGKEYS(                XK_bracketleft,   4)
	TAGKEYS(                XK_bracketright,  5)
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
