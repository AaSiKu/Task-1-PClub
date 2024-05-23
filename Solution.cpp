#include <bits/stdc++.h>
using namespace std;

// Defining struct for linkedList
struct LinkedList
{
    int data;
    LinkedList *next;
};

// Returns a pair containing lenght of the Linked list and whether it is circular or not.
pair<int, int> LenLinkedList(LinkedList *head)
{
    int count = 0;
    int head_value = 0;
    int is_circular = 0;
    LinkedList *temp = head;
    while (temp != NULL)
    {
        if (temp->data == head_value)
        {
            is_circular = 1;
            break;
        }
        if (head_value == 0)
        {
            head_value = temp->data;
        }
        count++;
        temp = temp->next;
    }
    pair<int, int> result;
    result.first = count;
    result.second = is_circular;
    return result;
}

// Iterates over the vector and print value in each cell.
void PrintResult(vector<int> vec)
{
    for (int x = 0; x < vec.size(); x++)
    {
        printf("%d ", vec[x]);
    }
    cout << endl;
}

int main()
{
    int n = 12;
    vector<pair<int, int>> preference;
    set<int> Remaining;

    for (int i = 0; i < n; i++)
    {
        int a, b;
        cin >> a >> b;
        Remaining.insert(a);
        preference.push_back({a, b});
    }

    vector<pair<LinkedList *, LinkedList *>> answer; // Contains a pair , first LinkedList* points to head of the linked list and the second to the tail of the linked list.

    int Found = 0;
    auto it = preference.begin();

    // Putting students in different linked lists on the basis of who prefers whom.
    while (it != preference.end())
    {

        if (Remaining.find(it->first) == Remaining.end() || Remaining.find(it->second) == Remaining.end())
        {
            continue;
        }

        Found = 0;
        for (int x = 0; x < answer.size(); x++)
        {
            if (answer[x].second->data == it->first)
            {
                Found = 1;
                if (it->second == answer[x].first->data)
                {
                    answer[x].second->next = answer[x].first;
                    preference.erase(it);
                }
                else
                {
                    LinkedList *temp = new LinkedList();
                    temp->data = it->first;
                    temp->next = new LinkedList();
                    temp->next->data = it->second;
                    temp->next->next = NULL;
                    answer[x].second->next = temp->next;
                    answer[x].second = temp->next;
                    preference.erase(it);
                    it = preference.begin();
                }
                break;
            }
        }

        if (Found == 0)
        {

            LinkedList *temp = new LinkedList();
            temp->data = it->first;
            temp->next = new LinkedList();
            temp->next->data = it->second;
            temp->next->next = NULL;
            answer.push_back({temp, temp->next});
            preference.erase(it);
            it = preference.begin();
        }
    }

    // Printing the linked lists
    for (int x = 0; x < answer.size(); x++)
    {
        int head_value = 0;
        LinkedList *temp = answer[x].first;
        while (temp != nullptr && temp->data != head_value)
        {
            if (head_value == 0)
            {
                head_value = temp->data;
            }
            temp = temp->next;
        }
    }
    int doubleSharing = 3;
    int tripleSharing = 2;

    // Printing results
    for (int x = 0; x < answer.size(); x++)
    {
        vector<int> Result;
        pair<int, int> result = LenLinkedList(answer[x].first);
        if (result.first == 2 && result.second == 1 && doubleSharing > 0)
        {
            doubleSharing--;
            int head_value = 0;
            while (answer[x].first != NULL)
            {
                if (answer[x].first->data == head_value)
                {
                    break;
                }
                if (head_value == 0)
                {
                    head_value = answer[x].first->data;
                }
                Result.push_back(answer[x].first->data);
                Remaining.erase(answer[x].first->data);
                answer[x].first = answer[x].first->next;
            }
        }
        else if (result.first == 3 && result.second == 1 && tripleSharing > 0)
        {
            int head_value = 0;
            tripleSharing--;
            while (answer[x].first != NULL)
            {
                if (answer[x].first->data == head_value)
                {
                    break;
                }
                if (head_value == 0)
                {
                    head_value = answer[x].first->data;
                }
                Result.push_back(answer[x].first->data);
                Remaining.erase(answer[x].first->data);
                answer[x].first = answer[x].first->next;
            }
        }
        if (Result.size() != 0)
        {
            sort(Result.begin(), Result.end());
            PrintResult(Result);
        }
    }

    for (int x = 0; x < answer.size(); x++)
    {
        vector<int> Result;
        while (answer[x].first->next != NULL && Remaining.find(answer[x].first->data) != Remaining.end())
        {
            if (answer[x].first->next != NULL && Remaining.find(answer[x].first->next->data) != Remaining.end())
            {
                if (doubleSharing > 0)
                {
                    Result = {answer[x].first->data, answer[x].first->next->data};
                    sort(Result.begin(), Result.end());
                    PrintResult(Result);
                    Remaining.erase(answer[x].first->data);
                    Remaining.erase(answer[x].first->next->data);

                    answer[x].first = answer[x].first->next->next;
                    doubleSharing--;
                    continue;
                }
                else if (answer[x].first->next->next != NULL)
                {
                    Result = {answer[x].first->data, answer[x].first->next->data, answer[x].first->next->next->data};
                    sort(Result.begin(), Result.end());
                    PrintResult(Result);

                    Remaining.erase(answer[x].first->data);
                    Remaining.erase(answer[x].first->next->data);
                    Remaining.erase(answer[x].first->next->next->data);
                    answer[x].first = answer[x].first->next->next->next;
                    doubleSharing--;
                    continue;
                }
            }
            answer[x].first = answer[x].first->next;
        }
    }
    for (auto it = Remaining.begin(); it != Remaining.end(); it++)
    {
        cout << *it << " ";
    }
    return 0;
}
