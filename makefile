main:Source.cpp PortScanTool.cpp
	g++ Source.cpp PortScanTool.cpp -o main
.PHONY:clean
clean:
	rm -rf main