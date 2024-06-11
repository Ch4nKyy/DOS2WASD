Remove-Item $PSScriptRoot/build -Recurse -Force -ErrorAction:SilentlyContinue -Confirm:$False | Out-Null
& cmake -B $PSScriptRoot/build -S $PSScriptRoot/DOS2WASD --preset=REL -DPLUGIN_MODE:BOOL=TRUE
& cmake --build $PSScriptRoot/build --config Release