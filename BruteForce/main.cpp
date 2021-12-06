#include <stdio.h>

int main()
{
    int arrInput[9];
    int arrOutput[7] = { 0, };
    int totalHeight = 0;

    for (int i = 0; i < 9; i++)
    {
        scanf("%d", &arrInput[i]);
        totalHeight = totalHeight + arrInput[i];
    }

    int target1, target2;
    for (int i = 0; i < 9; i++)
    {
        for (int j = i + 1; j < 9; j++)
        {
            if (totalHeight - arrInput[i] - arrInput[j] == 100)
            {
                target1 = i;
                target2 = j;
            }
        }
    }

    int tmp = 0;
    for (int i = 0; i < 9; i++)
    {
        if (i == target1 || i == target2)
        {
            continue;
        }
        else
        {
            arrOutput[tmp++] = arrInput[i];
        }
    }

    for (int i = 0; i < 7; i++)
    {
        for (int j = i + 1; j < 7; j++)
        {
            if (arrOutput[i] > arrOutput[j])
            {
                int tmp = arrOutput[i];
                arrOutput[i] = arrOutput[j];
                arrOutput[j] = tmp;
            }
        }
    }


    for (int i = 0; i < 7; i++)
    {
        printf("%d\n", arrOutput[i]);
    }
    return 0;
}