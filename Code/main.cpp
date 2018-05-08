#include <bits/stdc++.h>
#include <typeinfo>
    
using namespace std;
    
#if 1
    #define pv(x) cout<<#x<<" = "<<(x)<<"; ";cout.flush()
    #define pn cout<<endl
#else
    #define pv(x)
    #define pn
#endif
    
#ifdef INFOARENA
    ifstream in(".in");
    ofstream out(".out");
#else 
    #define in cin
    #define out cout
#endif
    
using ll = long long;
using ull = unsigned long long;
using ui = unsigned int;
#define pb push_back
#define mp make_pair
const int NMax = 1e5 + 500;
const ll inf_ll = 1e18 + 5;
const int inf_int = 1e9 + 5;
const ll lim = 1e5;
using zint = int;

#include "unordered_map.h"
#include "biblioteca.h"

struct elem {
    int x,y,z;
    elem(int _x = 0,int _y = 0,int _z = 0): x(_x), y(_y), z(_z) {}
    elem operator+ (elem other) {
        return elem(x + other.x, y + other.y, z + other.z);
    }
    friend std::ostream& operator<< (std::ostream& out, const elem& e) {
        out << e.x << ' ' << e.y << ' ' << e.z;
        return out;
    }
};

int main() {
    cin.sync_with_stdio(false);
    cin.tie(0);
    
    // mtd::unordered_map< string, int > mp;
    // mp["ala"] = 1;
    // mp["baba"];
    // ++mp["hehe"];
    // ++mp["hehe"];
    // ++mp["hehe"];
    // ++mp["hehe"];
    // mp["ala"] = 0;
    // mp["ala"] = 5;
    // mp["ala"]--;

    // for (mtd::unordered_map< string, int >::iterator it = mp.begin(); it != mp.end(); ++it) {
    //     pv(it->first); pv(it->second); pn;
    // }

    // for (mtd::unordered_map< string, int >::iterator it = mp.end(); ;) {
    //     --it;
    //     pv(it->first); pv(it->second); pn;
    // }

    try {
        mtd::Biblioteca<elem>& b1 = mtd::Biblioteca<elem>::getInstance();
        b1.add(1123ll, "nume");
        b1.add("11String","StringInFirst");
        // mtd::Biblioteca<elem>::deleteInstance();


        mtd::Biblioteca<elem>& b = mtd::Biblioteca<elem>::getInstance();
        b.add("String1", "name1");
        b.add("StringOther", "name1");
        b.add("String2", "name2");
        mtd::Address a1("rom","tr","rosiori","strada1",23);
        mtd::Address a2("ang","lond","Londra","strada2",911);
        b.add(a1,"myAddress1");
        b.add(a2,"myAddress2");

        mtd::Complex c1(0.3,1.0);
        mtd::Complex c2(1.3,1.1);

        b.add(c1, "complex1");
        b.add(c2, "complex2");
        b.add(c2, "complex1");

        b.add(100ll, "intreg1");
        b.add(150ll, "intreg2");
        b.add(150ll, "intreg2");
        b.add(150ll, "intreg2");

        // b.erase(0);

        b.add(555ll);
        b.add(555ll);
        b.add(555ll);
        b.add("myUnnamed string");
        int idx = b.add(555ll);

        b.erase("complex1");
        b.erase("intreg1asdasdasds");
        b.erase(14);

        mtd::Biblioteca<elem>::Container c;
        // c = b.find(idx);
        // cout << c << "\n\n";
        // c = b.find("7");
        // pv(c.getPtr()); pn;
        // cout << c << "\n\n";

        // vector<mtd::Biblioteca<elem>::Container> v = b.search("1");

        // for (auto c : v) {
        //     cout << c << '\n';
        // }

        idx = b.add("Mama", "myString");
        //b.erase(idx);
        b.add(" are","myString");
        b.add(" mere!","myString");

        cout << b.find("myString") << ' ';

        idx = b.add(mtd::Complex(1.1, 2.2), "myComplex");
        b.erase(idx);
        b.add(mtd::Complex(1.1, 2.2), "myComplex");
        b.add(mtd::Complex(1.1, 2.2), "myComplex");

        cout << b.find("myComplex") << ' ';

        idx = b.add(mtd::Address("","a","b","c",2), "myAsadsad");
        cout << b.find(idx) << '\n';

        idx = b.add(123ll, "myInteger");
        b.erase(idx);
        idx = b.add(123ll, "myInteger");
        idx = b.add(123ll, "myInteger");
        cout << b.find("myInteger") << '\n';

        b.add(elem(1,-1,0), "myElem");
        b.add(elem(1,0,1), "myElem");
        b.add(elem(10,0,0), "myElem");
        mtd::Biblioteca<elem>& br = mtd::Biblioteca<elem>::getInstance();

        out << br.find("myElem") << '\n';

    }
    catch(const exception& e) {
        pv(e.what()); pn;
    }
    cout << "The program has exited successfully!" << '\n';
    
    return 0;
}