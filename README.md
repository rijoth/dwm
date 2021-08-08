My fork of dwm - dynamic window manager
============================
dwm is an extremely fast, small, and dynamic window manager for X, I used a number of patches in this build to make dwm more productive.

**Note** : This fork is based on [gruvbox](https://github.com/morhetz/gruvbox) theme and can matched with my build of [st](https://github.com/rijoth/st).

The patches I added to this build include:
============================
+ dwm-movestack-6.1.diff (This plugin allows you to move clients around in the stack and swap them with the master.)
+ dwm-alwayscenter-20200625-f04cac6.diff (All floating windows are centered.)
+ dwm-attachbottom-6.2.diff (New clients attach at the bottom of the stack instead of the top.)
+ dwm-vanitygaps-20190508-6.2.diff (Adds (inner) gaps between client windows and (outer) gaps between windows and the screen edge.)
+ dwm-status2d-6.2.diff (Colors and rectangle drawing in DWM status bar.)
+ dwm-noborder-6.2.diff (Remove the border when there is only one window visible.)
+ dwm-hide_vacant_tags-6.2.diff (Prevents dwm from drawing tags with no clients.)
+ dwm-autostart-20200610-cb3f58a.diff (This patch will make dwm run "~/.dwm/autostart_blocking.sh" and "~/.dwm/autostart.sh &" before entering the handler loop.)

The dependencies for my fork of dwm.
===========================
+ libxft
+ Jetbrains Mono
+ st
+ dmenu

Requirements
------------
In order to build dwm you need the Xlib header files.


Installation
------------
Edit config.mk to match your local setup (dwm is installed into
the /usr/local namespace by default).

Afterwards enter the following command to build and install dwm (if
necessary as root):

    make clean install

Running dwm
-----------
Add the following line to your .xinitrc to start dwm using startx:

    exec dwm

In order to connect dwm to a specific display, make sure that
the DISPLAY environment variable is set correctly, e.g.:

    DISPLAY=foo.bar:1 exec dwm

(This will start dwm on display :1 of the host foo.bar.)

In order to display status info in the bar, you can do something
like this in your .xinitrc:

    while xsetroot -name "`date` `uptime | sed 's/.*,//'`"
    do
    	sleep 1
    done &
    exec dwm


Configuration
-------------
The configuration of dwm is done by creating a custom config.h
and (re)compiling the source code.

Adding an autostart file
-------------
My fork of dwm has been patched in such a way that it looks for an autostart file at: $HOME/.dwm/autostart.sh
You will need to create this file and the directory that it is located.  An example autostart.sh is included below:

```console
rijo@rijo-pc .dwm$ cat autostart.sh
nitrogen --restore &
slstatus &
alsamixer &
#dwmblocks &
#nm-applet &
```
