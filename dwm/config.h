/* See LICENSE file for copyright and license details. */

/* appearance */
static const unsigned int borderpx = 8; /* border pixel of windows */
static const unsigned int snap = 32;    /* snap pixel */
static const int showbar = 1;           /* 0 means no bar */
static const int topbar = 1;            /* 0 means bottom bar */
static const char *fonts[] = {
    "ProFontIIxNerdFontMono-Regular:antialias=false:size=18"};
static const char dmenufont[] =
    "ProFontIIxNerdFontMono-Regular:antialias=false:size=18";
static const char col_gray1[] = "#252235";
static const char col_gray2[] = "#444444";
static const char col_gray3[] = "#a8fdde";
static const char col_gray4[] = "#ffffff";
static const char col_accent_1[] = "#793a80";
static const char col_accent_2[] = "#bc4b9b";
static const char *colors[][3] = {
    /*               fg         bg         border   */
    [SchemeNorm] = {col_gray3, col_gray1, col_gray2},
    [SchemeSel] = {col_gray4, col_accent_1, col_accent_2},
};

static const char *const autostart[] = {
    "slstatus",
    NULL,
    "feh",
    "--bg-scale",
    "/usr/bin/wallpaper.jpg",
    NULL,
    "lightscreen",
    "--quiet",
    NULL,
    "setxkbmap",
    "-layout",
    "us",
    "-variant",
    "intl-mod",
    NULL,
    "xrandr",
    "-r",
    "120",
    NULL,
    NULL /* terminate */
};

/* tagging */
static const char *tags[] = {"main", "comms", "media", "4", "5"};

static const Rule rules[] = {
    /* xprop(1):
     *	WM_CLASS(STRING) = instance, class
     *	WM_NAME(STRING) = title
     */
    /* class      instance    title       tags mask     isfloating   monitor */
    {"Firefox", NULL, NULL, 1 << 8, 0, -1},
};

/* layout(s) */
static const float mfact = 0.55; /* factor of master area size [0.05..0.95] */
static const int nmaster = 1;    /* number of clients in master area */
static const int resizehints =
    0; /* 1 means respect size hints in tiled resizals */
static const int lockfullscreen =
    1; /* 1 will force focus on the fullscreen window */

#include "horizgrid.c"
static const Layout layouts[] = {
    /* symbol     arrange function */
    {"[]=", tile}, /* first entry is default */
    {"><>", NULL}, /* no layout function means floating behavior */
    {"[M]", monocle},
    {"###", horizgrid},
};

/* key definitions */
#define MODKEY Mod4Mask
#define TAGKEYS(KEY, TAG)                                                      \
  {MODKEY, KEY, view, {.ui = 1 << TAG}},                                       \
      {MODKEY | ControlMask, KEY, toggleview, {.ui = 1 << TAG}},               \
      {MODKEY | ShiftMask, KEY, tag, {.ui = 1 << TAG}},                        \
      {MODKEY | ControlMask | ShiftMask, KEY, toggletag, {.ui = 1 << TAG}},
#define STACKKEYS(MOD, ACTION)                                                 \
  {MOD, XK_n, ACTION##stack, {.i = INC(+1)}},                                  \
      {MOD, XK_e, ACTION##stack, {.i = INC(-1)}},

/* helper for spawning shell commands in the pre dwm-5.0 fashion */
#define SHCMD(cmd)                                                             \
  {                                                                            \
    .v = (const char *[]) { "/bin/fish", "-c", cmd, NULL }                       \
  }

static const int dmenudesktop = 1; /* 1 means dmenu will use only desktop files
                                      from [/usr/share/applications/] */

/* commands */
static char dmenumon[2] =
    "0"; /* component of dmenucmd, manipulated in spawn() */
static const char *dmenucmd[] = {
    "dmenu_run", "-m",  dmenumon,     "-fn", dmenufont, "-nb", col_gray2, "-nf",
    col_gray3,   "-sb", col_accent_1, "-sf", col_gray4, NULL};

static const char *termcmd[] = {"st", "fish", "-i", "-C", "tmux attach || tms dev", NULL};

static const char *toggleplaypause[] = {"playerctl", "play-pause", NULL};
static const char *nextmusic[] = {"playerctl", "next", NULL};
static const char *decvolume[] = {"pamixer", "--decrease", "5", NULL};
static const char *incvolume[] = {"pamixer", "--increase", "5", NULL};
static const char *setoutcodec[] = {
    "pactl", "set-default-sink",
    "alsa_output.usb-BurrBrown_from_Texas_Instruments_USB_AUDIO_CODEC-00."
    "analog-stereo",
    NULL};
static const char *setoutspeaker[] = {
    "pactl", "set-default-sink",
    "alsa_output.pci-0000_0a_00.1.hdmi-stereo-extra3", NULL};

#include <X11/XF86keysym.h>
static const Key keys[] = {
    /* modifier                     key        function        argument */
    {0, XF86XK_AudioNext, spawn, {.v = nextmusic}},
    {0, XF86XK_AudioPlay, spawn, {.v = toggleplaypause}},
    {MODKEY, XK_bracketleft, spawn, {.v = decvolume}},
    {MODKEY, XK_bracketright, spawn, {.v = incvolume}},
    {MODKEY | ShiftMask, XK_9, spawn, {.v = setoutcodec}},
    {MODKEY | ShiftMask, XK_0, spawn, {.v = setoutspeaker}},
    {MODKEY, XK_p, spawn, {.v = dmenucmd}},
    {MODKEY, XK_o, spawn, {.v = termcmd}},
    {MODKEY, XK_b, togglebar, {0}},
    STACKKEYS(MODKEY, focus) STACKKEYS(MODKEY | ShiftMask, push){
        MODKEY, XK_u, incnmaster, {.i = +1}},
    {MODKEY, XK_d, incnmaster, {.i = -1}},
    {MODKEY, XK_m, setmfact, {.f = -0.05}},
    {MODKEY, XK_i, setmfact, {.f = +0.05}},
    {MODKEY, XK_Return, zoom, {0}},
    {MODKEY, XK_Tab, view, {0}},
    {MODKEY, XK_q, killclient, {0}},
    {MODKEY, XK_t, setlayout, {.v = &layouts[0]}},
    {MODKEY, XK_z, setlayout, {.v = &layouts[1]}},
    {MODKEY, XK_f, setlayout, {.v = &layouts[2]}},
    {MODKEY, XK_g, setlayout, {.v = &layouts[3]}},
    {MODKEY, XK_space, setlayout, {0}},
    {MODKEY | ShiftMask, XK_space, togglefloating, {0}},
    {MODKEY, XK_0, view, {.ui = ~0}},
    {MODKEY | ShiftMask, XK_0, tag, {.ui = ~0}},
    {MODKEY, XK_Down, focusmon, {.i = -1}},
    {MODKEY, XK_Up, focusmon, {.i = +1}},
    {MODKEY, XK_period, tagmon, {.i = -1}},
    {MODKEY, XK_comma, tagmon, {.i = +1}},
    {MODKEY, XK_Right, viewnext, {0}},
    {MODKEY, XK_Left, viewprev, {0}},
    {MODKEY | ShiftMask, XK_Right, tagtonext, {0}},
    {MODKEY | ShiftMask, XK_Left, tagtoprev, {0}},
    TAGKEYS(XK_1, 0) TAGKEYS(XK_2, 1) TAGKEYS(XK_3, 2) TAGKEYS(XK_4, 3)
        TAGKEYS(XK_5, 4) TAGKEYS(XK_6, 5) TAGKEYS(XK_7, 6) TAGKEYS(XK_8, 7)
            TAGKEYS(XK_9, 8){MODKEY | ShiftMask, XK_x, quit, {0}},
};

/* button definitions */
/* click can be ClkTagBar, ClkLtSymbol, ClkStatusText, ClkWinTitle,
 * ClkClientWin, or ClkRootWin */
static const Button buttons[] = {
    /* click                event mask      button          function argument */
    {ClkLtSymbol, 0, Button1, setlayout, {0}},
    {ClkLtSymbol, 0, Button3, setlayout, {.v = &layouts[2]}},
    {ClkWinTitle, 0, Button2, zoom, {0}},
    {ClkStatusText, 0, Button2, spawn, {.v = termcmd}},
    {ClkClientWin, MODKEY, Button1, movemouse, {0}},
    {ClkClientWin, MODKEY, Button2, togglefloating, {0}},
    {ClkClientWin, MODKEY, Button3, resizemouse, {0}},
    {ClkTagBar, 0, Button1, view, {0}},
    {ClkTagBar, 0, Button3, toggleview, {0}},
    {ClkTagBar, MODKEY, Button1, tag, {0}},
    {ClkTagBar, MODKEY, Button3, toggletag, {0}},
};
