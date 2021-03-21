**Aluno:** Gustavo de Castro Biage (18200424)  
**Disciplina:** Computação Distribuída  
**Semestre:** 20202

> Refererência: [Opção de socket SO_REUSEPORT](https://lwn.net/Articles/542629/)

## Instruções de execução

```bash
make build
```

```bash
rmiregistry -J-Djava.class.path=out
```

```bash
java -cp out/ rmi.servidor.CounterServidor
java -cp out/ -Djava.security.policy=resouces/server.policy \
rmi.servidor.CounterServidor
```

```bash
java -cp out/ -Djava.security.policy=resouces/server.policy \
rmi.cliente.CounterCliente
```

```
java -cp out/ -Djava.security.policy=resouces/server.policy \
rmi.cliente.StressTest
```