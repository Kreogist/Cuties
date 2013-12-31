#Cuties

Copyright © 2013 Kreogist Dev Team. All rights reserved.

##Menu
* Recommended System Requirements
* Required OS
* Building
* Install
* License

##Recommended System Requirements

- Intel® Pentium™ III M processor or better.
- 64MB of RAM or better(DDR or better recommended).
- Intel® HD Graphics 2000 or better
- ??MB of disk space.

##Required OS

Cuties is a cross-platform application. It is supported on a variety of 32-bit and 64-bit platforms. You can use Cuites on the following desktop platforms:

- Microsoft® Windows® XP Service Pack 2 or later.
- Apple Mac OS X Lion 10.7 or later.
- Linux/X11

##Building

###Prerequisites

To build the source the following must first be installed on your system:

* `Qt` — to compile, link and debug the source.
* `Github` - to clone our project or fork our project on Github.

IMPORTANT:
You should build Cuties via Qt 5.0.1 or later version. 

You can find Qt Creator and Qt Linguist on http://qt-project.org. We suggest you to download a binary package which includes Qt libraries and Qt Creator from http://qt-project.org/downloads. 

We build Cuties on Windows Platform via Qt 5.1.1 for Windows 32-bit (MinGW 4.8, OpenGL, 666 MB), on Mac OS X Platform via Qt 5.1.1 for Mac (425 MB), and on Linux via Qt 5.1.1 for Linux 64-bit (415 MB).

You can find Github on https://help.github.com/articles/set-up-git. You can also find how to set up git on that page. Follow the instructure and install Git. You need a Github account.

###Building Cuties

You should install the `Qt` and `Github`, and both of the tools have been well configured.

After this you can clone our projects on either GUI or Command-Line. Here we are using Command-Line.

Launch your terminal, Input:

	git clone https://github.com/Kreogist/Cuties.git

Open the folder and find 'src' folder, open Kreogist-Cuties.pro via Qt Creator. Compile and build the ConsoleRunner project first using Release Mode and then the app project. Copy KciConsoleRunner app to the path of Kreogist-Cuties. 

If you are using Windows, please copy the following DLLs to the path of Kreogist-Cuties if you are using a MinGW compiler:

        icudt51.dll
        icuin51.dll
        icuuc51.dll
        libgcc_s_dw2-1.dll
        libstdc++-6.dll
        libwinpthread-1.dll
        Qt5Core.dll
        Qt5Gui.dll
        Qt5Widgets.dll

For MSVC compiler, you should also copy the basic DLLs to the path of Kreogist-Cuties.

##Install


##License
   Kreogist-Cuties is free software: you can redistribute it and/or modify it under the terms of the GNU General Public License as published by the Free Software Foundation, either version 3 of the License, or (at your option) any later version.

   Kreogist-Cuties is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU General Public License for more details.

   You should have received a copy of the GNU General Public License along with Kreogist-Cuties.  If not, see <http://www.gnu.org/licenses/>.

