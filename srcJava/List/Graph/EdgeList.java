package List.Graph;

public class EdgeList {

    private Edge head, tail;
    private String word;

    public EdgeList() {
        head = null;
        tail = null;
        word = "";

    };

    public Boolean isEmpty() {
        return head == null;
    }

    public Edge search(int to) {
        Edge tmp = head;
        while (tmp != null) {
            if (to == tmp.getTo()) {
                return tmp;
            }
            tmp = tmp.getNext();
        }
        return null;
    }

    public void insert(Edge edge) {
        if (head == null) {
            head = edge;
        } else {
            tail.setNext(edge);
        }
        tail = edge;

    }

    public Edge getHead() {
        return head;
    }

    public Edge getTail() {
        return tail;
    }

    public String getWord() {
        return word;
    }

    public void setWord(String word) {
        this.word = word;
    }

}