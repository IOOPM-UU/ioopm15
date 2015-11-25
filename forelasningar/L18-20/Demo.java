class Post {
    Metadata[] metadata;
    String msg;

    Post(final String msg, final Metadata[] metadata) {
        this.msg = msg;
        this.metadata = metadata;
    }
    
    String render() {
        String html = this.msg;
        for(Metadata m : this.metadata) {
            html = m.render(html);
        }
        return html;
    }
}

abstract class Metadata {
    abstract String render(final String html);
}

class Seen extends Metadata {
    final String username;
    final String time;

    Seen(final String username, final String time) {
        this.username = username;
        this.time = time;
    }
    
    String render(final String html) {
        return
            html +
            "\n\tSeen by: " +
            this.username +
            " at " +
            this.time;
    }
}

class Like extends Metadata {
    final String username;

    Like(final String username) {
        this.username = username;
    }
    
    String render(final String html) {
        return
            html +
            "\n\t" +
            this.username +
            " likes this"; 
    }
}

public class Demo {
    public static void main(String[] args) {
        Seen seen1 = new Seen("Tobias", "just now");
        Seen seen2 = new Seen("Elias", "yesterday");
        Like like1 = new Like("Tobias");
        Like like2 = new Like("Stephan");

        Metadata[] m = new Metadata[] { seen1, like2, like1, seen2 };
        
        Post post = new Post("grymt fett med parra!", m);

        System.out.println(post.render());
    }
}
