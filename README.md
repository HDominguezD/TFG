# TFG
### Important:
This project still is being developed and it may present bugs. More functionalities 
and a revision of the display of the interface soon will be added.
### Description
The purpose of this application is to create a tool that initially 
can represent image, surface and volume data, and a plugin manager 
to add other functionalities to treat this data.

### Getting Started
* __Install CMake:__ Download [CMake](https://cmake.org/download/)
* __Install VTK:__ Download [vtk](https://vtk.org/download/) and unzip.
 
Create a new folder into it and name it build.
Move to /build and execute CMake with the next flags:

```
cmake -DVTK_QT_VERSION:STRING=5 \
      -DQT_QMAKE_EXECUTABLE:PATH=/home/hector/Qt/5.9.6/gcc_64/bin/qmake \
      -DVTK_Group_Qt:BOOL=ON \
      -DCMAKE_PREFIX_PATH:PATH=/home/hector/Qt/5.9.6/gcc_64/lib/cmake  \
      -DBUILD_SHARED_LIBS:BOOL=ON ..
```

Use ```cmake .. ```

use ```make -j4 ```(4 is the number of threads you want to do this action in parallel)

Finally use ```make install```

* __Install QT:__ download the [qt installer](https://www.qt.io/download-qt-installer?hsCtaTracking=9f6a2170-a938-42df-a8e2-a9f0b1d6cdce%7C6cb0de4f-9bb5-4778-ab02-bfb62735f3e5) 
and select the 5.9.6 version.
* __Integrate VTK in QT:__
Move /usr/local/plugins/designer/libQVTKWidgetPlugin to /Qt/Tools/QtCreator/lib/Qt/plugins/Designer

### Features
* __Images:__  
      The application can read and represent tif files with one image.

![TifImage](/Documentation/tifImage.png)

The application also can read stacks of tif files, and select which tif is showed using a slider.

![TifStack](/Documentation/tifStack.gif)

* __Surface.__  
      The application can read obj files and render the objects.

![Surface](/Documentation/surface.gif)

* __Volume.__  
The application can create volume objects reading tif stack files. The 
opacity and color value of this objects can be modified by the transference
function editor. Also the transfer function can be saved with the next format.
If a transfer function is not found when the tif stack is readed, a default
transfer function is loaded.

![Volume](/Documentation/volume.gif)

A obj object can be loaded to the scene so you can compare the surface and the
volume object, this surface can be scaled with a slider and all the scene can 
be capturated pressing the button.

![Scale](/Documentation/scale.gif)

* __Interface__ The interface is based on docks. You can dock or undock each 
part of the application to distribute the visualization of these parts as 
you want.

![Docks](/Documentation/docks.gif)

* __Plugin Manager__  
All the functionality modules of the project are saved as plugins and loaded
in executions as a normal QT plugins. This plugins are loaded from the directory
ApplicationPackage/Plugins

### Future Features
* __Python script reader__  A plugin to load python scripts will be added,
the main purpose of this addition is to connect the application to a neuronal
network writted in python that analize neurons represented in volumetric data
and separate the trunk of the dentrites of the neuron from the spines.
* __Convert tif volume to obj__  It will be availaible to convert volume objects
to surface objects using the marching cubes algorithm.
* __Change UI__  The interface will be modified to be more like the unity engine
one, specially to ease the navegation during the scene and to center the camera 
in the object we want.
* __Windows and Mac version__ Adding support for windows and Mac

### How to contribute
If you want to contribute to the project by adding some functionalities, you 
must create a .so file and move it into the ApplicationPackage/Plugins folder 
of the project. When the project is initialized all the plugins of that directory
will be loaded.

### Built With
* __[VTK](https://vtk.org/)__: open source software for manipulating and displaying scientific data.
* __[QT](https://www.qt.io/)__: C++ framework used to design the project interfaces
and main code.


### Authors
**Hector Dominguez Diego**     [@HDominguezD](https://github.com/HDominguezD)  
 Contact: h.dominguezd@alumnos.urjc.es or hectorddh13@gmail.com
