#include <stdio.h>
#include <iostream>
#include <list>
#include <string.h>
using namespace std;

void calculate(char units[][20], list<float> con, float value)
{
    int n = 0;
    float sol;

    FILE *fp1;
    fp1 = fopen("history.txt", "a");

    for (auto i = con.begin(); i != con.end(); i++)
    {
        sol = value / *i;
        printf("%.2f %s\n", sol, units[n]);
        fprintf(fp1, "%.2f %s\n", sol, units[n]);
        n++;
    }
    fclose(fp1);
}

void search(char units[][20], list<float> con)
{
    int n = 0;
    float value, input;
    char unit[10];

    scanf("%f %s", &input, &unit);

    for (auto i = con.begin(); i != con.end(); i++)
    {
        if (strcmp(unit, units[n]) == 0)
        {
            value = input * *i;
            calculate(units, con, value);
        }
        n++;
    }
}

void Measure()
{
    list<float> weight = {1.0, 1000.0, 28.35, 423.592};
    char w[][20] = {"g", "kg", "oz", "lbs"};

    list<float> length = {1.0, 100.0, 100000.0, 160934.0, 30.48};
    char l[][20] = {"cm", "m", "km", "miles", "feet"};

    int sw;

    while (sw != 3)
    {
        printf("Chose type of measurement\n\n1.Lenght\n2.Weight\n\nPress '3' to go Back\n\n");
        scanf("%d", &sw);

        //switch between length and weight
        switch (sw)
        {
        case 1:
            printf("\nenter input length = ");
            search(l, length);
            break;
        case 2:
            printf("\nenter input weight = ");
            search(w, weight);
            break;
        case 3:
            break;
        default:
            printf("INVALID INPUT!\n");
            break;
        }
    }
}

struct amount
{
    float money;
    char name[20];
};
//function to convert currency
void Currency()
{
    int i, n, found = 0;
    float dollars, pounds, yen;
    float conno[10] = {0.013, 0.010, 1.53};
    struct amount a[10];
    char sname[20];
    //enter number of amounts you want to convert
    printf("Enter the number of details n= ");
    scanf("%d", &n);
    for (i = 0; i < n; i++)
    {
        printf("\nenter the %d amount details \n", i + 1);
        printf("enter the account name without white spaces:");
        scanf("%s", a[i].name);
        printf("enter the amount in rupees : ");
        scanf("%f", &a[i].money);
    }
    //print converted output
    printf("\nThe account details are \n");
    printf("\nName\tRupees\t\tDollars\t\tPounds\t\tYen\n");
    for (i = 0; i < n; i++)
    {
        dollars = a[i].money * conno[0];
        pounds = a[i].money * conno[1];
        yen = a[i].money * conno[2];
        printf("\n%s\t₹%.2f\t$%.2f\t\t£%.2f\t\t¥%.2f\n", a[i].name, a[i].money, dollars, pounds, yen);
    }
}

int main()
{
    int s;
    while (s != 3)
    {
        //switch between measurement and currency convertor
        printf("\n1.Measurement\n2.Currency\n\nPress '3' to Exit\n");
        scanf("%d", &s);
        switch (s)
        {
        case 1:
            Measure();
            break;

        case 2:
            Currency();
            break;

        case 3:
            break;

        default:
            printf("\nInvalid Input!!\n");
            break;
        }
    }
    return 0;
}