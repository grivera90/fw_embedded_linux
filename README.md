# FW embedded x86/64 linux

This repository contains a firmware generic for microcontrollers or linux embedded.

## Submodules

  - [app]()
  - [bsp_linux]()
  - [libraries/cli_board]()
  - [libraries/configuration_parser]()
  - [libraries/file_binary_pack]()
  - [libraries/log_debug]()
  - [libraries/ring_buffer]()
  - [libraries/scheduler]()

## Download

For each repo execute this cmd's

  - git submodule init
  - git submodule update

or in the project for init and update all submodules (recommended by me)

  - git clone --recursive git@bitbucket.org:cuffiateam/ecu_siap_x86_64_linux.git

## Built With

  - [VSCode](https://code.visualstudio.com/download)
  - Install make: 
    - sudo apt install make -y
    - make --version (to confirm) 
  - Install GCC: 
    - sudo apt update
    - sudo apt install build-essential
    - gcc --version (to confirm)
  - Once downloaded and install all this, in a terminal execute: 
    - cd fw_embedded_linux/
    - make
  - Confirm output build and check if executable file "fw_embedded_linux" was created

## Use
  - See can_configuration.conf:
    - nano can_configuration.conf
    - For "can_port" parameter select "vcan0" to virtual can or "can0" to can device
  - In a terminal: 
    - cd fw_embedded_linux/
    - ./fw_embedded_linux
  In fw_embedded_linux/ there is an file "run.sh". You can execute that in a terminal to run fw_embedded_linux firmware with some parameters.
  Format:  "./run.sh <-v> <program-name>". -v parameter is optional
    - Option 1: "./run.sh -v fw_embedded_linux". The -v parameter run the firmware with a CLI separated to interact with the program.
    - Option 2: "./run.sh fw_embedded_linux". Without CLI

## Deployment

  - TBD

## Authors

  - [Gonzalo Rivera](gonzalorveras90@gmail.com)

## License

© 2023 grivera. All rights reserved.