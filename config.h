/* See LICENSE file for copyright and license details. */



#include <X11/XF86keysym.h>


/* appearance */
static const char *upvol[]   = { "/usr/bin/pactl", "set-sink-volume", "0", "+5%",     NULL };
static const char *downvol[] = { "/usr/bin/pactl", "set-sink-volume", "0", "-5%",     NULL };
static const char *mutevol[] = { "/usr/bin/pactl", "set-sink-mute",   "0", "toggle",  NULL };
static const unsigned int borderpx  = 2;        /* border pixel of windows */
static const unsigned int gappx     = 5;       /* gap pixel between windows */
static const unsigned int snap      = 32;       /* snap pixel */
static const int showbar            = 1;        /* 0 means no standard bar */
static const int topbar             = 0;        /* 0 means standard bar at bottom */
static const int extrabar           = 0;        /* 0 means no extra bar */
static const char statussep         = ';';      /* separator between statuses */
static const char *fonts[]          = { "fontawesome:pixelsize=13", "Symbols Nerd Font:pixelsize=14" };
static const char dmenufont[]       = "monospace:size=10";
static const char buttonbar[]       = "";

//inactive desktop
static const char inactive_desktop1[]= "#001319";
//active desktop
static const char active_desktop1[]  = "#0c94c6";
//inactive window color
static const char inactive_window1[] = "#0b6080";
//active window color
static const char active_window1[]   = "#0087b9";
//font color
static const char unselected_font1[] = "#0ecae2";
//selected_font color
static const char selected_font1[]   = "#044d50";



//inactive desktop
static const char inactive_desktop2[]= "#000000";
//active desktop
static const char active_desktop2[]  = "#909090";
//inactive window color
static const char inactive_window2[] = "#1c1c1c";
//active window color
static const char active_window2[]   = "#bcbcbc";
//font color
static const char unselected_font2[] = "#909090";
//selected_font color
static const char selected_font2[]   = "#000000";



//inactive desktop
static const char inactive_desktop3[]= "#0f0200";
//active desktop
static const char active_desktop3[]  = "#c6290c";
//inactive window color
static const char inactive_window3[] = "#500f04";
//active window color
static const char active_window3[]   = "#e22f0e";
//font color
static const char unselected_font3[] = "#d41000";
//selected_font color
static const char selected_font3[]   = "#260300";




static const char *colors[][3]      = {
	/*               fg         bg         border   */
	{ unselected_font1, inactive_desktop1, inactive_window1 }, /* blue */
	{ selected_font1,   active_desktop1,  active_window1  }, 
        
	{ unselected_font2, inactive_desktop2, inactive_window2 }, /* dark */
	{ selected_font2,   active_desktop2,  active_window2  }, 
        
	{ unselected_font3, inactive_desktop3, inactive_window3 }, /* red */
	{ selected_font3,    active_desktop3,   active_window3 }, 
};

/* tagging */
static const char *tags[] = { "", "", "", "", "", "", "" };

static const Rule rules[] = {
	/* xprop(1):
	 *	WM_CLASS(STRING) = instance, class
	 *	WM_NAME(STRING) = title
	 */
	/* class      instance    title       tags mask     isfloating   monitor */
	{ "Gimp",     NULL,       NULL,       0,            1,           -1 },
	{ "Firefox",  NULL,       NULL,       1 << 8,       0,           -1 },
};

/* layout(s) */
static const float mfact     = 0.5; /* factor of master area size [0.05..0.95] */
static const int nmaster     = 1;    /* number of clients in master area */
static const int resizehints = 0;    /* 1 means respect size hints in tiled resizals */
static const int lockfullscreen = 1; /* 1 will force focus on the fullscreen window */

static const Layout layouts[] = {
	/* symbol     arrange function */
	{ "ﱖ",      tile },    /* first entry is default */
	{ "",      NULL },    /* no layout function means floating behavior */
	{ "ﱡ",      monocle },
};

/* key definitions */
#define MODKEY Mod4Mask
#define ALTKEY Mod1Mask
#define TAGKEYS(KEY,TAG) \
	{ MODKEY,                       KEY,      view,           {.ui = 1 << TAG} }, \
	{ MODKEY|ControlMask,           KEY,      toggleview,     {.ui = 1 << TAG} }, \
	{ MODKEY|ShiftMask,             KEY,      tag,            {.ui = 1 << TAG} }, \
	{ MODKEY|ControlMask|ShiftMask, KEY,      toggletag,      {.ui = 1 << TAG} },

/* helper for spawning shell commands in the pre dwm-5.0 fashion */
#define SHCMD(cmd) { .v = (const char*[]){ "/usr/local/bin/st", "-c", cmd, NULL } }

/* commands */
static char dmenumon[2] = "0"; /* component of dmenucmd, manipulated in spawn() */
static const char *dmenucmd[] = { "dmenu_run", "-m", dmenumon, "-fn", dmenufont, "-nb", inactive_desktop2, "-nf", unselected_font2, "-sb", active_desktop2, "-sf", selected_font2, NULL };
static const char *termcmd[]  = { "st", NULL };


#include "shiftview.c"
static Key keys[] = {
	/* modifier                     key        function        argument */
	{ 0,         XF86XK_AudioLowerVolume,	   spawn,  	       {.v = downvol } },
	{ 0,                XF86XK_AudioMute,	   spawn,	       {.v = mutevol } },
	{ 0,         XF86XK_AudioRaiseVolume,	   spawn,          {.v = upvol   } },
	{ MODKEY,                       XK_r,      spawn,          {.v = dmenucmd } },
	{ MODKEY,                       XK_t,      spawn,          {.v = termcmd } },
	{ MODKEY,                       XK_space,  togglebar,      {0} },
	{ MODKEY|ShiftMask,             XK_space,  toggleextrabar, {0} },
	{ ALTKEY,                      XK_Tab,     focusstack,     {.i = +1 } },
	{ ALTKEY|ShiftMask,            XK_Tab,     focusstack,     {.i = -1 } },
	{ MODKEY,                     XK_Return,   incnmaster,     {.i = +1 } },
	{ MODKEY,                  XK_BackSpace,   incnmaster,     {.i = -1 } },
	{ MODKEY,                       XK_a,      setmfact,       {.f = -0.05} },
	{ MODKEY,                       XK_d,      setmfact,       {.f = +0.05} },
	{ MODKEY,                       XK_z,      zoom,           {0} },
	{ MODKEY,                       XK_Tab,    view,           {0} },
	{ MODKEY,                       XK_w,      killclient,     {0} },
	{ MODKEY,                   XK_equal,      setlayout,      {.v = &layouts[0]} },
	{ MODKEY,                       XK_minus,  setlayout,      {.v = &layouts[1]} },
	{ MODKEY,                       XK_m,      setlayout,      {.v = &layouts[2]} },
	{ MODKEY,                       XK_b,      setlayout,      {0} },
	{ MODKEY|ShiftMask,             XK_b,      togglefloating, {0} },
	{ MODKEY,                       XK_0,      view,           {.ui = ~0 } },
	{ MODKEY|ShiftMask,             XK_0,      tag,            {.ui = ~0 } },
	{ MODKEY,                       XK_comma,  focusmon,       {.i = -1 } },
	{ MODKEY,                       XK_period, focusmon,       {.i = +1 } },
	{ MODKEY|ShiftMask,             XK_comma,  tagmon,         {.i = -1 } },
	{ MODKEY|ShiftMask,             XK_period, tagmon,         {.i = +1 } },
	{ MODKEY|ShiftMask,             XK_t,      schemeToggle,   {0} },
	{ MODKEY|ShiftMask,             XK_z,      schemeCycle,    {0} },
	{ MODKEY|ControlMask,           XK_Tab,    shiftview, 	   {.i = +1 } },
	{ MODKEY|ControlMask|ShiftMask, XK_Tab,    shiftview,	   {.i = -1 } },
	TAGKEYS(                        XK_1,                      0)
	TAGKEYS(                        XK_2,                      1)
	TAGKEYS(                        XK_3,                      2)
	TAGKEYS(                        XK_4,                      3)
	TAGKEYS(                        XK_5,                      4)
	TAGKEYS(                        XK_6,                      5)
	TAGKEYS(                        XK_7,                      6)
	TAGKEYS(                        XK_8,                      7)
	TAGKEYS(                        XK_9,                      8)
	{ MODKEY|ShiftMask,             XK_q,      quit,           {0} },
};

/* button definitions */
/* click can be ClkTagBar, ClkLtSymbol, ClkStatusText, ClkWinTitle, ClkClientWin, or ClkRootWin */
static Button buttons[] = {
	/* click                event mask      button          function        argument */
	{ ClkButton,		    0,		        Button1,	    spawn,		    {.v = termcmd } },
	{ ClkLtSymbol,          0,              Button1,        setlayout,      {0} },
	{ ClkLtSymbol,          0,              Button3,        setlayout,      {.v = &layouts[2]} },
	{ ClkWinTitle,          0,              Button2,        zoom,           {0} },
	{ ClkStatusText,        0,              Button2,        spawn,          {.v = termcmd } },
	{ ClkExBarLeftStatus,   0,              Button2,        spawn,          {.v = termcmd } },
	{ ClkExBarMiddle,       0,              Button2,        spawn,          {.v = termcmd } },
	{ ClkExBarRightStatus,  0,              Button2,        spawn,          {.v = termcmd } },
	{ ClkClientWin,         MODKEY,         Button1,        movemouse,      {0} },
	{ ClkClientWin,         MODKEY,         Button2,        togglefloating, {0} },
	{ ClkClientWin,         MODKEY,         Button3,        resizemouse,    {0} },
	{ ClkTagBar,            0,              Button1,        view,           {0} },
	{ ClkTagBar,            0,              Button3,        toggleview,     {0} },
	{ ClkTagBar,            MODKEY,         Button1,        tag,            {0} },
	{ ClkTagBar,            MODKEY,         Button3,        toggletag,      {0} },
};

