# Viewfinder demo application

This application is built on VSCode Getting Started Template (alif_vscode-template)
The default hardware is Gen 2 Ensemble DevKit with camera module and display.

Demo application initializes camera and display modules and starts capturing frames
in a single-frame mode. Each captured frame is processed through bayer-to-RGB and
white balance before updating the frame to display buffer.
While running, the green LED blinks (on DevKit). In error case the red LED is set.

To build the app you need to update the Board Library submodule.
From your local clone, do the following:
1. *git submodule init*
2. *git submodule update*

The required software setup consists of VSCode, Git, CMake, cmsis-toolbox, Arm GNU toolchain and Alif tools.
Please refer to the [Getting Started Guide](https://alifsemi.com/download/AUGD0012) for more details.

After setting up the environment according to the guide you can select File->Open Folder from VSCode
and press F1 and start choosing from the preset build tasks.
F1 --> Tasks:Run Task --> First time pack installation
F1 --> Tasks:Run Task --> Generate and Build with csolution + cbuild
F1 --> Tasks:Run Task --> Program with Security Toolkit

