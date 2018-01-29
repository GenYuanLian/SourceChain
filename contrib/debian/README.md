
Debian
====================
This directory contains files used to package srcchaind/srcchain-qt
for Debian-based Linux systems. If you compile srcchaind/srcchain-qt yourself, there are some useful files here.

## srcchain: URI support ##


srcchain-qt.desktop  (Gnome / Open Desktop)
To install:

	sudo desktop-file-install srcchain-qt.desktop
	sudo update-desktop-database

If you build yourself, you will either need to modify the paths in
the .desktop file or copy or symlink your srcchain-qt binary to `/usr/bin`
and the `../../share/pixmaps/srcchain128.png` to `/usr/share/pixmaps`

srcchain-qt.protocol (KDE)

