# FW embedded x86/64 linux

This repository contains a firmware generic for microcontrollers or linux embedded.

## Submodules

  - [bsp_linux](https://github.com/grivera90/bsp_linux)
  - [libraries/cli_board](https://github.com/grivera90/cli_board)
  - [libraries/configuration_parser](https://github.com/grivera90/configuration_parser)
  - [libraries/file_binary_pack](https://github.com/grivera90/file_binary_pack)
  - [libraries/log_debug](https://github.com/grivera90/log_debug)
  - [libraries/ring_buffer](https://github.com/grivera90/ring_buffer)
  - [libraries/scheduler](https://github.com/grivera90/scheduler)

## Download

For each repo execute this cmd's

  - git submodule init
  - git submodule update

or in the project for init and update all submodules (recommended by me)

  - git clone --recursive git@github.com:grivera90/fw_embedded_linux.git

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
    - For "can_port" parameter select "vcan0" to virtual can or "can0" to can device.
  - In a terminal: 
    - cd fw_embedded_linux/
    - ./fw_embedded_linux
  - In fw_embedded_linux/ there is an file "run.sh". You can execute that in a terminal to run fw_embedded_linux firmware with some parameters. 
  - Format:  "./run.sh <-v> `<target>`". -v parameter is optional.
    - Option 1: "./run.sh -v fw_embedded_linux". The -v parameter run the firmware with a CLI separated to interact with the program.
    - Option 2: "./run.sh fw_embedded_linux" without CLI.

## Deployment

  - TBD

## Authors

  - [Gonzalo Rivera](gonzaloriveras90@gmail.com)

## License

© 2023 grivera. All rights reserved.