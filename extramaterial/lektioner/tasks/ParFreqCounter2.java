import java.util.*;
import java.io.*;
import java.util.concurrent.ForkJoinPool;
import java.util.concurrent.RecursiveAction;
import java.util.concurrent.ConcurrentHashMap;

public class ParFreqCounter2 {
    public static void main(String[] args) {
        if (args.length < 1) {
            System.out.println("Usage: java ParFreqCounter file1 ... filen"); 
        } else {
            final HashMap<String, Integer> frequences = new HashMap<String, Integer>();

            for (String fileName : args) {
                final File f = new File(fileName);
                ConcurrentHashMap<String, Integer> f_frequences = new ConcurrentHashMap<String, Integer>();
                f.getWordFrequenciesParallel(f_frequences);
                
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

class ArrayTask extends RecursiveAction {
    public static int SEQUENTIAL_CUTOFF = 64 * 1024;
    private String[] words;
    private int start;
    private int stop;
    private ConcurrentHashMap<String, Integer> f_frequences;
    
    ArrayTask(String[] words, int start, int stop, ConcurrentHashMap<String, Integer> f_frequences) {
        this.words = words;
        this.start = start;
        this.stop = stop;
        this.f_frequences = f_frequences;
    }

    private int length() {
        return this.stop - this.start;
    }

    public void compute() {
        if (this.length() < SEQUENTIAL_CUTOFF) {
            for (int i = this.start; i < this.stop; ++i) {
                int newFrequence = this.f_frequences.getOrDefault(this.words[i], 0);
                this.f_frequences.put(this.words[i], newFrequence + 1); 
            }
        } else {
            int middle = this.length() / 2;
            ArrayTask firstHalf = new ArrayTask(this.words, this.start, this.start + middle, this.f_frequences);
            ArrayTask secondHalf = new ArrayTask(this.words, this.start + middle, this.stop, this.f_frequences);

            firstHalf.fork();
            secondHalf.compute();
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

    public void getWordFrequenciesParallel(ConcurrentHashMap<String, Integer> f_frequences) {
        try {
            final String[] words = getWordArray();
            final ForkJoinPool fjPool = new ForkJoinPool();
            Globals.fjPool.invoke(new ArrayTask(words, 0, words.length, f_frequences));
        } catch (Exception e) {
            // TODO: better exception handling
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
