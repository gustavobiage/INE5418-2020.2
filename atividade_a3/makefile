SRC_DIR = src
CLASS_DIR = out
RESOURCE_DIR = resources
RMI_PACKAGE = $(SRC_DIR)/rmi
SERVIDOR_PACKAGE = $(RMI_PACKAGE)/servidor
COMMON_PACKAGE = $(RMI_PACKAGE)/common
CLIENTE_PACKAGE = $(RMI_PACKAGE)/cliente

SERVIDOR_IMPL = $(SERVIDOR_PACKAGE)/CounterServidor.java
GLOBAL_COUNTER_IMPL = $(SERVIDOR_PACKAGE)/GlobalCounter.java
REMOTE_COUNTER_INTERFACE = $(COMMON_PACKAGE)/RemoteCounter.java
CLIENTE_IMPL = $(CLIENTE_PACKAGE)/CounterCliente.java
STRESS_TEST_IMPL = $(CLIENTE_PACKAGE)/StressTest.java

# Cria o diretório dos arquivos, o git não permite commitar diretórios vazios.
build_resources_dir := $(shell mkdir -p $(RESOURCE_DIR))
build_class_dir := $(shell mkdir -p $(CLASS_DIR))

build: $(SERVIDOR_IMPL) $(GLOBAL_COUNTER_IMPL) $(REMOTE_COUNTER_INTERFACE) $(CLIENTE_IMPL)
	@javac \
	$(SERVIDOR_IMPL) \
	$(GLOBAL_COUNTER_IMPL) \
	$(REMOTE_COUNTER_INTERFACE) \
	$(CLIENTE_IMPL) \
	$(STRESS_TEST_IMPL) \
	-d $(CLASS_DIR)
	@echo "Construído com sucesso!"

clean:
	rm -f -d -r $(CLASS_DIR)/*
