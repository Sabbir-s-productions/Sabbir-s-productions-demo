#include<stdio.h>

int main() {
        int grade;
        printf("Enter your marks : ");
        scanf("%d", &grade);

        switch (grade)
        {
            case 100 : printf("Platinum A+ \n");
                 break;
            case 95 ... 99 : printf("Golden A+ \n");
                 break;
             case 90 ... 94 : printf("Silver A+ \n");
                 break;
            case 80 ... 89 : printf("A+ \n");
                   break;
            case 70 ... 79 : printf("A \n");
                   break;   
            case 60 ... 69 : printf("A- \n");
                   break;
             case 50 ... 59 : printf("B \n");
                     break;
            case 40 ... 49  : printf("C \n");
                     break;
                case 33 ... 39 : printf("D \n");
                     break;    
            default : printf("Fail \n");

       
        }

     

        return 0;
}