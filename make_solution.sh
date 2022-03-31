#! /usr/bin/env bash

function main()
{
    local files=("Makefile")
    local dir="solution"

    if [ ! -d ${dir} ]; then
        mkdir ${dir}
    fi
    cp ${files[*]} ${dir}
    cp *.cpp ${dir}
    cp *.hpp ${dir}
    cp *.h ${dir}
    tar -cvf solution.tar ${dir}

    rm -r ${dir}
}

main $@