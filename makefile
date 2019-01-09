CXXFLAGS := -std=c++1z

.SILENT:
all: typing

clean:
	$(RM) typing

install: typing
	install -s typing /usr/local/bin
