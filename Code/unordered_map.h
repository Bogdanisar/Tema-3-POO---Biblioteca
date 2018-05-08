#ifndef MTD_UNORDERED_MAP
#define MTD_UNORDERED_MAP

#include <vector>
#include <string>
#include <stdexcept>

template<typename Key>
struct Hasher {
    // unsigned int operator() (Key k) {
    //     return 1;
    // }
};

template<>
struct Hasher<int> {
    unsigned int operator() (int k) {
        return k;
    }
};

template<>
struct Hasher<long long> {
    unsigned int operator() (long long k) {
        return k;
    }
};

template<>
struct Hasher<unsigned long long> {
    unsigned int operator() (unsigned long long k) {
        return k;
    }
};

template<>
struct Hasher<std::string> {
    unsigned int operator() (const std::string& str) {
        unsigned int hash = 0;
        const int base = 307;

        for (auto c : str) {
            hash = hash * base + c * base;
        }

        return hash;
    }
};

namespace mtd {

    template< typename Key, typename Value, typename Hash = Hasher<Key> > 
    class unordered_map {
        public:
        class iterator {
            private:
            int i, j;
            const int vmod;
            std::vector< std::vector< std::pair<Key, Value> > >& v;

            friend unordered_map<Key, Value, Hash>;

            private:
            iterator(int _i, int _j, int _vmod, std::vector< std::vector< std::pair<Key, Value> > >& _v): 
            i(_i), j(_j), vmod(_vmod), v(_v)  {}
            
            public:

            bool operator== (const iterator& other) {
                return i == other.i && j == other.j && vmod == other.vmod && v == other.v;
            }

            bool operator!= (const iterator& other) {
                return !(*this == other);
            }

            const iterator& operator++ () {
                if (i >= mod) {
                    throw std::logic_error("Can't increment iterator after end!");
                }

                ++j;
                if (j >= (int)v[i].size()) {
                    ++i;
                    j = 0;

                    while (i < mod && (int)v[i].size() == 0) {
                        ++i;
                    }
                }

                return *this;
            }

            iterator operator++ (int) {
                iterator ret(*this);
                this->operator++();
                return ret;
            }

            const iterator& operator-- () {
                if (i < 0) {
                    throw std::logic_error("Can't decrement iterator before begin!");
                }

                --j;
                if (j < 0) {
                    --i;
                    while (i >= 0 && (int)v[i].size() == 0) {
                        --i;
                    }

                    if (i >= 0) {
                        j = v[i].size() - 1;
                    }
                }

                return *this;
            }

            virtual iterator operator-- (int) {
                iterator ret(*this);
                this->operator--();
                return ret;
            }

            std::pair<Key, Value>& operator* () {
                if (i < 0 || i >= mod) {
                    throw std::domain_error("Can't dereference map iterator; it is out of range!");
                }

                return v[i][j];
            }

            std::pair<Key, Value>* operator->() {
                if (i < 0 || i >= mod) {
                    throw std::domain_error("Can't dereference map iterator; it is out of range!");
                }

                return &(v[i][j]);
            }
        };

        private:
        static const int mod = 1e6 + 3;
        int sz;
        std::vector< std::vector< std::pair<Key, Value> > > v;

        public:
        unordered_map(): sz(0), v(mod) {}

        unordered_map& operator= (const unordered_map& other) {
            v = other.v;
            sz = other.sz;
        }

        Value& operator[] (Key k) {
            int idx = Hash()(k) % mod;

            unsigned int i = 0;
            for(; i < v[idx].size(); ++i) {
                if (v[idx][i].first == k) {
                    return v[idx][i].second;
                }
            }

            ++sz;
            v[idx].pb( {k, Value()} );
            return v[idx][v[idx].size() - 1].second;
        }

        void erase(Key k) {
            int idx = Hash()(k) % mod;

            unsigned int i = 0;
            for(; i < v[idx].size(); ++i) {
                if (v[idx][i].first == k) {
                    int last = v[idx].size() - 1;
                    swap(v[idx][last], v[idx][i]);
                    v[idx].pop_back();

                    --sz;
                    return;                    
                }
            }
        }

        int size() {
            return sz;
        }

        iterator begin() {
            int i = 0, j = 0;
            while (v[i].size() == 0) {
                ++i;
            }

            return iterator(i, j, mod, v);
        }

        iterator end() {
            return iterator(mod, 0, mod, v);
        }

        bool find(Key k) {
            int idx = Hash()(k) % mod;

            unsigned int i = 0;
            for(; i < v[idx].size(); ++i) {
                if (v[idx][i].first == k) {
                    return true;
                }
            }

            return false;
        }
    };
}

#endif