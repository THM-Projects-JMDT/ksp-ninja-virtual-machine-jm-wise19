#!/bin/bash

cd ${0%/*.*}/

# Make sure globstar is enabled
shopt -s globstar

count=0

#Create tmp file
tmpFile=$(mktemp ./njasm.XXXXXX)

# Loop throw all files
for file in src/**/*; do
   # get filePath wihtout src
   out=bin/${file#src/}

    # compile asm files
    if [[ $file =~ \.asm$ ]]; then
       compiler/nja $file ${out%.*}
       ((count++))
    # compile nj files
    elif [[ $file =~ \.nj$ ]]; then
       
       # NJA -> ASM
       compiler/njc $file > $tmpFile
       
       # ASM -> BIN
       compiler/nja $tmpFile ${out%.*}
       ((count++))
    else
      # create dir if not exsits
      mkdir -p bin/${file#src/} 
    fi
done

# Remove tmp file
rm $tmpFile
