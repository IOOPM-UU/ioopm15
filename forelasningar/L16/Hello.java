public class Hello {
    static public void main(String args[]) {
        // Instantiera ett nytt objekt (en person). Konstruktorn
        // anropas direkt.
        Person p1 = new Person(28, "Elias", "Castegren");

        System.out.println("Hello, world!");
        String name = p1.getName(); // "Ursakta, objektet. Kan jag fa ditt namn tack?"
        System.out.println("Also, hello " + name + "!");
        int age = p1.getAge();
        System.out.println("You are looking good (for a " +
                           age + " year old)");

        Person p2 = new Person(20, "Haubir Mariwani");
        System.out.println("Hi " + p2.getName("Sir"));

        Person p3 = new Person("Tobias Wrigstad", 22);
        System.out.println(p3); // System.out.println(p3.toString());

        Person p4 = new Person(28, "Elias", "Castegren");

        if(p1 == p4) { // Kollar identitet
            System.out.println("They are the same object");
        } else if(p1.equals(p4)) { // Kollar ekvivalens
            System.out.println("They are equivalent");
        } else {
            System.out.println("They aren't even similar!");
        }

        if(p1 == p3) { // Kollar identitet
            System.out.println("They are the same object");
        } else if(p1.equals(p3)) { // Kollar ekvivalens
            System.out.println("They are equivalent");
        } else {
            System.out.println("They aren't even similar!");
        }

        Person p5 = p1;

        if(p1 == p5) { // Kollar identitet
            System.out.println("They are the same object");
        } else if(p1.equals(p5)) { // Kollar ekvivalens
            System.out.println("They are equivalent");
        } else {
            System.out.println("They aren't even similar!");
        }

        System.out.println("We have created " + Person.numberOfPeople + " people");
    }
}
