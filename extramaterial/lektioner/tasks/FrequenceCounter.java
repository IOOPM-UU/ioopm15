import java.util.*;
import java.io.*;

public class FrequenceCounter {
    public static void main(String[] args) {
        if (args.length < 1) {
            System.out.println("Usage: java FrequenceCounter file1 ... filen"); 
        } else {
            final HashMap<String, Integer> frequences = new HashMap<String, Integer>();

            for (String fileName : args) {
                final File f = new File(fileName);
                final HashMap<String, Integer> f_frequences = f.getWordFrequencies();
                
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
