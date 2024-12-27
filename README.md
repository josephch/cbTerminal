# cbTerminal plugin for Code::Blocks (Linux)
cbTerminal provides bash shell in the bottom pane of Code::Blocks
cbTerminal depends on GTK widget VTE

## Building the plugin
Please install libvte-2.91-dev. For Ubuntu, you can install it via below command.
```
sudo apt install libvte-2.91-dev
```
Also codeblocks needs to be installed.
Please run following commands to build with cmake
```
cd cbTerminal
mkdir build
cd build
cmake ../
make
```
Alternatively, you can open the project in codeblocks and build it from there.

## Thanks
Most of the code is taken from ThreadedSearch plugin and modified. Thank you authors of threaded search plugin.
