DemPack
==========

This is a tool for reading and writing arbitrary data stored in GoldSource demo files.
It utilizes unused bytes in the demo files for data storage.
The resulting demo files are of exactly the same length as the original ones and behave exactly like the original ones.

#Usage
- `DemPack <path to .dem>`: prints the number of bytes you can pack into the given demo.
- `DemPack <path to .dem> -u`: prints the packed bytes.
- `DemPack <path to .dem> -p <path to out.dem>`: reads the input demo file, packs as many bytes from stdin as it can, then saves the resulting file into out. Outputs the number of bytes packed.

Example usage: `DemPack mydemo.dem -p newdemo.dem < input.txt`, where input.txt contains some text.

#Building
####Windows
- Get [Boost](http://www.boost.org/) and [Boost.Nowide](http://cppcms.com/files/nowide/html/) and build the latter.
- Create a build directory along the *src* directory.
- Run `cmake -DBOOST_ROOT=path\to\boost\base\dir ..` from the build directory.
- Compile the **ALL_BUILD** project from the generated VS solution.

####Linux
- Get Boost.Nowide.
- Create a build directory along the *src* directory.
- Run `cmake ..` from the build directory.
- Run `make` from the build directory.
