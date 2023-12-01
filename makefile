CC := g++
OBJECTS := TwoLevelBranchPredictor.o HybridBranchPredictor.o AccuracyCalculator.o finalmain.o
EXECUTABLE := MainExecutable

all: $(EXECUTABLE)

$(EXECUTABLE): $(OBJECTS)
	$(CC) $(CFLAGS) $^ -o $@

%.o: %.cpp
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f *.o $(EXECUTABLE)
