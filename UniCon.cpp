#include <stdio.h>
#include <iostream>
#include <list>
#include <string.h>
using namespace std;

void calculate(char units[][20], list<float> con, float value)
{
    int ele = 0;
    float sol;

    FILE *fp1;
    fp1 = fopen("history.txt", "a");

    for (auto i = con.begin(); i != con.end(); i++)
    {
        sol = value / *i;
        printf("%.2f %s\n", sol, units[ele]);
        fprintf(fp1, "%.2f %s\n", sol, units[ele]);
        ele++;
    }
    fclose(fp1);
}

void find(char units[][20], list<float> con)
{
    int ele = 0;
    float value, input;
    char unit[10];

    scanf("%f %s", &input, &unit);

    FILE *fp1;
    fp1 = fopen("history.txt", "a");

    printf("\nConvertions of %.2f %s are:\n", input, unit);
    fprintf(fp1, "\nConvertions of %.2f %s are:\n", input, unit);
    fclose(fp1);

    for (auto i = con.begin(); i != con.end(); i++)
    {
        if (strcmp(unit, units[ele]) == 0)
        {
            value = input * *i;
            calculate(units, con, value);
        }
        ele++;
    }
    if (ele == 0)
    {
        printf("Unit not found !!\n");
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
        printf("Chose type of measurement\n1.Lenght\n2.Weight\nPress '3' to go Back\n");
        scanf("%d", &sw);

        //switch between length and weight
        switch (sw)
        {
        case 1:
            printf("\nenter input length = ");
            find(l, length);
            break;
        case 2:
            printf("\nenter input weight = ");
            find(w, weight);
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
char inputCurr[10];
float convUnits[20] = {1.0, 0.013, 0.010, 1.53};
struct amount a[10];

void scan(int key, float inp)
{
    int x;
    char currencies[][20] = {"rupees", "dollars", "pounds", "yen"};
    for (x = 0; x < 4; x++)
    {
        if (strcmp(inputCurr, currencies[x]) == 0)
        {
            a[key].money = inp / convUnits[x];
        }
    }
}

void count(int key)
{
    float rupees, dollars, pounds, yen;

    rupees = a[key].money * convUnits[0];
    dollars = a[key].money * convUnits[1];
    pounds = a[key].money * convUnits[2];
    yen = a[key].money * convUnits[3];
    printf("\n%s\t₹%.2f\t$%.2f\t\t£%.2f\t\t¥%.2f\n", a[key].name, a[key].money, dollars, pounds, yen);
}

void search(int n)
{
    int i, found = 0;
    char sname[20];

    printf("\nEnter account name to search: ");
    scanf("%s", sname);
    for (i = 0; i < n; i++)
    {
        if (strcmp(a[i].name, sname) == 0)
        {
            found++;
            printf("\nAccount details are:\n");
            count(i);
        }
    }
    if (found == 0)
    {
        printf("Account not found");
    }
}

void edit(int n)
{
    int i;
    float inp;
    char sname[10];

    printf("\nEnter the account name : ");
    scanf("%s", sname);
    for (i = 0; i < n; i++)
    {
        if (strcmp(a[i].name, sname) == 0)
        {
            printf("enter the new amount : ");
            scanf("%f %s", &inp, &inputCurr);
            scan(i, inp);
            printf("Successfully edited");
        }
    }
}

void add(int n)
{
    int i;
    float inp;

    printf("\nenter the new amount details \n");
    printf("enter the new account name without white spaces: ");
    scanf("%s", a[n].name);
    printf("enter the amount : ");
    scanf("%f %s", &inp, &inputCurr);
    scan(n, inp);
    printf("new account successfully added\n");
}

//function to convert currency
void Currency()
{
    int i, n, ch;
    float inp;
    printf("Enter the number of details n= ");
    scanf("%d", &n);
    for (i = 0; i < n; i++)
    {
        printf("\nenter the %d amount details \n", i + 1);
        printf("enter the account name without white spaces:");
        scanf("%s", a[i].name);
        printf("enter the amount in rupees : ");
        scanf("%f %s", &inp, &inputCurr);
        scan(i, inp);
    }
    printf("\nThe account details are \n");
    printf("\nName\tRupees\t\tDollars\t\tPounds\t\tYen\n");
    for (i = 0; i < n; i++)
    {
        count(i);
    }

    while (ch != 5)
    {
        printf("\nselect option\n1.Display  2.Add  3.Search  4.Edit  5.Exit\n");
        scanf("%d", &ch);
        switch (ch)
        {
        case 1:
            printf("\naccount details are:\n");
            printf("\nName\tRupees\t\tDollars\t\tPounds\t\tYen\n");
            for (i = 0; i < n; i++)
            {
                count(i);
            }
            break;
        case 2:
            add(n);
            n++;
            break;
        case 3:
            search(n);
            break;
        case 4:
            edit(n);
            break;
        case 5:
            break;
        default:
            printf("Invalid choise!!");
            break;
        }
    }
}

int main()
{
    int s;
    while (s != 3)
    {
        //switch between measurement and currency convertor
        printf("\n1.Measurement\n2.Currency\nPress '3' to Exit\n");
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