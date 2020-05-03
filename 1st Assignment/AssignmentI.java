/*
 *  ASSIGNMENT I : RECURSIVE FUNCTION
 */
package assignmenti;

import java.util.InputMismatchException;
import java.util.Scanner;


public class AssignmentI {
    
    static long calcFactorial(int n){
        
        long ans;
        
        if(n == 0){
            
            System.out.println(n + "! is a base case. Returning 1 as an answer");
            ans = 1;
            return ans;
        }
        else{
            
            System.out.println(n + "! is a recursive case. Returning " + n + " * " + (n - 1) + "!");
            ans = calcFactorial(n - 1);
            System.out.print("Returning " + (n - 1) + "! = " + ans + " to calculate " + n + "!");
            System.out.println(" = [" + n + " * " + (n - 1) + "!] = " + n + " * " + ans + " = " + (n * ans));
            return ans * n;
        }
    }
/*
    //Recursively calculate factorial using TAIL RECURSION
    static long calcFactorialTR(int n, long accumulator){
        
        System.out.println("Current value of accumulator: " + accumulator);
        
        if(n == 0 || n == 1){
            
            System.out.println("Base case reached!");
            return accumulator;
        }
        else{
            
            System.out.println(n + "! is a recursive case. The answer is " + n + " * Recursion of " + (n - 1) + "!");
            return calcFactorialTR(n - 1, n * accumulator);
        }
    }
*/    
    static int getInt(){
                  
        Scanner sc = new Scanner(System.in);
        boolean success = false;
        int input = 0;
        
        while(!success){
            
            try{
                
                success = true;
                System.out.print("Input n: ");
                input = sc.nextInt();
            }
            catch(InputMismatchException e){
                
                System.out.println("Invalid input. Only positive integer 1 - 20 allowed. Please try again");
                sc.nextLine();
                success = !success;
            }
            if(input < 0 || 15 < input){
                
                System.out.println("Invalid input. Only positive integer 1 - 20 allowed. Please try again");
                sc.nextLine();
                success = !success;
            }
        }
        
        return input;
    }

    public static void main(String[] args) {

        long normalAnswer, TRAnswer;
        int input;
        boolean running = true;
        
        Scanner sc = new Scanner(System.in);
        
        while(running){
            
            System.out.println("Ultimate recursion program");
            System.out.println("Written by 62070501051 Phattarapol Lertchaisirikul");
            System.out.println("Program calculate n! using both NORMAL recursive method and TAIL recursive method");
            System.out.println("(n must be 15 or lower)");

            input = getInt();

            System.out.println("\nInitiating normal recursive method...");
            normalAnswer = calcFactorial(input);

    //      System.out.println("\nInitiating tail call optimization...");
    //      TRAnswer = calcFactorialTR(input, 1);

            System.out.println("");
            System.out.println("The answer of " + input + " factorial calculated using ordinary recursion (O(n)) is " + normalAnswer);
    //      System.out.println("The answer of " + input + " factorial calculated using tail recursion (O(1)) is " + TRAnswer);
    
            System.out.println("press [y] to continue, others to exit.");
            
            if(!sc.next().equals("y")){
                
                System.out.println("End program.");
                running = !running;
            }
        }
    }
    
}
