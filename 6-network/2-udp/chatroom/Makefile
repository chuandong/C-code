SER_DIR:=server
CLT_DIR:=client
COMM_DIR:=comm
SERVER:=server
CLIENT:=client
INSTALL_DIR:=./install

export SERVER CLIENT
.PHONY:all clean

all:
	-make -C $(SER_DIR)
	-make -C $(CLT_DIR)
	-mkdir $(INSTALL_DIR) -p
	-cp ./$(SER_DIR)/$(SERVER) $(INSTALL_DIR)
	-cp ./$(CLT_DIR)/$(CLIENT) $(INSTALL_DIR)

clean:
	-cd ./$(SER_DIR) && $(MAKE) clean
	-cd ./$(CLT_DIR) && $(MAKE) clean
	-rm $(INSTALL_DIR) -rf

