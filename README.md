# 📟 STM32 NUCLEO-H753ZI C++ Demo
This repository contains a simple C++ demo with Application/application.cpp file.
It is based on
- [🔗STM32CubeMX](https://www.st.com/en/development-tools/stm32cubemx.html) (v6.17.0)<br>
- [🔗Visual Studio Code](https://code.visualstudio.com/) (v1.117.0) with the 
- ST extension pack [🔗 STM32CubeIDE for Visual Studio Code](https://marketplace.visualstudio.com/items?itemName=stmicroelectronics.stm32-vscode-extension) (v3.8.0)

<br>

## 📁 Folder & File Structure
```
nucleo-h753zi-threadx-demo/ ....... # Root folder of repository.
├─ STM32Project/ .................. # Root folder of STM32 firmware project.
│  ├─ .settings/
│  │  ├─ bundles.store.json ....... # Versions of st bundles, see System Bundle Manager in STM32CubeIDE for Visual Studio Code extension.
│  │  ├─ bundles-lock.store.json .. # Versions of st bundles, see System Bundle Manager in STM32CubeIDE for Visual Studio Code extension.
│  │  └─ ide.store.json ........... # Board information.
│  ├─ .vscode/
│  │  ├─ launch.json .............. # Debugger configuration.
│  │  └─ task.json ................ # Task to restart incl. build during debugging.
│  ├─ Application/
│  │  ├─ application.cpp .......... # Simple demo application.
│  │  └─ CMakeLists.txt ........... # Changed compiler settings, automatic include sources in 'Application' folder.
│  ├─ Core/
│  │  └─ Src/
│  │     └─ main.c ................ # Added the call of C++ functions Setup() and Loop().
│  ├─ .clangd ..................... # Clangd configuration
│  ├─ .clang-format ............... # Example of clang formatter configuration.
│  ├─ .gitignore .................. # Git ignore configuration.
│  ├─ CMakeLists.txt .............. # Link to 'Application' subdirectory added, this includes the CMakeLists.txt in Application folder.
│  ├─ README.doc .................. # GitHub readme file.
│  ├─ STM32Firmware.ioc ........... # STM32 configuration file for STM32CubeMX
│  └─ STM32Project_open_in_VSCode.code-workspace  # VSCode workspace to open the project via double click.
```

<br>

## 🛠️ Tools
Install and configure the tools:

### STM32CubeMX
1. Install STM32CubeMx [🔗STM32CubeMX](https://www.st.com/en/development-tools/stm32cubemx.html) 

2. Install the [🔗STM32CubeH7 MCU Package](https://www.st.com/en/embedded-software/stm32cubeh7.html#:~:text=STM32Cube%20MCU%20Package%20for%20STM32H7%20series%20%28HAL%2C%20Low-Layer,easier%20by%20reducing%20development%20effort%2C%20time%20and%20cost.) in SMT32CubeMX

### STLink Upgrade Tool
1. Install the [🔗STLink Upgrade Tool](https://www.st.com/en/development-tools/stsw-link007.html).
  
2. Connect the CN1 Micro-USB of your NUCLEO-H753ZI board to your PC.

3. Start the tool by double-clicking the *`STLinkUpgrade.jar`* file.
   
4. Set *`MCO Output`* to *`HSE/5 (5MHz)`*<br>
  This is the clock that is provided to the STM32 as the HSE clock.
   > 🔍 **Background:**<br>
   > The 5 MHz value has been selected to make it easier to reach the STM32H753ZI's maximum CPU clock of 480 MHz. For other controllers, different values may be required. Please refer to the relevant STM32 configuration page or use the STM32CubeMx tool to find the correct value.


### VSCode
1. Install [🔗Visual Studio Code](https://code.visualstudio.com/)

2. Create a *`STM32 Dev`* VSCode profile for STM32 development (see: https://code.visualstudio.com/docs/configure/profiles).

3. In this *`STM32 Dev`* profile install the extension pack [🔗 STM32CubeIDE for Visual Studio Code](https://marketplace.visualstudio.com/items?itemName=stmicroelectronics.stm32-vscode-extension)

<br>

## 💾 Open Project first Time

### First Time

1. Clone this repo.

2. Open *`STM32Firmware.ioc`* in STM32CubeMX and generate the sources.

3. Open VSCode and switch to the *`STM32 Dev`* profile.

4. Select 'File' / 'Open Workspace from File...' and search the file *`STM32Project_open_in_VSCode.code-workspace`*
  
5. Click *`yes`* if the message box *`Would you like to configure discovered CMake project(s) as STM32Cube project(s)?`* appears in the lower right corner.
   > 💡 **Hint:**<br>
   > If this dialog box does not appear, or if it disappears after a few seconds, try closing the project folder via 'File' / 'Close workspace'
   > and > opening it again in VSCode. Please be patient, it may take more than 30 seconds for the dialog box to appear.
   
6. Click *`Debug`* if *`Select a configure preset for STM32Project`* appears in top command bar.<br>
   > 💡 **Hint:**<br>
   > If you miss this selection, enter the command >CMake: Select Configure Preset to show it again.

### Daily usage

1. Open the project by double clicking the *`STM32Project_open_in_VSCode.code-workspace`* file.

<br>

## 🚀 Build the Project in VSCode
1. Perform the command *`>CMake: Delete Cache and Reconfigure`*.<br>
   > 💡 **Hint:**<br>
   > This will rebuild the CMake structure. This is only needed if you change something on CMakeLists.txt or you add, rename or delete a source file.  
   > If you have some changes on clangd or other issues delete the complete build folder and try again. 

2. Perform a complete clean rebuild with the command *`>CMake: Clean Rebuild`*.

3. Or build only the changes with the command *`>CMake: Build`*

<br>

## 🔍 Debugging
1. Connect the CN1 Micro-USB of your NUCLEO-H753ZI board to your PC.
   
2. Switch to the 'Run and Debug' view in the right sidebar.
   
3. Click on the green play button. 
