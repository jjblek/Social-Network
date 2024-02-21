COMPILER=g++
FLAGS=-std=c++17
COMPILE=$(COMPILER) $(FLAGS)
RM=rm -f

EXE=SocialNetwork.x

OBJS=main.o SocialNetwork.o User.o
OBJS+=JSONParser.o JSONTokenizer.o
OBJS+=JSONEntitySet.o JSONEntity.o JSONObject.o JSONPair.o

$(EXE): $(OBJS)
	$(COMPILER) -o $@ $(OBJS)

.cpp.o:
	$(COMPILE) -c $<

clean:
	@echo "Cleaning...";
	$(RM) *.o $(EXE)
