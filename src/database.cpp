#include <iostream>

using namespace std;

int main(){

    long id;
    string carModel;
    double carPrice;
    vector<string> cararray;


    public void AddCar()
    {
        cin >> carModel;
        cin >> carPrice;
        cararray.push_back(id, carModel, carPrice);
    }

    public void RemoveCar()
    {
        cin >> idToDelete;

        for(int i = 0; i < cararray.size() ; i++)
            {
                if (cararray[i].find(idToDelete) != std::string::npos)
                {
                    cararray.erase (cararray.begin()+i);
                    break;
                }
            }
    }

    public void getAll()
    {
        for(int i = 0; i < cararray.size() ; i++)
            {
            cout << i << " " << cararray[i] <<  " " ; ;
            }
    }

    public void getCar()
    {
        cin >> idToSelect;

        for(int i = 0; i < cararray.size() ; i++)
            {
                if (cararray[i].find(idToSelect) != std::string::npos)
                {
                    cout << cararray[idToSelect] << carModel << carPrice;
                }
            }
    }

}
