#include <iostream>
#include <time.h>

#define n 1000000

using namespace std;


struct stack_
{
    __int64 indexStart;
    __int64 sizeArr;
    stack_* next;
};

void outputArray(__int64* arr)
{
    for (__int64 i = 0; i < n; i++)
        std::cout << *(arr + i) << " ";
    std::cout << endl;
}

void outputArrayWithSize(__int64* arr, __int64 size)
{
    for (__int64 i = 0; i < size; i++)
        std::cout << *(arr + i) << " ";
    std::cout << endl;
}

void outputArrayWithIndex(__int64* arr, __int64 start, __int64 end)
{
    for (__int64 i = start; i <= end; i++)
        cout << arr[i] << " ";
    cout << endl;
}

__int64 power2(__int64 someNumber)
{
    if (someNumber == 0) return 1;
    else
    {
        __int64 someResult = 1;
        for (someNumber; someNumber > 0; someNumber--)
        {
            someResult *= 2;
        }
        return someResult;
    }
}

void isThisTrue(__int64* arr)
{
    bool is = true;
    for (__int64 i = 1; i < n; i++)
    {
        if (arr[i - 1] > arr[i])
        {
            is = false;
            break;
        }
    }
    if (is == false)
        cout << "That's false sequence" << endl;
    else cout << "That's true sequence " << endl;
}

void outputStack(stack_* move)
{
    while (move != nullptr)
    {
        std::cout << move->indexStart << ":" << move->indexStart + move->sizeArr - 1 << endl;
        move = move->next;
    }
}

__int64 getMin(__int64 l1, __int64 r1, __int64 l2, __int64 r2)
{
    if (r1 - l1 + 1 >= r2 - l2 + 1)
        return r1 - l1 + 1; else return r2 - l2 + 1;
}

void fillVector(__int64 *inArr, __int64 *outArr, __int64 start, __int64 end)
{
    __int64 j = start;
    for (__int64 i = 0; i <= end-start; i++)
    {
        inArr[i] = outArr[j];
        j++;
    }
}

void naturalMergeSort(__int64* arr, __int64 left1, __int64 right1, __int64 left2, __int64 right2)
{ // [left1; right1] [left2; right2] --> от 1 до 20 == [0; 19]
  // right1 - left1 = 19 - 0 = 19 - включённая граница
    __int64 gM = getMin(left1, right1, left2, right2);
    __int64* newArr = new __int64[gM]; //Временный массив с размером минимального
                                //из сливаемых массивов
    __int64 i, j, multiplier, iStart = 0, jStart = 0;
    
    if (gM == right1 - left1 + 1)
    {
        //Рассмариваем случай, что r1-l1 <= r2-l2
        //std::cout << "Попадание в первый случай" << std::endl;
        fillVector(newArr, arr, left1, right1);
        i = 0; //Отвечает за индексы newArr
        multiplier = 0; //Отвечает за увеличение шага
        j = left2; //Отвечает за индексы arr
        __int64 outputBorder = 0;
        bool isEntry = false;
        __int64 power = 0;
        __int64 m = left1; //movement по массиву arr, начиная с позиции left1
        while (m <= right2)
        {
            iStart = i; 
            multiplier = 0;
            isEntry = false;
            power = 0;
            while (i <= right1-left1 && j <= right2 && newArr[i] <= arr[j])
            { //Проходка с i до r1
                //std::cout << "i: " << i << "; newArr[i]: " << newArr[i] << "; arr[j]: " << arr[j] << std::endl;
                isEntry = true;
                if (i - iStart < 8) //step + 1, сравниваю первые 8 элементов
                {
                    i++;
                }
                else {
                    multiplier = power2(power); //Работаю с multiplier-ом
                    if (i + multiplier <= right1-left1 && newArr[i+multiplier] <= arr[j])
                    {
                        i += multiplier;
                        power++;
                        if (i == right1-left1) //Достиг края
                            break;
                    }
                    else if (i + multiplier > right1 - left1 && newArr[right1 - left1] <= arr[j])
                    { //Скачок за границы массива
                        i = right1 - left1 + 1;
                        break;
                    }
                    else if (i + multiplier <= right1 - left1 && newArr[i+multiplier] > arr[j])
                    { //В пределах границ, но сравниваемый элемент оказался меньше, чем искомый граничный
                        if (multiplier == 1)
                        {
                            i++;
                            break;
                        }
                        else
                        {
                            multiplier = 0;
                            power = 0;
                        }
                    }
                    else if (i + multiplier > right1 - left1 && newArr[right1 - left1] > arr[j])
                    {
                        multiplier = 0;
                        power = 0;
                    }
                }
            }

            //Прошли с iStart до i
            if (isEntry == true)
            {
                for (iStart; i - iStart != 0; iStart++, m++)
                {
                    arr[m] = newArr[iStart];
                }
            }
          
            if (iStart >= right1 - left1 + 1)
            {//Завершили проход меньшего массива. Можно дозаполнить arr оставшимися элементами из arr и break-нуться
                break; //Временно, пока для теста
            }
            isEntry = false;
            jStart = j;
            multiplier = 0;
            power = 0;
            while (j <= right2 && i <= right1-left1 && arr[j] <= newArr[i])
            {
                isEntry = true;
                if (j - jStart < 8)
                    j++;
                else 
                { 
                    multiplier = power2(power);
                    if (j + multiplier <= right2 && arr[j + multiplier] <= newArr[i])
                    {
                        j += multiplier;
                        power++;
                        if (j == right2) //Достиг края
                            break;
                    }
                    else if (j + multiplier > right2 && arr[right2] <= newArr[i])
                    { //Скачок за границы массива
                        j = right2 + 1;
                        break;
                    }
                    else if (j + multiplier <= right2 && arr[j + multiplier] > newArr[i])
                    { //В пределах границ, но сравниваемый элемент оказался меньше, чем искомый граничный
                        if (multiplier == 1)
                        {
                            j++;
                            break;
                        }
                        else
                        {
                            power = 0;
                            multiplier = 0;
                        }
                    }
                    else if (j + multiplier > right2 && arr[right2] > newArr[i])
                    {
                        multiplier = 0;
                        power = 0;
                    }
                }
            }
            if (isEntry == true)
            for (; j - jStart != 0; jStart++, m++)
            {
                arr[m] = arr[jStart];
            }
            if (jStart > right2)
            {//Завершили проход большего массива. Можно дозаполнить arr оставшимися элементами из newArr и break-нуться
                while (i < right1 - left1+1)
                {
                    arr[m] = newArr[i];
                    i++;
                    m++;
                }
                break;
            }
        }
    }
    else {
        //Рассматриваем случай, что r2-l2 <= r1-l1
        //std::cout << "Попадание во второй случай" << std::endl;
        fillVector(newArr, arr, left2, right2);
       
        /*
            Обращаю внимание, что в данной ситуации
            я хочу поменять местами части массива, чтобы
            привести данный вариант к первому случаю.
            Дальнейшие действия заключаются в записи в новый массив
            сначала меньшего подмассива, а потом большего подмассива.
            Следовательно, поскольку данный этап не входит в особенности
            идеи алгоритма, я его не буду учитывать при формулировке времени.
        */
        __int64 *arrForReverse = new __int64[right2 - left1+1];
        fillVector(arrForReverse, newArr, 0, right2 - left2);
        __int64 o = right2-left2+1;
        for (__int64 g = left1; g <= right1; g++)
        {
            arrForReverse[o] = arr[g];
            o++;
        }
        o = 0;
        for (__int64 g = left1; g <= right2; g++)
        {
            arr[g] = arrForReverse[o];
            o++;
        }
        /*
            Подмассивы приведены к нормальному виду;
            Меняю местами границы.
        */
        right1 = left1 + (right2 - left2);
        left2 = right1 + 1;
        delete[]arrForReverse;
        i = 0; //Отвечает за индексы newArr
        multiplier = 0; //Отвечает за увеличение шага
        j = left2; //Отвечает за индексы arr
        __int64 outputBorder = 0;
        bool isEntry = false;
        __int64 power;
        __int64 m = left1; //movement по массиву arr, начиная с позиции left1
        while (m <= right2)
        {
            iStart = i;
            multiplier = 0;
            isEntry = false;
            power = 0;

            while (i <= right1 - left1 && j <= right2 && newArr[i] <= arr[j])
            { //Проходка с i до r1
                //std::cout << "i: " << i << "; newArr[i]: " << newArr[i] << "; arr[j]: " << arr[j] << std::endl;
                isEntry = true;
                if (i - iStart < 8) //step + 1, сравниваю первые 8 элементов
                {
                    i++;
                }
                else {
                    multiplier = power2(power); //Работаю с multiplier-ом
                    if (i + multiplier <= right1 - left1 && newArr[i + multiplier] <= arr[j])
                    {
                        i += multiplier;
                        power++;
                        if (i == right1 - left1) //Достиг края
                            break;
                    }
                    else if (i + multiplier > right1 - left1 && newArr[right1 - left1] <= arr[j])
                    { //Скачок за границы массива
                        i = right1 - left1 + 1;
                        break;
                    }
                    else if (i + multiplier <= right1 - left1 && newArr[i + multiplier] > arr[j])
                    { //В пределах границ, но сравниваемый элемент оказался меньше, чем искомый граничный
                        if (multiplier == 1)
                        {
                            i++;
                            break;
                        }
                        else
                        {
                            power = 0;
                            multiplier = 0;
                        }
                    }
                    else if (i + multiplier > right1 - left1 && newArr[right1 - left1] > arr[j])
                    {
                        multiplier = 0;
                        power = 0;
                    }
                }
            }

            //Прошли с iStart до i
            if (isEntry == true)
            {
                for (iStart; i - iStart != 0; iStart++, m++)
                {
                    arr[m] = newArr[iStart];
                }
            }

            if (iStart >= right1 - left1 + 1)
            {//Завершили проход меньшего массива. Можно дозаполнить arr оставшимися элементами из arr и break-нуться
                break; //Временно, пока для теста
            }
            isEntry = false;
            jStart = j;
            multiplier = 0;
            while (j <= right2 && i <= right1 - left1 && arr[j] <= newArr[i])
            {
                isEntry = true;
                if (j - jStart < 8)
                    j++;
                else
                {
                    multiplier++;
                    if (j + multiplier <= right2 && arr[j + multiplier] <= newArr[i])
                    {
                        j += multiplier;
                        if (j == right2) //Достиг края
                            break;
                    }
                    else if (j + multiplier > right2 && arr[right2] <= newArr[i])
                    { //Скачок за границы массива
                        j = right2 + 1;
                        break;
                    }
                    else if (j + multiplier <= right2 && arr[j + multiplier] > newArr[i])
                    { //В пределах границ, но сравниваемый элемент оказался меньше, чем искомый граничный
                        if (multiplier == 1)
                        {
                            j++;
                            break;
                        }
                        else
                            multiplier = 0;
                    }
                    else if (j + multiplier > right2 && arr[right2] > newArr[i])
                    {
                        multiplier = 0;
                    }
                }
            }
            if (isEntry == true)
                for (; j - jStart != 0; jStart++, m++)
                {
                    arr[m] = arr[jStart];
                }
            if (jStart > right2)
            {//Завершили проход большего массива. Можно дозаполнить arr оставшимися элементами из newArr и break-нуться
                while (i < right1 - left1-1)
                {
                    arr[m] = newArr[i];
                    i++;
                    m++;
                }
                break;
            }
        }
    } //end else

    delete[]newArr;
}

void insertSort(__int64 left, __int64 right, __int64* arr)
{ //Classic insert sort. Example: arr[0..n-1] --> left = 0, right = n-1
    if (left < 0) left = 0;
    if (right > n) right = n - 1;

    if (left != right)
    {
        __int64 save; // first element on the right place --> left+1
        __int64 movement;

        for (__int64 i = left + 1; i <= right; i++)
        {
            movement = i;
            save = *(arr + movement);

            while (movement != left && save < *(arr + movement - 1))
            {
                arr[movement] = *(arr + movement - 1);
                movement--;
            }

            if (movement == left) arr[movement] = save;
            else arr[movement] = save;
        }
    }
}

void autoFillingVector(__int64* arr)
{
    srand(time(NULL));
    for (__int64 i = 0; i < n; i++)
    {
        arr[i] = rand() % 100;
    }
}

__int64 getMinrun(__int64 k)
{
    __int64 r = 0;
    while (k >= 64) {
        r |= k & 1;
        k >>= 1;
    }
    return k + r;
}


void timsort(__int64* arr)
{
    __int64 minrun = getMinrun(n);
    //т.к. массив начинается с 0-го элемента
    if (minrun == n) insertSort(0, n - 1, arr);
    else {
        __int64 startPo__int64;
        __int64 swaps;
        __int64 decrement;
        for (__int64 i = 0; i < n / minrun; i++)
        {
            startPo__int64 = 0;
            for (__int64 j = i * minrun + 1; j < minrun * i + minrun; j++)
            {
                if (arr[j] <= arr[j - 1])
                {
                    startPo__int64 = j - 1;
                    while (arr[j] <= arr[j - 1] && j < minrun * i + minrun)
                        j++;
                    if (arr[j] > arr[j - 1]) j++;
                    decrement = -1;
                    if (j >= minrun * i + minrun)
                        j = minrun * i + minrun - 1;

                    for (__int64 k = startPo__int64; j + decrement > k; k++)
                    {
                        swaps = arr[k];
                        arr[k] = arr[(j)+decrement];
                        arr[(j)+decrement] = swaps;
                        decrement -= 1;
                    }
                    j = minrun * i + minrun;
                }
            }
        }
        __int64 counter = 0;
        for (counter = 0; counter < n / minrun; counter++)
            insertSort(counter * minrun, counter * minrun + minrun - 1, arr); //Сорт run-ов instert-ом
        if (n % minrun > 0)
            insertSort(counter * minrun, n - 1, arr); //Сорт остатка (Остаток меньше minrun --> insertsort)
        //Остаток тоже должен быть упорядочен по возрастанию (его часть)
        if (n % minrun > 0) counter = 1; else counter = 0;
        __int64 sizeArr_info = n / minrun;
        sizeArr_info += (n % minrun > 0 ? 1 : 0);
        //cout << sizeArr_info << endl;
        //outputArray(arr);
        if (sizeArr_info > 2)
        { // Если в стеке больше двух упорядоченных подмассивов, то реализуется алгоритм.
            stack_* arr_info = new stack_();
            stack_* move_ = arr_info;
            stack_* beforeMove = arr_info;
            for (__int64 i = 0; i < sizeArr_info; i++)
            {
                
                if (i == 0)
                {
                    move_->indexStart = 0; move_->sizeArr = minrun;
                   // cout << "Index start: " << move_->indexStart << "; Size: " << move_->sizeArr << "; End: " << move_->indexStart + move_->sizeArr-1 << endl;
                    //outputArrayWithIndex(arr, move_->indexStart, move_->indexStart + move_->sizeArr - 1);
                    move_->next = new stack_();
                    move_ = move_->next;
                }
                else {
                    move_->indexStart = beforeMove->indexStart + beforeMove->sizeArr;
                    move_->sizeArr = minrun;
                   // cout << "Index start: " << move_->indexStart << "; Size: " << move_->sizeArr << "; End: " << move_->indexStart + move_->sizeArr-1 << endl;
                    //outputArrayWithIndex(arr, move_->indexStart, move_->indexStart + move_->sizeArr - 1);
                    if (i + 1 != sizeArr_info)
                    {
                        move_->next = new stack_();
                        beforeMove = beforeMove->next;
                        move_ = move_->next;
                    }
                }
            }
            move_->sizeArr = n - (beforeMove->indexStart + beforeMove->sizeArr);
            stack_* beforeBeforeMove;
            move_ = arr_info->next->next; // Z
            beforeMove = arr_info->next; // Y
            beforeBeforeMove = arr_info; // X

            for (__int64 i = 0; i < sizeArr_info; i++)
            {
                //Проверка на возможность слияния и слияние здесь
                if ((move_ != nullptr && beforeMove != nullptr && beforeBeforeMove != nullptr) && 
                    !((move_->sizeArr > beforeMove->sizeArr + beforeBeforeMove->sizeArr) &&
                    (beforeMove->sizeArr > beforeBeforeMove->sizeArr)))
                { // X > Y + Z и Y > Z - Если нарушилось хотя бы одно правило, слияние Y с меньшим из X, Z
                    //Слияние Y с меньшим из X, Z
                    if (move_->sizeArr <= beforeBeforeMove->sizeArr)
                    {
                        //Слияние X с Y
                        naturalMergeSort(arr, beforeBeforeMove->indexStart, beforeBeforeMove->indexStart + beforeBeforeMove->sizeArr - 1, beforeMove->indexStart, beforeMove->indexStart + beforeMove->sizeArr - 1);
                        beforeBeforeMove->sizeArr += beforeMove->sizeArr;
                        beforeMove = beforeMove->next;
                        move_ = move_->next;
                        delete beforeBeforeMove->next;
                        beforeBeforeMove->next = beforeMove;
                    }
                    else {
                        //Слияние Y с Z
                        naturalMergeSort(arr, beforeMove->indexStart, beforeMove->indexStart + beforeMove->sizeArr-1, move_->indexStart, move_->indexStart + move_->sizeArr - 1);
                        beforeMove->sizeArr += move_->sizeArr;
                        move_ = move_->next;
                        delete beforeMove->next;
                        beforeMove->next = move_;
                    } 
                    //Слияние завершено
                }
            }
            //Осталось 2 подмассива
            move_ = arr_info->next;
            beforeMove = arr_info;
            naturalMergeSort(arr, beforeMove->indexStart, beforeMove->indexStart + beforeMove->sizeArr - 1, move_->indexStart, move_->indexStart + move_->sizeArr-1);
            delete move_;
            delete beforeMove;
        }
        else {
            //Если в стеке может быть только 2 подмассива, то смысла создавать стек нет, просто сортируем
            //два подмассива слиянием.
            naturalMergeSort(arr, 0, minrun-1, minrun, n - 1);
        }
        
}
    
}