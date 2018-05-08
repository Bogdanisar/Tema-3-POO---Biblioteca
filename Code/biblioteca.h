#ifndef MTD_BIBLIOTECA
#define MTD_BIBLIOTECA

#include <iostream>
#include <string>
#include <sstream>
#include <vector>
#include <exception>
#include <stdexcept>
#include "unordered_map.h"

namespace mtd {

    struct Complex {
        double x,y;
        Complex(double _x = 0.0, double _y = 0.0): x(_x), y(_y) {}
    };

    std::ostream& operator<< (std::ostream& out, const Complex& c) {
        out << c.x << ' ' << c.y;
        return out;
    }

    struct Address {
        std::string country, county, city, street;
        int number;
        Address(const std::string& _c1, const std::string& _c2, const std::string& _city, const std::string& _street, int _number):
        country(_c1), county(_c2), city(_city), street(_street), number(_number) {
        
        }
    };

    std::ostream& operator<< (std::ostream& out, const Address& c) {
        out << c.country << ", ";
        out << c.county << ", ";
        out << c.city << " at ";
        out << c.street << ", ";
        out << c.number;
        return out;
    }

    enum class ElementType {
        STRING, INTEGER, COMPLEX, ADDRESS, OTHER
    };

    struct placeholder {  };
    std::ostream& operator<< (std::ostream& out, const placeholder& c) {
        placeholder p = c;
        p = p;
        return out;
    }

    template<typename OtherType = placeholder>
    class Biblioteca {
        private:
        class Element {
            public:

            virtual ElementType getType() = 0;
            virtual ~Element() {}
            virtual std::string& getString() = 0;
            virtual long long& getInteger() = 0;
            virtual Complex& getComplex() = 0;
            virtual Address& getAddress() = 0;
            virtual OtherType& getOther() = 0;

            virtual void print(std::ostream&) const = 0;

            friend std::ostream& operator<< (std::ostream& out, const Element& e) {
                e.print(out);
                return out;
            }
        };

        class StringElement: public Element {
            friend Biblioteca;
            public:

            std::string member;

            StringElement(const std::string& p) {
                member = p;
            }

            ElementType getType() {
                return ElementType::STRING;
            }
            
            virtual std::string& getString() {
                return member;
            }
            virtual long long& getInteger() {
                throw std::logic_error("Requested type differs from contained type!");
                // return 0;
            }
            virtual Complex& getComplex() {
                throw std::logic_error("Requested type differs from contained type!");                
                // return Complex();
            }
            virtual Address& getAddress() {
                throw std::logic_error("Requested type differs from contained type!");                
                // return Address("", "", "", "", 0);
            }
            virtual OtherType& getOther() {
                throw std::logic_error("Requested type differs from contained type!");                
                // return OtherType();
            }
            
            virtual void print(std::ostream& out) const {
                out << member;
            }

            virtual ~StringElement() {}
        };

        class IntegerElement: public Element {
            friend Biblioteca;
            public:

            long long member;

            IntegerElement(const long long& p): member(p) {}

            ElementType getType() {
                return ElementType::INTEGER;
            }
            
            virtual std::string& getString() {
                throw std::logic_error("Requested type differs from contained type!");
                // return "";
            }
            virtual long long& getInteger() {
                return member;
            }
            virtual Complex& getComplex() {
                throw std::logic_error("Requested type differs from contained type!");                
                // return Complex();
            }
            virtual Address& getAddress() {
                throw std::logic_error("Requested type differs from contained type!");                
                // return Address("", "", "", "", 0);
            }
            virtual OtherType& getOther() {
                throw std::logic_error("Requested type differs from contained type!");                
                // return OtherType();
            }

            virtual void print(std::ostream& out) const {
                out << member;
            }

            virtual ~IntegerElement() {}
        };
        
        class ComplexElement: public Element {
            friend Biblioteca;
            public:

            Complex member;

            ComplexElement(const Complex& p): member(p) {}

            ElementType getType() {
                return ElementType::COMPLEX;
            }
            
            virtual std::string& getString() {
                throw std::logic_error("Requested type differs from contained type!");
                // return "";
            }
            virtual long long& getInteger() {
                throw std::logic_error("Requested type differs from contained type!");                
                // return 0;
            }
            virtual Complex& getComplex() {
                return member;
            }
            virtual Address& getAddress() {
                throw std::logic_error("Requested type differs from contained type!");                
                // return Address("", "", "", "", 0);
            }
            virtual OtherType& getOther() {
                throw std::logic_error("Requested type differs from contained type!");                
                // return OtherType();
            }
            
            virtual void print(std::ostream& out) const {
                out << member;
            }

            virtual ~ComplexElement() {}
        };
        
        class AddressElement: public Element {
            friend Biblioteca;
            public:

            Address member;

            AddressElement(const Address& p): member(p) {}

            ElementType getType() {
                return ElementType::ADDRESS;
            }
            
            virtual std::string& getString() {
                throw std::logic_error("Requested type differs from contained type!");
                // return "";
            }
            virtual long long& getInteger() {
                throw std::logic_error("Requested type differs from contained type!");                
                // return 0;
            }
            virtual Complex& getComplex() {
                throw std::logic_error("Requested type differs from contained type!");                
                // return Complex();
            }
            virtual Address& getAddress() {
                return member;
            }
            virtual OtherType& getOther() {
                throw std::logic_error("Requested type differs from contained type!");                
                // return OtherType();
            }
            
            virtual void print(std::ostream& out) const {
                out << member;
            }

            virtual ~AddressElement() {}
        };
        
        class OtherElement: public Element {
            friend Biblioteca;
            public:

            OtherType member;

            OtherElement(const OtherType& p): member(p) {}

            ElementType getType() {
                return ElementType::OTHER;
            }
            
            virtual std::string& getString() {
                throw std::logic_error("Requested type differs from contained type!");
                // return "";
            }
            virtual long long& getInteger() {
                throw std::logic_error("Requested type differs from contained type!");                
                // return 0;
            }
            virtual Complex& getComplex() {
                throw std::logic_error("Requested type differs from contained type!");                
                // return Complex();
            }
            virtual Address& getAddress() {
                throw std::logic_error("Requested type differs from contained type!");                
                // return Address("", "", "", "", 0);
            }
            virtual OtherType& getOther() {
                return member;
            }
            
            virtual void print(std::ostream& out) const {
                out << member;
            }

            virtual ~OtherElement() {}
        };

        public:
        class Container {
            friend Biblioteca;
            std::string name;
            unsigned long long id;
            Element* m;

            private:
            Container(const std::string& _name, unsigned long long _id, Element* _m = nullptr):
            name(_name), id(_id), m(_m) {
                
            };

            public:
            Container(): name(""), id(0), m(nullptr) {}

            Container(const Container& other): name(other.name), id(other.id) {
                if (other.m == nullptr) {
                    m = nullptr;
                    return;
                }

                switch (other.m->getType()) {
                    case ElementType::STRING: {
                        m = new StringElement(other.m->getString());
                        break;
                    }
                    case ElementType::INTEGER: {
                        m = new IntegerElement(other.m->getInteger());
                        break;
                    }
                    case ElementType::COMPLEX: {
                        m = new ComplexElement(other.m->getComplex());
                        break;
                    }
                    case ElementType::ADDRESS: {
                        m = new AddressElement(other.m->getAddress());
                        break;
                    }
                    case ElementType::OTHER: {
                        m = new OtherElement(other.m->getOther());
                        break;
                    }
                }
            }

            Container& operator= (const Container& other) {
                if (this == &other) {
                    return *this;
                }

                name = other.name;
                id = other.id;
                if (m != 0) {
                    delete m;
                }

                if (other.m == nullptr) {
                    m = nullptr;
                    return *this;
                }

                switch (other.m->getType()) {
                    case ElementType::STRING: {
                        m = new StringElement(other.m->getString());
                        break;
                    }
                    case ElementType::INTEGER: {
                        m = new IntegerElement(other.m->getInteger());
                        break;
                    }
                    case ElementType::COMPLEX: {
                        m = new ComplexElement(other.m->getComplex());
                        break;
                    }
                    case ElementType::ADDRESS: {
                        m = new AddressElement(other.m->getAddress());
                        break;
                    }
                    case ElementType::OTHER: {
                        m = new OtherElement(other.m->getOther());
                        break;
                    }
                }

                return *this;
            }

            friend std::ostream& operator<< (std::ostream& out, const Container& c) {
                out << "Container name: " << c.name << "; Container id: " << c.id << ";\nElement data: ";
                if (c.getPtr() == nullptr) {
                    out << "Null data;";
                }
                else {
                    Element& e = *(c.getPtr());
                    e.print(out);
                    out << ";";
                }
                return out;
            }

            public:
            Element* getPtr() const {
                return m;
            }
            unsigned long long getId() const {
                return id;
            }
            std::string getName() const {
                return name;
            }

            ~Container() {
                if (m != nullptr) {
                    delete m;
                }
            }
        };
      
        private:
        static const int mod = 1e6 + 3;
        static const char FORBIDDEN = '#';
        std::vector< std::vector< Container > > v;
        unsigned long long sz, currId;
        mtd::unordered_map<unsigned long long, int> idToIdx;

        std::string fixStr(const std::string& other) {
            if (other.find(FORBIDDEN) != std::string::npos) {
                throw std::invalid_argument( std::string("The name can't containt character ").append(1, FORBIDDEN) );
            }
            if (other == "") {
                std::stringstream ss;
                ss << FORBIDDEN << currId;
                return ss.str();
            }

            return other;
        }

        bool check(const std::string& keyword, const std::string& mine) {
            return mine.find(keyword) != std::string::npos;
        }
        bool check(const std::string& keyword, const long long& mine) {
            std::stringstream ss;
            ss << mine;
            return ss.str().find(keyword) != std::string::npos;
        }
        bool check(const std::string& keyword, const Complex& mine) {
            std::stringstream ss;
            ss << mine.x << ' ' << mine.y;
            return ss.str().find(keyword) != std::string::npos;
        }

        bool check(const std::string& keyword, const Container& mine) {
            if (check(keyword, mine.name) || check(keyword, mine.id)) {
                return true;
            }

            bool flag = false;
            Element& r = *(mine.m);
            switch(r.getType()) {
                case ElementType::STRING: {
                    flag |= check(keyword, r.getString());
                    break;   
                }
                case ElementType::INTEGER: {
                    flag |= check(keyword, r.getInteger());
                    break;
                }
                case ElementType::COMPLEX: {
                    flag |= check(keyword, r.getComplex());
                    break;
                }
                case ElementType::ADDRESS: {
                    Address a = r.getAddress();
                    flag |= check(keyword, a.country);
                    flag |= check(keyword, a.county);
                    flag |= check(keyword, a.city);
                    flag |= check(keyword, a.street);
                    flag |= check(keyword, a.number);                    
                    break;
                }
                default: {
                    break;
                }
            }

            return flag;
        }      

        private:
        Biblioteca(): v(mod), sz(0), currId(0) {}
        Biblioteca(const Biblioteca& other) = delete;
        Biblioteca& operator= (const Biblioteca& other) = delete;
        ~Biblioteca() {};

        public:

        unsigned long long add(const std::string& infoStr, std::string name = "") {
            name = fixStr(name);

            unsigned int idx = Hasher<std::string>()(name) % mod;

            unsigned int i = 0;
            for(; i < v[idx].size(); ++i) {
                if (v[idx][i].name == name) {
                    if (v[idx][i].m->getType() != ElementType::STRING) {
                        throw std::invalid_argument("You can't add different element types with the same name!");
                    }

                    std::string& str = v[idx][i].m->getString();
                    str.append(infoStr);

                    return v[idx][i].id;
                }
            }

            Element* p = new StringElement(infoStr);
            Container c(name, currId, p);
            idToIdx[currId] = idx;

            v[idx].pb(c);
            ++currId;
            return currId-1;
        }

        unsigned long long add(const long long& info, std::string name = "") {
            name = fixStr(name);

            unsigned int idx = Hasher<std::string>()(name) % mod;

            unsigned int i = 0;
            for(; i < v[idx].size(); ++i) {
                if (v[idx][i].name == name) {
                    if (v[idx][i].m->getType() != ElementType::INTEGER) {
                        throw std::invalid_argument("You can't add different element types with the same name!");
                    }

                    long long& num = v[idx][i].m->getInteger();
                    num += info;

                    return v[idx][i].id;
                }
            }

            Element* p = new IntegerElement(info);
            Container c(name, currId, p);
            idToIdx[currId] = idx;

            v[idx].pb(c);
            ++currId;
            return currId-1;
        }
        
        unsigned long long add(const Complex& info, std::string name = "") {
            name = fixStr(name);

            unsigned int idx = Hasher<std::string>()(name) % mod;

            unsigned int i = 0;
            for(; i < v[idx].size(); ++i) {
                if (v[idx][i].name == name) {
                    if (v[idx][i].m->getType() != ElementType::COMPLEX) {
                        throw std::invalid_argument("You can't add different element types with the same name!");
                    }

                    Complex& complex = v[idx][i].m->getComplex();
                    complex.x += info.x;
                    complex.y += info.y;

                    return v[idx][i].id;
                }
            }
            
            Element* p = new ComplexElement(info);
            Container c(name, currId, p);
            idToIdx[currId] = idx;

            v[idx].pb(c);
            ++currId;
            return currId - 1;
        }

        unsigned long long add(const Address& info, std::string name = "") {
            name = fixStr(name);

            unsigned int idx = Hasher<std::string>()(name) % mod;

            unsigned int i = 0;
            for(; i < v[idx].size(); ++i) {
                if (v[idx][i].name == name) {
                    throw std::invalid_argument("You can't add addresses! You have two addresses with the same name!");
                }
            }

            Element* p = new AddressElement(info);
            Container c(name, currId, p);
            idToIdx[currId] = idx;

            v[idx].pb(c);
            ++currId;
            return currId - 1;
        }

        unsigned long long add(const OtherType& info, std::string name = "") {
            name = fixStr(name);

            unsigned int idx = Hasher<std::string>()(name) % mod;

            unsigned int i = 0;
            for(; i < v[idx].size(); ++i) {
                if (v[idx][i].name == name) {
                    if (v[idx][i].m->getType() != ElementType::OTHER) {
                        throw std::invalid_argument("You can't add different element types with the same name!");
                    }
                    v[idx][i].m->getOther() = v[idx][i].m->getOther() + info;
                    return v[idx][i].id;
                }
            }

            Element* p = new OtherElement(info);
            Container c(name, currId, p);
            idToIdx[currId] = idx;

            v[idx].pb(c);
            ++currId;
            return currId - 1;
        }

        void erase(const std::string& name) {
            unsigned int idx = Hasher< std::string >()(name) % mod;

            unsigned int i = 0;
            for(; i < v[idx].size(); ++i) {
                if (v[idx][i].name == name) {
                    unsigned int last = v[idx].size() - 1;
                    swap( v[idx][last], v[idx][i] );
                    v[idx].pop_back();
                    return;
                }
            }
        }

        void erase(unsigned long long id) {
            unsigned int idx = idToIdx[id];

            unsigned int i = 0;
            for(; i < v[idx].size(); ++i) {
                if (v[idx][i].id == id) {
                    unsigned int last = v[idx].size() - 1;
                    swap( v[idx][last], v[idx][i] );
                    v[idx].pop_back();
                    return;
                }
            }
        }

        Container find(const std::string& name) {
            unsigned int idx = Hasher< std::string >()(name) % mod;

            unsigned int i = 0;
            for(; i < v[idx].size(); ++i) {
                if (v[idx][i].name == name) {
                    return v[idx][i];
                }
            }

            return Container("",-1);
        }

        Container find(unsigned long long id) {
            unsigned int idx = idToIdx[id];

            unsigned int i = 0;
            for(; i < v[idx].size(); ++i) {
                if (v[idx][i].id == id) {
                    return v[idx][i];
                }
            }

            return Container("",-1);
        }

        std::vector<Container> search(const std::string& keyword) {
            std::vector<Container> ans;

            for (unsigned int i = 0; i < mod; ++i) {
                for (Container& c : v[i]) {
                    if (check(keyword, c)) {
                        ans.push_back(c);
                    }
                }
            }

            return ans;
        }

        private:
        static Biblioteca* ptr;

        public:
        static Biblioteca& getInstance() {
            if (ptr == nullptr) {
                ptr = new Biblioteca();
            }
            
            return *ptr;
        }

        static void deleteInstance() {
            if (ptr != nullptr) {
                delete ptr;
                ptr = nullptr;
            }
        }
    };

    template<typename otherType>
    Biblioteca<otherType>* Biblioteca<otherType>::ptr = nullptr;

    template<> class Biblioteca<long long> {Biblioteca() = delete;};
    template<> class Biblioteca<unsigned long long> {Biblioteca() = delete;};
    template<> class Biblioteca<int> {Biblioteca() = delete;};
    template<> class Biblioteca<unsigned int> {Biblioteca() = delete;};
    template<> class Biblioteca<short> {Biblioteca() = delete;};
    template<> class Biblioteca<unsigned short> {Biblioteca() = delete;};
    template<> class Biblioteca<double> {Biblioteca() = delete;};
    template<> class Biblioteca<float> {Biblioteca() = delete;};
    template<> class Biblioteca<long double> {Biblioteca() = delete;};
    template<> class Biblioteca<std::string> {Biblioteca() = delete;};
    template<> class Biblioteca<Complex> {Biblioteca() = delete;};
    template<> class Biblioteca<Address> {Biblioteca() = delete;};
    template<> class Biblioteca<bool> {Biblioteca() = delete;};
};

#endif