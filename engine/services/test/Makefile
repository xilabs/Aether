
INC := -I../websocketpp/

all: websockets_metrics_client.cpp
	$(CXX) websockets_metrics_client.cpp -o websockets_metrics_client -Wall $(INC) -L/usr/local/lib  -lboost_thread -lboost_system -lboost_random -levent

clean:
	$(RM) websockets_metrics_client

