#include <stdio.h>
#include <stdlib.h>

int GetContry()
{
    int costCountry;
    char ans;
    printf("Select a country for delivery. Press the corresponding number. Order is carried out only to Russia-1, Belarus-2, Ukraine-3 and Moldova-4\n");
     while(getchar()!='\n'){}
    scanf("%c", &ans);

    switch (ans)
    {
    case '1':
        costCountry = 320;
        break;
    case '2':
        costCountry = 200;
        break;
    case '3':
        costCountry = 320;
        break;
    case '4':
        costCountry = 360;
        break;
    default:
        printf("You entered an invalid input\n");
        break;
    }
    return costCountry;
}

int Cement()
{
    int flag = 0, countCement;
    printf("How many tons do you want to order?\n");
    while(flag==scanf("%d", &countCement)){}
    return countCement;
}

int Gravel()
{
    int flag = 0, countGravel;
    printf("How many tons do you want to order?\n");
    while(flag==scanf("%d", &countGravel)){}
    return countGravel;
}

int Concrete()
{
    int flag = 0, countConcrete;
    printf("How many tons do you want to order?\n");
    while(flag==scanf("%d", &countConcrete)){}
    return countConcrete;
}

void Info();

void Exit();

void Decision(int cost, int trueCost, int costCountry, int counter)
{
    int finalCost = cost - trueCost - counter * costCountry;
    if (finalCost <= 25000)
    {
        printf("Your order is unprofitable for our factory, so we will refuse this order\n");
        Info(); 
        Exit();
    }
    else
    {
        int flag=0;
        char answer3;
        while(getchar()!='\n');
        while(flag!=scanf("%d", &cost))
        printf("The cost of the order is'%d'", cost);
        printf(". Confirm your order. Yes 1. No-2.\n");
        flag=0;
        while(getchar()!='\n');
        while(flag!=scanf("%c", &answer3))
        if (answer3 == '1' || answer3 == '2')
        {
            if (answer3 == '1')
                printf(".Profit of the company'%d'", finalCost);
            else
            {
                Info(); 
                Exit();
            }
        }
    }
}

int Num(int countCement, int countGravel, int countConcrete)
{
        int counter = countCement+countGravel+countConcrete;
        if(counter%50==0)
        counter /= 50;
        else
        {
        counter-=counter%50;
        counter/=50;
        counter++;
        }
        return counter;  
}

void Parameters(int countCement, int countGravel, int countConcrete, int cost)
{
        printf("Tariffs for these materials. Cement-230, gravel-142, concrete-260");
        printf(". The total cost of the order - %d", cost);
        int counter=Num(countCement, countGravel, countConcrete);
        printf("The number of wagons required for transportation - %f", counter);
        printf("Transportation to Russia and Ukraine will cost -320, to Belarus-200, to Moldova-360");
}

 void Info()
    {
        printf("Developed by Shlyapo E.D. Program version 1.0 \n");
    }

void Exit()
    {
        printf("Goodbye !!!!!!! \n");
        exit(0);
    }

int main()
    {
        int n = 1, countCement=0, countGravel = 0, countConcrete = 0, cost = 0, counter = 0, trueCost = 0;
        while (n==1)
        {
            char answer;
            printf("What do you want to order? Enter the corresponding number: cement-1, gravel-2, concrete-3 \n");
            while(getchar()!='\n'){}
            scanf("%c", &answer);
            int count = 0;
            switch (answer)
            {
            case '1':
                countCement=Cement();
                cost += 230 * countCement;
                trueCost += 160 * countCement;
                break;
            case '2':
                countGravel=Gravel();
                cost += 142 * countGravel;
                trueCost += 96 * countGravel;
                break;
            case '3':
                countConcrete=Concrete();
                cost += 260 * countConcrete;
                trueCost += 205 * countConcrete;
                break;
            default:
                printf("Incorrect input \n");
                break;
            }
            printf("Do you want to order anything else? Press 1 if yes. No-2 \n");
            while(getchar()!='\n'){}
            char answer2 = getchar();
            if(answer2 == '1' || answer2 == '2')
            {
                if (answer2 == '2')
                    break;
            }
            else
                printf("Incorrect input \n");
        }
        int country=GetContry();
        Parameters(countCement, countGravel, countConcrete, cost);
        counter=Num(countCement, countGravel, countConcrete);
        Decision(cost, trueCost, country, counter);
        Info(); 
        Exit();
        return 0;
    }