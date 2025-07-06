#include <stdio.h>
#include <string.h>

void create_account(); 
void deposit_money(); 
void withdraw_money(); 
void check_balance(); 

const char* ACCOUNT_FILE = "account.dat";

typedef struct {
    char name[50];
    int acc_no;
    float balance;
} Account;


int main(){

    while(1){
        int choice;
        printf("\n\n Bank managment system");
        printf("\n 1.Create Account");
        printf("\n 2.Deposit Money");
        printf("\n 3.Withdraw money");
        printf("\n 4.Check Balance");
        printf("\n 5.Exit");
        printf("\n Enter your choice ");
        scanf("%d" , &choice );
         
        switch (choice)
        {
        case 1:
            create_account();
            break;
        case 2:
            deposit_money();
            break;
        case 3:
            withdraw_money();
            break;
        case 4:
            check_balance();
            printf("");
            break;
        case 5:
            printf("Exiited Succesffuly");
            return 0;
            break;
        default:
            printf("Invalid Choice");
            break;
        }
    }
}


// fgets reads the input including the newline character '\n'
// strcspn finds the index of the first '\n' in the input string
// We replace that '\n' with '\0' to remove the newline from the stored name
void create_account(){
    Account acc;
    FILE *file = fopen(ACCOUNT_FILE , "ab+");
    if (file == NULL){
        printf("File cannot be accessed");
        return;
    }

    char c;
    do
    {
        c = getchar();
    } while (c != '\n' && c != EOF);
    

    printf("\n Enter your name : ");
    fgets(acc.name , sizeof(acc.name) , stdin);
    int ind = strcspn(acc.name , "\n");
    acc.name[ind] = '\0';
    printf("Enter your account number:");
    scanf("%d" , &acc.acc_no);
    acc.balance = 0;

    fwrite(&acc , sizeof(acc) , 1 , file);
    fclose(file);
    printf("\n Account Created successfully");
}

    

void deposit_money(){
    FILE *file = fopen(ACCOUNT_FILE , "rb+");
    if(file == NULL){
        printf("unable to access account");
        return;
    }
    int acc_no;
    float money;
    Account acc_to_read;
    printf("enter account num:");
    scanf("%d" , &acc_no);
    printf("enter amount to deposit:");
    scanf("%f" , &money);

    while (fread(&acc_to_read, sizeof(acc_to_read) , 1 , file)){
       if (acc_to_read.acc_no == acc_no){
            acc_to_read.balance += money;
            fseek(file, -sizeof(acc_to_read) ,SEEK_CUR);
            fwrite(&acc_to_read , sizeof(acc_to_read) , 1 , file);
            fclose(file);
            printf("succesffuly deposited Rs.%.2f New balance is Rs.%.2f" , money, acc_to_read.balance);
            return;
        } 
    }
    
    fclose(file);
    printf("Acoount not found %d for account" , acc_no);
}

void withdraw_money(){
     FILE *file = fopen(ACCOUNT_FILE , "rb+");
    if(file == NULL){
        printf("unable to access account");
        return;
    }
    int acc_no;
    float money;
    Account acc_to_read;
    printf("Enter account number:");
    scanf("%d" , &acc_no);
    printf("Enter money you want to withdraw:");
    scanf("%f" , &money);

    while (fread(&acc_to_read, sizeof(acc_to_read) , 1 , file) != EOF){
       if (acc_to_read.acc_no == acc_no){
        if (acc_to_read.balance >= money){
            acc_to_read.balance -= money;
            fseek(file , -sizeof(acc_to_read) , SEEK_CUR);
            fwrite(&acc_to_read , sizeof(acc_to_read) , 1 , file);
            printf("Money withdrawn Rs.%.2f" , money, acc_to_read.balance);
        } else{
            printf("Insuuficent Balance");
        }
        fclose(file);
        return;
    }
}   
    fclose(file);
    printf("money not withdrawn as account %d was not found in records." , acc_no);

}

void check_balance(){
    FILE *file = fopen(ACCOUNT_FILE , "rb");
    if (file == NULL){
        printf("File cannot be accessed");
        return;
    }
    

   int acc_no;
   Account acc_read;
   printf("Enter your account number:");
   scanf("%d" , &acc_no);

   while (fread(&acc_read , sizeof(acc_read) ,1 , file)){
        if (acc_read.acc_no == acc_no){
        printf("Your account balance is Rs.%2.f", 
        acc_read.balance);
        fclose(file);
        return;
        }
   }
   fclose(file);
   printf("\n Account No : %d was not found \n" , acc_no); 
}