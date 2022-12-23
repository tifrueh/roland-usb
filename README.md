# roland-usb

This program is designed to manage the renaming of audio files for the Roland FP-30 Digital Piano.
Audio files on a USB drive are only readable to the FP-30 if they have specific names, e. g. "R068_001.wav". But names like these are not truly human-readable and changing the order of the songs or adding a new one as the first one can prove to be very tedious when done by hand.


## On the FP-30

There are a few things to note when using a USB drive with the FP-30.

1. Before putting any songs on the drive you want to use, you need to format the drive. The procedure for this is described in the manual on page 6.

2. For the FP-30 to be able to play any of the songs on the drive, they must be in the `WAV` format, 44.1 kHz, 16-bit linear. More information on playable formats is given in the manual on page 11.

[Official owner's manual](https://www.roland.com/global/support/by_product/fp-30/owners_manuals/367f2953-5e00-431c-8fd7-9bc663ce1ec8/)


## Installation

Currently, there are two ways to install `roland-usb`on your machine:


### 1. Compile and Install it Yourself (Recommended)

The program can be compiled and installed using [GNU make](https://www.gnu.org/software/make/).
Just download the source and run:

~~~ text
$ make
# make install
~~~

The process can be influenced using the following variables:

~~~ text
CXX          The compiler to be used (default is g++)
CPPFLAGS     Preprocessor flags
CXXFLAGS     Compiler flags
LDFLAGS      Linker flags
DESTDIR      Installation directory (default is /usr/local -> installation in /user/local/bin)
~~~


### 2. Download Binary and Install Manually

You can also download the binary for your system (if such a binary should exist) from the [latest release](https://github.com/tifrueh/roland-usb/releases/latest). You'll have to take care of the installation yourself, however.


## Usage


### Initialisation

To use the program with a plugged in USB-drive (you can also use it with a normal folder, the process stays the same), you need to initialise this USB-drive first:

~~~ text
$ roland-usb /path/to/usb init
~~~

This will scan the drive for `.wav` files and create a `titles.conf` file, which will contain the names of all files it found, each one on a new line.


### Configuration

You can now edit the `titles.conf` file to configure the order of the songs after they are renamed to the FP-30 format. Simply reorder the lines in `titles.conf` to match the order in which you want the songs to be.

An example: if the file `song1.wav` is on the third line, it will be renamed to `R068_003.wav`, causing it to be the third song when played from the FP-30.


### Adding Songs after Initialisation

If you want to add more songs after the first initialisation, simply add them to the directory while it is decrypted (meaning in the human-readable state) and initialise it again.

You can also add the new files to `titles.conf` manually, of course, but reinitialisation is the recommended method nonetheless.


### Renaming

After a drive (or a folder, for that matter) is initialised, the other two subcommands `encrypt` and `decrypt` can be used.

To rename all files to a FP-30 readable format, use:
~~~ text
$ roland-usb /path/to/usb encrypt
~~~

To rename all files back to a human-readable format, use:
~~~ text
$ roland-usb /path/to/usb decrypt
~~~


### On `titles.conf`

As soon as all the files are renamed to a FP-30 readable name, `titles.conf` is renamed to `.titles.conf`, hiding it on UNIX systems.

This is not without reason: it is **IMPERATIVE** that you **DO NOT** modify `.titles.conf` **EVER**. If you were to do that, `roland-usb` would have no idea (or the wrong idea) on how to rename the files back to a human-readable name.
