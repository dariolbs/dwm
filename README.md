# dwm - dynamic window manager
dwm is an extremely fast, small, and dynamic window manager for X made
by the [suckless guys](https://suckless.org/)

## Installation
Edit config.mk to match your local setup (dwm is installed into
the /usr/local namespace by default).

### Building
In order to build dwm you need the Xlib header files.

To compile: `sudo make clean install`

### Running dwm
To run dwm you have to add `exec dwm` to .xinitrc and then run `startx`.

## Features
This fork has some cool features like:
+ Focusing/pushing windows relative to their position (focusdir and pushdir)
+ Systray
+ Replacement bar to put whatever you want
+ Change colors through xresources
+ Change the default attacment method on the fly

### Replacement Bar
You can place whatever text you want on the replacement bar by changing the xroot name.

Example: `xsetroot -name "bar1 left;bar2 right;bar2 left"`

You can change the separator in config.h

### Attachment Methods
There are 2 attachment methods by default, **attachdefault** and **attachbottom**.

You can change them on the fly by using **cycledirection**, mapped to MOD + s by default.

## Configuration
Configuring dwm is made by editing config.h
