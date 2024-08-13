cc = g++
ver = c++20

full : main.cpp
	$(cc) --std=$(ver) main.cpp -o prayers-full
polybar : polybar_module.cpp
	$(cc) --std=$(ver) polybar_module.cpp -o prayers

