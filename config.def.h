#include <X11/XF86keysym.h>

static const unsigned int borderpx  = 1;
static const unsigned int gappx     = 3;
static const unsigned int snap      = 8;
static const int showbar            = 1;
static const int topbar             = 1;
static const int horizpadbar        = -5;
static const int vertpadbar         = 8;

static const char *fonts[] = {
	"Hack:size=11:antialias=true:autohint=true",
	"Font Awesome 6 Free Solid:size=9:antialias=true:autohint=true",
	"Font Awesome 6 Brands:size=9:antialias=true:autohint=true",
};
static const char dmenufont[] = "Hack:size=11:antialias=true:autohint=true";

static const char color_bg[]      = "#24273A";
static const char color_muted[]   = "#75829c";
static const char color_text[]    = "#EAEEFA";
static const char color_teal[]    = "#8BD5CA";
static const char color_blue[]    = "#8AADF4";
static const char color_red[]     = "#ED8796";
static const char color_yellow[]  = "#EED49F";
static const char color_green[]   = "#A6DA95";
static const char color_purple[]  = "#CBA6F7";
enum { SchemeNorm, SchemeSel, SchemeWarn, SchemeUrgent,
	SchemeAccentRed, SchemeAccentTeal, SchemeAccentBlue,
	SchemeAccentYellow, SchemeAccentGreen, SchemeMuted,
	SchemeAccentPurple };
static const unsigned int baralpha    = OPAQUE;
static const unsigned int borderalpha = OPAQUE;
static const char *colors[][3] = {
	/*                 fg      bg      border */
	[SchemeNorm]         = { color_text,   color_bg, color_bg     },
	[SchemeSel]          = { color_text,   color_bg, color_muted  },
	[SchemeWarn]         = { color_bg,     color_yellow, color_yellow },
	[SchemeUrgent]       = { color_red,    color_bg, color_red    },
	[SchemeAccentRed]    = { color_red,    color_bg, color_bg     },
	[SchemeAccentTeal]   = { color_teal,   color_bg, color_bg     },
	[SchemeAccentBlue]   = { color_blue,   color_bg, color_bg     },
	[SchemeAccentYellow] = { color_yellow, color_bg, color_bg     },
	[SchemeAccentGreen]  = { color_green,  color_bg, color_bg     },
	[SchemeMuted]        = { color_muted,  color_bg, color_bg     },
	[SchemeAccentPurple] = { color_purple, color_bg, color_bg     },
};
static const unsigned int alphas[][3] = {
	/*                 fg      bg        border */
	[SchemeNorm]   = { OPAQUE, baralpha, borderalpha },
	[SchemeSel]    = { OPAQUE, baralpha, borderalpha },
	[SchemeWarn]   = { OPAQUE, baralpha, borderalpha },
	[SchemeUrgent] = { OPAQUE, baralpha, borderalpha },
	[SchemeAccentRed]    = { OPAQUE, baralpha, borderalpha },
	[SchemeAccentTeal]   = { OPAQUE, baralpha, borderalpha },
	[SchemeAccentBlue]   = { OPAQUE, baralpha, borderalpha },
	[SchemeAccentYellow] = { OPAQUE, baralpha, borderalpha },
	[SchemeAccentGreen]  = { OPAQUE, baralpha, borderalpha },
	[SchemeMuted]        = { OPAQUE, baralpha, borderalpha },
	[SchemeAccentPurple] = { OPAQUE, baralpha, borderalpha },
};
static const StatusStyle statusstyles[] = {
	{ 'n', SchemeNorm },
	{ 'r', SchemeAccentRed },
	{ 't', SchemeAccentTeal },
	{ 'b', SchemeAccentBlue },
	{ 'y', SchemeAccentYellow },
	{ 'g', SchemeAccentGreen },
	{ 'p', SchemeAccentPurple },
	{ 'm', SchemeMuted },
	{ 'u', SchemeUrgent },
};

static const TagStyle tags[] = {
    /* vacant, occupied, selected, urgent */
	TAG_STYLE("", SchemeMuted, "", SchemeAccentRed, "", SchemeAccentRed, "", SchemeUrgent),
	TAG_STYLE("", SchemeMuted, "", SchemeAccentTeal, "", SchemeAccentTeal, "", SchemeUrgent),
	TAG_STYLE("", SchemeMuted, "", SchemeAccentBlue, "", SchemeAccentBlue, "", SchemeUrgent),
	TAG_STYLE("", SchemeMuted, "", SchemeAccentYellow, "", SchemeAccentYellow, "", SchemeUrgent),
	TAG_STYLE("", SchemeMuted, "", SchemeAccentGreen, "", SchemeAccentGreen, "", SchemeUrgent),
	TAG_STYLE("", SchemeMuted, "", SchemeAccentPurple, "", SchemeAccentPurple, "", SchemeUrgent),
	TAG_STYLE("", SchemeMuted, "", SchemeAccentBlue, "", SchemeAccentBlue, "", SchemeUrgent),
};
static const BarStyle barstyle = {
	.layout = SchemeMuted,
	.title = {
		[BarInactive] = SchemeMuted,
		[BarActive] = SchemeNorm,
	},
	.floating = {
		[BarInactive] = SchemeMuted,
		[BarActive] = SchemeMuted,
	},
	.empty = SchemeMuted,
};

static const Rule rules[] = {
	/* xprop(1):
	 *	WM_CLASS(STRING) = instance, class
	 *	WM_NAME(STRING) = title
	 */
	/* class      instance    title       tags mask     isfloating   monitor */
	{ NULL,       "float-m",  NULL,       0,            1,           -1 },
};

/* layout(s) */
static const float mfact     = 0.55; /* factor of master area size [0.05..0.95] */
static const float wtilefact = 2.0;  /* weight of first wtile stack client */
static const float wtilefactmin = 1.0;
static const float wtilefactmax = 10.0;
static const float wtilefactstep = 1.0;
static const int nmaster     = 1;    /* number of clients in master area */
static const int resizehints = 0;    /* 1 means respect size hints in tiled resizals */
static const int lockfullscreen = 1; /* 1 will force focus on the fullscreen window */
static const int refreshrate = 120;  /* refresh rate (per second) for client move/resize */

static const Layout layouts[] = {
	/* symbol     arrange function */
	{ "| ",      tile },    /* first entry is default */
	{ "| ",      centeredmaster },
	{ "| ",      monocle },
	{ "| ",     wtile },
	{ "| ",      NULL },    /* no layout function means floating behavior */
};

/* key definitions */
#define MODKEY  Mod1Mask
#define MODKEY2 Mod5Mask
#define CMD(cmd) { .v = (const char *[]) { "/bin/sh", "-c", cmd, NULL } }
#define TAGKEYS(KEY,TAG) \
	{ MODKEY2,                       KEY,      view,           {.ui = 1 << TAG} }, \
	{ MODKEY2|ControlMask|ShiftMask, KEY,      toggleview,     {.ui = 1 << TAG} }, \
	{ MODKEY2|ShiftMask,             KEY,      tag,            {.ui = 1 << TAG} }, \
	{ MODKEY2|ControlMask,           KEY,      toggletag,      {.ui = 1 << TAG} },

/* commands */
static char dmenumon[2] = "0"; /* component of dmenucmd, manipulated in spawn() */
static const char *dmenucmd[] = { "dmenu_run", "-m", dmenumon, "-fn", dmenufont, "-nb", color_bg, "-nf", color_text, "-sb", color_blue, "-sf", color_bg, NULL };
static const char *termcmd[]  = { "st", NULL };

static const Key keys[] = {
	/* modifier                     key        function        argument */
	{ MODKEY2|ShiftMask,             XK_space, togglebar,      {0} },
	{ MODKEY,                        XK_n,     focusstack,     {.i = +1 } },
	{ MODKEY,                        XK_p,     focusstack,     {.i = -1 } },
	{ MODKEY|ShiftMask,              XK_k,     incnmaster,     {.i = +1 } },
	{ MODKEY|ShiftMask,              XK_j,     incnmaster,     {.i = -1 } },
	{ MODKEY,                        XK_j,     setmfact,       {.f = +0.05} },
	{ MODKEY,                        XK_k,     setmfact,       {.f = -0.05} },
	{ MODKEY,                        XK_bracketleft,  setwtilefact, {.i = -1 } },
	{ MODKEY,                        XK_bracketright, setwtilefact, {.i = +1 } },
	{ MODKEY,                        XK_i,          zoom,           {0} },
	{ MODKEY,                        XK_apostrophe, focusmaster,    {0} },
	{ MODKEY,                        XK_e,          killclient,     {0} },
	{ MODKEY,                        XK_space,      togglefloating, {0} },

	{ MODKEY2,                       XK_z, setlayout, {.v = &layouts[0]} },
	{ MODKEY2|ShiftMask,             XK_z, setlayout, {.v = &layouts[3]} },
	{ MODKEY2,                       XK_x, setlayout, {.v = &layouts[1]} },
	{ MODKEY2,                       XK_m, setlayout, {.v = &layouts[2]} },
	{ MODKEY2,                       XK_v, setlayout, {.v = &layouts[4]} },

	{ MODKEY|ControlMask,            XK_0, tag,  {.ui = ~0 } },
	{ MODKEY|ControlMask|ShiftMask,  XK_0, view, {.ui = ~0 } },

	{ MODKEY2,                       XK_h, focusmon, {.i = -1 } },
	{ MODKEY,                        XK_l, focusmon, {.i = +1 } },
	{ MODKEY2|ShiftMask,             XK_h, tagmon,   {.i = -1 } },
	{ MODKEY|ShiftMask,              XK_l, tagmon,   {.i = +1 } },

	{ MODKEY,              XK_1,      spawn, CMD("change-layout.sh workman") },
	{ MODKEY,              XK_2,      spawn, CMD("change-layout.sh us") },
	{ MODKEY2,             XK_e,      spawn, CMD("connect-bt-earp.sh") },
	{ MODKEY2,             XK_l,      spawn, CMD("slock") },
	{ MODKEY2,             XK_k,      spawn, CMD("connect-bt-keyb.sh") },
	{ MODKEY,              XK_slash,  spawn, CMD("sk-launch.sh") },
	{ MODKEY2,             XK_t,      spawn, CMD("st -T '~'") },
	{ MODKEY,              XK_f,      spawn, CMD("firefox") },
	{ MODKEY|ShiftMask,    XK_f,      spawn, CMD("firefox --private-window") },
	{ MODKEY,              XK_o,      spawn, CMD("float.sh 'pulsemixer' 80x16 pulsemixer") },
	{ MODKEY2,             XK_g,      spawn, CMD("float.sh ~ 80x16 fish") },
	{ MODKEY2|ControlMask, XK_g,      spawn, CMD("float.sh ~ 80x16 qalc.sh") },
	{ MODKEY2,             XK_a,      spawn, CMD("float.sh 'install packages' 128x16 install.sh") },
	{ MODKEY2|ShiftMask,   XK_a,      spawn, CMD("float.sh 'remove packages' 128x16 remove.sh") },
	{ MODKEY2,             XK_s,      spawn, CMD("pass-2-clip.sh") },
	{ MODKEY,              XK_comma,  spawn, CMD("float.sh stopwatch 28x5 stopwatch.sh") },
	{ MODKEY,              XK_period, spawn, CMD("float.sh roam 150x35 roam") },
	{ MODKEY,              XK_y,      spawn, CMD("calcurse-dwm.sh") },
	{ 0,                   XK_Print,  spawn, CMD("sleep 0.2; scrot -s") },
	{ MODKEY2|ControlMask, XK_s,      spawn, CMD("poweroff.sh") },
	{ MODKEY2|ControlMask, XK_z,      spawn, CMD("hibernate.sh") },
	{ MODKEY2|ControlMask, XK_i,      spawn, CMD("wifi-connect.sh") },
	{ MODKEY2|ControlMask, XK_a,      spawn, CMD("mount-script.sh") },
	{ MODKEY|ControlMask,  XK_u,      spawn, CMD("umount-script.sh") },
	{ MODKEY2|ControlMask, XK_v,      spawn, CMD("vpn-select.sh") },
	{ 0, XF86XK_AudioLowerVolume,  spawn, CMD("pactl set-sink-volume 0 -5%") },
	{ 0, XF86XK_AudioRaiseVolume,  spawn, CMD("pactl set-sink-volume 0 +5%") },
	{ 0, XF86XK_MonBrightnessDown, spawn, CMD("xbacklight -dec 10") },
	{ 0, XF86XK_MonBrightnessUp,   spawn, CMD("xbacklight -inc 10") },

	{ MODKEY|ShiftMask, XK_q, quit, {0} },
	{ MODKEY|ShiftMask, XK_r, quit, {.i = 1} },

	TAGKEYS(XK_1, 0)
	TAGKEYS(XK_q, 1)
	TAGKEYS(XK_d, 2)
	TAGKEYS(XK_r, 3)
	TAGKEYS(XK_w, 4)
	TAGKEYS(XK_b, 5)
	TAGKEYS(XK_5, 6)
};

/* button definitions */
/* click can be ClkTagBar, ClkLtSymbol, ClkStatusText, ClkWinTitle, ClkClientWin, or ClkRootWin */
static const Button buttons[] = {
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
