#!/bin/bash  
################################################################################
#                              SCRIPT                                  
#                                                                              
#   title:          run
#   description:    este script lee del STDIN los comandos que seran enviados al 
#                   nodo virtual a traves del nodo que simula la consola.
#   author:         fantasma.
#   date:           25/08/2023
#   version:        0.1    
#   usage:          ./read_cmd.sh <program-name>
#   notes:
#   bash_version:
#
################################################################################
#                               VARIABLES
################################################################################
program=$1
pipe_tx=/tmp/pipe_tx
pipe_rx=/tmp/pipe_rx
my_prompt="$: "
instructions="Please type vboard -h to more information"
################################################################################
#                               BODY
################################################################################
#  SCRIPT LOGIC GOES HERE
trap ctrl_c INT

function ctrl_c() 
{
        rm $pipe_tx
        rm $pipe_rx
        killall -v $program
        clear
        echo "** finished **"
        kill -15 $PPID
}

if [[ ! -p $pipe_tx ]]; then
    mknod $pipe_tx p
    exec 8<>$pipe_tx
fi

if [[ ! -p $pipe_rx ]]; then
    mknod $pipe_rx p
    exec 7<>$pipe_rx
fi

echo "$instructions"

while :
do

    read -p "$my_prompt" usr_cmd
    length=$(echo -n "$usr_cmd" | wc -m)

    if [ ! $length = "0" ]; then
        echo "$usr_cmd" >&8
    fi
    
    while : 
    do
        IFS=$'' read -t 0.1 node_cmd <&7
        length=$(echo -n "$node_cmd" | wc -m)
        if [ ! $length = "0" ]; then
            echo "$node_cmd"
        else
            break
        fi        
    done 

done
################################################################################
#                               END
################################################################################
