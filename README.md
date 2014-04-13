## Installation

It is necessary to export some environment variables for a local installation. Here is an example:

	export PATH=$HOME/.usr/bin:$PATH
	export CPATH=$HOME/.usr/include
	export LD_LIBRARY_PATH=$HOME/.usr/lib:$LD_LIBRARY_PATH
	export LIBRARY_PATH=$HOME/.usr/lib:$LIBRARY_PATH
	export MANPATH=$HOME/.usr/share/man:$MANPATH
	export PYTHONPATH=$HOME/.usr/lib/python2.7/site-packages/:$PYTHONPATH

First create all autoconf and automake files with

	autoreconf

For local installations to *$HOME/.usr* use

	./configure --prefix=$HOME/.usr

and otherwise simply

	./configure

Now the source can be compiled and installed with

	make
	make install

The configuration file *~/.pwgen.conf* has to be installed manually. An example file *src/pwgen.conf* is available. The file contains a field called *seed-init* which should be set to a random integer. Passwords are generated using the initial seed and the private password.
