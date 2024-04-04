all: directories program

directories:
	@mkdir -p ./bin

program:
	g++ ./src/DeviceReader.cc -o ./bin/DeviceReader