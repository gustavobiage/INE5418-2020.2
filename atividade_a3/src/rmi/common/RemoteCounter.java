package rmi.common;

import java.rmi.*;

public interface RemoteCounter extends Remote {

    public Integer getCounter() throws RemoteException;
}
