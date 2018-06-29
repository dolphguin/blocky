# blocky


## Compression implementation

First off you'll need to create a new subfolder within the **OpenFOAM-x.x/src/OpenFOAM/IOStreams** folder called **Blocky**.

This **OpenFOAM-x.x/src/OpenFOAM/IOStreams/Blocky** folder then needs to be filled with all the files and folders in the **src** folder of this repository.

In the **OpenFOAM-x.x/src/OpenFOAM/IOStrems/FStream** folder you need to change the *OFStream.C* file:
### New include:
`#include "../Blocky/io/blockyoutputstream.hpp"`
### Change to existing code:
#### Old code:
`ofPtr_ = new ogzstream((pathname + ".gz").c_str());`
#### New code:
`ofPtr_ = new BlockyOutputStream((pathname + ".bky").c_str());`

The *files* text file within the **OpenFOAM-x.x/src/OpenFOAM/Make** folder has to contain all the used blocky files:



## Decompression implementation
