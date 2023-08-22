#include <iostream>
#include <fstream>
#include <vector>
#include <tuple>
#include <climits>

#define INF INT_MAX


#define TASK 100

using namespace std;

vector<tuple<double,double,double>> counting_sort(ostream &output,vector<tuple<double,double,double>> &a){

    double massimo=0.0;
    double minimo=INF;
    double max_min;

    for(int i=0;i<a.size();i++){
        massimo=max(massimo,get<0>(a[i]));
        minimo=min(minimo,get<0>(a[i]));
    }
    max_min=massimo-minimo;
    vector<int> c(max_min+1,0);
    vector<tuple<double,double,double>> b(a.size());
    
    for(int i=0;i<a.size();i++)
        c[get<0>(a[i])-minimo]++;
    
    for(int i=1;i<=max_min;i++)
        c[i]+=c[i-1];

    for(int i=b.size()-1;i>=0;i--){
        b[c[get<0>(a[i])-minimo]-1]=make_tuple(get<0>(a[i]),get<1>(a[i]),get<2>(a[i]));
        --c[get<0>(a[i])-minimo];
    }
    for(int i=0;i<=max_min;i++){
    output<<c[i]<<" ";
    }

    return b;
}

void print_array(ostream &output,vector<tuple<double,double,double>> &b){
    for(int i=0;i<b.size();i++)
        output<<"("<<get<0>(b[i])/10<<" "<<get<1>(b[i])/10<<" "<<get<2>(b[i])/10<<") ";
    output<<endl;
}

int main(){
    ifstream input("input.txt");
    ofstream output("output.txt");

    int length;
    string temp1;
    string temp2;
    string temp3;
    vector<tuple<double,double,double>> array;
    vector<tuple<double,double,double>> res;

    for(int i=0;i<TASK;i++){
        input>>length;
        array.resize(0);
        for(int j=0;j<length;j++){
            input>>temp1>>temp2>>temp3;
            array.push_back(make_tuple(stod(temp1.substr(1,temp1.length()-1))*10,stod(temp2)*10,stod(temp3.substr(0,temp3.length()-1))*10));

        }
        
        res=counting_sort(output,array);
        print_array(output,res);
    
    }

}