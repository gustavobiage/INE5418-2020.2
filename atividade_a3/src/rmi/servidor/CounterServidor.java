package rmi.servidor;

import java.rmi.Naming;

public class CounterServidor {
	
    private static final String LOCAL_HOST = "localhost";
    public static final String SERVER_NAME = "rmi://" + LOCAL_HOST + "/" + CounterServidor.class.getCanonicalName();

    public static void main(String[] argv) {
        try {
            System.out.println(SERVER_NAME);
            Naming.rebind(SERVER_NAME, new GlobalCounter());
        } catch (Exception e) {
            System.out.println("GlobalCounter exception: " + e);
        }
    }
}
