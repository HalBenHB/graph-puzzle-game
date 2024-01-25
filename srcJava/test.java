import java.io.BufferedReader;
import java.io.FileInputStream;
import java.io.IOException;
import java.io.InputStreamReader;
import java.nio.charset.StandardCharsets;
import java.util.Vector;

import List.Graph.Graph;

public class test {

    static void puzzle1() {
        Vector<String> words3Letters = new Vector<>();
        Vector<String> words4Letters = new Vector<>();
        Vector<String> words5Letters = new Vector<>();
        Vector<String> allWords = new Vector<>();
        int no_3letters = 0, no_4letters = 0, no_5letters = 0, no_allWords = 0;
        System.out.println("Working Directory = " + System.getProperty("user.dir"));
        try {
            String dictionaryPath = "srcJava\\turkish-dictionary.txt";
            String word;
            BufferedReader br = new BufferedReader(new InputStreamReader(
                    new FileInputStream(dictionaryPath), StandardCharsets.UTF_8));
            while ((word = br.readLine()) != null) {
                allWords.add(word);
                no_allWords++;
                if (word.length() == 3) {
                    words3Letters.add(word);
                    no_3letters++;
                    // System.out.println(word.length() + " letter: " + word);
                } else if (word.length() == 4) {
                    words4Letters.add(word);
                    no_4letters++;
                } else if (word.length() == 5) {
                    words5Letters.add(word);
                    no_5letters++;
                }
            }
            br.close();
        } catch (IOException e) {
            e.printStackTrace();
        }

        Graph letter_3s = new Graph(no_3letters);
        Graph letter_4s = new Graph(no_4letters);
        Graph letter_5s = new Graph(no_5letters);

        letter_3s.addFromVector(words3Letters);
        letter_4s.addFromVector(words4Letters);
        letter_5s.addFromVector(words5Letters);

        int testCases = 3;
        String testWords1[] = { "aşk", "mert", "stone" };
        String testWords2[] = { "ask", "baba", "score" };
        Graph testGraphs[] = { letter_3s, letter_4s, letter_5s };

        for (int i = 0; i < testCases; ++i) {
            String testResult, word1, word2;
            word1 = testWords1[i];
            word2 = testWords2[i];
            System.out.println("-------------------------");
            System.out.println(
                    "||Test Case: Adding Edges with One-Letter Difference (" + word1.length() + " letters words)");
            System.out.println("||Shortest Path from '" + word1 + "'' to '" + word2 + "' by BFS:");
            testResult = testGraphs[i].BFSearch(word1, word2);
            System.out.println(testResult);
            // System.out.println("||Shortest Path from '" + word1 + "'' to '" + word2 + "'
            // by Dijkstra:");
            // testResult = testGraphs[i].DijkstraSearch(word1, word2);
            // System.out.println(testResult);
        }

    }

    static void puzzle2() {
        Vector<String> allWords = new Vector<>();
        int no_allWords = 0;
        System.out.println("Working Directory = " + System.getProperty("user.dir"));
        try {
            String dictionaryPath = "srcJava\\words_aplha.txt";
            String word;
            BufferedReader br = new BufferedReader(new InputStreamReader(
                    new FileInputStream(dictionaryPath), StandardCharsets.UTF_8));
            while ((word = br.readLine()) != null) {
                allWords.add(word);
                no_allWords++;
            }
            br.close();
        } catch (IOException e) {
            e.printStackTrace();
        }
        System.out.println("Words are read");

        Graph allWordsGraph = new Graph(no_allWords);

        allWordsGraph.addFromVector(allWords);
        System.out.println("Words are graphed");

        int testCases = 7;
        String testWords1[] = { "mert", "ekşi", "ekşi", "istanbul", "bolu", "çekecek", "kemal" };
        String testWords2[] = { "sen", "inci", "limon", "ankara", "düzce", "asacak", "recep" };

        for (int i = 0; i < testCases; ++i) {
            String testResult, word1, word2;
            word1 = testWords1[i];
            word2 = testWords2[i];
            System.out.println("-------------------------");
            System.out.println(
                    "||Test Case: Adding Edges with One-Letter Difference (" + word1.length() + " letters words)");
            System.out.println("||Shortest Path from '" + word1 + "'' to '" + word2 + "' by BFS:");
            testResult = allWordsGraph.BFSearch(word1, word2);
            System.out.println(testResult);
        }
    }

    public static void main(String[] args) {

        puzzle2();
    }
}