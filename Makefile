SRCS = main.cpp nameconverter.cpp
OBJS = $(subst .cpp,.o,$(SRCS))

CXX ?= g++
CPPFLAGS ?= -I./include
CXXFLAGS ?= -std=c++20
LDFLAGS ?=

DESTDIR ?= /usr/local
DESTDIR_BIN ?= $(DESTDIR)/bin

TARGET = roland-usb

MAKE_OBJ = $(CXX) $(CPPFLAGS) $(CXXFLAGS) -c
MAKE_LINK = $(CXX) $(LDFLAGS) -o $(TARGET)

all : $(TARGET)

$(TARGET) : $(OBJS)
	$(MAKE_LINK) $(OBJS)

main.o : src/main.cpp
	$(MAKE_OBJ) src/main.cpp

nameconverter.o : src/nameconverter.cpp
	$(MAKE_OBJ) src/nameconverter.cpp


.PHONY : clean distclean install uninstall

clean : 
	rm $(OBJS)

distclean : 
	rm $(TARGET)

install : $(TARGET)
	@install -d $(DESTDIR_BIN)
	@install $(TARGET) $(DESTDIR_BIN)
	@echo "$(TARGET) was installed to $(DESTDIR)"

uninstall :
	@if [ -f $(DESTDIR_BIN)/$(TARGET) ]; then rm $(DESTDIR_BIN)/$(TARGET); else echo "ERROR: $(TARGET) not installed at location: \"$(DESTDIR_BIN)\" --> please uninstall manually"; fi
