all: program directories

program:
	g++ ./src/DeviceReader.cc -o ./bin/DeviceReader

directories:
	@mkdir -p ./bin