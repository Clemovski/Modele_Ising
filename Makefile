EXEC = Ising
SRCS =  Imprimante.cpp Solide.cpp Solide1D.cpp Solide2D.cpp Solide3D.cpp main.cpp
CXXFLAGS = -Wall

# Ne rien changer a partir d'ici

DEPEND_FILE = .depend
OBJS = $(SRCS:%.cpp=%.o)

all: $(DEPEND_FILE) $(EXEC)

$(EXEC): $(OBJS)
	g++ $(OBJS) -o $(EXEC)

clean:
	$(RM) *~ *.o $(EXEC) \#* 

cleanall: clean
	$(RM) $(EXEC) $(DEPEND_FILE)

cleaner: cleanall

$(DEPEND_FILE): $(SRCS)
	g++ -MM $(SRCS) > $(DEPEND_FILE)

-include $(DEPEND_FILE)
