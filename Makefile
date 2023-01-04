dependency:
	cd build && cmake .. --graphviz=graph.dot && dot -Tpng graph.dot -o graphimage.png

prepare:
	rm -r build
	mkdir build
	cd build && conan install .. && cd ..
