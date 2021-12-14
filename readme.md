# OF_Essentia_Demo - A Yin-Based Tuner

## What is this?

This is one of two demo projects meant to show how [Openframeworks](https://openframeworks.cc/) and [Essentia](https://essentia.upf.edu/index.html) can be used to create small real-time audio applications. This project in particular creates a monophonic tuner using Essentia's Yin-pitch implementation. When set up, the app should look like [this.](https://youtu.be/FvqDZTUYr9k) It is my hope that those looking to develop small scale audio app prototypes may find this project useful as an example to study.

## Setup

*This setup guide applies to Debian Linux distros, as that is the platform the project was made on. Both Openframeworks and Essentia are well supported on MacOS as well, however I am unable to describe the specifics of setting up the project and linking libraries for that platform. If you are looking to build the project on Windows, I **Strongly** recommend that you upgrade to Windows 11 and install WSL. This will let you run a Debian-based distro of your choice and follow this guide exactly (upgrading to Windows 11 is necessary to use GUI applications in WSL). You will likely find this much easier than setting up both Openframeworks and Essentia for Windows.*

*Openframeworks supports multiple IDEs for development. However, this guide describes the process for building projects in Linux using make. This means that any text editor can be used. I provide additional details for setting up the project in Visual Studio Code at the end.*

### 1) Install OpenFrameworks and Essentia

Download and install both Openframeworks and Essentia from their respective sites. The setup guide for Openframeworks for Linux is found [here.](https://openframeworks.cc/setup/linux-install/) The setup guide for all Essentia platforms is found [here.](https://essentia.upf.edu/installing.html) Note that for this project it is necessary to build Essentia from source. Therefore you will need to follow the guides for installing dependencies on your platform and compiling the library. This guide will assume a default installation of both Openframeworks and Essentia.

I recommend that you test your OpenFrameworks installation by building and running a few of the included example projects before proceeding. You will also need to install the project generator described in the setup guide.

### 2) Configure the project using projectGenerator

Once you've set up Openframeworks and the project generator, navigate to the /*your_OF_root_folder*/apps/myApps and clone this repo directly into it. Then navigate to /*your_OF_root_folder*/projectGenerator-Linux64 and run projectGenerator.

In addition to setting up new projects, the project generator can be used to configure preexisting ones. Click on the "import" button in projectGenerator and select the folder OF_Essentia_Demo. Under addons you should now see "ofxGui" and "ofxSvg". Openframeworks has a number of community addons and these are two which are packaged with the base installation. You should also see "Linux 64-bit (QtCreator)" under platforms. Note that it is not necessary to actually use QtCreator for development even though its listed here.

Click the "Update" button. You should now see a number of new files in OF_Essentia_Demo. If you're not using QtCreator, you may delete the .qbs file. The last thing to do is modify the config.make file to link the Essentia library components.

### 3) Import Essentia in config.make

In the config.make file set these parameters to the following:

PROJECT_LDFLAGS += -L/usr/local/lib -lessentia -lfftw3 -lyaml -lavcodec -lavformat -lavutil -lsamplerate -ltag -lfftw3f -lchromaprint -lavresample

PROJECT_CFLAGS = -pipe -Wall -O2 -fPIC -I/usr/local/include/essentia/ -I/usr/local/include/essentia/scheduler/ -I/usr/local/include/essentia/streaming/  -I/usr/local/include/essentia/utils -I/usr/include/taglib -I/usr/include/

Make sure that the values for PROJECT_LDFLAGS are assigned with += and that neither parameter is commented out (they will be commented out by default).

You should now be able to build the project using "make -j" and run the project using "make run". If you get a build error mentioning that your OF install can't be found check the OF_ROOT parameter in config.make and try setting it to the *absolute* path of your openframeworks root folder. If the build was successful, you will see a "bin" folder under the main project folder. It is possible to copy this folder to any other device of the same platform and run the project by running the executable found within.

### 4) Setting up Include Paths in VS Code

While everything should build fine, your editor may not recognize any of the include statements or function calls. This is because the include paths for both OpenFrameworks and Essentia have not been configured in your editor. The steps to do this will vary depending on the editor. However, OpenFrameworks does include a template for use with VS Code that makes it a bit faster to get these paths set up. 

Open the project generator and import this project again. Click on the gear icon and activate "Advanced options". Now on the main page you should see a template section. Select "Visual Studio Code" under templates and click on "Generate".

Now if you open the project in VS code you should see a c_cpp_properties.json file that adds all of the include paths for the core libraries of OpenFrameworks. However, it may stil be missing the folders for any OpenFrameworks addons as well as any Essentia components. In the section corresponding to your platform, add these to includePath (note the path to the Essentia components may be slightly different if your platform is not Linux):

"${workspaceRoot}/../../../addons/ofxGui/src"

"${workspaceRoot}/../../../addons/ofxSvg/src"

"/usr/local/include/essentia"

"/usr/local/include/essentia/scheduler"

"/usr/local/include/essentia/streaming"

"/usr/local/include/essentia/utils"

Code completion and intellisense should now be working in VS Code provided you've installed the C++ plugin!

# Learning OpenFrameworks and Essentia

As stated, my hope is that this project may be useful as a learning aid for those trying to develop their own audio app prototypes. Of course, to get any use out of the project it is still necessary to learn OpenFrameworks and Essentia on their own. [OfBook](https://openframeworks.cc/ofBook/chapters/foreword.html) is an excellent introduction to OpenFrameworks and even C++ in general. As for Essentia, the [design overview](https://essentia.upf.edu/design_overview.html) and description of [standard mode](https://essentia.upf.edu/howto_standard_extractor.html) cover everything necessary to understand this project.


