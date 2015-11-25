import java.lang.reflect.*;

public class ReflectionDemo {
    public static void main(String[] args) throws Exception {
        if (args.length != 3) {
            System.out.println("Usage: java ReflectionDemo ClassName MethodName string");
            return;
        }
        
        Class c = Class.forName(args[0]);
        Object o = c.newInstance();
        Method m = c.getMethod(args[1], new Class[] {String.class});
        m.invoke(o, args[2]);
    }
}

class Hello {
    public void greet(String s) {
        System.out.println("Hello, " + s + "!");
    }
}
