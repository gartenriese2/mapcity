#!/bin/bash

PROJ_FILE=./.mapcity.files

find ./src -type f \( -iname \*.cpp -o -iname \*.hpp \) > "${PROJ_FILE}.tmp"
diff "${PROJ_FILE}" "${PROJ_FILE}.tmp" &> /dev/null
if [ $? -ne 0 ]; then
    make clean
fi

mv "${PROJ_FILE}.tmp" "${PROJ_FILE}"

make && ./bin/mapcity
