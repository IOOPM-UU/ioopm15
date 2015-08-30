/**
 * @author Tobias Wrigstad (tobias.wrigstad@it.uu.se)
 * @date 2013-10-04
 */
public class ListDriver {
    public static void main(String[] args) {
	List l = new List();
	String a = "Hej"; 
	String b = "Hopp"; 
	System.out.println("Listan: " + l.toString()); 
	l.prepend(a);
	l.prepend(b);
	System.out.println("Listan: " + l.toString()); 
	System.out.println("Does list contain " + a + "? ... " + l.contains(a)); 
    }
}
