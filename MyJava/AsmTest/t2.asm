Compiled from "t2.java"
public class t2 extends java.lang.Object{
public static java.lang.String[] vals;

public static java.util.ArrayList list;

public t2();
  Code:
   0:	aload_0
   1:	invokespecial	#1; //Method java/lang/Object."<init>":()V
   4:	return

public static void init();
  Code:
   0:	iconst_0
   1:	istore_0
   2:	iload_0
   3:	getstatic	#2; //Field vals:[Ljava/lang/String;
   6:	arraylength
   7:	if_icmpge	28
   10:	getstatic	#3; //Field list:Ljava/util/ArrayList;
   13:	getstatic	#2; //Field vals:[Ljava/lang/String;
   16:	iload_0
   17:	aaload
   18:	invokevirtual	#4; //Method java/util/ArrayList.add:(Ljava/lang/Object;)Z
   21:	pop
   22:	iinc	0, 1
   25:	goto	2
   28:	return

public static void main(java.lang.String[]);
  Code:
   0:	invokestatic	#5; //Method t.init:()V
   3:	getstatic	#3; //Field list:Ljava/util/ArrayList;
   6:	invokevirtual	#6; //Method java/util/ArrayList.iterator:()Ljava/util/Iterator;
   9:	astore_1
   10:	aload_1
   11:	invokeinterface	#7,  1; //InterfaceMethod java/util/Iterator.hasNext:()Z
   16:	ifeq	39
   19:	aload_1
   20:	invokeinterface	#8,  1; //InterfaceMethod java/util/Iterator.next:()Ljava/lang/Object;
   25:	checkcast	#9; //class String
   28:	astore_2
   29:	getstatic	#10; //Field java/lang/System.out:Ljava/io/PrintStream;
   32:	aload_2
   33:	invokevirtual	#11; //Method java/io/PrintStream.println:(Ljava/lang/String;)V
   36:	goto	10
   39:	return

static {};
  Code:
   0:	bipush	7
   2:	anewarray	#9; //class String
   5:	dup
   6:	iconst_0
   7:	ldc	#12; //String This
   9:	aastore
   10:	dup
   11:	iconst_1
   12:	ldc	#13; //String is
   14:	aastore
   15:	dup
   16:	iconst_2
   17:	ldc	#14; //String a
   19:	aastore
   20:	dup
   21:	iconst_3
   22:	ldc	#15; //String test
   24:	aastore
   25:	dup
   26:	iconst_4
   27:	ldc	#16; //String of
   29:	aastore
   30:	dup
   31:	iconst_5
   32:	ldc	#17; //String the
   34:	aastore
   35:	dup
   36:	bipush	6
   38:	ldc	#18; //String compiler
   40:	aastore
   41:	putstatic	#2; //Field vals:[Ljava/lang/String;
   44:	new	#19; //class ArrayList
   47:	dup
   48:	invokespecial	#20; //Method java/util/ArrayList."<init>":()V
   51:	putstatic	#3; //Field list:Ljava/util/ArrayList;
   54:	return

}

