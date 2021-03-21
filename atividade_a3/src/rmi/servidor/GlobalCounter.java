package rmi.servidor;

import rmi.common.RemoteCounter;

import java.rmi.*;
import java.rmi.server.UnicastRemoteObject;

public class GlobalCounter extends UnicastRemoteObject implements RemoteCounter {
    private Integer counter;

    public GlobalCounter() throws RemoteException {
        counter = 1;
    }

    @Override
    public synchronized Integer getCounter() throws RemoteException {
        try {
	        return this.counter;
        } finally {
        	this.counter++;
        }
    }
}
