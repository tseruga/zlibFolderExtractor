# zlibFolderExtractor
A simple utility to extract a folder of zlibbed files.
<br>
This program only extracts a single folder that contains .z files.
<br>
This program does not handle sub-directories (yet?)
<br><br>
<b>Compile in g++ with the following:</b>
<br>
g++ --std=c++11 removeZ.cpp -lz

<b>Dependencies:</b>
<br>
zlib 1.2.8

<b>Make sure to change the directory in removeZ.cpp to match your own executable location.</b>
<br><br>
Add a folder to extract into the directory that contains the executable.
<br><br>
A folder with name \<folderToUncompress\>_ is created in the same directory and has all of the uncompressed files.
<br><br>
See the example below:
<br><br>
Settings in removeZ.cpp:
<br>
exeDir = "/home/tyler/Desktop/removeZ/"
<br>
folderToUncomp = "CrossSection"
<img src="http://i.imgur.com/lZSHoao.png" title="source: imgur.com" /></a>


