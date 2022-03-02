#include <stdio.h>
#include <iostream>
#include <list>
#include <string.h>
using namespace std;
#pragma region functions
void add(int);
void calculate(char[][20], list<float>, float);
void simplify(char[][20], list<float>);
void history();
void Measure();
void findCurr(int, float);
void convert(int);
void display(int);
void add(int);
void search(int);
void edit(int);
void remove(int);
void Currency();
#pragma endregion
int main()
{
    int s;
    while (s != 3)
    {
        // switch between measurement and currency convertor
        printf("\n1.Measurement\t2.Currency\tPress '3' to Exit\n");
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

#pragma region measurement
void Measure()
{
    // conversions units and SI units of the different measurement systems
    list<float> weight = {1.0, 1000.0, 28.35, 423.592};
    char w[][20] = {"g", "kg", "oz", "lbs"};

    list<float> length = {1.0, 100.0, 100000.0, 160934.0, 30.48};
    char l[][20] = {"cm", "m", "km", "miles", "feet"};

    list<float> liquid = {1.0, 0.2641722, 1.05669, 33.814};
    char lq[][20] = {"L", "gal", "qt", "oz"};

    int sw;

    while (sw != 5)
    {
        printf("Chose type of measurement\n1.Lenght\t2.Weight\t3.Liquid\t4.History\t5.Back\n");
        scanf("%d", &sw);

        // switch between length, weight and liquid conversions
        switch (sw)
        {
        case 1:
            printf("\nenter input length = ");
            simplify(l, length);
            break;
        case 2:
            printf("\nenter input weight = ");
            simplify(w, weight);
            break;
        case 3:
            printf("\nenter input liquid = ");
            simplify(lq, liquid);
            break;
        case 4:
            history();
            break;
        case 5:
            break;
        default:
            printf("INVALID INPUT!\n");
            break;
        }
    }
}

// simplify the input unit to the simplest unit
void simplify(char units[][20], list<float> con)
{
    int ele = 0, found = 0;
    float value, input;
    char unit[10];

    scanf("%f %s", &input, &unit);

    FILE *fp1;
    fp1 = fopen("history.txt", "a");

    printf("\nConvertions of %.2f %s are:\n", input, unit);
    fprintf(fp1, "\nConvertions of %.2f %s are:\n", input, unit);
    fclose(fp1);

    // find the input uniy and multiply with the list containing conversion units
    for (auto i = con.begin(); i != con.end(); i++)
    {
        if (strcmp(unit, units[ele]) == 0)
        {
            value = input * *i;
            found = 1;
            calculate(units, con, value);
        }
        ele++;
    }
    if (found == 0)
    {
        printf("Unit not found !!\n");
    }
}

// convert the simpified input unit to all different available units
void calculate(char units[][20], list<float> con, float value)
{
    int ele = 0;
    float sol;

    FILE *fp1;
    fp1 = fopen("history.txt", "a");
    if (fp1 == NULL)
    {
        printf("Error: could not open file\n");
    }

    // divide with the list containing conversion units
    for (auto i = con.begin(); i != con.end(); i++)
    {
        sol = value / *i; // convert to all other available units
        printf("%.2f %s\n", sol, units[ele]);
        // insert the results into a history file
        fprintf(fp1, "%.2f %s\n", sol, units[ele]);
        ele++;
    }
    printf("\n");
    fclose(fp1);
}

void history()
{
    int ch;
    const int max = 256;
    char details[50];
    printf("1.Veiw history\t2.clear history\n");
    scanf("%d", &ch);

    FILE *fp1;

    switch (ch)
    {
    // veiw the history saved in the history file
    case 1:
        fp1 = fopen("history.txt", "r");
        if (fp1 == NULL)
        {
            printf("Error: could not open file\n");
        }

        char buffer[max];
        // gets read the contents of the file one line at a time
        while (fgets(buffer, max, fp1))
            printf("%s", buffer);
        break;
    case 2:
        // clear the history saved in the history file
        fp1 = fopen("history.txt", "w");
        fprintf(fp1, " ");
        printf("history has been cleared\n");
        break;
    default:
        printf("INVALID INPUT!\n");
    }
    fclose(fp1);
}
#pragma endregion

#pragma region currency
// array of structures containing all the account details
struct account
{
    float money;   // amount of money in account
    char name[20]; // name of account
};
char inputCurr[10];
float convUnits[20] = {1.0, 0.013, 0.010, 1.53, 0.012};
struct account a[10];

// function to convert currency
void Currency()
{
    int i, n = 0, ch;
    float inp;

    while (ch != 6)
    {
        printf("\nselect option\n1.Display\t2.Add\t3.Search\t4.Edit\t5.Delete\t6.Back\n");
        scanf("%d", &ch);
        switch (ch)
        {
        case 1:
            display(n);
            break;
        case 2:
            printf("\nenter the %d acount details \n", n + 1);
            printf("enter the account name without white spaces: ");
            scanf("%s", a[n].name);
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
            remove(n);
            break;
        case 6:
            break;
        default:
            printf("Invalid choise!!");
            break;
        }
    }
}

// convert the money in the account to different units
void convert(int key)
{
    float rupees, dollars, pounds, yen, euro;

    rupees = a[key].money * convUnits[0];
    dollars = a[key].money * convUnits[1];
    pounds = a[key].money * convUnits[2];
    yen = a[key].money * convUnits[3];
    euro = a[key].money * convUnits[4];
    printf("\n%s\t₹%.2f\t$%.2f\t\t£%.2f\t\t¥%.2f\t\t€%.2f\n", a[key].name, a[key].money, dollars, pounds, yen, euro);
}

// find what is the currency that the user entered
void findCurr(int key, float inp)
{
    int x, found = 0;
    char currencies[][20] = {"rupees", "dollars", "pounds", "yen", "euro"};
    for (x = 0; x < 5; x++)
    {
        if (strcmp(inputCurr, currencies[x]) == 0)
        {
            found = 1;
            a[key].money = inp / convUnits[x]; // simplify the currency into rupees
            printf("new amount successfully added");
        }
    }
    if (found == 0)
    {
        printf("Invalid input currency!!\nenter valid unit of currency\n");
        add(key);
    }
}

// display the account details with converted units
void display(int n)
{
    int i;
    printf("\nThe account details are \n");
    printf("\nName\tRupees\t\tDollars\t\tPounds\t\tYen\n");
    for (i = 0; i < n; i++)
    {
        convert(i);
    }
}

// add a new account to the array
void add(int n)
{
    float inp, i;

    printf("enter the amount : ");
    scanf("%f %s", &inp, &inputCurr);
    // find input currency
    findCurr(n, inp);
}

// search for the account that the user wants to veiw
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
            // display details of the found account
            printf("\nAccount details are:\n");
            convert(i);
        }
    }
    if (found == 0)
    {
        printf("Account not found");
    }
}

// edit the amount of money in an existing account
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
            findCurr(i, inp);
        }
    }
}

// remove the details from unrequired account
void remove(int n)
{
    int i, found = 0;
    char sname[20];

    printf("\nEnter account name to delete: ");
    scanf("%s", sname);
    for (i = 0; i < n; i++)
    {
        if (strcmp(a[i].name, sname) == 0)
        {
            found++;
            a[i].money = 0;
            printf("details successfully removed");
        }
    }
    if (found == 0)
    {
        printf("Account not found\n");
    }
}
#pragma endregion