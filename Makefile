#!/usr/bin/make

all: compile upload clean

compile: ## Compile the sketch
	arduino-cli compile --warnings all --output-dir .build .

upload: ## Upload compiled sketch
	arduino-cli upload --input-dir .build --verify --verbose .

clean: ## Make clean
	rm -R .build
