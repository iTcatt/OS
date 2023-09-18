CC = gcc
ZMQ = -lzmq
OBJDIR = obj

.PHONY: all clean

all: build

build: check_folder compute control  

control: $(OBJDIR)/control.o $(OBJDIR)/bst.o
	$(CC) -g $^ $(ZMQ) -o $@

$(OBJDIR)/control.o: cmd/control.c
	$(CC) -c $^ -o $@

$(OBJDIR)/bst.o: topology/bst.c
	$(CC) -c $^ -o $@
	
compute: $(OBJDIR)/map.o $(OBJDIR)/compute.o $(OBJDIR)/list.o
	$(CC) -g $^ $(ZMQ) -o $@

$(OBJDIR)/map.o: storage/map.c
	$(CC) -c $^ -o $@

$(OBJDIR)/list.o: storage/list/list.c
	$(CC) -c $^ -o $@

$(OBJDIR)/compute.o: cmd/compute.c
	$(CC) -c $^ -o $@

check_folder:
	@if [ ! -d $(OBJDIR) ]; then echo "creating $(OBJDIR)"; mkdir $(OBJDIR); fi

list_test: storage/list/list_test.c storage/list/list.c
	$(CC) -g $^ -o storage/$@

map_test: storage/list/list.c storage/map.c storage/map_test.c
	$(CC) -g $^ -o storage/$@

tree_test: topology/bst_test.c topology/bst.c
	$(CC) -g $^ -o topology/$@

test: map_test tree_test list_test

run: clean build
	./control

clean:
	rm -rf compute control $(OBJDIR) storage/map_test storage/list_test
	