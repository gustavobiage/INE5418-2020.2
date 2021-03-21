**Aluno:** Gustavo de Castro Biage (18200424)  
**Disciplina:** Computação Distribuída  
**Semestre:** 20202

## Instruções de execução

**Passo 1:** Compilação das implementações em java com uso de `makefile`.

```bash
foo@bar:~/.../atividade_a3$ make build
```

**Passo 2:** Execução do `rmiregistry` definindo o diretório de armazenamento dos arquivos `.class`.

```bash
foo@bar:~/.../atividade_a3$ rmiregistry -J-Djava.class.path=out
```

**Passo 2:** Execução do servidor, junto com a definição do diretório de armazenamento dos arquivos `.class` e as configurações do servidor em relação à políticas de segurança e permissões.

```bash
foo@bar:~/.../atividade_a3$ java -cp out/ -Djava.security.policy=resouces/server.policy \
rmi.servidor.CounterServidor
```

**Passo 3:** Execução do cliente, junto com a definição do diretório de armazenamento dos arquivos `.class` e as configurações do servidor em relação à políticas de segurança e permissões.

```bash
foo@bar:~/.../atividade_a3$ java -cp out/ -Djava.security.policy=resouces/server.policy \
rmi.cliente.CounterCliente
```

**(Variação) Passo 3:** Execução de vários clientes que realizam múltiplas requisições, assim, também define-se o diretório de armazenamento dos arquivos de `.class` e as configurações do servidor em relação à políticas de segurança e permissões.

```bash
foo@bar:~/.../atividade_a3$ java -cp out/ -Djava.security.policy=resouces/server.policy \
rmi.cliente.StressTest
```