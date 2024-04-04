all: directories program

directories:
	@mkdir -p ./bin

program:
	g++ ./src/DeviceReader.cc -o ./bin/DeviceReader

.PHONY: clean
clean:
	rm -rf ./bin