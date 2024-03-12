# shellcheck shell=sh

export ASMCDIR="/usr/lib/asmc"
if [ -z "$INCLUDE" ]; then
    export INCLUDE="/usr/lib/asmc/include"
else
    export INCLUDE="${INCLUDE}:/usr/lib/asmc/include"
fi
if [ -z "$LIBRARY_PATH" ]; then
    export LIBRARY_PATH="/usr/lib/asmc"
else
    export LIBRARY_PATH="${LIBRARY_PATH}:/usr/lib/asmc"
fi
