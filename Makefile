INC_DIR:=./include
SRC_DIR:=./src
LOG_DIR:=./log
SRCS:=$(wildcard $(SRC_DIR)/*.cc)
OBJS:=$(patsubst %.cc, %.o, $(SRCS))
LIBS:=-llog4cpp -lpthread
LOGS:=$(wildcard $(LOG_DIR)/*.log)

CXX:=g++

CXXFLAGS:=-w -g -std=c++11 $(addprefix -I, $(INC_DIR)) $(LIBS) -Wno-deprecated

EXE:=./bin/main.exe

$(EXE):$(OBJS)
	$(CXX) -o $(EXE) $(OBJS) $(CXXFLAGS)

clean:
	rm -rf $(EXE)
	rm -rf $(OBJS)
	rm -rf $(LOGS)
