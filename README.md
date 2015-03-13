## Quickstart ##

>####./run.sh####

* Downloads [GLFW 3.0.4](http://www.glfw.org/) and [monoEngine](https://github.com/gartenriese2/monoengine) to `dl`.
This step is skipped if the download files are already there.
* Builds everything to `contrib`.  
* Installs the binary file to `bin`.  
* Executes MapCity.  

>####./legacy_run.sh####

* Does the same as `./run.sh`, but uses legacy mode.

## Other commands ##

>####/bin/mapcity####

* Executes MapCity.

>####/bin/mapcity_legacy####

* Executes MapCity in legacy mode.

>####make####

* Downloads [GLFW 3.0.4](http://www.glfw.org/) and [monoEngine](https://github.com/gartenriese2/monoengine) to `dl`.
This step is skipped if the download files are already there.
* Builds everything to `contrib`.  
* Installs the binary file to `bin`.

>####make legacy####

* Does the same as `make`, but uses legacy mode.

>####make clean####

* Deletes all temporary files except `dl`.
* Use this if you don't want to redownload the dependencies.

>####make distclean####

* Deletes all temporary files including `dl`.
* Use this if you want to redownload the dependencies.

## Dependencies ##

### Linux ###

* `cmake`
* Either `g++ 4.9` or `clang++ 3.5`
* `libx11-dev`, `libxrandr-dev`, `libxi-dev`, `libxxf86vm-dev` for OpenGL
* Graphics Drivers that support OpenGL 4.5 (OpenGL 3.3 in legacy mode)
