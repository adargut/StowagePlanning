#!/bin/env tcsh
echo "Initializing system variables"
if (! $?LD_LIBRARY_PATH) then       
  setenv LD_LIBRARY_PATH "/usr/local/lib/gcc-8.3.0/lib64/:/usr/local/lib/gcc-8.3.0/lib32/"
else
  setenv LD_LIBRARY_PATH "${LD_LIBRARY_PATH}:/usr/local/lib/gcc-8.3.0/lib64/:/usr/local/lib/gcc-8.3.0/lib32/"
endif

echo "Done!"
