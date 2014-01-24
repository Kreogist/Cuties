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
- Intel GMA-HD / nVIDIA GeForce 6200LE / ATI Radeon X300 or better.
- ??MB of disk space.

##Required OS

Cuties is a cross-platform application. It is supported on a variety of 32-bit and 64-bit platforms. You can use Cuites on the following desktop platforms:

- Microsoft® Windows® XP Service Pack 2 or later.
- Apple Mac OS X Lion 10.7 or later.
- Linux/X11

## Prerequisites

Cuties requires that various tools and packages be available for use in the build procedure. Modifying Cuties sources requires additional tools described below.

If you think the following step is too advanced or too tedious, we provide you a [Quick preparing guide](https://github.com/Kreogist/Cuties/wiki/Quick-preparing-guide). And you can skip to [Downloading the source](https://github.com/Kreogist/Cuties/wiki/Build-&-Install-Cuties#downloading-the-source).

### Tools/packages necessary for building Cuties

* **Qt 5.1.1 libraries or above**

You should have 5.1.1 or later version of Qt. We suggest you to use Qt 5.2 to build Cuties.

Please **DO NOT** use Qt 5.1, there're several bugs in Qt 5.1 and it works really bad on Mac OS X. But Qt 5.1.1 works really nice.

* **Compilers on your own system**

You should have a compiler for your own operating system. 

For Windows, we suggest you to use MinGW GNU Compiler Collections (MinGW GCC). You can get it from the [homepage](http://gcc.gnu.org/) of GCC. If you hope that you don't have to worry about the compilers, we suggest you to download binary package 'Qt 5.2.0 for Windows 32-bit' on Qt Project [download page](http://qt-project.org/downloads).

For Mac OS X, we suggest you to use XCode with command line tools. You can get it from the Mac App Store, and you can get Command Line Tools from Apple Developer. You can access [Downloads](https://developer.apple.com/downloads/) on Apple Developer to get a command line tools for XCode 5.0. We find out that command line tools will not provided any more on the XCode 5.0.

For Ubuntu Linux or other Linux user, you should provide your own compilers. You need `g++` and `gcc` to build Cuties for essential need.

If you have trouble with set up Qt, please visit [Download Qt](http://qt-project.org/downloads) for binary packages, [Getting Started with Qt](http://qt-project.org/doc/qt-5/gettingstarted.html) for Downloading and Installing Qt guide.

### Tools/packages additional for building GCC

* **Qt Creator 2.7 or above**

You may need a Qt Creator to do make and build for you instead of doing them by yourself. We suggest you to build Cuties with Qt Creator.

For Qt 5.1.1, we suggest you to use Qt Creator 2.7.2. For Qt 5.2, we suggest you to use Qt Creator 3.0. For more details about Qt Creator, please visit [Qt Project](http://qt-project.org/).

* **Qt Linguist**

You may need Qt Linguist to release a translation file, or you have to release translation files by `lupdate` and `lupdate`. 

* **CMake**

We are know currently working on build Cuties for CMake. You can use CMake instead of qmake to build Cuties if you like to.

### Tools/packages necessary for modifying Cuties

* **A code editor or an IDE**

To modifying Cuties code, you should have a code editor - like Notepad in Windows, though we all don't like to use it :) - or an IDE - like Qt Creator.

So, we really suggest you to download the full package of Qt 5.1.1 or above. You can find Qt Creator and Qt Linguist on http://qt-project.org. We suggest you to download a binary package which includes Qt libraries and Qt Creator from http://qt-project.org/downloads.

### Tips from Kreogist
* **The version of Qt we used to build Cuties**

We build Cuties on Windows Platform via Qt 5.2.0 for Android (Windows 32-bit, 761 MB), on Mac OS X Platform via Qt 5.2.0 for Android and iOS (Mac, 1.0 GB), and on Linux via Qt 5.1.1 for Linux 64-bit (415 MB).

* **Set environment variables**

This is really important. For Windows and Mac OS X users.

* Windows

If you are using windows, add the path of Qt to your system environment variables %PATH%. It should be like a path below:

    D:\Qt\Qt5.2.0\5.2.0\mingw48_32\bin

And you have to add MinGW compiler path to your system environment variables %PATH%. To learn more about system environment varibables, please visit [Environment variable](http://en.wikipedia.org/wiki/Environment_variable#Microsoft_Windows) on Wikipedia. To learn more about how to set system environment variable on Windows, please visit [User Environment Variables](http://msdn.microsoft.com/en-us/library/windows/desktop/bb776899%28v=vs.85%29.aspx) from Microsoft Dev Center - Desktop.

* Mac OS X

FIXME: check the path!

You should know the basic operate of vi or any text editor you'd like to use. To learn the basic operate of vi, please visit [Vim documentation: help](http://vimdoc.sourceforge.net/htmldoc/help.html) for moving the text cursor, text insert and file saving in vi. These means are the same in both vi and vim.

Launch your terminal, input:

    sudo vi /etc/paths

and input your password to launch `vi` editor to edit `path` file. You should check whether the Qt directory is in the file. It should be like a path below:

    Applications/Qt5.2.0/5.2.0/clang64/bin

## Downloading the source

Cuties is distributed via Git and HTTP tarballs compressed with zip or tar.gz.

You can download our source code from the bottom of the "Download" page at Cuties [homepage](http://kreogist.github.io/Cuties/). Click in "Project Cuties". And choose the package you would like to. Here's a [link](http://kreogist.github.io/Cuties/en/opensource.html) to Project Cuties in English. Or if you like to, here we provide the four links to download the package directly:

* [Cuties source code tar.gz package(master)](https://github.com/Kreogist/Cuties/tarball/master): tar.gz format source code package of branch master. 
* [Cuties source code zip package(master)](https://github.com/Kreogist/Cuties/zipball/master): zip format source code package of branch master. 
* [Cuties source code tar.gz package(dev)](https://github.com/Kreogist/Cuties/tarball/dev): tar.gz format source code package of branch dev. 
* [Cuties source code zip package(dev)](https://github.com/Kreogist/Cuties/zipball/dev): zip format source code package of branch dev. 

You can also get the source code by cloning the git repository. For more information about Git and Manage your code, please visit [Git, managed code](https://github.com/Kreogist/Cuties/wiki/Git,-managed-code).

The source code includes Cuties and KciConsoleRunner. For previous versions there were downloadable at the [Development schedule](https://github.com/Kreogist/Cuties/wiki/Development-schedule) of Cuties.

## Building

Here we will use Qt Creator to build Cuties. We will show you how to build Cuties in Windows platform. It is nearly the same as what it will be in Mac OS X and Linux.

Launch Qt Creator and open the `Kreogist-Cuties.pro` in `src` folder. 

Select kit Release > app for the project. Choose Build > Build Project or press Ctrl+B to build Cuties. Wait for it finished.

Select kit Release > ConsoleRunner. And Choose Build > Build Project or press Ctrl+B to build command line application executor. Wait for it finished.

Open your build directory in your file browser. You can find `app` directory, `tools` directory and `Makefile` file. Open `tools` folder, there will be only one folder named `ConsoleRunner`. Open ConsoleRunner folder. You will find several folders and files:

	debug                  <Directory>
	release                <Directory>
	Makefile               <File>
	Makefile.Debug         <File>
	Makefile.Release       <File>

Open release folder, you will find a binary file `KciConsoleRunner.exe`, others will be `KciConsoleRunner`. Copy this file to directory `(You build directory)/app/release`.

Then switch to the `src` folder which contains `Kreogist-Cuties.pro`, open `app` folder, copy file `default.style` and `DefaultColorConfig.ini` file to the directory `(You build directory)/app/release`. These two files are color configure file.

The copy the following files to the directory `(You build directory)/app/release`:

ICU Libraries:

    icudt51.dll
    icuin51.dll
    icuuc51.dll

For MinGW compiler, C/C++ runtime libraries.

    libgcc_s_dw2-1.dll
    libstdc++-6.dll
    libwinpthread-1.dll

Qt 5 Libraries:

    Qt5Core.dll
    Qt5Gui.dll
    Qt5Network.dll
    Qt5Widgets.dll

Now, try to launch Cuties.exe, It should can be used.

##Install

Currently, Cuties is still don't have a unintaller or setup program. Cuties won't write any other values to system. So if you wan't to remove Cuties, just delete it.

##License
   Kreogist-Cuties is free software: you can redistribute it and/or modify it under the terms of the GNU General Public License as published by the Free Software Foundation, either version 3 of the License, or (at your option) any later version.

   Kreogist-Cuties is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU General Public License for more details.

   You should have received a copy of the GNU General Public License along with Kreogist-Cuties.  If not, see <http://www.gnu.org/licenses/>.

