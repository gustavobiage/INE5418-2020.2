package rmi.cliente;

import rmi.common.RemoteCounter;
import rmi.servidor.CounterServidor;

import java.rmi.Naming;

public class CounterCliente {
    public static void main(String[] argv) {
        RemoteCounter counter;
        try {
            counter = (RemoteCounter) Naming.lookup(CounterServidor.SERVER_NAME);
            System.out.println("Eu recebi o contador: " + counter.getCounter());
        } catch (Exception e) {
            System.out.println("GlobalCounter exception: " + e);
        }
        System.out.println("Cliente completo.");
    }
}
