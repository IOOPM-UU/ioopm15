import java.util.*;
import java.io.*;
import java.util.concurrent.ForkJoinPool;
import java.util.concurrent.RecursiveTask;

public class ParFreqCounter {
    public static void main(String[] args) {
        if (args.length < 1) {
            System.out.println("Usage: java ParFreqCounter file1 ... filen"); 
        } else {
            final HashMap<String, Integer> frequences = new HashMap<String, Integer>();

            for (String fileName : args) {
                final File f = new File(fileName);
                final HashMap<String, Integer> f_frequences = f.getWordFrequenciesParallel();
                
                for (String word : f_frequences.keySet()) {
                    frequences.put(word, f_frequences.get(word) + frequences.getOrDefault(word, 0));
                }
            }

            new Histogram(frequences).print();
        }
    }
}

class Histogram {
    public HashMap<String, Integer> values;

    public Histogram(final HashMap<String, Integer> values) {
        this.values = values;
    }

    public void print() {
        /// We don't actually want to print a histogram because
        /// that will skew performance results. When benchmarking,
        /// you should comment out these lines. For now we don't
        /// actually print a histogram, just dump the frequences.
        for (String word : this.values.keySet()) {
            System.out.printf("%s:\t%d\n", word, this.values.get(word));
        }
    }

}

class ArrayTask extends RecursiveTask<HashMap<String,Integer>> {
    public static int SEQUENTIAL_CUTOFF = 64 * 1024;
    private String[] words;
    private int start;
    private int stop;
    
    ArrayTask(String[] words, int start, int stop) {
        this.words = words;
        this.start = start;
        this.stop = stop;
    }

    private int length() {
        return this.stop - this.start;
    }

    private HashMap<String, Integer> fuse(final HashMap<String, Integer> a, final HashMap<String, Integer> b) {
        // Optimering -- välja den minsta
        for (String word : b.keySet()) {
            a.put(word, b.get(word) + a.getOrDefault(word, 0));
        }
        return a;
    }
    
    public HashMap<String, Integer> compute() {
        if (this.length() < SEQUENTIAL_CUTOFF) {
            final HashMap<String, Integer> frequences = new HashMap<String, Integer>();
            for (int i = this.start; i < this.stop; ++i) {
                int newFrequence = frequences.getOrDefault(this.words[i], 0);
                frequences.put(this.words[i], newFrequence + 1); 
            }
            return frequences;
        } else {
            int middle = this.length() / 2;
            ArrayTask firstHalf = new ArrayTask(this.words, this.start, this.start + middle);
            ArrayTask secondHalf = new ArrayTask(this.words, this.start + middle, this.stop);

            firstHalf.fork();
            HashMap<String, Integer> secondHalfResult = secondHalf.compute();
            HashMap<String, Integer> firstHalfResult = firstHalf.join();

            return fuse(firstHalfResult, secondHalfResult);
        }
    }
}

class File {
    private final String fileName;
    
    public File(final String fileName) {
        this.fileName = fileName;
    }

    /**
     * Create a mapping from words to the number of times the
     * occurred in the file
     */
    public HashMap<String, Integer> getWordFrequencies() {
        final HashMap<String, Integer> frequences = new HashMap<String, Integer>();

        try {
            for (String s : this.getWordArray()) {
                int newFrequence = frequences.getOrDefault(s, 0);
                frequences.put(s, newFrequence + 1); 
            }
        } catch (Exception e) {
            // TODO: better exception handling
        }

        return frequences;
    }

    public HashMap<String, Integer> getWordFrequenciesParallel() {
        try {
            final String[] words = getWordArray();
            final ForkJoinPool fjPool = new ForkJoinPool();
            return Globals.fjPool.invoke(new ArrayTask(words,0,words.length));
        } catch (Exception e) {
            // TODO: better exception handling
            return null;
        }
    }
    
    private String[] getWordArray() throws IOException, FileNotFoundException {
        final List<String> words = new LinkedList<String>();
        final BufferedReader data = new BufferedReader(new FileReader(fileName));
        
        for (String line = data.readLine(); line != null; line = data.readLine()) {
            for (String word : line.split("[ .:,!?]+")) { /// Avoid .,!? etc. in files
                if (word.length() > 0) words.add(word);
            }
        }

        return words.toArray(new String[]{});
    }

}
