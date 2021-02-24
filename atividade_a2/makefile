SRC_DIR = src
RESOURCES_DIR = resources
TMP_DIR = $(RESOURCES_DIR)/tmp
OBJECT_DIR = $(RESOURCES_DIR)/object_files

SERVER_PID_FILE = $(TMP_DIR)/servidor.pid

CLIENT_IMPL = $(SRC_DIR)/cliente.c
CLIENTE_OBJECT = $(OBJECT_DIR)cliente.o
CLIENTE_EXE = cliente

MULTI_CLIENTE_IMPL = $(SRC_DIR)/multi_cliente.c
MULTI_CLIENTE_OBJECT = $(OBJECT_DIR)multi_cliente.o
MULTI_CLIENTE_EXE = multi_cliente

SERVER_IMPL = $(SRC_DIR)/servidor.c
SERVER_OBJECT = $(OBJECT_DIR)/servidor.o
SERVER_EXE = servidor

# Cria o diretório dos arquivos, o git não permite commitar diretórios vazios.
build_resources_dir := $(shell mkdir -p $(RESOURCES_DIR))
build_tmp_dir := $(shell mkdir -p $(TMP_DIR))
build_object_dir := $(shell mkdir -p $(OBJECT_DIR))

all: $(CLIENTE_EXE) $(SERVER_EXE) $(MULTI_CLIENTE_EXE)
	@# Inicializar servidor 1
	@./$(SERVER_EXE) & echo $$! > $(SERVER_PID_FILE) ;
	@# Inicializar cliente 1
	@./$(MULTI_CLIENTE_EXE) 1+2 2+3 4+5
	@# Matar servidor 1
	@echo "finalizando server 1"
	@cat $(SERVER_PID_FILE) | xargs kill

$(MULTI_CLIENTE_EXE) : $(CLIENTE_EXE) $(MULTI_CLIENTE_OBJECT)
	gcc -g3 $(MULTI_CLIENTE_OBJECT) -o $(MULTI_CLIENTE_EXE) -fopenmp 

$(CLIENTE_EXE): $(CLIENTE_OBJECT)
	gcc -g3 $(CLIENTE_OBJECT) -o $(CLIENTE_EXE) -fopenmp 

$(SERVER_EXE): $(SERVER_OBJECT)
	gcc -g3 $(SERVER_OBJECT) -o $(SERVER_EXE) -fopenmp 

$(MULTI_CLIENTE_OBJECT): $(MULTI_CLIENTE_IMPL)
	gcc -g3 -c $(MULTI_CLIENTE_IMPL) -fopenmp -o $(MULTI_CLIENTE_OBJECT)

$(CLIENTE_OBJECT): $(CLIENT_IMPL)
	gcc -g3 -c $(CLIENT_IMPL) -fopenmp -o $(CLIENTE_OBJECT)

$(SERVER_OBJECT): $(SERVER_IMPL)
	gcc -g3 -c $(SERVER_IMPL) -fopenmp -o $(SERVER_OBJECT)