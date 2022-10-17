# Coin_Catcher

## Files to Download

Download "Opengl_Homework1" 

Download [glew](https://glew.sourceforge.net/) , unzip the 32-bits version file

Download [glfw](https://www.glfw.org/download.html) , use windows 32-bits binaries version , unzip 

Download [glm-0.9.8](https://glm.g-truc.net/0.9.8/index.html), unzip

## Visual studio include 

Right click "專案" -> Choose "屬性" -> "C/C++" -> 一般 -> 其他 Include目錄 -> 編輯 

-> Add "[FilePath]\glm\glm", "[FilePath]\glfw-3.3.8.bin.WIN32\include", "[FilePath]\glew-2.1.0\include"

-> Go to "連結器" -> "一般" -> "其他程式庫目錄" -> 編輯 -> Add "[FilePath]\glew-2.1.0\lib\Release\Win32", "[FilePath]\glfw-3.3.8.bin.WIN32\lib-vc2022"

-> Go to "連結器" -> "輸入" ->  "其他相依性" -> 編輯 -> Add "opengl32.lib", "glew32s.lib", "glfw3.lib"

F5 
