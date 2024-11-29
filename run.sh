#!/bin/bash  
################################################################################
#                              SCRIPT                                  
#                                                                              
#   title:          run
#   description:    
#   author:         fantasma.
#   date:           25/08/2023
#   version:        1.0    
#   usage:          ./run.sh [-v] (opcional) <program-name> <path-to-config-file>
#                   ./run-sh -v name_target workingdir/test_1/node_1_100.conf
#                   ./run-sh name_target workingdir/test_1/node_1_100.conf
#   notes:
#   bash_version:
#
################################################################################
#                               VARIABLES
################################################################################
param_1=$1
param_2=$2
param_3=$3
terminal_name="FW VIRTUAL TERMINAL"
################################################################################
#                               BODY
################################################################################
#  SCRIPT LOGIC GOES HERE

if [[ $param_1 == "-v" ]]
then 
    chmod +x read_cmd.sh
    gnome-terminal --title="$terminal_name" -- sh -c "bash -c \"./read_cmd.sh $param_2; exec bash\""
    ./$param_2 $param_1
else
    ./$param_1 $param_2
fi
################################################################################
#                               END
################################################################################



