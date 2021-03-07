SRC_DIR = src
RESOURCES_DIR = resources
TMP_DIR = $(RESOURCES_DIR)/tmp
OBJECT_DIR = $(RESOURCES_DIR)/object_files

SERVER_PID_FILE = $(TMP_DIR)/servidor.pid

CONCURRENT_QUEUE_IMPL = $(SRC_DIR)/concurrent_queue.c
CONCURRENT_QUEUE_OBJECT = $(OBJECT_DIR)/concurrent_queue.o

CALCULADORA_IMPL = $(SRC_DIR)/calculadora.c
CALCULADORA_OBJECT = $(OBJECT_DIR)/calculadora.o
CALCULADORA_EXE = calculadora

CLIENT_IMPL = $(SRC_DIR)/cliente.c
CLIENTE_OBJECT = $(OBJECT_DIR)/cliente.o
CLIENTE_EXE = cliente

MULTI_CLIENTE_IMPL = $(SRC_DIR)/multi_cliente.c
MULTI_CLIENTE_OBJECT = $(OBJECT_DIR)/multi_cliente.o
MULTI_CLIENTE_EXE = multi_cliente

SERVER_IMPL = $(SRC_DIR)/servidor.c
SERVER_OBJECT = $(OBJECT_DIR)/servidor.o
SERVER_EXE = servidor

# Cria o diretório dos arquivos, o git não permite commitar diretórios vazios.
build_resources_dir := $(shell mkdir -p $(RESOURCES_DIR))
build_tmp_dir := $(shell mkdir -p $(TMP_DIR))
build_object_dir := $(shell mkdir -p $(OBJECT_DIR))

build:$(MULTI_CLIENTE_EXE) $(CLIENTE_EXE) $(SERVER_EXE) $(CALCULADORA_EXE)
	@echo "construído com sucesso"

testar: $(CLIENTE_EXE) $(SERVER_EXE) $(MULTI_CLIENTE_EXE)
	@# Inicializar servidor 1
	@./$(SERVER_EXE) & echo $$! > $(SERVER_PID_FILE) ;
	@# Inicializar cliente 1, 2, 3
	@./$(MULTI_CLIENTE_EXE) 1+2*3+4 2+3-9/2 4+5-5+4*1
	@# Matar servidor 1
	@echo "finalizando servidor"
	@cat $(SERVER_PID_FILE) | xargs kill

$(MULTI_CLIENTE_EXE) : $(CLIENTE_EXE) $(MULTI_CLIENTE_OBJECT)
	gcc -g3 $(MULTI_CLIENTE_OBJECT) -o $(MULTI_CLIENTE_EXE) -fopenmp 

$(CLIENTE_EXE): $(CLIENTE_OBJECT)
	gcc -g3 $(CLIENTE_OBJECT) -o $(CLIENTE_EXE) -fopenmp 

$(SERVER_EXE): $(SERVER_OBJECT) $(CONCURRENT_QUEUE_OBJECT)
	gcc -g3 $(SERVER_OBJECT) $(CONCURRENT_QUEUE_OBJECT) -o $(SERVER_EXE) -fopenmp 

$(CALCULADORA_EXE) : $(CALCULADORA_OBJECT)
	gcc -g3 $(CALCULADORA_OBJECT) -o $(CALCULADORA_EXE) -fopenmp

$(MULTI_CLIENTE_OBJECT): $(MULTI_CLIENTE_IMPL)
	gcc -g3 -c $(MULTI_CLIENTE_IMPL) -fopenmp -o $(MULTI_CLIENTE_OBJECT)

$(CLIENTE_OBJECT): $(CLIENT_IMPL)
	gcc -g3 -c $(CLIENT_IMPL) -fopenmp -o $(CLIENTE_OBJECT)

$(SERVER_OBJECT): $(SERVER_IMPL)
	gcc -g3 -c $(SERVER_IMPL) -fopenmp -o $(SERVER_OBJECT)

$(CONCURRENT_QUEUE_OBJECT): $(CONCURRENT_QUEUE_IMPL)
	gcc -g3 -c $(CONCURRENT_QUEUE_IMPL) -fopenmp -o $(CONCURRENT_QUEUE_OBJECT)

$(CALCULADORA_OBJECT) : $(CALCULADORA_IMPL)
	gcc -g3 -c $(CALCULADORA_IMPL) -fopenmp -o $(CALCULADORA_OBJECT)

clean:
	rm -f $(OBJECT_DIR)/*.o
	rm -f $(TMP_DIR)/*.pid
	rm -f $(SERVER_EXE)
	rm -f $(CLIENTE_EXE)
	rm -f $(MULTI_CLIENTE_EXE)
	rm -f $(CALCULADORA_EXE)
	rm -d -r $(RESOURCES_DIR)