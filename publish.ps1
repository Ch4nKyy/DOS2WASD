
if (!$args) { throw "Provide version number as argument!" }
$version_number = $args[0]
if (-Not ($version_number -match '^\d\.\d\.\d$')) { throw "Version number must be of format x.y.z" }
$version_line = "    VERSION $version_number"
$file = "$PSScriptRoot\CMakeLists.txt"
$regex = '^\s*VERSION\s+\d\.\d\.\d$'
(Get-Content $file) -replace $regex, $version_line | Set-Content $file

Remove-Item $PSScriptRoot/build -Recurse -Force -ErrorAction:SilentlyContinue -Confirm:$False | Out-Null
& cmake -B $PSScriptRoot/build -S $PSScriptRoot --preset=REL -DPLUGIN_MODE:BOOL=TRUE
& cmake --build $PSScriptRoot/build --config Release

Remove-Item $PSScriptRoot\package\DefEd -Force -Recurse -ErrorAction:SilentlyContinue | Out-Null
Remove-Item $PSScriptRoot\package\*.zip -Force -Recurse -ErrorAction:SilentlyContinue | Out-Null
New-Item -ItemType Directory -Path $PSScriptRoot\package\DefEd\bin\NativeMods | Out-Null
Copy-Item $PSScriptRoot\extern\SDL2\SDL2*.dll $PSScriptRoot\package\DefEd\bin\
Copy-Item $PSScriptRoot\extern\NativeModLoader\*.dll $PSScriptRoot\package\DefEd\bin\
Copy-Item $PSScriptRoot\build\Release\* $PSScriptRoot\package\DefEd\bin\NativeMods\
Copy-Item $PSScriptRoot\package\*.toml $PSScriptRoot\package\DefEd\bin\NativeMods\
& "C:\Program Files\7-Zip\7z.exe" a -tzip $PSScriptRoot\package\DOS2WASD.zip $PSScriptRoot\package\DefEd
Remove-Item $PSScriptRoot\package\DefEd -Force -Recurse  -ErrorAction:SilentlyContinue | Out-Null
