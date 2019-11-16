#!/bin/bash

# Make sure globstar is enabled
shopt -s globstar

count=0

#Create tmp file
tmpFile=$(mktemp ./njasm.XXXXXX)

# Loop throw all files
for file in src/**/*; do
    # compile asm files
    if [[ $file =~ \.asm$ ]]; then
       compiler/nja $file prog${count}
       ((count++))
    # compile nj files
    elif [[ $file =~ \.nj$ ]]; then
       
       # NJA -> ASM
       compiler/njc $file > $tmpFile
       
       # ASM -> BIN
       compiler/nja $tmpFile prog${count}
       ((count++))
    fi
done

# Remove tmp file
rm $tmpFile
