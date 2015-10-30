public class Person {
    // Attribut
    public static int numberOfPeople;
    private int age;
    private final String name;
    // Vi ändrade från nedanstående till ovanstående under föreläsningen
//    private String firstName;
//    private String lastName;

    // Konstruktorer som är *överlagrade* (samma namn, olika argument)
    public Person(int age, String name) {
        Person.numberOfPeople++;
        this.age = age;
        this.name = name;
    }

    public Person(int age, String firstName, String lastName) {
        this(age, firstName + " " + lastName);
    }

    public Person(String name, int age) {
        this(age, name);
    }

    // Metoder
    //
    // Alla metoder har ett dolt argument "this" som är refererar
    // till mottagaren av metodanropet ("objektet vi är inne i
    // just nu")
    public String getName(/* Person this */) {
        return this.name; // this.firstName + " " + this.lastName;
    }

    // Överlagring igen. Anropar man getName utan argument körs
    // ovanstående metod. Med ett strängargument körs
    // nedanstående metod istället.
    public String getName(String title) {
        return title + " " + this.name;
    }

    // Om man använder en variabel som inte är definierad men som
    // finns som en av klassens attribut kommer ett implicit
    // "this" sättas in framför.
    public int getAge() {
        return age; // Samma som return this.age;
    }

    // Metoden equals är speciell och används för att avgöra om
    // två objekt är likadana. **OBS!** Metoden equals ska
    // egentligen ta ett argument som har typen Object. Mer om
    // detta när vi pratar om arv.
    public boolean equals(Person other) {
        String otherName = other.getName();
        return this.getName().equals(otherName) &&
               this.getAge() == other.getAge();
    }

    // Metoden toString är också speciell. Om man använder ett
    // objekt som en sträng, till exempel om man försöker printa
    // ett objekt anropas den här metoden implicit:
    //
    //    System.out.println(p) ==> System.out.println(p.toString());
    public String toString() {
        return name + " (" + age + ")";
    }
}