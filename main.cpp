#include <iostream>
#include <stack>

using namespace std;

int* subset;

void print_subset(int* a,int n)
{
    cout << '{';
    if(0 < n)
        cout << a[0];
    for(int i = 1;i < n;i++)
        cout << ", " << a[i] ;
    cout << "}\n";
}

void recursiveGenerateSubsets(int* a,int n,int ichoice,int isubset)
{
    if(ichoice == n)
    {
        print_subset(subset,isubset);
        return;
    }

    recursiveGenerateSubsets(a,n,ichoice + 1,isubset);
    subset[isubset] = a[ichoice];
    recursiveGenerateSubsets(a,n,ichoice + 1,isubset + 1);
    return;
}

void recursiveGenerateSubsets(int* a,int n)
{
    subset = new int[n];
    recursiveGenerateSubsets(a,n,0,0);
    delete []subset;
    return;
}

enum call_type {Generate,Select};

struct generate_subsets_call
{
    call_type type;
    int ichoice, isubset;
};

void GenerateSubsets(int* a,int n)
{
    subset = new int[n];
    stack <generate_subsets_call> virtual_runtime_stack;
    generate_subsets_call stcall, curr_call;
    stcall.type = Generate;
    stcall.ichoice = 0;
    stcall.isubset = 0;
    virtual_runtime_stack.push(stcall);
    while(!virtual_runtime_stack.empty())
    {
        curr_call = virtual_runtime_stack.top();
        virtual_runtime_stack.pop();

        if(curr_call.ichoice == n)
        {
            print_subset(subset,curr_call.isubset);
            continue;
        }
        if(curr_call.type == Select)
        {
            subset[curr_call.isubset] = a[curr_call.ichoice];
            continue;
        }

        generate_subsets_call call1, call2, call3;

        call1.type = Generate;
        call2.type = Select;
        call3.type = Generate;

        call1.ichoice = curr_call.ichoice + 1;
        call2.ichoice = curr_call.ichoice;
        call3.ichoice = curr_call.ichoice + 1;

        call1.isubset = curr_call.isubset;
        call2.isubset = curr_call.isubset;
        call3.isubset = curr_call.isubset + 1;

        virtual_runtime_stack.push(call3);
        virtual_runtime_stack.push(call2);
        virtual_runtime_stack.push(call1);
    }

    delete []subset;
    return;
}

int main()
{

    int a[]={1,3,8}; int n=sizeof(a)/sizeof(a[0]);

    cout << "Recursive ALL Possible Subsets Generation :\n";
    recursiveGenerateSubsets(a, n);
    cout << "\nIterative ALL Possible Subsets Generation :\n";
    GenerateSubsets(a,n);

    return 0;
}
