/* See LICENSE file for copyright and license details. */

#pragma once
#ifndef CONFIG_H
#define CONFIG_H

#include "dwm.h"

/* appearance */
#define ICONSIZE 16   /* icon size */
#define ICONSPACING 5 /* space between icon and title */
static const unsigned int borderpx       = 0;  /* border pixel of windows */
static const unsigned int snap           = 32; /* snap pixel */
static const unsigned int systraypinning = 0;  /* 0: sloppy systray follows selected monitor, >0: pin systray to monitor X */
static const unsigned int systrayonleft  = 1;  /* 0: systray in the right corner, >0: systray on left of status text */
static const unsigned int systrayspacing = 2;  /* systray spacing */
static const int systraypinningfailfirst = 1;  /* 1: if pinning fails, display systray on the first monitor, False: display systray on the last monitor*/
static const int showsystray             = 1;  /* 0 means no systray */
static const int showbar                 = 1;  /* 0 means no bar */
static const int topbar                  = 1;  /* 0 means bottom bar */
static const int user_bh                 = 24; /* 0 means that dwm will calculate bar height, >= 1 means dwm will user_bh as bar height */
static const char *fonts[]               = { "monospace:size=10" };
static const char dmenufont[]            = "monospace:size=10";
static const char col_gray1[]            = "#222222";
static const char col_gray2[]            = "#444444";
static const char col_gray3[]            = "#bbbbbb";
static const char col_gray4[]            = "#eeeeee";
static const char col_cyan[]             = "#005577";
static const char col_light_blue[]       = "#8aecff";
static const char *colors[][3]           = {
	/*               fg              bg         border   */
	[SchemeNorm] = { col_gray3,      col_gray1, col_gray2 },
	[SchemeSel]  = { col_gray4,      col_cyan,  col_cyan  },
	[SchemeHid]  = { col_light_blue, col_gray1, col_cyan  },
};
static const char *bin_path = "/usr/local/bin/dwm";

/* alt-tab configuration */
static const unsigned int tabModKey 	= 0x40;	/* if this key is hold the alt-tab functionality stays acitve. This key must be the same as key that is used to active functin altTabStart `*/
static const unsigned int tabCycleKey 	= 0x17;	/* if this key is hit the alt-tab program moves one position forward in clients stack. This key must be the same as key that is used to active functin altTabStart */
static const unsigned int tabPosY 		= 1;	/* tab position on Y axis, 0 = bottom, 1 = center, 2 = top */
static const unsigned int tabPosX 		= 1;	/* tab position on X axis, 0 = left, 1 = center, 2 = right */
static const unsigned int maxWTab 		= 600;	/* tab menu width */
static const unsigned int maxHTab 		= 200;	/* tab menu height */

/* tagging */
static const char *tags[] = { "1", "2", "3", "4", "5", "6", "7", "8", "9" };

static const Rule rules[] = {
	/* xprop(1):
	 *	WM_CLASS(STRING) = instance, class
	 *	WM_NAME(STRING) = title
	 */
	/* class_  instance    title       tags mask   isfloating   monitor  preserveOnRestart underCurrentIfFloat*/
	{ "Gimp",     NULL,       NULL,       0,            1,           -1,     true,             false  },
	{ "copyq",    NULL,       NULL,       0,            1,           -1,     false,            true   },
	{ "Firefox",  NULL,       NULL,       0,            0,           -1,     true,             true   },
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
	{ "|M|",      centeredmaster },
	{ ">M>",      centeredfloatingmaster },
	{ "TTT",      bstack },
	{ "===",      bstackhoriz },
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
static const char *dmenucmd[] = { "dmenu_run", "-fn", dmenufont, "-nb", col_gray1, "-nf", col_gray3, "-sb", col_cyan, "-sf", col_gray4, NULL };
static const char *termcmd[]  = { "alacritty", NULL };
static const char *rofi_run_cmd[] = { "rofi", "-show", "run", NULL };
static const char *rofi_window_cmd[] = { "rofi", "-show", "window", NULL };
static const char *xmouseless_cmd[] = { "xmouseless", NULL };

/* */
static const char *kblayout_us[]  = { "bash", "-c", "python /home/user/dwm_scripts/kb_layout.py set us && python /home/user/dwm_scripts/dwm_status_bar.py render", NULL };
static const char *kblayout_ru[]  = { "bash", "-c", "python /home/user/dwm_scripts/kb_layout.py set ru && python /home/user/dwm_scripts/dwm_status_bar.py render", NULL };
static const char *kblayout_circle[]  = { "bash", "-c", "python /home/user/dwm_scripts/kb_layout.py circle us ru && python /home/user/dwm_scripts/dwm_status_bar.py render", NULL };

// set size in main.cpp
const Key keys[500] = {
	/* modifier                     key                 function           argument */
	{ MODKEY,                       XK_f,               togglefullscr,     {0} },
	{ MODKEY,                       XK_r,               spawn,             {.v = rofi_run_cmd } },
	{ MODKEY|ShiftMask,             XK_r,               spawn,             {.v = rofi_window_cmd } },
	{ MODKEY,             			XK_Cyrillic_ya,     spawn,             {.v = kblayout_us } },
	{ MODKEY,                       XK_x,               spawn,             {.v = kblayout_ru } },
	{ MODKEY,             			XK_space,           spawn,             {.v = kblayout_circle } },
	{ MODKEY,                       XK_p,               spawn,             {.v = dmenucmd } },
	{ MODKEY|ShiftMask,             XK_Return,          spawn,             {.v = termcmd } },
	{ MODKEY|ShiftMask,             XK_m,               spawn,             {.v = xmouseless_cmd } },
	{ MODKEY,                       XK_b,               togglebar,         {0} },
	{ MODKEY,                       XK_j,        		focusstackvis,     {.i = +1 } },
	{ MODKEY,                       XK_k,        		focusstackvis,     {.i = -1 } },
	{ MODKEY|ShiftMask,             XK_j,        		focusstackhid,     {.i = +1 } },
	{ MODKEY|ShiftMask,             XK_k,        		focusstackhid,     {.i = -1 } },
	{ MODKEY,                       XK_i,               incnmaster,        {.i = +1 } },
	{ MODKEY,                       XK_d,               incnmaster,        {.i = -1 } },
	{ MODKEY,                       XK_h,               setmfact,          {.f = -0.05} },
	{ MODKEY,                       XK_l,               setmfact,          {.f = +0.05} },
	{ MODKEY,                       XK_Return,          zoom,              {0} },
	{ MODKEY,                       XK_Tab,             view,              {0} },
	{ MODKEY|ShiftMask,             XK_c,               killclient,        {0} },
	{ MODKEY,                       XK_t,               setlayout,         {.v = &layouts[0]} },
	{ MODKEY|ShiftMask,             XK_f,               setlayout,         {.v = &layouts[1]} },
	{ MODKEY,                       XK_m,               setlayout,         {.v = &layouts[2]} },
	{ MODKEY,                       XK_u,               setlayout,         {.v = &layouts[3]} },
	{ MODKEY,                       XK_o,               setlayout,         {.v = &layouts[4]} },
	{ MODKEY|ShiftMask,             XK_u,   		    setlayout,         {.v = &layouts[5]} },
	{ MODKEY|ShiftMask,             XK_o,   		    setlayout,         {.v = &layouts[6]} },
	{ MODKEY,                       XK_v,               setlayout,         {0} },
	{ MODKEY|ShiftMask,             XK_v,               togglefloating,    {0} },
	{ MODKEY,                       XK_0,               view,              {.ui = ~0 } },
	{ MODKEY|ShiftMask,             XK_0,               tag,               {.ui = ~0 } },
	{ MODKEY,                       XK_comma,           focusmon,          {.i = -1 } },
	{ MODKEY,                       XK_period,          focusmon,          {.i = +1 } },
	{ MODKEY|ShiftMask,             XK_comma,           tagmon,            {.i = -1 } },
	{ MODKEY|ShiftMask,             XK_period,          tagmon,            {.i = +1 } },
	{ MODKEY|ShiftMask,             XK_q,               quit,              {0} },
	{ MODKEY,                       XK_Right,           viewnext,          {0} },
	{ MODKEY,                       XK_Left,            viewprev,          {0} },
	{ MODKEY|ShiftMask,             XK_Right,           tagtonext,         {0} },
	{ MODKEY|ShiftMask,             XK_Left,            tagtoprev,         {0} },
	{ Mod1Mask,             		XK_Tab,             altTabStart,	   {0} },
	{ MODKEY|ShiftMask,             XK_t,               togglealwaysontop, {0} },
	{ MODKEY,                       XK_q,               self_restart,      {0} },
	{ MODKEY,                       XK_s,      			show,              {0} },
	{ MODKEY|ShiftMask,             XK_s,      			showall,           {0} },
	{ MODKEY|ShiftMask,             XK_h,      			hide,              {0} },
	{ MODKEY|ShiftMask,             XK_y,      			hideall,           {0} },
	TAGKEYS(                        XK_1,                                  0 )
	TAGKEYS(                        XK_2,                                  1 )
	TAGKEYS(                        XK_3,                                  2 )
	TAGKEYS(                        XK_4,                                  3 )
	TAGKEYS(                        XK_5,                                  4 )
	TAGKEYS(                        XK_6,                                  5 )
	TAGKEYS(                        XK_7,                                  6 )
	TAGKEYS(                        XK_8,                                  7 )
	TAGKEYS(                        XK_9,                                  8 )
};

/* button definitions */
/* click can be ClkTagBar, ClkLtSymbol, ClkStatusText, ClkWinTitle, ClkClientWin, or ClkRootWin */
static const Button buttons[] = {
	/* click                event mask      button          function        argument */
	{ ClkLtSymbol,          0,              Button1,        setlayout,      {0} },
	{ ClkLtSymbol,          0,              Button3,        setlayout,      {.v = &layouts[2]} },
	{ ClkWinTitle,          0,              Button1,        togglewin,      {0} },
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

#endif
