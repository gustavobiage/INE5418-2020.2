package rmi.cliente;

import rmi.common.RemoteCounter;
import rmi.servidor.CounterServidor;

import java.rmi.Naming;
import java.util.*;
import java.util.concurrent.*;

public class StressTest {

    public static void main(String[] argv) {
        int threadCnt, testLength;
        if (argv.length == 3) {
            threadCnt = Integer.parseInt(argv[1]);
            testLength = Integer.parseInt(argv[2]);
        } else {
            threadCnt = 15;
            testLength = 100000;
        }
        ThreadPoolExecutor threadPoolExecutor = new ThreadPoolExecutor(
                threadCnt,
                threadCnt,
                1,
                TimeUnit.HOURS,
                new ArrayBlockingQueue<Runnable>(threadCnt));
        final Set<Integer> integerSet = new HashSet<>();
        RemoteCounter counter;

        try {
            counter = (RemoteCounter) Naming.lookup(CounterServidor.SERVER_NAME);
            List<Future<Boolean>> results = new ArrayList<>();

            System.out.println("Isso deve demorar alguns segundos.");

            for (int i = 0; i < threadCnt; i++) {
                Future<Boolean> future = threadPoolExecutor.submit(new CallServer(integerSet, counter, testLength));
                results.add(future);
            }

            boolean passed = true;
            for (Future<Boolean> result : results) {
                Boolean value = result.get();
                passed = passed && value;
            }

            Integer max = -1;
            Integer min = Integer.MAX_VALUE;
            Integer expectedValue = threadCnt * testLength;
            for (Integer i : integerSet) {
                if (i > max) {
                    max = i;
                }
                if (i < min) {
                    min = i;
                }
            }
            Integer diference = max - min + 1;
            // O contador pode estar sendo incrementado mais de uma vez (implementação 1 ou +)?
            // Pode ocorre falhas na comunicação utilizando localhost?
            passed = passed && diference.equals(expectedValue);

            if (passed) {
                System.out.println("Concorrência está funcionando!");
            } else {
                System.out.println("Talvez exista um problema de concorrência (" + (diference - expectedValue) + ")");
            }
        } catch (Exception e) {
            System.out.println("StressTest exception: " + e);
        }
        threadPoolExecutor.shutdown();
        System.out.println("Teste completo.");
    }

    private static class CallServer implements Callable<Boolean> {
        private final Set<Integer> encounteredValues;
        private RemoteCounter remoteCounter;
        private int length;

        public CallServer(final Set<Integer> encounteredValues, RemoteCounter remoteCounter, int length) {
            this.encounteredValues = encounteredValues;
            this.remoteCounter = remoteCounter;
            this.length = length;
        }

        @Override
        public Boolean call() throws Exception {
            List<Integer> values = new ArrayList<>();
            for (int i = 0; i < length; i++) {
                Integer value = this.remoteCounter.getCounter();
                values.add(value);
            }

            for (Integer value : values) {
                synchronized (encounteredValues) {
                    if (encounteredValues.contains(value)) {
                        return false;
                    }
                    encounteredValues.add(value);
                }
            }
            return true;
        }
    }
}
