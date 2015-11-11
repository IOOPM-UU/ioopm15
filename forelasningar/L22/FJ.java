import java.util.concurrent.ForkJoinPool;
import java.util.concurrent.RecursiveTask;

public class FJ {
    public static void main(String[] args) {
        System.out.println(Sum.sumArray(new int[] { 1, 234, 43, 345, 2, 445, 56456, 546, 345435, 234, 1 }));
    }
}

class Globals {
    static ForkJoinPool fjPool = new ForkJoinPool();
}

class Sum extends RecursiveTask<Long> {
    static final int SEQUENTIAL_THRESHOLD = 1; // No cut-off!
    int low;
    int high;
    int[] array;

    Sum(int[] arr, int lo, int hi) {
        array = arr;
        low   = lo;
        high  = hi;
    }

    protected Long compute() {
        if(high - low <= SEQUENTIAL_THRESHOLD) {
            long sum = 0;
            for(int i=low; i < high; ++i)
                sum += array[i];
            return sum;
        } else {
            int mid = low + (high - low) / 2;
            Sum left  = new Sum(array, low, mid);
            Sum right = new Sum(array, mid, high);
            left.fork();
            long rightAns = right.compute();
            long leftAns  = left.join();
            return leftAns + rightAns;
        }
    }

    static long sumArray(int[] array) {
        return Globals.fjPool.invoke(new Sum(array,0,array.length));
    }
}
