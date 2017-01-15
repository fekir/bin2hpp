import java.nio.charset.StandardCharsets;

public class Main {

	public final static String hello = "Hello World!\n\n";

	public static void test1() throws Exception {
		if(res1.helloworld_txt.length != 14){
			throw new RuntimeException("size is wrong");
		}

	    final String str = new String(res1.helloworld_txt, StandardCharsets.UTF_8);

		if(!hello.equals(str)){
			throw new RuntimeException("Strings are not equals");
		}
	}

    public static void main() throws Exception {
		test1();
		System.out.println("All test passed");
	}


}

